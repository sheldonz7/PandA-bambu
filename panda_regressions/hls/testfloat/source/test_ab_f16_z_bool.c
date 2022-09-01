
/*============================================================================

This C source file is part of TestFloat, Release 3e, a package of programs for
testing the correctness of floating-point arithmetic complying with the IEEE
Standard for Floating-Point, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015, 2017 The Regents of the University of
California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#include "platform.h"

#include "genCases.h"
#include "softfloat.h"
#include "testLoops.h"
#include "verCases.h"
#include "writeCase.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef FLOAT16

#pragma STDC FENV_ACCESS ON

void test_ab_f16_z_bool(bool trueFunction(float16_t, float16_t), bool subjFunction(float16_t, float16_t))
{
   int count;
   bool trueZ;
   uint_fast8_t trueFlags;
   bool subjZ;
   uint_fast8_t subjFlags;

   genCases_f16_ab_init();
   genCases_writeTestsTotal(testLoops_forever);
   verCases_errorCount = 0;
   verCases_tenThousandsCount = 0;
   count = 10000;
   while(!genCases_done || testLoops_forever)
   {
      genCases_f16_ab_next();
      *testLoops_trueFlagsPtr = 0;
      trueZ = trueFunction(genCases_f16_a, genCases_f16_b);
      trueFlags = *testLoops_trueFlagsPtr;
      testLoops_subjFlagsFunction();
      subjZ = subjFunction(genCases_f16_a, genCases_f16_b);
      subjFlags = testLoops_subjFlagsFunction();
      --count;
      if(!count)
      {
         verCases_perTenThousand();
         count = 10000;
      }
      if((trueZ != subjZ) || (verCases_checkExcFlags && trueFlags != subjFlags))
      {
         if(!verCases_checkNaNs && (f16_isSignalingNaN(genCases_f16_a) || f16_isSignalingNaN(genCases_f16_b)))
         {
            trueFlags |= softfloat_flag_invalid;
         }
         if((trueZ != subjZ) || (verCases_checkExcFlags && trueFlags != subjFlags))
         {
            ++verCases_errorCount;
            verCases_writeErrorFound(10000 - count);
            writeCase_ab_f16(genCases_f16_a, genCases_f16_b);
            writeCase_z_bool(trueZ, trueFlags, subjZ, subjFlags);
            if(verCases_errorCount == verCases_maxErrorCount)
               break;
         }
      }
   }
   verCases_writeTestsPerformed(10000 - count);
}

#endif
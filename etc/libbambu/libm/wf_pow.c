/**
 * Porting of the libm library to the PandA framework
 * starting from the original FDLIBM 5.3 (Freely Distributable LIBM) developed by SUN
 * plus the newlib version 1.19 from RedHat and plus uClibc version 0.9.32.1 developed by Erik Andersen.
 * The author of this port is Fabrizio Ferrandi from Politecnico di Milano.
 * The porting fall under the LGPL v2.1, see the files COPYING.LIB and COPYING.LIBM_PANDA in this directory.
 * Date: September, 11 2013.
 */
/* wf_pow.c -- float version of w_pow.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * wrapper powf(x,y) return x**y
 */

#include "math_privatef.h"
#ifndef _IEEE_LIBM
#include <errno.h>
#endif

float powf(float x, float y) /* wrapper powf */
{
#ifdef _IEEE_LIBM
   return __hide_ieee754_powf(x, y);
#else
   float z;
   struct exception exc;
   z = __hide_ieee754_powf(x, y);
   if(_LIB_VERSION == _IEEE_ || isnanf(y))
      return z;
   if(isnanf(x))
   {
      if(y == (float)0.0)
      {
         /* powf(NaN,0.0) */
         /* error only if _LIB_VERSION == _SVID_ & _XOPEN_ */
         exc.type = DOMAIN;
         exc.name = "powf";
         exc.err = 0;
         exc.arg1 = (double)x;
         exc.arg2 = (double)y;
         exc.retval = 1.0;
         if(_LIB_VERSION == _IEEE_ || _LIB_VERSION == _POSIX_)
            exc.retval = 1.0;
         else if(!matherr(&exc))
         {
            errno = EDOM;
         }
         if(exc.err != 0)
            errno = exc.err;
         return (float)exc.retval;
      }
      else
         return z;
   }
   if(x == (float)0.0)
   {
      if(y == (float)0.0)
      {
         /* powf(0.0,0.0) */
         /* error only if _LIB_VERSION == _SVID_ */
         exc.type = DOMAIN;
         exc.name = "powf";
         exc.err = 0;
         exc.arg1 = (double)x;
         exc.arg2 = (double)y;
         exc.retval = 0.0;
         if(_LIB_VERSION != _SVID_)
            exc.retval = 1.0;
         else if(!matherr(&exc))
         {
            errno = EDOM;
         }
         if(exc.err != 0)
            errno = exc.err;
         return (float)exc.retval;
      }
      if(finitef(y) && y < (float)0.0)
      {
         /* 0**neg */
         exc.type = DOMAIN;
         exc.name = "powf";
         exc.err = 0;
         exc.arg1 = (double)x;
         exc.arg2 = (double)y;
         if(_LIB_VERSION == _SVID_)
            exc.retval = 0.0;
         else
            exc.retval = -HUGE_VAL;
         if(_LIB_VERSION == _POSIX_)
            errno = EDOM;
         else if(!matherr(&exc))
         {
            errno = EDOM;
         }
         if(exc.err != 0)
            errno = exc.err;
         return (float)exc.retval;
      }
      return z;
   }
   if(!finitef(z))
   {
      if(finitef(x) && finitef(y))
      {
         if(isnanf(z, IEEE32_SPEC))
         {
            /* neg**non-integral */
            exc.type = DOMAIN;
            exc.name = "powf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)y;
            if(_LIB_VERSION == _SVID_)
               exc.retval = 0.0;
            else
               exc.retval = 0.0 / 0.0; /* X/Open allow NaN */
            if(_LIB_VERSION == _POSIX_)
               errno = EDOM;
            else if(!matherr(&exc))
            {
               errno = EDOM;
            }
            if(exc.err != 0)
               errno = exc.err;
            return (float)exc.retval;
         }
         else
         {
            /* powf(x,y) overflow */
            exc.type = OVERFLOW;
            exc.name = "powf";
            exc.err = 0;
            exc.arg1 = (double)x;
            exc.arg2 = (double)y;
            if(_LIB_VERSION == _SVID_)
            {
               exc.retval = HUGE;
               y *= 0.5;
               if(x < 0.0 && rint(y) != y)
                  exc.retval = -HUGE;
            }
            else
            {
               exc.retval = HUGE_VAL;
               y *= 0.5;
               if(x < 0.0 && rint(y) != y)
                  exc.retval = -HUGE_VAL;
            }
            if(_LIB_VERSION == _POSIX_)
               errno = ERANGE;
            else if(!matherr(&exc))
            {
               errno = ERANGE;
            }
            if(exc.err != 0)
               errno = exc.err;
            return (float)exc.retval;
         }
      }
   }
   if(z == (float)0.0 && finitef(x) && finitef(y))
   {
      /* powf(x,y) underflow */
      exc.type = UNDERFLOW;
      exc.name = "powf";
      exc.err = 0;
      exc.arg1 = (double)x;
      exc.arg2 = (double)y;
      exc.retval = 0.0;
      if(_LIB_VERSION == _POSIX_)
         errno = ERANGE;
      else if(!matherr(&exc))
      {
         errno = ERANGE;
      }
      if(exc.err != 0)
         errno = exc.err;
      return (float)exc.retval;
   }
   return z;
#endif
}

#ifdef _DOUBLE_IS_32BITS

double pow(double x, double y)
{
   return (double)powf((float)x, (float)y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */

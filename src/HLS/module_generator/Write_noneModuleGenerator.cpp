/*
 *
 *                   _/_/_/    _/_/   _/    _/ _/_/_/    _/_/
 *                  _/   _/ _/    _/ _/_/  _/ _/   _/ _/    _/
 *                 _/_/_/  _/_/_/_/ _/  _/_/ _/   _/ _/_/_/_/
 *                _/      _/    _/ _/    _/ _/   _/ _/    _/
 *               _/      _/    _/ _/    _/ _/_/_/  _/    _/
 *
 *             ***********************************************
 *                              PandA Project
 *                     URL: http://panda.dei.polimi.it
 *                       Politecnico di Milano - DEIB
 *                        System Architectures Group
 *             ***********************************************
 *              Copyright (C) 2022-2022 Politecnico di Milano
 *
 *   This file is part of the PandA framework.
 *
 *   The PandA framework is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/**
 * @file Write_noneModuleGenerator.cpp
 * @brief
 *
 *
 *
 * @author Michele Fiorito <michele.fiorito@polimi.it>
 * @author Fabrizio Ferrandi <fabrizio.ferrandi@polimi.it>
 * $Revision$
 * $Date$
 * Last modified by $Author$
 *
 */

#include "Write_noneModuleGenerator.hpp"

#include "language_writer.hpp"

Write_noneModuleGenerator::Write_noneModuleGenerator(const HLS_managerRef& _HLSMgr) : Registrar(_HLSMgr)
{
}

void Write_noneModuleGenerator::InternalExec(std::ostream& out, const module* /* mod */, unsigned int /* function_id */,
                                             vertex /* op_v */, const HDLWriter_Language language,
                                             const std::vector<ModuleGenerator::parameter>& /* _p */,
                                             const std::vector<ModuleGenerator::parameter>& _ports_in,
                                             const std::vector<ModuleGenerator::parameter>& _ports_out,
                                             const std::vector<ModuleGenerator::parameter>& /* _ports_inout */)
{
   if(language == HDLWriter_Language::VHDL)
   {
      out << "begin\n  \\" << _ports_out[0].name << "\\ <= std_logic_vector(resize(unsigned(" << _ports_in[1].name
          << "), " << _ports_out[0].type_size << "));\n";
   }
   else
   {
      out << "assign " << _ports_out[0].name << " = " << _ports_in[1].name << ";\n";
   }
}
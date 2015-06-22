/* Copyright (C) 2014 Fraunhofer Institute for Embedded Systems and
 * Communication Technologies ESK
 *
 * This file is part of ERNEST.
 * 
 * ERNEST is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ERNEST is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ERNEST.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <ernest/ernest.hpp>
#include "execution_specification_interface_test.hpp"

using namespace ERNEST;

void ExecutionSpecificationInterfaceTest::Execute(void)
{
    UniformExecutionSpecification* uniform = new
    UniformExecutionSpecification(milliseconds(20),
                                  milliseconds(10));
    NormalExecutionSpecification* normal = new
    NormalExecutionSpecification(milliseconds(20),
                                 milliseconds(5));
    WorstCaseExecutionSpecification* worst_case = new
    WorstCaseExecutionSpecification(milliseconds(20));

    int counter = 10000;

    while(counter > 0) {
        cout << uniform->GetExecutionTime().GetMilliseconds()
             << " ms"
             << endl;
        cout << normal->GetExecutionTime().GetMilliseconds()
             << " ms"
             << endl;
        cout << worst_case->GetExecutionTime().GetMilliseconds()
             << " ms"
             << endl;
        cout << endl;

        counter--;
    }

    delete uniform;
    delete normal;
    delete worst_case;
}

int sc_main(int argc, char* argv[])
{
    ExecutionSpecificationInterfaceTest::Execute();
    return 0;
}

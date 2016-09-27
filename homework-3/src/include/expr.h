/*
 * ai-course, Foundation of Artificial Intelligence
 * Copyright (C) 2014-2016, Cloudzfy
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _EXPR_H_
#define _EXPR_H_

#include <string>
#include <vector>
#include <regex.h>
#include "utilities.h"

using namespace std;

class expr
{
public:
    expr();
    ~expr();
    bool isVariable(string statement);
    bool isConstant(string statement);
    bool isCompound(string statement);
    bool isList(string statement);
    bool isSimpleTerm(string statement);
    bool isComplexTerm(string statement);
    string getArgsFromCompound(string statement);
    string getOpFromCompound(string statement);
    string getFirstFromList(string statement);
    string getRestFromList(string statement);
    string getFirstFromClause(string statement);
    string getRestFromClause(string statement);
    regex_t getSubstReg();
private:
    bool checkExpr(string statement, string reg);
    regex_t variableReg;
    regex_t constantReg;
    regex_t compoundReg;
    regex_t listReg;
    regex_t simpleReg;
    regex_t substReg;
    
};

extern expr expr;

#endif

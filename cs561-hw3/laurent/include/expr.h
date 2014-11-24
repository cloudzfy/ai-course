//
//  expr.h
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

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

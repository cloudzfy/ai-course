//
//  expr.cpp
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "expr.h"
#include <stdio.h>

class expr expr;

expr::expr()
{
    regcomp(&variableReg, "^[a-z]+$", REG_EXTENDED);
    regcomp(&constantReg, "^[A-Z][A-Za-z]*$", REG_EXTENDED);
    regcomp(&compoundReg, "^[A-Z][A-Za-z]*\\([A-Za-z]+(\\,[A-Za-z]+)*\\)$", REG_EXTENDED);
    regcomp(&listReg, "^[A-Za-z]+(\\,[A-Za-z]+)+$", REG_EXTENDED);
    regcomp(&simpleReg, "^[A-Za-z]+$", REG_EXTENDED);
    regcomp(&substReg, "[\\,\\(\\)][a-z]+[\\,\\(\\)]", REG_EXTENDED);
}

expr::~expr()
{
    regfree(&variableReg);
    regfree(&constantReg);
    regfree(&compoundReg);
    regfree(&listReg);
    regfree(&simpleReg);
    regfree(&substReg);
}

bool expr::isVariable(string statement)
{
    if (regexec(&variableReg, statement.c_str(), 0, NULL, 0) == 0)
    {
        return true;
    }
    return false;
}

bool expr::isConstant(string statement)
{
    if (regexec(&constantReg, statement.c_str(), 0, NULL, 0) == 0)
    {
        return true;
    }
    return false;
}

bool expr::isCompound(string statement)
{
    if (regexec(&compoundReg, statement.c_str(), 0, NULL, 0) == 0)
    {
        return true;
    }
    return false;
}

bool expr::isList(string statement)
{
    if (regexec(&listReg, statement.c_str(), 0, NULL, 0) == 0)
    {
        return true;
    }
    return false;
}

bool expr::isSimpleTerm(string statement)
{
    if (regexec(&simpleReg, statement.c_str(), 0, NULL, 0) == 0)
    {
        return true;
    }
    return false;
}

bool expr::isComplexTerm(string statement)
{
    if(isSimpleTerm(statement))
    {
        return false;
    }
    return true;
}

string expr::getArgsFromCompound(string statement)
{
    int a = (int)statement.find("(");
    int b = (int)statement.find(")");
    return statement.substr(a+1, b-a-1);
}

string expr::getOpFromCompound(string statement)
{
    int a = (int)statement.find("(");
    return statement.substr(0, a);
}

string expr::getFirstFromList(string statement)
{
    int a = (int)statement.find(",");
    return statement.substr(0, a);
}

string expr::getRestFromList(string statement)
{
    int a = (int)statement.find(",");
    if (a == statement.npos)
    {
        return string("");
    }
    else
    {
        return statement.substr(a+1, statement.length()-a-1);
    }
}

string expr::getFirstFromClause(string statement)
{
    int a = (int)statement.find("&");
    return statement.substr(0, a);
}

string expr::getRestFromClause(string statement)
{
    int a = (int)statement.find("&");
    if (a == statement.npos)
    {
        return string("");
    }
    else
    {
        return statement.substr(a+1, statement.length()-a-1);
    }
}

regex_t expr::getSubstReg()
{
    return substReg;
}

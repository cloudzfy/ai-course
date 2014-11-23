//
//  expr.cpp
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "expr.h"
#include <regex>
#include <stdio.h>

bool expr::isVariable(string statement)
{
    regex reg("^[a-z]$");
    if(regex_match(statement, reg))
    {
        return true;
    }
    return false;
}

bool expr::isConstant(string statement)
{
    regex reg("^[A-Z][a-z]*$");
    if(regex_match(statement, reg))
    {
        return true;
    }
    return false;
}

bool expr::isCompound(string statement)
{
    regex reg("^[A-Z][a-z]*\\([A-Za-z]*,[A-Za-z]*\\)$");
    if(regex_match(statement, reg))
    {
        return true;
    }
    return false;
}

bool expr::isList(string statement)
{
    regex reg("^[A-Za-z]*,[A-Za-z]*$");
    if(regex_match(statement, reg))
    {
        return true;
    }
    return false;
}

bool expr::isSimpleTerm(string statement)
{
    regex reg("^[A-Za-z]+$");
    if(regex_match(statement, reg))
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
    return statement.substr(a+1, statement.length()-a-1);
}

string expr::getFirstFromClause(string statement)
{
    int a = (int)statement.find("&");
    return statement.substr(0, a);
}

string expr::getRestFromClause(string statement)
{
    int a = (int)statement.find("&");
    return statement.substr(a+1, statement.length()-a-1);
}

rule expr::standardizeVariables(rule r)
{
    
}

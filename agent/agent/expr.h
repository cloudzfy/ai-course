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

#include "utilities.h"

using namespace std;

class expr
{
public:
    static bool isVariable(string statement);
    static bool isConstant(string statement);
    static bool isCompound(string statement);
    static bool isList(string statement);
    static bool isSimpleTerm(string statement);
    static bool isComplexTerm(string statement);
    static string getArgsFromCompound(string statement);
    static string getOpFromCompound(string statement);
    static string getFirstFromList(string statement);
    static string getRestFromList(string statement);
    static string getFirstFromClause(string statement);
    static string getRestFromClause(string statement);
    static rule standardizeVariables(rule r);
};

#endif

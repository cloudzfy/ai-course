//
//  chaining.cpp
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "chaining.h"
#include "expr.h"
#include <ctime>
#include <iostream>
#include <sstream>
using namespace std;

bool backwardChainingAsk(knowledgeBase kb, string query)
{
    theta th = backwardChainingOr(kb, query, theta(true));
    return th.getSubst().size() > 0;
}

theta backwardChainingOr(knowledgeBase kb, string goal, theta th)
{
    theta newTh = theta(true);
    vector<rule> rawRules = kb.fetchRulesForGoal(goal);
    for (vector<rule>::iterator it = rawRules.begin(); it!=rawRules.end();it++)
    {
        rule newRule = standardizeVariables(*it, th);
        theta ans = backwardChainingAnd(kb, newRule.getLeftHandSide(),
            unify(newRule.getRightHandSide(), goal, th));
        string a=goal;
        newTh.copyFromTheta(ans);
    }
    return newTh;
}

theta backwardChainingAnd(knowledgeBase kb, string goal, theta th)
{
    if(!th.getStatus())
        return th;
    else if(goal.length() == 0)
        return th;
    else
    {
        string first = expr.getFirstFromClause(goal);
        string rest = expr.getRestFromClause(goal);
        theta newTh = theta(true);
        theta th1 = backwardChainingOr(kb, substitute(first, th), th);
        map<string, string>::iterator it;
        map<string, string> subst = th1.getSubst();
        for (it = subst.begin(); it != subst.end(); it++)
        {
            theta th2 = backwardChainingAnd(kb, rest, th1);
            newTh.copyFromTheta(th2);
        }
        return newTh;
    }
}

theta unify(string x, string y, theta th)
{
    if (!th.getStatus())
        return theta(false);
    else if(x == y)
        return th;
    else if(expr.isVariable(x))
        return unifyVariables(x, y, th);
    else if(expr.isVariable(y))
        return unifyVariables(y, x, th);
    else if(expr.isCompound(x) && expr.isCompound(y))
        return unify(expr.getArgsFromCompound(x), expr.getArgsFromCompound(y),
                     unify(expr.getOpFromCompound(x), expr.getOpFromCompound(y), th));
    else if(expr.isList(x) && expr.isList(y))
        return unify(expr.getRestFromList(x), expr.getRestFromList(y),
                     unify(expr.getFirstFromList(x), expr.getFirstFromList(y), th));
    else return theta(false);
}

theta unifyVariables(string var, string x, theta th)
{
    if(th.isExisted(var))
        return unify(th.getValue(var), x, th);
    else if(th.isExisted(x))
        return unify(var, th.getValue(x), th);
    else if(occurCheck(var, x)) return theta(false);
    else
    {
        th.addSubst(var, x);
        return th;
    }
}

bool occurCheck(string var, string val)
{
    if(expr.isSimpleTerm(var) && expr.isSimpleTerm(val))
    {
        return false;
    }
    else if(expr.isComplexTerm(var) && expr.isComplexTerm(val))
    {
        return false;
    }
    return true;
}

string substitute(string statement, theta th)
{
    int index = 0;
    regmatch_t match;
    vector<regmatch_t> matches;
    regex_t reg = expr.getSubstReg();
    while (regexec(&reg, statement.c_str() + index, 1, &match, 0) == 0)
    {
        match.rm_so += index;
        match.rm_eo += index;
        matches.push_back(match);
        index += match.rm_eo - 1;
    }
    while(!matches.empty())
    {
        match = matches.back();
        matches.pop_back();
        string var = statement.substr(match.rm_so + 1, match.rm_eo - match.rm_so - 2);
        if (th.isExisted(var))
        {
            string val = th.getValue(var);
            statement.replace(match.rm_so + 1, match.rm_eo - match.rm_so - 2, val);
        }
    }
    return statement;
}

rule standardizeVariables(rule r, theta th)
{
    string lhs, rhs;
    regmatch_t match;
    vector<regmatch_t> matchLHS, matchRHS;
    map<string, string> varMap;
    regex_t reg = expr.getSubstReg();
    int index = 0;
    lhs = r.getLeftHandSide();
    while (regexec(&reg, lhs.c_str() + index, 1, &match, 0) == 0)
    {
        match.rm_so += index;
        match.rm_eo += index;
        matchLHS.push_back(match);
        index += match.rm_eo - 1;
    }
    index = 0;
    rhs = r.getRightHandSide();
    while (regexec(&reg, rhs.c_str() + index, 1, &match, 0) == 0)
    {
        match.rm_so += index;
        match.rm_eo += index;
        matchRHS.push_back(match);
        index += match.rm_eo - 1;
    }
    for (int i = 0; i < matchLHS.size(); i++)
    {
        string var = lhs.substr(matchLHS[i].rm_so + 1, matchLHS[i].rm_eo - matchLHS[i].rm_so - 2);
        varMap[var] = "";
    }
    for (int i = 0; i < matchRHS.size(); i++)
    {
        string var = rhs.substr(matchRHS[i].rm_so + 1, matchRHS[i].rm_eo - matchRHS[i].rm_so - 2);
        varMap[var] = "";
    }
    map<string, string>::iterator it;
    srand((unsigned)time(NULL));
    for (it = varMap.begin(); it != varMap.end(); it++)
    {
        string var = it->first;
        while (th.isExisted(var) || var == "x")
        {
            stringstream stream;
            for (int i = 0; i < 4; i++)
            {
                char ch = 'a' + rand() % 26;
                stream<< ch;
            }
            stream>> var;
        }
        it->second = var;
    }
    while(!matchLHS.empty())
    {
        match = matchLHS.back();
        matchLHS.pop_back();
        string var = lhs.substr(match.rm_so + 1, match.rm_eo - match.rm_so - 2);
        string newVar = varMap[var];
        if (var != newVar)
        {
            lhs.replace(match.rm_so + 1, match.rm_eo - match.rm_so - 2, newVar);
        }
    }
    r.setLeftHandSide(lhs);
    while(!matchRHS.empty())
    {
        match = matchRHS.back();
        matchRHS.pop_back();
        string var = rhs.substr(match.rm_so + 1, match.rm_eo - match.rm_so - 2);
        string newVar = varMap[var];
        if (var != newVar)
        {
            rhs.replace(match.rm_so + 1, match.rm_eo - match.rm_so - 2, newVar);
        }
    }
    r.setRightHandSide(rhs);
    return r;
}


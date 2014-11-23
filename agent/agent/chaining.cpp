//
//  chaining.cpp
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "chaining.h"
#include "expr.h"

theta backwardChainingAsk(knowledgeBase kb, string query)
{
    return backwardChainingOr(kb, query, theta(true));
}

theta backwardChainingOr(knowledgeBase kb, string goal, theta th)
{
    theta newTheta = theta(true);
    vector<rule> rawRules = kb.fetchRulesForGoal(goal);
    for (vector<rule>::iterator it = rawRules.begin(); it!=rawRules.end();it++)
    {
        rule newRule = expr::standardizeVariables(*it);
        theta ans = backwardChainingAnd(kb, newRule.getLeftHandSide(), th);
        // copy ans to newTheta
    }
    return newTheta;
}

theta backwardChainingAnd(knowledgeBase kb, string goal, theta th)
{
    if(!th.getStatus())
        return th;
    else if(goal.length() == 0)
        return th;
    else
    {
        string first = expr::getFirstFromClause(goal);
        string rest = expr::getRestFromClause(goal);
        // two for-cycle
    }
}

theta unify(string x, string y, theta th)
{
    if (!th.getStatus())
        return theta(false);
    else if(x == y)
        return th;
    else if(expr::isVariable(x))
        return unifyVariables(x, y, th);
    else if(expr::isVariable(y))
        return unifyVariables(y, x, th);
    else if(expr::isCompound(x) && expr::isCompound(y))
        return unify(expr::getArgsFromCompound(x), expr::getArgsFromCompound(y),
                     unify(expr::getOpFromCompound(x), expr::getOpFromCompound(y), th));
    else if(expr::isList(x) && expr::isList(y))
        return unify(expr::getRestFromList(x), expr::getRestFromList(y),
                     unify(expr::getFirstFromList(x), expr::getFirstFromList(y), th));
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
    if(expr::isSimpleTerm(var) && expr::isSimpleTerm(val))
    {
        return true;
    }
    else if(expr::isComplexTerm(var) && expr::isComplexTerm(val))
    {
        return true;
    }
    return false;
}

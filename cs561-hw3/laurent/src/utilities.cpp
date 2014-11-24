//
//  utilities.cpp
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "utilities.h"
#include "expr.h"

theta::theta(bool status)
{
    this->status = status;
}

void theta::setStatus(bool status)
{
    this->status = status;
}

bool theta::getStatus()
{
    return this->status;
}

bool theta::isExisted(string var)
{
    if(subst.find(var) == subst.end())
    {
        return false;
    }
    return true;
}

string theta::getValue(string var)
{
    return subst[var];
}

void theta::addSubst(string var, string val)
{
    subst[var] = val;
}

map<string, string> theta::getSubst()
{
    return subst;
}

void theta::copyFromTheta(theta th)
{
    map<string, string>::iterator it;
    map<string, string> subst = th.getSubst();
    for(it = subst.begin(); it != subst.end(); it++)
    {
        addSubst(it->first, it->second);
    }
}

rule::rule(string lhs, string rhs)
{
    this->leftHandSide = lhs;
    this->rightHandSide = rhs;
}

string rule::getLeftHandSide()
{
    return this->leftHandSide;
}

string rule::getRightHandSide()
{
    return this->rightHandSide;
}

void rule::setLeftHandSide(string lhs)
{
    this->leftHandSide = lhs;
}

void rule::setRightHandSide(string rhs)
{
    this->rightHandSide = rhs;
}

void knowledgeBase::addNewStatement(string r)
{
    string lhs, rhs;
    int a = (int)r.find("=>");
    if(a == r.npos)
    {
        lhs = "";
        rhs = r;
    }
    else
    {
        lhs = r.substr(0, a);
        rhs = r.substr(a+2, r.length()-a-2);
    }
    rules.push_back(rule(lhs, rhs));
}

vector<rule> knowledgeBase::fetchRulesForGoal(string goal)
{
    vector<rule> fetchedGoals;
    for(int i = 0; i < rules.size(); i++)
    {
        string rhs = rules[i].getRightHandSide();
        if (expr.getOpFromCompound(rhs) == expr.getOpFromCompound(goal))
        {
            fetchedGoals.push_back(rules[i]);
        }
    }
    return fetchedGoals;
}

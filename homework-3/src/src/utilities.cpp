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
 
#include "utilities.h"
#include "expr.h"

theta::theta(bool status)
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

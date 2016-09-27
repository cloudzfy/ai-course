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

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <vector>
#include <map>
#include <string>
using namespace std;

class theta
{
public:
    theta(bool status);
    bool getStatus();
    bool isExisted(string var);
    string getValue(string var);
    void addSubst(string var, string val);
    map<string, string> getSubst();
    void copyFromTheta(theta th);
private:
    bool status;
    map<string, string> subst;
};

class rule
{
public:
    rule(string lhs, string rhs);
    string getLeftHandSide();
    string getRightHandSide();
    void setLeftHandSide(string lhs);
    void setRightHandSide(string rhs);
private:
    string leftHandSide;
    string rightHandSide;
};

class knowledgeBase
{
public:
    void addNewStatement(string rule);
    vector<rule> fetchRulesForGoal(string goal);
private:
    vector<rule> rules;
};

#endif

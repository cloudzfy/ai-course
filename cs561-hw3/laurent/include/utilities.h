//
//  utilities.h
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

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

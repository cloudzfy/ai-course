//
//  chaining.h
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#ifndef _CHAINING_H_
#define _CHAINING_H_

#include "utilities.h"

bool backwardChainingAsk(knowledgeBase kb, string query);

theta backwardChainingOr(knowledgeBase kb, string goal, theta th);

theta backwardChainingAnd(knowledgeBase kb, string goal, theta th);

theta unify(string x, string y, theta th);

theta unifyVariables(string var, string x, theta th);

bool occurCheck(string var, string val);

string substitute(string statement, theta th);

rule standardizeVariables(rule r, theta th);

#endif

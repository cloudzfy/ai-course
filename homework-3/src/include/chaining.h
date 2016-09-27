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

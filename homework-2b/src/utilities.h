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

#include <string>
#include <queue>

using namespace std;

#define TRUE 1
#define FALSE 0
#define INF 2147483647

#define EMPTY 2
#define XPOS 1
#define OPOS 0
#define ZERO 3

#define STABLE 0
#define SEMISTABLE 1
#define UNSTABLE 2

#define ZEROLINE 0
#define STABLELINE 4

#define WIN 1
#define TIE 0
#define LOSS -1

struct point
{
    int x;
    int y;
    int value;
    int depth;
    point* child;
    point* parent;
    int alpha;
    int beta;
    int pass;
    point(){}
    point(int value, int depth)
    {
        this->value = value;
        this->depth = depth;
        this->child = NULL;
        this->parent = NULL;
    }
    point(int value, int depth, int alpha, int beta)
    {
        this->value = value;
        this->depth = depth;
        this->alpha = alpha;
        this->beta = beta;
        this->child = NULL;
        this->parent = NULL;
        this->pass = FALSE;
    }
};

struct log
{
    string node;
    int depth;
    int value;
    int alpha;
    int beta;
};

extern int map[8][8];

extern int eval[8][8];


extern long long valCount;

extern long long legalCount;

extern queue<log> history;

extern int ply;

extern int myPly;

extern int depth;

int legal(int x, int y, int rec[][8], int op);

void backup(int rec[][8]);

void init(int rec[][8], int val);

int valueOfEvaluation();

void printMap();

void printValue(int value);

int terminalStateCheck();

#endif /* defined(__agent__utilities__) */

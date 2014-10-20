//
//  competition.h
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#ifndef _COMPETITION_H_
#define _COMPETITION_H_

#include "utilities.h"

extern int edgeWeight[7][3];

extern int edgePoint[4][7][2];

extern int xSquarePoint[4][2];

extern int edgeStabilityMap[6561][8];

extern int internalStabilityMap[8][8];

extern int moveNumber;

int competition(point* root);

int valueOfEvaluation4Competition(int d);

int edgeStability();

int xSquareCost();

int internalStability();

int currentMobility();

int potentialMobility();

int finalDiscDifferential();

int threeValueMeasure();

int terminalStateCheck4Competition();

void importEdgeStabilityMap();

void depthAdjustment();

#endif /* defined(__agent__competition__) */

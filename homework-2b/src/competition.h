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

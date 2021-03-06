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
 
#include "competition.h"
#include "utilities.h"

void depthAdjustment(int cpuTime)
{
	moveNumber = 0;
	for (int i = 0; i< 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (map[i][j] != EMPTY)
			moveNumber++;
		}
	}
	moveNumber -= 4;
	if(moveNumber < 46)
	{
		if(cpuTime > 80) depth = 7;
		else depth = 5;
	}
	else depth = 60 - moveNumber;
}

// For 150000 times evaluation, this machine takes 2200 ms.
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

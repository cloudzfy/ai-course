//
//  greedy.cpp
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "greedy.h"

int greedy()
{
    int rec[8][8];
    int max = -INF;
    int x = 0, y = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(legal(i, j, rec, TRUE))
            {
                int tmp = valueOfEvaluation();
                if(tmp > max)
                {
                    max = tmp;
                    x = i;
                    y = j;
                }
                backup(rec);
            }
        }
    }
    if(max != -INF)
    {
        legal(x, y, rec, TRUE);
        return TRUE;
    }
    return FALSE;
}

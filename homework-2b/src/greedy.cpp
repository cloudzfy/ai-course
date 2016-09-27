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

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

#include <iostream>
#include "utilities.h"

int map[8][8];

int eval[8][8] = {
    {99, -8, 8, 6, 6, 8, -8, 99},
    {-8, -24, -4, -3, -3, -4, -24, -8},
    {8, -4, 7, 4, 4, 7, -4, 8},
    {6, -3, 4, 0, 0, 4, -3, 6},
    {6, -3, 4, 0, 0, 4, -3, 6},
    {8, -4, 7, 4, 4, 7, -4, 8},
    {-8, -24, -4, -3, -3, -4, -24, -8},
    {99, -8, 8, 6, 6, 8, -8, 99}
};

queue<log> history;

int ply;
int myPly;
int depth;

int legal(int x, int y, int rec[][8], int op)
{
    int a, b, c = FALSE;
    a = FALSE; b = FALSE;
    if(map[x][y] != EMPTY)
    {
        return FALSE;
    }
    // X+ Direction
    for (int i = x + 1; i < 8; i++)
    {
        if(map[i][y] == ply && a) b = TRUE;
        else if(map[i][y] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x + 1; i < 8; i++)
        {
            if(map[i][y] == (ply + 1) % 2)
            {
                rec[i][y] = map[i][y];
                map[i][y] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // X- Direction
    for (int i = x - 1; i >= 0; i--)
    {
        if(map[i][y] == ply && a) b = TRUE;
        else if(map[i][y] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x - 1; i >= 0; i--)
        {
            if(map[i][y] == (ply + 1) % 2)
            {
                rec[i][y] = map[i][y];
                map[i][y] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // Y+ Direction
    for (int j = y + 1; j < 8; j++)
    {
        if(map[x][j] == ply && a) b = TRUE;
        else if(map[x][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int j = y + 1; j < 8; j++)
        {
            if(map[x][j] == (ply + 1) % 2)
            {
                rec[x][j] = map[x][j];
                map[x][j] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // Y- Direction
    for (int j = y - 1; j >= 0; j--)
    {
        if(map[x][j] == ply && a) b = TRUE;
        else if(map[x][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int j = y - 1; j >= 0; j--)
        {
            if(map[x][j] == (ply + 1) % 2)
            {
                rec[x][j] = map[x][j];
                map[x][j] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // X+Y+ Direction
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
    {
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
        {
            if(map[i][j] == (ply + 1) % 2)
            {
                rec[i][j] = map[i][j];
                map[i][j] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // X-Y- Direction
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
    {
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
        {
            if(map[i][j] == (ply + 1) % 2)
            {
                rec[i][j] = map[i][j];
                map[i][j] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // X+Y- Direction
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
    {
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
        {
            if(map[i][j] == (ply + 1) % 2)
            {
                rec[i][j] = map[i][j];
                map[i][j] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    a = FALSE; b = FALSE;
    // X-Y+ Direction
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++)
    {
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++)
        {
            if(map[i][j] == (ply + 1) % 2)
            {
                rec[i][j] = map[i][j];
                map[i][j] = ply;
            }
            else break;
        }
        c = TRUE;
    }
    if(c)
    {
        rec[x][y] = map[x][y];
        map[x][y] = ply;
        return TRUE;
    }
    return FALSE;
}

void backup(int rec[][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (rec[i][j] != 3)
            {
                map[i][j] = rec[i][j];
            }
        }
    }
}

void init(int rec[][8], int val)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rec[i][j] = val;
        }
    }
}

int valueOfEvaluation()
{
    int val = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == myPly)
            {
                val += eval[i][j];
            }
            else if(map[i][j] == (myPly + 1) % 2)
            {
                val -= eval[i][j];
            }
        }
    }
    return val;
}

void printMap()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == 1)
            {
                cout<<"X";
            }
            else if(map[i][j] == 0)
            {
                cout<<"O";
            }
            else
            {
                cout<<"*";
            }
        }
        cout<<endl;
    }
}

void printValue(int value)
{
    if (value == INF)
    {
        cout<<"Infinity";
    }
    else if(value == -INF)
    {
        cout<<"-Infinity";
    }
    else
    {
        cout<<value;
    }
}

int terminalStateCheck()
{
    int pCount = 0, oCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[i][j] == myPly) pCount++;
            if (map[i][j] == (myPly + 1) % 2) oCount++;
        }
    }
    if(pCount == 0 || oCount == 0) return TRUE;
    return FALSE;
}

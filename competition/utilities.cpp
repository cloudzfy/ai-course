//
//  utilities.cpp
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <iostream>
#include "utilities.h"

int map[8][8];

int eval[8][8] = {
    500, - 150, 30, 10, 10, 30, - 150, 500, - 150, - 250, 0, 0, 0, 0, - 250, - 150, 30, 0, 1, 2, 2, 1, 0, 30, 10, 0, 2, 16, 16, 2, 0, 10, 10, 0, 2, 16, 16, 2, 0, 10, 30, 0, 1, 2, 2, 1, 0, 30, - 150, - 250, 0, 0, 0, 0, - 250, - 150, 500, - 150, 30, 10, 10, 30, - 150, 500
};

queue<log> history;

int ply;
int myPly;
int depth;

long long valCount;

long long legalCount;

int legal(int x, int y, int rec[][8], int op)
{
    legalCount++;
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

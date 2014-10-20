//
//  edgeStabilityGenerator.cpp
//  edgeStabilityGenerator
//
//  Created by Youzheng Chen on 10/15/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#define FALSE 0
#define TRUE 1

#define STABLE 0
#define SEMISTABLE 1
#define UNSTABLE 2

#define XPOS 1
#define OPOS 0
#define EMPTY 2
#define NOSTAT 3

#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;
int map[8], refmap[8];
int data[6561][2][8];
int ply, current;
int enumCount;
struct point
{
    int x;
    int depth;
};

void backup(int rec[])
{
    for(int i = 0; i < 8; i++)
    {
        if(rec[i] != NOSTAT)
        {
            map[i] = rec[i];
        }
    }
}

int move(int x, int rec[])
{
    int a, b, c;
    for(int i = 0; i < 8; i++)
    {
        rec[i] = NOSTAT;
    }
    a = FALSE;
    b = FALSE;
    c = FALSE;
    for (int i = x - 1; i >= 0; i--)
    {
        if(map[i] == (ply + 1) % 2) a = TRUE;
        else if(map[i] == ply && a) b = TRUE;
        else break;
    }
    if (b)
    {
        c = TRUE;
        for (int i = x - 1; i >= 0; i--)
        {
            if(map[i] == (ply + 1) % 2)
            {
                rec[i] = map[i];
                map[i] = ply;
            }
            else break;
        }
    }
    a = FALSE;
    b = FALSE;
    for (int i = x + 1; i < 8; i++)
    {
        if(map[i] == (ply + 1) % 2) a = TRUE;
        else if(map[i] == ply && a) b = TRUE;
        else break;
    }
    if (b)
    {
        c = TRUE;
        for (int i = x + 1; i < 8; i++)
        {
            if (map[i] == (ply + 1) % 2)
            {
                rec[i] = map[i];
                map[i] = ply;
            }
            else break;
        }
    }
    rec[x] = map[x];
    map[x] = ply;
    if (c) return TRUE;
    return FALSE;
}

void checkStability(point *root)
{
    int rec[8];
    ply = (ply + 1) % 2;
    for (int i = 0; i < 8; i++)
    {
        if (map[i] == EMPTY)
        {
            move(i, rec);
            for (int j = 0; j < 8; j++)
            {
                if(map[j] != refmap[j])
                {
                    if(root->depth == 0)
                    {
                        data[enumCount][current][j] = UNSTABLE;
                    }
                    else if(data[enumCount][current][j] == STABLE)
                    {
                        data[enumCount][current][j] = SEMISTABLE;
                    }
                }
            }
            point *tmp = new point();
            tmp->x = i;
            tmp->depth = root->depth + 1;
            checkStability(tmp);
            backup(rec);
            delete tmp;
        }
    }
    ply = (ply + 1) % 2;
}
int main()
{
    FILE *out = freopen("src/edgeStability.cpp", "w", stdout);
    cout<<"#include \"competition.h\""<<endl;
    cout<<endl;
    cout<<"int edgeStabilityMap[6561][8] = {"<<endl;
    enumCount = 0;
    while (enumCount < 6561)
    {
        int tmp = enumCount;
        for(int j = 0; j < 8; j++)
        {
            map[j] = tmp % 3;
            refmap[j] = map[j];
            data[enumCount][OPOS][j] = STABLE;
            data[enumCount][XPOS][j] = STABLE;
            tmp /= 3;
        }
        ply = 1;
        current = ply;
        point *root = new point();
        checkStability(root);
        delete root;
        ply = 0;
        current = ply;
        root = new point();
        checkStability(root);
        delete root;
        enumCount++;
    }
    for (int i = 0;i < enumCount; i++)
    {
        cout<<"    {";
        for (int j = 0; j < 8; j++)
        {
            cout<<MAX(data[i][OPOS][j], data[i][XPOS][j]);
            if(j < 7) cout<<", ";
        }
        if (i < enumCount - 1)cout<<"},"<<endl;
        else cout<<"}"<<endl;
    }
    cout<<"};"<<endl;
    fclose(out);
    return 0;
}

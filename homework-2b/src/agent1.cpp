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
#include "greedy.h"
#include "minimax.h"
#include "alphabeta.h"
#include "competition.h"

int main(int argc, const char * argv[]) {
    int taskNumber;
    string player, states;
    valCount = 0;
    legalCount = 0;
    FILE *in, *out;
    in = freopen("output.txt", "r", stdin);
    out = freopen("input.txt", "w", stdout);
    taskNumber = 3;
    depth = 8;
    ply=1;
    myPly = ply;
    for (int i = 0; i < 8; i++)
    {
        cin>>states;
        for (int j = 0; j < 8; j++)
        {
            if(states[j] == 'X')
            {
                map[i][j] = 1;
            }
            else if(states[j] == 'O')
            {
                map[i][j] = 0;
            }
            else
            {
                map[i][j] = 2;
            }
        }
    }
    if(taskNumber == 1)
    {
        greedy();
        printMap();
    }
    else if(taskNumber == 2)
    {
        point* root = new point(-INF, 0);
        ply = (ply + 1) % 2;
        int ans = minimax(root);
        if(ans)
        {
            ply = (ply + 1) % 2;
            int rec[8][8];
            legal(root->child->x, root->child->y, rec, TRUE);
        }
        printMap();
    }
    else if(taskNumber == 3)
    {
        point* root = new point(-INF, 0, -INF, INF);
        ply = (ply + 1) % 2;
        int ans = alphabeta(root);
        if(ans)
        {
            ply = (ply + 1) % 2;
            int rec[8][8];
            legal(root->child->x, root->child->y, rec, TRUE);
        }
        printMap();
    }
    else if(taskNumber == 4)
    {
        depthAdjustment();
        point* root = new point(-INF, 0, -INF, INF);
        ply = (ply + 1) % 2;
        int ans = competition(root);
        if(ans)
        {
            ply = (ply + 1) % 2;
            int rec[8][8];
            legal(root->child->x, root->child->y, rec, TRUE);
        }
        printMap();
    }
    fclose(in);
    fclose(out);
    return 0;
}

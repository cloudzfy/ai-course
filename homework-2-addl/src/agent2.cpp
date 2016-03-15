//
//  agent.cpp
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <sys/timeb.h>
#include "greedy.h"
#include "minimax.h"
#include "alphabeta.h"
#include "competition.h"

int main(int argc, const char * argv[]) {
    int taskNumber;
    string player, states;
    FILE *in, *out;
    double tt;
    FILE* fp = fopen("time.txt","r");
    fscanf(fp, "%lf", &tt);
    fclose(fp);
    fp = fopen("count.txt","r");
    fscanf(fp, "%lld", &valCount);
    fclose(fp);
    time_t startTime, endTime;
    startTime = clock();
    legalCount = 0;
    in = freopen("input.txt", "r", stdin);
    out = freopen("output.txt", "w", stdout);
    taskNumber = 4;
    ply = 0;
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
        printLog4Minimax();
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
        printLog4Alphabeta();
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
    endTime = clock();
    tt += difftime(endTime,startTime)/CLOCKS_PER_SEC;
    fp = fopen("log.txt","a");
    fprintf(fp, "================%d==================\n", moveNumber);
    fprintf(fp, "Evaluation count: %lld\n", valCount);
    fprintf(fp, "Legal check count: %lld\n", legalCount);
    fprintf(fp, "Time: %.3fms.\n", tt);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(map[i][j]==XPOS)fprintf(fp, "X");
            else if(map[i][j]==OPOS)fprintf(fp, "O");
            else fprintf(fp, "*");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    fp = fopen("time.txt","w");
    fprintf(fp, "%.3f\n", tt);
    fclose(fp);
    fp = fopen("count.txt","w");
    fprintf(fp, "%lld\n", valCount);
    fclose(fp);
    return 0;
}

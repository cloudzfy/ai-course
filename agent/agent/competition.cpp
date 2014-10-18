//
//  competition.cpp
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include "competition.h"

int edgeWeight[7][3] = {
    {700, 0, 0},        // Corner
    {1200, 200, -25},   // C-Square
    {1000, 200, 75},    // A-Square
    {1000, 200, 50},    // B-Square
    {1000, 200, 50},    // B-Square
    {1000, 200, 75},    // A-Square
    {1200, 200, -25}    // C-Square
};

int edgePoint[4][7][2] = {
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}},
    {{7, 7}, {7, 6}, {7, 5}, {7, 4}, {7, 3}, {7, 2}, {7, 1}},
    {{7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}}
};

int xSquarePoint[4][2] = {
    {1, 1}, {1, 6}, {6, 6}, {6, 1}
};

int edgeStabilityMap[6561][8];

int internalStabilityMap[8][8];

int moveNumber;

int competition(point* root)
{
    int rec[8][8];
    if(root->depth == depth)
    {
        root->value = valueOfEvaluation4Competition();
        return FALSE;
    }
    if(terminalStateCheck())
    {
        root->value = valueOfEvaluation4Competition();
        return FALSE;
    }
    ply = (ply + 1) % 2;
    int flag = TRUE, visited = FALSE;
    for (int i = 0; i < 8 && flag; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (legal(i, j, rec, TRUE))
            {
                visited = TRUE;
                point* tmp = new point((root->depth % 2 == 0) ? INF : -INF, root->depth + 1, root->alpha, root->beta);
                tmp->x = i;
                tmp->y = j;
                competition(tmp);
                if(root->depth % 2 == 0 && root->value < tmp->value)
                {
                    root->value = tmp->value;
                    if (root->alpha < tmp->value) root->alpha = tmp->value;
                    if(root->child != NULL) delete root->child;
                    root->child = tmp;
                }
                else if (root->depth % 2 == 1 && root->value > tmp->value)
                {
                    root->value = tmp->value;
                    if (root->beta > tmp->value) root->beta = tmp->value;
                    if(root->child != NULL) delete root->child;
                    root->child = tmp;
                }
                else delete tmp;
                backup(rec);
                if(root->alpha >= root->beta)
                {
                    flag = FALSE;
                    break;
                }
            }
        }
    }
    if(!visited)
    {
        point* tmp = new point((root->depth % 2 == 0) ? INF : -INF, root->depth + 1, root->alpha, root->beta);
        tmp->pass = TRUE;
        root->child = NULL;
        competition(tmp);
        if(root->depth % 2 == 0 && root->value < tmp->value)
        {
            root->value = tmp->value;
            root->alpha = tmp->value;
        }
        else if (root->depth % 2 == 1 && root->value > tmp->value)
        {
            root->value = tmp->value;
            root->beta = tmp->value;
        }
    }
    ply = (ply + 1) % 2;
    if(root->child == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

int valueOfEvaluation4Competition()
{
    if (moveNumber < 46)
    {
        int esac = 213 + 6.24 * moveNumber;
        int cmac = (moveNumber < 25) ? (50 + 2 * moveNumber) : (75 + moveNumber);
        return esac * edgeStability() + 36 * internalStability()
        + cmac * currentMobility() + 99 * potentialMobility();
    }
    else if(moveNumber < 48)
    {
        return threeValueMeasure();
    }
    else
    {
        return finalDiscDifferential();
    }
}

int edgeStability()
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        int tmp = 0;
        for (int j = 0; j < 7; j++)
        {
            tmp *= 3;
            tmp += map[edgePoint[i][j][0]][edgePoint[i][j][1]];
        }
        for (int j = 0; j < 7; j++)
        {
            if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == myPly)
            {
                sum += edgeWeight[j][edgeStabilityMap[tmp][j]];
            }
            else if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (myPly + 1) % 2)
            {
                sum -= edgeWeight[j][edgeStabilityMap[tmp][j]];
            }
        }
    }
    return sum + xSquareCost();
}

int xSquareCost()
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        if(map[xSquarePoint[i][0]][xSquarePoint[i][1]] == myPly
           && map[edgePoint[i][0][0]][edgePoint[i][0][1]] == EMPTY)
        {
            int tmp = 0;
            int a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == myPly) a = TRUE;
                else if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (myPly + 1) % 2 && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += (myPly + 1) % 2;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (myPly + 1) % 2) break;
                    tmp *= 3;
                    tmp += myPly;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (myPly + 1) % 2) break;
                    sum -= edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
            tmp = 0;
            a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == myPly) a = TRUE;
                else if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (myPly + 1) % 2 && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += (myPly + 1) % 2;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (myPly + 1) % 2) break;
                    tmp *= 3;
                    tmp += myPly;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (myPly + 1) % 2) break;
                    sum -= edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
        }
        if(map[xSquarePoint[i][0]][xSquarePoint[i][1]] == (myPly + 1) % 2
           && map[edgePoint[i][0][0]][edgePoint[i][0][1]] == EMPTY)
        {
            int tmp = 0;
            int a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (myPly + 1) % 2) a = TRUE;
                else if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == myPly && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += myPly;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == myPly) break;
                    tmp *= 3;
                    tmp += (myPly + 1) % 2;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == myPly) break;
                    sum += edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
            tmp = 0;
            a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (myPly + 1) % 2) a = TRUE;
                else if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == myPly && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += myPly;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == myPly) break;
                    tmp *= 3;
                    tmp += (myPly + 1) % 2;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == myPly) break;
                    sum += edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
        }
    }
    return FALSE;
}

int internalStability()
{
    queue<point> q;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            internalStabilityMap[i][j] = ZEROLINE;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int tmp = 0;
        for (int j = 0; j < 7; j++)
        {
            tmp *= 3;
            tmp += map[edgePoint[i][j][0]][edgePoint[i][j][1]];
        }
        for (int j = 0; j < 7; j++)
        {
            if(edgeStabilityMap[tmp][j] == STABLE && map[edgePoint[i][j][0]][edgePoint[i][j][1]] != EMPTY)
            {
                internalStabilityMap[edgePoint[i][j][0]][edgePoint[i][j][1]] = STABLELINE;
                point *p = new point();
                p->x = edgePoint[i][j][0];
                p->y = edgePoint[i][j][1];
                q.push(*p);
            }
        }
    }
    while(!q.empty())
    {
        point *cur = &(q.front());
        q.pop();
        if(cur->x > 0 && map[cur->x - 1][cur->y] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x - 1][cur->y] < STABLELINE)
        {
            internalStabilityMap[cur->x - 1][cur->y]++;
            if(internalStabilityMap[cur->x - 1][cur->y] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x - 1;
                p->y = cur->y;
                q.push(*p);
            }
        }
        if(cur->x < 7 && map[cur->x + 1][cur->y] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x + 1][cur->y] < STABLELINE)
        {
            internalStabilityMap[cur->x + 1][cur->y]++;
            if(internalStabilityMap[cur->x + 1][cur->y] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x + 1;
                p->y = cur->y;
                q.push(*p);
            }
        }
        if(cur->y > 0 && map[cur->x][cur->y - 1] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x][cur->y - 1] < STABLELINE)
        {
            internalStabilityMap[cur->x][cur->y - 1]++;
            if(internalStabilityMap[cur->x][cur->y - 1] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x;
                p->y = cur->y - 1;
                q.push(*p);
            }
        }
        if(cur->y < 7 && map[cur->x][cur->y + 1] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x][cur->y + 1] < STABLELINE)
        {
            internalStabilityMap[cur->x][cur->y + 1]++;
            if(internalStabilityMap[cur->x][cur->y + 1] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x;
                p->y = cur->y + 1;
                q.push(*p);
            }
        }
        if(cur->x > 0 && cur->y > 0 && map[cur->x - 1][cur->y - 1] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x - 1][cur->y - 1] < STABLELINE)
        {
            internalStabilityMap[cur->x - 1][cur->y - 1]++;
            if(internalStabilityMap[cur->x - 1][cur->y - 1] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x - 1;
                p->y = cur->y - 1;
                q.push(*p);
            }
        }
        if(cur->x < 7 && cur->y < 7 && map[cur->x + 1][cur->y + 1] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x + 1][cur->y + 1] < STABLELINE)
        {
            internalStabilityMap[cur->x + 1][cur->y + 1]++;
            if(internalStabilityMap[cur->x + 1][cur->y + 1] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x + 1;
                p->y = cur->y + 1;
                q.push(*p);
            }
        }
        if(cur->x > 0 && cur->y < 7 && map[cur->x - 1][cur->y + 1] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x - 1][cur->y + 1] < STABLELINE)
        {
            internalStabilityMap[cur->x - 1][cur->y + 1]++;
            if(internalStabilityMap[cur->x - 1][cur->y + 1] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x - 1;
                p->y = cur->y + 1;
                q.push(*p);
            }
        }
        if(cur->x < 7 && cur->y > 0 && map[cur->x + 1][cur->y - 1] == map[cur->x][cur->y]
           && internalStabilityMap[cur->x + 1][cur->y - 1] < STABLELINE)
        {
            internalStabilityMap[cur->x + 1][cur->y - 1]++;
            if(internalStabilityMap[cur->x + 1][cur->y - 1] == STABLELINE)
            {
                point *p = new point();
                p->x = cur->x + 1;
                p->y = cur->y - 1;
                q.push(*p);
            }
        }
        //delete cur;
    }
    int pCount = 0, oCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == myPly && internalStabilityMap[i][j] == STABLELINE) pCount++;
            if(map[i][j] == (myPly + 1) % 2 && internalStabilityMap[i][j] == STABLELINE) oCount++;
        }
    }
    return pCount - oCount;
}

int currentMobility()
{
    int pCount = 0, oCount = 0;
    int rec[8][8];
    int tmpPly = ply;
    ply = myPly;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(legal(i, j, rec, FALSE))
            {
                pCount++;
            }
        }
    }
    ply = (ply + 1) % 2;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(legal(i, j, rec, FALSE))
            {
                oCount++;
            }
        }
    }
    ply = tmpPly;
    return 100 * (pCount - oCount)/(pCount + oCount + 2);
}

int potentialMobility()
{
    int sumOfOppo = 0, sumOfEmpty = 0, sumOfOppos = 0;
    int rec[8][8];
    init(rec, 0);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == (myPly + 1) % 2)
            {
                if(i > 0 && map[i-1][j] == EMPTY)
                {
                    rec[i][j]++;
                    rec[i-1][j]++;
                }
                if(j > 0 && map[i][j-1] == EMPTY)
                {
                    rec[i][j]++;
                    rec[i][j-1]++;
                }
                if(i > 0 && j > 0 && map[i-1][j-1] == EMPTY)
                {
                    rec[i][j]++;
                    rec[i-1][j-1]++;
                }
                if(i < 7 && map[i+1][j] == EMPTY)
                {
                    rec[i][j]++;
                    rec[i+1][j]++;
                }
                if(j < 7 && map[i][j+1] == EMPTY)
                {
                    rec[i][j]++;
                    rec[i][j+1]++;
                }
                if(i < 7 && j < 7 && map[i+1][j+1] == EMPTY)
                {
                    rec[i][j]++;
                    rec[i+1][j+1]++;
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == (myPly + 1) % 2 && rec[i][j])
            {
                sumOfOppos += rec[i][j];
                sumOfOppo++;
            }
            if(map[i][j] == EMPTY && rec[i][j])
            {
                sumOfEmpty++;
            }
        }
    }
    return sumOfEmpty + sumOfOppo + sumOfOppos;
}

int finalDiscDifferential()
{
    int pCount = 0, oCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == myPly)
            {
                pCount++;
            }
            else if(map[i][j] == (myPly + 1) % 2)
            {
                oCount++;
            }
        }
    }
    return pCount - oCount;
}

int threeValueMeasure()
{
    int pCount = 0, oCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == myPly)
            {
                pCount++;
            }
            else if(map[i][j] == (myPly + 1) % 2)
            {
                oCount++;
            }
        }
    }
    if (pCount < oCount) return LOSS;
    if (pCount > oCount) return WIN;
    return TIE;
}

void importEdgeStabilityMap()
{
    FILE *fp = fopen("edgeStability.txt", "r");
    for (int i = 0; i< 6561; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fscanf(fp, "%d", &edgeStabilityMap[i][j]);
        }
    }
    fclose(fp);
}

void depthAdjustment()
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
    if(moveNumber < 46) depth = 7;
    else depth = 60 - moveNumber;
}

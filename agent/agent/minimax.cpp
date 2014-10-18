//
//  minimax.cpp
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <iostream>
#include "minimax.h"

int minimax(point* root)
{
    int rec[8][8];
    if(root->depth == depth)
    {
        root->value = valueOfEvaluation();
        addToLog4Minimax(*root);
        return FALSE;
    }
    if(terminalStateCheck())
    {
        root->value = valueOfEvaluation();
        addToLog4Minimax(*root);
        return FALSE;
    }
    addToLog4Minimax(*root);
    ply = (ply + 1) % 2;
    int visited = FALSE;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (legal(i, j, rec, TRUE))
            {
                visited = TRUE;
                point* tmp = new point((root->depth % 2 == 0) ? INF : -INF, root->depth + 1);
                tmp->x = i;
                tmp->y = j;
                minimax(tmp);
                if(root->depth % 2 == 0 && root->value < tmp->value)
                {
                    root->value = tmp->value;
                    root->child = tmp;
                }
                else if (root->depth % 2 == 1 && root->value > tmp->value)
                {
                    root->value = tmp->value;
                    root->child = tmp;
                }
                addToLog4Minimax(*root);
                backup(rec);
            }
        }
    }
    if(!visited)
    {
        point* tmp = new point((root->depth % 2 == 0) ? INF : -INF, root->depth + 1);
        tmp->pass = TRUE;
        root->child = NULL;
        minimax(tmp);
        if(root->depth % 2 == 0 && root->value < tmp->value)
        {
            root->value = tmp->value;
        }
        else if (root->depth % 2 == 1 && root->value > tmp->value)
        {
            root->value = tmp->value;
        }
        addToLog4Minimax(*root);
    }
    ply = (ply + 1) % 2;
    if(root->child == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

void addToLog4Minimax(point p)
{
    log l;
    if (p.depth == 0)
    {
        l.node = "root";
    }
    else if(p.pass)
    {
        l.node = "pass";
    }
    else
    {
        l.node = "a1";
        l.node[0] = 'a' + p.y;
        l.node[1] = '1' + p.x;
    }
    l.depth = p.depth;
    l.value = p.value;
    history.push(l);
}

void printLog4Minimax()
{
    cout<<"Node,Depth,Value"<<endl;
    while(history.size() > 0)
    {
        log l = history.front();
        cout<<l.node<<","<<l.depth<<",";
        printValue(l.value);
        cout<<endl;
        history.pop();
    }
}

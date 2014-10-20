//
//  alphabeta.cpp
//  agent
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <iostream>
#include "alphabeta.h"

int alphabeta(point* root)
{
    int rec[8][8];
    if(root->depth == depth)
    {
        root->value = valueOfEvaluation();
        addToLog4Alphabeta(*root);
        return FALSE;
    }
    if(terminalStateCheck())
    {
        root->value = valueOfEvaluation();
        addToLog4Alphabeta(*root);
        return FALSE;
    }
    if(root->parent != NULL && root->pass && root->parent->pass)
    {
        root->value = valueOfEvaluation();
        addToLog4Alphabeta(*root);
        return FALSE;
    }
    ply = (ply + 1) % 2;
    addToLog4Alphabeta(*root);
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
                tmp->parent = root;
                alphabeta(tmp);
                if(root->depth % 2 == 0 && root->value < tmp->value)
                {
                    root->value = tmp->value;
                    if(root->child != NULL) delete root->child;
                    root->child = tmp;
                }
                else if (root->depth % 2 == 1 && root->value > tmp->value)
                {
                    root->value = tmp->value;
                    if(root->child != NULL) delete root->child;
                    root->child = tmp;
                }
                backup(rec);
                if((root->depth % 2 == 0 && root->value >= root->beta)
                   || (root->depth % 2 == 1 && root->value <= root->alpha))
                {
                    addToLog4Alphabeta(*root);
                    flag = FALSE;
                    break;
                }
                if (root->depth % 2 == 0 && root->alpha < root->value) root->alpha = root->value;
                if (root->depth % 2 == 1 && root->beta > root->value) root->beta = root->value;
                addToLog4Alphabeta(*root);
            }
        }
    }
    if(!visited)
    {
        point* tmp = new point((root->depth % 2 == 0) ? INF : -INF, root->depth + 1, root->alpha, root->beta);
        tmp->parent = root;
        tmp->pass = TRUE;
        alphabeta(tmp);
        if(root->depth % 2 == 0 && root->value < tmp->value)
        {
            root->value = tmp->value;
        }
        else if (root->depth % 2 == 1 && root->value > tmp->value)
        {
            root->value = tmp->value;
        }
        if(!(root->depth % 2 == 0 && root->value >= root->beta)
           && !(root->depth % 2 == 1 && root->value <= root->alpha))
        {
            if (root->depth % 2 == 0 && root->alpha < root->value) root->alpha = root->value;
            if (root->depth % 2 == 1 && root->beta > root->value) root->beta = root->value;
        }
        addToLog4Alphabeta(*root);
    }
    ply = (ply + 1) % 2;
    if(root->child == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

void addToLog4Alphabeta(point p)
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
    l.alpha = p.alpha;
    l.beta = p.beta;
    history.push(l);
}

void printLog4Alphabeta()
{
    cout<<"Node,Depth,Value,Alpha,Beta"<<endl;
    while(history.size() > 0)
    {
        log l = history.front();
        cout<<l.node<<","<<l.depth<<",";
        printValue(l.value);
        cout<<",";
        printValue(l.alpha);
        cout<<",";
        printValue(l.beta);
        cout<<endl;
        history.pop();
    }
}

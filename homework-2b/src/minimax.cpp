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
    if(root->parent != NULL && root->pass && root->parent->pass)
    {
        root->value = valueOfEvaluation();
        addToLog4Minimax(*root);
        return FALSE;
    }
    ply = (ply + 1) % 2;
    addToLog4Minimax(*root);
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
                tmp->parent = root;
                minimax(tmp);
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
                addToLog4Minimax(*root);
                backup(rec);
            }
        }
    }
    if(!visited)
    {
        point* tmp = new point((root->depth % 2 == 0) ? INF : -INF, root->depth + 1);
        tmp->parent = root;
        tmp->pass = TRUE;
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

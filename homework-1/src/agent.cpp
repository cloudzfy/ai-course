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
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <string>
using namespace std;
#define TRUE 1
#define FALSE 0
#define INF 999999

int graph[1000][1000];
int node_num,src_i,dest_i;
vector<int> expansion, output;

struct Node
{
    string name;
    int parent;
    int visited;
    int cost;
    int index;
    friend bool operator< (Node a, Node b)
    {
        if(a.cost == b.cost)
        {
            return a.name > b.name;
        }
        return a.cost > b.cost;
    }
    
}node[1000];

int bfs()
{
    priority_queue<Node> q;
    node[src_i].visited = 1;
    node[src_i].cost = 0;
    q.push(node[src_i]);
    while(!q.empty())
    {
        int cur = q.top().index;
        expansion.push_back(cur);
        q.pop();
        if(cur == dest_i)
        {
            return TRUE;
        }
        for(int i=0;i<node_num;i++)
        {
           if(graph[cur][i] && !node[i].visited)
           {
               node[i].parent = cur;
               node[i].cost = node[cur].cost + 1;
               node[i].visited = 1;
               q.push(node[i]);
           }
        }
    }
    return FALSE;
}

int dfs()
{
    priority_queue<Node> q;
    node[src_i].visited = 1;
    node[src_i].cost = 0;
    q.push(node[src_i]);
    while(!q.empty())
    {
        int cur = q.top().index;
        expansion.push_back(cur);
        q.pop();
        if(cur == dest_i)
        {
            return TRUE;
        }
        for(int i=0;i<node_num;i++)
        {
            if(graph[cur][i] && !node[i].visited)
            {
                node[i].parent = cur;
                node[i].cost = node[cur].cost - 1;
                node[i].visited = 1;
                q.push(node[i]);
            }
        }
    }
    return FALSE;
}

int ucs()
{
    priority_queue<Node> q;
    node[src_i].cost = 0;
    q.push(node[src_i]);
    while(!q.empty())
    {
        int cur = q.top().index;
        q.pop();
        if (node[cur].visited) continue;
        node[cur].visited = 1;
        expansion.push_back(cur);
        if(cur == dest_i)
        {
            return TRUE;
        }
        for(int i=0;i<node_num;i++)
        {
            if(graph[cur][i] && !node[i].visited)
            {
                if(node[i].cost > node[cur].cost + graph[cur][i])
                {
                    node[i].parent = cur;
                    node[i].cost = node[cur].cost + graph[cur][i];
                    q.push(node[i]);
                }
            }
        }
    }
    return FALSE;
}

int main(int argc, char const * argv[])
{
    int task_num,ans,cost;
    string src,dest;
    FILE *in, *out;
    in = freopen("input.txt","r",stdin);
    out = freopen("output.txt","w",stdout);
    cin>>task_num>>src>>dest>>node_num;
    for(int i=0;i<node_num;i++)
    {
        cin>>node[i].name;
        node[i].visited = 0;
        node[i].cost = INF;
        node[i].index = i;
        if(node[i].name == src)
        {
            src_i=i;
        }
        if(node[i].name == dest)
        {
            dest_i =i;
        }
    }
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            cin>>graph[i][j];
        }
    }
    if(task_num == 1)
    {
        ans=bfs();
    }
    else if(task_num == 2)
    {
        ans = dfs();
    }
    else if(task_num == 3)
    {
        ans = ucs();
    }
    cout<<node[expansion.at(0)].name;
    for(int i=1;i<expansion.size();i++)
    {
        cout<<"-"<<node[expansion.at(i)].name;
    }
    cout<<endl;
    if(ans)
    {
        int cur=dest_i;
        output.push_back(cur);
        cost=0;
        while(cur!=src_i)
        {
            cost += graph[node[cur].parent][cur];
            cur = node[cur].parent;
            output.push_back(cur);
        }
        cout<<node[output.back()].name;
        for (int i = (int)output.size() - 2; i >= 0; i--)
        {
            cout<<"-"<<node[output.at(i)].name;
        }
        cout<<endl;
        cout<<cost<<endl;
    }
    else
    {
        cout<<"NoPathAvailable"<<endl;
        cout<<"0"<<endl;
    }
    fclose(in);
    fclose(out);
    return 0;
}

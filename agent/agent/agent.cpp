#include <iostream>
#include <string>
#include <cstring>
#include <string>
#include <stack>
#include <queue>

#define TRUE 1
#define FALSE 0
#define INF 9999999

using namespace std;

int map[8][8];
int ply, depth;

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
struct Point
{
    int x;
    int y;
    Point* parent;
    int value;
    int depth;
    Point* child;
};

struct Log
{
    string node;
    int depth;
    int value;
};

queue<Log> history;

int legal(int x, int y)
{
    int a, b;
    a = 0; b = 0;
    // X+ Direction
    for (int i = x + 1; i < 8; i++)
    {
        if(map[i][y] == ply && a == 1) b = 1;
        if(map[i][y] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X- Direction
    for (int i = x - 1; i >= 0; i--)
    {
        if(map[i][y] == ply && a == 1) b = 1;
        if(map[i][y] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // Y+ Direction
    for (int j = y + 1; j < 8; j++)
    {
        if(map[x][j] == ply && a == 1) b = 1;
        if(map[x][j] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // Y- Direction
    for (int j = y - 1; j >= 0; j--)
    {
        if(map[x][j] == ply && a == 1) b = 1;
        if(map[x][j] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X+Y+ Direction
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X-Y- Direction
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X+Y- Direction
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X-Y+ Direction
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
        else break;
    }
    if(b == 1) return TRUE;
    return FALSE;
}

int val()
{
    int val = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == ply)
            {
                val += eval[i][j];
            }
            else
            {
                val -= eval[i][j];
            }
        }
    }
    return val;
}

void print()
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

void printLog()
{
    while(history.size() > 0)
    {
        Log l = history.front();
        cout<<l.node<<","<<l.depth<<",";
        if (l.value == INF)
        {
            cout<<"Infinity";
        }
        else if(l.value == -INF)
        {
            cout<<"-Infinity";
        }
        else
        {
            cout<<l.value;
        }
        cout<<endl;
        history.pop();
    }
}

int greedy()
{
    int max = -INF;
    int x = 0, y = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(legal(i, j))
            {
                int tmp = val() + eval[i][j];
                if(tmp > max)
                {
                    max = tmp;
                    x = i;
                    y = j;
                }
            }
        }
    }
    if(max != -INF)
    {
        map[x][y] = ply;
        return TRUE;
    }
    return FALSE;
}

int minimax()
{
    stack<Point> s;
    Point root;
    root.value = -INF;
    root.depth = 0;
    root.parent = NULL;
    root.child = NULL;
    s.push(root);
    while(!s.empty())
    {
        Point cur = s.top();
        s.pop();
        Log l;
        if (cur.depth == 0)
        {
            l.node = "root";
        }
        else
        {
            l.node[0] = 'a' + cur.x;
            l.node[1] = '1' + cur.y;
            l.node[2] = 0;
        }
        l.depth = cur.depth;
        l.value = cur.value;
        history.push(l);
        if(cur.depth > 0)
        {
            if(cur.depth % 2 == 1)
            {
                map[cur.x][cur.y] = ply;
            }
            else
            {
                map[cur.x][cur.y] = (ply + 1) % 2;
            }
        }
        if(cur.depth == depth)
        {
            while(cur.depth >= s.top().depth)
            {
                cur.value = (cur.depth % 2 == 0) ? val() : -val();
                map[cur.x][cur.y] = 2;
                if (cur.parent->depth % 2 == 0)
                {
                    cur.parent->value = (cur.parent->value < cur.value) ? cur.value : cur.parent->value;
                    cur.parent->child = &cur;
                }
                else
                {
                    cur.parent->value = (cur.parent->value > cur.value) ? cur.value : cur.parent->value;
                    cur.parent->child = &cur;
                }
                cur = *cur.parent;
            }
        }
        else
        {
            if(cur.depth % 2 == 1)
            {
                ply = (ply + 1) % 2;
            }
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (legal(i, j))
                    {
                        Point tmp;
                        tmp.x = i;
                        tmp.y = j;
                        tmp.value = (cur.depth % 2 == 0) ? INF : -INF;
                        tmp.depth = cur.depth + 1;
                        tmp.parent = &cur;
                        tmp.child = NULL;
                        s.push(tmp);
                    }
                }
            }
            if(cur.depth % 2 == 1)
            {
                ply = (ply + 1) % 2;
            }
        }
    }
    if (root.child != NULL)
    {
        map[root.child->x][root.child->y] = ply;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


int main(int argc, const char * argv[]) {
    int task_no;
    string player, states;
    FILE *in, *out;
    //in = freopen("input.txt", "r", stdin);
    //out = freopen("output.txt", "w", stdout);
    cin>>task_no>>player>>depth;
    if(player[0] == 'X')
    {
        ply = 1;
    }
    else
    {
        ply = 0;
    }
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
    if(task_no == 1)
    {
        greedy();
        print();
    }
    else if(task_no == 2)
    {
        minimax();
        print();
        printLog();
    }
    fclose(in);
    fclose(out);
    return 0;
}

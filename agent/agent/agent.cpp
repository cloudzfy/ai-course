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

void init(int rec[][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rec[i][j] = 3;
        }
    }
}

int legal(int x, int y, int rec[][8])
{
    int a, b, c = FALSE;
    a = FALSE; b = FALSE;
    // X+ Direction
    for (int i = x + 1; i < 8; i++)
    {
        if(map[i][y] == ply && a == TRUE) b = TRUE;
        if(map[i][y] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
        if(map[i][y] == ply && a == TRUE) b = TRUE;
        if(map[i][y] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
        if(map[x][j] == ply && a == TRUE) b = TRUE;
        if(map[x][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
        if(map[x][j] == ply && a == TRUE) b = TRUE;
        if(map[x][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
        if(map[i][j] == ply && a == TRUE) b = TRUE;
        if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
        if(map[i][j] == ply && a == TRUE) b = TRUE;
        if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
        if(map[i][j] == ply && a == TRUE) b = TRUE;
        if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
        {
            if(map[i][j] == ply && a == TRUE)
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
        if(map[i][j] == ply && a == TRUE) b = TRUE;
        if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b == TRUE)
    {
        if(!c) init(rec);
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
            else if(map[i][j] != 2)
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

void addToLog(Point p)
{
    Log l;
    if (p.depth == 0)
    {
        l.node = "root";
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

int greedy()
{
    int rec[8][8];
    int max = -INF;
    int x = 0, y = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(legal(i, j, rec))
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


int minimax(Point* root)
{
    int rec[8][8];
    ply = (ply + 1) % 2;
    if(root->depth == depth)
    {
        root->value = val();
        addToLog(*root);
    }
    else
    {
        addToLog(*root);
        root->child = NULL;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (legal(i, j, rec))
                {
                    Point* tmp = new Point();
                    tmp->x = i;
                    tmp->y = j;
                    tmp->value = (root->depth % 2 == 0) ? INF : -INF;
                    tmp->depth = root->depth + 1;
                    tmp->child = NULL;
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
                    addToLog(*root);
                    backup(rec);
                }
            }
        }
    }
    ply = (ply + 1) % 2;
    if(root->child == NULL)
    {
        return FALSE;
    }
    return TRUE;
}


int main(int argc, const char * argv[]) {
    int task_no;
    string player, states;
    FILE *in, *out;
    in = freopen("input.txt", "r", stdin);
    out = freopen("output.txt", "w", stdout);
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
        Point root;
        root.value = -INF;
        root.depth = 0;
        ply = (ply + 1) % 2;
        int ans = minimax(&root);
        if(ans)
        {
            ply = (ply + 1) % 2;
            int rec[8][8];
            legal(root.child->x, root.child->y, rec);
        }
        print();
        printLog();
    }
    fclose(in);
    fclose(out);
    return 0;
}

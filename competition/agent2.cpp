#include <iostream>
#include <string>
#include <cstring>
#include <string>
#include <stack>
#include <queue>

#define TRUE 1
#define FALSE 0
#define INF 2147483647

#define EMPTY 2
#define XPOS 1
#define OPOS 0
#define ZERO 3

#define STABLE 0
#define SEMISTABLE 1
#define UNSTABLE 2

#define ZEROLINE 0
#define STABLELINE 4

#define WIN 1
#define TIE 0
#define LOSS -1

using namespace std;

int map[8][8];

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

int ply, depth, moveNumber;

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
struct point
{
    int x;
    int y;
    int value;
    int depth;
    point* child;
    int alpha;
    int beta;
    int pass;
    point(){}
    point(int value, int depth)
    {
        this->value = value;
        this->depth = depth;
        this->child = NULL;
    }
    point(int value, int depth, int alpha, int beta)
    {
        this->value = value;
        this->depth = depth;
        this->alpha = alpha;
        this->beta = beta;
        this->child = NULL;
        this->pass = FALSE;
    }
};

struct Log
{
    string node;
    int depth;
    int value;
    int alpha;
    int beta;
};

queue<Log> history;

void init(int rec[][8], int val)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rec[i][j] = val;
        }
    }
}

int legal(int x, int y, int rec[][8], int op)
{
    int a, b, c = FALSE;
    a = FALSE; b = FALSE;
    if(map[x][y] != EMPTY)
    {
        return FALSE;
    }
    // X+ Direction
    for (int i = x + 1; i < 8; i++)
    {
        if(map[i][y] == ply && a) b = TRUE;
        else if(map[i][y] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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
        if(map[i][y] == ply && a) b = TRUE;
        else if(map[i][y] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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
        if(map[x][j] == ply && a) b = TRUE;
        else if(map[x][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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
        if(map[x][j] == ply && a) b = TRUE;
        else if(map[x][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--)
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
    // X-Y+ Direction
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++)
    {
        if(map[i][j] == ply && a) b = TRUE;
        else if(map[i][j] == (ply + 1) % 2) a = TRUE;
        else break;
    }
    if(b && !op) return TRUE;
    if(b)
    {
        if(!c) init(rec, ZERO);
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

int valueOfEvaluation()
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
            else if(map[i][j] == (ply + 1) % 2)
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

void printValue(int value)
{
    if (value == INF)
    {
        cout<<"Infinity";
    }
    else if(value == -INF)
    {
        cout<<"-Infinity";
    }
    else
    {
        cout<<value;
    }
}

void printLog4Minimax()
{
    cout<<"Node,Depth,Value"<<endl;
    while(history.size() > 0)
    {
        Log l = history.front();
        cout<<l.node<<","<<l.depth<<",";
        printValue(l.value);
        cout<<endl;
        history.pop();
    }
}

void printLog4Alphabeta()
{
    cout<<"Node,Depth,Value,Alpha,Beta"<<endl;
    while(history.size() > 0)
    {
        Log l = history.front();
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

void addToLog4Minimax(point p)
{
    Log l;
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

void addToLog4Alphabeta(point p)
{
    Log l;
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

int greedy()
{
    int rec[8][8];
    int max = -INF;
    int x = 0, y = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(legal(i, j, rec, TRUE))
            {
                int tmp = valueOfEvaluation();
                if(tmp > max)
                {
                    max = tmp;
                    x = i;
                    y = j;
                }
                backup(rec);
            }
        }
    }
    if(max != -INF)
    {
        legal(x, y, rec, TRUE);
        return TRUE;
    }
    return FALSE;
}


int minimax(point* root)
{
    int rec[8][8];
    ply = (ply + 1) % 2;
    if(root->depth == depth)
    {
        root->value = valueOfEvaluation();
        addToLog4Minimax(*root);
    }
    else
    {
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
        }
    }
    ply = (ply + 1) % 2;
    if(root->child == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

int alphabeta(point* root)
{
    int rec[8][8];
    ply = (ply + 1) % 2;
    if(root->depth == depth)
    {
        root->value = valueOfEvaluation();
        addToLog4Alphabeta(*root);
    }
    else
    {
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
                    alphabeta(tmp);
                    if(root->depth % 2 == 0 && root->value < tmp->value)
                    {
                        root->value = tmp->value;
                        root->alpha = tmp->value;
                        if(root->child != NULL) delete root->child;
                        root->child = tmp;
                    }
                    else if (root->depth % 2 == 1 && root->value > tmp->value)
                    {
                        root->value = tmp->value;
                        root->beta = tmp->value;
                        if(root->child != NULL) delete root->child;
                        root->child = tmp;
                    }
                    addToLog4Alphabeta(*root);
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
            alphabeta(tmp);
            if(root->depth % 2 == 0 && root->value < tmp->value)
            {
                root->value = tmp->value;
                root->alpha = tmp->value;
                root->child = tmp;
            }
            else if (root->depth % 2 == 1 && root->value > tmp->value)
            {
                root->value = tmp->value;
                root->beta = tmp->value;
                root->child = tmp;
            }
            addToLog4Alphabeta(*root);
        }
    }
    ply = (ply + 1) % 2;
    if(root->child == NULL)
    {
        return FALSE;
    }
    return TRUE;
}


int xSquareCost()
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        if(map[xSquarePoint[i][0]][xSquarePoint[i][1]] == ply
           && map[edgePoint[i][0][0]][edgePoint[i][0][1]] == EMPTY)
        {
            int tmp = 0;
            int a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == ply) a = TRUE;
                else if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (ply + 1) % 2 && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += (ply + 1) % 2;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (ply + 1) % 2) break;
                    tmp *= 3;
                    tmp += ply;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (ply + 1) % 2) break;
                    sum -= edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
            tmp = 0;
            a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == ply) a = TRUE;
                else if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (ply + 1) % 2 && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += (ply + 1) % 2;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (ply + 1) % 2) break;
                    tmp *= 3;
                    tmp += ply;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (ply + 1) % 2) break;
                    sum -= edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
        }
        if(map[xSquarePoint[i][0]][xSquarePoint[i][1]] == (ply + 1) % 2
           && map[edgePoint[i][0][0]][edgePoint[i][0][1]] == EMPTY)
        {
            int tmp = 0;
            int a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (ply + 1) % 2) a = TRUE;
                else if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == ply && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += ply;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == ply) break;
                    tmp *= 3;
                    tmp += (ply + 1) % 2;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == ply) break;
                    sum += edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
            tmp = 0;
            a = FALSE, b = FALSE;
            for (int j = 1; j < 7; j++)
            {
                if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == (ply + 1) % 2) a = TRUE;
                else if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == ply && a) b = TRUE;
                else break;
            }
            if(b)
            {
                tmp += ply;
                for(int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == ply) break;
                    tmp *= 3;
                    tmp += (ply + 1) % 2;
                }
                for (int j = 1; j < 7; j++)
                {
                    if(map[edgePoint[(i + 1) % 4][j][0]][edgePoint[(i + 1) % 4][j][1]] == ply) break;
                    sum += edgeWeight[j][edgeStabilityMap[tmp][j]];
                }
            }
        }
    }
    return FALSE;
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
            if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == ply)
            {
                sum += edgeWeight[j][edgeStabilityMap[tmp][j]];
            }
            else if(map[edgePoint[i][j][0]][edgePoint[i][j][1]] == (ply + 1) % 2)
            {
                sum -= edgeWeight[j][edgeStabilityMap[tmp][j]];
            }
        }
    }
    return sum + xSquareCost();
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
            if(map[i][j] == ply && internalStabilityMap[i][j] == STABLELINE) pCount++;
            if(map[i][j] == (ply + 1) % 2 && internalStabilityMap[i][j] == STABLELINE) oCount++;
        }
    }
    return pCount - oCount;
}

int currentMobility()
{
    int pCount = 0, oCount = 0;
    int rec[8][8];
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
    ply = (ply + 1) % 2;
    return 100 * (pCount - oCount)/(pCount + oCount + 2);
}

int potentialMobility()
{
    int sumOfOppo = 0, sumOfEmpty = 0, sumOfOppos = 0;
    int oppo = (ply + 1) % 2;
    int rec[8][8];
    init(rec, 0);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == oppo)
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
            if(map[i][j] == oppo && rec[i][j])
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
            if(map[i][j] == ply)
            {
                pCount++;
            }
            else if(map[i][j] == (ply + 1) % 2)
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
            if(map[i][j] == ply)
            {
                pCount++;
            }
            else if(map[i][j] == (ply + 1) % 2)
            {
                oCount++;
            }
        }
    }
    if (pCount < oCount) return LOSS;
    if (pCount > oCount) return WIN;
    return TIE;
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

int competition(point* root)
{
    int rec[8][8];
    ply = (ply + 1) % 2;
    if(root->depth == depth)
    {
        root->value = valueOfEvaluation4Competition();
    }
    else
    {
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
                        root->alpha = tmp->value;
                        if(root->child != NULL) delete root->child;
                        root->child = tmp;
                    }
                    else if (root->depth % 2 == 1 && root->value > tmp->value)
                    {
                        root->value = tmp->value;
                        root->beta = tmp->value;
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
            competition(tmp);
            if(root->depth % 2 == 0 && root->value < tmp->value)
            {
                root->value = tmp->value;
                root->alpha = tmp->value;
                root->child = tmp;
            }
            else if (root->depth % 2 == 1 && root->value > tmp->value)
            {
                root->value = tmp->value;
                root->beta = tmp->value;
                root->child = tmp;
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

void importEdgeStabilityMap()
{
    FILE *fp = fopen("/Users/cloudzfy/Documents/workspace/cs561/edgeStabilityGenerator/edgeStabilityGenerator/edgeStability.txt", "r");
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
    if(moveNumber < 46) depth = 5;
    else depth = 60 - moveNumber;
}

int main(int argc, const char * argv[]) {
    int taskNumber;
    string states;
    FILE *in, *out;
    in = freopen("input.txt", "r", stdin);
    out = freopen("output.txt", "w", stdout);
    taskNumber = 4;
    ply = 0;
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
        print();
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
        print();
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
        print();
        printLog4Alphabeta();
    }
    else if(taskNumber == 4)
    {
        importEdgeStabilityMap();
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
        print();
    }
    fclose(in);
    fclose(out);
    return 0;
}

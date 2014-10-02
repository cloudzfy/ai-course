#include <iostream>
#include <string>
#include <cstring>

#define TRUE 1
#define FALSE 0

using namespace std;

int map[8][8];
int ply;

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

int legal(int x, int y)
{
    int a, b;
    a = 0; b = 0;
    // X+ Direction
    for (int i = x; i < 8; i++)
    {
        if(map[i][y] == ply && a == 1) b = 1;
        if(map[i][y] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X- Direction
    for (int i = x; i >= 0; i--)
    {
        if(map[i][y] == ply && a == 1) b = 1;
        if(map[i][y] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // Y+ Direction
    for (int j = y; j < 8; j++)
    {
        if(map[x][j] == ply && a == 1) b = 1;
        if(map[x][j] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // Y- Direction
    for (int j = y; j >= 0; j--)
    {
        if(map[x][j] == ply && a == 1) b = 1;
        if(map[x][j] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X+Y+ Direction
    for (int i = x, j = y; i < 8 && j < 8; i++, j++)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X-Y- Direction
    for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X+Y- Direction
    for (int i = x, j = y; i < 8 && j >= 0; i++, j--)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    a = 0; b = 0;
    // X-Y+ Direction
    for (int i = x, j = y; i >= 0 && j < 8; i--, j++)
    {
        if(map[i][j] == ply && a == 1) b = 1;
        if(map[i][j] == (ply + 1) % 2) a = 1;
    }
    if(b == 1) return TRUE;
    return FALSE;
}

int greedy()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(legal(i,j))
            {
                
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int task_no, depth;
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
        
    }
    fclose(in);
    fclose(out);
    return 0;
}

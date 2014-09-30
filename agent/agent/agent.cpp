#include <iostream>
#include <string>
#include <cstring>

using namespace std;

char map[10][10];

int main(int argc, const char * argv[]) {
    int task_no, depth;
    string player;
    FILE *in, *out;
    in = freopen("input.txt", "r", stdin);
    out = freopen("output.txt", "w", stdout);
    cin>>task_no>>player>>depth;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin>>map[i][j];
        }
    }
    if(task_no == 1)
    {
        
    }
    fclose(in);
    fclose(out);
    return 0;
}

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

int main(int argc, const char * argv[]) {
    char states[10];
    int x;
        int xnum = 0, onum = 0;
    FILE *fp = fopen("input.txt", "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%s", states);
        for (int j = 0; j < 8; j++)
        {
            if(states[j] == 'X')
            {
                xnum++;
            }
            else if(states[j] == 'O')
            {
                onum++;
            }
        }
    }
    fclose(fp);
    printf("X:%d\tO:%d\tSUM:%d\n",xnum,onum,xnum+onum);
    if(x==2 || xnum+onum == 64)
    {
        printf("################");
        if(xnum>onum) printf("X Win.\n");
        else if(xnum<onum) printf("O Win.\n");
        else printf("TIE.");
        
    }
    return 0;
}

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
    FILE *fp = fopen("output.txt", "r");
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

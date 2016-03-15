//
//  depthAdjustmentGenerator.cpp
//  depthAdjustmentGenerator
//
//  Created by Youzheng Chen on 10/17/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <ctime>
#include "competition.h"
#include "utilities.h"

int tmpMap[8][8] = {
    {XPOS, EMPTY, OPOS, EMPTY, EMPTY, XPOS, EMPTY, XPOS},
    {EMPTY, OPOS, EMPTY, OPOS, XPOS, XPOS, XPOS, EMPTY},
    {OPOS, OPOS, XPOS, OPOS, XPOS, XPOS, EMPTY, EMPTY},
    {EMPTY, EMPTY, XPOS, OPOS, OPOS, XPOS, EMPTY, OPOS},
    {EMPTY, EMPTY, XPOS, OPOS, XPOS, XPOS, XPOS, EMPTY},
    {EMPTY, EMPTY, XPOS, OPOS, XPOS, XPOS, XPOS, XPOS},
    {EMPTY, EMPTY, XPOS, XPOS, EMPTY, EMPTY, XPOS, EMPTY},
    {EMPTY, EMPTY, XPOS, EMPTY, EMPTY, EMPTY, EMPTY, XPOS}
};

void initialMap()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            map[i][j] = tmpMap[i][j];
        }
    }
}

int main()
{
    int d;
    ply = 0;
    time_t startTime = clock();
    for (int i = 0; i < 150000; i++)
    {
        valueOfEvaluation4Competition(5);
    }
    time_t endTime = clock();
    if((endTime - startTime) / CLOCKS_PER_SEC > 3.0)
    {
        d = 5;
    }
    else
    {
        d = 7;
    }
    FILE *out = freopen("src/depthAdjustment.cpp", "w", stdout);
    cout<<"// For 150000 times evaluation, this machine takes ";
    cout<<(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
    cout<<" ms."<<endl;
    cout<<"#include \"competition.h\""<<endl;
    cout<<"#include \"utilities.h\""<<endl;
    cout<<endl;
    cout<<"void depthAdjustment(int cpuTime)"<<endl;
    cout<<"{"<<endl;
    cout<<"\tmoveNumber = 0;"<<endl;
    cout<<"\tfor (int i = 0; i< 8; i++)"<<endl;
    cout<<"\t{"<<endl;
    cout<<"\t\tfor (int j = 0; j < 8; j++)"<<endl;
    cout<<"\t\t{"<<endl;
    cout<<"\t\t\tif (map[i][j] != EMPTY)"<<endl;
    cout<<"\t\t\tmoveNumber++;"<<endl;
    cout<<"\t\t}"<<endl;
    cout<<"\t}"<<endl;
    cout<<"\tmoveNumber -= 4;"<<endl;
    cout<<"\tif(moveNumber < 46)"<<endl;
    cout<<"\t{"<<endl;
    cout<<"\t\tif(cpuTime > 80) depth = "<<d<<";"<< endl;
    cout<<"\t\telse depth = 5;"<<endl;
    cout<<"\t}"<<endl;
    cout<<"\telse depth = 60 - moveNumber;"<<endl;
    cout<<"}"<<endl;
    fclose(out);
    return 0;
}

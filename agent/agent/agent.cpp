//
//  agent.cpp
//  agent
//
//  Created by Youzheng Chen on 11/22/14.
//  Copyright (c) 2014 USC. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "utilities.h"
#include "chaining.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int numOfClauses;
    string sentence;
    //FILE *in, *out;
    //in = freopen("input.txt","r",stdin);
    //out = freopen("output.txt","w",stdout);
    cin>>sentence;
    scanf("%d",&numOfClauses);
    for(int i=0;i<numOfClauses;i++)
    {
        cin>>sentence;
    }
    return 0;
}

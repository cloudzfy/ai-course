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
    string sentence, query;
    knowledgeBase kb;
    FILE *in, *out;
    in = freopen("input.txt","r",stdin);
    out = freopen("output.txt","w",stdout);
    cin>>query;
    scanf("%d",&numOfClauses);
    for(int i=0;i<numOfClauses;i++)
    {
        cin>>sentence;
        kb.addNewStatement(sentence);
    }
    bool ans = backwardChainingAsk(kb, query);
    if(ans)
    {
        cout<<"TRUE"<<endl;
    }
    else
    {
        cout<<"FALSE"<<endl;
    }
    return 0;
}

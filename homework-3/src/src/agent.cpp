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

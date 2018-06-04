//
// Created by wj_de on 18-5-30.
//

#ifndef CONTROLLED_INSTRUCT_H
#define CONTROLLED_INSTRUCT_H

#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
class Cinstruct {
private:
    string shell(const string &command,const string &ip);
    int socket;
public:
    void find_instruct(map<string,string> &inst);
    Cinstruct(int sock):socket(sock)
            {

            }


};


#endif //CONTROLLED_INSTRUCT_H

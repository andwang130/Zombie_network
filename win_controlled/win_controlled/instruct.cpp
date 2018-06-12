//
// Created by wj_de on 18-5-30.
//

#include "instruct.h"
#include <string.h>
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<stdlib.h>
#include "Protocol.h"
void Cinstruct::find_instruct(map<string,string> &inst)
{
    if (inst["inst_type"] == "shell") {
        string cmd = inst["command"];
        string ip=inst["Publisher"];
        shell(cmd,ip);
    }

}

string Cinstruct::shell(const string &command,const string &ip) {
    cout<<"*****进入shell操作******"<<endl;
	int n = system(command.c_str());
	string req;
	if (n != 0)
	{
		req = "flase";
	}
	else
	{
		req = "true";
	}
    cout<<"*****shell操作结束******"<<endl;
    map<string,string> requst;
    requst["url"]="shellreq";
    requst["to"]=ip;
    requst["body"]=req;
    CProtocol pro;
    string reqson=pro.structure(requst);
	//cout <<reqson<<endl;
    send(socket,reqson.c_str(),strlen(reqson.c_str()),0);
    return req;
}


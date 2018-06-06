//
// Created by wj_de on 18-5-30.
//


#include "instruct.h"
#include <string.h>
#include <sys/socket.h>
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
    FILE *PP = popen(command.c_str(), "r");  //linux执行shell命令的函数
    if (!PP) {
        return "fall"; //执行失败
    }
    string req;
    char tmp[1024]={0};//用来接收命令的返回
    while(fgets(tmp, sizeof(tmp),PP)!=NULL)   //fgets用来获取返回每行数据
    {


        tmp[strlen(tmp)-1]='$';
        req+=tmp;
        memset(tmp,0,1024);
    }
    pclose(PP);
    cout<<req<<endl;
    cout<<"*****shell操作结束******"<<endl;
    map<string,string> requst;
    requst["url"]="shellreq";
    requst["to"]=ip;
    requst["body"]=req;
    CProtocol pro;
    string reqson=pro.structure(requst);
    cout<<reqson<<endl;
    send(socket,reqson.c_str(),strlen(reqson.c_str()),0);
    return req;
}


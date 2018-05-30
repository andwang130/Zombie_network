//
// Created by wj_de on 18-5-30.
//


#include "instruct.h"


void Cinstruct::find_instruct(map<string,string> &inst)
{
    if (inst["inst_type"] == "shell") {
        string cmd = inst["command"];
        shell(cmd);
    }

}

string Cinstruct::shell(const string command) {
    cout<<"*****进入shell操作******"<<endl;
    FILE *PP = popen(command.c_str(), "r");  //linux执行shell命令的函数
    if (!PP) {
        return "fall"; //执行失败
    }
    string req;
    char tmp[1024]={0};//用来接收命令的返回
    while(fgets(tmp, sizeof(tmp),PP)!=NULL)   //fgets用来获取返回每行数据
    {
        cout<<tmp<<endl;
        req+=tmp;
    }
    return req;
    cout<<"*****shell操作结束******"<<endl;
}


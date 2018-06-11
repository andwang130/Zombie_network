#include <iostream>
#include "control_socket.h"
#include "Protocol.h"
#include <string.h>

int main() {
    Csocket C_socket("127.0.0.1",8080);
    CProtocol pr;
    map<string,string> dt;
    dt["url"]="cout_info";
    dt["to"]="127.0.0.1:44678";
    dt["inst_type"]="shell";
    dt["hax"]="hax123412312321"; //控制端必须的密码
    while (true)
    {   string str;
        cin>>str;
        dt["command"] = str;
        string req = pr.structure(dt);
        C_socket.socket_send((char *) req.c_str());
        C_socket.sokcet_recv();
    }
        cin.get();

//    string text="aaaa:aaaaa\ndsd:sdsd\n<-suoyuzhif->";
//    map<string,string> map1=pr.analysis(text);
//    map<string,string>::iterator ite;
//    for(ite=map1.begin();ite!=map1.end();ite++)
//    {
//        cout<<"back:"<<ite->first<<"end:"<<ite->second<<endl;
//    }
    return 0;
}
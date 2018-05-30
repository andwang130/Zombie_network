
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
    } else if (dt["url"] == "to") {
        to_Broiler();
    }


}

void Base::to_Broiler() {
    cout << "进入 to" << endl;
    string ip = dt["to"];
    int coon = Broiler[ip];
    string test =CProtocol::structure(dt);
    cout << "coon：" << coon << endl;
    cout<<"test"<<test<<endl;
    send(coon, test.c_str(), strlen(test.c_str()), 0);
    cout << strerror(errno) << endl; //打印一下错误信息

}

void Base::login() {
    stringstream stream;
    stream << coon_info.port;

    Broiler[coon_info.ip + ':' + stream.str()] = coon_info.socket;

    cout << "login" << "::"<<coon_info.ip + ':' + stream.str()<<"coon"<<coon_info.socket<<endl;
}

void Base::Base_init(int coon, string ip, int port, string req) {

    coon_info.ip = ip;
    coon_info.socket = coon;
    coon_info.port = port;
    dt = CProtocol::analysis(req);
    find_url();

}

void Base::cout_info() {
    map<string, int>::iterator ite;
    for (ite = Broiler.begin(); ite != Broiler.end(); ite++) {
        cout << ite->first << " coon" << ite->second << endl;
    }
}
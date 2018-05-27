//
// Created by wj_de on 18-5-27.
//

#ifndef MIDDLE_SERVER_REQUETSHANDEL_H
#define MIDDLE_SERVER_REQUETSHANDEL_H
#endif //MIDDLE_SERVER_REQUETSHANDEL_H

#include <map>
#include<iostream>
using namespace std;
class Base
{
    map<string,string>dt;

    map<string,int> Broiler;
    map<string,int> Controller;
     struct info {
         string ip;
         int port;
         int socket;
     }coon_info;
    void find_url();
    void login();
    void cout_info();
public:
   void Base_init(int coon,string ip,int port,string req);  //把socket和ip端口和接受到的信息进行实例化
};

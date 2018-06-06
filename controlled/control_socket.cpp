//
// Created by meidai on 18-5-24.
//
#include "control_socket.h"
#include <string.h>
#include "instruct.h"
#include "Protocol.h"
#include <iostream>
const int LENMAX=1024;
void Csocket::socket_init(char *ip, int port)
{
  server.sin_addr.s_addr=inet_addr(ip);  //初始化要绑定的server
  server.sin_port=htons(port);
  server.sin_family=AF_INET;
  Clinet_socket=socket(AF_INET,SOCK_STREAM,0); //创建一个socket

}
void Csocket::socket_coont()
{
    connect(Clinet_socket,(struct sockaddr *)&server, sizeof(server));
    cout << strerror(errno) << endl; //打印一下错误信息

}
bool end_func(char *req) {
    //新的匹配方法
    char *flag = "<-suoyuzhif->";

    int flag_len = strlen(flag);
    int num = 0;
    int req_len = strlen(req);
    for(int i=req_len-flag_len;i<req_len;i++)
    {
        if(req[i]!=flag[num])
        {
            return false;
        }
        num++;
    }
    return true;


}
string  Csocket::sokcet_recv()
{
    char req[LENMAX];
    string  text;
    while (true)
    {
        memset(req,0, sizeof(req));
        int buf=recv(Clinet_socket,req,LENMAX,0);
        text+=req;
        cout<<req<<endl;
        if(end_func(req))
        {   cout<<"接收完毕"<<endl;
            Cinstruct cinst(Clinet_socket);
            CProtocol Cpro;
            map<string,string> re=Cpro.analysis(text);
            cinst.find_instruct(re);
        }
        if(buf==0||buf==-1)
        {
            return text;
        }
    }

}
void Csocket::socket_send(char * req)
{
    send(Clinet_socket,req,strlen(req),0);
    cout << strerror(errno) << endl; //打印一下错误信息

}
Csocket::Csocket(char *ip,int port){
    socket_init(ip,port);
    socket_coont();
}
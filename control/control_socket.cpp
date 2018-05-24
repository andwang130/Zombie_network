//
// Created by meidai on 18-5-24.
//
#include "control_socket.h"
#include <string.h>
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
}
string  Csocket::sokcet_recv()
{
    char req[LENMAX];
    string  text;
    while (true)
    {
        memset(req,0, sizeof(req));
        recv(Clinet_socket,req,LENMAX,0);
        text+=req;
    }
    cout<<text<<endl;
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
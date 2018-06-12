//
// Created by meidai on 18-5-24.
//

#ifndef CONTROL_CONTROL_SOCKET_H
#define CONTROL_CONTROL_SOCKET_H

#endif //CONTROL_CONTROL_SOCKET_H
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include<WinSock2.h>
#include <ws2tcpip.h>
using namespace std;
class Csocket
{
private:
    struct sockaddr_in server;
	SOCKET Clinet_socket;
    void socket_init(const char *ip,int port);
    void socket_coont();
public:
    Csocket(const char *ip,int port);
    string  sokcet_recv();
    void socket_send(char * req);
};
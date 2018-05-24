//
// Created by meidai on 18-5-24.
//

#ifndef CONTROL_CONTROL_SOCKET_H
#define CONTROL_CONTROL_SOCKET_H

#endif //CONTROL_CONTROL_SOCKET_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
class Csocket
{
private:
    struct sockaddr_in server;
    int Clinet_socket;
    void socket_init(char *ip,int port);
    void socket_coont();
public:
    Csocket(char *ip,int port);
    string  sokcet_recv();
    void socket_send(char * req);
};
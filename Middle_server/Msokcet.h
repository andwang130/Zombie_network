//
// Created by meidai on 18-5-23.
//

#ifndef MIDDLE_SERVER_MSOKCET_H
#define MIDDLE_SERVER_MSOKCET_H

#endif //MIDDLE_SERVER_MSOKCET_H

#include <sys/socket.h>
#include <iostream>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <map>
#include "requetshandel.h"
using namespace std;
class Csocket
{
private:
    Base *base;
    int serever_socket;
    int epoll_fd;
    struct info{
        string ip;
        int port;
        int socket;
    };
    map<int,info> Broiler;
    map<string,int> Controller;
    struct sockaddr_in server_in ;
    void server_bin(void);
    void server_listen(void);
    void server_ep_ctl();
    void epoll_while(void);
    void accept_coon(void);
    void coon_recv(int coon);
public:
    void serever_init(char *ip,int port);
    void run();
};

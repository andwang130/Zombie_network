//
// Created by meidai on 18-5-23.
//
#include "Msokcet.h"
void Csocket::serever_init(char *ip,int port)
{
    server_in.sin_family=AF_INET;
    server_in.sin_port=htons(port);
    server_in.sin_addr.s_addr=inet_addr(ip);
    epoll_fd=epoll_create(1);
    serever_socket=socket(AF_INET,SOCK_STREAM,0);


}
void Csocket::server_bin()
{

    if(bind(serever_socket,(struct sockaddr *)&server_in, sizeof(server_in))==-1)
    {
        cout << strerror(errno) << endl; //打印一下错误信息

        cout<< "bin init fall"<<endl;
    }
}
void Csocket::server_listen()
{
    listen(serever_socket,10);
}
void Csocket::server_ep_ctl()
{
    struct epoll_event event;
    event.data.fd=serever_socket;
    event.events=EPOLLIN;
    epoll_ctl(epoll_fd,EPOLLIN,serever_socket,&event);
}
void Csocket::epoll_while()
{
    while (true)
    {
        struct epoll_event event;
        epoll_wait(epoll_fd,&event,1,0);
        if(event.data.fd=serever_socket)
        {

         accept_coon();
        }

    }
}
void Csocket::accept_coon()
{
    string ip;
    struct sockaddr_in coon_in;
    socklen_t lent= sizeof(coon_in);
    int coon=accept(serever_socket,(struct sockaddr*)&coon_in,&lent);
    struct epoll_event event;
    event.data.fd=coon;
    event.events=EPOLLIN;
    epoll_ctl(epoll_fd,EPOLLIN,coon,&event);
    ip=inet_ntoa(coon_in.sin_addr);

    cout<<ip<<"已经链接"<<endl;
}
void Csocket::run()
{
     server_bin();
     server_listen();
     server_ep_ctl();
     epoll_while();
}

//协议体
/*hax:XXXXXXXXXXXXXXXXXX
  type:XXXX
*/
//
// Created by meidai on 18-5-23.
//
#include "Msokcet.h"
#include "Protocol.h"
const int LENMAX=1024;
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
        cout<<"发生事件"<<endl;
        if(event.data.fd==serever_socket)
        {
         accept_coon();
        }
        else
        {
            coon_recv(event.data.fd);
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
bool end_func(char *req)
{
    char *flag="<-suoyuzhif->";
    int flag_len=strlen(flag);
    int num=0;
    int req_len=strlen(req);
    for(int i=0;i<req_len;i++)
    {
        if(req[i]==flag[0])
        {
            for(int j=0;j<flag_len;j++)
            {
                if(req[i+j]!=flag[j])
                {
                    break;
                }
                else
                {
                    num++;
                }
            }
        }
        if(num==flag_len)
        {
            return true;
        }

    }
    cout<<num<<endl;
    if(num==flag_len)
    {
        cout<<"sd"<<endl;
        return true;
    }
    else
    {
        return false;
    }

}
void Csocket::coon_recv(int coon)
{
    cout<<"进入recv"<<endl;
    char req[LENMAX];
    string  text;
    while (true)
    {
        memset(req,0, sizeof(req));
        int buf=recv(coon,req,LENMAX,0);
        text+=req;
        if(end_func(req))
        {
            cout<<"数据接收完毕"<<endl;
            break;
        }

    }
    CProtocol pr;
    map<string,string> map1=pr.analysis(text);
    map<string,string>::iterator ite;
    for(ite=map1.begin();ite!=map1.end();ite++)
    {
        cout<<"back:"<<ite->first<<"end:"<<ite->second<<endl;
    }

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
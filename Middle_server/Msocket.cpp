//
// Created by meidai on 18-5-23.
//
#include "Msokcet.h"
#include "Protocol.h"
#include<unistd.h>

const int LENMAX = 1024;

void Csocket::serever_init(char *ip, int port) {
    data =Cdata::get_Cdata();
    server_in.sin_family = AF_INET;
    server_in.sin_port = htons(port);
    server_in.sin_addr.s_addr = inet_addr(ip);
    epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    serever_socket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    events = new epoll_event[10];
    setsockopt(serever_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //socket复用
}

void Csocket::server_bin() {

    if (bind(serever_socket, (struct sockaddr *) &server_in, sizeof(server_in)) == -1) {
        cout << strerror(errno) << endl; //打印一下错误信息

        cout << "bin init fall" << endl;
    }
}

void Csocket::server_listen() {
    listen(serever_socket, 10);
}

void Csocket::server_ep_ctl() {
    struct epoll_event event;
    event.data.fd = serever_socket;
    event.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serever_socket, &event);
}

void Csocket::epoll_while() {
    while (true) {
        struct epoll_event event;
        int ret = epoll_wait(epoll_fd, events, 10, -1);   //epoll_waith函数，获取响应的事件，第一个参数是epoll的描述符
        //第二个参数是用来接收epoll事件的结构体，可以是一个数组，第3个是一次接收的个数，第4个超时时间
        cout << "发生事件" << ret << endl;

        if (ret == 0) {
            continue;
        }
        if (ret == -1) {
            cout << "time out" << endl;
        }
        for (int i = 0; i < ret; i++) {
            if (events[i].data.fd == serever_socket) {
                accept_coon();
            } else {
                if (events[i].events == EPOLLIN) {
                    coon_recv(events[i].data.fd);
                } else
                {
                    close_socket(events[i].data.fd);
                }
            }
        }
    }
}

void Csocket::accept_coon() {
    string ip;
    struct sockaddr_in coon_in;
    socklen_t lent = sizeof(coon_in);
    int coon = accept(serever_socket, (struct sockaddr *) &coon_in, &lent);
    struct epoll_event event;
    event.data.fd = coon;
    event.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, coon, &event);
    ip = inet_ntoa(coon_in.sin_addr);
    int port = coon_in.sin_port;
    info info_coon;
    info_coon.ip = ip;
    info_coon.port = port;
    info_coon.socket = coon;
    Broiler[coon] = info_coon;
    cout << coon << "已经链接" << endl;

}

//bool end_func(char *req) {
//    char *flag = "<-suoyuzhif->";
//
//    int flag_len = strlen(flag);
//    int num = 0;
//    int req_len = strlen(req);
//    for (int i = 0; i < req_len; i++) {
//        if (req[i] == flag[0]) {
//            for (int j = 0; j < flag_len; j++) {
//                if (req[i + j] != flag[j]) {
//                    break;
//                } else {
//                    num++;
//                }
//            }
//        }
//        if (num == flag_len) {
//            return true;
//        }
//
//    }
//    cout << num << endl;
//    if (num == flag_len) {
//
//        return true;
//    } else {
//        cout << "sd" << endl;
//        return false;
//    }
//
//}
//旧的结束头匹配方法
bool end_func1(char *req) {
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
void Csocket::close_socket(int coon) {
    struct epoll_event event;
    event.data.ptr = NULL;
    event.events = 0;
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, coon, &event);//epool注销一个监听

    close(coon);
    data->Broiler_del(coon);

}

bool Csocket::hax_judge(char *req) {
    int num=0;
    int lent = strlen(req);
    for (int i = 0; i < 16; i++) {
        if (req[i] == hax_init[i]) {
            num++;
        }
    }

    cout << "num" << num << endl;
    if (num < 16) {
        return false;
    } else {
        return true;
    }


}

void Csocket::coon_recv(int coon) {
    char hax[16];
    memset(hax, 0, sizeof(hax));
    recv(coon, hax, 16, 0);
    if (!hax_judge(hax))  //测试用的hax值
    {
        cout << strlen(hax) << endl;
        cout << "验证未通过断开链接" << "hax" << hax << endl;
        close_socket(coon);
        return;      //验证未通过断开连接
    }


    cout << "进入recv" << endl;
    char req[LENMAX];
    string text;
    while (true) {
        memset(req, 0, sizeof(req));
        int buf = recv(coon, req, LENMAX, 0);
        text += req;
        cout << "buf" << buf << endl;
        if (end_func1(req)) {
            cout << "数据接收完毕" << endl;
            info coon_info = Broiler[coon];
            Base base;
            base.Base_init(coon_info.socket, coon_info.ip, coon_info.port, text);
            break;
        }
        if (buf == 0 || buf == -1) {
            close_socket(coon);
            break;
        }

    }
}

void Csocket::run() {
    server_bin();
    server_listen();
    server_ep_ctl();
    epoll_while();
}

Csocket::~Csocket() {
    delete events;
    delete data;
};
//xxxxxxxxxxxxxxxx  //hax值。比较被服务器验证才可以链接
//url&xxxxxxxxxxxxxxxx //这个参数决定转到函数来处理
//to&XXXXXXXXXXXXXXXXXX
//body&xx
//xx&xx
//<-suoyuzhif->   //结尾值
//一个段是通过/n来区分的，所以其他地方不要出现/n
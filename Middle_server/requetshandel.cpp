
#include"requetshandel.h"
#include "Protocol.h"
void Base::find_url()
{
    map<string,string>::iterator ite;
    for(ite=dt.begin();ite!=dt.end();ite++)
    {
        cout<<ite->first<<"  "<<ite->second<<endl;
    }
    cout<<"find"<<endl;

    if(dt["url"]=="login")
    {
        login();
    }
    else if(dt["url"]=="cout_info")
    {
        cout_info();
    }

}
void Base::login() {
    Broiler[coon_info.ip] = coon_info.socket;
    cout << "login" << endl;
}
void Base::Base_init(int coon,string ip,int port,string req)
{

    coon_info.ip=ip;
    coon_info.socket=coon;
    coon_info.port=port;
    dt=CProtocol::analysis(req);
    find_url();

}
void Base::cout_info() {
    map<string,int>::iterator ite;
    for(ite=Broiler.begin();ite!=Broiler.end();ite++)
    {
        cout<<ite->first<<ite->second<<endl;
    }
}
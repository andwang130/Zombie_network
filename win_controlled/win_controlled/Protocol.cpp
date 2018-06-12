//
// Created by meidai on 18-5-24.
//
#include "Protocol.h"
#include <vector>
string CProtocol::structure(map<string,string> str)
{
    string text;
    text="wwwwwwwwwwwwwwww";
    map<string,string>::iterator ite;
    for(ite=str.begin();ite!=str.end();ite++)
    {
        text+=ite->first+"&"+ite->second;
        text+='\n';
    }
    text+="<-suoyuzhif->";
    return text;

}
map<string,string> CProtocol::analysis(string str)
{

    map<string,string> dt;
    vector<string> vet;
    string::iterator ite;
    string text;
    for(ite=str.begin();ite!=str.end();ite++)
    {
        text+=*ite;
        if(*ite=='\n')
        {
            vet.push_back(text);
            text="";
        }
    }
    text="";
    vector<string>::iterator vite;
    for(vite=vet.begin();vite!=vet.end();vite++)
    {
        for(ite=vite->begin();ite!=vite->end();ite++)
        {
            if(*ite=='&')
            {
                string back(vite->begin(),ite);
                string end(ite+1,vite->end()-1);
                dt[back]=end;
                break;
            }
        }

    }
    return dt;
}

//
// Created by meidai on 18-5-24.
//

#ifndef CONTROL_PROTOCOL_H
#define CONTROL_PROTOCOL_H

#endif //CONTROL_PROTOCOL_H
#include <map>
using namespace std;   //协议体，构造协议和解析协议
class CProtocol
{
public:
    string structure(map<string,string> str);
    map<string,string> analysis(string);
};
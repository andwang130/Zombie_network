//
// Created by meidai on 18-5-24.
//

#ifndef MIDDLE_SERVER_PROTOCOL_H
#define MIDDLE_SERVER_PROTOCOL_H

#endif //MIDDLE_SERVER_PROTOCOL_H

#include <map>

using namespace std;   //协议体，构造协议和解析协议
class CProtocol {
public:
    static string structure(map<string, string> str);

    static map<string, string> analysis(string);
};
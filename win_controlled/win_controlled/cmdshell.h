#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<string.h>

using namespace std;
class MyCmdshell
{
public:
	string cmd_shell(string cmd_code)
	{
		/*
		通过使用winodws的管道Pipe来实现执行CMD命令，管道实际上一一段共享内存
		用来进程间通信
		*/
		STARTUPINFO si;  //STARTUPINFO用于指定新进程的主窗口特性的一个结构

		PROCESS_INFORMATION pi;//该结构返回有关新进程及其主线程的信息。

		HANDLE hread = NULL, hwrite = NULL; //句柄
		string req = "";
		char Cmdline[300] = { 0 };//命令行缓冲
		char senbuf[2048] = { 0 };//保存cmd命令的缓冲数据
		SECURITY_ATTRIBUTES sa; //安全描述符
		DWORD bytesread = 0;
		int ret = 0;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		
		//创建匿名管道
		if (!CreatePipe(&hread, &hwrite, &sa,0))
		{
			goto clean;
		}

		si.cb = sizeof(STARTUPINFO);
		GetStartupInfo(&si);

		si.hStdError = hwrite;
		si.hStdOutput = hwrite;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

		GetSystemDirectory(Cmdline, sizeof(Cmdline));  //获得系统CMD的目录

		strcat_s(Cmdline, "\\cmd.exe /c ");   //strcat函数字符串拼接，和目录进行拼接
		strcat_s(Cmdline, cmd_code.c_str());  //拼接上CMD命令

		//使用拼接好目录和cmd.exe和cmd命令打开一个CMD进程,传入了管道，可以使用管道来获得CMD执行的返回信息
		if (!CreateProcess(NULL, Cmdline, NULL, NULL,true, NULL, NULL, NULL, &si, &pi))
		{
			goto clean;
		}
		CloseHandle(hwrite);  //关闭，ReadFile才不阻塞
		while (true)
		{
			if (ReadFile(hread, senbuf, sizeof(senbuf), &bytesread, NULL)==0)
			{
				break;
			}//返回的数据大小0，读完了
			
			req += senbuf;
		
			memset(senbuf, 0, sizeof(senbuf));//清空缓存区
			Sleep(100);
		}
		return req;
	clean:
		if (hread!=NULL)
		{
			CloseHandle(hread);
		}
		if (hwrite != NULL)
		{
			CloseHandle(hwrite);
		}
		return "false";
	}
};
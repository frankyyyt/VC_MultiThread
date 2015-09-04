// Multi_Thead.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int index = 0;
int ticks = 200;
HANDLE hMutex;
DWORD WINAPI fun1Proc(LPVOID lpParameter)
{
	/*Sleep(3000);
	cout << "输出传递的参数" << endl;
	string * pstr = static_cast<string*>(lpParameter);
	cout << *pstr << endl;*/
	while (true)
	{
		WaitForSingleObject(hMutex,INFINITE);
		if (ticks>0)
		{
			//Sleep(1);
			cout << "thread1 sell tickets: " << ticks-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	
	
	return 0;
}

DWORD WINAPI funProc(LPVOID lpParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex,0);
		if (ticks>0)
		{
			//Sleep(1);
			cout << "thread2 sell tickets: " << ticks-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThtread1;
	HANDLE hThread2;
	hMutex = CreateMutex(NULL,false,NULL);
	string name("test sub thread");
	hThtread1 = CreateThread(NULL, 0, fun1Proc, &name, 0, NULL);
	hThread2 = CreateThread(NULL,0,funProc,NULL,0,NULL);
	CloseHandle(hThtread1);
	CloseHandle(hThread2);
	/*while (index++<200)
	{
		cout << index << ": main thread is runing" << endl;
	}*/
	Sleep(2500);
	
	/*int a;
	cin >> a;*/
	
	return 0;
}


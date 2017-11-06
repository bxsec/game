#include <stdio.h>
#include <Windows.h>

#include "Inject.h"

//获取游戏进程的句柄
//向指定进程写入我们的代码
DWORD WINAPI ThreadProc_Msg(
	LPVOID lpParameter
)
{
	MessageBox(0, "内容", "标题", (DWORD)lpParameter);
	return 1;
}
int main()
{
	//远程调用MessageBox   传入多个参数  需要分配内存，将代码注入进去
	

	HANDLE hp = GetGameHprocess();
	//1. 线程函数在本进程内，创建远程进程时，报错
	//CreateRemoteThread(hp, 0, 0, ThreadProc_Msg, (PVOID)MB_OK, 0, 0);


	/***************************************************/
	//1.在游戏空间分配内存空间，以写入代码
	//2.在游戏空间分配空间，以写入参数
	LPVOID pCall = VirtualAllocEx(hp, NULL, 0x6000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD byWriteSize = 0;
	BOOL bIsWriteCall = WriteProcessMemory(hp, pCall, ThreadProc_Msg, 0x6000, &byWriteSize);
	

	return 0;
}


int main_1()
{
	
	printf("远程代码注入\n");
	printf("游戏进程句柄=%08X\n", GetGameHprocess());

	/*DWORD* pGameAddress = (DWORD*)VirtualAllocEx(
		GetGameHprocess(),
		NULL,
		4096,
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
	);*/

	//printf("分配的内存地址=%08X\n", pGameAddress);


	/*DWORD parg[10] = { 0 };
	CreateRemoteThread(
		GetGameHprocess(),
		0,
		0,
		(LPTHREAD_START_ROUTINE)pGameAddress,
		parg,
		0,
		0
	);*/

	DWORD dwCall = 0x006c72d0;
	DWORD parg[10] = { 0 };
	CreateRemoteThread(
		GetGameHprocess(),
		0,
		0,
		(LPTHREAD_START_ROUTINE)dwCall,
		(PVOID)0x80005790,
		0,
		0
	);

	/*VirtualFreeEx(GetGameHprocess(),
		pGameAddress,
		4096,
		MEM_DECOMMIT);*/
	
	getchar();
	return 0;
}

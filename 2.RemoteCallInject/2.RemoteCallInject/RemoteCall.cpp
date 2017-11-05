#include <stdio.h>
#include <Windows.h>

#include "Inject.h"

//获取游戏进程的句柄
//向指定进程写入我们的代码


int main()
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

#include <stdio.h>
#include <Windows.h>

#include "Inject.h"

//��ȡ��Ϸ���̵ľ��
//��ָ������д�����ǵĴ���


int main()
{
	
	printf("Զ�̴���ע��\n");
	printf("��Ϸ���̾��=%08X\n", GetGameHprocess());

	/*DWORD* pGameAddress = (DWORD*)VirtualAllocEx(
		GetGameHprocess(),
		NULL,
		4096,
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
	);*/

	//printf("������ڴ��ַ=%08X\n", pGameAddress);


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

#include <stdio.h>
#include <Windows.h>

#include "Inject.h"

//��ȡ��Ϸ���̵ľ��
//��ָ������д�����ǵĴ���
DWORD WINAPI ThreadProc_Msg(
	LPVOID lpParameter
)
{
	MessageBox(0, "����", "����", (DWORD)lpParameter);
	return 1;
}
int main()
{
	//Զ�̵���MessageBox   ����������  ��Ҫ�����ڴ棬������ע���ȥ
	

	HANDLE hp = GetGameHprocess();
	//1. �̺߳����ڱ������ڣ�����Զ�̽���ʱ������
	//CreateRemoteThread(hp, 0, 0, ThreadProc_Msg, (PVOID)MB_OK, 0, 0);


	/***************************************************/
	//1.����Ϸ�ռ�����ڴ�ռ䣬��д�����
	//2.����Ϸ�ռ����ռ䣬��д�����
	LPVOID pCall = VirtualAllocEx(hp, NULL, 0x6000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD byWriteSize = 0;
	BOOL bIsWriteCall = WriteProcessMemory(hp, pCall, ThreadProc_Msg, 0x6000, &byWriteSize);
	

	return 0;
}


int main_1()
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

#include <stdio.h>
#include <Windows.h>

#include "Inject.h"



typedef struct _parglist {
	HWND m_hHwnd;
	char m_strCaption[100];
	char m_strText[100];
	UINT m_uType;
	DWORD m_dwCall;
} parglist;
//��ȡ��Ϸ���̵ľ��
//��ָ������д�����ǵĴ���
DWORD WINAPI ThreadProc_Msg(
	LPVOID lpParameter
)
{
	//MessageBox(0, "����", "����", (UINT)lpParameter);

	parglist* parglist1 = (parglist*)lpParameter;
	UINT utype = parglist1->m_uType;
	char *pText = parglist1->m_strText;
	char *pCaption = parglist1->m_strCaption;
	HWND hHwnd = parglist1->m_hHwnd;

	DWORD dwCall = parglist1->m_dwCall;

	_asm
	{
		push utype
		push pText
		push pCaption
		push hHwnd

		call dwCall
	}
	

	return 1;
}

void InjectRemoteMessageBox(TCHAR* szCaption, TCHAR* szText, UINT uType,DWORD dwCall)
{
	//Զ�̵���MessageBox   ����������  ��Ҫ�����ڴ棬������ע���ȥ


	HANDLE hp = GetGameHprocess();
	//1. �̺߳����ڱ������ڣ�����Զ�̽���ʱ������
	//CreateRemoteThread(hp, 0, 0, ThreadProc_Msg, (PVOID)MB_OK, 0, 0);


	/***************************************************/
	//1.����Ϸ�ռ�����ڴ�ռ䣬��д�����
	//2.����Ϸ�ռ����ռ䣬��д�����
	LPVOID pCall = VirtualAllocEx(hp, NULL, 0x100, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	SIZE_T byWriteSize = 0;

	

	BOOL bIsWriteCall = WriteProcessMemory(hp, pCall, &ThreadProc_Msg, 0x100, &byWriteSize);

	parglist arglist;
	arglist.m_hHwnd = NULL;
	strcpy_s(arglist.m_strCaption, szCaption);
	strcpy_s(arglist.m_strText, szText);
	arglist.m_uType = uType;
	arglist.m_dwCall = dwCall;
	parglist* pArg = (parglist*)VirtualAllocEx(hp, NULL, sizeof(parglist), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	bIsWriteCall = WriteProcessMemory(hp, pArg, &arglist, sizeof(parglist), &byWriteSize);

	HANDLE hRemoteThread = CreateRemoteThread(hp, 0, 0, (LPTHREAD_START_ROUTINE)pCall, pArg, 0, 0);

	WaitForSingleObject(hRemoteThread, INFINITE);

	BOOL bIsFreeCall = VirtualFreeEx(hp, pCall, 0x100, MEM_DECOMMIT);
	BOOL bIsFreeArg = VirtualFreeEx(hp, pArg, sizeof(parglist), MEM_DECOMMIT);

	CloseHandle(hRemoteThread);
	CloseHandle(hp);
}

int main()
{
	DWORD dwCall = (DWORD)&MessageBoxA;
	InjectRemoteMessageBox("Hello", "World", MB_OK, dwCall);
	getchar();
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

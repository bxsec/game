// 1.ReadInfo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include "ReadInfo.h"


int main()
{
	//1. ��ȡ��Ϸ���ھ��
	HWND hGame = FindWindow("XYElementClient Window", "�ڴ�����");

	//2. ͨ�����ھ����ȡ����PID
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hGame, &dwPid);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);


	//��Ѫ��
	DWORD dwBaseAddress = 0x0D0DF1C;
	//DWORD dw1Address = ((*((DWORD*)dwBaseAddress)) + 0x1C);
	//DWORD dw2Address = ((*((DWORD*)dw1Address)) + 0x28);
	//DWORD dw3Address = ((*((DWORD*)dw2Address)) + 0x288);

	DWORD dwpb = 0x1F7F0F6C;
	DWORD dwHp;
	DWORD dwSize;
	
	DWORD dwArr[] = { 0x0D0DF1C, 0x1C, 0x28, 0x288 };
	CReadInfo reader("XYElementClient Window", "�ڴ�����");
	DWORD hp = reader.read_i4(dwArr, 4);
	
	DWORD dwXArr[] = { 0x0D0DF1C, 0x1C, 0x28, 0x3C };
	float x = reader.read_f4(dwXArr, 4);

	DWORD dwYArr[] = { 0x0D0DF1C, 0x1C, 0x28, 0x44 };
	float y = reader.read_f4(dwYArr, 4);

	DWORD dwZArr[] = { 0x0D0DF1C, 0x1C, 0x28, 0x40 };
	float z = reader.read_f4(dwZArr, 4);

	//ReadProcessMemory(hProcess, (LPDWORD)dwBaseAddress, &dwBaseAddress, 4, &dwSize);
	//ReadProcessMemory(hProcess, (LPDWORD)(dwBaseAddress+0x1C), &dwBaseAddress, 4, &dwSize);
	//ReadProcessMemory(hProcess, (LPDWORD)(dwBaseAddress+0x28), &dwBaseAddress, 4, &dwSize);
	//ReadProcessMemory(hProcess, (LPDWORD)(dwBaseAddress+0x288), &dwHp, 4, &dwSize);

	

    return 0;
}


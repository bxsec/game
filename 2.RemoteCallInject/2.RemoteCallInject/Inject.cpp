#pragma once
#include <stdio.h>
#include <Windows.h>
#include "Inject.h"
//hp���̾��
//dwBase Ҫ��ȡ���ڴ��ַ
DWORD  _R4(HANDLE hp, DWORD dwBase)
{
	DWORD	dwForReadSize = 0;
	DWORD	dwBuf4 = 0;
	ReadProcessMemory(hp,
		(LPDWORD)dwBase,
		&dwBuf4,
		4,
		&dwForReadSize);

	return dwBuf4;
}

//ȡ����Ϸ���̾��
HANDLE GetGameHprocess()
{
	static HANDLE hp = 0;
	if (hp)
	{
		return hp;
	}
	//������Ϸ���ھ��
	HWND hGame = NULL;
	hGame = FindWindow("XYElementClient Window", "�ڴ�����");
	if (hGame)
	{
		printf("�ɹ��ҵ���� hGame=%08X\n", hGame);
	}
	else
	{
		printf("������Ϸδ�����������Ϸ����...");
		return NULL;
	}
	//��ȡ����ID GetWindowThreadProcessId
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hGame, &dwPid);

	hp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (hp)
	{
		printf("�򿪽��̳ɹ�\n");
		return hp;
	}
	else
	{
		printf("�򿪽���ʧ��\n");
		return NULL;
	}
}

DWORD R4(DWORD dwBase)
{
	return _R4(GetGameHprocess(), dwBase);
}
float R4F(DWORD dwBase)
{
	DWORD dwRet = R4(dwBase);
	return *(float*)&dwRet;
}
float _R4F(DWORD dwBase)
{
	HANDLE hp = GetGameHprocess();
	DWORD dwForReadSize = 0;
	float dwBuf4 = 0;
	ReadProcessMemory(hp,
		(LPDWORD)dwBase,
		&dwBuf4,
		4,
		&dwForReadSize);
	return dwBuf4;
}

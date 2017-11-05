#pragma once
#include <stdio.h>
#include <Windows.h>
#include "Inject.h"
//hp进程句柄
//dwBase 要读取的内存地址
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

//取得游戏进程句柄
HANDLE GetGameHprocess()
{
	static HANDLE hp = 0;
	if (hp)
	{
		return hp;
	}
	//查找游戏窗口句柄
	HWND hGame = NULL;
	hGame = FindWindow("XYElementClient Window", "口袋西游");
	if (hGame)
	{
		printf("成功找到句柄 hGame=%08X\n", hGame);
	}
	else
	{
		printf("可能游戏未开启，请打开游戏再试...");
		return NULL;
	}
	//获取进程ID GetWindowThreadProcessId
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hGame, &dwPid);

	hp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (hp)
	{
		printf("打开进程成功\n");
		return hp;
	}
	else
	{
		printf("打开进程失败\n");
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

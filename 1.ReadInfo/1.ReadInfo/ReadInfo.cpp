#include "stdafx.h"
#include "ReadInfo.h"

CReadInfo::CReadInfo()
{
	m_hGame = NULL;
	m_dwPid = 0;
	m_hProcess = NULL;
}

CReadInfo::CReadInfo(TCHAR *szClassName, TCHAR* szWindowName)
{
	//1. 获取游戏窗口句柄
	m_hGame = FindWindow(szClassName, szWindowName);

	//2. 通过窗口句柄获取进程PID
	
	GetWindowThreadProcessId(m_hGame, &m_dwPid);

	m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwPid);
}

DWORD CReadInfo::InitReader(TCHAR *szClassName, TCHAR* szWindowName)
{
	//1. 获取游戏窗口句柄
	m_hGame = FindWindow(szClassName, szWindowName);

	//2. 通过窗口句柄获取进程PID

	GetWindowThreadProcessId(m_hGame, &m_dwPid);

	m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwPid);
	return 0;
}

DWORD  CReadInfo::read_i4(DWORD addArr[], int len, int iReadSize)
{
	if (len == 0)
		return -1;
	DWORD dwBaseAddress = addArr[0];
	DWORD dwSize;

	ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &dwBaseAddress, 4, &dwSize);
	for (int i = 1; i < len - 1; i++)
	{
		
		dwBaseAddress += addArr[i];
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &dwBaseAddress, 4, &dwSize);
	}
	dwBaseAddress += addArr[len - 1];

	switch (iReadSize)
	{
	case 1:
	{
		BYTE byte;
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &byte, iReadSize, &dwSize);
		return byte;
	}
		break;
	case 2:
	{
		short s;
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &s, iReadSize, &dwSize);
		return s;
	}
		break;
	case 4:
	{
		DWORD dwData;
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &dwData, iReadSize, &dwSize);
		return dwData;
	}
		break;

	default:
		return -1;
	}
	


}

float  CReadInfo::read_f4(DWORD addArr[], int len, int iReadSize)
{
	if (len == 0)
		return -1;
	DWORD dwBaseAddress = addArr[0];
	DWORD dwSize;

	ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &dwBaseAddress, 4, &dwSize);
	for (int i = 1; i < len - 1; i++)
	{

		dwBaseAddress += addArr[i];
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &dwBaseAddress, 4, &dwSize);
	}
	dwBaseAddress += addArr[len - 1];

	switch (iReadSize)
	{
	case 1:
	{
		BYTE byte;
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &byte, iReadSize, &dwSize);
		return byte;
	}
	break;
	case 2:
	{
		short s;
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &s, iReadSize, &dwSize);
		return s;
	}
	break;
	case 4:
	{
		float dwData;
		ReadProcessMemory(m_hProcess, (LPDWORD)dwBaseAddress, &dwData, iReadSize, &dwSize);
		return dwData;
	}
	break;

	default:
		return -1;
	}



}



CReadInfo::~CReadInfo()
{
}

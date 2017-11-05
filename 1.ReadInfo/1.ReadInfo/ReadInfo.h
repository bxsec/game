#pragma once
#include <Windows.h>
class CReadInfo
{
private:
	HWND m_hGame;
	DWORD m_dwPid;
	HANDLE m_hProcess;
public:
	CReadInfo();
	CReadInfo(TCHAR *szClassName, TCHAR* szWindowName);

	DWORD InitReader(TCHAR *szClassName, TCHAR* szWindowName);
	DWORD  read_i4(DWORD addArr[], int len, int iReadSize = 4);
	float  read_f4(DWORD addArr[], int len, int iReadSize = 4);
	~CReadInfo();
};


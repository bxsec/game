#include "stdafx.h"
#include "EnumgWindow.h"

EnumgWindow::EnumgWindow()
{

}
EnumgWindow::~EnumgWindow()
{

}

BOOL CALLBACK EnumProc(
	HWND hwnd,
	LPARAM lParam
)
{
	TCHAR szCaption[MAX_PATH] = { 0 };
	TCHAR szClassName[MAX_PATH] = { 0 };
	HWND* phlst = (HWND*)lParam;
	GetWindowText(hwnd, szCaption, MAX_PATH);
	GetClassName(hwnd, szClassName, MAX_PATH);
	//TRACE("窗口句柄=%08X,类名=%s,窗口名=%s\n", hwnd, szCaption, szClassName);
	CString str;
	if (lstrlen(szCaption) && (lstrcmp(szClassName,TEXT("ANNCLIENT"))) == 0)
	{
		for (int i = 0; i < 100; i++)
		{
			if (phlst[i] == NULL)
			{
				phlst[i] = hwnd;
			}
		}
		str.Format(TEXT("窗口句柄=%08X,类名=%s,窗口名=%s\n"), hwnd, szCaption, szClassName);
		OutputDebugString(str);
	}

	//返回TRUE，则一直遍历，直到所有窗口遍历完成
	//返回FALSE 则终止遍历
	return TRUE;
}

void EnumGameWnd()
{
	HWND hwndArr[100] = { 0 };
	EnumWindows(EnumProc, (LPARAM)hwndArr);
}
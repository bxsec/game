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
	//TRACE("���ھ��=%08X,����=%s,������=%s\n", hwnd, szCaption, szClassName);
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
		str.Format(TEXT("���ھ��=%08X,����=%s,������=%s\n"), hwnd, szCaption, szClassName);
		OutputDebugString(str);
	}

	//����TRUE����һֱ������ֱ�����д��ڱ������
	//����FALSE ����ֹ����
	return TRUE;
}

void EnumGameWnd()
{
	HWND hwndArr[100] = { 0 };
	EnumWindows(EnumProc, (LPARAM)hwndArr);
}
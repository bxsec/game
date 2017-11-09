#pragma once

class EnumgWindow
{
public:
	EnumgWindow();
	~EnumgWindow();
};

BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam);

void EnumGameWnd();

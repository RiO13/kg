#include <windows.h>              // ������������ ����� ��� Windows
#include "Framework.h"

int WINAPI WinMain(HINSTANCE  hInstance,        // ���������� ����������
	HINSTANCE  hPrevInstance,        // ���������� ������������� ����������
	LPSTR    lpCmdLine,        // ��������� ��������� ������
	int    nCmdShow)        // ��������� ����������� ����
{
	MSG  msg;              // ��������� ��� �������� ��������� Windows
	BOOL  done = false;            // ���������� ���������� ��� ������ �� �����
	// ���������� ������������, ����� ����� ������ �� ������������
	bool full = true;
	if (MessageBox(NULL, "������ �� �� ��������� ���������� � ������������� ������?", "��������� � ������������� ������?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		full = false;          // ������� �����
	}
	bool err = false;
	// ������� ���� OpenGL ����
	CFramework framework(L"NeHe OpenGL ����", 1024, 768, 32, full, err);
	if (err)
	{
		return 0;              // �����, ���� ���� �� ����� ���� �������
	}
	framework.EnterMsgLoop();
	return 0;
}

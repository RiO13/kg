#pragma once
#include "Scene.h"
#include <gl\gl.h>                // ������������ ����� ��� ���������� OpenGL32
#include <gl\glu.h>              // ������������ ����� ��� ���������� GLu32
#include "glaux.h"              // ������������ ����� ��� ���������� GLaux
class CFramework
{
public:
	CFramework(LPCWSTR title, int width, int height, int bits, bool fullscreenflag, bool & error);
	~CFramework();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	static int InitGL(GLvoid);
	static int DrawGLScene(GLvoid);
	int CFramework::EnterMsgLoop();
	void mainLoop();
	void display();
private:
	bool static m_active;
	bool static m_keys[256];
	HGLRC m_hRC;              // ���������� �������� ����������
	HDC m_hDC;              // ��������� �������� ���������� GDI
	HWND m_hWnd;              // ����� ����� �������� ���������� ����
	HINSTANCE m_hInstance;              // ����� ����� �������� ���������� ����������
	bool  m_fullscreen;

	CScene static scene;
	GLuint static m_textures[10];
};


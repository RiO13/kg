#pragma once
#include "Scene.h"
#include <gl\gl.h>                // Заголовочные файлы для библиотеки OpenGL32
#include <gl\glu.h>              // Заголовочные файлы для библиотеки GLu32
#include "glaux.h"              // Заголовочные файлы для библиотеки GLaux
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
	HGLRC m_hRC;              // Постоянный контекст рендеринга
	HDC m_hDC;              // Приватный контекст устройства GDI
	HWND m_hWnd;              // Здесь будет хранится дескриптор окна
	HINSTANCE m_hInstance;              // Здесь будет хранится дескриптор приложения
	bool  m_fullscreen;

	CScene static scene;
	GLuint static m_textures[10];
};


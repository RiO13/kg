#include "Framework.h"

bool CFramework::m_active = false;
bool CFramework::m_keys[256];
CScene CFramework::scene;
GLuint CFramework::m_textures[15];
CFramework::CFramework(LPCWSTR title, int width, int height, int bits, bool fullscreenflag, bool & error)
{
	GLuint    PixelFormat;              // ������ ��������� ����� ������
	WNDCLASS  wc;                // ��������� ������ ����
	DWORD    dwExStyle;              // ����������� ����� ����

	DWORD    dwStyle;              // ������� ����� ����
	RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values

	WindowRect.left = (long)0;              // ���������� ����� ������������ � 0
	WindowRect.right = (long)width;              // ���������� ������ ������������ � Width
	WindowRect.top = (long)0;                // ���������� ������� ������������ � 0
	WindowRect.bottom = (long)height;              // ���������� ������ ������������ � Height
	helper::m_width = width;
	helper::m_height = height;
	m_fullscreen = fullscreenflag;              // ������������� �������� ���������� ���������� fullscreen
	m_hInstance = GetModuleHandle(NULL);        // ������� ���������� ������ ����������

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // ���������� ��� ����������� � ������ ������� DC
	wc.lpfnWndProc = (WNDPROC)WndProc;          // ��������� ��������� ���������
	wc.cbClsExtra = 0;              // ��� �������������� ���������� ��� ����
	wc.cbWndExtra = 0;              // ��� �������������� ���������� ��� ����
	wc.hInstance = m_hInstance;            // ������������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // ��������� ������ �� ���������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // ��������� ��������� �����
	wc.hbrBackground = NULL;              // ��� �� ��������� ��� GL
	wc.lpszMenuName = NULL;              // ���� � ���� �� �����
	wc.lpszClassName = "OpenGL";            // ������������� ��� ������
	if (!RegisterClass(&wc))              // �������� ���������������� ����� ����
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (m_fullscreen)                // ������������� �����?
	{
		DEVMODE dmScreenSettings;            // ����� ����������
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // ������� ��� �������� ���������
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // ������ ��������� Devmode
		dmScreenSettings.dmPelsWidth = width;        // ������ ������
		dmScreenSettings.dmPelsHeight = height;        // ������ ������
		dmScreenSettings.dmBitsPerPel = bits;        // ������� �����
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// ����� �������
		// �������� ���������� ��������� ����� � �������� ���������.  ����������: CDS_FULLSCREEN ������� ������ ����������.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// ���� ������������ � ������������� ����� ����������, ����� ���������� ��� ��������: ������� ����� ��� �����.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				m_fullscreen = false;          // ����� �������� ������ (fullscreen = false)
			}
			else
			{
				// ������������� ����, ���������� ������������ � �������� ����.
				error = true;
			}
		}
	}
	if (m_fullscreen)                  // �� �������� � ������������� ������?
	{
		dwExStyle = WS_EX_APPWINDOW;          // ����������� ����� ����
		dwStyle = WS_POPUP;            // ������� ����� ����
		ShowCursor(false);              // ������ ��������� �����
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // ����������� ����� ����
		dwStyle = WS_OVERLAPPEDWINDOW;        // ������� ����� ����
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // ��������� ���� ���������� �������
	if (!(m_hWnd = CreateWindowEx(dwExStyle,          // ����������� ����� ��� ����

		"OpenGL",          // ��� ������

		"title",            // ��������� ����
		WS_CLIPSIBLINGS |        // ��������� ����� ��� ����
		WS_CLIPCHILDREN |        // ��������� ����� ��� ����
		dwStyle,          // ���������� ����� ��� ����
		0, 0,            // ������� ����
		WindowRect.right - WindowRect.left,    // ���������� ���������� ������
		WindowRect.bottom - WindowRect.top,    // ���������� ���������� ������
		NULL,            // ��� �������������
		NULL,            // ��� ����
		m_hInstance,          // ���������� ����������
		NULL)))          // �� ������� ������ �� WM_CREATE (???)
	{
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	static  PIXELFORMATDESCRIPTOR pfd =            // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // ������ ����������� ������� ������� ��������
		1,                  // ����� ������
		PFD_DRAW_TO_WINDOW |              // ������ ��� ����
		PFD_SUPPORT_OPENGL |              // ������ ��� OpenGL
		PFD_DOUBLEBUFFER,              // ������ ��� �������� ������
		PFD_TYPE_RGBA,                // ��������� RGBA ������
		bits,                  // ���������� ��� ������� �����
		0, 0, 0, 0, 0, 0,              // ������������� �������� �����
		0,                  // ��� ������ ������������
		0,                  // ��������� ��� ������������
		0,                  // ��� ������ ����������
		0, 0, 0, 0,                // ���� ���������� ������������
		32,                  // 32 ������ Z-����� (����� �������)
		0,                  // ��� ������ ���������
		0,                  // ��� ��������������� �������
		PFD_MAIN_PLANE,                // ������� ���� ���������
		0,                  // ���������������
		0, 0, 0                  // ����� ���� ������������
	};
	if (!(m_hDC = GetDC(m_hWnd)))              // ����� �� �� �������� �������� ����������?
	{
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!(PixelFormat = ChoosePixelFormat(m_hDC, &pfd)))        // ������ �� ���������� ������ �������?
	{
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!SetPixelFormat(m_hDC, PixelFormat, &pfd))          // �������� �� ���������� ������ �������?
	{
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!(m_hRC = wglCreateContext(m_hDC)))          // �������� �� ���������� �������� ����������?
	{
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!wglMakeCurrent(m_hDC,m_hRC))            // ����������� ������������ �������� ����������
	{
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	ShowWindow(m_hWnd, SW_SHOW);              // �������� ����
	SetForegroundWindow(m_hWnd);              // ������ ������� ���������
	SetFocus(m_hWnd);                // ���������� ����� ���������� �� ���� ����
	ReSizeGLScene(width, height);              // �������� ����������� ��� ������ OpenGL ������.
	if (!InitGL())                  // ������������� ������ ��� ���������� ����
	{
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
 
}
int CFramework::EnterMsgLoop()
{
	MSG  msg;              // ��������� ��� �������� ��������� Windows
	BOOL  done = false;
	DWORD   dwInputTimer = 0;
	static float lastTime = (float)timeGetTime();
	while (!done)                // ���� ������������, ���� done �� ����� true
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // ���� �� � ������� �����-������ ���������?
		{
			if (msg.message == WM_QUIT)        // �� ������� ��������� � ������?
			{
				done = true;          // ���� ���, done=true
			}
			else              // ���� ���, ������������ ���������
			{
				TranslateMessage(&msg);        // ��������� ���������
				DispatchMessage(&msg);        // �������� ���������
			}
		}
		else                // ���� ��� ���������
		{
			// ������������� �����.
			if (m_active)          // ������� �� ���������?
			{
				
				if (m_keys[VK_ESCAPE])        // ���� �� ������ ������� ESC?
				{
					done = true;      // ESC ������� �� �������� ���������� ���������
				}
				else            // �� ����� ��� ������, ������� �����.
				{
					if (timeGetTime() > dwInputTimer) {
						// Check for input
						dwInputTimer = timeGetTime() + 10;
					}

					float currTime = (float)timeGetTime();
					float timeDelta = (currTime - lastTime)*0.001f;
					DrawGLScene();        // ������ �����
					SwapBuffers(m_hDC);    // ������ ����� (������� �����������)
					if (m_keys[VK_UP])
					{
						scene.onEvent(EVENTS::PRESS_UP_BUTTON);
						m_keys[VK_UP] = false;
					}
					if (m_keys[VK_DOWN])
					{
						scene.onEvent(EVENTS::PRESS_DOWN_BUTTON);
						m_keys[VK_DOWN] = false;
					}
					if (m_keys[VK_LEFT])
					{
						scene.onEvent(EVENTS::PRESS_LEFT_BUTTON);
						m_keys[VK_LEFT] = false;
					}
					if (m_keys[VK_RIGHT])
					{
						scene.onEvent(EVENTS::PRESS_RIGHT_BUTTON);
						m_keys[VK_RIGHT] = false;
					}
					if (m_keys[VK_NUMPAD8])
					{
						scene.onEvent(EVENTS::PRESS_8NUMPAD);
						m_keys[VK_NUMPAD8] = false;
					}
					if (m_keys[VK_NUMPAD2])
					{
						scene.onEvent(EVENTS::PRESS_2NUMPAD);
						m_keys[VK_NUMPAD2] = false;
					}
					if (m_keys[VK_NUMPAD6])
					{
						scene.onEvent(EVENTS::PRESS_6NUMPAD);
						m_keys[VK_NUMPAD6] = false;
					}
					if (m_keys[VK_NUMPAD4])
					{
						scene.onEvent(EVENTS::PRESS_4NUMPAD);
						m_keys[VK_NUMPAD4] = false;
					}
					if (m_keys[VK_TAB])
					{
						scene.onEvent(EVENTS::PRESS_TAB);
						m_keys[VK_TAB] = false;
					}
					if (m_keys[VK_ADD])
					{
						scene.onEvent(EVENTS::PRESS_ADD);
						m_keys[VK_ADD] = false;
					}
					if (m_keys[VK_SUBTRACT])
					{
						scene.onEvent(EVENTS::PRESS_SUB);
						m_keys[VK_SUBTRACT] = false;
					}

					if (m_keys[VK_PRIOR])
					{
						scene.onEvent(EVENTS::PRESS_PRIOR);
						m_keys[VK_PRIOR] = false;
					}

					if (m_keys[VK_NEXT])
					{
						scene.onEvent(EVENTS::PRESS_NEXT);
						m_keys[VK_NEXT] = false;
					}
					if (m_keys[VK_RETURN])
					{
						scene.onEvent(EVENTS::PRESS_ENTER);
						m_keys[VK_RETURN] = false;
					}
					if (m_keys[' '])
					{
						scene.onEvent(EVENTS::PRESS_SPACE);
						m_keys[' '] = false;

					}
				}
			}
		}
	}
	return (msg.wParam);              // ������� �� ���������
}


CFramework::~CFramework()
{
	if (m_fullscreen)              // �� � ������������� ������?
	{
		ChangeDisplaySettings(NULL, 0);        // ���� ��, �� ������������� ������� � ������� �����
		ShowCursor(true);            // �������� ������ �����
	}
	if (m_hRC)                // ���������� �� �������� ����������?
	{
		if (!wglMakeCurrent(NULL, NULL))        // �������� �� ���������� RC � DC?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(m_hRC))        // �������� �� ������� RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		m_hRC = NULL;              // ���������� RC � NULL
	}
	if (m_hDC && !ReleaseDC(m_hWnd, m_hDC))          // �������� �� ���������� DC?
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hDC = NULL;                // ���������� DC � NULL
	}
	if (m_hWnd && !DestroyWindow(m_hWnd))            // �������� �� ���������� ����?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hWnd = NULL;                // ���������� hWnd � NULL
	}
	if (!UnregisterClass("OpenGL", m_hInstance))        // �������� �� ����������������� �����
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hInstance = NULL;                // ���������� hInstance � NULL
	}
}

 


int CFramework::InitGL(GLvoid)                // ��� ��������� ������� OpenGL ���������� �����
{
	// �������� �������
/*	if (!scene.LoadGLTextures())
	{
		return FALSE;
	}*/
	
	glShadeModel(GL_SMOOTH);    // ��������� ������� ���������

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // ������ ���

	glClearDepth(1.0f);         // ��������� ������ �������

	glDisable(GL_DEPTH_TEST);   // ���������� ����� �������

//	glEnable(GL_BLEND);         // ��������� ����������
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE); // ��� ����������
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ���������� ���������� �����������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);  // ���������� �������� ��������
	glEnable(GL_TEXTURE_2D);                 // ���������� ��������� ��������
	helper::fillTextures();
	glGenTextures(15, CFramework::m_textures);

	if (!scene.init())
	{
		return false;
	}
	// ������������� ������� ����������
	return true;                // ������������� ������ �������
}

int CFramework::DrawGLScene(GLvoid)                // ����� ����� ����������� ��� ����������
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������ � ������ �������

	glLoadIdentity(); // ����� ������� ��������� ������
	scene.Draw();

	return true;                // ���������� ������ �������
}

LRESULT CALLBACK CFramework::WndProc(HWND  hWnd,            // ���������� ������� ����
	UINT  uMsg,            // ��������� ��� ����� ����
	WPARAM  wParam,            // �������������� ����������
	LPARAM  lParam)            // �������������� ����������
{
	switch (uMsg)                // �������� ��������� ��� ����
	{
	case WM_ACTIVATE:            // �������� ��������� ���������� ����
	{
									 if (!HIWORD(wParam))          // ��������� ��������� �����������
									 {
										 m_active = true;          // ��������� �������
									 }
									 else
									 {
										 m_active = false;          // ��������� ������ �� �������
									 }
									 return 0;            // ������������ � ���� ��������� ���������
	}
	case WM_SYSCOMMAND:            // ������������� ��������� �������
	{
									   switch (wParam)            // ������������� ��������� �����
									   {
									   case SC_SCREENSAVE:        // �������� �� ���������� �����������?
									   case SC_MONITORPOWER:        // �������� �� ������� ������� � ����� ���������� �������?
										   return 0;          // ������������� ���
									   }
									   break;              // �����
	}
	case WM_CLOSE:              // �� �������� ��������� � ��������?
	{
									PostQuitMessage(0);          // ��������� ��������� � ������
									return 0;            // ��������� �����
	}
	case WM_KEYDOWN:            // ���� �� ������ ������?
	{
									m_keys[wParam] = true;          // ���� ���, �� ����������� ���� ������ true
									return 0;            // ������������
	}
	case WM_KEYUP:              // ���� �� �������� �������?
	{
									m_keys[wParam] = false;          //  ���� ���, �� ����������� ���� ������ false
									return 0;            // ������������
	}
	case WM_SIZE:              // �������� ������� OpenGL ����
	{
								   ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // ������� �����=Width, ������� �����=Height
								   return 0;            // ������������
	}
	}
	if (!scene.isAlive){
		PostQuitMessage(0);
		return 0;
	}
	// ���������� ��� �������������� ��������� DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GLvoid CFramework::ReSizeGLScene(GLsizei width, GLsizei height)        // �������� ������ � ���������������� ���� GL

{
	if (height == 0)              // �������������� ������� �� ����
	{
		height = 1;
	}
	glViewport(0, 0, width, height);          // ����� ������� ������� ������ 
	glMatrixMode(GL_PROJECTION);            // ����� ������� ��������

	glLoadIdentity();              // ����� ������� ��������

	// ���������� ����������� �������������� �������� ��� ����
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);            // ����� ������� ���� ������
	glLoadIdentity();              // ����� ������� ���� ������
}


 
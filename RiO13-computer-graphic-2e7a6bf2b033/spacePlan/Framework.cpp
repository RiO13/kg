#include "Framework.h"

bool CFramework::m_active = false;
bool CFramework::m_keys[256];
CScene CFramework::scene;
GLuint CFramework::m_textures[15];
CFramework::CFramework(LPCWSTR title, int width, int height, int bits, bool fullscreenflag, bool & error)
{
	GLuint    PixelFormat;              // Хранит результат после поиска
	WNDCLASS  wc;                // Структура класса окна
	DWORD    dwExStyle;              // Расширенный стиль окна

	DWORD    dwStyle;              // Обычный стиль окна
	RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values

	WindowRect.left = (long)0;              // Установить левую составляющую в 0
	WindowRect.right = (long)width;              // Установить правую составляющую в Width
	WindowRect.top = (long)0;                // Установить верхнюю составляющую в 0
	WindowRect.bottom = (long)height;              // Установить нижнюю составляющую в Height
	helper::m_width = width;
	helper::m_height = height;
	m_fullscreen = fullscreenflag;              // Устанавливаем значение глобальной переменной fullscreen
	m_hInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
	wc.lpfnWndProc = (WNDPROC)WndProc;          // Процедура обработки сообщений
	wc.cbClsExtra = 0;              // Нет дополнительной информации для окна
	wc.cbWndExtra = 0;              // Нет дополнительной информации для окна
	wc.hInstance = m_hInstance;            // Устанавливаем дескриптор
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // Загружаем указатель мышки
	wc.hbrBackground = NULL;              // Фон не требуется для GL
	wc.lpszMenuName = NULL;              // Меню в окне не будет
	wc.lpszClassName = "OpenGL";            // Устанавливаем имя классу
	if (!RegisterClass(&wc))              // Пытаемся зарегистрировать класс окна
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (m_fullscreen)                // Полноэкранный режим?
	{
		DEVMODE dmScreenSettings;            // Режим устройства
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // Очистка для хранения установок
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Размер структуры Devmode
		dmScreenSettings.dmPelsWidth = width;        // Ширина экрана
		dmScreenSettings.dmPelsHeight = height;        // Высота экрана
		dmScreenSettings.dmBitsPerPel = bits;        // Глубина цвета
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя
		// Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				m_fullscreen = false;          // Выбор оконного режима (fullscreen = false)
			}
			else
			{
				// Выскакивающее окно, сообщающее пользователю о закрытие окна.
				error = true;
			}
		}
	}
	if (m_fullscreen)                  // Мы остались в полноэкранном режиме?
	{
		dwExStyle = WS_EX_APPWINDOW;          // Расширенный стиль окна
		dwStyle = WS_POPUP;            // Обычный стиль окна
		ShowCursor(false);              // Скрыть указатель мышки
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // Расширенный стиль окна
		dwStyle = WS_OVERLAPPEDWINDOW;        // Обычный стиль окна
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры
	if (!(m_hWnd = CreateWindowEx(dwExStyle,          // Расширенный стиль для окна

		"OpenGL",          // Имя класса

		"title",            // Заголовок окна
		WS_CLIPSIBLINGS |        // Требуемый стиль для окна
		WS_CLIPCHILDREN |        // Требуемый стиль для окна
		dwStyle,          // Выбираемые стили для окна
		0, 0,            // Позиция окна
		WindowRect.right - WindowRect.left,    // Вычисление подходящей ширины
		WindowRect.bottom - WindowRect.top,    // Вычисление подходящей высоты
		NULL,            // Нет родительского
		NULL,            // Нет меню
		m_hInstance,          // Дескриптор приложения
		NULL)))          // Не передаём ничего до WM_CREATE (???)
	{
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	static  PIXELFORMATDESCRIPTOR pfd =            // pfd сообщает Windows каким будет вывод на экран каждого пикселя
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // Размер дескриптора данного формата пикселей
		1,                  // Номер версии
		PFD_DRAW_TO_WINDOW |              // Формат для Окна
		PFD_SUPPORT_OPENGL |              // Формат для OpenGL
		PFD_DOUBLEBUFFER,              // Формат для двойного буфера
		PFD_TYPE_RGBA,                // Требуется RGBA формат
		bits,                  // Выбирается бит глубины цвета
		0, 0, 0, 0, 0, 0,              // Игнорирование цветовых битов
		0,                  // Нет буфера прозрачности
		0,                  // Сдвиговый бит игнорируется
		0,                  // Нет буфера накопления
		0, 0, 0, 0,                // Биты накопления игнорируются
		32,                  // 32 битный Z-буфер (буфер глубины)
		0,                  // Нет буфера трафарета
		0,                  // Нет вспомогательных буферов
		PFD_MAIN_PLANE,                // Главный слой рисования
		0,                  // Зарезервировано
		0, 0, 0                  // Маски слоя игнорируются
	};
	if (!(m_hDC = GetDC(m_hWnd)))              // Можем ли мы получить Контекст Устройства?
	{
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!(PixelFormat = ChoosePixelFormat(m_hDC, &pfd)))        // Найден ли подходящий формат пикселя?
	{
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!SetPixelFormat(m_hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?
	{
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!(m_hRC = wglCreateContext(m_hDC)))          // Возможно ли установить Контекст Рендеринга?
	{
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	if (!wglMakeCurrent(m_hDC,m_hRC))            // Попробовать активировать Контекст Рендеринга
	{
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
	ShowWindow(m_hWnd, SW_SHOW);              // Показать окно
	SetForegroundWindow(m_hWnd);              // Слегка повысим приоритет
	SetFocus(m_hWnd);                // Установить фокус клавиатуры на наше окно
	ReSizeGLScene(width, height);              // Настроим перспективу для нашего OpenGL экрана.
	if (!InitGL())                  // Инициализация только что созданного окна
	{
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		error = true;
	}
 
}
int CFramework::EnterMsgLoop()
{
	MSG  msg;              // Структура для хранения сообщения Windows
	BOOL  done = false;
	DWORD   dwInputTimer = 0;
	static float lastTime = (float)timeGetTime();
	while (!done)                // Цикл продолжается, пока done не равно true
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // Есть ли в очереди какое-нибудь сообщение?
		{
			if (msg.message == WM_QUIT)        // Мы поучили сообщение о выходе?
			{
				done = true;          // Если так, done=true
			}
			else              // Если нет, обрабатывает сообщения
			{
				TranslateMessage(&msg);        // Переводим сообщение
				DispatchMessage(&msg);        // Отсылаем сообщение
			}
		}
		else                // Если нет сообщений
		{
			// Прорисовываем сцену.
			if (m_active)          // Активна ли программа?
			{
				
				if (m_keys[VK_ESCAPE])        // Было ли нажата клавиша ESC?
				{
					done = true;      // ESC говорит об останове выполнения программы
				}
				else            // Не время для выхода, обновим экран.
				{
					if (timeGetTime() > dwInputTimer) {
						// Check for input
						dwInputTimer = timeGetTime() + 10;
					}

					float currTime = (float)timeGetTime();
					float timeDelta = (currTime - lastTime)*0.001f;
					DrawGLScene();        // Рисуем сцену
					SwapBuffers(m_hDC);    // Меняем буфер (двойная буферизация)
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
	return (msg.wParam);              // Выходим из программы
}


CFramework::~CFramework()
{
	if (m_fullscreen)              // Мы в полноэкранном режиме?
	{
		ChangeDisplaySettings(NULL, 0);        // Если да, то переключаемся обратно в оконный режим
		ShowCursor(true);            // Показать курсор мышки
	}
	if (m_hRC)                // Существует ли Контекст Рендеринга?
	{
		if (!wglMakeCurrent(NULL, NULL))        // Возможно ли освободить RC и DC?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(m_hRC))        // Возможно ли удалить RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		m_hRC = NULL;              // Установить RC в NULL
	}
	if (m_hDC && !ReleaseDC(m_hWnd, m_hDC))          // Возможно ли уничтожить DC?
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hDC = NULL;                // Установить DC в NULL
	}
	if (m_hWnd && !DestroyWindow(m_hWnd))            // Возможно ли уничтожить окно?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hWnd = NULL;                // Установить hWnd в NULL
	}
	if (!UnregisterClass("OpenGL", m_hInstance))        // Возможно ли разрегистрировать класс
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		m_hInstance = NULL;                // Установить hInstance в NULL
	}
}

 


int CFramework::InitGL(GLvoid)                // Все установки касаемо OpenGL происходят здесь
{
	// Загрузка текстур
/*	if (!scene.LoadGLTextures())
	{
		return FALSE;
	}*/
	
	glShadeModel(GL_SMOOTH);    // Разрешить плавное затенение

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Черный фон

	glClearDepth(1.0f);         // Установка буфера глубины

	glDisable(GL_DEPTH_TEST);   // Запрещение теста глубины

//	glEnable(GL_BLEND);         // Разрешаем смешивание
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Тип смешивания
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Улучшенные вычисления перспективы
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);  // Улучшенные точечное смешение
	glEnable(GL_TEXTURE_2D);                 // Разрешение наложения текстуры
	helper::fillTextures();
	glGenTextures(15, CFramework::m_textures);

	if (!scene.init())
	{
		return false;
	}
	// Устанавливаем функцию смешивания
	return true;                // Инициализация прошла успешно
}

int CFramework::DrawGLScene(GLvoid)                // Здесь будет происходить вся прорисовка
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистка экрана и буфера глубины

	glLoadIdentity(); // Сброс матрицы просмотра модели
	scene.Draw();

	return true;                // Прорисовка прошла успешно
}

LRESULT CALLBACK CFramework::WndProc(HWND  hWnd,            // Дескриптор нужного окна
	UINT  uMsg,            // Сообщение для этого окна
	WPARAM  wParam,            // Дополнительная информация
	LPARAM  lParam)            // Дополнительная информация
{
	switch (uMsg)                // Проверка сообщения для окна
	{
	case WM_ACTIVATE:            // Проверка сообщения активности окна
	{
									 if (!HIWORD(wParam))          // Проверить состояние минимизации
									 {
										 m_active = true;          // Программа активна
									 }
									 else
									 {
										 m_active = false;          // Программа теперь не активна
									 }
									 return 0;            // Возвращаемся в цикл обработки сообщений
	}
	case WM_SYSCOMMAND:            // Перехватываем системную команду
	{
									   switch (wParam)            // Останавливаем системный вызов
									   {
									   case SC_SCREENSAVE:        // Пытается ли запустится скринсейвер?
									   case SC_MONITORPOWER:        // Пытается ли монитор перейти в режим сбережения энергии?
										   return 0;          // Предотвращаем это
									   }
									   break;              // Выход
	}
	case WM_CLOSE:              // Мы получили сообщение о закрытие?
	{
									PostQuitMessage(0);          // Отправить сообщение о выходе
									return 0;            // Вернуться назад
	}
	case WM_KEYDOWN:            // Была ли нажата кнопка?
	{
									m_keys[wParam] = true;          // Если так, мы присваиваем этой ячейке true
									return 0;            // Возвращаемся
	}
	case WM_KEYUP:              // Была ли отпущена клавиша?
	{
									m_keys[wParam] = false;          //  Если так, мы присваиваем этой ячейке false
									return 0;            // Возвращаемся
	}
	case WM_SIZE:              // Изменены размеры OpenGL окна
	{
								   ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // Младшее слово=Width, старшее слово=Height
								   return 0;            // Возвращаемся
	}
	}
	if (!scene.isAlive){
		PostQuitMessage(0);
		return 0;
	}
	// пересылаем все необработанные сообщения DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GLvoid CFramework::ReSizeGLScene(GLsizei width, GLsizei height)        // Изменить размер и инициализировать окно GL

{
	if (height == 0)              // Предотвращение деления на ноль
	{
		height = 1;
	}
	glViewport(0, 0, width, height);          // Сброс текущей области вывода 
	glMatrixMode(GL_PROJECTION);            // Выбор матрицы проекций

	glLoadIdentity();              // Сброс матрицы проекции

	// Вычисление соотношения геометрических размеров для окна
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);            // Выбор матрицы вида модели
	glLoadIdentity();              // Сброс матрицы вида модели
}


 
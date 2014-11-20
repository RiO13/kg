#include <windows.h>              // Заголовочные файлы для Windows
#include "Framework.h"

int WINAPI WinMain(HINSTANCE  hInstance,        // Дескриптор приложения
	HINSTANCE  hPrevInstance,        // Дескриптор родительского приложения
	LPSTR    lpCmdLine,        // Параметры командной строки
	int    nCmdShow)        // Состояние отображения окна
{
	MSG  msg;              // Структура для хранения сообщения Windows
	BOOL  done = false;            // Логическая переменная для выхода из цикла
	// Спрашивает пользователя, какой режим экрана он предпочитает
	bool full = true;
	if (MessageBox(NULL, "Хотите ли Вы запустить приложение в полноэкранном режиме?", "Запустить в полноэкранном режиме?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		full = false;          // Оконный режим
	}
	bool err = false;
	// Создать наше OpenGL окно
	CFramework framework(L"NeHe OpenGL окно", 1024, 768, 32, full, err);
	if (err)
	{
		return 0;              // Выйти, если окно не может быть создано
	}
	framework.EnterMsgLoop();
	return 0;
}

#pragma once
#pragma comment(lib, "opengl32.lib") //сообщаем линковщику, что мы будет использовать библиотеки opengl32, glu32. 
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ilut.lib")
#pragma comment(lib,"ilu.lib")

// Хидеры библиотеки DevIL
#include <ilu.h>
#include <il.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "glut.h"
#include "glaux.h"	
#include <vector>
#include <string>

// Создадим структуру TextureImage для хранения данных текстуры.
typedef struct TextureImage
{
	GLubyte *imageData;		// Данные текстуры
	GLuint	bpp;			// Байт на пиксел
	GLuint width, height;		// Высота и ширина
	GLuint texID;			// ID текстуры
}TextureImage;


// Класс текстур. Загрузка и высвобождение.
class CTexture{
public:

	CTexture();
	~CTexture();

	// Собственно, класс наш делает немного - в нём только 2 функции - 
	// загрузка и освобождение текстур =)
	void LoadTexture(ILenum FileType, char *filename, TextureImage *texture, int i);
	void FreeTexture(TextureImage *texture);
};

 
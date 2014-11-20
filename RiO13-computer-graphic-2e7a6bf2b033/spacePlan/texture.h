#pragma once
#pragma comment(lib, "opengl32.lib") //�������� ����������, ��� �� ����� ������������ ���������� opengl32, glu32. 
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ilut.lib")
#pragma comment(lib,"ilu.lib")

// ������ ���������� DevIL
#include <ilu.h>
#include <il.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "glut.h"
#include "glaux.h"	
#include <vector>
#include <string>

// �������� ��������� TextureImage ��� �������� ������ ��������.
typedef struct TextureImage
{
	GLubyte *imageData;		// ������ ��������
	GLuint	bpp;			// ���� �� ������
	GLuint width, height;		// ������ � ������
	GLuint texID;			// ID ��������
}TextureImage;


// ����� �������. �������� � �������������.
class CTexture{
public:

	CTexture();
	~CTexture();

	// ����������, ����� ��� ������ ������� - � �� ������ 2 ������� - 
	// �������� � ������������ ������� =)
	void LoadTexture(ILenum FileType, char *filename, TextureImage *texture, int i);
	void FreeTexture(TextureImage *texture);
};

 
#include "Fon.h"


CFon::CFon()
{
}


CFon::~CFon()
{
}


void CFon::Draw()
{
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
	glBegin(GL_QUADS);                      // ������ ���
	//glColor3f(0.0f, 1.0f, 0.0f);              // �����
	// �������� �����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-12, -12, 1.0f);	// ��� ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12, -12, 1.0f);	// ��� �����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12, 12, 1.0f);	// ���� �����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-12, 12, 1.0f);	// ���� ����
	glEnd();
}

void CFon::onEvent(EVENTS type)
{

}
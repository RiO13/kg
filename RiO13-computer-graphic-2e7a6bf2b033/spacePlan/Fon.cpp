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
	glBegin(GL_QUADS);                      // Рисуем куб
	//glColor3f(0.0f, 1.0f, 0.0f);              // Синий
	// Передняя грань
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-12, -12, 1.0f);	// Низ лево
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12, -12, 1.0f);	// Низ право
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12, 12, 1.0f);	// Верх право
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-12, 12, 1.0f);	// Верх лево
	glEnd();
}

void CFon::onEvent(EVENTS type)
{

}
#include "Rocket.h"


CRocket::CRocket()
{
	m_speedX = (rand() % 1000) / 100000.0;
	int factor1 = rand() % 2 == 1 ? 1 : -1;
	m_speedX = factor1 *m_speedX;
	m_speedY = (rand() % 1000) / 100000.0;
	int factor2 = rand() % 2 == 1 ? 1 : -1;
	m_speedY = factor2 *m_speedY;
	m_timer = 0;
}


CRocket::~CRocket()
{
}

void CRocket::Draw()
{
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -30.0f);
	glRotatef(0.0f, 1.0f, 1.0f, 1.0f);        // Вращение куба по X, Y & Z
	glBegin(GL_QUADS);                      // Рисуем куб
	//glColor3f(0.0f, 1.0f, 0.0f);              // Синий
	// Передняя грань
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f + m_x, -1.0f + m_y, 1.0f);	// Низ лево
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + m_x, -1.0f + m_y, 1.0f);	// Низ право
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + m_x, 1.0f + m_y, 1.0f);	// Верх право
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f + m_x, 1.0f + m_y, 1.0f);	// Верх лево

	glEnd();
	m_timer++;
	m_x += m_speedX;
	m_y += m_speedY;
	
	// Disable 2D rendering

}

GLfloat CRocket::getXCenter()const
{
	return m_x + (1.0 / 2);
}
GLfloat CRocket::getYCenter()const {
	return m_y + (1.0 / 2);
}

void CRocket::onEvent(EVENTS type)
{
}


GLfloat CRocket::getX()const
{
	return m_x;
}
GLfloat CRocket::getY()const
{
	return m_y;
}


GLuint CRocket::getTime()const
{
	return m_timer;
}
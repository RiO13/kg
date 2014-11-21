#include "Fon.h"


CFon::CFon()
{
	m_speed = 0.0f;
	m_xP = 12.0f;
	m_xM = -12.0f;
}


CFon::~CFon()
{
}


void CFon::Draw()
{
	if ((m_xP) > 19.0f)
		m_speed = -m_speed;
	if (m_xM < -19.0f)
		m_speed = -m_speed;
	m_xP += m_speed;
	m_xM += m_speed;
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
	glBegin(GL_QUADS);                      // Рисуем куб
	//glColor3f(0.0f, 1.0f, 0.0f);              // Синий
	// Передняя грань
	glTexCoord2f(0.0f, 0.0f); glVertex3f(m_xM, -12, 1.0f);	// Низ лево
	glTexCoord2f(1.0f, 0.0f); glVertex3f(m_xP, -12, 1.0f);	// Низ право
	glTexCoord2f(1.0f, 1.0f); glVertex3f(m_xP, 12, 1.0f);	// Верх право
	glTexCoord2f(0.0f, 1.0f); glVertex3f(m_xM, 12, 1.0f);	// Верх лево
	glEnd();
}

void CFon::onEvent(EVENTS type)
{

}


void CFon::setSpeed(GLfloat speed)
{
	m_speed = speed;
}

GLfloat CFon::getSpeed()const
{
	return m_speed;
}
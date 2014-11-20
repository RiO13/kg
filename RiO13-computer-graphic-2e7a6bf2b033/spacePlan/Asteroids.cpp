#include "Asteroids.h"


CAsteroids::CAsteroids()
{
	m_x = 1;
	m_y = 9;
	srand(helper::sault + 100);
	m_speedX = (rand() % 1000) / 500000.0;
	int factor1 = rand() % 2 == 1 ? 1 : -1;
	m_speedX = factor1 *m_speedX;
	m_speedY = (rand() % 1000) / 500000.0;
	int factor2 = rand() % 2 == 1 ? 1 : -1;
	m_speedY = factor2 *m_speedY;
	m_isLive = true;
}


CAsteroids::~CAsteroids()
{
}


void CAsteroids::Draw()
{
	if (CAsteroids::isAlive()){
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -25.0f);
		glRotatef(0.0f, 1.0f, 1.0f, 1.0f);        // Вращение куба по X, Y & Z
		glBegin(GL_QUADS);                      // Рисуем куб
		//glColor3f(0.0f, 1.0f, 0.0f);              // Синий
		// Передняя грань
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f + m_x, -1.0f + m_y, 1.0f);	// Низ лево
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + m_x, -1.0f + m_y, 1.0f);	// Низ право
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + m_x, 1.0f + m_y, 1.0f);	// Верх право
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f + m_x, 1.0f + m_y, 1.0f);	// Верх лево

		glEnd();

		m_x += m_speedX;
		m_y += m_speedY;
	}
	if ((m_x > 15 || m_x < -15) || (m_y > 15 || m_y < -15))
	{
		CAsteroids::kill();
	}
	// Disable 2D rendering
}

void CAsteroids::onEvent(EVENTS type)
{
}


void CAsteroids::kill() {
	m_isLive = false;
}
bool CAsteroids::isAlive()const {
	return m_isLive;
}
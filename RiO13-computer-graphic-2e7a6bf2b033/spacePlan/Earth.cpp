#include "Earth.h"


CEarth::CEarth()
{
	m_textureID = 0;
	m_radius = 3.5f;
	m_lighting = true;
	m_renderInWireFrame = false;
	m_precision = 32;
	m_spinX = 0.0f;
	m_spinY = 0.0f;
	cx = 0.0f;
	cy = 0.0f;
	cz = 0.0f;
}


CEarth::~CEarth()
{
}


void CEarth::Draw()
{	
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -30.0);     //  используется для рисования красный цвет  
	glRotatef(-m_spinY, 0.0f, 1.0f, 1.0f);
	glRotatef(70.0f, 0.5, 0.0, 0.0);     // Поворот по Y      
	glRotatef(2.0f, 0.2, 0.5, 0.0);     // поворот по Z      
	glRotatef(0.0f, 0.0, 0.0, 0.5);
	const float PI = 3.14159265358979f;
	const float TWOPI = 6.28318530717958f;
	const float PIDIV2 = 1.57079632679489f;
	
	float theta1 = 0.0;
	float theta2 = 0.0;
	float theta3 = 0.0;

	float ex = 0.0f;
	float ey = 0.0f;
	float ez = 0.0f;

	float px = 0.0f;
	float py = 0.0f;
	float pz = 0.0f;

	// Disallow a negative number for radius.
	if (m_radius < 0)
		m_radius = -m_radius;

	// Disallow a negative number for precision.
	if (m_precision < 0)
		m_precision = -m_precision;

	// If the sphere is too small, just render a OpenGL point instead.
	if (m_precision < 4 || m_radius <= 0)
	{
		glBegin(GL_POINTS);
		glVertex3f(cx, cy, cz);
		glEnd();
		return;
	}
	for (int i = 0; i < m_precision / 2; ++i)
	{
		theta1 = i * TWOPI / m_precision - PIDIV2;
		theta2 = (i + 1) * TWOPI / m_precision - PIDIV2;

		glBegin(GL_TRIANGLE_STRIP);
		{
			for (int j = 0; j <= m_precision; ++j)
			{
				theta3 = j * TWOPI / m_precision;

				ex = cosf(theta2) * cosf(theta3);
				ey = sinf(theta2);
				ez = cosf(theta2) * sinf(theta3);
				px = cx + m_radius * ex;
				py = cy + m_radius * ey;
				pz = cz + m_radius * ez;

				glNormal3f(ex, ey, ez);
				glTexCoord2f(-(j / (float)m_precision), 2 * (i + 1) / (float)m_precision);
				glVertex3f(px, py, pz);

				ex = cosf(theta1) * cosf(theta3);
				ey = sinf(theta1);
				ez = cosf(theta1) * sinf(theta3);
				px = cx + m_radius * ex;
				py = cy + m_radius * ey;
				pz = cz + m_radius * ez;

				glNormal3f(ex, ey, ez);
				glTexCoord2f(-(j / (float)m_precision), 2 * i / (float)m_precision);
				glVertex3f(px, py, pz);
			}
		}
		glEnd();
	}
	m_spinY +=0.01f;
	//m_spinX += 0.01f;
}


void CEarth::onLeft()
{

}
void CEarth::onUp()
{

}
void CEarth::onDown()
{

}
void CEarth::onRight()
{

}

void CEarth::loadTexture()
{

}
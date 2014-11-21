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
	glBegin(GL_QUADS);                      // ������ ���
	//glColor3f(0.0f, 1.0f, 0.0f);              // �����
	// �������� �����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(m_xM, -12, 1.0f);	// ��� ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(m_xP, -12, 1.0f);	// ��� �����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(m_xP, 12, 1.0f);	// ���� �����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(m_xM, 12, 1.0f);	// ���� ����
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
#include "Zone.h"


CZone::CZone()
{
	m_x = 0;
	m_y = 2.0f;
	m_rx = 0;
	m_z = 0;
}


CZone::~CZone()
{
}
void CZone::addX()
{
	m_x += 0.1f;
}
void CZone::addY()
{
	m_y += 0.1f;
}
void  CZone::decrementX()
{
	m_x -= 0.1f;
}
void CZone::decrementY(){
	m_y -= 0.1f;
}

int CZone::LoadGLTextures()
{
	return 1;                  // ���������� ������
}

int CZone::Draw()
{
	GLfloat xRotated = 30; GLfloat yRotated; GLfloat zRotated = 30.0;
	GLfloat radius = 1.0f;
	xRotated = 33;
	yRotated = 40;
	m_z += 0.01f;
	if (m_rx > 1.0f)
	{
		m_rx -= 0.1f;
	}
	else 
	{
		m_rx += 0.1f;
	}

	glTranslatef(0.0, 0.0, -10.0);     //  ������������ ��� ��������� ������� ����     
	glColor3f(0.8, 0.5, 0.1);         //  ������� �� �     
	glRotatef(70.0f, 0.5, 0.0, 0.0);     // ������� �� Y      
	glRotatef(m_y, 0.2, 0.5, 0.0);     // ������� �� Z      
	glRotatef(m_z, 0.0, 0.0, 0.5);
	glScalef(1.0, 1.0, 1.0);   // ���������������    
	glutSolidSphere(m_rx, 20, 20);  // ������� ��������� �����    

	//glTranslatef(-1.5f, 0.0f, -6.0f);         // ��������� ����� �� 1.5 ������� �
	//glRotatef(1.0f, 0.0f, 2.0f, 0.0f);         // �������� ������������ �� ��� Y
	// � ����� �� 6.0
	glLoadIdentity();
	glTranslatef(m_x, m_y, -15.0f);          // �������� ������ � ������ ������
	glRotatef(m_rx, 1.0f, 1.0f, 1.0f);        // �������� ���� �� X, Y & Z
	glBegin(GL_QUADS);                      // ������ ���
	glColor3f(0.0f, 1.0f, 0.0f);              // �����
	glVertex3f(0.5f, 0.5f, -0.5f);          // ����� ���� �������� (����)
	glVertex3f(-0.5f, 0.5f, -0.5f);          // ���� ����
	glVertex3f(-0.5f, 0.5f, 0.5f);          // ���� ���
	glVertex3f(0.5f, 0.5f, 0.5f);          // ����� ���

	glColor3f(1.0f, 0.5f, 0.0f);              // ���������
	glVertex3f(0.5f, -0.5f, 0.5f);          // ���� ����� �������� (���)
	glVertex3f(-0.5f, -0.5f, 0.5f);          // ���� ����
	glVertex3f(-0.5f, -0.5f, -0.5f);          // ��� ����
	glVertex3f(0.5f, -0.5f, -0.5f);          // ��� �����

	glColor3f(1.0f, 0.0f, 0.0f);              // �������
	glVertex3f(0.5f, 0.5f, 0.5f);          // ���� ����� �������� (�����)
	glVertex3f(-0.5f, 0.5f, 0.5f);          // ���� ����
	glVertex3f(-0.5f, -0.5f, 0.5f);          // ��� ����
	glVertex3f(0.5f, -0.5f, 0.5f);          // ��� �����

	glColor3f(1.0f, 1.0f, 0.0f);              // ������
	glVertex3f(0.5f, -0.5f, -0.5f);          // ���� ����� �������� (���)
	glVertex3f(-0.5f, -0.5f, -0.5f);          // ���� ����
	glVertex3f(-0.5f, 0.5f, -0.5f);          // ��� ����
	glVertex3f(0.5f, 0.5f, -0.5f);          // ��� �����

	glColor3f(0.0f, 0.0f, 1.0f);              // �����
	glVertex3f(-0.5f, 0.5f, 0.5f);          // ���� ����� �������� (����)
	glVertex3f(-0.5f, 0.5f, -0.5f);          // ���� ����
	glVertex3f(-0.5f, -0.5f, -0.5f);          // ��� ����
	glVertex3f(-0.5f, -0.5f, 0.5f);          // ��� �����

	glColor3f(0.5f, 0.0f, 1.0f);              // ����������
	glVertex3f(0.5f, 0.5f, -0.5f);          // ���� ����� �������� (�����)
	glVertex3f(0.5f, 0.5f, 0.5f);          // ���� ����
	glVertex3f(0.5f, -0.5f, 0.5f);          // ��� ����
	glVertex3f(0.5f, -0.5f, -0.5f);          // ��� �����
	glEnd(); 
	m_rx += 0.1f;
/*m_rtri += 0.2f;             // ���������� ���������� �������� ��� ������������
	m_rquad -= 0.15f;           // ���������� ���������� �������� ��� �������� */
	return TRUE;
}

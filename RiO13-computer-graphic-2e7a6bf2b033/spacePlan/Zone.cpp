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
	return 1;                  // Возвращаем статус
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

	glTranslatef(0.0, 0.0, -10.0);     //  используется для рисования красный цвет     
	glColor3f(0.8, 0.5, 0.1);         //  поворот по Х     
	glRotatef(70.0f, 0.5, 0.0, 0.0);     // Поворот по Y      
	glRotatef(m_y, 0.2, 0.5, 0.0);     // поворот по Z      
	glRotatef(m_z, 0.0, 0.0, 0.5);
	glScalef(1.0, 1.0, 1.0);   // масштабирование    
	glutSolidSphere(m_rx, 20, 20);  // функция рисования сферы    

	//glTranslatef(-1.5f, 0.0f, -6.0f);         // Сдвинемся влево на 1.5 единицы и
	//glRotatef(1.0f, 0.0f, 2.0f, 0.0f);         // Вращение треугольника по оси Y
	// в экран на 6.0
	glLoadIdentity();
	glTranslatef(m_x, m_y, -15.0f);          // Сдвинуть вправо и вглубь экрана
	glRotatef(m_rx, 1.0f, 1.0f, 1.0f);        // Вращение куба по X, Y & Z
	glBegin(GL_QUADS);                      // Рисуем куб
	glColor3f(0.0f, 1.0f, 0.0f);              // Синий
	glVertex3f(0.5f, 0.5f, -0.5f);          // Право верх квадрата (Верх)
	glVertex3f(-0.5f, 0.5f, -0.5f);          // Лево верх
	glVertex3f(-0.5f, 0.5f, 0.5f);          // Лево низ
	glVertex3f(0.5f, 0.5f, 0.5f);          // Право низ

	glColor3f(1.0f, 0.5f, 0.0f);              // Оранжевый
	glVertex3f(0.5f, -0.5f, 0.5f);          // Верх право квадрата (Низ)
	glVertex3f(-0.5f, -0.5f, 0.5f);          // Верх лево
	glVertex3f(-0.5f, -0.5f, -0.5f);          // Низ лево
	glVertex3f(0.5f, -0.5f, -0.5f);          // Низ право

	glColor3f(1.0f, 0.0f, 0.0f);              // Красный
	glVertex3f(0.5f, 0.5f, 0.5f);          // Верх право квадрата (Перед)
	glVertex3f(-0.5f, 0.5f, 0.5f);          // Верх лево
	glVertex3f(-0.5f, -0.5f, 0.5f);          // Низ лево
	glVertex3f(0.5f, -0.5f, 0.5f);          // Низ право

	glColor3f(1.0f, 1.0f, 0.0f);              // Желтый
	glVertex3f(0.5f, -0.5f, -0.5f);          // Верх право квадрата (Зад)
	glVertex3f(-0.5f, -0.5f, -0.5f);          // Верх лево
	glVertex3f(-0.5f, 0.5f, -0.5f);          // Низ лево
	glVertex3f(0.5f, 0.5f, -0.5f);          // Низ право

	glColor3f(0.0f, 0.0f, 1.0f);              // Синий
	glVertex3f(-0.5f, 0.5f, 0.5f);          // Верх право квадрата (Лево)
	glVertex3f(-0.5f, 0.5f, -0.5f);          // Верх лево
	glVertex3f(-0.5f, -0.5f, -0.5f);          // Низ лево
	glVertex3f(-0.5f, -0.5f, 0.5f);          // Низ право

	glColor3f(0.5f, 0.0f, 1.0f);              // Фиолетовый
	glVertex3f(0.5f, 0.5f, -0.5f);          // Верх право квадрата (Право)
	glVertex3f(0.5f, 0.5f, 0.5f);          // Верх лево
	glVertex3f(0.5f, -0.5f, 0.5f);          // Низ лево
	glVertex3f(0.5f, -0.5f, -0.5f);          // Низ право
	glEnd(); 
	m_rx += 0.1f;
/*m_rtri += 0.2f;             // Увеличение переменной вращения для треугольника
	m_rquad -= 0.15f;           // Уменьшение переменной вращения для квадрата */
	return TRUE;
}

#include "Draft.h"

static float SIZE_TRASH	 = 0.4f;
CDraft::CDraft(GLfloat x, GLfloat y )
{
	m_x = x;
	m_time = 0;
	m_y = y;
	m_speedX = 0;
	m_speedY = 0;
	m_isLive = true;
}


CDraft::~CDraft()
{
}


void CDraft::Draw()
{
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -30.0f);
	glRotatef(0.0f, 1.0f, 1.0f, 1.0f);        // Вращение куба по X, Y & Z
	glBegin(GL_QUADS);                      // Рисуем куб
	//glColor3f(0.0f, 1.0f, 0.0f);              // Синий
	// Передняя грань
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-SIZE_TRASH + m_x, -SIZE_TRASH + m_y -0.1, 1.0f);	// Низ лево
	glTexCoord2f(1.0f, 0.0f); glVertex3f(SIZE_TRASH + m_x, -SIZE_TRASH + m_y - 0.1, 1.0f);	// Низ право
	glTexCoord2f(1.0f, 1.0f); glVertex3f(SIZE_TRASH + m_x, SIZE_TRASH + m_y + 0.1, 1.0f);	// Верх право
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-SIZE_TRASH + m_x, SIZE_TRASH + m_y + 0.1, 1.0f);	// Верх лево
	glEnd();
	m_time++;
	if (m_time == 600)
	{
		m_speedX = 0;
		m_speedY = 0;
	}
	m_y += m_speedY;
	m_x += m_speedX;
}
void CDraft::onEvent(EVENTS type){

}


void CDraft::setCoords(GLfloat x, GLfloat y)
{
	m_x = (x == 0.0f) ? m_x : x;
	m_y = (y == 0.0f) ? m_y : y;

}


void CDraft::setSpeed(GLfloat speed){
	m_speedX = speed;
}
GLfloat CDraft::getSpeed()const{
	return m_speedX;
}
void CDraft::setX(GLfloat x){
	m_x = x;
}
GLfloat CDraft::getX()const {
	return m_x;
}
void CDraft::setY(GLfloat y){
	m_y = y;
}
GLfloat CDraft::getY()const {
	return m_y;
}
void CDraft::kill() {
	m_isLive = false;
}
bool CDraft::isAlive()const {
	return m_isLive;
}

GLfloat CDraft::getTop()const
{
	return m_y + SIZE_TRASH;
}
GLfloat CDraft::getBottom()const{
	return m_y - SIZE_TRASH;
}
GLfloat CDraft::getRight()const{
	return m_x + SIZE_TRASH;
}
GLfloat CDraft::getLeft()const{
	return m_x - SIZE_TRASH;
}
GLfloat CDraft::getXCenter()const
{
	return m_x + (SIZE_TRASH / 2);
}
GLfloat CDraft::getYCenter()const {
	return m_y + (SIZE_TRASH / 2);
}

GLfloat CDraft::getWidth()const {
	return SIZE_TRASH;
}
GLfloat CDraft::getHeight()const {
	return SIZE_TRASH;
}
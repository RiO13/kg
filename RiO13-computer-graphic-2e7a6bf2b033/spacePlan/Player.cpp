#include "Player.h"


const double CPlayer::MIN_RADIUS = 5;
const double CPlayer::MAX_RADIUS = 12;

using namespace std;

CPlayer::CPlayer()
	:m_x(0), m_y(0), m_cubeRadius(MIN_RADIUS), m_cubeAngle(M_PI / 2), m_delta(0)
{
	m_step = STAY;
}


void CPlayer::onCollision()
{

}
CPlayer::~CPlayer()
{
}
void CPlayer::Draw()
{
	switch (m_step)
	{
	case STAY:
		glBindTexture(GL_TEXTURE_2D, helper::ALFRED);
		break;
	case STEP_ONE:
		glBindTexture(GL_TEXTURE_2D, helper::STEP_AL);
		break;
	case STEP_TWO:
		glBindTexture(GL_TEXTURE_2D, helper::STEP_TWO_AL);
		break;
	default:
		break;
	}

	m_x = m_cubeRadius * cos(m_cubeAngle);
	m_y = m_cubeRadius * sin(m_cubeAngle);
	if (m_cubeRadius > MAX_RADIUS)
	{
		m_cubeRadius = MAX_RADIUS;
		m_delta = 0.0f;
	}
	if (m_cubeRadius < MIN_RADIUS)
	{
		m_cubeRadius = MIN_RADIUS;
		m_delta = 0.0f;
	}
	if (m_delta != 0.0f)
	{
		m_cubeRadius += m_delta;
		m_delta -= 0.000001;
	}
 
	glLoadIdentity();
	glTranslatef(m_x, m_y, -30.0);

	glBegin(GL_QUADS);                      // Рисуем куб
	// Передняя грань
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, -1.5f, 0);	// Низ лево
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, -1.5f, 0);	// Низ право
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, 1.5f, 0);	// Верх право
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, 1.5f, 0);	// Верх лево*/


	glEnd();

 	// Disable 2D rendering

}

void CPlayer::onEvent(EVENTS type)
{
	switch (type)
	{
	case EVENTS::PRESS_DOWN_BUTTON:
		onDown();
		break;
	case EVENTS::PRESS_UP_BUTTON:
		onUp();
		break;
	case EVENTS::PRESS_LEFT_BUTTON:
		onLeft();
		break;
	case EVENTS::PRESS_RIGHT_BUTTON:
		onRight();
		break;
	default:
		break;
	}
}




void CPlayer::onLeft()
{
	switch (m_step)
	{
	case STAY:
		setStep(STEP_ONE);
		break;
	case STEP_ONE:
		setStep(STEP_TWO);
		break;
	case STEP_TWO:
	{
		setStep(STAY);
		break;
	}
	default:
		break;
	}
	m_cubeAngle += M_PI / 120;
}
void CPlayer::onUp()
{
	m_cubeRadius += 0.1;
	m_delta = 0.0001;
	if (m_cubeRadius > MAX_RADIUS)
	{
		m_cubeRadius = MAX_RADIUS;
	}
}
void CPlayer::onDown()
{
	m_cubeRadius -= 0.1;
	m_delta = -0.0001;
	if (m_cubeRadius < MIN_RADIUS)
	{
		m_cubeRadius = MIN_RADIUS;
	}
}
void CPlayer::onRight()
{
	switch (m_step)
	{
	case STAY:
		setStep(STEP_ONE);
		break;
	case STEP_ONE:
		setStep(STEP_TWO);
		break;
	case STEP_TWO:
	{
		setStep(STAY);
		break;
	}
	default:
		break;
	}
	m_cubeAngle -= M_PI / 120;
}

GLfloat CPlayer::getTop()const
{
	return m_y + 1.0f;
}
GLfloat CPlayer::getBottom()const
{
	return m_y - 1.0f;
}
GLfloat CPlayer::getRight()const
{
	return m_x + 1.0f;
}
GLfloat CPlayer::getLeft()const
{
	return m_x - 1.0f;
}
GLfloat CPlayer::getXCenter()const 
{
	return (m_x  + 2)/ 2;
}
GLfloat CPlayer::getYCenter()const 
{
	return (m_y + 2) / 2;
}

GLfloat CPlayer::getWidth()const 
{
	return 2.0f;
}
GLfloat CPlayer::getHeight()const 
{
	return 2.0f;
}



CPlayer::STEPS CPlayer::getStep()const {
	return m_step;
}
void CPlayer::setStep(STEPS step) {
	m_step = STAY;
}

float CPlayer::getMaxRadius(){
	return MAX_RADIUS;
}

float CPlayer::getMinRadius(){
	return MIN_RADIUS;
}
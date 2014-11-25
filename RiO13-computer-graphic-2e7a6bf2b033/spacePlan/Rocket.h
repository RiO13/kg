#pragma once
#include "ObjectScene.h"

class CRocket : public CObjectScene
{
public:
	CRocket();
	~CRocket();
	virtual void Draw();
	virtual void onEvent(EVENTS type);
	GLfloat getX()const;
	GLfloat getY()const;
	GLuint getTime()const;
	GLfloat getXCenter()const;
	GLfloat getYCenter()const;
private:
	GLfloat m_x;
	GLfloat m_y;
	GLfloat m_speed;
	GLfloat m_speedX;
	GLuint m_timer;
	GLfloat m_speedY;
};


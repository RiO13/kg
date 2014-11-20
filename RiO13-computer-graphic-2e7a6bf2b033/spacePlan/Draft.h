#pragma once
#include "ObjectScene.h"
class CDraft :
	public CObjectScene
{
public:
	CDraft(GLfloat x, GLfloat y);
	~CDraft();
	void setCoords(GLfloat x = 0.0f, GLfloat y = 0.0f);
	virtual void Draw();
	virtual void onEvent(EVENTS type);
	void setSpeed(GLfloat speed);
	GLfloat getSpeed()const;
	void setX(GLfloat x);
	GLfloat getX()const;
	void setY(GLfloat y);
	GLfloat getY()const;
	void kill();
	bool isAlive()const;
	GLfloat getTop()const;
	GLfloat getBottom()const;
	GLfloat getRight()const;
	GLfloat getLeft()const;
	GLfloat CDraft::getXCenter()const;
	GLfloat CDraft::getYCenter()const;
	GLfloat CDraft::getWidth()const;
	GLfloat CDraft::getHeight()const;
private:
	GLuint m_time;
	GLfloat m_speedX;
	GLfloat m_speedY;
	GLfloat m_x;
	GLfloat m_y;
	bool m_isLive;
};


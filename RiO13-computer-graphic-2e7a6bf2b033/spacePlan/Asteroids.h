#pragma once
#include "ObjectScene.h"


class CAsteroids
{
public:
	CAsteroids();
	~CAsteroids();
	virtual void Draw();
	virtual void onEvent(EVENTS type);
	void kill();
	bool isAlive()const;
private:
	GLfloat m_x;
	GLfloat m_y;
	GLfloat m_speed;
	GLfloat m_speedX;
	GLfloat m_speedY;
	bool m_isLive;
};


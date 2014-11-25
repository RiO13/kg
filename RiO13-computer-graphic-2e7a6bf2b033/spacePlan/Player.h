#pragma once
#include "ObjectScene.h"

#define _USE_MATH_DEFINES
#include <math.h>

class CPlayer :
	public CObjectScene
{
public:
	enum STEPS{
		STAY,
		STEP_ONE,
		STEP_TWO
	};
	CPlayer();
	~CPlayer();
	virtual void Draw();
	virtual void onEvent(EVENTS type) ;
	GLfloat getTop()const;
	GLfloat getBottom()const;
	GLfloat getRight()const;
	GLfloat getLeft()const;
	void onCollision();
	GLfloat CPlayer::getXCenter()const;
	GLfloat CPlayer::getYCenter()const;
	GLfloat CPlayer::getWidth()const;
	GLfloat CPlayer::getHeight()const;
	STEPS getStep()const;
	float getMaxRadius();
	float getMinRadius();
	void setStep(STEPS step);
private:
	void onLeft();
	void onUp();
	void onDown();
	void onRight();
	GLfloat m_x;
	GLfloat m_y;
	STEPS m_step;
	float m_cubeRadius;
	float m_cubeAngle;
	GLfloat m_delta;
	static const double MIN_RADIUS;
	static const double MAX_RADIUS;
};


#pragma once
#include "ObjectScene.h" 
class CFon : public CObjectScene
{
public:
	CFon();
	~CFon();
	virtual void Draw() ;
	virtual void onEvent(EVENTS type);
	void setSpeed(GLfloat speed);
	GLfloat CFon::getMx()const;
	GLfloat CFon::getPx()const;
	GLfloat getSpeed()const;
	void setMx(GLfloat mX);
	void setPx(GLfloat pX);
private:
	GLfloat m_speed;
	GLfloat m_xP;
	GLfloat m_xM;
};


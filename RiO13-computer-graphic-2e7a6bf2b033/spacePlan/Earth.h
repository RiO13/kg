#pragma once
#include "ObjectScene.h" 
class CEarth : public CObjectScene
{
public:
	CEarth();
	~CEarth();
	virtual void Draw();
	void onLeft();
	void onUp();
	void onDown();
	void onRight();
	virtual void onEvent(EVENTS type) {};
	void loadTexture();
private:
	GLfloat m_p;
	GLuint m_textureID;
	bool m_lighting ;
	bool m_renderInWireFrame ;
	int  m_precision;
	float m_spinX;
	float m_spinY;
	float m_radius;
	GLfloat cx;
	GLfloat cy;
	GLfloat cz;
};


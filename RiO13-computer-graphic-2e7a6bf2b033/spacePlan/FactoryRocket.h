#pragma once
#include "ObjectScene.h"
#include "Rocket.h"
#include "Player.h"

class CFactoryRocket
{
public:
	CFactoryRocket();
	~CFactoryRocket();
	void addRocket();
	void deleteRocket();
	void getRocketCoords(GLfloat &x, GLfloat &y);
	void drowRockets();
	int getRandomCoords();
	bool CFactoryRocket::collissionPlayer(CPlayer & player);
private:
	std::vector<CRocket> m_rockets;

};


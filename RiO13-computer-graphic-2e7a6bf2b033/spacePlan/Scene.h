#pragma once
#include "Earth.h"
#include "Draft.h"
#include "Player.h" 
#include "Fon.h"
#include "Rocket.h"
#include "Asteroids.h"
#include "FactoryRocket.h"

class CScene
{
public:
	CScene();
	~CScene();
	int Draw();
	void onEvent(EVENTS t);
	bool init();
	void drawFon();
	void collission();
private:
	std::vector<CDraft> m_drafts;
	bool isDeawl;
	CFon m_fon;
	CEarth m_earth;
	CPlayer m_player;
	CRocket m_rocket;
	CAsteroids m_asteroid;
	GLfloat m_time;
	GLfloat m_timeForAsteroids;
	GLboolean m_isActive;
	int m_testRandom;
	int m_timeForRocket;
	CFactoryRocket m_factory; 
};


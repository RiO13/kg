#pragma once
/*
	here we will draw all our objects!
*/
#include "Earth.h"
#include "Draft.h"
#include "Player.h" 
#include "Fon.h"
//#include "Rocket.h"
#include "Asteroids.h"
#include "FactoryRocket.h"

class CScene
{
public:
	bool isAlive;
	CScene();
	~CScene();
	int Draw();
	void onEvent(EVENTS t);
	bool init();
	void CScene::collissionRocket();
	void drawFon();
	void collission();
private:
	std::vector<CDraft> m_drafts;
	bool isDeawl;
	CFon m_fon;
	CFon m_stars;
	CFon m_fog;
	bool m_isDrawing;
	CFon m_back;
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


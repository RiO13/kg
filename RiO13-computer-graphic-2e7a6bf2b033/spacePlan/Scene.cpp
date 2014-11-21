#include "Scene.h"
#include<sstream>
#include <math.h>

static float getRand(int up, int down)
{
	helper::sault++;
	srand(helper::sault);
	float x = (rand() % (up - down)) + down;
	return x;
}
static const int TIME_FOR_DRAFT = 700;
//static const int TIME_FOR_ASTEROIDS = 400;
CScene::CScene()
{ 
	m_isActive = true;
	m_time = 0;
	m_timeForRocket = 0;
	//m_timeForAsteroids = 0;
	isDeawl = true;
	m_factory.addRocket();
	m_testRandom = (int)getRand(2000, 1000);
	m_stars.setSpeed(0.009f);
	m_fog.setSpeed(0.0009f);
}


CScene::~CScene()
{
}

 
void CScene::collission()
{

	for (size_t i = 0; i < m_drafts.size(); ++i) {
		if (((m_drafts.at(i).getXCenter() > m_player.getLeft() && m_drafts.at(i).getXCenter() < m_player.getRight())
			&& m_drafts.at(i).getYCenter() < m_player.getTop() && m_drafts.at(i).getYCenter() > m_player.getBottom()))
		{
			
			m_drafts.at(i).kill();
		}
	}
	
}
 


int CScene::Draw()
{
	glBindTexture(GL_TEXTURE_2D, helper::FON);
	m_fon.Draw();

	glBindTexture(GL_TEXTURE_2D, helper::STARS);
	m_stars.Draw();

	glBindTexture(GL_TEXTURE_2D, helper::FOG);
	m_fog.Draw();

	glBindTexture( GL_TEXTURE_2D, helper::EARTH);
	m_earth.Draw();
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, helper::ROCKET);
	//	m_rocket.Draw();
	m_factory.drowRockets();
//	m_factory.addRocket();
	m_player.Draw();
	glBindTexture(GL_TEXTURE_2D, helper::ASTEROID);
	m_asteroid.Draw();
	float randValue = getRand((int)m_player.getMaxRadius(), (int)m_player.getMinRadius());
	/*
	if (m_rocket.getX() == randValue || m_rocket.getY() == randValue)
	{
		m_drafts.push_back(CDraft(m_rocket.getX(), m_rocket.getY()));
	}*/
	if (m_isActive && m_time >= m_testRandom) {
		m_isActive = false;
		m_time = 0;
		float x, y;
		m_factory.getRocketCoords(x, y);
		m_drafts.push_back(CDraft(x, y));
	}
	
	glBindTexture(GL_TEXTURE_2D, helper::DRAFT);
	for (size_t i = 0; i < m_drafts.size(); i++)
	{
		if (m_drafts[i].isAlive())
			m_drafts[i].Draw();
	}
	collission();
	m_time++;
	m_timeForRocket++;
	m_factory.deleteRocket();
	if (m_timeForRocket > 1000)
	{
		m_isActive = true;
		m_timeForRocket = 0;
		m_factory.addRocket();
	}
	return TRUE;
}
void CScene::onEvent(EVENTS e)
{
	m_player.onEvent(e);
	m_earth.onEvent(e);
	m_rocket.onEvent(e);
}


bool CScene::init()
{
	return true;
}
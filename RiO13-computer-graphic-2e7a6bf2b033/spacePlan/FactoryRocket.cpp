#include "FactoryRocket.h"
#include <math.h>

CFactoryRocket::CFactoryRocket()
{
}



CFactoryRocket::~CFactoryRocket()
{
}


void CFactoryRocket::addRocket()
{
	m_rockets.push_back(CRocket());
}
/*
 * delete unvisible Rockets
*/
void CFactoryRocket::deleteRocket()
{
	std::vector<int> unvisibleRockets;
	for (size_t i = 0; i < m_rockets.size(); i++)
	{
		if (m_rockets.at(i).getTime() > 2500)
		{
			unvisibleRockets.push_back(i);
		}

	}
	for (size_t i = 0; i < unvisibleRockets.size(); i++)
	{
		m_rockets.erase(m_rockets.begin() + unvisibleRockets.at(i));
	}
}
void CFactoryRocket::getRocketCoords(GLfloat &x, GLfloat &y)
{
	helper::sault += 10;
	int maxX = 0;
	int iX = 0;
	int iY = 0;
	int maxY = 0;
	srand(helper::sault);
	for (size_t i = 0; i < m_rockets.size(); ++i) {
		if (std::abs(m_rockets.at(i).getX()) > std::abs(maxX))
		{
			iX = i;
			maxX = m_rockets.at(i).getX();
		}
		if (std::abs(m_rockets.at(i).getY()) > std::abs(maxY))
		{
			iY = i;
			maxY = m_rockets.at(i).getY();
		}
	}
	x = m_rockets.at(iX).getX();
	y = m_rockets.at(iY).getY();
}
void CFactoryRocket::drowRockets()
{
	for (size_t i = 0; i < m_rockets.size(); i++)
	{
		m_rockets[i].Draw();
	}
}


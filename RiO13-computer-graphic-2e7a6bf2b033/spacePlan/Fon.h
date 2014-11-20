#pragma once
#include "ObjectScene.h" 
class CFon : public CObjectScene
{
public:
	CFon();
	~CFon();
	virtual void Draw() ;
	virtual void onEvent(EVENTS type);

};


#pragma once
#include "Helper.h"						// Header File For The GLaux Library
#include <Windows.h>
#include <stdio.h>
extern "C" {
//# include "lua.h"
//# include "lauxlib.h"
//# include "lualib.h"
}

enum EVENTS {
	PRESS_LEFT_BUTTON,
	PRESS_RIGHT_BUTTON,
	PRESS_DOWN_BUTTON,
	PRESS_UP_BUTTON,
	CLICK_LEFT,
	CLICK_RIGHT,
	CLICK_SPACE,
	CLICK_ENTER,
	PRESS_8NUMPAD,
	PRESS_2NUMPAD,
	PRESS_4NUMPAD,
	PRESS_6NUMPAD,
	PRESS_TAB,
	PRESS_ADD,
	PRESS_SUB,
	PRESS_PRIOR,
	PRESS_NEXT,
	PRESS_ENTER,
	PRESS_SPACE,
};
class CObjectScene
{
public:
	
	virtual ~CObjectScene()
	{
	}
	 
	virtual void Draw() = 0;
	virtual void onEvent(EVENTS type) = 0;
};


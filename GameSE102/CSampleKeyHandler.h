#pragma once
#include "CKeyEventHandler.h"
#include "CPlayer.h"
#include "CWindow.h"



class CSampleKeyHandler : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
public:
	static bool isUpDown;
	static bool isDownDown;
	static void update();
};
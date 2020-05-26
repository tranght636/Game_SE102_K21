#pragma once
#include "CWindow.h"

enum TEXTURE_DIRECTION
{
	TEXTURE_DIRECTION_LEFT = -1,
	TEXTURE_DIRECTION_RIGHT = 1
};

class DirectionTexture
{
	static DirectionTexture* instance;
public:
	static DirectionTexture* getInstance();
	void SetDirection(int direction, int x, int width);
	DirectionTexture();
	~DirectionTexture();
};


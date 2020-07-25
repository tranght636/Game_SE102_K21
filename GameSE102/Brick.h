#pragma once
#include "GameObject.h"

#define PATH_GROUND_INFO L"objects\\ground\\ground.info.txt"

class Brick : public CGameObject
{
	static Brick* instance;
public:
	static Brick* getInstance();
	void init();
	void render();
	Brick(float x, float y, float width, float height);
	Brick();
	~Brick();
};


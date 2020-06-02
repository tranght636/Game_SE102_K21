#pragma once
#include <Windows.h>
#include "Objects.h"
#include "CPlayer.h"
#include "Textures.h"
#include "TileMap.h"
#include "Brick.h"

class CGame
{
	static CGame * __instance;
public:
	static CGame * GetInstance();
	void Init();
	void Update(DWORD dt);
	void Render();
	CGame();
	~CGame();
};



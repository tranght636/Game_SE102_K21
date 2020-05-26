#pragma once
#include <Windows.h>
#include "CPlayer.h"
#include "Textures.h"
#include "TileMap.h"

class CGame
{
	static CGame * __instance;
public:
	static CGame * GetInstance();
	void Init();
	void Update(DWORD dt);
	void Render();
	~CGame();
};



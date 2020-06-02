#include "Game.h"


CGame * CGame::__instance = NULL;

CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

void CGame::Init() {
	CPlayer::getInstane()->Init();
	TileMap::getInstance()->init();
	Brick::getInstance()->init();
}

void CGame::Update(DWORD dt) {
	Camera::getInstance()->update();
	CPlayer::getInstane()->Update(dt, &Objects::GetInstance()->getAllObjects());
}

void CGame::Render() {
	TileMap::getInstance()->render(Camera::getInstance());
	CPlayer::getInstane()->Render();
}

CGame::CGame()
{

}

CGame::~CGame()
{

}

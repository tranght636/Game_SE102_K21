#include "Game.h"

#define ID_TEX_PLAYER 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

CGame * CGame::__instance = NULL;

CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

void CGame::Init() {
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_PLAYER, L"textures\\player\\image.png", D3DCOLOR_ARGB(255, 255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texPlayer = textures->Get(ID_TEX_PLAYER);

	sprites->Add(10001, 0, 1, 16, 31, texPlayer); // player idle right
	sprites->Add(10002, 16, 1, 28, 31, texPlayer);
	sprites->Add(10003, 28, 1, 43, 31, texPlayer);

	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(MARIO_ANI_IDLE, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(MARIO_ANI_WALKING, ani);

	CPlayer::AddAnimation(MARIO_ANI_IDLE);		// idle right
	CPlayer::AddAnimation(MARIO_ANI_WALKING);		// walk right

	CPlayer::getInstane()->SetPosition(0.0f, 100.0f);

	TileMap::getInstance()->init(L"textures\\tilemap\\tilesheet.png", L"textures\\tilemap\\matrix.dat");
}

void CGame::Update(DWORD dt) {
	Camera::getInstance()->update();
	CPlayer::getInstane()->Update(dt);
}

void CGame::Render() {
	TileMap::getInstance()->render(Camera::getInstance());
	CPlayer::getInstane()->Render();
}

CGame::~CGame()
{

}

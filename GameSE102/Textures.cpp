#include "textures.h"

CTextures* CTextures::__instance = NULL;

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	textures[id] = CWindow::GetInstance()->LoadTexture(filePath, transparentColor);
	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i)
{
	return textures[i];
}

CTextures::CTextures() {}
CTextures::~CTextures() {}
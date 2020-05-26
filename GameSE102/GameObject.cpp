#include "GameObject.h"

unordered_map<int, LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void CGameObject::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CGameObject::Render()
{
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations[aniId] = ani;
}



CGameObject::~CGameObject()
{
}
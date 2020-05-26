#pragma once
#include <Windows.h>
#include <unordered_map>
#include "Sprites.h"
//#include "DirectionTexture.h"
using namespace std;

class CGameObject
{
protected:
	float x;
	float y;
	float vx;
	float vy;
	int nx;
	int state;
	int direction;
	static unordered_map<int, LPANIMATION> animations;
public:
	static void AddAnimation(int aniId);

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	void Update(DWORD dt);
	void Render();
	CGameObject();
	~CGameObject();
};
#pragma once
#include "GameObject.h"
#include "DirectionTexture.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_JUMP_SPEED_Y		1.0f
#define MARIO_GRAVITY			0.08f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300

#define MARIO_ANI_IDLE		1
#define MARIO_ANI_WALKING	2

class CPlayer : public CGameObject
{
	static CPlayer * instance;
public:
	static CPlayer * getInstane();
	void Init();
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};
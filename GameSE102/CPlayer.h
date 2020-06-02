#pragma once
#include "GameObject.h"
#include "DirectionTexture.h"
#include "Brick.h"

#define PLAYER_WALKING_SPEED	0.1f
#define PLAYER_JUMP_SPEED_Y		0.6f
#define PLAYER_GRAVITY			0.002f

#define PLAYER_STATE_IDLE			0
#define PLAYER_STATE_WALKING_RIGHT	100
#define PLAYER_STATE_WALKING_LEFT	200
#define PLAYER_STATE_JUMP			300

#define PLAYER_ANI_IDLE		1
#define PLAYER_ANI_WALKING	2

class CPlayer : public CGameObject
{
	static CPlayer * instance;
	bool isOnGround;
public:
	static CPlayer * getInstane();
	void Init();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;
	void SetState(int state);
	void setOnGround(bool isOnGround) { this->isOnGround = isOnGround; }
	bool getOnGround() { return this->isOnGround; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CPlayer();
	~CPlayer();
};
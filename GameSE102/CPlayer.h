#pragma once
#include "GameObject.h"
#include "DirectionTexture.h"
#include "Brick.h"

#define PLAYER_WALKING_SPEED	0.1f
#define PLAYER_ON_STAIR_SPEED	0.04f
#define PLAYER_JUMP_SPEED_Y		0.6f
#define PLAYER_GRAVITY			0.002f

#define PLAYER_STATE_IDLE			0
#define PLAYER_STATE_WALKING_RIGHT	100
#define PLAYER_STATE_WALKING_LEFT	200
#define PLAYER_STATE_JUMP			300
#define PLAYER_STATE_WALKING_STAIR_UP	400
#define PLAYER_STATE_WALKING_STAIR_DOWN	500
#define PLAYER_STATE_STAND_STAIR	501
#define PLAYER_STATE_NOMAL	600
#define PLAYER_STATE_ON_STAIR	700

#define PLAYER_ANI_IDLE		0
#define PLAYER_ANI_WALKING	1
#define PLAYER_ANI_STAIR_UP	2
#define PLAYER_ANI_STAIR_DOWN	3
#define PLAYER_ANI_STAND_STAIR_UP	4
#define PLAYER_ANI_STAND_STAIR_DOWN	5

#define PLAYER_NO_PREPARE_STAIR 0
#define PLAYER_PREPARE_STAIR_UP 1
#define PLAYER_PREPARE_STAIR_DOWN 2

#define DXY_STAIR	8.0f
#define PLAYER_ON_STAIR_LEFT -1
#define PLAYER_ON_STAIR_RIGHT 1

class CPlayer : public CGameObject
{
	static CPlayer * instance;
	float start_x;			// initial position of Player at scene
	float start_y;
	int isPrepareGoStair;	// 0: no up or down key. 1: up. 2: down
	bool isStateStair;
	bool isOnGround;
	int stateOnStair;
	int stairDirection;
	float destX;
	float destY;
public:
	static CPlayer * getInstane();
	//void Init();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) override;
	void Render() override;
	void SetState(int state);
	void setOnGround(bool isOnGround) { this->isOnGround = isOnGround; }
	bool getOnGround() { return this->isOnGround; }
	void setStateStair(bool isStateStair) { this->isStateStair = isStateStair; }
	bool getStateStair() { return isStateStair; }
	void setPrepareGoStair(int isPrepareGoStair) { this->isPrepareGoStair = isPrepareGoStair; }
	bool getPrepareGoStair() { return this->isPrepareGoStair; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setDestX(float destX) { this->destX = destX; }
	void setDestY(float destY) { this->destY = destY; }
	int getStateOnStair() { return this->stateOnStair; }
	void setStateOnStair(int stateOnStair) { this->stateOnStair = stateOnStair; }
	int getStairDirection() { return stairDirection; }
	void setStairDirection(int dir) { this->stairDirection = dir; }
	CPlayer();
	~CPlayer();
};
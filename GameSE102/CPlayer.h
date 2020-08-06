#pragma once
#include "GameObject.h"
#include "DirectionTexture.h"
#include "Brick.h"
#include "Weapon.h"

#define PLAYER_WALKING_SPEED	0.1f
#define PLAYER_ON_STAIR_SPEED	0.04f
#define PLAYER_JUMP_SPEED_Y		0.4f
#define PLAYER_GRAVITY			0.002f

#define PLAYER_STATE_IDLE			0
#define PLAYER_STATE_WALKING_RIGHT	100
#define PLAYER_STATE_WALKING_LEFT	200
#define PLAYER_STATE_SIT			201
#define PLAYER_STATE_JUMP			300
#define PLAYER_STATE_WALKING_STAIR_UP	400
#define PLAYER_STATE_WALKING_STAIR_DOWN	500
#define PLAYER_STATE_STAND_STAIR	501
#define PLAYER_STATE_NOMAL	600
#define PLAYER_STATE_ON_STAIR	700
#define PLAYER_STATE_DUNG_DANH	1
#define PLAYER_STATE_DOI_NGUOC	2

#define PLAYER_ANI_IDLE		0
#define PLAYER_ANI_WALKING	1
#define PLAYER_ANI_STAIR_UP	2
#define PLAYER_ANI_STAIR_DOWN	3
#define PLAYER_ANI_STAND_STAIR_UP	4
#define PLAYER_ANI_STAND_STAIR_DOWN	5
#define PLAYER_ANI_JUMP	6
#define PLAYER_ANI_SIT	7
#define PLAYER_ANI_DUNG_DANH 8
#define PLAYER_ANI_DOI_NGUOC 10

#define PLAYER_NO_PREPARE_STAIR 0
#define PLAYER_PREPARE_STAIR_UP 1
#define PLAYER_PREPARE_STAIR_DOWN 2

#define DXY_STAIR	8.0f
#define PLAYER_ON_STAIR_LEFT -1
#define PLAYER_ON_STAIR_RIGHT 1

//#define WEAPON_ROI_LEVEL1 0
//#define WEAPON_ROI_LEVEL2 1

enum WeaponLevel {
	WEAPON_ROI_LEVEL1 = 1,
	WEAPON_ROI_LEVEL2 = 2,
	LEVEL_FINAL
};

class CPlayer : public CGameObject
{
	static CPlayer * instance;
	
	int isPrepareGoStair;	// 0: no up or down key. 1: up. 2: down
	bool isStateStair;
	bool isOnGround;
	int stateOnStair;
	int stairDirection;
	bool isEndStair;
	bool isGiaoStair;
	bool isDoiNguoc;
	float destX;
	float destY;
	int directionStart;

	//Weapon* weapon;

	int levelWeapon;
	unordered_map<int, Weapon*> weapons;

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
	int getIsEndStair() { return isEndStair; }
	void setIsEndStair(int isEndStair) { this->isEndStair = isEndStair; }
	bool getIsGiaoStair() { return isGiaoStair; }
	void setIsGiaoStair(bool isGiaoStair) { this->isGiaoStair = isGiaoStair; }
	int getCurrentFrame();
	void setIsDoiNguoc(bool isDoiNguoc) { this->isDoiNguoc = isDoiNguoc; }
	bool getIsDoiNguoc() { return this->isDoiNguoc; }

	/*void setWeapon(Weapon* w) { this->weapon = w; }
	Weapon* getWeapon() { return this->weapon; }*/

	Weapon* getWeapon() { return weapons[levelWeapon]; }
	void addWeapon(int id, Weapon* w) { weapons[id] = w; }

	void setWeaponLevel(int level) { this->levelWeapon = level; }
	void increaseWeaponLevel();

	void setDirectionStart(int direction) { this->directionStart = direction; }
	int getDirectionStart() { return this->directionStart; }
	CPlayer();
	~CPlayer();
};
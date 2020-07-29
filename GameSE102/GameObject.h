#pragma once
#include <Windows.h>
#include <unordered_map>
#include "Sprites.h"
#include "Collision.h"
using namespace std;

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;
struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) {
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b) {
		return a->t < b->t;
	}
};

class CGameObject
{
protected:
	float x;
	float y;
	float width;
	float height;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	float vx;
	float vy;
	int nx;
	int state;
	int stateCommon;
	int direction;
	DWORD dt;
	//static unordered_map<int, LPANIMATION> animations;

	int ani;

	LPANIMATION_SET animation_set;
public:
	//static void AddAnimation(int aniId);

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void setSize(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	void setStateCommon(int stateCommon) { this->stateCommon = stateCommon; }
	int getStateCommon() { return this->stateCommon; }

	float getX() { return this->x; }
	float getY() { return this->y; }

	float getWidth() {
		if (ani != -1) {
			LPANIMATION animations = animation_set->at(ani);
			return animations->getCurrentFrame()->GetSprite()->getWidth();
		}
		else {
			return this->width;
		}
	}
	float getHeight() { 
		if (ani != -1) {
			LPANIMATION animations = animation_set->at(ani);
			float height = animations->getCurrentFrame()->GetSprite()->getHeight();
			return height;
		}
		return this->height; 
	}

	// get độ chệnh lệnh rộng 2 frame
	float getDW() {
		if (ani != -1) {
			LPANIMATION animations = animation_set->at(ani);
			float currenWidth = animations->getCurrentFrame()->GetSprite()->getWidth();
			float nextWidth = 0;
			if (animations->getNextFrame() != 0) {
				nextWidth = animations->getNextFrame()->GetSprite()->getWidth();
			}
			
			return nextWidth - currenWidth;
		}
	}

	float getBottom() { return y + getHeight(); }
	float getRight() { return x + getWidth(); }
	float getMidX() { return x + getWidth() / 2; }
	float getMidY() { return y - getHeight() / 2; }
	float getVx() { return this->vx; }
	float getVy() { return this->vy; }
	void setDx(float dx) { this->dx = dx; }
	float getDx() { return this->dx; }
	void setDy(float dy) { this->dy = dy; }
	float getDy() { return this->dy; }
	float getDirection() { return direction; }
	void setDirection(int dir) { this->direction = dir; }

	void setAni(int ani) { this->ani = ani; }
	int getAni() { return this->ani; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() {};

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderBoundingBox(int alpha);

	CGameObject();
	~CGameObject();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	
};
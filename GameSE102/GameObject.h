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
	int direction;
	DWORD dt;
	static unordered_map<int, LPANIMATION> animations;
public:
	static void AddAnimation(int aniId);

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

	float getX() { return this->x; }
	float getY() { return this->y; }

	float getVx() { return this->vx; }
	float getVy() { return this->vy; }

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

	CGameObject();
	~CGameObject();
};

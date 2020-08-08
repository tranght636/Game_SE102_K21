#include "RoiItem.h"
#include "CPlayer.h"
#include "PlayScence.h"



RoiItem::RoiItem()
{
}


RoiItem::~RoiItem()
{
}


void RoiItem::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CGameObject::Update(dt);
	vy += PLAYER_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	vector<LPGAMEOBJECT> coObjects;
	for (unsigned i = 0; i < colliable_objects->size(); i++) {
		LPGAMEOBJECT object = colliable_objects->at(i);
		if (dynamic_cast<Brick*>(object)) {
			coObjects.push_back(object);
		}
	}

	CalcPotentialCollisions(&coObjects, coEvents);
	if (coEvents.size() == 0) {
		y += dy;
	} else {
		float min_tx, min_ty, nx = 0, ny = 0;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0) {
			vy = 0;
		}
	}

	coObjects.clear();
}

void RoiItem::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void RoiItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 18;
}
#include "bat.h"
#include "CPlayer.h"
#define	BAT_VX 0.04

Bat::Bat()
{
	vx = BAT_VX;
}


Bat::~Bat()
{
}


void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
	}

	/*CGameObject::Update(dt);
	x -= dx;*/
}

void Bat::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 14;
}
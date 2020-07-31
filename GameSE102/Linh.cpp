#include "Linh.h"
#include "CPlayer.h"

#define	LINH_VX 0.04
Linh::Linh()
{
	vx = LINH_VX;

}

Linh::~Linh()
{
}

void Linh::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
		player->setWeaponLevel(100);
	}

	/*CGameObject::Update(dt);
	x += dx;*/
}

void Linh::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void Linh::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}
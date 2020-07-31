#include "Duoc.h"
#include "CPlayer.h"

Duoc::Duoc()
{
}


Duoc::~Duoc()
{
}

void Duoc::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
		player->setWeaponLevel(100);
	}
}

void Duoc::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void Duoc::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}
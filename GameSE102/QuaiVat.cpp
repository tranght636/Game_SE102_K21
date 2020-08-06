#include "QuaiVat.h"
#include "CPlayer.h"



QuaiVat::QuaiVat()
{
	item = 0;
}


QuaiVat::~QuaiVat()
{
}

void QuaiVat::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
	CPlayer* player = CPlayer::getInstane();
	if (Collision::checkAABB(this, player->getWeapon())) {
		this->setY(-50);
	}
}

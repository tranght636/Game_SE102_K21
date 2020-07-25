#include "Stair.h"
#include "CPlayer.h"
#include "CSampleKeyHandler.h"

Stair::Stair(float x, float y, float width, float height, int isTop, int isRightStair) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->isTop = isTop;
	this->isRightStair = isRightStair;
}

void Stair::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CPlayer* player = CPlayer::getInstane();
	float xPlayerOnStair, yPlayerOnStair;
	if (Collision::checkAABB(this, CPlayer::getInstane())) {
		//if (CPlayer::getInstane()->getPrepareGoStair() == PLAYER_PREPARE_STAIR_UP) {
		if (CSampleKeyHandler::isUpDown && CPlayer::getInstane()->getOnGround() && CPlayer::getInstane()->getStateCommon() != PLAYER_STATE_ON_STAIR) {
			player->setStateCommon(PLAYER_STATE_ON_STAIR);
			player->setStateOnStair(PLAYER_STATE_STAND_STAIR);
			if (!this->isTop) {
				if (this->isRightStair) {
					
				}
				else {
					xPlayerOnStair = this->getMidX()+2;
					yPlayerOnStair = this->getBottom() - player->getHeight();
					player->SetPosition(xPlayerOnStair, yPlayerOnStair);
				}
				player->setDirection(this->isRightStair ? 1 : -1);
				player->setDestX(xPlayerOnStair);
				player->setDestY(yPlayerOnStair);
			}

			
			
			//player->SetState(PLAYER_STATE_ON_STAIR);
		}
		else if (CSampleKeyHandler::isDownDown) {

		}
		else {

		}
	}
}

Stair::Stair()
{
}


Stair::~Stair()
{
}

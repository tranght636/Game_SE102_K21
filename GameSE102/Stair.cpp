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
		if (CSampleKeyHandler::isUpDown 
			&& !this->isTop
			&& CPlayer::getInstane()->getOnGround() 
			&& CPlayer::getInstane()->getStateCommon() != PLAYER_STATE_ON_STAIR) {
				player->setStateCommon(PLAYER_STATE_ON_STAIR);
				player->setStateOnStair(PLAYER_STATE_STAND_STAIR);
				if (this->isRightStair) {
					xPlayerOnStair = this->getMidX() - this->getWidth();
					yPlayerOnStair = this->getBottom() - player->getHeight();
					player->SetPosition(xPlayerOnStair, yPlayerOnStair);	
				}
				else {
					xPlayerOnStair = this->getMidX()+2;
					yPlayerOnStair = this->getBottom() - player->getHeight();
					player->SetPosition(xPlayerOnStair, yPlayerOnStair);
				}
				player->setAni(PLAYER_ANI_STAND_STAIR_UP);
				player->setStairDirection(this->isRightStair ? 1 : -1);
				

			//player->SetState(PLAYER_STATE_ON_STAIR);
		}
		else if (CSampleKeyHandler::isDownDown
			&& this->isTop
			&& CPlayer::getInstane()->getOnGround()
			&& CPlayer::getInstane()->getStateCommon() != PLAYER_STATE_ON_STAIR) {

				player->setStateCommon(PLAYER_STATE_ON_STAIR);
				player->setStateOnStair(PLAYER_STATE_STAND_STAIR);
				if (this->isRightStair) {
					
				}
				else {
					xPlayerOnStair = this->getRight() + 2;
					yPlayerOnStair = this->getBottom() + this->getHeight() / 2 - player->getHeight();
					player->SetPosition(xPlayerOnStair, yPlayerOnStair);
				}
				player->setAni(PLAYER_ANI_STAND_STAIR_DOWN);
				player->setStairDirection(this->isRightStair ? 1 : -1);
				player->setDestX(xPlayerOnStair);
				player->setDestY(yPlayerOnStair);
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

#include "CPLayer.h"
#include "Portal.h"
#include "CSampleKeyHandler.h"

CPlayer* CPlayer::instance = NULL;
CPlayer* CPlayer::getInstane() {
	if (instance == NULL) {
		instance = new CPlayer();
	}
	return instance;
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	switch (stateCommon)
	{
		case PLAYER_STATE_ON_STAIR :
		{
			switch (stateOnStair)
			{
			case PLAYER_STATE_STAND_STAIR:
				
				if (CSampleKeyHandler::isUpDown) {
					destX = getX() - DXY_STAIR;
					destY = getY() - DXY_STAIR;
					vx = -PLAYER_ON_STAIR_SPEED;
					vy = -PLAYER_ON_STAIR_SPEED;
					ani = PLAYER_ANI_STAIR_UP;
					stateOnStair = PLAYER_STATE_WALKING_STAIR_UP;
				}
				break;

			case PLAYER_STATE_WALKING_STAIR_UP:
				if (getX() < destX) {
					vx = 0;
					vy = 0;
					/*x = destX;
					y = destY;*/
					ani = PLAYER_ANI_STAND_STAIR_UP;
					stateOnStair = PLAYER_STATE_STAND_STAIR;
				}
				else {
					CGameObject::Update(dt);
					x += dx;
					y += dy;
				}
				break;
			}
			
			
			break;
		}
		case PLAYER_STATE_NOMAL:
		{
			// Calculate dx, dy 
			CGameObject::Update(dt);
			// Simple fall down
			vy += PLAYER_GRAVITY * dt;

			vector<LPCOLLISIONEVENT> coEvents;
			coEvents.clear();
			CalcPotentialCollisions(coObjects, coEvents);

			//// reset untouchable timer if untouchable time has passed
			//if (GetTickCount() - untouchable_start > PLAYER_UNTOUCHABLE_TIME)
			//{
			//	untouchable_start = 0;
			//	untouchable = 0;
			//}

			// No collision occured, proceed normally
			if (coEvents.size() == 0)
			{
				if (vx < 0 && x < 0) {
					vx = 0;
					x = 0;
				}
				else if (vx > 0 && x > TileMap::getInstance()->getMapWidth() - 16) {
					vx = 0;
					x = TileMap::getInstance()->getMapWidth() - 16;
				}
				else {
					x += dx;
				}
				if (vy < 0 && y < 0) {
					vy = 0;
					y = 0;
				}
				else {
					y += dy;
				}
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				vector<LPCOLLISIONEVENT> coEventsResult;
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

				// block 
				x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;	// prevent moving when collsion
				if (ny != 0) vy = 0;

				// Collision logic with orther object
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];

					if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Goomba 
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);
						if (e->ny < 0)	//ny < 0 player's bottom collie brick's top
						{
							this->setOnGround(true);
						}
						/*float dw = getDW();
						if (e->nx < 0 && dw > 0) {
							this->x -= (dw + 1);
						}
						if (e->nx < 0 && Collision::checkAABB(this, brick)) {
							this->x -= 2;
						}*/

					}
					else if (dynamic_cast<CPortal*>(e->obj))
					{
						CPortal *p = dynamic_cast<CPortal *>(e->obj);
						CGame::GetInstance()->SwitchScene(p->GetSceneId());
						break;
					}
				}
			}

			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			break;
		}
	}
	//if (isStateStair) {
	//	if (CSampleKeyHandler::isUpDown) {
	//		destX = getX() - 6.0f;
	//		destY = getY() - 6.0f;
	//		vx = -PLAYER_ON_STAIR_SPEED;
	//		vy = -PLAYER_ON_STAIR_SPEED;
	//		ani = PLAYER_ANI_STAIR_UP;
	//	}
	//	if (getX() < destX) {
	//		vx = 0;
	//		vy = 0;
	//		x = destX;
	//		y = destY;
	//		ani = PLAYER_ANI_STAND_STAIR_UP;
	//	}
	//	else {
	//		CGameObject::Update(dt);
	//		x += dx;
	//		y += dy;
	//	}
	//}
	//else {
	//	// Calculate dx, dy 
	//	CGameObject::Update(dt);
	//	// Simple fall down
	//	vy += PLAYER_GRAVITY * dt;

	//	vector<LPCOLLISIONEVENT> coEvents;
	//	coEvents.clear();
	//	CalcPotentialCollisions(coObjects, coEvents);

	//	//// reset untouchable timer if untouchable time has passed
	//	//if (GetTickCount() - untouchable_start > PLAYER_UNTOUCHABLE_TIME)
	//	//{
	//	//	untouchable_start = 0;
	//	//	untouchable = 0;
	//	//}

	//	// No collision occured, proceed normally
	//	if (coEvents.size() == 0)
	//	{
	//		if (vx < 0 && x < 0) {
	//			vx = 0;
	//			x = 0;
	//		}
	//		else if (vx > 0 && x > TileMap::getInstance()->getMapWidth() - 16) {
	//			vx = 0;
	//			x = TileMap::getInstance()->getMapWidth() - 16;
	//		}
	//		else {
	//			x += dx;
	//		}
	//		if (vy < 0 && y < 0) {
	//			vy = 0;
	//			y = 0;
	//		}
	//		else {
	//			y += dy;
	//		}
	//	}
	//	else
	//	{
	//		float min_tx, min_ty, nx = 0, ny;

	//		vector<LPCOLLISIONEVENT> coEventsResult;
	//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//		// block 
	//		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//		y += min_ty * dy + ny * 0.4f;

	//		if (nx != 0) vx = 0;	// prevent moving when collsion
	//		if (ny != 0) vy = 0;

	//		// Collision logic with orther object
	//		for (UINT i = 0; i < coEventsResult.size(); i++)
	//		{
	//			LPCOLLISIONEVENT e = coEventsResult[i];

	//			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Goomba 
	//			{
	//				Brick* brick = dynamic_cast<Brick*>(e->obj);
	//				if (e->ny < 0)	//ny < 0 player's bottom collie brick's top
	//				{
	//					this->setOnGround(true);
	//				} 
	//				/*float dw = getDW();
	//				if (e->nx < 0 && dw > 0) {
	//					this->x -= (dw + 1);
	//				}
	//				if (e->nx < 0 && Collision::checkAABB(this, brick)) {
	//					this->x -= 2;
	//				}*/

	//			}
	//			else if (dynamic_cast<CPortal*>(e->obj))
	//			{
	//				CPortal *p = dynamic_cast<CPortal *>(e->obj);
	//				CGame::GetInstance()->SwitchScene(p->GetSceneId());
	//				break;
	//			}
	//		}
	//	}

	//	// clean up collision events
	//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//}

	
}

void CPlayer::Render()
{
	switch (stateCommon)
	{
	case PLAYER_STATE_ON_STAIR:
		if (ani == -1) {
			ani = PLAYER_ANI_STAND_STAIR_UP;
		}
		break;
	case PLAYER_STATE_NOMAL:
		if (vx == 0)
		{
			ani = PLAYER_ANI_IDLE;
			if (nx > 0) direction = TEXTURE_DIRECTION_RIGHT;
			else direction = TEXTURE_DIRECTION_LEFT;
		}
		else if (vx > 0) {
			ani = PLAYER_ANI_WALKING;
			direction = TEXTURE_DIRECTION_RIGHT;
		}
		else {
			ani = PLAYER_ANI_WALKING;
			direction = TEXTURE_DIRECTION_LEFT;
		}
		break;
	}
	/*if (getStateStair()) {
		
	} else {
		if (vx == 0)
		{
			ani = PLAYER_ANI_IDLE;
			if (nx > 0) direction = TEXTURE_DIRECTION_RIGHT;
			else direction = TEXTURE_DIRECTION_LEFT;
		}
		else if (vx > 0) {
			ani = PLAYER_ANI_WALKING;
			direction = TEXTURE_DIRECTION_RIGHT;
		}
		else {
			ani = PLAYER_ANI_WALKING;
			direction = TEXTURE_DIRECTION_LEFT;
		}
	}*/

	animation_set->at(ani)->Render(x, y, direction);
	//RenderBoundingBox(150);
}

void CPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLAYER_STATE_WALKING_RIGHT:
		DebugOut(L"Key right pressed\n");
		vx = PLAYER_WALKING_SPEED;
		nx = 1;
		break;
	case PLAYER_STATE_WALKING_LEFT:
		vx = -PLAYER_WALKING_SPEED;
		nx = -1;
		break;
	case PLAYER_STATE_JUMP: 
		if (getOnGround() && getStateCommon()!=PLAYER_STATE_ON_STAIR) {
			vy = -PLAYER_JUMP_SPEED_Y;
			setOnGround(false);
		}
	case PLAYER_STATE_IDLE:
		vx = 0;
		break;
	/*case PLAYER_STATE_ON_STAIR:
		setStateStair(true);
		break;*/
	}
}

void CPlayer::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;	// getAnimation(animationIndex)->getFrame(frameIndex)->getWidth();
	bottom = y + this->getHeight(); // ||||||||
}

CPlayer::CPlayer() {
	isOnGround = false;
	stateCommon = PLAYER_STATE_NOMAL;
}

CPlayer::~CPlayer() {

}
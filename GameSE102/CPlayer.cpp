#include "CPLayer.h"
#include "Portal.h"
#include "CSampleKeyHandler.h"

bool isSit = false;

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
					
					if (stairDirection == PLAYER_ON_STAIR_RIGHT) {
						destX = getX() + DXY_STAIR;
						vx = PLAYER_ON_STAIR_SPEED;
						direction = 1;
					}
					else {
						destX = getX() - DXY_STAIR;
						vx = -PLAYER_ON_STAIR_SPEED;
						direction = -1;
					}
					destY = getY() - DXY_STAIR;
					vy = -PLAYER_ON_STAIR_SPEED;

					ani = PLAYER_ANI_STAIR_UP;
					stateOnStair = PLAYER_STATE_WALKING_STAIR_UP;
				}
				else if (CSampleKeyHandler::isDownDown) {
					
					if (stairDirection == PLAYER_ON_STAIR_RIGHT) {
						destX = getX() - DXY_STAIR;
						vx = -PLAYER_ON_STAIR_SPEED;
						direction = -1;
					}
					else {
						destX = getX() + DXY_STAIR;
						vx = +PLAYER_ON_STAIR_SPEED;
						direction = +1;
					}
					destY = getY() + DXY_STAIR;
					vy = +PLAYER_ON_STAIR_SPEED;


					ani = PLAYER_ANI_STAIR_DOWN;
					stateOnStair = PLAYER_STATE_WALKING_STAIR_DOWN;
				}
				break;

			case PLAYER_STATE_WALKING_STAIR_UP:
				if ((getX() < destX && stairDirection == PLAYER_ON_STAIR_LEFT)
					|| (getX() > destX && stairDirection == PLAYER_ON_STAIR_RIGHT)) {
					vx = 0;
					vy = 0;
					/*x = destX;
					y = destY;*/
					ani = PLAYER_ANI_STAND_STAIR_UP;
					stateOnStair = PLAYER_STATE_STAND_STAIR;
					if (isEndStair) {
						stateCommon = PLAYER_STATE_NOMAL;
					}
				}
				else {
					CGameObject::Update(dt);
					x += dx;
					y += dy;
				}
				break;
			case PLAYER_STATE_WALKING_STAIR_DOWN:
				if ((getX() > destX && stairDirection == PLAYER_ON_STAIR_LEFT)
					|| (getX() < destX && stairDirection == PLAYER_ON_STAIR_RIGHT)) {
					vx = 0;
					vy = 0;
					/*x = destX;
					y = destY;*/
					ani = PLAYER_ANI_STAND_STAIR_DOWN;
					stateOnStair = PLAYER_STATE_STAND_STAIR;
					if (isEndStair) {
						stateCommon = PLAYER_STATE_NOMAL;
					}
				}
				else {
					CGameObject::Update(dt);
					x += dx;
					y += dy;
				}
				break;
			}
			vector<LPCOLLISIONEVENT> coEvents;
			coEvents.clear();
			CalcPotentialCollisions(coObjects, coEvents);

			float min_tx, min_ty, nx = 0, ny;
			vector<LPCOLLISIONEVENT> coEventsResult;

			if (coEvents.size() > 0) {
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			}

			// Collision logic with orther object
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CPortal*>(e->obj))
				{
					CPortal* p = dynamic_cast<CPortal*>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
					break;
				}
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
							if (ani == PLAYER_ANI_JUMP) {
								y -= 7;
							}
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
						CPortal* p = dynamic_cast<CPortal*>(e->obj);
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
		/*switch (this->state)
		{
		case PLAYER_STATE_IDLE:
			ani = PLAYER_ANI_IDLE;
			break;
		case PLAYER_STATE_WALKING_LEFT:
		case PLAYER_STATE_WALKING_RIGHT:
			ani = PLAYER_ANI_WALKING;
			break;
		case PLAYER_STATE_JUMP:
			ani = PLAYER_ANI_JUMP;
			break;
		case PLAYER_STATE_SIT:
			ani = PLAYER_ANI_SIT;
			break;
		}*/



		if (isOnGround) {
			if (state == PLAYER_STATE_SIT) {
				ani = PLAYER_ANI_SIT;
			}
			else if (vx == 0) {
				if (isSit) {
					isSit = false;
					y -= 7;
				}
				ani = PLAYER_ANI_IDLE;
			}
			else {
				if (isSit) {
					isSit = false;
					y -= 7;
				}
				ani = PLAYER_ANI_WALKING;
			}
		}
		else {
			ani = PLAYER_ANI_JUMP;
		}
		break;
	}

	animation_set->at(ani)->Render(x, y, direction);
	//RenderBoundingBox(150);
}

void CPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLAYER_STATE_WALKING_RIGHT:
		vx = PLAYER_WALKING_SPEED;
		direction = 1;
		break;
	case PLAYER_STATE_WALKING_LEFT:
		vx = -PLAYER_WALKING_SPEED;
		direction = -1;
		break; 
	case PLAYER_STATE_JUMP: 
		if (getOnGround() 
			&& getStateCommon()!=PLAYER_STATE_ON_STAIR) {
			vy = -PLAYER_JUMP_SPEED_Y;
			setOnGround(false);
		}
		break;
	case PLAYER_STATE_IDLE:
		vx = 0;
		break;
	case PLAYER_STATE_SIT:
		if (isGiaoStair) {
			this->state = PLAYER_STATE_IDLE;
			isGiaoStair = false;
			vx = 0;
			break;
		}
		if (isSit == false) {
			isSit = true;
			y += 3;
		}
		vx = 0;
		break;
	
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
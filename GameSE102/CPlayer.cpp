#include "CPLayer.h"

CPlayer* CPlayer::instance = NULL;
CPlayer* CPlayer::getInstane() {
	if (instance == NULL) {
		instance = new CPlayer();
	}
	return instance;
}

void CPlayer::Init() {

}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	//// reset untouchable timer if untouchable time has passed
	//if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	//{
	//	untouchable_start = 0;
	//	untouchable = 0;
	//}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (vx < 0 && x < 0) {
			x = 0;
		} else {
			x += dx;
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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPlayer::Render()
{
	int ani;
	if (vx == 0)
	{
		ani = MARIO_ANI_IDLE;
		if (nx > 0) direction = TEXTURE_DIRECTION_RIGHT;
		else direction = TEXTURE_DIRECTION_LEFT;
	}
	else if (vx > 0) {
		ani = MARIO_ANI_WALKING;
		direction = TEXTURE_DIRECTION_RIGHT;
	}
	else {
		ani = MARIO_ANI_WALKING;
		direction = TEXTURE_DIRECTION_LEFT;
	}
	animations[ani]->Render(x, y, direction);
}

void CPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;

	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	}
	
}

void CPlayer::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;	// getAnimation(animationIndex)->getFrame(frameIndex)->getWidth();
	bottom = y + 16; // ||||||||
}
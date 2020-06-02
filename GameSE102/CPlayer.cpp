#include "CPLayer.h"

CPlayer* CPlayer::instance = NULL;
CPlayer* CPlayer::getInstane() {
	if (instance == NULL) {
		instance = new CPlayer();
	}
	return instance;
}

void CPlayer::Init() {
	LPDIRECT3DTEXTURE9 texPlayer = CTextures::GetInstance()->Get(ID_TEX_PLAYER);
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	sprites->Add(ID_TEX_PLAYER + 1, 0, 1, 16, 31, texPlayer); // player idle right
	sprites->Add(ID_TEX_PLAYER + 2, 16, 1, 28, 31, texPlayer);
	sprites->Add(ID_TEX_PLAYER + 3, 28, 1, 43, 31, texPlayer);

	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(ID_TEX_PLAYER + 1);
	animations->Add(PLAYER_ANI_IDLE, ani);

	ani = new CAnimation(100);
	ani->Add(ID_TEX_PLAYER + 1);
	ani->Add(ID_TEX_PLAYER + 2);
	ani->Add(ID_TEX_PLAYER + 3);
	animations->Add(PLAYER_ANI_WALKING, ani);

	CPlayer::AddAnimation(PLAYER_ANI_IDLE);		// idle right
	CPlayer::AddAnimation(PLAYER_ANI_WALKING);		// walk right

	CPlayer::getInstane()->SetPosition(0.0f, 100.0f);
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny < 0)	//ny < 0 player's bottom collie brick's top
				{
					this->setOnGround(true);
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPlayer::Render()
{
	int ani;
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
	animations[ani]->Render(x, y, direction);
	//RenderBoundingBox(150);
}

void CPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLAYER_STATE_WALKING_RIGHT:
		vx = PLAYER_WALKING_SPEED;
		nx = 1;
		break;
	case PLAYER_STATE_WALKING_LEFT:
		vx = -PLAYER_WALKING_SPEED;
		nx = -1;
		break;
	case PLAYER_STATE_JUMP: {
		if (getOnGround()) {
			vy = -PLAYER_JUMP_SPEED_Y;
			setOnGround(false);
		}
	}
	case PLAYER_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CPlayer::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;	// getAnimation(animationIndex)->getFrame(frameIndex)->getWidth();
	bottom = y + 30; // ||||||||
}

CPlayer::CPlayer() {
	isOnGround = false;
}

CPlayer::~CPlayer() {

}
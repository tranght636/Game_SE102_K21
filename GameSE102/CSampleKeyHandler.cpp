#include "CSampleKeyHandler.h"
#include "debug.h"
#include "CPlayer.h"

bool CSampleKeyHandler::isUpDown = false;
bool CSampleKeyHandler::isDownDown = false;

void CSampleKeyHandler::update() {
	isUpDown = GetAsyncKeyState(VK_UP);
	isDownDown = GetAsyncKeyState(VK_DOWN);
}

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (CPlayer::getInstane()->getStateCommon() != PLAYER_STATE_ON_STAIR) {
			CPlayer::getInstane()->SetState(PLAYER_STATE_JUMP);
		}
		break;
	//case DIK_UP:
	//	CPlayer::getInstane()->setPrepareGoStair(1);
	//	break;
	//case DIK_DOWN:
	//	CPlayer::getInstane()->setPrepareGoStair(2);
	//	//CPlayer::getInstane()->SetState(PLAYER_STATE_WALKING_STAIR_DOWN);
	//	break;
	//default:
	//	CPlayer::getInstane()->setPrepareGoStair(0);
	//	break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	if (CPlayer::getInstane()->getStateCommon() != PLAYER_STATE_ON_STAIR) {
		if (CWindow::GetInstance()->IsKeyDown(DIK_RIGHT))
			CPlayer::getInstane()->SetState(PLAYER_STATE_WALKING_RIGHT);
		else if (CWindow::GetInstance()->IsKeyDown(DIK_LEFT))
			CPlayer::getInstane()->SetState(PLAYER_STATE_WALKING_LEFT);
		else CPlayer::getInstane()->SetState(PLAYER_STATE_IDLE);
	}
}

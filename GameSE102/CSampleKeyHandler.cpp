#include "CSampleKeyHandler.h"
#include "debug.h"
#include "CPlayer.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		CPlayer::getInstane()->SetState(PLAYER_STATE_JUMP);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	if (CWindow::GetInstance()->IsKeyDown(DIK_RIGHT))
		CPlayer::getInstane()->SetState(PLAYER_STATE_WALKING_RIGHT);
	else if (CWindow::GetInstance()->IsKeyDown(DIK_LEFT))
		CPlayer::getInstane()->SetState(PLAYER_STATE_WALKING_LEFT);
	else CPlayer::getInstane()->SetState(PLAYER_STATE_IDLE);
}

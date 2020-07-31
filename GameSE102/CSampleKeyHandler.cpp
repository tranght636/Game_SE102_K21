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
	case DIK_X:
	case DIK_SPACE:
		if (CPlayer::getInstane()->getStateCommon() != PLAYER_STATE_ON_STAIR) {
			CPlayer::getInstane()->SetState(PLAYER_STATE_JUMP);
		}
		break;
	case DIK_Z:
		CPlayer::getInstane()->SetState(PLAYER_STATE_DUNG_DANH);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CPlayer* player = CPlayer::getInstane();
	if (player->getStateCommon() != PLAYER_STATE_ON_STAIR
		&& player->GetState() != PLAYER_STATE_DUNG_DANH) {
		if (CWindow::GetInstance()->IsKeyDown(DIK_RIGHT))
			player->SetState(PLAYER_STATE_WALKING_RIGHT);
		else if (CWindow::GetInstance()->IsKeyDown(DIK_LEFT))
			player->SetState(PLAYER_STATE_WALKING_LEFT);
		else if(CWindow::GetInstance()->IsKeyDown(DIK_DOWN))
			player->SetState(PLAYER_STATE_SIT);
		else if(player->GetState() != PLAYER_STATE_DUNG_DANH)
			player->SetState(PLAYER_STATE_IDLE);
	}
}

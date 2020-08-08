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
	CPlayer* player = CPlayer::getInstane();
	switch (KeyCode)
	{
	case DIK_X:
	case DIK_SPACE:
		if (player->getStateCommon() != PLAYER_STATE_ON_STAIR) {
			player->SetState(PLAYER_STATE_JUMP);
		}
		break;
	case DIK_Z:
		if (player->getStateCommon() == PLAYER_STATE_NOMAL) {
			player->SetState(PLAYER_STATE_DUNG_DANH);
		}
		else if (player->getStateCommon() == PLAYER_STATE_ON_STAIR) {
			player->SetState(PLAYER_STATE_THANG_DANH);
		}
			
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
		&& player->GetState() != PLAYER_STATE_DUNG_DANH
		&& !player->getIsDoiNguoc()) {
		if (CWindow::GetInstance()->IsKeyDown(DIK_RIGHT))
			player->SetState(PLAYER_STATE_WALKING_RIGHT);
		else if (CWindow::GetInstance()->IsKeyDown(DIK_LEFT))
			player->SetState(PLAYER_STATE_WALKING_LEFT);
		else if(CWindow::GetInstance()->IsKeyDown(DIK_DOWN))
			player->SetState(PLAYER_STATE_SIT);
		else if(player->GetState() != PLAYER_STATE_DUNG_DANH )
			player->SetState(PLAYER_STATE_IDLE);
	}
}

#pragma once
#include "GameObject.h"
class QuaiVat : public CGameObject
{
protected:
	int item;	// phần thưởng khi đánh quái vật (nếu có); item = 0 => không có
	int aniSetItem;
public:
	QuaiVat();
	~QuaiVat();
	int getItem() { return this->item; }
	void setItem(int item) { this->item = item; }
	int getAniSetItem() { return this->aniSetItem; }
	void setAniSetItem(int aniSetItem) { this->aniSetItem = aniSetItem; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
};


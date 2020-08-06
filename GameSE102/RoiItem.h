#pragma once
#include "GameObject.h"
class RoiItem : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	RoiItem();
	~RoiItem();
};


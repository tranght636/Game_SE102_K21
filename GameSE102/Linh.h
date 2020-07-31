#pragma once
#include "QuaiVat.h"
class Linh : public QuaiVat
{
public:
	Linh();
	~Linh();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) override;
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
};
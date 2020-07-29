#pragma once
#include "GameObject.h"

class Duoc : public CGameObject
{
public:
	Duoc();
	~Duoc();
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
};


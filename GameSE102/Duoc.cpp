#include "Duoc.h"

Duoc::Duoc()
{
}


Duoc::~Duoc()
{
}

void Duoc::Render() {
	ani = 0;
	animation_set->at(ani)->Render(x, y);
}

void Duoc::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}
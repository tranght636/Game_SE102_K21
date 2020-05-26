#pragma once
#include<d3dx9.h>
class Camera
{
	float x;
	float y;
	float width;
	float height;
	float dx;
	float dy;
	static Camera* instance;
public:
	static Camera* getInstance();
	void convertWorldToView(float xWorld, float yWorld, float& xView, float& yView);
	float getLeft();
	float getTop();
	float getRight();
	float getBottom();
	float getDx();
	float getDy();

	void setDx(float dx);
	void setDy(float dy);

	void update();
	Camera();
	~Camera();
};


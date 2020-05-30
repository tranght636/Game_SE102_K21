#pragma once
#include<d3dx9.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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
	float getX();
	float getY();
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


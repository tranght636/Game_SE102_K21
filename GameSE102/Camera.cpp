#include "Camera.h"
#include "CPlayer.h"

Camera * Camera::instance = 0;
Camera * Camera::getInstance() {
	if (instance == 0) {
		instance = new Camera();
	}
	return instance;
}

float Camera::getX() {
	return x;
}

float Camera::getY() {
	return y;
}

float Camera::getLeft() {
	return x;
}
float Camera::getRight() {
	return x + width;
}
float Camera::getTop() {
	return y;
}
float Camera::getBottom() {
	return y - height;
}
float Camera::getDx() {
	return this->dx;
}
float Camera::getDy() {
	return this->dy;
}
void Camera::setDx(float dx) {
	this->dx = dx;
}
void Camera::setDy(float dy) {
	this->dy = dy;
}

void Camera::update() {
	float xPlayer = CPlayer::getInstane()->getX();
	if (xPlayer > SCREEN_DX) {
		this->x = xPlayer - SCREEN_DX;
	}
}

Camera::Camera()
{
	this->x = 0;
	this->y = 480;
	this->width = 640;
	this->height = 480;
}


Camera::~Camera()
{
}

#include "Camera.h"

Camera * Camera::instance = 0;
Camera * Camera::getInstance() {
	if (instance == 0) {
		instance = new Camera();
	}
	return instance;
}

void Camera::convertWorldToView(float xWorld, float yWorld, float & xView, float & yView)
{
	/* ma trận biến đổi world to view */
	D3DXMATRIX matrixWorldToView;
	D3DXMatrixIdentity(&matrixWorldToView);
	matrixWorldToView._22 = -1;
	matrixWorldToView._41 = -this->getLeft();
	matrixWorldToView._42 = this->getTop();
	/* nhân ma trận đó với xWorld yWorld ta được xView yView */
	D3DXVECTOR3 pos3(xWorld, yWorld, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrixWorldToView);
	xView = MatrixResult.x;
	yView = MatrixResult.y;
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
	x += dx;
}

Camera::Camera()
{
	this->x = 0;
	this->y = 400;
	this->width = 640;
	this->height = 480;
	this->dx = 3.5f;
	this->dy = 0.0f;
}


Camera::~Camera()
{
}

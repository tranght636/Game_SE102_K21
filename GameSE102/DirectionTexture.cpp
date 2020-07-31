#include "DirectionTexture.h"

DirectionTexture* DirectionTexture::instance = NULL;

DirectionTexture* DirectionTexture::getInstance() {
	if (instance == NULL) {
		instance = new DirectionTexture();
	}
	return instance;
}

void DirectionTexture::SetDirection(int d, int x, int widthCurrent, int width) {
	D3DXMATRIX flipMatrix;
	D3DXMatrixIdentity(&flipMatrix);
	if (d == TEXTURE_DIRECTION_LEFT) {
		flipMatrix._11 = -1;
		flipMatrix._41 = 2 * (x - Camera::getInstance()->getX() + widthCurrent / 2) - widthCurrent + width;
	}
	CWindow::GetInstance()->GetSpriteHandler()->SetTransform(&flipMatrix);
}

DirectionTexture::DirectionTexture()
{
}


DirectionTexture::~DirectionTexture()
{
}

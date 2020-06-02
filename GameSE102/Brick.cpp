#include "Brick.h"
#include "Game.h"
#include<fstream>

Brick* Brick::instance = NULL;

Brick* Brick::getInstance() {
	if (instance == NULL) {
		instance = new Brick();
	}
	return instance;
}

void Brick::init() {
	int numOfBrick, x, y, width, height;
	fstream fs(PATH_GROUND_INFO);
	fs >> numOfBrick;
	LPGAMEOBJECT object = NULL;
	for (int i = 0; i < numOfBrick; i++) {
		fs >> x >> y >> width >> height;
		object = new Brick();
		object->setSize(x, y, width, height);
		Objects::GetInstance()->addObject(object);
	}
}

//void Brick::render() {
//	vector<LPGAMEOBJECT> bricks = Objects::GetInstance()->getAllObjects();
//	for (UINT i = 0; i < bricks.size(); i++) {
//		bricks[i]->RenderBoundingBox(150);
//	}
//}

Brick::Brick()
{
}


Brick::~Brick()
{
}

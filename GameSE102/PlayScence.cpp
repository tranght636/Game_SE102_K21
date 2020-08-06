#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "CLayer.h"
#include "CSampleKeyHandler.h"
#include "Duoc.h"
#include "Weapon.h"
#include "Zoombie.h"
#include "Linh.h"
#include "Bat.h"
#include "DenCay.h"
#include <algorithm>

using namespace std;

vector<LPGAMEOBJECT> CPlayScene::objects;

void CPlayScene::removeObject(LPGAMEOBJECT gameObject) {
	objects.erase(remove(objects.begin(), objects.end(), gameObject), objects.end());
}

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	//key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/
//
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TILEMAP	1
#define SCENE_SECTION_CAMRA		2
#define SCENE_SECTION_OBJECTS	3

#define OBJECT_TYPE_PLAYER	0
#define OBJECT_TYPE_PORTAL	-1
#define OBJECT_TYPE_BRICK	-2
#define	OBJECT_TYPE_STAIR	-3
#define OBJECT_TYPE_DUOC	1
#define OBJECT_TYPE_VUKHI	2
#define OBJECT_TYPE_ZOOMBIE	3
#define	OBJECT_TYPE_LINH	4
#define	OBJECT_TYPE_BAT		5
#define OBJECT_TYPE_DEN_CAY	6



#define MAX_SCENE_LINE 1024

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());
	int tokenSize = tokens.size();
	if (tokenSize < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_PLAYER: {
		CPlayer* player = CPlayer::getInstane();
		player->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		player->SetAnimationSet(ani_set);
		if (tokenSize == 7) {
			float startX = atof(tokens[4].c_str());
			float startY = atof(tokens[5].c_str());
			float direct = atof(tokens[6].c_str());
			player->setStart(startX, startY);
			player->setDirectionStart(direct);
		}
		return;
	}
	case OBJECT_TYPE_STAIR: {
		float width, height, isTop, isRightStair;
		width = atof(tokens[3].c_str());
		height = atof(tokens[4].c_str());
		isTop = atof(tokens[5].c_str());
		isRightStair = atof(tokens[6].c_str());
		obj = new Stair(x, y, width, height, isTop, isRightStair);
		break;
	}
	case OBJECT_TYPE_BRICK: {
		float width, height;
		width = atof(tokens[3].c_str());
		height = atof(tokens[4].c_str());
		obj = new Brick(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_PORTAL: {
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	case OBJECT_TYPE_DUOC: {
		obj = new Duoc();
		if (tokenSize > 4) {
			int item = atoi(tokens[4].c_str());
			int aniSetItem = atoi(tokens[5].c_str());
			((QuaiVat*)obj)->setItem(item);
			((QuaiVat*)obj)->setAniSetItem(aniSetItem);
		}
		break;
	}

	case OBJECT_TYPE_ZOOMBIE: {
		obj = new Zoombie();
		break;
	}

	case OBJECT_TYPE_LINH: {
		obj = new Linh();
		break;
	}
	case OBJECT_TYPE_BAT: {
		obj = new Bat();
		break;
	}
	case OBJECT_TYPE_DEN_CAY: {
		obj = new DenCay();
		break;
	}

	/*case OBJECT_TYPE_VUKHI: {
		obj = new Weapon();
		CPlayer::getInstane()->setWeapon((Weapon* )obj);
		break;
	}*/
	
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	obj->setStart(x, y);

	// if object < 0 -> object no have sprite and animation.
	if (object_type > 0) {
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_TILEMAP(string line) {
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 2) return; // skip invalid lines - an object set must have at least id, x, y

	LPCWSTR pathImage = ToLPCWSTR(tokens[0]);
	LPCWSTR pathInfo = ToLPCWSTR(tokens[1]);
	TileMap::getInstance()->init(pathImage, pathInfo);
}

void CPlayScene::_ParseSection_CAMERA(string line) {
	if (line == "") return;
	int typeCam = atoi(line.c_str());
	if (typeCam) {
		int xCam = TileMap::getInstance()->getMapWidth() - SCREEN_WIDTH + 16;
		Camera::getInstance()->setX(xCam);
	}
	else {
		Camera::getInstance()->reset();
	}
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line == "[CAMERA]") {
			section = SCENE_SECTION_CAMRA; continue;
		}
		/*if (line == "") {
			section = SCENE_SECTION_UNKNOWN; continue;
		}*/
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
		case SCENE_SECTION_CAMRA: _ParseSection_CAMERA(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	//// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	//// TO-DO: This is a "dirty" way, need a more organized way 

	//vector<LPGAMEOBJECT> coObjects;
	/*for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}*/

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
	}

	//// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	//if (player == NULL) return;

	//// Update camera to follow mario
	//float cx, cy;
	//player->GetPosition(cx, cy);

	//CGame *game = CGame::GetInstance();
	//cx -= game->GetScreenWidth() / 2;
	//cy -= game->GetScreenHeight() / 2;

	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	CSampleKeyHandler::update();
	Camera::getInstance()->update();
	CPlayer::getInstane()->Update(dt, &objects);
}

void CPlayScene::Render()
{
	TileMap::getInstance()->render(Camera::getInstance());
	
	for (int i = 0; i < objects.size(); i++) {
		//if (dynamic_cast<Weapon*>(objects[i])) continue;
		objects[i]->Render();
	}
		
	CPlayer::getInstane()->Render();
	/*for (UINT i = 0; i < objects.size(); i++) {
		objects[i]->RenderBoundingBox(150);
	}*/
	
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	TileMap::getInstance()->clear();
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}
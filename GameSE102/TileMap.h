#pragma once
#include "CWindow.h"
#include "Sprites.h"
#include "Camera.h"


class TileMap
{
	int tileWidth;
	int tileHeight;
	int tileRows;
	int tileColumns;
	int tilesheetColumns;
	int mapHeight;
	
	int** matrix;
	LPDIRECT3DTEXTURE9 texture;
	static TileMap* instance;
public:
	static TileMap* getInstance();
	void render(Camera* camera);
	int getMapHeight();
	void init(LPCWSTR tilesheetPath, LPCWSTR matrixPath);
	TileMap();
	~TileMap();
};


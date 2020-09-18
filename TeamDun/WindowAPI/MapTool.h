#pragma once
#include "gameNode.h"

struct Grid
{
	int		_x;		// X ��ġ
	int		_y;		// Y ��ġ
	RECT	_rc;	// RECT
	image* _img;	// IMAGE
};

class mapScene;
class MapTool : public gameNode
{
private:
	vector<vector<Grid*>>	_vMapData;
	mapScene*				_mapScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	vector<vector<Grid*>>& GetGrid() { return _vMapData; }

	Grid* mouseCollisionCheck();
	void SaveData();
	void LoadData();
	void MapLineAddRow();
	void MapLineAddCol();
	void MapLineRemoveCol();
	void MapLineRemoveRow();
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
};
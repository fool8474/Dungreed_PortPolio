#pragma once
#include "gameNode.h"

struct Grid
{
	int		_x;			// X ��ġ
	int		_y;			// Y ��ġ
	int     _xIndex;	// xIndex
	int		_yIndex;	// yIndex
	RECT	_rc;		// RECT
	image*	_img;		// IMAGE
};

class mapScene;

class MapTool : public gameNode
{
private:

	vector<vector<Grid*>>			_vMapData;		// �� �����͸� ������ �ִ� ����
	vector<Grid*>					_vUiBrushGrid;	// ���� ������ �귯�ĵ��� ������ �ִ� ����
	vector<vector<vector<string>>>	_vEveData;		// ������Ҹ� ���� �ൿ �� ���� ������ ����

	mapScene*						_mapScene;		// �ʾ�

public:
	HRESULT init();
	HRESULT init(int width, int height);
	void release();
	void update();
	void render();


	Grid* mouseCollisionCheck();
	void SaveData(string name);
	void LoadData(string name);
	void EveSaveData();
	void EveLoadData();
	void MapLineAddRow();
	void MapLineAddCol();
	void MapLineRemoveCol();
	void MapLineRemoveRow();
	void FillAll();
	void FloodFill(image * targetImage, int indexX, int indexY);
	void GridRange(float x, float y, float x1, float y1);
	
	// GETSET // 
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
	vector<vector<Grid*>>& GetGrid() { return _vMapData; }

};
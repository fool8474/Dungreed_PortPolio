#pragma once
#include "gameNode.h"

struct Tile
{
	int		_x;					// X ��ġ
	int		_y;					// Y ��ġ
	image*	_img;				// IMAGE
	image*	_img2;				// IMAGE2
	image*	_collisionImage;	// �ȼ��浹 �̹���
};

class gameScene : public gameNode
{
private:
	vector <vector<Tile*>>	_vMapData;
	vector <Object*>		_vObjs;
	vector <RECT>			_vMiniRc;
	float					_pivX;
	float					_pivY;

public:
	HRESULT init();
	void LoadMap(string fileName);
	void release();
	void update();
	void render();
	void setMiniMap();

};


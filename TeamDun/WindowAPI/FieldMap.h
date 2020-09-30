#pragma once

struct Tile
{
	int		_x;					// X ��ġ
	int		_y;					// Y ��ġ
	image* _img;				// IMAGE
	image* _img2;				// IMAGE2
	image* _collisionImage;	// �ȼ��浹 �̹���
};

class FieldMap
{
private :
	string					_fileName;
	vector<vector<Tile*>>	_vMapData;
	vector <Object*>		_vObjs;
	vector <RECT>			_vMiniRc;
	
	int						_nextMapIndex[4];
	int						_stage;
public :
	void LoadMap();

	HRESULT init(string fileName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	string	GetFileName()			{ return _fileName; }
	void	SetStage(int stage)		{ _stage = stage; }
};


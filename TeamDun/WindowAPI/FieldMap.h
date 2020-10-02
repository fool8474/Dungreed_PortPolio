#pragma once

struct Tile
{
	int		_x;					// X ��ġ
	int		_y;					// Y ��ġ
	image* _img;				// IMAGE
	image* _img2;				// IMAGE2
	image* _collisionImage;		// �ȼ��浹 �̹���
};

class FieldMap
{
private :
	string					_fileName;			// ���� �̸� (�� �̸�)
	vector<vector<Tile*>>	_vMapData;			// �� �׸��� ���� ����
	vector<Object*>			_vObjs;				// �ش� �濡 �����ϴ� ������Ʈ��
	vector<RECT>			_vMiniRc;			// �̴ϸʿ� Rects
												   
	int						_nextMapIndex[4];	// ���� ���� Vector Index (���⺰)
	int						_stage;				// �ش� ���� ��������
												   
	bool					_isCleared;			// ���� ���͸� ��� ó���ߴ��� ����
												
	bool					_isSpawning;		// ���� ��
	int						_spawnTimer;		// ���� ������ Ÿ�̸�

public :
	void LoadMap();

	void MakeNearTileCollision(Door* door, bool isActivate);

	void MakeDoor(Door* door);
	void PixelCollisionMapGenerate();
	void GridMapGenerate();

	HRESULT init(string fileName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void ShotObject();
	void SetDoorSpawning();
	void SpawnMonsters();
	void CheckNoMonsterInMap();
	void EraseDeathObject();
	
	// GETSET //
	string				GetFileName()		{ return _fileName; }
	bool				GetIsCleared()		{ return _isCleared; }
	vector<Object*>&	GetObjects()		{ return _vObjs; }	


	void	SetIsSpawning(bool isSpawning)	{ _isSpawning = isSpawning; }
	void	SetStage(int stage)				{ _stage = stage; }
};
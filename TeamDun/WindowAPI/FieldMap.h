#pragma once

struct Tile
{
	int		_x;					// X ��ġ
	int		_y;					// Y ��ġ
	image* _img;				// IMAGE
	image* _img2;				// IMAGE2
	image* _collisionImage;		// �ȼ��浹 �̹���
};

enum FIELDMAPTYPE
{
	FMT_ENTER, FMT_END, FMT_RESTAURANT, FMT_SHOP, FMT_TEMPLE, FMT_NORMAL
};
class Portal;
class FieldMap
{
private :
	int						_xIndex;			// ��ġ X
	int						_yIndex;			// ��ġ Y
	string					_fileName;			// ���� �̸� (�� �̸�)
	vector<vector<Tile*>>	_vMapData;			// �� �׸��� ���� ����
	vector<Object*>			_vObjs;				// �ش� �濡 �����ϴ� ������Ʈ��
	vector<RECT>			_vMiniRc;			// �̴ϸʿ� Rects
	vector<RECT>			_vMiniObjRc;		// �̴ϸʿ� ������Ʈ Rects
	image*					_backImageEtc;		// ��Ÿ ���� �̹���
	image*					_backImageMain;		// ���� ����̹���
	image*					_townBackgroundImg;	// Ÿ�� ��׶��� �̹���
	image*					_townMountainImg;	// Ÿ�� �� �̹���
	image*					_townGrassImg;		// Ÿ�� Ǯ �̹���
	FIELDMAPTYPE			_mapType;			// �� Ÿ��
	int						_nextMapIndex[4];	// ���� ���� Vector Index (���⺰)
	POINT					_mapMovePos[4];		// �� ������ �����Ҷ��� �÷��̾� ��ġ
	int						_stage;				// �ش� ���� ��������
												   
	bool					_isCleared;			// ���� ���͸� ��� ó���ߴ��� ����	
	bool					_isSpawning;		// ���� ��
	bool					_mapGenVisited;		// �� ���۽� �÷����� üũ�� 
	bool					_visited;			// �湮�ߴ��� ����
	int						_spawnTimer;		// ���� ������ Ÿ�̸�
	
	Portal*					_portal;			// �� ���� ��Ż

public :
	void LoadMap();

	void LoadObject();

	void MakeNearTileCollision(Door* door, bool isActivate);

	void MakeDoor(Door* door);
	void PixelCollisionMapGenerate();
	void GridMapGenerate();

	HRESULT init(string fileName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void DoorParticleGenerate();

	void ShotObject();
	void ChangePlayerByDirection(DIRECTION dir);
	void SetDoorSpawning();
	void SpawnMonsters();
	void CheckNoMonsterInMap();
	void EraseDeathObject();
	
	// GETSET //
	int					GetMapSizeY()					{ return _vMapData.size(); }
	int					GetMapSizeX()					{ return _vMapData[0].size(); }
	int					GetXIndex()						{ return _xIndex; }
	int					GetYIndex()						{ return _yIndex; }
	string				GetFileName()					{ return _fileName; }
	bool				GetIsCleared()					{ return _isCleared; }
	vector<Object*>&	GetObjects()					{ return _vObjs; }	
	FIELDMAPTYPE		GetFieldMapType()				{ return _mapType; }
	int					GetStage()						{ return _stage; }
	POINT				GetMovePos(DIRECTION dir)		{ return _mapMovePos[(int)dir]; }		
	int					GetNextMapIndex(DIRECTION dir)	{ return _nextMapIndex[(int)dir]; }
	bool				GetMapGenVisited()				{ return _mapGenVisited; }
	bool				GetVisited()					{ return _visited; }
	Portal*				GetPortal()						{ return _portal; }

	void	SetXIndex(int index)						{ _xIndex = index; }
	void	SetYIndex(int index)						{ _yIndex = index; }
	void	SetIsSpawning(bool isSpawning)				{ _isSpawning = isSpawning; }
	void	SetStage(int stage)							{ _stage = stage; }
	void	SetFieldType(FIELDMAPTYPE type)				{ _mapType = type; }
	void	SetNextMapIndex(DIRECTION dir, int index)	{ _nextMapIndex[(int)dir] = index; }
	void	SetMovePos(DIRECTION dir, POINT pos)		{ _mapMovePos[(int)dir] = pos; }
	void	SetMapGenVisited(bool visit)				{ _mapGenVisited = visit; }
	void	SetVisited(bool visit)						{ _visited = visit; }
	void	SetPortal(Portal* portal)					{ _portal = portal; }
};
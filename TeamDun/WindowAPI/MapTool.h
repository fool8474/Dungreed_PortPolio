#pragma once
#include "gameNode.h"

struct Grid
{
	int				_x;					// X ��ġ
	int				_y;					// Y ��ġ
	int				_width;				// ��Ʈ����
	int				_height;			// ��Ʈ���α���
	int				_xIndex;			// xIndex
	int				_yIndex;			// yIndex
	RECT			_rc;				// RECT
	image*			_img;				// IMAGE
	image*			_img2;				// IMGE2
	vector<image*>	_vBeforeImg;		// ��IMAGE
	vector<image*>	_vBeforeImg2;		// ��IMAGE2
	image*			_checkImg;			// üũ�̹���
	int				_alpha;
};

class mapScene;

class MapTool : public gameNode
{
private:

	vector<vector<Grid*>>			_vMapData;		// �� �����͸� ������ �ִ� ����
	vector<vector<vector<string>>>	_vEveData;		// ������Ҹ� ���� �ൿ �� ���� ������ ����

	mapScene*						_mapScene;		// �ʾ�

	bool							_isLayer;		// ���̾� �����ϱ����� �Ұ�
	bool							_useTwoLayer;	// FloodFill���� �� ���̾ ��� ����Ѵ�
	float							_zoomWidth;
	float							_zoomHeight;
	
	// OBJECT ���� //
	vector<MapObject*>				_vObjs;			// ������Ʈ ���

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
	void PreviewGridRange( int startIndexX, int startIndexY, int indexX, int indexY,int alpha);
	void GridRange(float x, float y, float x1, float y1);

	void SetMap();
	
	// GETSET // 
	void					SetMapScene(mapScene* scene)		{ _mapScene = scene; }
	vector<vector<Grid*>>&	GetGrid()							{ return _vMapData; }
	vector<MapObject *>&	GetVObject()						{ return _vObjs; }
	bool					getIsLayer()						{ return _isLayer; }
	void					setIsLayer(bool isLayer)			{ _isLayer = isLayer; }
	bool					getUseTwoLayer()					{ return _useTwoLayer; }
	void					setUseTwolayer(bool useTwoLayer)	{ _useTwoLayer = useTwoLayer; }
	float					getZoomWidth()						{ return _zoomWidth;}
	void					setZoomWidth(float width)			{ _zoomWidth = width; }
	float					getZoomHeight()						{ return _zoomHeight; }
	void					setZoomHeight(float height)			{ _zoomHeight = height; }
};
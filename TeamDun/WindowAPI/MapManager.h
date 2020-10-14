#pragma once
#include "singletonBase.h"
#include "Stage.h"

class PixelGetter 
{

public :
	BYTE* pData;
	BITMAP bmInfo;
};

class MapManager : public singletonBase<MapManager>
{
private:
	vector<FieldMap*>	_vOriginMaps;	// �����ͷ� �ҷ��� �ʵ�

	vector<Stage*>		_vStage;		// �������� ������
	int					_currentMap;	// ���� ��
	int					_currentStage;	// ���� ��������
	
	// MAP UI ���� //
	int					_moveClickTimer;
	POINT				_recentMousePos;
	PixelGetter*		_pixelGetter;

public:
	HRESULT init();
	void update();
	void SetMapUIOnOff();
	void GenerateMapParticle();
	void DungeonMapUIMover();
	void ReNewMapUI();
	void release();
	void render(HDC hdc);
	void ChangeMap(int stage, int index);

	// GETSET //
	int					GetCurrentStage()	{ return _currentStage; }
	int					GetCurrentMap()		{ return _currentMap; }
	FieldMap*			GetPlayMap()		{ return _vStage[_currentStage]->GetMaps()[_currentMap]; }
	vector<FieldMap*>&	GetMaps()			{ return _vOriginMaps; }
	PixelGetter*		GetPixelGetter()	{ return _pixelGetter; }
	int			SetCurrentStage(int stage)	{ _currentStage = stage; }
	int			SetCurrentMap(int map)		{ _currentMap = map; }
};


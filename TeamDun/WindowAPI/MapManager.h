#pragma once
#include "singletonBase.h"
#include "Stage.h"
#include "StageChanger.h"

class PixelGetter 
{

public :
	BYTE* pData;
	BITMAP bmInfo;
	int mapSize;
	int byteSize;
};

class MapManager : public singletonBase<MapManager>
{
private:
	vector<FieldMap*>		_vOriginMaps;	// �����ͷ� �ҷ��� �ʵ�

	Stage*					_stage;			// ���� ��������
	int						_curStageNum;	// ���� �������� ��ȣ
	int						_currentMap;	// ���� ��
	// MAP UI ���� //
	int						_moveClickTimer;
	POINT					_recentMousePos;
	PixelGetter*			_pixelGetter;
	bool					_portalOn;
	bool					_portalAnimOn;
	UIFrame*				_mapFrame;
	Portal*					_currentPortal;
	vector<vector<string>>	_mapData;
	StageChanger*			_stageChanger;

public:
	HRESULT init();
	void ClearStage(int cntStage);
	void AddStage(int stageNum);
	void update();
	void SetMapUIOnOff();
	void GenerateMapParticle();
	void DungeonMapUIMover();
	void UsePortalMap();
	void ReNewMapUI();
	void release();
	void render(HDC hdc);
	void ChangeMap(int index);

	void ChangeMapBGM(FIELDMAPTYPE prevMapType);

	// GETSET //
	int					GetCurrentMap()		{ return _currentMap; }
	FieldMap*			GetPlayMap()		{ return _stage->GetMaps()[_currentMap]; }
	vector<FieldMap*>&	GetMaps()			{ return _vOriginMaps; }
	PixelGetter*		GetPixelGetter()	{ return _pixelGetter; }
	bool				GetPortalOn()		{ return _portalOn; }
	bool				GetPortalAnimOn()	{ return _portalAnimOn; }
	Portal*				GetCurrentPortal()	{ return _currentPortal; }
	int					GetCurStageNum()	{ return _curStageNum; }
	StageChanger*		GetStageChanger()	{ return _stageChanger; }

	void 		SetCurrentMap(int map)		{ _currentMap = map; }
	void		SetPortalOn(bool on)		{ _portalOn = on; }
	void		SetCurrentPortal(Portal* p) { _currentPortal = p; }
	void		SetPortalAnimOn(bool on)	{ _portalAnimOn = on; }
};



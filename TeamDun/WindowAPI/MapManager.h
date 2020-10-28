#pragma once
#include "singletonBase.h"
#include "Stage.h"
#include "StageChanger.h"

/// <summary>
/// GetFastPixel�� �ϱ� ���� ��Ʈ�� ������ ����� PixelGetter
/// </summary>
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

	int						_uidCount;			// UID NUMBER
	vector<FieldMap*>		_vOriginMaps;		// �����ͷ� �ҷ��� �ʵ�

	Stage*					_stage;				// ���� ��������
	int						_curStageNum;		// ���� �������� ��ȣ
	int						_currentMap;		// ���� ��
	FIELDMAPTYPE			_prevMapType;		// ���� �� Ÿ��
	int						_prevMapIndex;		// ���� �� ��ȣ

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

	// �������� �������� �ؽ�Ʈ //
	float					_stageNameSpeedX;
	float					_stageNameGravity;
	UIText*					_stageNameText;
	bool					_stageTextMoving;
	int						_textMovingStartTimer;
	int						_textMovingMoveTimer;

public:
	// �⺻ //
	HRESULT init();
	void update();
	void GameResetter();
	void MapRandomChanger();
	void release();
	void render(HDC hdc);
	
	// �������� & �� ���� //
	void ClearStage(int cntStage);
	void MoveStage(int stageNum);
	void ChangeMap(int index);
	void SetPrevMapVariables();
	void ClearChangeMapVectors();
	void AdjustFirstVisitMap();
	void ChangeMapBGM(FIELDMAPTYPE prevMapType);
	void CameraLimitChecker();
	void GenerateMapParticle();

	// UI //
	void UsePortalMap();
	void ReNewMapUI();
	void SetMapUIOnOff();
	void DungeonMapUIMover();
	void MoveStageText();

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
	int					GetUid()			{ return _uidCount; }
	
	void		SetUid(int uid)				{ _uidCount = uid; }
	void 		SetCurrentMap(int map)		{ _currentMap = map; }
	void		SetPortalOn(bool on)		{ _portalOn = on; }
	void		SetCurrentPortal(Portal* p) { _currentPortal = p; }
	void		SetPortalAnimOn(bool on)	{ _portalAnimOn = on; }
};



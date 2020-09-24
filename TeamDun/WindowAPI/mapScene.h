#pragma once
#include "uibrushTool.h"
#include "MapTool.h"
enum BRUSHTYPE
{
	BT_NOFUNC, BT_PAINT, BT_ERASE, BT_FILLRECT, BT_FLOODFILL
};

class mapScene : public gameNode
{
private:
	// UI BRUSH ���� //
	uibrushTool*	_uiBrushTool;

	// MAP TOOL ���� //
	MapTool*		_mapTool;
	image*			_targetImage;
	MapObject*		_targetObject;

	// FILL RANGE ���� //
	bool			_isFillClicked;
	POINT			_clickedPointOne;
	POINT			_clickedPointTwo;

	// �ʱ� ������ ���� ���� //
	int				_heightNum;
	int				_widthNum;
	bool			_isSettingPage;

	// ȸ�� ���� (�׽�Ʈ��) //
	int				_rotateTester;
	int				_rotTimer;

	POINT			_pivot;

	// ���� ���� //
	bool			_isMonsterSettingOn;
	char			_spawnTime[100];
	int				_currentMonsterIndex;

	// ���̺� �ε�� //
	bool			_isEditorViewing;
	char			_fileName[128];
	bool			_isLoad;

	// Ŭ�� ���� //
	bool			_isLeftClicked;
	bool			_isRightClicked;
	bool			_isEnterPressed;
	BRUSHTYPE		_brushType;
	
	// UI ���� //
	bool			_isSizeAdjustOpened;
public :
	HRESULT init();
	void UIInit();
	void release();
	void update();
	void SetMonsterPage();
	void InMonsterSetPage();
	void PlaceObject();
	void EraseObject();
	void InputCheck();
	void SetMapSize();
	void CallSaveEditor();
	void RemovePaint();
	void UpdateFillSquareRange();
	void ToolMovePage();
	void FillSquareRange();
	void CheckShortCutBtnCollision();
	void DoClickByType();
	void PaintSaver();
	void EraseSaver();
	void Paint();
	void FloodFill();
	void FillAll();
	void GetUiBrush();
	void CallLoadEditor();
	void AddMapLine(int type);
	void Undo();
	void render();
	void CameraMove();
	void SaveLoadMap();
	void ShortcutKey();
	void SwitchSizeFrame();
	
	// GETSET //
	image* GetTargetImage() { return _targetImage; }
	void SetTargetImage(image* img) { _targetImage = img; }
	MapObject* GetTargetObject() { return _targetObject; }
	void SetTargetObject(MapObject* obj) { _targetObject = obj; }

	void SaveShortcutKey();
	void LoadShortcutKey();
	void SetLayer();
	void ZoomInOut();
};


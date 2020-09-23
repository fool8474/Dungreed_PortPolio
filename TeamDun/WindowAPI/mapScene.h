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

	// ���̺� �ε�� //
	bool			_isEditerViewing;
	char			_fileName[128];
	bool			_isLoad;

	// Ŭ�� ����//
	bool			_isLeftClicked;
	bool			_isRightClicked;
	BRUSHTYPE		_brushType;
	
public :
	HRESULT init();
	void UIInit();
	void release();
	void update();
	void InputCheck();
	void SetMapSize();
	void CallSaveEditor();
	void RemovePaint();
	void FillSquareRange();
	void CheckShortCutBtnCollision();
	void DoClickByType();
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
	void AddRemoveLine();
	

	// GETSET //
	image* GetTargetImage() { return _targetImage; }
	void SetTargetImage(image* img) { _targetImage = img; }
	void SaveShortcutKey();
	void LoadShortcutKey();
};


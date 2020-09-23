#pragma once
#include "uibrushTool.h"
#include "MapTool.h"

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

	// ���̺� �ε�� //
	bool			_isEditerViewing;
	char			_fileName[128];
	bool			_isLoad;

	// Ŭ�� ����//
	bool			_isLeftClicked;
	bool			_isRightClicked;

	image * _shorcutKeyIg;
	
public :
	HRESULT init();
	void UIInit();
	void release();
	void update();
	void InputCheck();
	void SetMapSize();
	void RemovePaint();
	void ToolMovePage();
	void FillSquareRange();
	void Paint();
	void FloodFill();
	void FillAll();
	void GetUiBrush();
	void CallSaveLoadEditor();
	void AddMapLine();
	void Undo();
	void render();
	void CameraMove();
	void SaveLoadMap();

	// GETSET //
	image* GetTargetImage() { return _targetImage; }
	void SetTargetImage(image* img) { _targetImage = img; }
	MapObject* GetTargetObject() { return _targetObject; }
	void SetTargetObject(MapObject* obj) { _targetObject = obj; }

	void SaveShortcutKey();
	void LoadShortcutKey();
};


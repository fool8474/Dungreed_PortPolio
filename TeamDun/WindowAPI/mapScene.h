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

public :
	HRESULT init();
	void UIInit();
	void release();
	void update();
	void SetMapSize();
	void RemovePaint();
	void FillSquareRange();
	void Paint();
	void FloodFill();
	void FillAll();
	void GetUiBrush();
	void saveData();
	void AddMapLine();
	void loadData();
	void render();

	// GETSET //
	image* GetTargetImage() { return _targetImage; }
	void SetTargetImage(image* img) { _targetImage = img; }
};


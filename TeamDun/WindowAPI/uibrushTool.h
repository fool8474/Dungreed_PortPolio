#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "Object.h"

class mapScene;
class uibrushTool : public gameNode
{
private:
	vector<vector<UIImage*>>	_vUiBrushGrid;		// �׸��� �귯��
	vector<vector<UIImage*>>	_vUiBrushObject;	// ������Ʈ �귯��
	mapScene*					_mapScene;			

	int							_gridPage;			// ���� �׸��� ������
	int							_objPage;			// ���� ������Ʈ ������
	bool						_isObject;			// ���� ������Ʈ�� �����ߴ���
	bool						_isOn;				// ���� �������� �����ִ���
	float						_xPos;				// �������� X��ġ

public:
	HRESULT init();
	void UIInit();
	void PageViewChange();
	void release();
	void update();
	void MoveBrushTool();
	void MenuCollisionCheck();
	void mouseCollisionCheck();
	void render();

	// GETSET //
	vector<vector<UIImage*>>& GetUiBrushGrid() { return _vUiBrushGrid; }
	vector<vector<UIImage*>>& GetUiObjectGrid() { return _vUiBrushObject; }
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
	int GetGridPage() { return _gridPage; }
	void SetGridPage(int page) { _gridPage = page; }
	int GetObjPage() { return _objPage; }
	void SetObjPage(int page) { _objPage = page; }
	bool GetIsObject() { return _isObject; }
};
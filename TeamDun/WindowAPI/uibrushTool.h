#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "Object.h"

class mapScene;
class uibrushTool : public gameNode
{
private:
	vector<vector<UIImage*>>	_vUiBrushGrid;		// �׸��� �귯��
	vector<vector<Object*>>		_vUiBrushObject;	// ������Ʈ �귯��
	mapScene*					_mapScene;			

	int							_page;				// ���� ������
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

	vector<vector<UIImage*>>& GetUiBrushGrid() { return _vUiBrushGrid; }
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
	int GetPage() { return _page; }
	void SetPage(int page) { _page = page; }
};
#pragma once
#include "singletonBase.h"
#include "Object.h"

#include "objHeaderCollector.h"

struct GridData
{
	string	_name;		// �׸��� �̸�
	int		_x;			// uiBrushTool������ x ��ǥ 
	int		_y;			// uiBrushTool������ y ��ǥ 
	int		_page;		// uiBrushTool������ ������ 
	image*	_image;		// ǥ�� �̹���
	image*	_colImage;	// �浹 �̹���
};

class DataManager : public singletonBase<DataManager>
{
private :
	map<string, GridData*>	_mGridDataByName;	// �׸��� ������ �� (�̸����� ��������)
	map<int, GridData*>		_mGridData;			// �׸��� ������ ��
	map<int, Object*>		_mObjectData;		// ������Ʈ ��
	map<int, MapObject*>	_mMapObjectData;	// �� ������Ʈ ��
	map<int, Item*>			_mMapItemData;		// ������ ��

	int	_itemMaxId;
	int _itemMinId;

public :
	HRESULT Init();
	// ������ �ҷ����� //
	void GetUIBrushToolGridData();
	void GetObjectData();
	void GetItemData();
	int GetItemSize();
	Item * GetItemByIndex(int index);
	Item* GetItemById(int id);

	// GETSET //
	map<int, GridData*>&	GetGridData()					{ return _mGridData; }
	GridData*				GetGridDataByName(string name)	{ return _mGridDataByName[name]; }
	map<int, MapObject*>&	GetMapObjectData()				{ return _mMapObjectData; }
	Object*					GetObjectById(int id)			{ return _mObjectData[id]; }
	map<int, Item*>&		GetMapItemData()				{return _mMapItemData; }
	
	int						GetItemMaxId()					{ return _itemMaxId; }
	int						GetItemMinId()					{ return _itemMinId; }
};


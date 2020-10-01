#pragma once
#include "singletonBase.h"
#include "Object.h"

#include "MapObject.h"
#include "Door.h"
#include "MonsterSpawner.h"
#include "BigWhiteSkel.h"
#include "Belial.h"
#include "LittleGhost.h"
#include "Minotaurs.h"
#include "RedBat.h"
#include "Skel.h"

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

public :
	// ������ �ҷ����� //
	void GetUIBrushToolGridData();
	void GetObjectData();

	// GETSET //
	map<int, GridData*>&	GetGridData()					{ return _mGridData; }
	GridData*				GetGridDataByName(string name)	{ return _mGridDataByName[name]; }
	map<int, MapObject*>&	GetMapObjectData()				{ return _mMapObjectData; }
	Object*					GetObjectById(int id)			{ return _mObjectData[id]; }
};


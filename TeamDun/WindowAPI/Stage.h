#pragma once
#include "FieldMap.h"

class Stage
{
private :
	vector<FieldMap*>			_vMaps;					// �� ���� ����
	FieldMap*					_cntMap;				// ���� ��
	int							_stage;					// ���� ��������
	int							_numOfFloodFillCount;	// �÷��� �� Ƚ��
public :
	HRESULT init(int stage);
	void update();
	void release();
	void render(HDC hdc);
	int FindSameIndex(int indexX, int indexY, int curIndex);
	int GetConnectedRoomCount(FieldMap* map, int index);
	void AddRooms();
	void CheckFloodFill(int index, int& numOfCheckRoom);
	bool FloodFillStart();
	void AddRoomConnections();
	bool SettingMap();

	bool AddLine(FieldMap* map, DIRECTION dir, int index);
	bool CheckCollision();

	vector<FieldMap*>& GetMaps() { return _vMaps; }
	FieldMap* GetMapIndex(int index) { return _vMaps[index]; }
};


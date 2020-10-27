#pragma once
#include "FieldMap.h"

class Stage
{
private :
	vector<FieldMap*>			_vMaps;					// �� ���� ����
	FieldMap*					_cntMap;				// ���� ��
	int							_stage;					// ���� ��������
	int							_numOfFloodFillCount;	// �÷��� �� Ƚ��

	// ���� ��������
	int							_resturantRoomIdx;		// ������� �ε���
	int							_startIdx;				// ���� �ε���
	int							_endIdx;				// �� �ε���
public :
	HRESULT init(int stage);
	void update();
	void release();
	void render(HDC hdc);
	int FindSameIndex(int indexX, int indexY, int curIndex);
	int GetConnectedRoomCount(FieldMap* map, int index);
	void AddRooms();
	void SetSpecialRoomPos();
	void CheckFloodFill(int index, int& numOfCheckRoom);
	bool FloodFillStart();
	void AddRoomConnections();
	void SetStageZero();
	void SetStageTwo();
	bool SettingMap();
	void SetFieldMapNumber();
	bool AddLine(FieldMap* map, DIRECTION dir, int index);
	bool CheckCollision();

	vector<FieldMap*>& GetMaps() { return _vMaps; }
	FieldMap* GetMapIndex(int index) { return _vMaps[index]; }
};


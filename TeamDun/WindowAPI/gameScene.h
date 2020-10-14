#pragma once
#include "gameNode.h"
#include "Stage.h"

class gameScene : public gameNode
{
private:
	float					_pivX;
	float					_pivY;
	Player*					_p;
	vector<string>			_vCharName;
	vector<string>			_CharExplanation;
	vector<string>			_CharAbility;
	vector<string>			_CharFirstStat;
	vector<string>			_CharSecondStat;

	int						_scrollTimer;		//��ũ�� Ÿ�̸�
	int						_mouseLocation;		//���� ���콺��ǥ�� ������ ����
public:
	HRESULT init();
	void InitWardrobeString();
	void initUI();
	void ConversationUIInit();
	void WardrobeUIInit();
	void DungeonMapUIInit();
	void InventoryUIInit();
	void ShopUIInit();
	void CharUIInit();
	void release();
	void UpdateWardrobeUI();
	void update();
	void render();
};


#pragma once
#include "Item.h"

class Player;
class Inventory
{

private :
	vector<Item*> _vInvenItems;
	UIFrame* _InvenFrame;
	UIFrame* _shopFrame;
	UIFrame* _swapFrame;

	int		_invenFullTextTimer;
	bool	_invenFullTextOn;
	int		_invenEqualTextTimer;
	bool	_invenEqualTextOn;

	bool	_leftClicked;
	int		_clickedTarget;
	int		_leftClickTimer;
	float	_toolTipFinalY;
	Item*	_curToolTipItem;	// ���� �������� �������� ������

	Item*	_dragItem;
	int		_dragIndex;

	Player* _p;

public :

	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();
	
	void UpdateMoney();

	void EquipItemPos(int pos, Item * item, int index, bool isUsed);
	void DragItemStart();
	void EquipItem();
	void SwitchItem(int num, Item* item, int index);
	void UnEquipItem();
	bool AddItem(Item* item);
	void ReloadUIImages();
	void OnInvenFullText();
	void OnInvenEqualText();
	void CheckInvenText();
	void SwitchWeapon(int selectedWeapon);
	void InitToolTipItem(Item* item);
	string OptionString(SubOption* option);
	void ShowToolTip();

	// GETSET //
	vector<Item*>& GetVItemList() { return _vInvenItems; }
	Item* GetCurToolTipItem() { return _curToolTipItem; }
	void SetCurToolTipItem(Item* item) { _curToolTipItem = item; }
};
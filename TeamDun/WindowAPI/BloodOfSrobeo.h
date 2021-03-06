#pragma once
#include "Item.h"
class BloodOfSrobeo : public Item
{
private:
	bool	_isReady;	//hp를 채울 준비가 되었는지
	int		_CoolTime;		//쿨타임
public:
	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
};


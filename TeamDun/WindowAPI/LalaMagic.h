#pragma once
#include  "Item.h"
class LalaMagic : public Item
{
private:
	int _animCount;
	int _finalAnimCount;
	int _renderFrontCount;
	bool _isLeftAttack;
	float _renderAngle;
public:
	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
	virtual void SetBaseRenderPos();
	void DoSkill();
	void FireBullet();
	virtual void Activate();
};


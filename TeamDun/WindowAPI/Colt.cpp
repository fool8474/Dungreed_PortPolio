#include "stdafx.h"
#include "Colt.h"

HRESULT Colt::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);
	
	_animCount = 0;
	_finalAnimCount = 0;
	
	return S_OK;
}

void Colt::update()
{
	SetBaseRenderPos();
	FireBullet();
	
}

void Colt::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void Colt::release()
{
}

void Colt::FireBullet()
{
	if (_isAttacking)
	{
		if (!ENTITYMANAGER->getPlayer()->GetIsReload())
		{

		SOUNDMANAGER->play("����_����");
		ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER,-20 +_angleCheckPosX +cosf(_angle)*50,-30+ _angleCheckPosY-sinf(_angle) * 50, _angle,
			10, 22, 1000, true, _angle);

		if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
		{

			Bullet* bullet2 = ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle - PI / 12,
				10, 22, 1000, true, _angle - PI / 24);
			
			Bullet* bullet3 = ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle + PI/12,
				10, 22, 1000, true, _angle + PI / 24);
		
		}
		ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);


		_curNumOfBullet--;
		
		}
		_isAttacking = false;
	}
	
}

void Colt::AttackAnim()

{
	
}

void Colt::Activate()
{
	_isAttacking = true;
}




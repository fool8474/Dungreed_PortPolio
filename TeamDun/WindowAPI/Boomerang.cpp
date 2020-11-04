#include "stdafx.h"
#include "Boomerang.h"

HRESULT Boomerang::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_animCount = 0;
	_finalAnimCount = 0;

	return S_OK;
}

void Boomerang::update()
{
	SetBaseRenderPos();
	FireBullet();

}

void Boomerang::render(HDC hdc)
{
	if(_curNumOfBullet == _initNumOfBullet)
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void Boomerang::release()
{
}

void Boomerang::FireBullet()
{
	if (_isAttacking)
	{
		if (!ENTITYMANAGER->getPlayer()->GetIsReload())
		{

			SOUNDMANAGER->play("¹«±â_±ÇÃÑ");
			ENTITYMANAGER->makeBullet("MetalBoomerangSpin", "BulletEffect01", BT_PLAYERNOCOL, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle,
				10, 20, 1000, true, _angle, BST_RETURN);

			if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
			{

				Bullet* bullet2 = ENTITYMANAGER->makeBullet("MetalBoomerangSpin", "BulletEffect01", BT_PLAYERNOCOL, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle - PI / 12,
					10, 20, 1000, true, _angle - PI / 24, BST_RETURN);

				Bullet* bullet3 = ENTITYMANAGER->makeBullet("MetalBoomerangSpin", "BulletEffect01", BT_PLAYERNOCOL, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle + PI / 12,
					10, 20, 1000, true, _angle + PI / 24 ,BST_RETURN);

			}
			ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);


			_curNumOfBullet--;

		}
		_isAttacking = false;
	}

}

void Boomerang::AttackAnim()
{
}

void Boomerang::Activate()
{
	_isAttacking = true;
}

#include "stdafx.h"
#include "RampageWpn.h"

HRESULT RampageWpn::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_animCount = 0;
	_finalAnimCount = 0;
	_targetAngle = 0;

	return S_OK;
}

void RampageWpn::update()
{
	SetBaseRenderPos();
	FireBullet();

}

void RampageWpn::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void RampageWpn::release()
{
}

void RampageWpn::FireBullet()
{
	if (INPUT->GetKey(VK_LBUTTON) && !ENTITYMANAGER->getPlayer()->GetIsReload())
		_angle = _targetAngle;

	if (_isAttacking)
	{
		if (!ENTITYMANAGER->getPlayer()->GetIsReload())
		{
			_targetAngle = RANDOM->range((float)-PI, (float)PI);

			SOUNDMANAGER->play("무기_권총");
			ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_targetAngle) * 50, -30 + _angleCheckPosY - sinf(_targetAngle) * 50, _targetAngle,
				10, 22, 600, true, _targetAngle);

			if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
			{
				Bullet* bullet2 = ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_targetAngle) * 50, -30 + _angleCheckPosY - sinf(_targetAngle) * 50, _targetAngle - PI / 12,
					10, 22, 600, true, _targetAngle - PI / 24);

				Bullet* bullet3 = ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_targetAngle) * 50, -30 + _angleCheckPosY - sinf(_targetAngle) * 50, _targetAngle + PI / 12,
					10, 22, 600, true, _targetAngle + PI / 24);
			}
			ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);

			_curNumOfBullet--;

		}
		_isAttacking = false;
	}

}


void RampageWpn::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();	//플레이어 왼쪽인지
	_yFrame = playerIsLeft ? 0 : 1;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 10 : 70);	//아이템 타입이 한손일때,각도체크용 중점에 플레이어의 x좌표+ 왼쪽인지 여부에따라 맞으면 +20,아니면 +40
	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;	//각도 체크용 중점에 플레이어의 Y좌표를 받아와서  +45만큼
	
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	
	if (!_isAttacking)	//공격중이 아니면
	{
		_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}

void RampageWpn::AttackAnim()
{

}

void RampageWpn::Activate()
{
	_isAttacking = true;
}




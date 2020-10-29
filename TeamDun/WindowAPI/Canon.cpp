#include "stdafx.h"
#include "Canon.h"

HRESULT Canon::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_animCount = 0;
	_finalAnimCount = 0;

	
	return S_OK;
}

void Canon::update()
{
	SetBaseRenderPos();
	FireBullet();
}

void Canon::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void Canon::release()
{
}

void Canon::FireBullet()
{
	if (_isAttacking)
	{
		if (!ENTITYMANAGER->getPlayer()->GetIsReload())
		{

			SOUNDMANAGER->play("����_����");
			ENTITYMANAGER->makeBullet("Canon_bullet", "boom", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle,
				10, 15, 1000, true, _angle , BST_GRAVITY ,"",false);

			if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
			{

				Bullet* bullet2 = ENTITYMANAGER->makeBullet("Canon_bullet", "boom", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle - PI / 12,
					10,15, 1000, true, _angle - PI / 24, BST_GRAVITY, "", false);

				Bullet* bullet3 = ENTITYMANAGER->makeBullet("Canon_bullet", "boom", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle + PI / 12,
					10, 15, 1000, true, _angle + PI / 24, BST_GRAVITY, "", false);

			}
			ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);


			_curNumOfBullet--;

		}
		_isAttacking = false;
	}
}

void Canon::AttackAnim()
{
}

void Canon::Activate()
{
	_isAttacking = true;
}

void Canon::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();	//�÷��̾� ��������
	_yFrame = playerIsLeft ? 0 : 1;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 20 : 50);	//������ Ÿ���� �Ѽ��϶�,����üũ�� ������ �÷��̾��� x��ǥ+ �������� ���ο����� ������ +20,�ƴϸ� +40

	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;	//���� üũ�� ������ �÷��̾��� Y��ǥ�� �޾ƿͼ�  +45��ŭ
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	if (!_isAttacking)	//�������� �ƴϸ�
	{
		_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}

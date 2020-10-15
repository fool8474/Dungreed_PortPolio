#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isSpawned = false;
	_hpBarAlpha = 0;
	_hpBar1 = IMAGEMANAGER->findImage("HpBar1");
	_hpBar2 = IMAGEMANAGER->findImage("HpBar2");
	return S_OK;
}

void Enemy::update()
{
	SpawnAnimation();
	HpBarDelete();
}

void Enemy::release()
{
	Object::release();
}

void Enemy::render(HDC hdc)
{
	Object::render(hdc);
	if (_hpBarAlpha > 0)
	{
		
		CAMERAMANAGER->alphaRender(hdc, _hpBar1, _x+_vImages[_useImage]->getFrameWidth()/2- _hpBar1->getWidth()/2, _y + _vImages[_useImage]->getFrameHeight(),0,0,_hpBar1->getWidth(),_hpBar1->getHeight(), _hpBarAlpha);
		CAMERAMANAGER->alphaRender(hdc, _hpBar2, _x + _vImages[_useImage]->getFrameWidth() / 2 - _hpBar2->getWidth() / 2, _y + _vImages[_useImage]->getFrameHeight(), 0, 0, _hpBar2->getWidth() / (float)_initHp * _HP, _hpBar2->getHeight(), _hpBarAlpha);
	}
	
	
}

void Enemy::Move()
{
	// 미구현 (상속 클래스 내부에서 세부구현) //
}

void Enemy::Attack()
{
	// 미구현 (상속 클래스 내부에서 세부구현) //
}

void Enemy::Animation()
{
	// 미구현 (상속 클래스 내부에서 세부구현) //
}

void Enemy::SpawnAnimation()
{

	if (_spawnEffect != nullptr)
	{
		if (_spawnEffect->GetIsDead())
		{
			_isSpawned = true;
			_spawnEffect = nullptr;
		}
	}
}

void Enemy::GetDamage()
{
	if (_isSpawned)
	{

		Player* p = ENTITYMANAGER->getPlayer();
		int damage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
		
		damage = damage + damage * p->GetPower() / 100 - _realDefence;
		int critical = RANDOM->range(100);
		if (critical <= p->GetRealCriPer()) 
		{
			_hpBarAlpha = 255;
			damage = damage + damage * p->GetCriDamage() / 100;
			_HP -= damage;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 0));
		}
		else
		{
			_hpBarAlpha = 255;
			_HP -= damage;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 255));

		}

		

		if (_HP <= 0)
		{
			SetIsDead(true);
		}
		
	}
}

void Enemy::HpBarDelete()
{
	if (_hpBarAlpha > 0)
	{
		_hpBarAlpha -= 2;

	}
	if (_hpBarAlpha < 0)
	{
		_hpBarAlpha = 0;
	}

}

void Enemy::SpawnEnemy()
{
	if(_spawnEffect == nullptr && !_isSpawned)
		_spawnEffect = EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth()/2 - 46, _y + _vImages[0]->getFrameHeight()/2 - 46, "monsterSpawnEffect", 6);
}

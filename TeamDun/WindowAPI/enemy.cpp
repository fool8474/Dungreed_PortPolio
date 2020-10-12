#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isSpawned = false;

	return S_OK;
}

void Enemy::update()
{
	SpawnAnimation();
	for (int i = 0; i < _vDamageView.size(); i++)
	{
		_vDamageView[i]->count++;


		if (_vDamageView[i]->count > 50)
		{
			_vDamageView.erase(_vDamageView.begin() + i);
		}
	}

}

void Enemy::release()
{
	Object::release();
}

void Enemy::render(HDC hdc)
{
	Object::render(hdc);

	
	
}

void Enemy::Move()
{
	// �̱��� (��� Ŭ���� ���ο��� ���α���) //
}

void Enemy::Attack()
{
	// �̱��� (��� Ŭ���� ���ο��� ���α���) //
}

void Enemy::Animation()
{
	// �̱��� (��� Ŭ���� ���ο��� ���α���) //
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
	int damage = RANDOM->range(ENTITYMANAGER->getPlayer()->GetMinDamage(), ENTITYMANAGER->getPlayer()->GetMaxDamage());
	damage = damage + damage * ENTITYMANAGER->getPlayer()->GetPower() / 100 - _realDefence;
	
	_HP -= damage;

	if (_HP <= 0)
	{
		SetIsDead(true);
	}
	
	EFFECTMANAGER->AddCameraText(_x, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 255));
}

void Enemy::SpawnEnemy()
{
	if(_spawnEffect == nullptr && !_isSpawned)
		_spawnEffect = EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth()/2 - 46, _y + _vImages[0]->getFrameHeight()/2 - 46, "monsterSpawnEffect", 6);
}

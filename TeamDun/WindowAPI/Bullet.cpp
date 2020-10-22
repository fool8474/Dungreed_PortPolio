#include "stdafx.h"
#include "Bullet.h"

HRESULT Bullet::init()
{
	_particleTimer = 0;

	return S_OK;
}

void Bullet::update()
{
	speedTypeMove();
	moveBullet();
	Animation();
	GenerateTraceParticle();
	_distance = getDistance(_startX, _startY, _x, _y);
}

void Bullet::release()
{
}

void Bullet::render(HDC hdc)
{
	if (_isFrame)
	{
		CAMERAMANAGER->FrameRender(hdc, _ig, _x, _y, _frameX, _frameY,_igAngle);
	}

	else
	{
		CAMERAMANAGER->Render(hdc, _ig, _x, _y ,_igAngle);
	}

}

void Bullet::GenerateTraceParticle()
{
	if (_useTraceParticle)
	{
		_particleTimer--;
		if (_particleTimer < 0)
		{
			particle* curParticle = PARTICLEMANAGER->AddNewParticle();
			curParticle->initParticle(
				_x + _ig->getFrameWidth()/2,					// X��ǥ�� ������ �߰�
				_y + _ig->getFrameHeight()/2,					// Y��ǥ�� ������ �߰�
				0, 0,					// ���ǵ� XY ��ȭ��
				0,						// X���ǵ� ������ �߰�
				0,						// Y���ǵ� ������ �߰�
				0,						// ������ ��ȭ��
				0,						// ������ ������ �߰�
				3,						// ���İ� ��ȭ��
				255,					// ���İ� ������ �߰�
				0,						// ũ�� XY ��ȭ��
				1,						// ũ�� X ������ �߰�
				60,						// ��ƼŬ ���� �ð��� ������ �߰�
				"SqaureParticle_5"		// �̹��� �� �ϳ��� ������ ��ƼŬ�� �Է�
			);
			_particleTimer = 4;
		}
	}
}

void Bullet::makeBullet(const char * imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle,float damage, float speed, float maxDis, bool isFrame ,float igAngle ,BULLETSPEEDTYPE speedtype, string effectSound)
{
	_ig = IMAGEMANAGER->findImage(imageName);
	_effectIgName = effectIgName;
	_type = type;
	_x = _startX = x;
	_y = _startY = y;
	_angle = angle;
	_speed = speed;
	_isFrame = isFrame;
	_frameX = 0;
	_frameY = 0; 
	_frameTimer = 0;
	_distance = getDistance(_startX, _startY, _x, _y);
	_maxDistance = maxDis;
	_igAngle = igAngle;
	_speedType = speedtype;
	_jumpPower = -1;
	_gravity = 0.3f;
	_effectSound = effectSound;
	if (_type == BT_PLAYER || _type == BT_PLAYERNOCOL)
	{
		if (_speedType == BST_CHARGE)
		{
			Player* p = ENTITYMANAGER->getPlayer();
			int Playerdamage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
			if (p->GetSpecialAbilityOn(0, 2))
			if (p->GetMaxHp() * 0.6f > p->GetHP())
			{
				if (p->GetInitHp() * 0.6f > p->GetHP())
				{
					Playerdamage = p->GetMaxDamage();
				}
			}

			_damage = Playerdamage+damage;
		}
		else
		{

			Player* p = ENTITYMANAGER->getPlayer();
			int Playerdamage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
			if (p->GetSpecialAbilityOn(0, 2))
			{
				if (p->GetInitHp() * 0.6f > p->GetHP())
				{
					Playerdamage = p->GetMaxDamage();
				}
			}

			_damage = Playerdamage;
		}
	}
	else
	{
		_damage = damage;
	}
	_isDead = false;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth(), _ig->getFrameHeight());

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth(), _ig->getHeight());
	}
}

void Bullet::moveBullet()
{
	_x += cosf(_angle)*_speed;
	_y += -sinf(_angle)*_speed;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth(), _ig->getFrameHeight());

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth(), _ig->getHeight());
	}
}

void Bullet::Animation()
{

	_frameTimer++;
	_frameY = 0;
	
	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX > _ig->getMaxFrameX())
		{
			_frameX = 0;  //�����
		}
	}
}

void Bullet::speedTypeMove()
{
	switch (_speedType)
	{
	case BST_NOMAL:
		break;
	case BST_SLOW:
		_speed -= 0.03;

		if (_speed < 0)
		{
			_isDead = true;
		}
		break;
	case BST_FAST:
		_speed += 0.1;

		
		break;
	case BST_GRAVITY:
		_y += _jumpPower;
		_jumpPower += _gravity;
		break;
	default:
		break;
	}
}



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
		CAMERAMANAGER->FrameStretchRender(hdc, _ig, _x, _y, _frameX, _frameY,_scale, _scale, _igAngle);
	}

	else
	{
		CAMERAMANAGER->StretchRender(hdc, _ig, _x, _y, _scale, _scale,_igAngle);
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
				_x + (_scale - 1) * (IMAGEMANAGER->findImage(_useTraceImage)->getFrameWidth() / 2) ,					// X좌표에 랜덤성 추가
				_y + (_scale - 1) * (IMAGEMANAGER->findImage(_useTraceImage)->getFrameHeight() / 2),					// Y좌표에 랜덤성 추가
				0, 0,					// 스피드 XY 변화량
				0,						// X스피드 랜덤성 추가
				0,						// Y스피드 랜덤성 추가
				0,						// 각도값 변화량
				0,						// 각도값 랜덤성 추가s
				_traceAlphaChanger,		// 알파값 변화량
				255,					// 알파값 랜덤성 추가
				0,						// 크기 XY 변화량
				_scale,						// 크기 X 랜덤성 추가
				60,						// 파티클 생존 시간에 랜덤성 추가
				_useTraceImage			// 이미지 중 하나를 선택해 파티클에 입력
			);
			_particleTimer = _particleTime;
		}
	}
}

void Bullet::makeBullet(const char * imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle,float damage, float speed, float maxDis, bool isFrame ,float igAngle ,BULLETSPEEDTYPE speedtype, string effectSound, bool isEffectAngle)
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
	_scale = 1;
	_useTraceImage = "SqaureParticle_5";
	_particleTime = 4;
	_traceAlphaChanger = 3;
	_angleChanger = (RANDOM->range(2) == 0 ? PI / 180.f : -PI / 180.f);
	_useWallCollision = true;
	_target = nullptr;
	_particleTimer = 0;
	_isEffectAngle = isEffectAngle;
	_isResetUid = false;
	if (_type == BT_PLAYER || _type == BT_PLAYERNOCOL)
	{
		if (_speedType == BST_CHARGE)
		{
			Player* p = ENTITYMANAGER->getPlayer();
			int Playerdamage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
			
			if (p->GetSpecialAbilityOn(0, 2))
			{
				if (p->GetMaxHp() * 0.6f > p->GetHP())
				{
					Playerdamage = p->GetMaxDamage();
				}
			}

			_damage = Playerdamage+ damage;
		}
		else
		{

			Player* p = ENTITYMANAGER->getPlayer();
			int Playerdamage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
			if (p->GetSpecialAbilityOn(0, 2))
			{
				if (p->GetMaxHp() * 0.6f > p->GetHP())
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
		_rc = RectMake(_x, _y, _ig->getFrameWidth()*_scale, _ig->getFrameHeight()*_scale);

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth()*_scale, _ig->getHeight()*_scale);
	}
}

void Bullet::moveBullet()
{
	_x += cosf(_angle)*_speed;
	_y += -sinf(_angle)*_speed;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth()*_scale, _ig->getFrameHeight()*_scale);

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth()*_scale, _ig->getHeight()*_scale);
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
			_frameX = 0;  //여기랑
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
	case BST_TRACE:
		_speed += 0.05f;
		if (!_target || _target->GetIsDead())
		{
			_angle += _angleChanger;

			float minDistance = INT_MAX;
			int minIndex = -1;
			for (int i = 0; i < MAPMANAGER->GetPlayMap()->GetObjects().size(); i++)
			{
				Object* obj = MAPMANAGER->GetPlayMap()->GetObjects()[i];
				if (obj->GetType() == OBJECTTYPE::OT_MONSTER && dynamic_cast<Enemy*>(obj)->GetIsSpawned())
				{
					float distance = getDistance(obj->GetX(), obj->GetY(), _x, _y);
					if (minDistance >= abs(distance))
					{
						minDistance = distance;
						minIndex = i;
					}
				}
			}
			if (minIndex != -1) _target = MAPMANAGER->GetPlayMap()->GetObjects()[minIndex];
		}

		else
		{
			float angle = UTIL::getAngle(_x, _y, _target->GetX(), _target->GetY());
			if (abs(angle - _angle) > PI / 15)
			{
				if (angle > _angle) _angle += PI / 30;
				else _angle -= PI / 30;
			}
		}
		break;
	case BST_RETURN:
		_speed -= 0.5f;
		if (_isResetUid == false)
		{
			if (_speed < 0)
			{
				_angle = UTIL::getAngle(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), _x, _y);
				_isResetUid = true;
				_vUid.clear();
			}
		}
		
		break;
	
	default:
		break;
	}
}



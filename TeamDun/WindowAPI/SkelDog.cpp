#include "stdafx.h"
#include "SkelDog.h"

HRESULT SkelDog::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 60, 54);
	_state = ES_IDLE;
	_frameX, _frameY = 0;
	_damage = 6;
	_count = _index = _jumpCount = 0;
	_initHp = _hp = 30;
	_gravity = 0.4f;
	_jumpPower = 7.0f;
	_attackCoolTime = RANDOM->range(50) + 30;
	_isAttack = _isJump = false;
	_jumpTimer = 80 + RANDOM->range(50);
	_randomXPos = RANDOM->range(-100, 100);
	_randomXPosTimer = RANDOM->range(30) + 70;
	return S_OK;
}

void SkelDog::update()
{
	Enemy::update();

	this->Move();
	this->Attack();
	this->Animation();
	this->pixelCollision();

	_jumpTimer--;

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200)
			{
				_state = ES_MOVE;
			}
			break;

		case ES_MOVE:

			_body = RectMake(_x, _y, 60, 54);
			_randomXPosTimer--;

			if (abs(ENTITYMANAGER->getPlayer()->GetX() + _randomXPos - _x) < 10 || _randomXPosTimer < 0) // ���� ��ǥ�� �Ÿ� 10 ���ϸ� ���� ��ǥ ������
			{
				_randomXPos = RANDOM->range(-200, 200);
				_randomXPosTimer = RANDOM->range(30) + 70;
			}

			else // �Ÿ� 10 �̻� -> ��ȣ�� ���� �¿� �� �̵� ����
			{
				if (ENTITYMANAGER->getPlayer()->GetX() + _randomXPos - _x > 0) 
				{
					_isLeft = true;
					_x += 4;
					_body = RectMake(_x, _y, 60, 54);
				}

				else
				{
					_isLeft = false;
					_x -= 4;
					_body = RectMake(_x, _y, 60, 54);
				}
			}

			if (ENTITYMANAGER->getPlayer()->GetX() - 70 < _x && ENTITYMANAGER->getPlayer()->GetX() + 70 > _x)
			{
				_attackCoolTime--;

				if (_attackCoolTime < 0)
				{
					_isAttack = true;
					_attackCoolTime = RANDOM->range(50) + 40;
				}

				if (_isAttack)
				{
					_state = ES_ATTACK;

					if (_x < ENTITYMANAGER->getPlayer()->GetX() + 20)
					{
						_isLeft = true;
					}
					else
					{
						_isLeft = false;
					}
				}
			}
			break;
		case ES_ATTACK:
			RECT temp;
			//�浹ó��
		
			if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
			{
				ENTITYMANAGER->getPlayer()->GetHitDamage(_damage);
			}


			if (_isLeft && _frameX >= _vImages[_useImage]->getMaxFrameX())
			{
				if (_count % 5 == 0)
				{
					_state = ES_IDLE;
					_isAttack = false;
				}
			}
			else if (!_isLeft && _frameX <= 0)
			{
				if (_count % 5 == 0)
				{
					_state = ES_IDLE;
					_isAttack = false;
				}
			}
			break;
		default:
			break;
		}
	}
}

void SkelDog::release()
{
	Enemy::release();
}

void SkelDog::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void SkelDog::Move()
{
	Enemy::Move();

	_body = RectMake(_x, _y, 60, 54);
}

void SkelDog::Attack()
{
	Enemy::Attack();

	if (abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 200 && abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && _isAttack)
	{
		if (_jumpTimer < 0)
		{
			_jumpTimer = 50 + RANDOM->range(30);
			if (_jumpCount == 0)
			{
				_jumpPower = 10;
				_y -= _jumpPower;
				_probeBottom = _y + IMAGEMANAGER->findImage("SkelDogIdle")->getFrameHeight();
				_jumpCount++;
			}
		}
	}
}

void SkelDog::Animation()
{
	Enemy::Animation();
	_count++;

	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{
			_frameY = 1;
			if (_count % 5 == 0)
			{
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count % 5 == 0)
			{
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		break;
	case ES_MOVE:
		_useImage = 1;
		if (_isLeft)
		{
			_frameY = 0;
			if (_count % 5 == 0)
			{
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_frameY = 1;
			if (_count % 5 == 0)
			{
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	case ES_ATTACK:
		_useImage = 1;
		if (_isLeft)
		{
			_frameY = 0;
			if (_count % 5 == 0)
			{
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_frameY = 1;
			if (_count % 5 == 0)
			{
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	default:
		break;
	}
}

void SkelDog::pixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;


	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* SkelDogIdle = IMAGEMANAGER->findImage("SkelDogIdle");

	_probeBottom = _y + SkelDogIdle->getFrameHeight();

	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + 11, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			isCollide = true;
			_isJump = false;
			_jumpPower = -2;

			_y = i - _vImages[_useImage]->getFrameHeight();
			_jumpCount = 0;

			break;
		}
		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
		{
			isCollide = true;
			_jumpPower = -2;

			_y = i - _vImages[_useImage]->getFrameHeight();
			_jumpCount = 0;
			break;
		}
	}
	if (_isLeft)
	{

		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + SkelDogIdle->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - SkelDogIdle->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - SkelDogIdle->getFrameHeight();
				_jumpCount = 0;
				break;
			}
		}
	}
	else
	{
		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _vImages[_useImage]->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - _vImages[_useImage]->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - _vImages[_useImage]->getFrameHeight();

				_jumpCount = 0;
				break;
			}
		}
	}

	for (int i = _y + 15; i > _y - 4; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _vImages[_useImage]->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_jumpPower = -2;
			_y = i + 5;
			break;
		}
	}
	if (!isCollide)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
		_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	}

	for (int i = _x + SkelDogIdle->getFrameWidth() - 15; i < _x + SkelDogIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;

			if (_RightCollision1 &&_RightCollision2)
			{
				_x = i - SkelDogIdle->getFrameWidth();
			}
			break;
		}

	}
	for (int i = _x + SkelDogIdle->getFrameWidth() - 15; i < _x + SkelDogIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 50);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;
			_x = i - SkelDogIdle->getFrameWidth();
			break;
		}
	}
	for (int i = _x + SkelDogIdle->getFrameWidth() - 15; i < _x + SkelDogIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i - SkelDogIdle->getFrameWidth();
			break;
		}
	}

	//���ʾƷ�
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision1 = true;

			if (_leftCollision1 &&_leftCollision2)
			{
				_x = i + 5 ;
			}
			break;
		}
	}
	//�����߰�
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 50);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision2 = true;
			_x = i + 5;

			break;
		}
	}
	//������
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i + 5;

			break;
		}
	}
}

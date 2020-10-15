#include "stdafx.h"
#include "Belial.h"

HRESULT Belial::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_angle = 0;
	_state = ES_IDLE;
	_PatternTime = 0;
	_bulletFireTimer = 0;
	_fireAngle = 0;
	_bossBack = IMAGEMANAGER->findImage("SkellBossBack");
	_playerY1 = 0;
	_playerY2 = 0;

	_firstSwordX = 20;
	_firstSwordY = 200;
	_makeSwordTimer = 0;
	_swordCount = 0;
	_swordEndCount = 0;
	_makeSword = false;
	_shootSword = false;
	_shootSwordTimer = 0;

	_RazerCount = 0;
	_RazerEnd = false;
	_RazerEndCount = 0;


	_initHp = _HP = 800;
	_Damage = 10; //阂房措固瘤


	_leftHandle.ig = IMAGEMANAGER->findImage("SkellBossLeftHandIdle");
	_leftHandle.frameX = 0;
	_leftHandle.frameY = 0;
	_leftHandle.Timer = 0;
	_leftHandle.state = ES_IDLE;

	_RightHandle.ig = IMAGEMANAGER->findImage("SkellBossRightHandIdle");
	_RightHandle.frameX = 0;
	_RightHandle.frameY = 0;
	_RightHandle.Timer = 0;
	_RightHandle.state = ES_IDLE;
	return S_OK;
}

void Belial::SetAfterSpawn()
{
	_leftHandle.x = _x - 288;
	_leftHandle.y = _y + 200;

	_RightHandle.x = _x + 370;
	_RightHandle.y = _y;

	_leftHandle.CenterX = _leftHandle.x + _leftHandle.ig->getFrameWidth() / 2;
	_leftHandle.CenterY = _leftHandle.y + _leftHandle.ig->getFrameHeight() / 2;
	_RightHandle.CenterX = _RightHandle.x + _leftHandle.ig->getFrameWidth() / 2;
	_RightHandle.CenterY = _RightHandle.y + _leftHandle.ig->getFrameHeight() / 2;
}

void Belial::update()
{
	Enemy::update();
	
	if (_isSpawned)
	{
		Animation();
		switch (_state)
		{
		case ES_IDLE:
			_PatternTime++;
			if (_PatternTime > 300)
			{
				SetPattern();
			}
			Move();


			break;
		case ES_ATTACK:

			Attack();
			switch (_BelialPattern)
			{

			case RAZER:
				Move();
				break;
			case KNIFE:
				Move();
				break;
			case BULLET:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Belial::release()
{
}

void Belial::render(HDC hdc)
{
	if (_isSpawned)
	{
		if (_BelialPattern == BULLET && _state == ES_ATTACK)
		{
		CAMERAMANAGER->FrameRender(hdc, _bossBack, _x+53, _y+ 215, _frameX, 0);
		}
		else
		{
		CAMERAMANAGER->FrameRender(hdc, _bossBack, _x+53, _y+ 135, _frameX, 0);
		}
		for (int i = 0; i < _vBossSword.size(); i++)
		{
			CAMERAMANAGER->StretchRender(hdc, _vBossSword[i]->ig, _vBossSword[i]->x,_vBossSword[i]->y,3,3,-_vBossSword[i]->angle + PI/2);	
		}
		
		Enemy::render(hdc);
		CAMERAMANAGER->FrameRender(hdc, _leftHandle.ig, _leftHandle.x, _leftHandle.y, _leftHandle.frameX, _leftHandle.frameY);
		CAMERAMANAGER->FrameRender(hdc, _RightHandle.ig, _RightHandle.x, _RightHandle.y, _RightHandle.frameX, _RightHandle.frameY);
		for (int i = 0; i < _vLeftRazer.size(); i++)
		{
			CAMERAMANAGER->FrameRender(hdc, _vLeftRazer[i]->ig, _vLeftRazer[i]->x, _vLeftRazer[i]->y, _leftHandle.frameX-8, 0);
		}
		for (int i = 0; i < _vRightRazer.size(); i++)
		{
			CAMERAMANAGER->FrameRender(hdc, _vRightRazer[i]->ig, _vRightRazer[i]->x, _vRightRazer[i]->y, _RightHandle.frameX - 8, 0);
		}
	}
}



void Belial::Move()
{
	_angle += 0.1f;
	_y += cosf(_angle) * 1;
}

void Belial::Attack()
{
	

	switch (_BelialPattern)
	{
	case RAZER:
		
		_RazerCount++;

		if (_RazerCount == 100)
		{
			_playerY1 = (float)ENTITYMANAGER->getPlayer()->GetY()-50;
			_leftHandle.state = ES_ATTACK;
			_leftHandle.Timer = 0;
			_leftHandle.frameX = 0;
			_leftHandle.ig = IMAGEMANAGER->findImage("SkellBossLeftHandAttack");
		}
		if (_RazerCount >= 100 && _RazerCount < 150)
		{
			_leftHandle.y = MoveLerp(_leftHandle.y, _playerY1, 0.1f);
		}
		if (_RazerCount == 200)
		{
			_playerY2 = (float)ENTITYMANAGER->getPlayer()->GetY()-50;
			_RightHandle.state = ES_ATTACK;
			_RightHandle.Timer = 0;
			_RightHandle.ig = IMAGEMANAGER->findImage("SkellBossRightHandAttack");
			_RightHandle.frameX = 0;

		}
		if (_RazerCount > 200 && _RazerCount < 250)
			_RightHandle.y = MoveLerp(_RightHandle.y, _playerY2, 0.1f);
		if (_RazerCount == 300)
		{
			_playerY1 = (float)ENTITYMANAGER->getPlayer()->GetY()-50	;
			_leftHandle.state = ES_ATTACK;
			_leftHandle.Timer = 0;
			_leftHandle.frameX = 0;
			_leftHandle.ig = IMAGEMANAGER->findImage("SkellBossLeftHandAttack");
			_RazerEnd = true;
		}
		if (_RazerCount > 300 && _RazerCount < 350)
			_leftHandle.y = MoveLerp(_leftHandle.y, _playerY1, 0.1f);
		if (_RazerEnd)
		{
			_RazerEndCount++;
			if (_RazerEndCount > 100)
			{
				_RazerCount = 0;
				_RazerEndCount = 0;
				_state = ES_IDLE;
				_RazerEnd = false;
			}
		}
		switch (_leftHandle.state)
		{
		case ES_IDLE:
			break;
		case ES_ATTACK:
			

			break;
		default:
			break;
		}


		break;
	case KNIFE:
		
		if (_makeSword)
		{
			SetSwordAngle();
			
			_makeSwordTimer++;
			if (_makeSwordTimer > 20)
			{
				_makeSwordTimer = 0;
				_firstSwordX += 100;
				

				_swordCount++;
				SetSword();

				if (_swordCount == 6)
				{
					_makeSword = false;
					_shootSword = true;

					_firstSwordX = 100;
					_firstSwordY = 200;
					_swordCount = 0;
				}
			}
		}
		if (_shootSword)
		{
			_shootSwordTimer++;
			for (int i = 0; i < _vBossSword.size(); i++)
			{
				if (_vBossSword[i]->speed == 0 &&_vBossSword[i]->isCol == false)
				{
					_vBossSword[i]->angle = getAngle(_vBossSword[i]->x + _vBossSword[i]->ig->getFrameWidth()*3 / 2, _vBossSword[i]->y + _vBossSword[i]->ig->getFrameHeight()*3 / 2, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY());
					if (_vBossSword[i]->angle < 0)
					{
						_vBossSword[i]->angle += PI2;
					}
					if (_vBossSword[i]->angle >= PI2)
					{
						_vBossSword[i]->angle -= PI2;
					}
					
				}
				_vBossSword[i]->x += cosf(_vBossSword[i]->angle)*_vBossSword[i]->speed;
				_vBossSword[i]->y += -sinf(_vBossSword[i]->angle)*_vBossSword[i]->speed;
				_vBossSword[i]->body = RectMakeCenter(_vBossSword[i]->x+ _vBossSword[i]->ig->getFrameWidth() *3/2 , _vBossSword[i]->y+ _vBossSword[i]->ig->getFrameHeight() * 3/2,
										_vBossSword[i]->ig->getFrameWidth()*2, _vBossSword[i]->ig->getFrameHeight()*2);

			}

			if (_shootSwordTimer > 20)
			{
				_shootSwordTimer = 0;
				for (int i = 0; i < _vBossSword.size(); i++)
				{
					
					if (_vBossSword[i]->speed == 0 && _vBossSword[i]->isCol == false)
					{
						_vBossSword[i]->ig = IMAGEMANAGER->findImage("SkellBossSwordFire");
						_vBossSword[i]->speed = 25;
						break;
					}
				}
			}


			SwordHit();
			SwordPixelCollision();
			EraseSword();
			if (_swordEndCount == 6)
			{
				_swordEndCount = 0;
				_state = ES_IDLE;
				_shootSword = false;
			}
		}
		break;
	case BULLET:
		_bulletFireTimer++;
		_bulletEndTimer++;
		if (_bulletFireTimer > 12)
		{	
			_fireAngle += PI / 24;
			for (int i = 0; i < 4; i++)
			{
				ENTITYMANAGER->makeBullet("BossBullet","BossBulletEffect", BT_NOMAL, _x + 110, _y + 270, _fireAngle + i * PI / 2,_Damage, 4, 1000, true);
			}
			_bulletFireTimer = 0;
		}
		if (_bulletEndTimer > 300)
		{
			_bulletEndTimer = 0;
			_state = ES_IDLE;
		}
		break;
	default:
		break;
	}
}

void Belial::Animation()
{
	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;

		_count++;

		_frameY = 0;
		if (_count > 3)
		{
			_count = 0;
			_frameX++;
			if (_frameX > _vImages[_useImage]->getMaxFrameX())
			{
				_frameX = 0;

			}
		}
		break;
	case ES_MOVE:
		break;
	case ES_ATTACK:
		switch (_BelialPattern)
		{
		case RAZER:
			_useImage = 0;

			_count++;

			_frameY = 0;
			if (_count > 3)
			{
				_count = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
			break;
		case KNIFE:
			_useImage = 0;

			_count++;

			_frameY = 0;
			if (_count > 3)
			{
				_count = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
			break;
		case BULLET:
			_useImage = 1;

			_count++;

			_frameY = 0;
			if (_count > 3)
			{
				_count = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = _vImages[_useImage]->getMaxFrameX() -4;
				}
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	switch (_leftHandle.state)
	{
	case ES_IDLE:
		_leftHandle.Timer++;
		if (_leftHandle.Timer > 5)
		{
			_leftHandle.Timer = 0;
			_leftHandle.frameX++;
			
			if (_leftHandle.frameX > _leftHandle.ig->getMaxFrameX())
			{
				_leftHandle.frameX = 0;
			}
		}
		break;
	case ES_ATTACK:
		_leftHandle.Timer++;
		if (_leftHandle.Timer > 7)
		{
			_leftHandle.Timer = 0;
			_leftHandle.frameX++;
			if (_leftHandle.frameX == 8)
			{
				for (int i = 0; i < 8; i++)
				{
					Razer* razer = new Razer;
					razer->ig = IMAGEMANAGER->findImage("SkellBossLaserBody");
					razer->x = 200+ _leftHandle.x +razer->ig->getFrameWidth() * i;
					razer->y = _leftHandle.y+50;
					razer->body = RectMake(razer->x, razer->y, razer->ig->getFrameWidth(), razer->ig->getFrameHeight());

					_vLeftRazer.push_back(razer);
				}
				EFFECTMANAGER->AddEffect(_leftHandle.x + 200 - IMAGEMANAGER->findImage("SkellBossLaserHead")->getFrameWidth(), _leftHandle.y + 60, "SkellBossLaserHead", 7);
			}
			if(_leftHandle.frameX == 9)
			{
				for (int i = 0; i < _vLeftRazer.size(); i++)
				{
					EFFECTMANAGER->AddEffect(_vLeftRazer[i]->x, _vLeftRazer[i]->y, "SkellBossLaserBody", 7, 2, 0);
				}
				_vLeftRazer.clear();
			}
			if (_leftHandle.frameX > _leftHandle.ig->getMaxFrameX())
			{
				_leftHandle.ig = IMAGEMANAGER->findImage("SkellBossLeftHandIdle");
				_leftHandle.state = ES_IDLE;
				_leftHandle.frameX = 0;
			}
		}
		RECT temp;
		//面倒贸府
		for (int i = 0; i < _vLeftRazer.size(); i++)
		{
			if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_vLeftRazer[i]->body))
			{
				if (ENTITYMANAGER->getPlayer()->GetIsHit() == false)
				{
					float damage;
					float block;
					float evasion;

					damage = 15 * ENTITYMANAGER->getPlayer()->GetRealDefence() / 100;
					evasion = RANDOM->range(100);
					block = RANDOM->range(100);
					if (ENTITYMANAGER->getPlayer()->GetRealEvasion() <= evasion)
					{
						if (ENTITYMANAGER->getPlayer()->GetBlock() <= block)
						{
							ENTITYMANAGER->getPlayer()->SetIsHit(true);
							ENTITYMANAGER->getPlayer()->SetHitCount(0);
							ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() - damage);
						}
					}
				}


			}
		}
		break;
	default:
		break;
	}

	switch (_RightHandle.state)
	{
	case ES_IDLE:
		_RightHandle.Timer++;
		if (_RightHandle.Timer > 5)
		{
			_RightHandle.Timer = 0;
			_RightHandle.frameX++;
			
			if (_RightHandle.frameX > _RightHandle.ig->getMaxFrameX())
			{
				_RightHandle.frameX = 0;
			}
		}
		break;

	case ES_ATTACK:
		_RightHandle.Timer++;
		if (_RightHandle.Timer >7)
		{
			_RightHandle.Timer = 0;
			_RightHandle.frameX++;
			if (_RightHandle.frameX == 8)
			{
				for (int i = 0; i < 8; i++)
				{
					Razer* razer = new Razer;
					razer->ig = IMAGEMANAGER->findImage("SkellBossLaserBody");
					razer->x =-81+_RightHandle.x - razer->ig->getFrameWidth() * (i);
					razer->y = _RightHandle.y + 50;
					razer->body = RectMake(razer->x, razer->y, razer->ig->getFrameWidth(), razer->ig->getFrameHeight());

					_vRightRazer.push_back(razer);
				}
				EFFECTMANAGER->AddEffect(_RightHandle.x , _RightHandle.y + 62, "SkellBossLaserHead", 7, 0, 1);
			}
			if (_RightHandle.frameX == 9)
			{
				for (int i = 0; i < _vRightRazer.size(); i++)
				{
					EFFECTMANAGER->AddEffect(_vRightRazer[i]->x, _vRightRazer[i]->y, "SkellBossLaserBody", 7, 2, 0);
				}
				_vRightRazer.clear();
			}
			
			if (_RightHandle.frameX > _RightHandle.ig->getMaxFrameX())
			{
				_RightHandle.ig = IMAGEMANAGER->findImage("SkellBossRightHandIdle");
				_RightHandle.state = ES_IDLE;
				_RightHandle.frameX = 0;
			}
		}
		
		RECT temp;
		//面倒贸府
		for (int i = 0; i <_vRightRazer.size(); i++)
		{
			if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_vRightRazer[i]->body))
			{
				if (ENTITYMANAGER->getPlayer()->GetIsHit() == false)
				{
					float damage;
					float block;
					float evasion;

					damage = 15 * ENTITYMANAGER->getPlayer()->GetRealDefence() / 100;
					evasion = RANDOM->range(100);
					block = RANDOM->range(100);
					if (ENTITYMANAGER->getPlayer()->GetRealEvasion() <= evasion)
					{
						if (ENTITYMANAGER->getPlayer()->GetBlock() <= block)
						{
							ENTITYMANAGER->getPlayer()->SetIsHit(true);
							ENTITYMANAGER->getPlayer()->SetHitCount(0);
							ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() - damage);
						}
					}
				}


			}
		}
		break;
	default:
		break;
	}
}

void Belial::SetPattern()
{
	int rndPatten = RANDOM->range(0, 2);
	switch (rndPatten)
	{
	case 0:
		_state = ES_ATTACK;
		_BelialPattern = RAZER;
		_frameX = 0;
		break;
	case 1:
		_state = ES_ATTACK;
		_BelialPattern = KNIFE;
		_frameX = 0;
		_makeSword = true;
		break;
	case 2:
		_state = ES_ATTACK;
		_BelialPattern = BULLET;
		_frameX = 0;
		break;

	default:
		break;
	}
	_BelialPattern = (BELIALPATTERN)rndPatten;

}

float Belial::MoveLerp(float y1, float y2, float amount)
{
	return y1 + (y2 - y1)*amount;	

}

void Belial::SetSword()
{
	BossSword* _sword = new BossSword;
	_sword->ig = IMAGEMANAGER->findImage("SkellBossSword0");
	_sword->x = _firstSwordX;
	_sword->y = _firstSwordY;
	_sword->body = RectMake(_sword->x, _sword->y, _sword->ig->getFrameWidth()*3, _sword->ig->getFrameHeight()*3);
	_sword->isDead = false;
	_sword->isCol = false;
	_sword->isHit = false;
	_sword->speed = 0;	
	_sword->Timer = 0;

	_vBossSword.push_back(_sword);
}

void Belial::SwordHit()
{

	Player* _p = ENTITYMANAGER->getPlayer();
	RECT temp;
	//面倒贸府
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		if (IntersectRect(&temp, &_p->GetBody(), &_vBossSword[i]->body))
		{
			if (_vBossSword[i]->speed > 0 && _vBossSword[i]->isHit == false)
			{
				if (_p->GetIsHit() == false)
				{
					_vBossSword[i]->isHit = true;
					float damage;
					float block;
					float evasion;

					damage = 15 * _p->GetRealDefence() / 100;
					evasion = RANDOM->range(100);
					block = RANDOM->range(100);
					if (_p->GetRealEvasion() <= evasion)
					{
						if (_p->GetBlock() <= block)
						{
							_p->SetIsHit(true);
							_p->SetHitCount(0);
							_p->SetHp(_p->GetHP() - damage);
						}
					}
				}

			}
		}
	}
}



void Belial::SetSwordAngle()
{
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		_vBossSword[i]->angle = getAngle(_vBossSword[i]->x + _vBossSword[i]->ig->getFrameWidth()*3 / 2, _vBossSword[i]->y + _vBossSword[i]->ig->getFrameHeight()*3/ 2, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY());
		if (_vBossSword[i]->angle < 0)
		{
			_vBossSword[i]->angle += PI2;
		}
		if (_vBossSword[i]->angle >= PI2)
		{
			_vBossSword[i]->angle -= PI2;
		}
	}
}

void Belial::SwordPixelCollision()
{
	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* _image = IMAGEMANAGER->findImage("SkellBossSword0");
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		COLORREF color1 = GetFastPixel(MAPMANAGER->GetPixelGetter(), _vBossSword[i]->x + _image->getFrameWidth()*3/2+cosf(_vBossSword[i]->angle)*60 , _vBossSword[i]->y + _image->getFrameHeight()*3 / 2-sinf(_vBossSword[i]->angle) * 60);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			if (_vBossSword[i]->speed != 0)
			{
				_vBossSword[i]->speed = 0;
				_vBossSword[i]->ig = IMAGEMANAGER->findImage("SkellBossSword0");
				_vBossSword[i]->isCol = true;

				if (_vBossSword[i]->angle > PI / 4 && _vBossSword[i]->angle <= PI - PI / 4)
				{
					EFFECTMANAGER->AddEffect(_vBossSword[i]->x , _vBossSword[i]->y + _image->getFrameHeight()*3 / 2, "BossSwordHitUp", 3);
				}
				else if (_vBossSword[i]->angle > PI - PI / 4 && _vBossSword[i]->angle <= PI + PI / 4)
				{

					EFFECTMANAGER->AddEffect(_vBossSword[i]->x + _image->getFrameWidth()*3 / 2, _vBossSword[i]->y + _image->getFrameHeight()*3 / 2, "BossSwordHitLeft", 3);
				}
				else if (_vBossSword[i]->angle > PI + PI / 4 && _vBossSword[i]->angle <= PI2 - PI / 4)
				{

					EFFECTMANAGER->AddEffect(_vBossSword[i]->x+ 30, _vBossSword[i]->y + _image->getFrameHeight()*3 / 2, "BossSwordHitDown", 3);
				}
				else
				{
					EFFECTMANAGER->AddEffect(_vBossSword[i]->x + _image->getFrameWidth()*3 / 2, _vBossSword[i]->y + _image->getFrameHeight()*3 / 2, "BossSwordHitRight", 3);

				}
				
			}
		}
	}

}

void Belial::EraseSword()
{
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		if (_vBossSword[i]->isCol == true)
		{
			_vBossSword[i]->Timer++;

			if (_vBossSword[i]->Timer == 150)
			{
				_vBossSword.erase(_vBossSword.begin() + i);

				_swordEndCount++;
			}
		}
	}
}

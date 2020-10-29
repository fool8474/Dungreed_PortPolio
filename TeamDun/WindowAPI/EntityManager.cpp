#include "stdafx.h"
#include "EntityManager.h"

HRESULT EntityManager::init()
{
	_vObjs = vector<Object*>();
	_vBullets = vector<Bullet*>();
	_p = nullptr;

	for (int i = 0; i < _vBullets.size(); i++)
	{
		_vBullets[i]->init();
	}

	_wormVillage = new WormVillage(*dynamic_cast<WormVillage*>(DATAMANAGER->GetObjectById(2501)));

	return S_OK;
}

void EntityManager::update()
{

	for (int i = 0; i < _vObjs.size(); i++) _vObjs[i]->update();
	for (int i = 0; i < _vBullets.size(); i++) _vBullets[i]->update();

	eraseBullet();

	_wormVillage->update();
	_p->update();
	HitBullet();
}

void EntityManager::render(HDC hdc)
{
	_wormVillage->render(hdc);
	for (int i = 0; i < _vObjs.size(); i++) _vObjs[i]->render(hdc);
	for (int i = 0; i < _vBullets.size(); i++) _vBullets[i]->render(hdc);
	_p->render(hdc);
}

void EntityManager::release()
{

	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->release();
		SAFE_DELETE(_vObjs[i]);
	}

	for (int i = 0; i < _vBullets.size(); i++)
	{
		_vBullets[i]->release();
		SAFE_DELETE(_vBullets[i]);
	}
}

Bullet* EntityManager::makeBullet(const char* imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle, float damage, float speed, float maxDis, bool isFrame, float igAngle, BULLETSPEEDTYPE speedtype, string effectSound ,bool isEffectAngle)
{
	Bullet* _bullet = new Bullet;
	_bullet->makeBullet(imageName, effectIgName, type, x, y, angle, damage, speed, maxDis, isFrame, igAngle, speedtype, effectSound, isEffectAngle);
	_bullet->SetUseTraceParticle(false);
	_vBullets.push_back(_bullet);
	return _bullet;
}

void EntityManager::eraseBullet()
{

	image* batBulletIg = IMAGEMANAGER->findImage("BatBullet");
	image* BansheeBulletIg = IMAGEMANAGER->findImage("BansheeBulletIdle");


	for (int i = 0; i < _vBullets.size(); i++)
	{
		if (_vBullets[i]->getDis() >= _vBullets[i]->getMaxDis())
		{
			if (_vBullets[i]->getIsEffectAngle())
			{
				if (_vBullets[i]->getSpeedType() == BST_GRAVITY)
				{
					EFFECTMANAGER->AddEffect(_vBullets[i]->getX(), _vBullets[i]->getY(), _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound(), _vBullets[i]->getDamage(), true);
					_vBullets[i]->SetIsDead(true);
				}
				else if (_vBullets[i]->getSpeedType() == BST_RETURN)
				{
					_vBullets[i]->SetIsDead(true);
				}
				else
				{
					EFFECTMANAGER->AddEffect(_vBullets[i]->getX(), _vBullets[i]->getY(), _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound());
					_vBullets[i]->SetIsDead(true);
				}
			}
			else
			{
				if (_vBullets[i]->getSpeedType() == BST_GRAVITY)
				{
					EFFECTMANAGER->AddEffect(_vBullets[i]->getX(), _vBullets[i]->getY(), _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound(), _vBullets[i]->getDamage(), true,false);
					_vBullets[i]->SetIsDead(true);
				}
				else if (_vBullets[i]->getSpeedType() == BST_RETURN)
				{
					_vBullets[i]->SetIsDead(true);
				}
				else
				{
					EFFECTMANAGER->AddEffect(_vBullets[i]->getX(), _vBullets[i]->getY(), _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound() , 0,false,false);
					_vBullets[i]->SetIsDead(true);
				}
			}
			
		}
	}

	//총알 레이어 1벽과 충돌체크
	for (int i = 0; i < _vBullets.size(); i++)
	{
		if (_vBullets[i]->getType() == BT_NOMAL || _vBullets[i]->getType() == BT_PLAYER)
		{
			if (_vBullets[i]->getUseWallCollision())
			{
				COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _vBullets[i]->getX() + (_vBullets[i]->getIg()->getFrameWidth() + _vBullets[i]->getScale()) / 2
					, _vBullets[i]->getY() + (_vBullets[i]->getIg()->getFrameHeight() + _vBullets[i]->getScale()) / 2);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if ((r == 255 && g == 0 && b == 0))
				{
					if (_vBullets[i]->getIsEffectAngle())
					{
						if (_vBullets[i]->getSpeedType() == BST_GRAVITY)
						{
							EFFECTMANAGER->AddEffect(_vBullets[i]->getX() + (_vBullets[i]->getIg()->getFrameWidth() + _vBullets[i]->getScale()) / 2
								, _vBullets[i]->getY() + (_vBullets[i]->getIg()->getFrameHeight() + _vBullets[i]->getScale()) / 2, _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound(), _vBullets[i]->getDamage(), true);
							_vBullets[i]->SetIsDead(true);
						}
						else
						{

							EFFECTMANAGER->AddEffect(_vBullets[i]->getX() + (_vBullets[i]->getIg()->getFrameWidth() + _vBullets[i]->getScale()) / 2
								, _vBullets[i]->getY() + (_vBullets[i]->getIg()->getFrameHeight() + _vBullets[i]->getScale()) / 2, _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound());
							_vBullets[i]->SetIsDead(true);
						}
					}
					else
					{
						if (_vBullets[i]->getSpeedType() == BST_GRAVITY)
						{
							EFFECTMANAGER->AddEffect(_vBullets[i]->getX() + (_vBullets[i]->getIg()->getFrameWidth() + _vBullets[i]->getScale()) / 2
								, _vBullets[i]->getY() + (_vBullets[i]->getIg()->getFrameHeight() + _vBullets[i]->getScale()) / 2, _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound(), _vBullets[i]->getDamage(), true ,false);
							_vBullets[i]->SetIsDead(true);
						}
						else
						{

							EFFECTMANAGER->AddEffect(_vBullets[i]->getX() + (_vBullets[i]->getIg()->getFrameWidth() + _vBullets[i]->getScale()) / 2
								, _vBullets[i]->getY() + (_vBullets[i]->getIg()->getFrameHeight() + _vBullets[i]->getScale()) / 2, _vBullets[i]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[i]->getAngle(), 1, 1, false, false, true, _vBullets[i]->getEffectSound(), 0, false, false);
							_vBullets[i]->SetIsDead(true);
						}
					}
					

				}
			}
		}
	}



	for (int i = 0; i < _vBullets.size(); i++)
	{
		if (_vBullets[i]->getIsDead() == true)
		{
			_vBullets.erase(_vBullets.begin() + i);
		}
	}
}

void EntityManager::HitBullet()
{

	RECT temp;
	for (int i = 0; i < _vBullets.size(); i++)
	{
		if (_vBullets[i]->getType() == BT_NOCOL || _vBullets[i]->getType() == BT_NOMAL)
		{

			if (IntersectRect(&temp, &_p->GetBody(), &_vBullets[i]->getRc()))
			{
				_vBullets[i]->SetIsDead(true);
				_p->GetHitDamage(_vBullets[i]->getDamage());
			}
		}
	}


	for (int i = 0; i < MAPMANAGER->GetPlayMap()->GetObjects().size(); i++)
	{
		Object* curObj = MAPMANAGER->GetPlayMap()->GetObjects()[i];
		if ((curObj->GetType() == OBJECTTYPE::OT_MONSTER || curObj->GetType() == OBJECTTYPE::OT_BREAKABLE))
		{
			for (int j = 0; j < _vBullets.size(); j++)
			{
				if (_vBullets[j]->getType() == BT_PLAYER || _vBullets[j]->getType() == BT_PLAYERNOCOL)
				{
					
					if (_vBullets[j]->getSpeedType() == BST_GRAVITY)
					{
						if (IntersectRect(&temp, &_vBullets[j]->getRc(), &curObj->GetBody()))
						{

							if (!curObj->GetIsDead())
							{
								if (curObj->GetType() == OBJECTTYPE::OT_MONSTER)
								{
									if (dynamic_cast<Enemy*>(curObj)->GetIsSpawned())
									{
										if (_vBullets[j]->getIsEffectAngle())
										{
											EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound(), _vBullets[j]->getDamage(), true);
										}
										else
										{
											EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound(), _vBullets[j]->getDamage(), true ,false);
										}
										_vBullets[j]->SetIsDead(true);
										MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
									}
								}
								else
								{
									if (_vBullets[j]->getIsEffectAngle())
									{
										EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound(), _vBullets[j]->getDamage(), true);

									}
									else
									{
										EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound(), _vBullets[j]->getDamage(), true ,false);
									}
									_vBullets[j]->SetIsDead(true);
									MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
								}
							}
							break;
						}
					}
					else if (_vBullets[j]->getSpeedType() == BST_RETURN)
					{
						if (IntersectRect(&temp, &_vBullets[j]->getRc(), &curObj->GetBody()))
						{
							if (!curObj->GetIsDead())
							{
								if (curObj->GetType() == OBJECTTYPE::OT_MONSTER)
								{
									if (dynamic_cast<Enemy*>(curObj)->GetIsSpawned())
									{
										if (_vBullets[j]->getSUid().size() != 0)
										{

											bool  isFinded = false;
											for (int k = 0; k < _vBullets[j]->getSUid().size(); k++)
											{
												if (MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetUid() == _vBullets[j]->getSUid()[k])
												{
													isFinded = true;
													
													break;
												}
											}

											if (!isFinded)
											{
												_vBullets[j]->getSUid().push_back(MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetUid());
												MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
											}
										}
										else
										{
											_vBullets[j]->getSUid().push_back(MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetUid());
											
											MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
										}

									}
								}
								else
								{
									if (_vBullets[j]->getSUid().size() != 0)
									{

										bool  isFinded = false;
										for (int k = 0; k < _vBullets[j]->getSUid().size(); k++)
										{
											if (MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetUid() == _vBullets[j]->getSUid()[k])
											{
												isFinded = true;

												break;
											}
										}

										if (!isFinded)
										{
											_vBullets[j]->getSUid().push_back(MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetUid());
											MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
										}
									}
									else
									{
										_vBullets[j]->getSUid().push_back(MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetUid());
										
										MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
									}
								}
							}
							break;
						}
					}
					else
					{
						if (IntersectRect(&temp, &_vBullets[j]->getRc(), &curObj->GetBody()))
						{

							if (!curObj->GetIsDead())
							{
								if (curObj->GetType() == OBJECTTYPE::OT_MONSTER)
								{
									if (dynamic_cast<Enemy*>(curObj)->GetIsSpawned())
									{
										if (_vBullets[j]->getIsEffectAngle())
										{
											EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound());

										}
										else
										{
											EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound(), 0 , false, false);

										}
										_vBullets[j]->SetIsDead(true);
										MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
									}
								}
								else
								{
									if (_vBullets[j]->getIsEffectAngle())
									{
										EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound());

									}
									else
									{
										EFFECTMANAGER->AddEffect(_vBullets[j]->getX(), _vBullets[j]->getY(), _vBullets[j]->getEffectIgName(), 4, 0, 0, false, 255, _vBullets[j]->getAngle(), 1, 1, false, false, true, _vBullets[j]->getEffectSound(), 0, false, false);

									}
									_vBullets[j]->SetIsDead(true);
									MAPMANAGER->GetPlayMap()->GetObjects()[i]->GetDamage(_vBullets[j]->getDamage());
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}

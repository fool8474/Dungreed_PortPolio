#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1

	_x = 300;
	_y = WINSIZEY / 2;

	_initHp = _HP = 100;
	_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	_useImage = 0;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	_frameX = 0;
	_frameY = 0;
	_gravity = 0.4f;
	_jumpPower = 7.0f;
	_jumpCount = 0;
	_downJumpTimer = 0;
	_dashTimer = 0;
	_dashSpeed = 0;
	_maxDashCount = 3;
	_atkSpeed = 0.f;
	_realAttackSpeed = _atkSpeed * 60;
	_dustEffectCount = 0;
	_isStun = false;
	_stunCount = 0;
	_stunAniCout = 0;
	_stunFrameX = 0;
	_stunFrameY = 0;
	_isDash = false;
	_leftBack = false;
	_rightBack = false;
	_pixelCenter = POINT{ (long)(_x + _vImages[_useImage]->getWidth() / 2), (long)(_y + _vImages[_useImage]->getHeight() / 2) };
	_bottomCol = false;
	_dashEffect = nullptr;
	_isPlayerDead = false;
	_dashRestoreCount = 0;
	_dashRestoreTime = 100;
	_evasion = 0;
	_defence = 10;
	_money = 10000;
	_isHit = false;
	_hitCount = 0;
	_aliceZone = IMAGEMANAGER->findImage("AliceZone");
	_aliceZoneRadius = 141;
	_aliceZoneIn = false;
	_swapCoolTime = 0;
	_accesoryCount = 4;
	_hp = _initHp = 100;

	_criticalPercent = 2;
	_criticalDamage = 100;

	// UI
	_hpFrame = UIMANAGER->GetGameFrame()->GetChild("hpFrame");
	_dashFrame = UIMANAGER->GetGameFrame()->GetChild("dashFrame");

	for (int i = 0; i < 17; i++) _vToolTips.push_back(CharToolTip());
	_vToolTipsName = vector<string>{ "powerImg", "defImg", "toughImg", "blockImg", "criImg", "criDmgImg", "evadeImg",
		"moveSpeedImg", "atkSpeedImg", "reloadImg", "dashImg", "trueDamageImg", "burnImg",
		"poisonImg", "coldImg", "elecImg", "stunImg" };

	DashUICheck();

	// ���ÿ�
	_selectedWeaponIdx = 0;

	_inven = new Inventory();
	_inven->init();

	_inven->AddItem(new DemonSword(*dynamic_cast<DemonSword*>(DATAMANAGER->GetItemById(4000))));
	_inven->AddItem(new DemonSword(*dynamic_cast<DemonSword*>(DATAMANAGER->GetItemById(4000))));
	_inven->AddItem(new DemonSword(*dynamic_cast<DemonSword*>(DATAMANAGER->GetItemById(4000))));
	_inven->AddItem(new Colt(*dynamic_cast<Colt*>(DATAMANAGER->GetItemById(4001))));
	_inven->AddItem(new Colt(*dynamic_cast<Colt*>(DATAMANAGER->GetItemById(4001))));

	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4002)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4002)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4002)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4003)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4003)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4003)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4004)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4004)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4004)));

	return S_OK;
}

void Player::update()
{
	if (!UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->GetIsViewing() &&
		!UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase")->GetIsViewing() &&
		!UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetIsViewing() &&
		!UIMANAGER->GetGameFrame()->GetChild("selectFrame")->GetIsViewing() &&
		!UIMANAGER->GetGameFrame()->GetChild("convFrame")->GetIsViewing() &&
		!MAPMANAGER->GetPortalAnimOn()
		&& !_isStun && !_isPlayerDead
		)

		// ����� UI�� OFF�϶�
	{
		if (INPUT->GetIsRButtonClicked() && _dashCount > 0)		//���콺 ������ ��ư�� ��������
		{
			_isDash = true;
			_dashPoint = _ptMouse;
			_jumpPower = 0;
			_dashCount--;
			DashImageCheck();
		}

		if (INPUT->GetKeyDown('X'))				//XŰ�� ��������
		{
			ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_PLAYERNOCOL, _x, _y, getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _ptMouse.x, _ptMouse.y), 10, 10, 600, true);
		}   //�÷��̾��� x,y��ǥ�� �޾ƿͼ� �÷��̾�� ���콺 ��ǥ ���� ������ ������ �� �Ÿ���ŭ �Ѿ��� ���ư��Բ�

		if (CAMERAMANAGER->GetRelativeX(_x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() / 2) >= _ptMouse.x)
		{	//�÷��̾��� ����+�̹��� ���α����� ���� ���콺 x��ǥ���� ũ�ų� ������
			_isLeft = true;		//������ �ٶ󺸰�
		}
		else
		{
			_isLeft = false;	//�������� �ٶ󺸰�
		}

		if (_isDash)			//�뽬 ����
		{
			this->dash();		//�뽬�� �ؾ��ϹǷ� dash�Լ� ����
		}
		else
		{
			this->Move();		//�뽬 ���°� �ƴϹǷ� Move�Լ� ����
		}

		_realAttackSpeed--;
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (_weapons[_selectedWeaponIdx] != nullptr && _realAttackSpeed < 0)
			{
				_realAttackSpeed = 60 / _atkSpeed;
				_weapons[_selectedWeaponIdx]->Activate();
			}
		}
		Animation();
	}

	else // ����� UI�� ON
	{
		_inven->update();
	}

	if (_isStun)
	{
		_stunCount++;
		if (_stunCount > 40)
		{
			_isStun = false;
			_stunCount = 0;
		}
		_stunAniCout++;
		if (_stunAniCout > 5)
		{
			_stunAniCout = 0;
			_stunFrameX++;
			if (_stunFrameX > 5)
			{
				_stunFrameX = 0;
			}
		}


	}
	SwitchWeapon();
	if (_weapons[_selectedWeaponIdx] != nullptr) _weapons[_selectedWeaponIdx]->update();
	if (_subWeapons[_selectedWeaponIdx] != nullptr) _subWeapons[_selectedWeaponIdx]->update();
	for (int i = 0; i < _vAccessories.size(); i++)
	{
		_vAccessories[i]->update();
	}

	CheckAliceZone();
	UpdateCharPage();
	invincibility();
	SetRealStat();
	SetHpUI();
	SetTextLeftDown();
	this->pixelCollision();


	if (INPUT->GetKeyDown('J'))
	{
		_maxDashCount++;
		DashUICheck();
	}

	//���߿� �뽬�ִ�Ƚ�� ������ų�� �ʿ�
	if (INPUT->GetKeyDown('K'))
	{
		if (_maxDashCount > 0) _maxDashCount--;
		if (_dashCount > _maxDashCount) _dashCount--;
		DashUICheck();
	}

	if (_maxDashCount > _dashCount)
	{
		_dashRestoreCount++;

		if (_dashRestoreCount > _dashRestoreTime)
		{
			_dashRestoreCount = 0;
			_dashCount++;
			DashImageCheck();
		}
	}

	if (_HP < 0)
	{
		
		_HP = 0;
	}
}

void Player::DashImageCheck()
{
	for (int i = 0; i < _maxDashCount; i++)
	{
		if (_dashCount > i)
			_dashFrame->GetChild("dashColor" + to_string(i))->SetImage(IMAGEMANAGER->findImage("DashCount"));
		else
			_dashFrame->GetChild("dashColor" + to_string(i))->SetImage(nullptr);
	}
}

void Player::SetTextLeftDown()
{
	dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("leftDown")->GetChild("CoinText"))->SetText(to_string(_money));
	dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("leftDown")->GetChild("FoodText"))->SetText(to_string(_satiety) + " / " + to_string(_maxSatiety));
}

void Player::DashUICheck()
{
	_dashCount = _maxDashCount;
	_dashFrame->GetVChildFrames().clear();

	UIFrame* dashStartFrame = new UIFrame();
	dashStartFrame->init("start", 0, 0, 6, 23, "DashBaseLeftEnd");
	_dashFrame->AddFrame(dashStartFrame);
	int x = 6;
	for (int i = 0; i < _maxDashCount; i++)
	{
		UIFrame* dashBar = new UIFrame();
		dashBar->init("dashBar" + to_string(i), x, 0, 27, 24, "DashBase");
		_dashFrame->AddFrame(dashBar);

		UIFrame* dashColor = new UIFrame();
		dashColor->init("dashColor" + to_string(i), x, 6, 27, 24, "DashCount");
		_dashFrame->AddFrame(dashColor);
		x += 23;
	}
	UIFrame* dashEndFrame = new UIFrame();
	dashEndFrame->init("end", x, 0, 6, 23, "DashBaseRightEnd");
	_dashFrame->AddFrame(dashEndFrame);
}

void Player::SwitchWeapon()
{
	if (_swapCoolTime > 0)
	{
		_swapCoolTime--;
		UIFrame* swapFrame = UIMANAGER->GetGameFrame()->GetChild("swapContainer");

		UIFrame* weapon1 = swapFrame->GetChild("weapon1");
		UIFrame* weapon2 = swapFrame->GetChild("weapon2");

		if (_swapCoolTime == 0)
		{
			swapFrame->GetVChildFrames().push_back(swapFrame->GetVChildFrames()[0]);
			swapFrame->GetVChildFrames().erase(swapFrame->GetVChildFrames().begin());
		}

		if (_selectedWeaponIdx == 0)
		{
			weapon1->MoveFrameChild(-2.5f, 2.5f);
			weapon2->MoveFrameChild(2.5f, -2.5f);
		}
		else
		{
			weapon1->MoveFrameChild(2.5f, -2.5f);
			weapon2->MoveFrameChild(-2.5f, 2.5f);
		}
	}

	if (_mouseWheel != 0)
	{
		if (_swapCoolTime == 0)
		{
			if (_weapons[_selectedWeaponIdx] != nullptr)
			{
				_weapons[_selectedWeaponIdx]->SetisAttacking(false);
				_weapons[_selectedWeaponIdx]->SetRenderAngle(0);
			}
			if (_subWeapons[_selectedWeaponIdx] != nullptr)
			{
				_subWeapons[_selectedWeaponIdx]->SetisAttacking(false);
				_subWeapons[_selectedWeaponIdx]->SetRenderAngle(0);
			}

			_realAttackSpeed = 0;

			_selectedWeaponIdx = _selectedWeaponIdx == 0 ? 1 : 0;
			_inven->SwitchWeapon(_selectedWeaponIdx);

			_swapCoolTime = 20;
		}
	}
}

void Player::CheckAliceZone()
{
	vector<Object*> objs = MAPMANAGER->GetPlayMap()->GetObjects();

	bool zoneInHere = false;
	for (int i = 0; i < objs.size(); i++)
	{
		if (objs[i]->GetType() == OBJECTTYPE::OT_MONSTER && dynamic_cast<Enemy*>(objs[i])->GetIsSpawned())
		{
			if (UTIL::interactRectCircle(objs[i]->GetBody(), POINT{ (long)(_x + _vImages[_useImage]->getFrameWidth() / 2), (long)(_y + _vImages[_useImage]->getFrameHeight() / 2) }, _aliceZoneRadius))
			{
				_aliceZoneIn = true;
				zoneInHere = true;
				break;
			}
		}
	}

	if (!zoneInHere)
	{
		_aliceZoneIn = false;
	}
}

void Player::SetHpUI()
{
	//if (INPUT->GetKeyDown('H')) _hp--;
	UIProgressBar* bar = dynamic_cast<UIProgressBar*>(_hpFrame->GetChild("hpBarPros"));
	bar->FillCheck(_initHp, _HP);
	float fillPercent = (float)_HP / _initHp;

	UIImage* hpWave = dynamic_cast<UIImage*>(_hpFrame->GetChild("Wave"));
	hpWave->SetX((_hpFrame->GetX() + 42) + 157 * fillPercent); // ��ġ�� ������ ����ؼ� ����

	dynamic_cast<UIText*>(_hpFrame->GetChild("hp"))->SetText(to_string(_HP) + " / " + to_string(_initHp));
}

void Player::release()
{
	_inven->release();
}

void Player::render(HDC hdc)
{
	if (!MAPMANAGER->GetPortalAnimOn())
	{
		if (_weapons[_selectedWeaponIdx] != nullptr && _weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);
		if (_subWeapons[_selectedWeaponIdx] != nullptr && _subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);
		
		for (int i = 0; i < _vAccessories.size(); i++)
		{
			if (_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);
		}

		if (_isHit)
		{
			CAMERAMANAGER->FrameAlphaRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY, _hitAlpha);
		}
		else
		{
			CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
		}

		if (_weapons[_selectedWeaponIdx] != nullptr && !_weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);
		if (_subWeapons[_selectedWeaponIdx] != nullptr && !_subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);
		for (int i = 0; i < _vAccessories.size(); i++)
		{
			if (!_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);
		}


	if (_isStun)
	{
		CAMERAMANAGER->FrameRender(hdc, IMAGEMANAGER->findImage("stun"), _x+13, _y -10, _stunFrameX, _stunFrameY);
	}
		_inven->render(hdc);
		CAMERAMANAGER->FrameRender(hdc, _aliceZone, _x + _vImages[_useImage]->getFrameWidth() / 2 - _aliceZone->getFrameWidth() / 2, _y + _vImages[_useImage]->getFrameHeight() / 2 - _aliceZone->getFrameHeight() / 2, _aliceZoneIn ? 1 : 0, 0);
	}
}

void Player::Animation()
{
	switch (_state)
	{
	case PS_IDLE:
		_useImage = 0;
		break;
	case PS_JUMP:
		_useImage = 1;
		break;
	case PS_MOVE:
		_useImage = 1;
		if (_isJump == false && (_jumpPower == 0 || _jumpPower == -2))
		{
			_dustEffectCount++;
			if (_dustEffectCount % 20 == 0)
			{
				if (_isLeft)
				{
					EFFECTMANAGER->AddEffect(_x + 40, _y + 20, "RunEffect", 5, 0, 1, false, 255);
				}
				else
				{
					EFFECTMANAGER->AddEffect(_x - 40, _y + 20, "RunEffect", 5, 0, 0, false, 255);
				}

			}
		}
		break;
	case PS_DIE:
		break;
	default:
		break;
	}

	if (_isLeft)
	{
		_frameTimer++;
		_frameY = 1;
		if (!_leftBack)
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
	}
	else
	{
		_frameTimer++;
		_frameY = 0;
		if (!_rightBack)
		{

			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
	}
}

void Player::Move()
{
	_isJump = false;				//ó���� �������°� �ƴϱ⶧����
	if (INPUT->GetKey('A'))			//AŰ�� ������ ��
	{
		_leftBack = false;			//���׸���� ���콺 ��ǥ�� ������ ǥ��
		if (!_isLeft)
		{
			_rightBack = true;
		}

		_state = PS_MOVE;			//�̹��� ���� �̵����·�
		_x -= 5;
		_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	}
	if (INPUT->GetKeyUp('A'))		//AŰ�� �����ٰ� ������
	{
		_state = PS_IDLE;			//�̹��� ���� �����·�
	}
	if (INPUT->GetKey('D'))
	{
		if (_isLeft)
		{
			_leftBack = true;
		}
		_rightBack = false;
		_state = PS_MOVE;
		_x += 5;
		_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
	}

	if (_jumpCount == 0 || _jumpCount == 1)	//������ ���߰ų� �ѹ�������
	{

		if (INPUT->GetKeyDown(VK_SPACE) && !_downJump)	//�����̽��ٸ� ������ �Ʒ��� �����Ѱ� �ƴҶ�
		{
			_isJump = true;
			_jumpPower = 11;
			_y -= _jumpPower;
			_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
			_jumpCount++;
		}
		if (INPUT->GetKey('S') && _isJump)	//SŰ�� �����µ� ���������� ��
		{
			_downJump = true;
			_jumpPower = -2;
			_jumpCount++;
		}
	}

	if (_downJump)							//�ٿ� ���� ������ ��
	{
		_downJumpTimer++;
		if (_downJumpTimer > 20)
		{
			_downJumpTimer = 0;
			_downJump = false;
		}
	}
}

void Player::pixelCollision()
{
	//////////////////////////// �ȼ��浹 //////////////////////////////

	bool isCollide = false; // �浹 �ߴ��� ����
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;
	_bottomCol = false;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");



	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // ������ �ȼ��浹�� ���� ��Ҵ�
		{
			isCollide = true; // �浹������ �긦 ON
			_bottomCol = true; // �Ʒ� �浹���ִ�
			_jumpPower = -2;	  // ���������� �ڿ������� �������� �ϱ����� �����Ŀ� �ʱ�ȭ


			_y = i - baseCharIg->getFrameHeight();// �ö󰣴�
			_jumpCount = 0;
			break;
		}

		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false && _isDash == false) // �Ķ��� �ȼ��浹�� ���� ��Ұ� �������� ���¶��
		{
			isCollide = true;		// �浹������ �긦 ON
			_jumpPower = -2;		// ���������� �ڿ������� �������� �ϱ����� �����Ŀ� �ʱ�ȭ

			_y = i - baseCharIg->getFrameHeight();// �ö󰣴�
			_jumpCount = 0;
			break;
		}
	}
	if (_bottomCol == false)
	{

		for (int i = _y + 15; i > _y - 4; i--)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + baseCharIg->getFrameWidth() / 2, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if ((r == 255 && g == 0 && b == 0)) // ������ �ȼ��浹�� ���� ��Ҵ�
			{
				_jumpPower = -2;
				_y = i + 5;

				break;
			}
		}
	}
	if (!isCollide) //�浹������ �ʴٸ�
	{
		_y -= _jumpPower;			//�߷�����
		_jumpPower -= _gravity;

		if (_jumpPower < -20)		//�����Ŀ��� -20���� ������
		{
			_jumpPower = -20;		//���̻� -�����ʰ� �����Ŀ� ���� ����
		}
		_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	}

	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;

			if (_RightCollision1 && _RightCollision2)
			{
				_x = i - baseCharIg->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 40);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - baseCharIg->getFrameWidth();
			break;
		}

	}
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - baseCharIg->getFrameWidth();


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

			if (_leftCollision1 && _leftCollision2)
			{
				_x = i;

			}

			break;
		}
	}
	//�����߰�
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 40);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision2 = true;
			_x = i;

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
			_x = i;
			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////

	// ��Ż �˻�
	_pixelCenter = POINT{ (long)(_x + 30), (long)(_y + 30) };

	COLORREF _color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _pixelCenter.x, _pixelCenter.y);
	if (_color == RGB(0, 255, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_LEFT));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_RIGHT);
	}

	else if (_color == RGB(0, 200, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_RIGHT));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_LEFT);
	}

	else if (_color == RGB(0, 155, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_UP));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_DOWN);
	}
	else if (_color == RGB(0, 100, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_DOWN));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_UP);
	}
}

void Player::dash()
{
	_dashTimer++;

	_x += cosf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
	_y += -sinf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
	_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();


	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");


	//�뽬�Ҷ��� �ӵ��� �ٲ�Ƿ� �ȼ��浹 �����÷��� ���ΰ˻�
	for (int i = _probeBottom - 20; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);				//���� �� �־��ֱ�
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // ������ �ȼ��浹�� ���� ��Ҵ�
		{

			_y = i - baseCharIg->getFrameHeight();// �ö󰣴�
			break;
		}
	}
	for (int i = _y + 20; i > _y - 5; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_y = i;
			break;
		}
	}
	for (int i = _x + baseCharIg->getFrameWidth() - 20; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - baseCharIg->getFrameHeight() / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i - baseCharIg->getFrameWidth();
			break;
		}
	}

	for (int i = _x + 20; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - baseCharIg->getFrameHeight() / 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i;
			break;
		}
	}
	if (_dashTimer == 1)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 3)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 5)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 6)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 7)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}

	if (_dashTimer >= 10)
	{
		_dashTimer = 0;		//�뽬 Ÿ�̸� �ʱ�ȭ
		_jumpPower = 0;		//���� �Ŀ� �ʱ�ȭ
		_isDash = false;	//�뽬���°� �ƴ�
	}
}

void Player::GetDamage()
{


}

void Player::invincibility()
{
	if (_isHit)
	{
		_hitCount++;
		if (_hitCount % 3 == 0)
		{
			_hitAlpha = 255;
		}
		else
		{
			_hitAlpha = 10;
		}

		if (_hitCount > 30)
		{
			_isHit = false;
			_hitCount = 0;
		}

	}
}

/// <summary>
/// ĳ���� �������� ���������� ����ؼ� ������Ʈ���ش�.
/// </summary>
void Player::UpdateCharPage()
{
	UIFrame* charFrame = UIMANAGER->GetGameFrame()->GetChild("charFrame");
	if (charFrame->GetIsViewing())
	{
		dynamic_cast<UIText*>(charFrame->GetChild("powerText"))->SetText(to_string(_minDamage) + " ~ " + to_string(_maxDamage) + " (" + to_string(_power) + ") ");
		dynamic_cast<UIText*>(charFrame->GetChild("defText"))->SetText(to_string_with_precision(_defence, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("toughText"))->SetText(to_string_with_precision(_toughness, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("blockText"))->SetText(to_string_with_precision(_block, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("criText"))->SetText(to_string_with_precision(_criticalPercent, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("criDmgText"))->SetText(to_string_with_precision(_criticalDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("evadeText"))->SetText(to_string_with_precision(_evasion, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("moveSpeedText"))->SetText(to_string_with_precision(_moveSpeed, 2));
		dynamic_cast<UIText*>(charFrame->GetChild("atkSpeedText"))->SetText(to_string_with_precision(_atkSpeed, 2));
		dynamic_cast<UIText*>(charFrame->GetChild("reloadText"))->SetText(to_string_with_precision(_reloadTime, 1));
		dynamic_cast<UIText*>(charFrame->GetChild("dashText"))->SetText(to_string_with_precision(_dashDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("trueDamageText"))->SetText(to_string_with_precision(_trueDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("burnText"))->SetText(to_string_with_precision(_fireDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("poisonText"))->SetText(to_string_with_precision(_posionDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("coldText"))->SetText(to_string_with_precision(_iceDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("elecText"))->SetText(to_string_with_precision(_elecDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("stunText"))->SetText(to_string_with_precision(_stunDamage, 0));

		CharPageToolTipOn();
	}
}

void Player::SetRealStat()
{
	_realEvasion = sqrt(_evasion * 36);
	if (_evasion < 0)
	{
		_realEvasion = 0;
	}


	if (_defence >= 0)
	{
		_realDefence = sqrt(_defence * 36);
	}
	else
	{
		_realDefence = -sqrt(abs(_defence) * 36);
	}

	_realCriticalPercent = sqrt(_criticalPercent * 36);
	if (_criticalPercent < 0)
	{
		_realCriticalPercent = 0;
	}

	

}

/// <summary>
/// ĳ���� �������� ������ �¿����ϰ� ���빰�� �ٲ۴�.
/// </summary>
void Player::CharPageToolTipOn()
{
	UIFrame* charFrame = UIMANAGER->GetGameFrame()->GetChild("charFrame");
	charFrame->GetChild("toolTipFrame")->SetIsViewing(false);

	for (int i = 0; i < _vToolTipsName.size(); i++)
	{
		if (PtInRect(&charFrame->GetChild(_vToolTipsName[i])->GetRect(), _ptMouse))
		{
			ReInitTooltip(i);
			SetToolTipFrame(_ptMouse.x - charFrame->GetChild("toolTipFrame")->GetX(), _ptMouse.y - charFrame->GetChild("toolTipFrame")->GetY(), i);
			charFrame->GetChild("toolTipFrame")->SetIsViewing(true);
		}
	}
}

/// <summary>
/// ���° �����ΰ��� ���� ���� ������ �˸°� �����Ѵ�.
/// </summary>
void Player::ReInitTooltip(int n)
{
	switch (n)
	{
	case 0:
		_vToolTips[0].init("powerImg", "������ݷ� (����)", "\"����\"�� ���� ���ݷ��� ������� �߰� ���ط��� ������ �ݴϴ�.", "���� ����: " + to_string(_power) + "(������ ���ʽ�)", 3.0f, 1.7f);
		break;
	case 1:
		_vToolTips[1].init("defImg", "����", "�޴� ���ظ� �氨�����ݴϴ�.", "���ذ��ҷ�: " + to_string_with_precision(_realDefence, 1) + "%", 3.0f, 1.7f);
		break;

	case 2:
		_vToolTips[2].init("toughImg", "������", "������ ��ġ�� ���� �������� ���ظ� �氨�����ݴϴ�.", "", 3.0f, 1.3f);
		break;

	case 3:
		_vToolTips[3].init("blockImg", "����", "���� ������ ���� �� �ִ� Ȯ���� ������ŵ�ϴ�.", "���� Ȯ��: " + to_string_with_precision(_block, 0) + "%", 3.0f, 1.7f);
		break;

	case 4:
		_vToolTips[4].init("criImg", "ũ��Ƽ��", "������ ġ������ ���ظ� ���� �� �ִ� ��ȸ�� �þ�ϴ�.", "ũ��Ƽ�� Ȯ��: " + to_string_with_precision(_realCriticalPercent, 1) + "%", 3.0f, 1.7f);
		break;

	case 5:
		_vToolTips[5].init("criDmgImg", "ũ��Ƽ�� ������", "ũ��Ƽ�� �߰� ���ط��� ��Ÿ���ϴ�.", "", 3.0f, 1.3f);
		break;

	case 6:
		_vToolTips[6].init("evadeImg", "ȸ��", "���� ������ ȸ���� �� �ִ� Ȯ���� ������ŵ�ϴ�.", "ȸ�� Ȯ��: " + to_string_with_precision(_realEvasion, 1) + "%", 3.0f, 1.3f);
		break;

	case 7:
		_vToolTips[7].init("moveSpeedImg", "�̵��ӵ�", "�� ������ �����̰� ���ݴϴ�.", "", 3.0f, 1.3f);
		break;

	case 8:
		_vToolTips[8].init("atkSpeedImg", "���ݼӵ�", "1�ʿ� ������ �� �ִ� Ƚ���� ��Ÿ���ϴ�.", "", 3.0f, 1.3f);
		break;

	case 9:
		_vToolTips[9].init("reloadImg", "�������ӵ�", "������ �� �ɸ��� �ӵ��� ��Ÿ���ϴ�.", "", 3.0f, 1.3f);
		break;

	case 10:
		_vToolTips[10].init("dashImg", "�뽬 ���ݷ�", "�뽬 ���ݷ��� ���� ���ݷ��� %�� ���˴ϴ�.", "", 3.0f, 1.3f);
		break;

	case 11:
		_vToolTips[11].init("trueDamageImg", "���� ������", "���� ���� ���� �����ϰ� ������ ���ظ� �����ϴ�", "", 3.0f, 1.3f);
		break;

	case 12:
		_vToolTips[12].init("burnImg", "ȭ�� ���� ��ȭ", "���� ���¿� ª���ð����� �������� �ݴϴ�.", "", 3.0f, 1.3f);
		break;

	case 13:
		_vToolTips[13].init("poisonImg", "�ߵ� ���� ��ȭ", "���� �ߵ����� �� �ð����� �������� �ݴϴ�.", "", 3.0f, 1.3f);
		break;

	case 14:
		_vToolTips[14].init("coldImg", "���� ���� ��ȭ", "���� ������ ����ϴ�.", "", 3.0f, 1.3f);
		break;

	case 15:
		_vToolTips[15].init("elecImg", "���� ���� ��ȭ", "���� ������ ��ȿȭ ��ŵ�ϴ�.", "", 3.0f, 1.3f);
		break;

	case 16:
		_vToolTips[16].init("stunImg", "���� ���� ��ȭ", "���� �Ͻ������� �ൿ�Ҵ����� ����ϴ�.", "", 3.0f, 1.3f);
		break;

	}
}

/// <summary>
/// ������ ���빰�� �ٲٰ�, ��ġ�� �˸°� �����Ѵ�.
/// </summary>
void Player::SetToolTipFrame(float x, float y, int index)
{
	UIFrame* toolTipFrame = UIMANAGER->GetGameFrame()->GetChild("charFrame")->GetChild("toolTipFrame");
	toolTipFrame->MoveFrameChild(x, y);
	toolTipFrame->SetScaleX(_vToolTips[index].scaleX);
	toolTipFrame->SetScaleY(_vToolTips[index].scaleY);

	dynamic_cast<UIText*>(toolTipFrame->GetChild("title"))->SetText(_vToolTips[index].title);
	dynamic_cast<UIText*>(toolTipFrame->GetChild("discription"))->SetText(_vToolTips[index].description);
	dynamic_cast<UIText*>(toolTipFrame->GetChild("additional"))->SetText(_vToolTips[index].additionalDescription);
}


void Player::GetHitDamage(int damage)
{
	if (_isHit == false)
	{
		float Realdamage;
		int block;
		int evasion;
		int critical;
		Realdamage = damage - damage * _realDefence / 100; // �뽬�� �浹�ϸ� �⺻ 20���������� ���
		evasion = RANDOM->range(100);
		block = RANDOM->range(100);
		if (_realEvasion <= evasion)
		{
			if (_block <= block)
			{
				_isHit = true;
				_hitCount = 0;
				_HP = _HP - Realdamage;
				EFFECTMANAGER->AddEffect(0, 0, "hit", 0, 0, 0, true, 100, 0, 1, 1, true ,true);
				CAMERAMANAGER->Shake(25, 25, 6, 1);

			}
			else
			{
				EFFECTMANAGER->AddCameraText(_x, _y, 200, 50, "BLOCK", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WSORT_LEFT, RGB(0, 0, 255));
			}
		}
		else
		{
			EFFECTMANAGER->AddCameraText(_x, _y, 200, 50, "EVADE", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WSORT_LEFT, RGB(0, 255, 0));
		}
	}

}


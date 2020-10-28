#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	_uid = 0;
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharDie")); //2
	_dashEffectCharImage = IMAGEMANAGER->findImage("baseCharEffect");
	_state = PS_IDLE;

	_x = 300;
	_y = WINSIZEY / 2;

	_initHp = _hp = 100;
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
	_atkSpeedPer = 0.f;
	_moveSpeed = 5;
	_moveSpeedPer = 0;
	_dashDamage = 100;
	_prevPowerPlus = 0;
	_realAttackSpeed = _atkSpeed + (_atkSpeed * _atkSpeedPer / 100);
	_dustEffectCount = 0;
	_restorePrevHp = 0;
	_restoreHpTimer = 0;
	_isStun = false;
	_isLeft = false;
	_jump = false;
	_isJump = false;
	_downJump = false;
	_hitAlpha = 0;
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
	_damageUpTimer = 0;
	_damageUpTimerUse = false;

	_isReload = false;
	_bulletCount = 0;
	_maxBullet = 0;
	_reloadCount = 0;
	_reloadTime = 100;
	_reloadSpeed = 1;
	_reloadEffect.frameX = 0;
	_reloadEffect.frameY = 0;
	_reloadEffect.ig = IMAGEMANAGER->findImage("ReloadEffect");
	_reloadEffect.isViewing = false;
	_reloadEffect.x = 0;
	_reloadEffect.y = 0;

	_regenEffect.frameTime = 0;
	_regenEffect.frameX = 0;
	_regenEffect.frameY = 0;
	_regenEffect.ig = IMAGEMANAGER->findImage("RegenerationSkin");
	_regenEffect.isViewing = false;
	_regenEffect.x = 0;
	_regenEffect.y = 0;

	_guardBreakEffect.frameTime = 0;
	_guardBreakEffect.frameX = 0;
	_guardBreakEffect.frameY = 0;
	_guardBreakEffect.ig = IMAGEMANAGER->findImage("GuardBreak");
	_guardBreakEffect.isViewing = false;
	_guardBreakEffect.x = 0;
	_guardBreakEffect.y = 0;

	_atkSpdUpUse = false;
	_dashRestoreCount = 0;
	_dashRestoreTime = 60;
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
	_maxSatiety = 200;
	_goldDrop = 100;
	_level = 30;
	_remainPoint = 35;
	_maxPoint = 35;
	_clothType = PC_NORMAL;
	_useGun = false;
	_useMeleeWeapon = false;
	_dashInvinCible = false;
	_dashInvincibTimer = 0;
	_deathDefencerActivated = false;
	_deathDefencerTimer = 0;
	_criminalCount = 0;
	_prevCriminalCount = 0;
	_shieldPoint = 0;
	_isFire = false;
	_fireCount = 0;
	_isIce = false;
	_isElectric = false;
	_isPoison = false;

	_immuneFire = false;
	_immuneIce = false;
	_immuneElectric = false;
	_immunePosion = false;

	_killPoint = 0;
	_maxKillPoint = 10;

	_isEquipGlass = false;
	_isEquipMulti = false;
	for (int i = 0; i < 7; i++) _abilityNum[i] = 0;

	_criticalPercent = 2;
	_criticalDamage = 100;
	_isCritical = false;

	_weapons[0] = nullptr;
	_weapons[1] = nullptr;
	_subWeapons[0] = nullptr;
	_subWeapons[1] = nullptr;
	for (int i = 0; i < _vAccessories.size(); i++)
	{
		_vAccessories[i] = nullptr;
	}
	// ���� //
	_isBossReady = false;
	// �ڽ�Ƭ 
	_rageCurrent = 0;
	_rageMax = 100;
	_rageTimer = 1200;
	_isRaging = false;
	_criminalCount = 0;
	_playerDeadCount = 0;
	_maxShieldPoint = 15;
	_shieldPoint = 0;

	_foodPower = 0;
	_foodDef = 0;
	_foodEvade = 0;
	_foodCriPer = 0;
	_foodCriDmg = 0;
	_foodInitHp = 0;
	_foodMaxDash = 0;
	_foodTrueDamage = 0;
	_foodAtkSpeedPer = 0;
	_foodReloadSpeed = 0;
	_foodAccsCount = 0;
	_foodToughness = 0;
	_foodBlock = 0;
	_foodMoveSpeed = 0;
	_foodRoomMoveSatiation = 0;

	// UI
	_hpFrame = UIMANAGER->GetGameFrame()->GetChild("hpFrame");
	_dashFrame = UIMANAGER->GetGameFrame()->GetChild("dashFrame");
	_traitFrame = UIMANAGER->GetGameFrame()->GetChild("allTraitFrame");
	_movedX = 0;

	for (int i = 0; i < 17; i++) _vToolTips.push_back(CharToolTip());
	_vToolTipsName = vector<string>{ "powerImg", "defImg", "toughImg", "blockImg", "criImg", "criDmgImg", "evadeImg",
		"moveSpeedImg", "atkSpeedImg", "reloadImg", "dashImg", "trueDamageImg", "burnImg",
		"poisonImg", "coldImg", "elecImg", "stunImg" };

	_vTraitTooltip[0][0] = "������ �� �ֺ� ���鿡�� 8�� ����";
	_vTraitTooltip[0][1] = "���� óġ�ϸ� 15�ʵ��� ������ 10 ���";
	_vTraitTooltip[0][2] = "HP�� 60% �̸��� �� ���� ���ݷ��� �ִ�� ����.\n�뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[1][0] = "�̴� ���� ����, �뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[1][1] = "�뽬 ��Ÿ�� ����, ���� ü���� 80% �̻��� ��� ���ݼӵ� ����";
	_vTraitTooltip[1][2] = "�뽬 ���� 0.2�ʰ� ����.\n�뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[2][0] = "�������и� ����";
	_vTraitTooltip[2][1] = "������ �̸��� ���ظ� ���� ��� 4�ʵ��� ���� (1����)";
	_vTraitTooltip[2][2] = "ü���� 30% �̸��� �� ü���� ����ϰ� ������ ������.\n�뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[3][0] = "���� ���� 30% ����";
	_vTraitTooltip[3][1] = "������ ���ȿ���� ��Ÿ�� 40% ����";
	_vTraitTooltip[3][2] = "Ž�� ����� �������� ������ �� �ϳ��� ������ ���� ����.\n�뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[4][0] = "��� ȹ�淮 +20%";
	_vTraitTooltip[4][1] = "������ �ִ�ġ +25";
	_vTraitTooltip[4][2] = "�׼����� ����+1, �Ĵ翡�� �Դ� ������ ������ ������ 10% ����.\n�뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[5][0] = "���Ÿ� ���� ������ �ִ� ü�� +20, ���� +10�� ȹ��";
	_vTraitTooltip[5][1] = "�������ӵ��� 15% �����ϰ�, ���� ��� ���͸� �����߸� ������ ü���� +2�� ȸ��";
	_vTraitTooltip[5][2] = "12�ʸ��� ���� �������� �ٷ� ���ִ� \"������ ����\"�� ȹ�� (�ִ� 3��)\n�뽬 �ִ� Ƚ�� +1";
	_vTraitTooltip[6][0] = "�� �������ݽ� 10% Ȯ���� \"��ȭ\"�����̻� �ο�(������ ���� ������)";
	_vTraitTooltip[6][1] = "��ȭ ������ �� �������� �� ���� ��������ŭ ȸ��";
	_vTraitTooltip[6][2] = "������ +15 ������Ű�� \"��ȭ\"Ȯ���� 100%�� ����.\n�뽬 �ִ� Ƚ�� +1";

	DashUICheck();

	// ���ÿ�
	_selectedWeaponIdx = 0;

	_inven = new Inventory();
	_inven->init();

	_inven->AddItem(DATAMANAGER->GetItemById(4000));
	_inven->AddItem(DATAMANAGER->GetItemById(4001));
	_inven->AddItem(DATAMANAGER->GetItemById(4500));
	_inven->AddItem(DATAMANAGER->GetItemById(4018));
	_inven->AddItem(DATAMANAGER->GetItemById(4005));
	_inven->AddItem(DATAMANAGER->GetItemById(4025));
	_inven->AddItem(DATAMANAGER->GetItemById(4028));
	_inven->AddItem(DATAMANAGER->GetItemById(4029));
	_inven->AddItem(DATAMANAGER->GetItemById(4100));
	_inven->AddItem(DATAMANAGER->GetItemById(4021));
	_inven->AddItem(DATAMANAGER->GetItemById(4026));
	_inven->AddItem(DATAMANAGER->GetItemById(4052));

	return S_OK;
}

void Player::update()
{

	if (!_isPlayerDead)
	{
		if (!UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("selectFrame")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("convFrame")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("_restaurantBase")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetIsViewing() &&
			!UIMANAGER->GetGameFrame()->GetChild("allTraitFrame")->GetIsViewing() &&
			!ENTITYMANAGER->GetWormVillage()->GetIsOn() &&
			!MAPMANAGER->GetPortalAnimOn() &&
			!MAPMANAGER->GetStageChanger()->GetIsChangingStage() &&
			!_traitFrame->GetIsViewing() &&
			!_isStun &&
			!_isPlayerDead &&
			!_isBossReady
			)

			// ����� UI�� OFF�϶�
		{
			RangeItemEquip();
			if (INPUT->GetIsRButtonClicked() && _dashCount > 0)		//���콺 ������ ��ư��������,�뽬ī��Ʈ�� 0���� Ŭ��
			{
				SOUNDMANAGER->play("�뽬�Ҹ�");
				_isDash = true;
				_dashPoint = _ptMouse;
				_jumpPower = 0;
				_dashCount--;
				DashImageCheck();;
			}


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
			if (INPUT->GetKey(VK_LBUTTON))	//���� ���� ��ư��������
			{
				if (_weapons[_selectedWeaponIdx] != nullptr)	//�����ȹ��Ⱑ �ְ�, ���� Ÿ�̸Ӱ� �����Ǿ��ٸ�
				{
					_weapons[_selectedWeaponIdx]->ActivateAlways();
					if (_realAttackSpeed < 0)
					{
						_realAttackSpeed = 60 / (_atkSpeed + (_atkSpeed * _atkSpeedPer / 100));
						_weapons[_selectedWeaponIdx]->Activate();
					}
				}
			}

			PlayerIsDead();
		}

		else // ����� UI�� ON
		{
			_inven->update();
		}

		if (_isStun)				//���ϻ���
		{
			_stunCount++;			//���� ����ī��Ʈ
			if (_stunCount > 40)	//���� ���� ī��Ʈ�� 40���� ������
			{
				_isStun = false;	//���� ���� �ƴ�
				_stunCount = 0;		//���� ���� ī��Ʈ�� �ʱ�ȭ
			}
			_stunAniCout++;			//���� �ִϸ��̼� ī��Ʈ
			if (_stunAniCout > 5)	//���� �ִϸ��̼� ī��Ʈ�� 5���� ũ��
			{
				_stunAniCout = 0;	//���� �ִϸ��̼� ī��Ʈ�� 0����
				_stunFrameX++;
				if (_stunFrameX > 5)
				{
					_stunFrameX = 0;
				}
			}
		}

		Animation();
		SwitchWeapon();
		if (_weapons[_selectedWeaponIdx] != nullptr) _weapons[_selectedWeaponIdx]->update();		//������ �ֹ��Ⱑ �ִٸ�, ������Ʈ �Լ� ����
		if (_subWeapons[_selectedWeaponIdx] != nullptr) _subWeapons[_selectedWeaponIdx]->update();	//������ �������Ⱑ �ִٸ�, ������Ʈ �Լ� ����
		for (int i = 0; i < _vAccessories.size(); i++)	//�Ǽ����� �����ŭ ���鼭
		{
			_vAccessories[i]->update();					//�Ǽ������� ������Ʈ�Լ��� ����
		}

		// ĳ���� �ɷ�
		CheckAliceZone();
		AdjustAlicePower();
		CheckUsePistolGunner();
		SetIkinaBearAngry();
		CheckMoveSpeedRiderH();
		CheckCliminal();
		Checkfasto();
		CheckMasterChef();
		ShieldUICheck();
		//====================
		UpdateCharPage();
		invincibility();
		SetRealStat();
		SetHpUI();
		SetTextLeftDown();
		this->pixelCollision();

		// Ư�� ����
		ControlTraitPage();
		JumpAttackRectUpdate();
		ControlDamageUpTimer();
		SpecialAtkSpeedUp();
		DashInvincibility();
		SetDeathDefencerTimerDown();
		RegenDefenceSkill();
		AbnormalState();
		ReloadBullet();
		RangeGetStatusAbility();
		ReloadItemChecker();
		RestoreHpTimerChecker();


		// UI
		BulletNumUIChecker();
		SkillUIChecker();

		if (INPUT->GetKeyDown('J'))
		{
			AddMaxDash();
		}

		//���߿� �뽬�ִ�Ƚ�� ������ų�� �ʿ�
		if (INPUT->GetKeyDown('K'))		//KŰ�� ��������
		{
			SubMaxDash();
		}

		if (_maxDashCount > _dashCount)	//�뽬 �ִ� Ƚ���� �뽬Ƚ������ Ŀ����
		{
			_dashRestoreCount++;	//�뽬 Ƚ�� ���� ī��Ʈ ����

			if (_dashRestoreCount > (_specialAbilityOn[1][1] ? _dashRestoreTime - 15 : _dashRestoreTime))	//�뽬 Ƚ�� ���� ī��Ʈ�� �뽬 ���� �ð����� Ŀ����
			{
				_dashRestoreCount = 0;	//�뽬 Ƚ�� ���� ī��Ʈ �ʱ�ȭ
				_dashCount++;			//�뽬 Ƚ�� ����
				DashImageCheck();
			}
		}

		if (_hp < 0)
		{
			_hp = 0;
		}

		SetNewMaxHp();
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("BossLifeBack")->SetIsViewing(false);
		pixelCollision();
		PlayerDeadTimerCheck();
		DeadToLive();
		SetNewMaxHp();
	}
}

void Player::PlayerIsDead()
{
	if (_hp <= 0)
	{
		SOUNDMANAGER->play("����_���(1)");
		_hp = 0;

		_isPlayerDead = true;

		_playerDeadTimer = 150;
		_frameX = 0;
		_frameY = 0;
		_frameTimer = 0;
	}
}

void Player::PlayerDeadTimerCheck()
{
	if (_clothType == CLOTHTYPE::PC_HORSESWORD)
	{
		if (_playerDeadCount < 2)	//������ Ÿ�̸Ӱ� 0���� Ŭ��
		{
			_useImage = 2;			//���� �̹���
			_hp = 0;				//ü�� 0
			_playerDeadTimer--;		//���� �� Ÿ�̸� ����

			if (_playerDeadTimer == 0)
			{
				_useImage = 0;
				_hp = _maxHp;
				_isPlayerDead = false;
				_playerDeadCount++;
			}
		}

		else // ��Ȱ �پ�
		{
			if (_playerDeadTimer > 0)
			{
				_useImage = 2;
				_hp = 0;
				_playerDeadTimer--;

				if (_playerDeadTimer == 0)
				{
					ReturnToHome();
					_playerDeadCount = 0;
				}
			}
		}
	}
	else
	{
		if (_playerDeadTimer > 0)
		{
			_useImage = 2;
			_hp = 0;
			_playerDeadTimer--;

			if (_playerDeadTimer == 0)
			{
				ReturnToHome();
			}
		}
	}
}

void Player::ReturnToHome()
{
	MAPMANAGER->GetStageChanger()->MoveStage(0);
	ReturnToHomeFoodInit();
	_inven->GetVItemList().clear();
	if (_weapons[_selectedWeaponIdx] != nullptr) _weapons[_selectedWeaponIdx]->EquipUnEquipStatus(false);
	if (_subWeapons[_selectedWeaponIdx] != nullptr) _subWeapons[_selectedWeaponIdx]->EquipUnEquipStatus(false);
	for (int i = 0; i < _vAccessories.size(); i++) _vAccessories[i]->EquipUnEquipStatus(false);

	_weapons[0] = nullptr;
	_weapons[1] = nullptr;
	_subWeapons[0] = nullptr;
	_subWeapons[1] = nullptr;
	_vAccessories.clear();
	_checkReturnOn = true;
	_hp = _maxHp;
	_satiety = 0;
	_money *= 0.2f;
	_inven->AddItem(DATAMANAGER->GetItemById(4017));
	_inven->ReloadUIImages();
}

void Player::DeadToLive()
{
	if (_isPlayerDead && !MAPMANAGER->GetStageChanger()->GetIsChangingStage() && _checkReturnOn)
	{
		_isPlayerDead = false;
		_useImage = 0;
		_checkReturnOn = false;
	}
}

void Player::ReturnToHomeFoodInit()
{
	_power -= _foodPower;
	_foodPower = 0;
	_defence -= _foodDef;
	_foodDef = 0;
	_evasion -= _foodEvade;
	_foodEvade = 0;
	_criticalPercent -= _foodCriPer;
	_foodCriPer = 0;
	_criticalDamage -= _foodCriDmg;
	_foodCriDmg = 0;
	_initHp -= _foodInitHp;
	_foodInitHp = 0;
	for (int i = 0; i < _foodMaxDash; i++) SubMaxDash();
	_foodMaxDash = 0;
	_trueDamage -= _foodTrueDamage;
	_foodTrueDamage = 0;
	_atkSpeedPer -= _foodAtkSpeedPer;
	_foodAtkSpeedPer = 0;
	_reloadSpeed -= _foodReloadSpeed;
	_foodReloadSpeed = 0;
	_accesoryCount -= _foodAccsCount;
	_foodAccsCount = 0;
	GetInventory()->SetInventoryAccesoryUI();
	GetInventory()->ReloadUIImages();
	_toughness -= _foodToughness;
	_foodToughness = 0;
	_block -= _foodBlock;
	_foodBlock = 0;
	_moveSpeed -= _foodMoveSpeed;
	_foodMoveSpeed = 0;
	_roomMoveSatiation -= _foodRoomMoveSatiation;
	_foodRoomMoveSatiation = 0;
}

void Player::DashInvincibility()
{
	if (_dashInvinCible >= 0)
	{
		_dashInvincibTimer--;
		if (_dashInvincibTimer < 0)
		{
			_dashInvinCible = false;
		}
	}
}

void Player::AddMaxDash()
{
	_maxDashCount++;
	DashUICheck();
}

void Player::SubMaxDash()
{
	if (_maxDashCount > 0) _maxDashCount--;	// �뽬 �ִ� Ƚ���� 0���� Ŭ�� �ִ�Ƚ�� ����
	if (_dashCount > _maxDashCount) _dashCount--;	//�뽬Ƚ���� �ִ� Ƚ������ Ŀ���� �뽬Ƚ�� ����
	DashUICheck();
}

void Player::SkillUIChecker()
{
	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("skillFrame");
	if (_weapons[_selectedWeaponIdx] != nullptr && _weapons[_selectedWeaponIdx]->GetSkill() != nullptr)
	{
		Skill* skill = _weapons[_selectedWeaponIdx]->GetSkill();
		frame->SetIsViewing(true);
		frame->GetChild("skillImageFrame")->SetImage(skill->GetImage());

		if (skill->GetCurCoolTime() == 0)
		{
			dynamic_cast<UIText*>(frame->GetChild("cooltime"))->SetIsViewing(false);
		}
		else
		{
			dynamic_cast<UIText*>(frame->GetChild("cooltime"))->SetIsViewing(true);
			int coolTime = skill->GetCurCoolTime() / 60.f;
			dynamic_cast<UIText*>(frame->GetChild("cooltime"))->SetText(to_string(coolTime));
		}
	}

	else
	{
		frame->SetIsViewing(false);
	}
}

void Player::BulletNumUIChecker()
{
	if (_weapons[_selectedWeaponIdx] != nullptr && (_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_PISTOL || _weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_RANGE))
	{
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("bulletText"))->SetText(to_string(_weapons[_selectedWeaponIdx]->GetCurNumOfBullet()) + " / " + to_string(_weapons[_selectedWeaponIdx]->GetInitNumOfBullet()));
		UIMANAGER->GetGameFrame()->GetChild("bulletText")->SetIsViewing(true);
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("bulletText")->SetIsViewing(false);
	}

}

void Player::DashAttack()
{
	if (_weapons[_selectedWeaponIdx] != nullptr &&
		_weapons[_selectedWeaponIdx]->GetWeaponType() != WEAPONTYPE::WT_RANGE &&
		_weapons[_selectedWeaponIdx]->GetWeaponType() != WEAPONTYPE::WT_PISTOL &&
		_weapons[_selectedWeaponIdx]->GetWeaponType() != WEAPONTYPE::WT_CHARGE)
	{
		_dashAttackRect = RectMake(_x - 30, _y - 30, _vImages[0]->getFrameWidth() + 60, _vImages[0]->getFrameHeight() + 60);

		for (int i = 0; i < MAPMANAGER->GetPlayMap()->GetObjects().size(); i++)
		{
			Object* obj = MAPMANAGER->GetPlayMap()->GetObjects()[i];
			if (obj->GetType() == OBJECTTYPE::OT_MONSTER)
			{
				RECT temp;
				if (IntersectRect(&temp, &_dashAttackRect, &obj->GetBody()))
					obj->GetDamage((_dashDamage * RANDOM->range(_minDamage, _maxDamage)) / 100.f);
			}
		}
	}
}

void Player::DashImageCheck()
{
	for (int i = 0; i < _maxDashCount; i++)	//�뽬 �ִ밹���� 3���̹Ƿ� 3�� �ݺ�
	{
		if (_dashCount > i)					//���� �뽬Ƚ���� i���� Ŀ����
			_dashFrame->GetChild("dashColor" + to_string(i))->SetImage(IMAGEMANAGER->findImage("DashCount"));	//�뽬�̹��� ���
		else
			_dashFrame->GetChild("dashColor" + to_string(i))->SetImage(nullptr);	//�뽬�̹��� ����
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

	UIFrame* dashStartFrame = new UIFrame();//UI ����
	dashStartFrame->init("start", 0, 0, 6, 23, "DashBaseLeftEnd");	//UI �ʱ�ȭ
	_dashFrame->AddFrame(dashStartFrame);	//dash�����ӿ� �ڽ��߰�
	int x = 6;
	for (int i = 0; i < _maxDashCount; i++)	//�뽬 �ִ�Ƚ����ŭ �ݺ�
	{
		UIFrame* dashBar = new UIFrame();	//UI����
		dashBar->init("dashBar" + to_string(i), x, 0, 27, 24, "DashBase");	//UI �ʱ�ȭ
		_dashFrame->AddFrame(dashBar);		//dash�����ӿ� �ڽ��߰�

		UIFrame* dashColor = new UIFrame();	//UI����
		dashColor->init("dashColor" + to_string(i), x, 6, 27, 24, "DashCount");	//UI �ʱ�ȭ
		_dashFrame->AddFrame(dashColor);	//dash�����ӿ� �ڽ��߰�
		x += 23;
	}
	UIFrame* dashEndFrame = new UIFrame();	//UI����
	dashEndFrame->init("end", x, 0, 6, 23, "DashBaseRightEnd");	//UI�ʱ�ȭ
	_dashFrame->AddFrame(dashEndFrame);	//dash�����ӿ� �ڽ��߰�
}

void Player::RangeGetStatusAbility()
{
	if (_specialAbilityOn[5][0])
	{
		if (_weapons[_selectedWeaponIdx] != nullptr &&
			(_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_RANGE ||
				_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_PISTOL ||
				_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_CHARGE))
		{
			if (!_getRangeStatus)
			{
				_initHp += 20;
				_power += 10;
				_getRangeStatus = true;
			}
		}

		else
		{
			if (_getRangeStatus)
			{
				_initHp -= 20;
				_power -= 10;
				_getRangeStatus = false;
			}
		}
	}
}

void Player::SwitchWeapon()
{
	if (_swapCoolTime > 0)	//���� ��Ÿ���� 0���� Ŀ����
	{
		_swapCoolTime--;	//��Ÿ���� ����
		UIFrame* swapFrame = UIMANAGER->GetGameFrame()->GetChild("swapContainer");	//swapUI�� ����

		UIFrame* weapon1 = swapFrame->GetChild("weapon1");	//swapUI�� �ڽ��� ����
		UIFrame* weapon2 = swapFrame->GetChild("weapon2");	//swapUI�� �ڽ��� ����

		if (_swapCoolTime == 0)	//��Ÿ���� 0�̵Ǹ�
		{
			swapFrame->GetVChildFrames().push_back(swapFrame->GetVChildFrames()[0]);	//swapUI�� �ڽĵ��� 0��������
			swapFrame->GetVChildFrames().erase(swapFrame->GetVChildFrames().begin());
		}

		if (_selectedWeaponIdx == 0)	//������ ���Ⱑ 0���̶��
		{
			weapon1->MoveFrameChild(-2.5f, 2.5f);	//weaponUI�� �ڽĵ� ��ǥ����
			weapon2->MoveFrameChild(2.5f, -2.5f);	//weaponUI�� �ڽĵ� ��ǥ����
		}
		else                            //0���̾ƴ϶�� 
		{
			weapon1->MoveFrameChild(2.5f, -2.5f);
			weapon2->MoveFrameChild(-2.5f, 2.5f);
		}
	}

	if (_mouseWheel != 0)	//���콺 �� �۵���
	{
		SOUNDMANAGER->play("����_���⽺��");
		if (_swapCoolTime == 0)
		{
			if (_weapons[_selectedWeaponIdx] != nullptr)	//������ ���Ⱑ �ִٸ�
			{
				_weapons[_selectedWeaponIdx]->SetisAttacking(false);	// �ֹ��� ���� ���� �ʱ�ȭ
				_weapons[_selectedWeaponIdx]->SetRenderAngle(0);		// �ֹ��� ���� �ޱ� �ʱ�ȭ
			}
			if (_subWeapons[_selectedWeaponIdx] != nullptr)	//������ �������Ⱑ �ִٸ�
			{
				_subWeapons[_selectedWeaponIdx]->SetisAttacking(false);	// �������� ���� ���� �ʱ�ȭ
				_subWeapons[_selectedWeaponIdx]->SetRenderAngle(0);		// �������� ���� ���� �ʱ�ȭ
			}

			_realAttackSpeed = 0;

			_selectedWeaponIdx = _selectedWeaponIdx == 0 ? 1 : 0;	//������ ���Ⱑ 0�̳� ? ������ 1 �ƴϸ� 0
			_inven->SwitchWeapon(_selectedWeaponIdx);

			_swapCoolTime = 20;		//��Ÿ�� 20
		}
	}
}

void Player::JumpAttackRectUpdate()
{
	if (_specialAbilityOn[0][0])
		_jumpAttackRect = RectMake(_x - 50, _y + _vImages[0]->getFrameHeight() * 0.2f, _vImages[0]->getFrameWidth() + 100, _vImages[0]->getFrameHeight() * 1.4f);
}

void Player::AbnormalState()
{
	if (_isFire)
	{
		if (!_immuneFire)
		{
			_fireCount++;
			if (_fireCount % 20 == 0)
			{
				float x;
				float y;
				x = RANDOM->range(_body.left, _body.right);
				y = RANDOM->range(_body.top, _body.bottom);
				EFFECTMANAGER->AddEffect(x, y, "StateFireEffect", 4,
					0, 0, false, 255, 0, 1, 1, false);

			}
			if (_fireCount > 200)
			{
				_fireCount = 0;
			}
		}
	}
}

void Player::ReloadBullet()
{
	if (_weapons[_selectedWeaponIdx] == nullptr)
	{
		_reloadCount = 0;
		_isReload = false;
	}
	if (_weapons[_selectedWeaponIdx] != nullptr)
	{
		if (_weapons[_selectedWeaponIdx]->GetInitNumOfBullet() == 0)
		{
			_reloadCount = 0;
			_isReload = false;
		}

		if (_maxBullet > 0)
		{
			if (_weapons[_selectedWeaponIdx]->GetCurNumOfBullet() <= 0)
			{
				_isReload = true;
			}
		}
		if (_reloadEffect.isViewing)
		{
			_reloadEffect.frameTime++;
			if (_reloadEffect.frameTime > 4)
			{
				_reloadEffect.frameTime = 0;
				_reloadEffect.frameX++;
				if (_reloadEffect.frameX >= _reloadEffect.ig->getMaxFrameX())
				{
					_reloadEffect.frameX = 0;
					_reloadEffect.isViewing = false;
				}
			}
		}
		_reloadEffect.x = _x - 6;
		_reloadEffect.y = _y - 14;
		if (_isReload)
		{
			_reloadCount += _reloadSpeed;
			if (_reloadCount > _reloadTime)
			{
				_reloadEffect.frameX = 0;
				_reloadEffect.frameY = 0;
				_reloadEffect.isViewing = true;

				_reloadCount = 0;
				_isReload = false;
				_weapons[_selectedWeaponIdx]->SetCurNumOfBullet(_maxBullet);
			}
		}

	}

}

void Player::DamageJumpAttackRect()
{
	for (int i = 0; i < MAPMANAGER->GetPlayMap()->GetObjects().size(); i++)
	{
		Object* obj = MAPMANAGER->GetPlayMap()->GetObjects()[i];
		if (obj->GetType() == OBJECTTYPE::OT_MONSTER || obj->GetType() == OBJECTTYPE::OT_BREAKABLE)
		{
			RECT temp;
			if (IntersectRect(&temp, &_jumpAttackRect, &obj->GetBody()))
				obj->GetDamage(8);
		}
	}
}

void Player::ControlDamageUpTimer()
{
	if (_specialAbilityOn[0][1])
	{
		if (_damageUpTimerUse)
		{
			if (_damageUpTimer > 0)
			{
				_damageUpTimer--;
			}

			else
			{
				_damageUpTimer = 0;
				_power -= 10;
				_damageUpTimerUse = false;
			}
		}
	}
}

void Player::DamageUpEnemyKill()
{
	if (_specialAbilityOn[0][1])
	{
		if (_damageUpTimer == 0)
		{
			_damageUpTimer = 60 * 15;
			_damageUpTimerUse = true;
			_power += 10;
		}
		else
		{
			_damageUpTimer = 60 * 15;
			_damageUpTimerUse = true;
		}
	}
}

void Player::SpecialAtkSpeedUp()
{
	if (_specialAbilityOn[1][1])
	{
		if (!_atkSpdUpUse && (_hp / (float)_maxHp * 100 >= 80))
		{
			_atkSpeedPer += 10;
			_atkSpdUpUse = true;
		}

		if (_atkSpdUpUse && (_hp / (float)_maxHp * 100 < 80))
		{
			_atkSpeedPer -= 10;
			_atkSpdUpUse = false;
		}
	}
	else
	{
		if (_atkSpdUpUse && (_hp / (float)_maxHp * 100 < 80))
		{
			_atkSpeedPer -= 10;
			_atkSpdUpUse = false;
		}
	}
}

void Player::SetHpUI()
{
	UIProgressBar* bar = dynamic_cast<UIProgressBar*>(_hpFrame->GetChild("hpBarPros"));
	bar->FillCheck(_maxHp, _hp);
	float fillPercent = (float)_hp / _maxHp;

	UIImage* hpWave = dynamic_cast<UIImage*>(_hpFrame->GetChild("Wave"));
	hpWave->SetX((_hpFrame->GetX() + 42) + 157 * fillPercent); // ��ġ�� ������ ����ؼ� ����

	dynamic_cast<UIText*>(_hpFrame->GetChild("hp"))->SetText(to_string(_hp) + " / " + to_string(_maxHp));
}

void Player::release()
{
	_inven->release();
}

void Player::render(HDC hdc)
{
	if (!MAPMANAGER->GetPortalAnimOn() && ENTITYMANAGER->GetWormVillage()->GetRenderPlayer())	//��Ż �� ����, 
	{
		if (!_isPlayerDead)
		{
			if (_weapons[_selectedWeaponIdx] != nullptr && _weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);				//������ ������ �ε����� ��������ʰ�, �÷��̾�� ����  �׷����ٸ� �����ȹ����� �ε����� �׷�������
			if (_subWeapons[_selectedWeaponIdx] != nullptr && _subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);	//���� ���������� �ε����� ��������ʰ�, �������Ⱑ �÷��̾�� ���� �׷����ٸ�, ���������� �ε����� �׷�������
		}

		for (int i = 0; i < _vAccessories.size(); i++)		//���� �Ǽ������� �÷��̾�� ���� �׷����ٸ�, �Ǽ������� �׷�������
		{
			if (_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);
		}


		if (_useImage == 2) // �׾�����
		{
			CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
		}

		else
		{
			if (_isHit)		//�÷��̾ �������� �Ծ��ٸ�
			{
				CAMERAMANAGER->FrameAlphaRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY, _hitAlpha);		//���İ��� �̿��� ������ ȿ�� ����
			}
			else            //�÷��̾ �������� �����ʾҴٸ�
			{
				CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);						//���� �̹��� �״��
			}
		}

		if (_isReload)
		{
			CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("ReloadBase"), _x + 6, _y - 6);
			CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("ReloadBar"), _x + 6 + 69 / _reloadTime * _reloadCount, _y - 9);
		}
		if (_reloadEffect.isViewing && _useImage != 2)
		{
			CAMERAMANAGER->FrameRender(hdc, _reloadEffect.ig, _reloadEffect.x, _reloadEffect.y, _reloadEffect.frameX, _reloadEffect.frameY);
		}

		if (!_isPlayerDead)
		{
			if (_weapons[_selectedWeaponIdx] != nullptr && !_weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);			//������ ������ �ε����� ��������ʰ�, �÷��̾�� ����  �׷������ʴ´ٸ� �����ȹ����� �ε����� �׷�������
			if (_subWeapons[_selectedWeaponIdx] != nullptr && !_subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);	//���� ���������� �ε����� ��������ʰ�, �������Ⱑ �÷��̾�� ���� �׷������ʴ´ٸ�, ���������� �ε����� �׷�������
		}

		for (int i = 0; i < _vAccessories.size(); i++)
		{
			if (!_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);	//���� �Ǽ������� �÷��̾�� ���� �׷������ʴ´ٸ�, �Ǽ������� �׷�������
		}

		if (_regenEffect.isViewing && _useImage != 2)
		{
			CAMERAMANAGER->FrameRender(hdc, _regenEffect.ig, _regenEffect.x, _regenEffect.y, _regenEffect.frameX, _regenEffect.frameY);
		}

		if (_guardBreakEffect.isViewing && _useImage != 2)
		{
			CAMERAMANAGER->FrameRender(hdc, _guardBreakEffect.ig, _guardBreakEffect.x, _guardBreakEffect.y, _guardBreakEffect.frameX, _guardBreakEffect.frameY);
		}

		if (_isStun)	//���ϻ����϶�
		{
			CAMERAMANAGER->FrameRender(hdc, IMAGEMANAGER->findImage("stun"), _x + 13, _y - 10, _stunFrameX, _stunFrameY);
		}
		_inven->render(hdc);	//�κ��丮�� ���� ����

		if (_clothType == CLOTHTYPE::PC_ALICE)
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
				int runSound = RANDOM->range(1, 4);
				SOUNDMANAGER->play("�ȴ¼Ҹ� (" + to_string(runSound) + ")");
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
		_x -= _moveSpeed + ((_moveSpeedPer * _moveSpeed) / 100.f);
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
		_x += _moveSpeed + ((_moveSpeedPer * _moveSpeed) / 100.f);
		_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
	}

	if (_jumpCount == 0 || (_specialAbilityOn[1][0] && _jumpCount == 1))	//������ ���߰ų� �ѹ������� (�ż� 5 Ư��)
	{

		if (INPUT->GetKeyDown(VK_SPACE) && !_downJump)	//�����̽��ٸ� ������ �Ʒ��� �����Ѱ� �ƴҶ�
		{
			SOUNDMANAGER->play("����");
			_isJump = true;
			_jumpPower = 11;
			_y -= _jumpPower;
			_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
			_jumpCount++;
			if (_specialAbilityOn[0][0]) DamageJumpAttackRect();
		}
		if (INPUT->GetKey('S') && _isJump)	//SŰ�� �����µ� ���������� ��
		{
			_downJump = true;
			_jumpPower = -2;
			_jumpCount++;
			if (_specialAbilityOn[0][0]) DamageJumpAttackRect();
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
		if (MAPMANAGER->GetPlayMap()->GetFileName() == "stage0_town")
		{
			ENTITYMANAGER->GetWormVillage()->Activate();
		}

		else
		{
			MAPMANAGER->ChangeMap(MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_LEFT));
			MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_RIGHT);
		}
	}
	else if (_color == RGB(0, 200, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_RIGHT));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_LEFT);
	}
	else if (_color == RGB(0, 155, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_UP));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_DOWN);
	}
	else if (_color == RGB(0, 100, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_DOWN));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_UP);
	}
}

void Player::dash()
{
	_dashTimer++;
	if (_specialAbilityOn[1][2])
	{
		_dashInvincibTimer = 0.2f * 60; // �뽬 ���� �ð�
		_dashInvinCible = true;
	}

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
			_x = i - baseCharIg->getFrameWidth()-3;
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
		EFFECTMANAGER->AddEffect(_x, _y, _dashEffectCharImage->getKey(), 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 3)
	{
		EFFECTMANAGER->AddEffect(_x, _y, _dashEffectCharImage->getKey(), 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 5)
	{
		EFFECTMANAGER->AddEffect(_x, _y, _dashEffectCharImage->getKey(), 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 6)
	{
		EFFECTMANAGER->AddEffect(_x, _y, _dashEffectCharImage->getKey(), 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 7)
	{
		EFFECTMANAGER->AddEffect(_x, _y, _dashEffectCharImage->getKey(), 3, 0, _frameY, false, 150);
	}

	if (_dashTimer >= 10)
	{
		DashAttack();
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
	if (_isHit)						//�÷��̾� ������ ����
	{
		_hitCount++;				//���� ������ ���� ī��Ʈ
		if (_hitCount % 3 == 0)		//���İ� ������ ���� ������ ȿ�� ����
		{
			_hitAlpha = 255;
		}
		else
		{
			_hitAlpha = 10;
		}

		if (_hitCount > 30)			//���� ������ ���� ī��Ʈ�� 30���� Ŀ������
		{
			_isHit = false;			//�÷��̾� �������� �����ʾ���
			_hitCount = 0;			//���� ���� ���� ī��Ʈ �ʱ�ȭ
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
		dynamic_cast<UIText*>(charFrame->GetChild("moveSpeedText"))->SetText(to_string_with_precision(_moveSpeed + (_moveSpeed * _moveSpeedPer / 100), 2));
		dynamic_cast<UIText*>(charFrame->GetChild("atkSpeedText"))->SetText(to_string_with_precision(_atkSpeed + (_atkSpeed * _atkSpeedPer / 100), 2));
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

void Player::SetDeathDefencerTimerDown()
{
	if (_deathDefencerTimer > 0)
	{
		if (_guardBreakEffect.isViewing)
		{
			_guardBreakEffect.frameTime++;
			if (_guardBreakEffect.frameTime > 6)
			{
				_guardBreakEffect.frameTime = 0;
				_guardBreakEffect.frameX++;
				if (_guardBreakEffect.frameX >= _guardBreakEffect.ig->getMaxFrameX())
				{
					_guardBreakEffect.frameX = 0;
					_guardBreakEffect.isViewing = true;
				}
			}

			_guardBreakEffect.x = _x - 15;
			_guardBreakEffect.y = _y - 20;
		}

		_deathDefencerTimer--;
	}
}

void Player::RegenDefenceSkill()
{
	if (_specialAbilityOn[2][2] && _maxHp * 0.3f > _hp)
	{
		_regenTimer++;
		if (_regenTimer > 60)
		{
			_hp++;
			_regenTimer = 0;
			_regenEffect.isViewing = true;
		}
	}

	else
	{
		_regenEffect.isViewing = false;
		_regenEffect.frameTime = 0;
		_regenEffect.frameX = 0;
	}

	if (_regenEffect.isViewing)
	{
		_regenEffect.frameTime++;
		if (_regenEffect.frameTime > 6)
		{
			_regenEffect.frameTime = 0;
			_regenEffect.frameX++;
			if (_regenEffect.frameX >= _regenEffect.ig->getMaxFrameX())
			{
				_regenEffect.frameX = 0;
			}
		}

		_regenEffect.x = _x + 20;
		_regenEffect.y = _y + 10;
	}
}


void Player::GetHitDamage(int damage)
{
	if (_isHit == false &&
		!_dashInvinCible && // �뽬 �������°� �ƴϸ�
		!_deathDefencerTimer != 0) // ����ߵ� ���°� �ƴϸ� 
	{
		float Realdamage;
		int block;
		int evasion;
		int critical;
		Realdamage = damage - damage * _realDefence / 100; // �뽬�� �浹�ϸ� �⺻ 20���������� ���
		evasion = RANDOM->range(100);
		block = RANDOM->range(100);
		if (_realEvasion <= evasion) // ȸ�� ����
		{
			if (_block <= block) // ��� ����
			{
				if (_specialAbilityOn[2][1] && _hp - Realdamage <= 0 && !_deathDefencerActivated) // ����ߵ� Ư��
				{
					_deathDefencerActivated = true;
					_deathDefencerTimer = 240;
					_guardBreakEffect.isViewing = false;
				}
				else
				{
					SOUNDMANAGER->play("Hit_Player");
					_isHit = true;
					_hitCount = 0;

					if (CLOTHTYPE::PC_MASTERCHEF && _shieldPoint > 0) // ���� ����
					{
						int tempRealDamage = Realdamage;
						Realdamage = Realdamage - _shieldPoint;
						if (Realdamage < 0) Realdamage = 0;

						_shieldPoint = _shieldPoint - tempRealDamage;
						if (_shieldPoint < 0)
						{
							_shieldPoint = 0;
						}
					}

					_hp = _hp - Realdamage; // ������ ����

					EFFECTMANAGER->AddEffect(0, 0, "hit", 0, 0, 0, true, 100, 0, 1, 1, true, true);
					CAMERAMANAGER->Shake(25, 25, 6, 1);

					if (_specialAbilityOn[6][1])
					{
						_restorePrevHp = Realdamage * 0.6f;
						_restoreHpTimer = 15;
					}
				}
			}
			else
			{
				EFFECTMANAGER->AddCameraText(_x, _y, 200, 50, "BLOCK", FONT::PIX, WORDSIZE::WS_MIDDLE, WSORT_LEFT, RGB(0, 0, 255));
			}
		}
		else
		{
			EFFECTMANAGER->AddCameraText(_x, _y, 200, 50, "EVADE", FONT::PIX, WORDSIZE::WS_MIDDLE, WSORT_LEFT, RGB(0, 255, 0));
		}
	}

}

void Player::RangeItemEquip()
{
	bool findMulti = false;
	bool findBig = false;
	for (int i = 0; i < _vAccessories.size(); i++)
	{
		if (_vAccessories[i]->GetId() == 4027) // ������ź �����ִٸ�
		{
			_isEquipMulti = true;
			findMulti = true;
		}

		if (_vAccessories[i]->GetId() == 4026) // ������ �����ִٸ�
		{
			_isEquipGlass = true;

			for (int i = 0; i < ENTITYMANAGER->getVBullets().size(); i++)
			{
				if (ENTITYMANAGER->getVBullets()[i]->getType() == BT_PLAYER || ENTITYMANAGER->getVBullets()[i]->getType() == BT_PLAYERNOCOL)
				{
					ENTITYMANAGER->getVBullets()[i]->SetScale(2);
				}
			}

			findBig = true;
		}
	}

	if (!findMulti)
	{
		_isEquipMulti = false;
	}

	if (!findBig)
	{
		_isEquipGlass = false;
		for (int i = 0; i < ENTITYMANAGER->getVBullets().size(); i++)
		{
			if (ENTITYMANAGER->getVBullets()[i]->getType() == BT_PLAYER || ENTITYMANAGER->getVBullets()[i]->getType() == BT_PLAYERNOCOL)
			{
				ENTITYMANAGER->getVBullets()[i]->SetScale(1);
			}
		}
	}
}

void Player::ShieldUICheck()
{
	if (_clothType == CLOTHTYPE::PC_MASTERCHEF)
	{
		UIProgressBar* bar = dynamic_cast<UIProgressBar*>(UIMANAGER->GetGameFrame()->GetChild("ShieldBaseFrame")->GetChild("ShieldBackProgress"));
		bar->FillCheck(_maxShieldPoint, _shieldPoint);

		_shieldPoint += 0.01f;
		if (_shieldPoint > _maxShieldPoint) _shieldPoint = _maxShieldPoint;
	}
}

void Player::RestoreHpTimerChecker()
{
	if (_restoreHpTimer < 0)
	{
		_restoreHpTimer = 0;
		_restorePrevHp = 0;
	}

	else
	{
		_restoreHpTimer--;
	}
}

void Player::ControlTraitPage()
{
	if (_traitFrame->GetIsViewing())
	{
		AddTraitPoint();
		ReloadTraitPoint();
		MoveTraitUI();
		CheckTraitIconHovered();
	}
}

void Player::ReloadItemChecker()
{
	if (_specialAbilityOn[5][2])
	{
		if (_reloadItemNumber < 3)
		{
			_reloadItemTimer++;
			if (_reloadItemTimer > 600)
			{
				_reloadItemNumber++;
				_reloadItemTimer = 0;
			}
		}

		if (_reloadItemNumber > 0 && _reloadCount > 0)
		{
			_reloadCount = _reloadTime;
			_reloadItemNumber--;
		}
	}
}

void Player::AddTraitPoint()
{
	vector<string> btnNames = { "AbilityBackgroundButtonDisable_Wrath", "AbilityBackgroundButtonDisable_Swiftness", "AbilityBackgroundButtonDisable_Patience", "AbilityBackgroundButtonDisable_Arcane", "AbilityBackgroundButtonDisable_Greed", "AbilityBackgroundButtonDisable_Patience", "AbilityBackgroundButtonDisable_Wrath" };
	vector<string> btnNames2 = { "AbilityBackgroundButton_Wrath", "AbilityBackgroundButton_Swiftness", "AbilityBackgroundButton_Patience", "AbilityBackgroundButton_Arcane", "AbilityBackgroundButton_Greed", "AbilityBackgroundButton_Patience", "AbilityBackgroundButton_Wrath" };

	for (int i = 0; i < 7; i++)
	{
		UIFrame* btnFrame = _traitFrame->GetChild("trait" + to_string(i))->GetChild("btn");
		if (PtInRect(&btnFrame->GetRect(), _ptMouse))
		{
			btnFrame->SetImage(IMAGEMANAGER->findImage(btnNames2[i]));

			if (INPUT->GetIsLButtonClicked() && _remainPoint > 0)
			{
				if (_abilityNum[i] < 20)
				{
					switch (i)
					{
					case 0:
						_power += 2;
						break;

					case 1:
						_moveSpeedPer += 0.5f;
						_atkSpeedPer += 0.5f;
						break;

					case 2:
						_defence += 1.5f;
						break;

					case 3:
						_criticalPercent += 0.5f;
						_evasion += 0.5f;
						break;

					case 4:
						_initHp += 2;
						SetNewMaxHp();
						_hp = _maxHp;
						break;

					case 5:
						_criticalDamage += 2.5;
						break;

					case 6:
						_power += 1;
						break;
					}
					_abilityNum[i]++;
					_remainPoint--;
					ReInitTraitUI();
					if (_abilityNum[i] == 5 || _abilityNum[i] == 10 || _abilityNum[i] == 20)
					{
						if (_abilityNum[i] == 5)
						{
							if (i == 1) AddMaxDash();
							if (i == 2) _inven->AddItem(DATAMANAGER->GetItemById(4120));
							if (i == 4) _goldDrop += 20;
							_specialAbilityOn[i][0] = true;
						}
						else if (_abilityNum[i] == 10)
						{
							if (i == 4) _maxSatiety += 25;
							if (i == 5) _reloadSpeed += 0.15f;
							_specialAbilityOn[i][1] = true;
						}
						else if (_abilityNum[i] == 20)
						{
							if (i == 4) { _accesoryCount += 1; _inven->SetInventoryAccesoryUI(); _inven->ReloadUIImages(); }
							if (i == 6) _power += 15;
							_specialAbilityOn[i][2] = true;
							AddMaxDash();
						}
						SOUNDMANAGER->play("NPC_�Ʒü�_Ư�����");
					}
					else
					{
						SOUNDMANAGER->play("NPC_�Ʒü�_Ư�����2");
					}
					break;
				}
			}
		}
		else
		{
			btnFrame->SetImage(IMAGEMANAGER->findImage(btnNames[i]));
		}
	}
}

void Player::MoveTraitUI()
{
	if (PtInRect(&_traitFrame->GetRect(), _ptMouse) && INPUT->GetKey(VK_LBUTTON))
	{
		_uiScrollTimer++;
		if (_uiScrollTimer == 1)
		{
			_uiMouseLocation = _ptMouse.x;
		}

		else if (_uiScrollTimer > 1)
		{
			for (int i = 0; i < 7; i++)
			{
				_traitFrame->GetChild("trait" + to_string(i))->MoveFrameChild(_ptMouse.x - _uiMouseLocation, 0);
			}
			_movedX += _ptMouse.x - _uiMouseLocation;
			_uiMouseLocation = _ptMouse.x;
		}
	}

	if (INPUT->GetIsLButtonUp())
	{
		_uiScrollTimer = 0;
		_uiMouseLocation = 0;
	}
}
void Player::SetNewMaxHp()
{
	_maxHp = _initHp + (_initHp * (_maxHpPercent / 100.0f));
	if (_clothType == CLOTHTYPE::PC_HORSESWORD)
	{
		_maxHp = 40;
	}
	if (_maxHp < _hp) _hp = _maxHp;
}

void Player::ReloadTraitPoint()
{
	if (INPUT->GetKeyDown('R'))
	{
		for (int i = 0; i < 7; i++)
		{
			switch (i)
			{
			case 0:
				_power -= 2 * _abilityNum[i];
				break;

			case 1:
				_moveSpeedPer -= 0.5f * _abilityNum[i];
				_atkSpeedPer -= 0.5f * _abilityNum[i];
				break;

			case 2:
				_defence -= 1.5f * _abilityNum[i];
				break;

			case 3:
				_criticalPercent -= 0.5f * _abilityNum[i];
				_evasion -= 0.5f * _abilityNum[i];
				break;

			case 4:
				_initHp -= 2 * _abilityNum[i];
				SetNewMaxHp();
				_hp = _maxHp;
				break;

			case 5:
				_criticalDamage -= 2.5 * _abilityNum[i];
				break;

			case 6:
				_power -= 1 * _abilityNum[i];
				break;
			}
			_remainPoint += _abilityNum[i];

			if (_abilityNum[i] >= 5 && i == 1) SubMaxDash();
			if (_abilityNum[i] >= 5 && i == 2) RemoveMagicShield();
			if (_abilityNum[i] >= 5 && i == 4) _goldDrop -= 20;
			if (_abilityNum[i] >= 5 && i == 5 && _getRangeStatus) { _getRangeStatus = false, _power -= 10, _initHp -= 20; SetNewMaxHp();  if (_hp > _maxHp) _hp = _maxHp; }
			if (_abilityNum[i] >= 10 && i == 4) _maxSatiety -= 25;
			if (_abilityNum[i] >= 10 && i == 5) _reloadSpeed -= 0.15f;
			if (_abilityNum[i] >= 20 && i == 4) { _accesoryCount -= 1; _inven->SetInventoryAccesoryUI(); _inven->ReloadUIImages(); }
			if (_abilityNum[i] >= 20 && i == 6) _power -= 15;
			_abilityNum[i] = 0;

			_specialAbilityOn[i][0] = false;
			_specialAbilityOn[i][1] = false;

			if (_specialAbilityOn[i][2]) SubMaxDash();
			_specialAbilityOn[i][2] = false;

		}
		ReInitTraitUI();
	}
}

void Player::RemoveMagicShield()
{
	for (int i = 0; i < _inven->GetVItemList().size(); i++)
	{
		if (_inven->GetVItemList()[i]->GetId() == 4120)
		{
			_inven->GetVItemList().erase(_inven->GetVItemList().begin() + i);
			_inven->ReloadUIImages();
			break;
		}
	}
}

void Player::CheckTraitIconHovered()
{
	UIText* text = dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("traitToolTip")->GetChild("description"));

	bool finded = false;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			UIFrame* frame = _traitFrame->GetChild("trait" + to_string(i))->GetChild("image" + to_string(j));
			if (PtInRect(&frame->GetRect(), _ptMouse))
			{
				finded = true;
				UIMANAGER->GetGameFrame()->GetChild("traitToolTip")->SetIsViewing(true);
				UIMANAGER->GetGameFrame()->GetChild("traitToolTip")->MoveFrameChild((_ptMouse.x) - text->GetX() + 20, (_ptMouse.y) + 20 - text->GetY());
				text->SetText(_vTraitTooltip[i][j]);
				break;
			}
		}

		if (finded) break;
	}

	if (!finded) UIMANAGER->GetGameFrame()->GetChild("traitToolTip")->SetIsViewing(false);
}

void Player::ReInitTraitUI()
{
	_traitFrame->GetVChildFrames().clear();

	UIFrame* traitUpperImg = new UIFrame();
	traitUpperImg->init("title", 0, 50, IMAGEMANAGER->findImage("AbilityTItle")->getWidth(), IMAGEMANAGER->findImage("AbilityTItle")->getHeight(), "AbilityTItle");
	_traitFrame->AddFrame(traitUpperImg);

	vector<string> vImageNames = { "AbilityBackground_Wrath", "AbilityBackground_Swiftness", "AbilityBackground_Patience", "AbilityBackground_Arcane", "AbilityBackground_Greed", "AbilityBackground_0", "AbilityBackground_1" };
	vector<string> btnNames = { "AbilityBackgroundButtonDisable_Wrath", "AbilityBackgroundButtonDisable_Swiftness", "AbilityBackgroundButtonDisable_Patience", "AbilityBackgroundButtonDisable_Arcane", "AbilityBackgroundButtonDisable_Greed", "AbilityBackgroundButtonDisable_Patience", "AbilityBackgroundButtonDisable_Wrath" };
	vector<string> traitNames = { "Trait_Power_", "Trait_Speed_", "Trait_Def_", "Trait_Mystery_", "Trait_avarice_", "Trait_Concentration_", "Trait_craving_" };
	vector<COLORREF> rgbs = { RGB(64, 19, 20), RGB(178, 213, 201), RGB(170, 175, 187), RGB(154, 168, 202), RGB(222, 174, 71), RGB(176,169,178), RGB(171,90,95) };

	for (int i = 0; i < 7; i++)
	{
		UIFrame* traitMainFrame = new UIFrame();
		traitMainFrame->init("trait" + to_string(i), 50 + (250 * i) + _movedX, 200, 200, 350, vImageNames[i]);
		_traitFrame->AddFrame(traitMainFrame);

		UIText* traitNumber = new UIText();
		traitNumber->init("number", 50, 138, 100, 100, to_string(_abilityNum[i]), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, rgbs[i]);
		traitMainFrame->AddFrame(traitNumber);

		UIFrame* button = new UIFrame();
		button->init("btn", 72, 290, 54, 54, btnNames[i]);
		traitMainFrame->AddFrame(button);

		for (int j = 0; j < 3; j++)
		{
			int num;
			if (j == 0) num = 5;
			else if (j == 1) num = 10;
			else num = 20;

			int light = 1;
			if (j == 0 && _abilityNum[i] >= 5) light = 2;
			if (j == 1 && _abilityNum[i] >= 10) light = 2;
			if (j == 2 && _abilityNum[i] >= 20) light = 2;

			UIFrame* traitImage = new UIFrame();
			traitImage->init("image" + to_string(j), 37 + j * 42, 244, 50, 50, traitNames[i] + to_string(num) + "_" + to_string(light));
			traitMainFrame->AddFrame(traitImage);
		}

		UIText* text;
		UIText* text2;

		switch (i)
		{
		case 0:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string(_abilityNum[0] * 2) + " ����", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 1:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[1] * 0.5f, 1) + "% �̵��ӵ�", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			text2 = new UIText();
			text2->init("ability1", 0, 195, 200, 50, "+" + to_string_with_precision(_abilityNum[1] * 0.5f, 1) + "% ���ݼӵ�", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text2);
			break;
		case 2:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[2] * 1.5f, 1) + " ����", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 3:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[3] * 0.5f, 1) + " ũ��Ƽ��", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			text2 = new UIText();
			text2->init("ability1", 0, 195, 200, 50, "+" + to_string_with_precision(_abilityNum[3] * 0.5f, 1) + " ȸ��", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text2);
			break;
		case 4:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string(_abilityNum[4] * 2) + " �ִ� ü��", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 5:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[5] * 2.5f, 1) + "% ũ��Ƽ�� ������", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 6:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string(_abilityNum[6] * 1) + " ����", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		}
	}

	UIFrame* rImage = new UIFrame();
	rImage->init("keyR", 1000, 720, 39, 42, "Keyboard_R");
	_traitFrame->AddFrame(rImage);

	UIText* text = new UIText();
	text->init("renew", 1055, 726, 100, 50, "�ʱ�ȭ", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_LEFT);
	_traitFrame->AddFrame(text);

	UIFrame* pointFrame = new UIFrame();
	pointFrame->init("point", 1170, 690, 226, 135, "YesOrNo", 1.5f, 1.5f);
	_traitFrame->AddFrame(pointFrame);

	UIText* remainPoint = new UIText();
	remainPoint->init("remainPoint", 0, 27, 169, 67, "���� ����Ʈ : " + to_string_with_precision(_remainPoint, 0), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
	pointFrame->AddFrame(remainPoint);
}

// ������ ������ Ư��
void Player::CheckUsePistolGunner()
{
	if (_clothType == PC_GUNNER)	//�ڽ�Ƭ�� ������ ������ �����̰�
	{
		if (_weapons[_selectedWeaponIdx] != nullptr)	//���� �����ȹ��Ⱑ �ְ�
		{
			if (_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_PISTOL)	//���� �����ȹ��Ⱑ ����Ÿ���̰�
			{
				if (!_useGun)	//���ѻ���� �ƴҶ�
				{
					_power += 50;
					_useGun = true;
				}
			}
			else    //���� �����ȹ��Ⱑ �����̾ƴѵ�
			{
				if (_useGun)	//������ ��� �� ��
				{
					_power -= 50;
					_useGun = false;
				}
			}
		}
		else        //���� ������ ���Ⱑ ���µ�
		{
			if (_useGun)	//������ ���� ��
			{
				_power -= 50;
				_useGun = false;
			}
		}
	}
	else            //�ڽ�Ƭ�� ������ ������ ���°� �ƴҶ�
	{
		if (_useGun)	//������ ���Ǹ�
		{
			_power -= 50;
			_useGun = false;
		}
	}
}

// �ٸ��� Ư��
void Player::CheckAliceZone()
{
	vector<Object*> objs = MAPMANAGER->GetPlayMap()->GetObjects(); // �� �� ���� ������Ʈ �������� ����

	bool zoneInHere = false;
	for (int i = 0; i < objs.size(); i++) // ������Ʈ �� ���鼭
	{
		if (objs[i]->GetType() == OBJECTTYPE::OT_MONSTER && dynamic_cast<Enemy*>(objs[i])->GetIsSpawned()) // ������ ���Ͱ� 
		{
			if (UTIL::interactRectCircle(objs[i]->GetBody(), POINT{ (long)(_x + _vImages[_useImage]->getFrameWidth() / 2), (long)(_y + _vImages[_useImage]->getFrameHeight() / 2) }, _aliceZoneRadius))
			{ // ���� �ȿ� ���Ͱ� ���Դ��� Ȯ��
				_aliceZoneIn = true; // ���Ծ��!
				zoneInHere = true; // ���Ծ��!
				break;
			}
		}
	}

	if (!zoneInHere) // �ƹ��� �ȵ�������
	{
		_aliceZoneIn = false; // �ȵ��Ծ��!
	}
}

void Player::AdjustAlicePower()
{
	if (_clothType == PC_ALICE)
	{
		if (_aliceZoneIn)//���Ͱ� ���԰�, 
		{
			if (!_alicePowerDownCheck)	//�����̰��� ��������,
			{
				_power -= 20;
				_alicePowerDownCheck = true;
			}
		}
		else
		{
			if (_alicePowerDownCheck)
			{
				_power += 20;
				_alicePowerDownCheck = false;
			}
		}
	}
	else
	{
		if (_alicePowerDownCheck)
		{
			_power += 20;
			_alicePowerDownCheck = false;
		}
	}
}

//	��Ű���� Ư��
void Player::SetIkinaBearAngry()
{
	if (_clothType == CLOTHTYPE::PC_IKINABEAR)	//������ �ڽ�Ƭ�� ��Ű���� ����
	{
		if (_rageCurrent >= _rageMax && !_isRaging)	//���� ȭ�� ���� ȭ���� �ִ뺸�� ũ�� �������� �ƴ� ��
		{
			_isRaging = true;		//���Ž����ְ�
			_atkSpeedPer += 100;	//���ݼӵ� ����
			_rageTimer = 1200;
			_rageCurrent = 0;
			_vImages[0] = IMAGEMANAGER->findImage("bearIdle");
			_vImages[1] = IMAGEMANAGER->findImage("bearRun");
			UIMANAGER->GetGameFrame()->GetChild("IkinaBearFaceFrame")->SetIsViewing(true);
		}
		else
		{
			if (_isRaging)
			{
				_rageTimer--;
				if (_rageTimer <= 0)
				{
					_atkSpeedPer -= 100;
					_rageTimer = 1200;
					_isRaging = false;
					_vImages[0] = IMAGEMANAGER->findImage("lkinabearIdle");
					_vImages[1] = IMAGEMANAGER->findImage("lkinabearRun");
					UIMANAGER->GetGameFrame()->GetChild("IkinaBearFaceFrame")->SetIsViewing(true);
				}
			}
			else
			{
				UIMANAGER->GetGameFrame()->GetChild("IkinaBearFaceFrame")->SetIsViewing(false);
			}
		}

		dynamic_cast<UIProgressBar*>(UIMANAGER->GetGameFrame()->GetChild("IkinaBaseFrame")->GetChild("progress"))->FillCheck(_rageMax, _rageCurrent); // ���� ��ġ ����
	}
}

//	���̴� H Ư��
void Player::CheckMoveSpeedRiderH()
{
	if (_clothType == CLOTHTYPE::PC_RIDERH)
	{
		_power -= _prevPowerPlus; // ���� �����ӿ��� �߰��ƴ� power���� ������� ������

		float speedPercent = ((_moveSpeed + (_moveSpeed * _moveSpeedPer / 100)) / 15.f);
		if (speedPercent > 1) speedPercent = 1;
		_power += 50 * speedPercent;
		_prevPowerPlus = 50 * speedPercent; // �̹� �����ӿ��� ���� ������ ���� �����ӿ��� ����ϱ� ���� �����ص�
	}
}

void Player::AdaptCriminalCount(bool isPlus)
{
	int pm = isPlus ? 1 : -1;
	_power += (isPlus ? _criminalCount : _prevCriminalCount) * pm * 4;
	_defence -= (isPlus ? _criminalCount : _prevCriminalCount) * pm * 2;
	_initHp -= (isPlus ? _criminalCount : _prevCriminalCount) * pm * 1;
	SetNewMaxHp();
	if (_hp > _maxHp) _hp = _maxHp;
}

//	������ �Ƿ翧 Ư��
void Player::CheckCliminal()
{
	if (_clothType == CLOTHTYPE::PC_CRIMINAL)	//������ �ڽ�Ƭ ����
	{
		_criminalCount = 0;
		AdaptCriminalCount(false);
		// ���ְ�

		if (_weapons[0] != nullptr)	//������ ���Ⱑ �ְ�
		{
			_criminalCount++;
		}

		if (_weapons[1] != nullptr)	//������ ���Ⱑ �ְ�
		{
			_criminalCount++;
		}

		if (_subWeapons[0] != nullptr)		//������ �������⵵ �ְ�
		{
			_criminalCount++;
		}

		if (_subWeapons[1] != nullptr)		//������ �������⵵ �ְ�
		{
			_criminalCount++;
		}

		_criminalCount += _vAccessories.size();
		_criminalCount += _inven->GetVItemList().size();

		_prevCriminalCount = _criminalCount;
		AdaptCriminalCount(true);
	}
}

//	�׶׺� Ư��
void Player::Checkfasto()
{
	if (_clothType == CLOTHTYPE::PC_FATGUY)
	{
		if (_weapons[_selectedWeaponIdx] != nullptr)
		{
			if (_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_KATANA)
			{
				if (!_useMeleeWeapon)
				{
					_power += 30;
					_useMeleeWeapon = true;
				}
			}
			else if (_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_NEAR)
			{
				if (!_useMeleeWeapon)
				{
					_power += 30;
					_useMeleeWeapon = true;
				}
			}
			else if (_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_SPEAR)
			{
				if (!_useMeleeWeapon)
				{
					_power += 30;
					_useMeleeWeapon = true;
				}
			}
			else
			{
				if (_useMeleeWeapon)
				{
					_power -= 30;
					_useMeleeWeapon = false;
				}
			}
		}
		else
		{
			if (_useMeleeWeapon)
			{
				_power -= 30;
				_useMeleeWeapon = false;
			}
		}
	}
	else
	{
		if (_useMeleeWeapon)
		{
			_power -= 30;
			_useMeleeWeapon = false;
		}
	}
}

void Player::CheckMasterChef()
{
	if (_clothType == CLOTHTYPE::PC_MASTERCHEF)
	{
		UIMANAGER->GetGameFrame()->GetChild("ShieldBaseFrame")->SetIsViewing(true);
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("ShieldBaseFrame")->SetIsViewing(false);
	}

}

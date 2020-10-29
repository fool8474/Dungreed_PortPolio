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
	// 보스 //
	_isBossReady = false;
	// 코스튬 
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

	_vTraitTooltip[0][0] = "점프할 때 주변 적들에게 8의 피해";
	_vTraitTooltip[0][1] = "적을 처치하면 15초동안 위력이 10 상승";
	_vTraitTooltip[0][2] = "HP가 60% 미만일 때 무기 공격력이 최대로 적용.\n대쉬 최대 횟수 +1";
	_vTraitTooltip[1][0] = "이단 점프 가능, 대쉬 최대 횟수 +1";
	_vTraitTooltip[1][1] = "대쉬 쿨타임 감소, 현재 체력이 80% 이상일 경우 공격속도 증가";
	_vTraitTooltip[1][2] = "대쉬 도중 0.2초간 무적.\n대쉬 최대 횟수 +1";
	_vTraitTooltip[2][0] = "마법방패를 얻음";
	_vTraitTooltip[2][1] = "죽음에 이르는 피해를 입을 경우 4초동안 무적 (1번만)";
	_vTraitTooltip[2][2] = "체력이 30% 미만일 때 체력이 재생하고 방어력이 증가함.\n대쉬 최대 횟수 +1";
	_vTraitTooltip[3][0] = "상점 가격 30% 할인";
	_vTraitTooltip[3][1] = "아이템 사용효과의 쿨타임 40% 감소";
	_vTraitTooltip[3][2] = "탐험 종료시 소지중인 아이템 중 하나를 선택해 보존 가능.\n대쉬 최대 횟수 +1";
	_vTraitTooltip[4][0] = "골드 획득량 +20%";
	_vTraitTooltip[4][1] = "포만감 최대치 +25";
	_vTraitTooltip[4][2] = "액세서리 슬롯+1, 식당에서 먹는 음식의 포만감 증가량 10% 감소.\n대쉬 최대 횟수 +1";
	_vTraitTooltip[5][0] = "원거리 무기 장착시 최대 체력 +20, 방어력 +10을 획득";
	_vTraitTooltip[5][1] = "재장전속도가 15% 증가하고, 방의 모든 몬스터를 쓰러뜨릴 때마다 체력을 +2씩 회복";
	_vTraitTooltip[5][2] = "12초마다 무기 재장전을 바로 해주는 \"재장전 도구\"를 획득 (최대 3개)\n대쉬 최대 횟수 +1";
	_vTraitTooltip[6][0] = "적 직접공격시 10% 확률로 \"약화\"상태이상 부여(적에게 지속 데미지)";
	_vTraitTooltip[6][1] = "약화 상태의 적 직접공격 시 입은 데미지만큼 회복";
	_vTraitTooltip[6][2] = "위력을 +15 증가시키고 \"약화\"확률을 100%로 증가.\n대쉬 최대 횟수 +1";

	DashUICheck();

	// 예시용
	_selectedWeaponIdx = 0;

	_inven = new Inventory();
	_inven->init();

	_inven->AddItem(DATAMANAGER->GetItemById(4005));
	_inven->AddItem(DATAMANAGER->GetItemById(4006));
	_inven->AddItem(DATAMANAGER->GetItemById(4025));
	_inven->AddItem(DATAMANAGER->GetItemById(4028));
	_inven->AddItem(DATAMANAGER->GetItemById(4029));
	_inven->AddItem(DATAMANAGER->GetItemById(4100));
	_inven->AddItem(DATAMANAGER->GetItemById(4021));
	_inven->AddItem(DATAMANAGER->GetItemById(4026));
	_inven->AddItem(DATAMANAGER->GetItemById(4052));
	_inven->AddItem(DATAMANAGER->GetItemById(5200));
	_inven->AddItem(DATAMANAGER->GetItemById(4031));
	_inven->AddItem(DATAMANAGER->GetItemById(4027));
	_inven->AddItem(DATAMANAGER->GetItemById(5201));

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
			!UIMANAGER->GetGameFrame()->GetChild("CheckExit")->GetIsViewing() &&
			!_traitFrame->GetIsViewing() &&
			!ENTITYMANAGER->GetWormVillage()->GetIsOn() &&
			!MAPMANAGER->GetPortalAnimOn() &&
			!MAPMANAGER->GetStageChanger()->GetIsChangingStage() &&
			!_isStun &&
			!_isPlayerDead &&
			!_isBossReady
			)

			// 잡다한 UI가 OFF일때
		{
			RangeItemEquip();
			if (INPUT->GetIsRButtonClicked() && _dashCount > 0)		//마우스 오른쪽 버튼을누르고,대쉬카운트가 0보다 클때
			{
				SOUNDMANAGER->play("대쉬소리");
				_isDash = true;
				_dashPoint = _ptMouse;
				_jumpPower = 0;
				_dashCount--;
				DashImageCheck();;
			}


			if (CAMERAMANAGER->GetRelativeX(_x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() / 2) >= _ptMouse.x)
			{	//플레이어의 중점+이미지 가로길이의 반이 마우스 x좌표보다 크거나 같을때
				_isLeft = true;		//왼쪽을 바라보게
			}
			else
			{
				_isLeft = false;	//오른쪽을 바라보게
			}

			if (_isDash)			//대쉬 상태
			{
				this->dash();		//대쉬를 해야하므로 dash함수 실행
			}
			else
			{
				this->Move();		//대쉬 상태가 아니므로 Move함수 실행
			}

			_realAttackSpeed--;
			if (INPUT->GetKey(VK_LBUTTON))	//만약 왼쪽 버튼을누르면
			{
				if (_weapons[_selectedWeaponIdx] != nullptr)	//장착된무기가 있고, 공격 타이머가 충족되었다면
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

		else // 잡다한 UI가 ON
		{
			_inven->update();
		}

		if (_isStun)				//스턴상태
		{
			_stunCount++;			//스턴 유지카운트
			if (_stunCount > 40)	//스턴 유지 카운트가 40보다 작을때
			{
				_isStun = false;	//스턴 상태 아님
				_stunCount = 0;		//스턴 유지 카운트는 초기화
			}
			_stunAniCout++;			//스턴 애니메이션 카운트
			if (_stunAniCout > 5)	//스턴 애니메이션 카운트가 5보다 크면
			{
				_stunAniCout = 0;	//스턴 애니메이션 카운트를 0으로
				_stunFrameX++;
				if (_stunFrameX > 5)
				{
					_stunFrameX = 0;
				}
			}
		}

		Animation();
		SwitchWeapon();
		if (_weapons[_selectedWeaponIdx] != nullptr) _weapons[_selectedWeaponIdx]->update();		//장착된 주무기가 있다면, 업데이트 함수 실행
		if (_subWeapons[_selectedWeaponIdx] != nullptr) _subWeapons[_selectedWeaponIdx]->update();	//장착된 보조무기가 있다면, 업데이트 함수 실행
		for (int i = 0; i < _vAccessories.size(); i++)	//악세서리 사이즈만큼 돌면서
		{
			_vAccessories[i]->update();					//악세서리의 업데이트함수를 실행
		}

		// 캐릭터 능력
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

		// 특성 관련
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

		//나중에 대쉬최대횟수 증가시킬때 필요
		if (INPUT->GetKeyDown('K'))		//K키를 눌렀을때
		{
			SubMaxDash();
		}

		if (_maxDashCount > _dashCount)	//대쉬 최대 횟수가 대쉬횟수보다 커지면
		{
			_dashRestoreCount++;	//대쉬 횟수 복구 카운트 증가

			if (_dashRestoreCount > (_specialAbilityOn[1][1] ? _dashRestoreTime - 15 : _dashRestoreTime))	//대쉬 횟수 복구 카운트가 대쉬 복구 시간보다 커지면
			{
				_dashRestoreCount = 0;	//대쉬 횟수 복구 카운트 초기화
				_dashCount++;			//대쉬 횟수 증가
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
		SOUNDMANAGER->play("몬스터_사망(1)");
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
		if (_playerDeadCount < 2)	//죽은후 타이머가 0보다 클때
		{
			_useImage = 2;			//죽은 이미지
			_hp = 0;				//체력 0
			_playerDeadTimer--;		//죽은 후 타이머 감소

			if (_playerDeadTimer == 0)
			{
				_useImage = 0;
				_hp = _maxHp;
				_isPlayerDead = false;
				_playerDeadCount++;
			}
		}

		else // 부활 다씀
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
	if (_maxDashCount > 0) _maxDashCount--;	// 대쉬 최대 횟수가 0보다 클때 최대횟수 감소
	if (_dashCount > _maxDashCount) _dashCount--;	//대쉬횟수가 최대 횟수보다 커지면 대쉬횟수 감소
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
	for (int i = 0; i < _maxDashCount; i++)	//대쉬 최대갯수가 3개이므로 3번 반복
	{
		if (_dashCount > i)					//만약 대쉬횟수가 i보다 커지면
			_dashFrame->GetChild("dashColor" + to_string(i))->SetImage(IMAGEMANAGER->findImage("DashCount"));	//대쉬이미지 출력
		else
			_dashFrame->GetChild("dashColor" + to_string(i))->SetImage(nullptr);	//대쉬이미지 없음
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

	UIFrame* dashStartFrame = new UIFrame();//UI 저장
	dashStartFrame->init("start", 0, 0, 6, 23, "DashBaseLeftEnd");	//UI 초기화
	_dashFrame->AddFrame(dashStartFrame);	//dash프레임에 자식추가
	int x = 6;
	for (int i = 0; i < _maxDashCount; i++)	//대쉬 최대횟수만큼 반복
	{
		UIFrame* dashBar = new UIFrame();	//UI저장
		dashBar->init("dashBar" + to_string(i), x, 0, 27, 24, "DashBase");	//UI 초기화
		_dashFrame->AddFrame(dashBar);		//dash프레임에 자식추가

		UIFrame* dashColor = new UIFrame();	//UI저장
		dashColor->init("dashColor" + to_string(i), x, 6, 27, 24, "DashCount");	//UI 초기화
		_dashFrame->AddFrame(dashColor);	//dash프레임에 자식추가
		x += 23;
	}
	UIFrame* dashEndFrame = new UIFrame();	//UI저장
	dashEndFrame->init("end", x, 0, 6, 23, "DashBaseRightEnd");	//UI초기화
	_dashFrame->AddFrame(dashEndFrame);	//dash프레임에 자식추가
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
	if (_swapCoolTime > 0)	//스왑 쿨타임이 0보다 커지면
	{
		_swapCoolTime--;	//쿨타임을 감소
		UIFrame* swapFrame = UIMANAGER->GetGameFrame()->GetChild("swapContainer");	//swapUI를 저장

		UIFrame* weapon1 = swapFrame->GetChild("weapon1");	//swapUI의 자식을 저장
		UIFrame* weapon2 = swapFrame->GetChild("weapon2");	//swapUI의 자식을 저장

		if (_swapCoolTime == 0)	//쿨타임이 0이되면
		{
			swapFrame->GetVChildFrames().push_back(swapFrame->GetVChildFrames()[0]);	//swapUI의 자식들을 0번지부터
			swapFrame->GetVChildFrames().erase(swapFrame->GetVChildFrames().begin());
		}

		if (_selectedWeaponIdx == 0)	//장착된 무기가 0번이라면
		{
			weapon1->MoveFrameChild(-2.5f, 2.5f);	//weaponUI의 자식도 좌표변경
			weapon2->MoveFrameChild(2.5f, -2.5f);	//weaponUI의 자식도 좌표변경
		}
		else                            //0번이아니라면 
		{
			weapon1->MoveFrameChild(2.5f, -2.5f);
			weapon2->MoveFrameChild(-2.5f, 2.5f);
		}
	}

	if (_mouseWheel != 0 ||
		(INPUT->GetKeyDown('1') &&	_selectedWeaponIdx == 1) ||
		(INPUT->GetKeyDown('2') && _selectedWeaponIdx == 0))
	{
		SOUNDMANAGER->play("게임_무기스왑");
		if (_swapCoolTime == 0)
		{
			if (_weapons[_selectedWeaponIdx] != nullptr)	//장착된 무기가 있다면
			{
				_weapons[_selectedWeaponIdx]->SetisAttacking(false);	// 주무기 공격 상태 초기화
				_weapons[_selectedWeaponIdx]->SetRenderAngle(0);		// 주무기 렌더 앵글 초기화
			}
			if (_subWeapons[_selectedWeaponIdx] != nullptr)	//장착된 보조무기가 있다면
			{
				_subWeapons[_selectedWeaponIdx]->SetisAttacking(false);	// 보조무기 공격 상태 초기화
				_subWeapons[_selectedWeaponIdx]->SetRenderAngle(0);		// 보조무기 렌더 상태 초기화
			}

			_realAttackSpeed = 0;

			_selectedWeaponIdx = _selectedWeaponIdx == 0 ? 1 : 0;	//장착된 무기가 0이냐 ? 맞으면 1 아니면 0
			_inven->SwitchWeapon(_selectedWeaponIdx);

			_swapCoolTime = 20;		//쿨타임 20
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

		if (_maxBullet > 0 && _weapons[_selectedWeaponIdx]->GetCurNumOfBullet() < _maxBullet) // 맥스 불릿이 0보다 크거나 현재 총알 갯수가 맥스 불릿보다 작을 때
		{
			if (_weapons[_selectedWeaponIdx]->GetCurNumOfBullet() <= 0 || INPUT->GetKeyDown('R')) // 총알이 0이 되거나 R키를 누르면
			{
				_isReload = true; // 재장전 하기
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
	hpWave->SetX((_hpFrame->GetX() + 42) + 157 * fillPercent); // 수치는 적당히 계산해서 넣음

	dynamic_cast<UIText*>(_hpFrame->GetChild("hp"))->SetText(to_string(_hp) + " / " + to_string(_maxHp));
}

void Player::release()
{
	_inven->release();
}

void Player::render(HDC hdc)
{
	if (!MAPMANAGER->GetPortalAnimOn() && ENTITYMANAGER->GetWormVillage()->GetRenderPlayer())	//포탈 온 상태, 
	{
		if (!_isPlayerDead)
		{
			if (_weapons[_selectedWeaponIdx] != nullptr && _weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);				//장착된 무기의 인덱스가 비어있지않고, 플레이어보다 먼저  그려진다면 장착된무기의 인덱스가 그려지도록
			if (_subWeapons[_selectedWeaponIdx] != nullptr && _subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);	//만약 보조무기의 인덱스가 비어있지않고, 보조무기가 플레이어보다 먼저 그려진다면, 보조무기의 인덱스가 그려지도록
		}

		for (int i = 0; i < _vAccessories.size(); i++)		//만약 악세서리가 플레이어보다 먼저 그려진다면, 악세서리가 그려지도록
		{
			if (_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);
		}


		if (_useImage == 2) // 죽었으면
		{
			CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
		}

		else
		{
			if (_isHit)		//플레이어가 데미지를 입었다면
			{
				CAMERAMANAGER->FrameAlphaRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY, _hitAlpha);		//알파값을 이용해 깜빡임 효과 연출
			}
			else            //플레이어가 데미지를 입지않았다면
			{
				CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);						//기존 이미지 그대로
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
			if (_weapons[_selectedWeaponIdx] != nullptr && !_weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);			//장착된 무기의 인덱스가 비어있지않고, 플레이어보다 먼저  그려지지않는다면 장착된무기의 인덱스가 그려지도록
			if (_subWeapons[_selectedWeaponIdx] != nullptr && !_subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);	//만약 보조무기의 인덱스가 비어있지않고, 보조무기가 플레이어보다 먼저 그려지지않는다면, 보조무기의 인덱스가 그려지도록
		}

		for (int i = 0; i < _vAccessories.size(); i++)
		{
			if (!_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);	//만약 악세서리가 플레이어보다 먼저 그려지지않는다면, 악세서리가 그려지도록
		}

		if (_regenEffect.isViewing && _useImage != 2)
		{
			CAMERAMANAGER->FrameRender(hdc, _regenEffect.ig, _regenEffect.x, _regenEffect.y, _regenEffect.frameX, _regenEffect.frameY);
		}

		if (_guardBreakEffect.isViewing && _useImage != 2)
		{
			CAMERAMANAGER->FrameRender(hdc, _guardBreakEffect.ig, _guardBreakEffect.x, _guardBreakEffect.y, _guardBreakEffect.frameX, _guardBreakEffect.frameY);
		}

		if (_isStun)	//스턴상태일때
		{
			CAMERAMANAGER->FrameRender(hdc, IMAGEMANAGER->findImage("stun"), _x + 13, _y - 10, _stunFrameX, _stunFrameY);
		}
		_inven->render(hdc);	//인벤토리의 렌더 실행

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
				SOUNDMANAGER->play("걷는소리 (" + to_string(runSound) + ")");
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
	_isJump = false;				//처음은 점프상태가 아니기때문에
	if (INPUT->GetKey('A'))			//A키를 눌렀을 때
	{
		_leftBack = false;			//던그리드는 마우스 좌표로 방향을 표시
		if (!_isLeft)
		{
			_rightBack = true;
		}

		_state = PS_MOVE;			//이미지 상태 이동상태로
		_x -= _moveSpeed + ((_moveSpeedPer * _moveSpeed) / 100.f);
		_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	}
	if (INPUT->GetKeyUp('A'))		//A키를 눌렀다가 뗏을때
	{
		_state = PS_IDLE;			//이미지 상태 대기상태로
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

	if (_jumpCount == 0 || (_specialAbilityOn[1][0] && _jumpCount == 1))	//점프를 안했거나 한번했을때 (신속 5 특성)
	{

		if (INPUT->GetKeyDown(VK_SPACE) && !_downJump)	//스페이스바를 누르고 아래로 점프한게 아닐때
		{
			SOUNDMANAGER->play("점프");
			_isJump = true;
			_jumpPower = 11;
			_y -= _jumpPower;
			_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
			_jumpCount++;
			if (_specialAbilityOn[0][0]) DamageJumpAttackRect();
		}
		if (INPUT->GetKey('S') && _isJump)	//S키를 눌렀는데 점프상태일 때
		{
			_downJump = true;
			_jumpPower = -2;
			_jumpCount++;
			if (_specialAbilityOn[0][0]) DamageJumpAttackRect();
		}
	}

	if (_downJump)							//다운 점프 상태일 때
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
	//////////////////////////// 픽셀충돌 //////////////////////////////
	float _speedCheck = _moveSpeed + ((_moveSpeedPer * _moveSpeed) / 100.f);
	bool isCollide = false; // 충돌 했는지 여부
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

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // 빨간색 픽셀충돌용 땅에 닿았다
		{
			isCollide = true; // 충돌했으면 얘를 ON
			_bottomCol = true; // 아래 충돌해있다
			_jumpPower = -2;	  // 떨어질때도 자연스럽게 떨어지게 하기위해 점프파워 초기화


			_y = i - baseCharIg->getFrameHeight();// 올라간다
			_jumpCount = 0;
			break;
		}

		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false && _isDash == false) // 파란색 픽셀충돌용 땅에 닿았고 떨어지는 상태라면
		{
			isCollide = true;		// 충돌했으면 얘를 ON
			_jumpPower = -2;		// 떨어질때도 자연스럽게 떨어지게 하기위해 점프파워 초기화

			_y = i - baseCharIg->getFrameHeight();// 올라간다
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


			if ((r == 255 && g == 0 && b == 0)) // 빨간색 픽셀충돌용 땅에 닿았다
			{
				_jumpPower = -2;
				_y = i + 5;

				break;
			}
		}
	}
	if (!isCollide) //충돌해있지 않다면
	{
		_y -= _jumpPower;			//중력적용
		_jumpPower -= _gravity;

		if (_jumpPower < -20)		//점프파워가 -20보다 작을때
		{
			_jumpPower = -20;		//더이상 -되지않게 점프파워 값을 고정
		}
		_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	}

	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + _speedCheck; i++)
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
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + _speedCheck; i++)
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
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + _speedCheck; i++)
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

	//왼쪽아래
	for (int i = _x + 15; i > _x - _speedCheck; i--)
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
	//왼쪽중간
	for (int i = _x + 15; i > _x - _speedCheck; i--)
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
	//왼쪽위
	for (int i = _x + 15; i > _x - _speedCheck; i--)
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

	// 포탈 검사
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
		_dashInvincibTimer = 0.2f * 60; // 대쉬 무적 시간
		_dashInvinCible = true;
	}

	_x += cosf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
	_y += -sinf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
	_body = RectMake(_x + 10, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 20, IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();


	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");


	//대쉬할때만 속도가 바뀌므로 픽셀충돌 범위늘려서 따로검사
	for (int i = _probeBottom - 20; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);				//색깔 값 넣어주기
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // 빨간색 픽셀충돌용 땅에 닿았다
		{

			_y = i - baseCharIg->getFrameHeight();// 올라간다
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
		_dashTimer = 0;		//대쉬 타이머 초기화
		_jumpPower = 0;		//점프 파워 초기화
		_isDash = false;	//대쉬상태가 아님
	}
}

void Player::GetDamage()
{


}

void Player::invincibility()
{
	if (_isHit)						//플레이어 데미지 입음
	{
		_hitCount++;				//무적 유지를 위한 카운트
		if (_hitCount % 3 == 0)		//알파값 번경을 통해 깜빡임 효과 연출
		{
			_hitAlpha = 255;
		}
		else
		{
			_hitAlpha = 10;
		}

		if (_hitCount > 30)			//무적 유지를 위한 카운트가 30보다 커졌을때
		{
			_isHit = false;			//플레이어 데미지를 입지않았음
			_hitCount = 0;			//무적 유지 위한 카운트 초기화
		}

	}
}

/// <summary>
/// 캐릭터 페이지가 켜져있을때 계속해서 업데이트해준다.
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
/// 캐릭터 페이지의 툴팁을 온오프하고 내용물을 바꾼다.
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
/// 몇번째 스탯인가에 따라 툴팁 내용을 알맞게 수정한다.
/// </summary>
void Player::ReInitTooltip(int n)
{
	switch (n)
	{
	case 0:
		_vToolTips[0].init("powerImg", "무기공격력 (위력)", "\"위력\"은 무기 공격력을 기반으로 추가 피해량에 영향을 줍니다.", "현재 위력: " + to_string(_power) + "(데미지 보너스)", 3.0f, 1.7f);
		break;
	case 1:
		_vToolTips[1].init("defImg", "방어력", "받는 피해를 경감시켜줍니다.", "피해감소량: " + to_string_with_precision(_realDefence, 1) + "%", 3.0f, 1.7f);
		break;

	case 2:
		_vToolTips[2].init("toughImg", "강인함", "강인함 수치에 따라 고정값의 피해를 경감시켜줍니다.", "", 3.0f, 1.3f);
		break;

	case 3:
		_vToolTips[3].init("blockImg", "막기", "적의 공격을 막을 수 있는 확률을 증가시킵니다.", "막기 확률: " + to_string_with_precision(_block, 0) + "%", 3.0f, 1.7f);
		break;

	case 4:
		_vToolTips[4].init("criImg", "크리티컬", "적에게 치명적인 피해를 입힐 수 있는 기회가 늘어납니다.", "크리티컬 확률: " + to_string_with_precision(_realCriticalPercent, 1) + "%", 3.0f, 1.7f);
		break;

	case 5:
		_vToolTips[5].init("criDmgImg", "크리티컬 데미지", "크리티컬 추가 피해량을 나타냅니다.", "", 3.0f, 1.3f);
		break;

	case 6:
		_vToolTips[6].init("evadeImg", "회피", "적의 공격을 회피할 수 있는 확률을 증가시킵니다.", "회피 확률: " + to_string_with_precision(_realEvasion, 1) + "%", 3.0f, 1.3f);
		break;

	case 7:
		_vToolTips[7].init("moveSpeedImg", "이동속도", "더 빠르게 움직이게 해줍니다.", "", 3.0f, 1.3f);
		break;

	case 8:
		_vToolTips[8].init("atkSpeedImg", "공격속도", "1초에 공격할 수 있는 횟수를 나타냅니다.", "", 3.0f, 1.3f);
		break;

	case 9:
		_vToolTips[9].init("reloadImg", "재장전속도", "재장전 시 걸리는 속도를 나타냅니다.", "", 3.0f, 1.3f);
		break;

	case 10:
		_vToolTips[10].init("dashImg", "대쉬 공격력", "대쉬 공격력은 무기 공격력의 %로 계산됩니다.", "", 3.0f, 1.3f);
		break;

	case 11:
		_vToolTips[11].init("trueDamageImg", "고정 데미지", "적의 방어력 등을 무시하고 고정된 피해를 입힙니다", "", 3.0f, 1.3f);
		break;

	case 12:
		_vToolTips[12].init("burnImg", "화상 피해 강화", "적을 불태워 짧은시간동안 데미지를 줍니다.", "", 3.0f, 1.3f);
		break;

	case 13:
		_vToolTips[13].init("poisonImg", "중독 피해 강화", "적을 중독시켜 긴 시간동안 데미지를 줍니다.", "", 3.0f, 1.3f);
		break;

	case 14:
		_vToolTips[14].init("coldImg", "추위 피해 강화", "적을 느리게 만듭니다.", "", 3.0f, 1.3f);
		break;

	case 15:
		_vToolTips[15].init("elecImg", "감전 피해 강화", "적의 방어력을 무효화 시킵니다.", "", 3.0f, 1.3f);
		break;

	case 16:
		_vToolTips[16].init("stunImg", "기절 피해 강화", "적을 일시적으로 행동불능으로 만듭니다.", "", 3.0f, 1.3f);
		break;

	}
}

/// <summary>
/// 툴팁의 내용물을 바꾸고, 위치를 알맞게 수정한다.
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
		!_dashInvinCible && // 대쉬 무적상태가 아니면
		!_deathDefencerTimer != 0) // 고통견딤 상태가 아니면 
	{
		float Realdamage;
		int block;
		int evasion;
		int critical;
		Realdamage = damage - damage * _realDefence / 100; // 대쉬시 충돌하면 기본 20데미지에서 계산
		evasion = RANDOM->range(100);
		block = RANDOM->range(100);
		if (_realEvasion <= evasion) // 회피 실패
		{
			if (_block <= block) // 블록 실패
			{
				if (_specialAbilityOn[2][1] && _hp - Realdamage <= 0 && !_deathDefencerActivated) // 고통견딤 특성
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

					if (CLOTHTYPE::PC_MASTERCHEF && _shieldPoint > 0) // 쉴드 까임
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

					_hp = _hp - Realdamage; // 데미지 받음

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
		if (_vAccessories[i]->GetId() == 4027) // 갈래총탄 끼고있다면
		{
			_isEquipMulti = true;
			findMulti = true;
		}

		if (_vAccessories[i]->GetId() == 4026) // 돋보기 끼고있다면
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
						SOUNDMANAGER->play("NPC_훈련소_특성찍기");
					}
					else
					{
						SOUNDMANAGER->play("NPC_훈련소_특성찍기2");
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
			text->init("ability0", 0, 210, 200, 50, "+" + to_string(_abilityNum[0] * 2) + " 위력", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 1:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[1] * 0.5f, 1) + "% 이동속도", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			text2 = new UIText();
			text2->init("ability1", 0, 195, 200, 50, "+" + to_string_with_precision(_abilityNum[1] * 0.5f, 1) + "% 공격속도", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text2);
			break;
		case 2:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[2] * 1.5f, 1) + " 방어력", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 3:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[3] * 0.5f, 1) + " 크리티컬", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			text2 = new UIText();
			text2->init("ability1", 0, 195, 200, 50, "+" + to_string_with_precision(_abilityNum[3] * 0.5f, 1) + " 회피", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text2);
			break;
		case 4:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string(_abilityNum[4] * 2) + " 최대 체력", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 5:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string_with_precision(_abilityNum[5] * 2.5f, 1) + "% 크리티컬 데미지", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		case 6:
			text = new UIText();
			text->init("ability0", 0, 210, 200, 50, "+" + to_string(_abilityNum[6] * 1) + " 위력", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
			traitMainFrame->AddFrame(text);
			break;
		}
	}

	UIFrame* rImage = new UIFrame();
	rImage->init("keyR", 1000, 720, 39, 42, "Keyboard_R");
	_traitFrame->AddFrame(rImage);

	UIText* text = new UIText();
	text->init("renew", 1055, 726, 100, 50, "초기화", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_LEFT);
	_traitFrame->AddFrame(text);

	UIFrame* pointFrame = new UIFrame();
	pointFrame->init("point", 1170, 690, 226, 135, "YesOrNo", 1.5f, 1.5f);
	_traitFrame->AddFrame(pointFrame);

	UIText* remainPoint = new UIText();
	remainPoint->init("remainPoint", 0, 27, 169, 67, "남은 포인트 : " + to_string_with_precision(_remainPoint, 0), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE);
	pointFrame->AddFrame(remainPoint);
}

// 석양의 총잡이 특성
void Player::CheckUsePistolGunner()
{
	if (_clothType == PC_GUNNER)	//코스튬이 석양의 총잡이 상태이고
	{
		if (_weapons[_selectedWeaponIdx] != nullptr)	//만약 장착된무기가 있고
		{
			if (_weapons[_selectedWeaponIdx]->GetWeaponType() == WEAPONTYPE::WT_PISTOL)	//만약 장착된무기가 권총타입이고
			{
				if (!_useGun)	//권총사용이 아닐때
				{
					_power += 50;
					_useGun = true;
				}
			}
			else    //만약 장착된무기가 권총이아닌데
			{
				if (_useGun)	//권총이 사용 될 때
				{
					_power -= 50;
					_useGun = false;
				}
			}
		}
		else        //만약 장착된 무기가 없는데
		{
			if (_useGun)	//권총이 사용될 때
			{
				_power -= 50;
				_useGun = false;
			}
		}
	}
	else            //코스튬이 석양의 총잡이 상태가 아닐때
	{
		if (_useGun)	//권총이 사용되면
		{
			_power -= 50;
			_useGun = false;
		}
	}
}

// 앨리스 특성
void Player::CheckAliceZone()
{
	vector<Object*> objs = MAPMANAGER->GetPlayMap()->GetObjects(); // 각 맵 안의 오브젝트 가져오기 위함

	bool zoneInHere = false;
	for (int i = 0; i < objs.size(); i++) // 오브젝트 쭉 돌면서
	{
		if (objs[i]->GetType() == OBJECTTYPE::OT_MONSTER && dynamic_cast<Enemy*>(objs[i])->GetIsSpawned()) // 스폰된 몬스터가 
		{
			if (UTIL::interactRectCircle(objs[i]->GetBody(), POINT{ (long)(_x + _vImages[_useImage]->getFrameWidth() / 2), (long)(_y + _vImages[_useImage]->getFrameHeight() / 2) }, _aliceZoneRadius))
			{ // 범위 안에 몬스터가 들어왔는지 확인
				_aliceZoneIn = true; // 들어왔어요!
				zoneInHere = true; // 들어왔어요!
				break;
			}
		}
	}

	if (!zoneInHere) // 아무도 안들어왔을때
	{
		_aliceZoneIn = false; // 안들어왔어요!
	}
}

void Player::AdjustAlicePower()
{
	if (_clothType == PC_ALICE)
	{
		if (_aliceZoneIn)//몬스터가 들어왔고, 
		{
			if (!_alicePowerDownCheck)	//위력이감소 안했을때,
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

//	이키나곰 특성
void Player::SetIkinaBearAngry()
{
	if (_clothType == CLOTHTYPE::PC_IKINABEAR)	//선택한 코스튬이 이키나곰 상태
	{
		if (_rageCurrent >= _rageMax && !_isRaging)	//현재 화난 값이 화남값 최대보다 크고 변신중이 아닐 때
		{
			_isRaging = true;		//변신시켜주고
			_atkSpeedPer += 100;	//공격속도 증가
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

		dynamic_cast<UIProgressBar*>(UIMANAGER->GetGameFrame()->GetChild("IkinaBaseFrame")->GetChild("progress"))->FillCheck(_rageMax, _rageCurrent); // 차는 수치 변경
	}
}

//	라이더 H 특성
void Player::CheckMoveSpeedRiderH()
{
	if (_clothType == CLOTHTYPE::PC_RIDERH)
	{
		_power -= _prevPowerPlus; // 저번 프레임에서 추가됐던 power량을 원래대로 돌려줌

		float speedPercent = ((_moveSpeed + (_moveSpeed * _moveSpeedPer / 100)) / 15.f);
		if (speedPercent > 1) speedPercent = 1;
		_power += 50 * speedPercent;
		_prevPowerPlus = 50 * speedPercent; // 이번 프레임에서 계산된 비율을 다음 프레임에서 사용하기 위해 저장해둠
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

//	범죄자 실루엣 특성
void Player::CheckCliminal()
{
	if (_clothType == CLOTHTYPE::PC_CRIMINAL)	//범죄자 코스튬 상태
	{
		_criminalCount = 0;
		AdaptCriminalCount(false);
		// 빼주고

		if (_weapons[0] != nullptr)	//장착된 무기가 있고
		{
			_criminalCount++;
		}

		if (_weapons[1] != nullptr)	//장착된 무기가 있고
		{
			_criminalCount++;
		}

		if (_subWeapons[0] != nullptr)		//장착된 보조무기도 있고
		{
			_criminalCount++;
		}

		if (_subWeapons[1] != nullptr)		//장착된 보조무기도 있고
		{
			_criminalCount++;
		}

		_criminalCount += _vAccessories.size();
		_criminalCount += _inven->GetVItemList().size();

		_prevCriminalCount = _criminalCount;
		AdaptCriminalCount(true);
	}
}

//	뚱뚱보 특성
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

#pragma once
#include "Object.h"
#include "inventory.h"
#include "Item.h"

class CharToolTip
{
public :
	string frameName;
	string title;
	string description;
	string additionalDescription;
	float scaleX;
	float scaleY;

	void init(string fn, string t, string des, string add, float xSize, float ySize)
	{
		frameName = fn;
		title = t;
		description = des;
		additionalDescription = add;
		scaleX = xSize;
		scaleY = ySize;
	}
};

//ĳ���� ����
enum PLAYERSTATE
{
	PS_IDLE,PS_JUMP,PS_MOVE,PS_DIE,
};
struct ReloadEffect
{
	image* ig;
	float x;
	float y; 
	int frameX;
	int frameY;
	int frameTime;
	bool isViewing;
};
enum CLOTHTYPE
{
	PC_NORMAL, PC_METAL, PC_GUNNER, PC_ALICE, PC_HONGRYAN, PC_IKINABEAR, 
	PC_RIDERH, PC_CRIMINAL, PC_PICKKING, PC_FATGUY, 
	PC_HORSESWORD, PC_HUMANLASLEY, PC_MASTERCHEF
};
class Player : public Object
{
private:
	// ���¸ӽ� // 
	// - ������ ��ġ
	PLAYERSTATE		_state;					// ĳ���� ����
	bool			_isLeft;				// �������� (�ƴҽ� ������)
	bool			_jump;					// ������ �ߴ���
	bool			_isJump;				// ����������
	bool			_downJump;				// �Ʒ�����������
	bool			_isDash;
	bool			_isPlayerDead;

	bool			_isReload;
	float			_reloadCount;
	ReloadEffect	_reloadEffect;
	int				_bulletCount;
	int				_maxBullet;
	
	// �ǰݰ���
	bool			_isStun;				//���ϻ�������
	int				_stunCount;
	int				_stunAniCout;
	int				_stunFrameX;
	int				_stunFrameY;
	bool			_isHit;					// �÷��̾ �������� �Ծ�����
	int				_hitCount;				// ��Ʈ�� �����ð� ���¿�
	int				_hitAlpha;				//	��Ʈ�� ���� ���İ�

	// �̵� ���� //					   
	// - ǥ���� ��ġ
	float			_moveSpeed;				// �̵��ӵ�
	float			_jumpPower;				// ������
	int				_dashCount;				// �뽬 Ƚ��
	int				_dashRestoreCount;		// �뽬 ����ī��Ʈ
	int				_dashRestoreTime;		// �뽬 �����ð�
	int				_maxDashCount;			// �ִ� �뽬 Ƚ��

	// - ������ ��ġ
	float			_gravity;				// �߷�
	float			_dashSpeed;				// �뽬 �ӵ�
	Effect*			_dashEffect;			// �뽬 ����Ʈ
	int				_jumpCount;				// ���� Ƚ��
	int				_downJumpTimer;			// �Ʒ� ����
	POINT			_dashPoint;				// �뽬 ��ġ
	int				_dashTimer;				// �뽬 �ð�
	float			_moveSpeedPer;			// �̵��ӵ� �ۼ�Ʈ

	// ���� ���� //			
	// - ǥ���� ��ġ (����)
	int				_minDamage;				// �ּ� ������
	int				_maxDamage;				// �ִ� ������
	int				_power;					// ����
	int				_trueDamage;			// ���� ������
	float			_atkSpeed;				// ���ݼӵ�
	float			_criticalPercent;		// ũ��Ƽ��
	float			_criticalDamage;		// ũ��Ƽ�� ������
	bool			_isCritical;			// ũ��Ƽ���� ������
	float			_dashDamage;			// �뽬 ���ݷ�
	float			_reloadTime;			// �������� �ɸ��� �ð�

	// - ǥ���� ��ġ (���) 					
	int				_initHp;				// �ʱ� ü��
	float			_defence;				// ���
	float			_evasion;				// ȸ�� 
	float			_toughness;				// ������
	float			_block;					// ����
	
	// - ������ ��ġ (����)
	float			_angle;					// ���� ����   
	float			_realCriticalPercent;	// ũ��Ƽ�� (��ȯ)
	int				_finalDamage;			// ���� ������ �߰���
	float			_finalDamagePercent;	// ���� ������ �߰��� (����)
	float			_reloadSpeed;			// ������ �ӵ� �߰���
	float			_fireAccuracy;			// ���� ��Ȯ��
	float			_realAttackSpeed;		// ���ݼӵ�(������)
	float			_atkSpeedPer;			// ���ݼӵ� �ۼ�Ʈ
	RECT			_dashAttackRect;		// �뽬 ���� ��Ʈ

	// - ������ ��ġ (���)
	float			_realEvasion;			// ȸ�� (��ȯ)
	float			_realDefence;			// ���� (��ȯ)
	int				_maxHp;					// �ִ� ü�� �߰���
	float			_maxHpPercent;			// �ִ� �ַ� �߰��� (����)

	// �Ӽ� //
	bool			_isFire;
	int				_fireCount;
	bool			_isIce;
	bool			_isElectric;
	bool			_isPoison;
	bool			_immuneFire;			// ȭ�� �鿪
	bool			_immuneIce;				// �ñ� �鿪
	bool			_immuneElectric;		// ���� �鿪
	bool			_immunePosion;			// �ߵ� �鿪
	bool			_immuneStun;			// ���� �鿪
	int				_toFire;				// ���� �� ȭ�� Ȯ��
	int				_toIce;					// ���� �� �ñ� Ȯ��
	int				_toElectric;			// ���� �� ���� Ȯ��
	int				_toPosion;				// ���� �� �ߵ� Ȯ��
	int				_toStun;				// ���� �� ���� Ȯ��
	int				_fireDamage;			// ȭ�� ���ݷ� (ȭ�� ���ݷ�)
	int				_iceDamage;				// �ñ� ���ݷ� (�ñ� �ð�)
	int				_elecDamage;			// ���� d���ݷ� (���� �ð�)
	int				_posionDamage;			// �ߵ� ���ݷ� (�ߵ� ���ݷ�)
	int				_stunDamage;			// ���� ���ݷ� (���� �ð�)

	// Ư�� ���� //
	int				_maxPoint;					// ��ü �ɷ�ġ
	int				_remainPoint;				// ���� �ɷ�ġ
	int				_abilityNum[7];				// ���ڵ� �ɷ�ġ
	bool			_specialAbilityOn[7][3];	// ����� �����Ƽ ��
	RECT			_jumpAttackRect;			// ���� ���� (�г� �����)
	int				_damageUpTimer;				// ������ �� Ÿ�̸� (�г� �����)
	bool			_damageUpTimerUse;			// ������ �� Ÿ�̸Ӱ� ���ǰ� �ִ��� (�г� �����)
	bool			_atkSpdUpUse;				// ���ݼӵ� ���� ���Ǿ����� (�ż� �����)
	int				_dashInvincibTimer;			// �뽬 ���� �ð� (�ż� �����)
	bool			_dashInvinCible;			// ���� �������� (�ż� �����)
	int				_deathDefencerTimer;		// ���� ���� Ÿ�̸� (��� �����)
	bool			_deathDefencerActivated;	// ���� ���� Ÿ�̸Ӱ� �۵��ߴ��� (��� �����)
	int				_regenTimer;				// ���� Ÿ�̸� (��� �����)
	bool			_getRangeStatus;			// Range �ɷ�ġ�� ������� (���� �����)
	int				_reloadItemTimer;			// ������ ��� Ÿ�̸� (���� �����)
	int				_reloadItemNumber;			// ������ ������ ���� (���� �����)
	int				_restorePrevHp;				// ������ ���� HPȸ�����ɷ� (���� �����)
	int				_restoreHpTimer;			// Hpȸ�� ���� Ÿ�̸� (���� �����)

	// �ȼ��浹 ���� //					 
	RECT			_collider[8];			// �ȼ��浹��
	POINT			_pixelCenter;			// �ȼ��浹�� �� �߾�
	float			_probeBottom;			// �ȼ��浹����ǥ
	bool			_leftBack;				   
	bool			_rightBack;				   
	bool			_bottomCol;
	
	// �ִϸ��̼� //
	// - ������ ��ġ
	int				_animCount;				// ������ ���� ī��Ʈ(�ӵ�����)
	int				_dustEffectCount;

	// ���� //
	Inventory*		_inven;					// �κ��丮
	Item*			_weapons[2];			// ���ݹ���
	Item*			_subWeapons[2];			// ��������
	vector<Item*>	_vAccessories;			// �Ǽ�������
	int				_selectedWeaponIdx;		// ������ ���� �ε���
	int				_accesoryCount;			// �Ǽ����� �ִ� ����
	
	// ��Ÿ //						 
	// - ǥ���� ��ġ
	int				_satiety;				// ������
	int				_maxSatiety;			// �ִ� ������
	int				_money;					// ��
	int				_level;					// ����
	CLOTHTYPE		_clothType;				// ���� ���� ��
	// - ������ ��ġ
	int				_experience;			// ����ġ
	int				_needExperience;		// �ʿ� ����ġ
	float			_goldDrop;				// �� �����

	// SWAP //
	int				_swapCoolTime;			// ���� ��Ÿ��

	// UI //
	vector<CharToolTip>		_vToolTips;				// ���� ������ ���
	vector<string>			_vToolTipsName;			// ���� ������ �̸� ���
	UIFrame*				_hpFrame;				// HPFrame
	UIFrame*				_dashFrame;				// DashFrame
	UIFrame*				_traitFrame;			// traitFrame
	int						_uiScrollTimer;			// ��ũ�ѿ� ���Ǵ� Ÿ�̸�
	float					_uiMouseLocation;		// ����� ���콺 X��ǥ
	float					_movedX;				// ������ �Ÿ�
	string					_vTraitTooltip[7][3];	// Ư�� ������
	
	// �� ĳ���ͺ� Ư�� //

	// ������ //
	bool			_useGun;
	

	// �ٸ��� //
	image*			_aliceZone;
	float			_aliceZoneRadius;
	bool			_aliceZoneIn;
	bool			_alicePowerDownCheck;

	// ��Ű���� //
	int				_rageCurrent;					// ���� ȭ�� ��
	int				_rageMax;						// ȭ���� �ִ� -> ���� -> ȭ���� 0
	bool			_isRaging;						// ���� �������ִ���
	int				_rageTimer;						// ���� �ð�

	// ���̴�H //
	int				_prevPowerPlus;					// ���� �������� ������ �Ŀ���
	

public:

	virtual HRESULT init();
	virtual void	update();
	void DashInvincibility();
	void AddMaxDash();
	void SubMaxDash();
	void DashAttack();
	void DashImageCheck();
	void SetTextLeftDown();
	void DashUICheck();
	void RangeGetStatusAbility();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	Move();				//�÷��̾� ������
	void DamageJumpAttackRect();
	void ControlDamageUpTimer();
	void DamageUpEnemyKill();
	void SpecialAtkSpeedUp();
	virtual void	pixelCollision();	//�ȼ��浹
	virtual void	dash();				//�뽬
	virtual void	GetDamage();
	void invincibility();				//��Ʈ�� ����
	void UpdateCharPage();
	void SetRealStat();
	void CharPageToolTipOn();

	void ReInitTooltip(int n);
	void SetToolTipFrame(float x, float y, int index);

	void SetDeathDefencerTimerDown();

	void RegenDefenceSkill();

	void GetHitDamage(int damage);

	void RestoreHpTimerChecker();

	void RemoveMagicShield();

	void ControlTraitPage();
	void ReloadItemChecker();
	void AddTraitPoint();
	void ReloadTraitPoint();
	void CheckTraitIconHovered();
	void ReInitTraitUI();

	void CheckUsePistolGunner();

	void MoveTraitUI();
	
	void SwitchWeapon();
	void JumpAttackRectUpdate();
	void AbnormalState(); // �����̻� ����
	void ReloadBullet();
	//ĳ���� �ɷ� ���� �Լ�
	void CheckAliceZone();
	void AdjustAlicePower();
	void SetIkinaBearAngry();
	void CheckMoveSpeedRiderH();
	void CheckCliminal();
	
	void SetHpUI();
	// GETSET //
	PLAYERSTATE		GetState()				{ return _state; }
	bool			GetIsLeft()				{ return _isLeft; }
	bool			GetJump()				{ return _jump; }
	bool			GetIsJump()				{ return _isJump; }
	bool			GetDownJump()			{ return _downJump; }
	bool			GetIsDash()				{ return _isDash; }
	bool			GetIsHit()				{ return _isHit; }
	bool			GetIsStun()				{ return _isStun; }
	float			GetMoveSpeed()			{ return _moveSpeed; }
	float			GetJumpPower()			{ return _jumpPower; }
	int				GetDashCount()			{ return _dashCount; }
	float			GetGravity()			{ return _gravity; }
	float			GetDashSpeed()			{ return _dashSpeed; }
	Effect*			GetDashEffect()			{ return _dashEffect; }
	int				GetJumpCount()			{ return _jumpCount; }
	int				GetDownJumpTimer()		{ return _downJumpTimer; }
	POINT			GetDashPoint()			{ return _dashPoint; }
	int				GetDashTimer()			{ return _dashTimer; }
	float			GetMoveSpeedPer()		{ return _moveSpeedPer; }
	int				GetMinDamage()			{ return _minDamage; }
	int				GetMaxDamage()			{ return _maxDamage; }
	int				GetPower()				{ return _power; }
	int				GetTrueDamage()			{ return _trueDamage; }
	float			GetAtkSpeed()			{ return _atkSpeed; }
	float			GetRealCriPer()			{ return _realCriticalPercent; }
	float			GetCriDamage()			{ return _criticalDamage; }
	float			GetDashDamage()			{ return _dashDamage; }
	float			GetReloadTime()			{ return _reloadTime; }
	int				GetBulletCount()		{ return _bulletCount; }
	int				GetMaxBullet()			{ return _maxBullet; }
	int				GetInitHp()				{ return _initHp; }
	float			GetRealDefence()		{ return _realDefence; }
	float			GetRealEvasion()		{ return _realEvasion; }
	float			GetToughness()			{ return _toughness; }
	float			GetBlock()				{ return _block; }
	float			GetAngle()				{ return _angle; }
	float			GetCriPer()				{ return _criticalPercent; }
	bool			GetIsCritical()			{ return _isCritical;}
	int				GetFinalDamage()		{ return _finalDamage; }
	float			GetFinalDamagePer()		{ return _finalDamagePercent; }
	float			GetReloadSpeed()		{ return _reloadSpeed; }
	float			GetFireAccuracy()		{ return _fireAccuracy; }
	float			GetDefence()			{ return _defence; }
	float			GetEvasion()			{ return _evasion; }
	int				GetMaxHp()				{ return _maxHp; }
	float			GetMaxHpPer()			{ return _maxHpPercent; }
	bool			GetImmuneFire()			{ return _immuneFire; }
	bool			GetImmuneIce()			{ return _immuneIce; }
	bool			GetImmuneElec()			{ return _immuneElectric; }
	bool			GetImmunePosion()		{ return _immunePosion; }
	bool			GetImmuneStun()			{ return _immuneStun; }
	int				GetToFire()				{ return _toFire; }
	int				GetToIce()				{ return _toIce; }
	int				GetToElec()				{ return _toElectric; }
	int				GetToPosion()			{ return _toPosion; }
	int				GetToStun()				{ return _toStun; }
	int				GetFireDamage()			{ return _fireDamage; }
	int				GetIceDamage()			{ return _iceDamage; }
	int				GetElecDamage()			{ return _elecDamage; }
	int				GetPosionDamage()		{ return _posionDamage; }
	int				GetStunDamage()			{ return _stunDamage; }
	int				GetAnimCount()			{ return _animCount; }
	Inventory*		GetInventory()			{ return _inven; }
	Item*			GetWeapon(int num)		{ return _weapons[num]; }
	Item*			GetSubWeapon(int num)	{ return _subWeapons[num]; }
	vector<Item*>&	GetVAccessories()		{ return _vAccessories; }
	Item*			GetAccessory(int num)	{ return _vAccessories[num]; }
	int				GetSelectedWeaponIdx()	{ return _selectedWeaponIdx; }
	int				GetSatiety()			{ return _satiety; }
	int				GetMoney()				{ return _money; }
	int				GetLevel()				{ return _level; }
	int				GetExperience()			{ return _experience; }
	int				GetNeedExperience()		{ return _needExperience; }
	float			GetRealAttackSpeed()	{ return _realAttackSpeed; }
	float			GetAtkSpeedPer()		{ return _atkSpeedPer; }
	float			GetGoldDrop()			{ return _goldDrop; }
	int				GetAccesoryCount()	    { return _accesoryCount; }
	int				GetMaxDashCount()		{ return _maxDashCount; }
	int				GetMaxSatiety()			{ return _maxSatiety; }
	int				GetRageCurrent()		{ return _rageCurrent; }
	int				GetRageMax()			{ return _rageMax; }
	bool			GetIsRaging()			{ return _isRaging; }
	int				GetRageTimer()			{ return _rageTimer; }
	float			GetPrevPowerPlus()		{ return _prevPowerPlus; }
	bool			GetIsReload()			{ return _isReload; }
	bool			GetDashInvincible()		{ return _dashInvinCible; }
	bool			GetDashInvincibleTimer(){ return _dashInvincibTimer; }
	CLOTHTYPE		GetClothType()			{ return _clothType; }
	int				GetRestorePrevHp()		{ return _restorePrevHp; }
	bool			GetSpecialAbilityOn(int indexBig, int indexSmall) { return _specialAbilityOn[indexBig][indexSmall]; }
	
	void			SetIsReload(bool isReload)						{ _isReload = isReload; }
	void			SetHitCount(int hitCount)						{ _hitCount = hitCount; }
	void			SetState(PLAYERSTATE state)						{ _state = state; }
	void			SetIsLeft(bool isLeft) 							{ _isLeft = isLeft; }
	void			SetJump(bool jump) 								{ _jump = jump; }
	void			SetIsJump(bool isJump)							{ _isJump = isJump; }
	void			SetDownJump(bool downJump) 						{ _downJump = downJump; }
	void			SetIsDash(bool isDash) 							{ _isDash = isDash; }
	void			SetIsHit(bool isHit)							{ _isHit = isHit; }
	void			SetMoveSpeed(float moveSpeed) 					{ _moveSpeed = moveSpeed; }
	void			SetJumpPower(float jumpPower) 					{ _jumpPower = jumpPower; }
	void			SetDashCount(int dashCount) 					{ _dashCount = dashCount; }
	void			SetGravity(float gravity) 						{ _gravity = gravity; }
	void			SetDashSpeed(float dashSpeed) 					{ _dashSpeed = dashSpeed; }
	void			SetDashEffect(Effect* dashEffect) 				{ _dashEffect = dashEffect; }
	void			SetJumpCount(int jumpCount) 					{ _jumpCount = jumpCount; }
	void			SetDownJumpTimer(int downJumpTimer)				{ _downJumpTimer = downJumpTimer; }
	void			SetDashPoint(POINT dashPoint) 					{ _dashPoint = dashPoint; }
	void			SetDashTimer(int dashTimer) 					{ _dashTimer = dashTimer; }
	void			SetMoveSpeedPer(float moveSpeedPer)				{ _moveSpeedPer = moveSpeedPer; }
	void			SetMinDamage(int minDamage) 					{ _minDamage = minDamage; }
	void			SetMaxDamage(int maxDamage) 					{ _maxDamage = maxDamage; }
	void			SetPower(int power) 							{ _power = power; }
	void			SetTrueDamage(int trueDamage)					{ _trueDamage = trueDamage; }
	void			SetAtkSpeed(float atkSpeed) 					{ _atkSpeed = atkSpeed; }
	void			SetAtkSpeedPer(float atkSpeedPer) 				{ _atkSpeedPer = atkSpeedPer; }
	void			SetRealCriPer(float realCriPer) 				{ _realCriticalPercent = realCriPer; }
	void			SetCriDamage(float criDamage) 					{ _criticalDamage = criDamage; }
	void			SetDashDamage(float dashDamage) 				{ _dashDamage = dashDamage; }
	void			SetReloadTime(float reloadTime) 				{ _reloadTime = reloadTime; }
	void			SetInitHp(int initHp)							{ _initHp = initHp; }
	void			SetRealDefence(float realDefence)				{ _realDefence = realDefence; }
	void			SetRealEvasion(float realEvasion)				{ _realEvasion = realEvasion; }
	void			SetToughness(float toughness) 					{ _toughness = toughness; }
	void			SetBlock(float block) 							{ _block = block; }
	void			SetAngle(float angle) 							{ _angle = angle; }
	void			SetCriPer(float criticalPercent)				{ _criticalPercent = criticalPercent; }
	void			SetIsCritical(bool isCritical)					{ _isCritical = isCritical; }
	void			SetFinalDamage(int finalDamage)					{ _finalDamage = finalDamage; }
	void			SetFinalDamagePer(float finalDamagePercent)		{ _finalDamagePercent = finalDamagePercent; }
	void			SetReloadSpeed(float reloadSpeed) 				{ _reloadSpeed = reloadSpeed; }
	void			SetFireAccuracy(float fireAccuracy)				{ _fireAccuracy = fireAccuracy; }
	void			SetDefence(float defence) 						{ _defence = defence; }
	void			SetEvasion(float evasion) 						{ _evasion = evasion; }
	void			SetMaxHp(int maxHp) 							{ _maxHp = maxHp; }
	void			SetMaxHpPer(float maxHpPercent) 				{ _maxHpPercent = maxHpPercent; }
	void			SetImmuneFire(bool immuneFire)					{ _immuneFire = immuneFire; }
	void			SetImmuneIce(bool immuneIce) 					{ _immuneIce = immuneIce; }
	void			SetImmuneElec(bool immuneElec)					{ _immuneElectric = immuneElec; }
	void			SetImmunePosion(bool immunePosion)  			{ _immunePosion = immunePosion; }
	void			SetImmuneStun(bool immuneStun)					{ _immuneStun = immuneStun; }
	void			SetToFire(int toFire) 							{ _toFire = toFire; }
	void			SetToIce(int toIce) 							{ _toIce = toIce; }
	void			SetToElec(int toElec)							{ _toElectric = toElec; }
	void			SetToPosion(int toPosion)						{ _toPosion = toPosion; }
	void			SetToStun(int toStun)							{ _toStun = toStun; }
	void			SetFireDamage(int fireDamage)					{ _fireDamage = fireDamage; }
	void			SetIceDamage(int iceDamage) 					{ _iceDamage = iceDamage; }
	void			SetElecDamage(int elecDamage) 					{ _elecDamage = elecDamage; }
	void			SetPosionDamage(int posionDamage)  				{ _posionDamage = posionDamage; }
	void			SetStunDamage(int stunDamage)					{ _stunDamage = stunDamage; }
	void			SetAnimCount(int animCount) 					{ _animCount = animCount; }
	void			SetInventory(Inventory* inven) 					{ _inven = inven; }
	Item*			SetWeapon(int num, Item* item)					{ Item* saveItem = _weapons[num]; _weapons[num] = item; return saveItem; }
	Item*			SetSubWeapon(int num, Item* item)				{ Item* saveItem = _subWeapons[num]; _subWeapons[num] = item; return saveItem; }
	Item*			SetVAccessory(int num, Item* item)				{ Item* saveItem = _vAccessories[num]; _vAccessories[num] = item; return saveItem; }
	void			SetSelectedWeaponIdx(int selectWeaponidx)		{ _selectedWeaponIdx = selectWeaponidx; }
	void			SetSatiety(int satiety) 						{ _satiety = satiety; }
	void			SetMoney(int money) 							{ _money = money; }
	void			SetLevel(int level) 							{ _level = level; }
	void			SetExperience(int experience) 					{ _experience = experience; }
	void			SetNeedExperience(int needExperience) 			{ _needExperience = needExperience; }
	void			SetGoldDrop(float goldDrop) 					{ _goldDrop = goldDrop; }
	void			SetAccesoryCount(int accesoryCount)				{ _accesoryCount = accesoryCount; }
	void			SetMaxDashCount(int dashCount)					{ _maxDashCount = dashCount; }
	void			SetMaxSatiety(int satiety)						{ _maxSatiety = satiety; }
	void			SetIsStun(bool isStun)							{ _isStun = isStun; }
	void			SetClothType(CLOTHTYPE type)					{ _clothType = type; }
	void			SetRageCurrent(int rage)						{ _rageCurrent = rage; }
	void			SetPrevPowerPlus(float num)						{ _prevPowerPlus = num; }
	void			SetRestorePrevHp(int num)						{ _restorePrevHp = num; }
	void			SetMaxBullet(int maxBullet)						{ _maxBullet = maxBullet; }
	void			SetBulletCount(int bulletCount)					{ _bulletCount = bulletCount; }
};

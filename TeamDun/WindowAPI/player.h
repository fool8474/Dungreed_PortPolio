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
	bool			_stun;					//���ϻ�������
	// �ǰݰ���
	bool			_isHit;					// �÷��̾ �������� �Ծ�����
	int				_hitCount;				// ��Ʈ�� �����ð� ���¿�
	int				_hitAlpha;				//	��Ʈ�� ���� ���İ�
	// �̵� ���� //					   
	// - ǥ���� ��ġ
	float			_moveSpeed;				// �̵��ӵ�
	float			_jumpPower;				// ������
	int				_dashCount;				// �뽬 Ƚ��

	// - ������ ��ġ
	float			_gravity;				// �߷�
	float			_dashSpeed;				// �뽬 �ӵ�
	Effect*			_dashEffect;			// �뽬 ����Ʈ
	int				_jumpCount;				// ���� Ƚ��
	int				_downJumpTimer;			// �Ʒ� ����
	POINT			_dashPoint;				// �뽬 ��ġ
	int				_dashTimer;				// �뽬 �ð�

	// ���� ���� //			
	// - ǥ���� ��ġ (����)
	int				_minDamage;				// �ּ� ������
	int				_maxDamage;				// �ִ� ������
	int				_power;					// ����
	int				_trueDamage;			// ���� ������
	float			_atkSpeed;				// ���ݼӵ�
	float			_criticalPercent;		// ũ��Ƽ��
	float			_criticalDamage;		// ũ��Ƽ�� ������
	float			_dashDamage;			// �뽬 ���ݷ�
	float			_reloadTime;			// �������� �ɸ��� �ð�

	// - ǥ���� ��ġ (���) 					
	int				_initHp;				// �ʱ� ü��
	int				_hp;					// ü��
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
	
	// - ������ ��ġ (���)
	float			_realEvasion;			// ȸ�� (��ȯ)
	float			_realDefence;			// ���� (��ȯ)
	int				_maxHp;					// �ִ� ü�� �߰���
	float			_maxHpPercent;			// �ִ� �ַ� �߰��� (����)

	// �Ӽ� //
	bool			_immuneFire;			// ȭ�� �鿪
	bool			_immuneIce;				// �ñ� �鿪
	bool			_immuneElectric;		// ���� �鿪
	bool			_immunePosion;			// �ߵ� �鿪
	bool			_immuneStun;
	int				_toFire;				// ���� �� ȭ�� Ȯ��
	int				_toIce;					// ���� �� �ñ� Ȯ��
	int				_toElectric;			// ���� �� ���� Ȯ��
	int				_toPosion;				// ���� �� �ߵ� Ȯ��
	int				_toStun;				// ���� �� ���� Ȯ��
	int				_fireDamage;			// ȭ�� ���ݷ� (ȭ�� ���ݷ�)
	int				_iceDamage;				// �ñ� ���ݷ� (�ñ� �ð�)
	int				_elecDamage;			// ���� ���ݷ� (���� �ð�)
	int				_posionDamage;			// �ߵ� ���ݷ� (�ߵ� ���ݷ�)
	int				_stunDamage;			// ���� ���ݷ� (���� �ð�)

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
	int				_money;					// ��
	int				_level;					// ����
	
											// - ������ ��ġ
	int				_experience;			// ����ġ
	int				_needExperience;		// �ʿ� ����ġ
	float			_goldDrop;				// �� �����

	// UI //
	vector<CharToolTip>		_vToolTips;		// ���� ������ ���
	vector<string>			_vToolTipsName; // ���� ������ �̸� ���

	// �� ĳ���ͺ� Ư�� //

	// �ٸ��� //
	image*			_aliceZone;
	float			_aliceZoneRadius;
	bool			_aliceZoneIn;

public:

	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	Move();				//�÷��̾� ������
	virtual void	pixelCollision();	//�ȼ��浹
	virtual void	dash();				//�뽬
	virtual void	GetDamage();
	void invincibility();				//��Ʈ�� ����
	void UpdateCharPage();
	void SetRealStat();
	void CharPageToolTipOn();

	void ReInitTooltip(int n);
	void SetToolTipFrame(float x, float y, int index);

	void SwitchWeapon();
	void CheckAliceZone();
	

	// GETSET //
	PLAYERSTATE		GetState()				{ return _state; }
	bool			GetIsLeft()				{ return _isLeft; }
	bool			GetJump()				{ return _jump; }
	bool			GetIsJump()				{ return _isJump; }
	bool			GetDownJump()			{ return _downJump; }
	bool			GetIsDash()				{ return _isDash; }
	bool			GetIsHit()				{ return _isHit; }
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
	int				GetMinDamage()			{ return _minDamage; }
	int				GetMaxDamage()			{ return _maxDamage; }
	int				GetPower()				{ return _power; }
	int				GetTrueDamage()			{ return _trueDamage; }
	float			GetAtkSpeed()			{ return _atkSpeed; }
	float			GetRealCriPer()			{ return _realCriticalPercent; }
	float			GetCriDamage()			{ return _criticalDamage; }
	float			GetDashDamage()			{ return _dashDamage; }
	float			GetReloadTime()			{ return _reloadTime; }
	int				GetInitHp()				{ return _initHp; }
	int				GetHp()					{ return _hp; }
	float			GetRealDefence()		{ return _realDefence; }
	float			GetRealEvasion()		{ return _realEvasion; }
	float			GetToughness()			{ return _toughness; }
	float			GetBlock()				{ return _block; }
	float			GetAngle()				{ return _angle; }
	float			GetCriPer()				{ return _criticalPercent; }
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
	float			GetGoldDrop()			{ return _goldDrop; }
	int				GetAccesoryCount()	    { return _accesoryCount; }
	
	void			SetHitCount(int hitCount)					  { _hitCount = hitCount; }
	void			SetState(PLAYERSTATE state)					  { _state = state; }
	void			SetIsLeft(bool isLeft) 						  { _isLeft = isLeft; }
	void			SetJump(bool jump) 							  { _jump = jump; }
	void			SetIsJump(bool isJump)						  { _isJump = isJump; }
	void			SetDownJump(bool downJump) 					  { _downJump = downJump; }
	void			SetIsDash(bool isDash) 						  { _isDash = isDash; }
	void			SetIsHit(bool isHit)						  { _isHit = isHit; }
	void			SetMoveSpeed(float moveSpeed) 				  { _moveSpeed = moveSpeed; }
	void			SetJumpPower(float jumpPower) 				  { _jumpPower = jumpPower; }
	void			SetDashCount(int dashCount) 				  { _dashCount = dashCount; }
	void			SetGravity(float gravity) 					  { _gravity = gravity; }
	void			SetDashSpeed(float dashSpeed) 				  { _dashSpeed = dashSpeed; }
	void			SetDashEffect(Effect* dashEffect) 			  { _dashEffect = dashEffect; }
	void			SetJumpCount(int jumpCount) 				  { _jumpCount = jumpCount; }
	void			SetDownJumpTimer(int downJumpTimer)			  { _downJumpTimer = downJumpTimer; }
	void			SetDashPoint(POINT dashPoint) 				  { _dashPoint = dashPoint; }
	void			SetDashTimer(int dashTimer) 				  { _dashTimer = dashTimer; }
	void			SetMinDamage(int minDamage) 				  { _minDamage = minDamage; }
	void			SetMaxDamage(int maxDamage) 				  { _maxDamage = maxDamage; }
	void			SetPower(int power) 						  { _power = power; }
	void			SetTrueDamage(int trueDamage)				  { _trueDamage = trueDamage; }
	void			SetAtkSpeed(float atkSpeed) 				  { _atkSpeed = atkSpeed; }
	void			SetRealCriPer(float realCriPer) 			  { _realCriticalPercent = realCriPer; }
	void			SetCriDamage(float criDamage) 				  { _criticalDamage = criDamage; }
	void			SetDashDamage(float dashDamage) 			  { _dashDamage = dashDamage; }
	void			SetReloadTime(float reloadTime) 			  { _reloadTime = reloadTime; }
	void			SetInitHp(int initHp)						  { _initHp = initHp; }
	void			SetHp(int hp) 								  { _hp = hp; }
	void			SetRealDefence(float realDefence)			  { _realDefence = realDefence; }
	void			SetRealEvasion(float realEvasion)			  { _realEvasion = realEvasion; }
	void			SetToughness(float toughness) 				  { _toughness = toughness; }
	void			SetBlock(float block) 						  { _block = block; }
	void			SetAngle(float angle) 						  { _angle = angle; }
	void			SetCriPer(float criticalPercent)			  { _criticalPercent = criticalPercent; }
	void			SetFinalDamage(int finalDamage) 			  { _finalDamage = finalDamage; }
	void			SetFinalDamagePer(float finalDamagePercent)   { _finalDamagePercent = finalDamagePercent; }
	void			SetReloadSpeed(float reloadSpeed) 			  { _reloadSpeed = reloadSpeed; }
	void			SetFireAccuracy(float fireAccuracy)			  { _fireAccuracy = fireAccuracy; }
	void			SetDefence(float defence) 					  { _defence = defence; }
	void			SetEvasion(float evasion) 					  { _evasion = evasion; }
	void			SetMaxHp(int maxHp) 						  { _maxHp = maxHp; }
	void			SetMaxHpPer(float maxHpPercent) 			  { _maxHpPercent = maxHpPercent; }
	void			SetImmuneFire(bool immuneFire)				  { _immuneFire = immuneFire; }
	void			SetImmuneIce(bool immuneIce) 				  { _immuneIce = immuneIce; }
	void			SetImmuneElec(bool immuneElec)				  { _immuneElectric = immuneElec; }
	void			SetImmunePosion(bool immunePosion)  		  { _immunePosion = immunePosion; }
	void			SetImmuneStun(bool immuneStun)				  { _immuneStun = immuneStun; }
	void			SetToFire(int toFire) 						  { _toFire = toFire; }
	void			SetToIce(int toIce) 						  { _toIce = toIce; }
	void			SetToElec(int toElec)						  { _toElectric = toElec; }
	void			SetToPosion(int toPosion)					  { _toPosion = toPosion; }
	void			SetToStun(int toStun)						  { _toStun = toStun; }
	void			SetFireDamage(int fireDamage)				  { _fireDamage = fireDamage; }
	void			SetIceDamage(int iceDamage) 				  { _iceDamage = iceDamage; }
	void			SetElecDamage(int elecDamage) 				  { _elecDamage = elecDamage; }
	void			SetPosionDamage(int posionDamage)  			  { _posionDamage = _posionDamage; }
	void			SetStunDamage(int stunDamage)				  { _stunDamage = stunDamage; }
	void			SetAnimCount(int animCount) 				  { _animCount = animCount; }
	void			SetInventory(Inventory* inven) 				  { _inven = inven; }
	void			SetWeapon(int num, Item* item) 				  { _weapons[num] = item; }
	void			SetSubWeapon(int num, Item* item)			  { _subWeapons[num] = item; }
	void			SetVAccessory(int num, Item* item)  		  { _vAccessories[num] = item; }
	void			SetSelectedWeaponIdx(int selectWeaponidx)	  { _selectedWeaponIdx = selectWeaponidx; }
	void			SetSatiety(int satiety) 					  { _satiety = satiety; }
	void			SetMoney(int money) 						  { _money = money; }
	void			SetLevel(int level) 						  { _level = level; }
	void			SetExperience(int experience) 				  { _experience = experience; }
	void			SetNeedExperience(int needExperience) 		  { _needExperience = needExperience; }
	void			SetGoldDrop(float goldDrop) 				  { _goldDrop = goldDrop; }
	void			SetAccesoryCount(int accesoryCount)           { _accesoryCount = accesoryCount; }
};

#pragma once
#include "Skill.h"
#include "Bullet.h"

enum ITEMCLASS
{
	IC_NORMAL, IC_ADVANCED, IC_RARE, IC_LEGENDARY
};

enum ITEMTYPE
{
	IT_WEAPON_ONEHAND, IT_WEAPON_TWOHAND, IT_SUBWEAPON, IT_ACCESORRY, IT_NOTHING
};

enum WEAPONTYPE
{
	WT_NEAR, WT_RANGE, WT_CHARGE, WT_SPEAR, WT_KATANA, WT_PISTOL, WT_NOWEAPON
};

enum OPTIONTYPE
{
	POWER,				 // ����
	ATKSPEED,			 // ���ݼӵ�
	DASHATK,			 // �뽬 ���ݷ�
	DEFENCE,			 // ����
	BLOCK,				 // ����
	CRITICALPERCENT,	 // ũ��Ƽ�� Ȯ��
	CRITICALDAMAGE,		 // ũ��Ƽ�� ������
	MINDAMAGE,			 // �ּ� ������
	MAXDAMAGE,			 // �ִ� ������
	FINALDAMAGEPERCENT,	 // ���� ������ (%)
	FINALDAMAGE,		 // ���� ������
	TRUEDAMAGE,			 // ���� ������
	TOUGHNESS,			 // ������
	MAXHP,				 // �ִ� HP
	MAXHPPERCENT,		 // �ִ� HP (%)
	EVADE,				 // ȸ��
	MOVESPEED,			 // �̵� �ӵ�
	JUMPPOWER,			 // ������
	GOLDDROP,			 // ��� ���
	RELOADSPEED,		 // ������ �ӵ�
	DASHCOUNT,			 // �뽬 Ƚ��
	ACCURACY,			 // ���� ��Ȯ��
	IMMUNEFIRE,			 // ȭ�� �鿪
	IMMUNEICE,			 // �ñ� �鿪
	IMMUNEELEC,			 // ���� �鿪
	IMMUNEPOSION,		 // �ߵ� �鿪
	TOFIRE,				 // ȭ������ȭ
	TOICE,				 // �ñ����ȭ
	TOELEC,				 // ��������ȭ
	TOPOSION,			 // �ߵ�����ȭ
	FIREDAMAGE,			 // ȭ�� �Ӽ� ������
	ICEDAMAGE,			 // �ñ� �Ӽ� ������
	ELECDAMAGE,			 // ���� �Ӽ� ������
	POSIONDAMAGE,		 // �ߵ� �Ӽ� ������
	ETC					 // �� �� (��ġ�� �ƴ� ���̽�, DESCRIPTION���� ����, ȿ���� ���� ���� �ʿ�)
};

class SubOption
{
public :
	OPTIONTYPE	_optionId;
	float		_optionPower;
	string		_description;
};

class Item
{
protected:
	
	// ���� //
	vector<image*>		_vImages;			// �̹��� ���
	vector<string>		_vImageNames;		// �̹��� �̸� ���
	int					_currentImage;		// ���� �̹���
	image*				_invenImage;		// �κ��丮�� �̹���
	float				_renderPosX;		// ��ġ X
	float				_renderPosY;		// ��ġ Y
	float				_angleCheckPosX;	// ����üũ�� ���� X
	float				_angleCheckPosY;	// ����üũ�� ���� Y
	float				_angle;				// ����
	float				_renderAngle;		// ������ ������ �ޱ�
	int					_xFrame;			// �̹��� XFrame
	int					_yFrame;			// �̹��� yFrame
	bool				_isAttacking;		// ���� ������

	// ���� //
	ITEMCLASS			_itemClass;			// ������ ���
	ITEMTYPE			_itemType;			// �������� ����
	WEAPONTYPE			_weaponType;		// ������ ����
	Skill*				_skill;				// ��ų
	int					_id;				// ������ ���̵�
	string				_name;				// �̸�
	string				_description;		// ����
	float				_minAtk;			// �ּ� ���ݷ�
	float				_maxAtk;			// �ִ� ���ݷ�
	float				_atkSpeed;			// ���� �ӵ�
	int					_defence;			// ����
	int					_buyPrice;			// ���� ���� (�Ǹ� ���� : ���� ���� * 0.3)

	vector<SubOption*>	_vSubOption;		// ���� �ɼ� ���
	bool				_useAtkSpeed;		// ���� �ӵ��� ����Ѵ�
	
	// ������ // 
	float				_chargePercent;		// ������ ��������
	
	// ���Ÿ� //
	int					_initNumOfBullet;	// �ʱ� �Ѿ� ����
	int					_curNumOfBullet;	// ���� �Ѿ� ����
	float				_reloadTime;		// ������ �ð�
	Bullet*				_bullet;			// ��� �Ѿ�
	float				_accuracy;			// ���� ��Ȯ��
	bool				_isBulletInfinite;	// źâ�� ��������
	
	bool				_isRenderFirst;		// �÷��̾�� ���� �����Ǵ���

public:

	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, 
		string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, 
		int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, 
		float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage);

	void AddSubOption(SubOption* option);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
	virtual void Activate();
	void EquipUnEquipItem(bool isEquip);
	void AdaptSubOption(SubOption* subOption, bool isEquip);
	

	void SetBaseRenderPos();

	// GETSET // 

	int					GetBuyPrice()			{ return _buyPrice; }
	int					GetSellPrice()			{ return _buyPrice * 0.3f; }
	vector<image*>&		GetImages()				{ return _vImages; }
	image*				GetImage(int index)		{ return _vImages[index]; }
	vector<string>&		GetImageNames()			{ return _vImageNames; }
	string				GetImageName(int index) { return _vImageNames[index]; }
	image*				GetInvenImage()			{ return _invenImage; }
	ITEMCLASS			GetItemClass()			{ return _itemClass; }
	ITEMTYPE			GetitemType()			{ return _itemType; }
	WEAPONTYPE			GetWeaponType()			{ return _weaponType; }
	Skill*				GetSkill()				{ return _skill; }
	int					GetId()					{ return _id; }
	string				GetName()				{ return _name; }
	string				GetDescription()		{ return _description; }
	float				GetMinAtk()				{ return _minAtk; }
	float				GetMaxAtk()				{ return _maxAtk; }
	float				GetAtkSpeed()			{ return _atkSpeed; }
	int					GetDefence()			{ return _defence; }
	vector<SubOption*>& GetSubOptions()			{ return _vSubOption; }
	bool				GetUseAtkSpeed()		{ return _useAtkSpeed; }
	float				GetChargePercent()		{ return _chargePercent; }
	int					GetInitNumOfBullet()	{ return _initNumOfBullet; }
	int					GetCurNumOfBullet()		{ return _curNumOfBullet; }
	float				GetReloadTime()			{ return _reloadTime; }
	Bullet*				GetBullet()				{ return _bullet; }
	float				GetAccuracy()			{ return _accuracy; }
	bool				GetIsBulletInfinite()	{ return _isBulletInfinite; }
	bool				GetIsRenderFirst()		{ return _isRenderFirst; }
	float				GetAngleCheckPosX()		{ return _angleCheckPosX; }
	float				GetAngleCheckPosY()		{ return _angleCheckPosY; }
	void				SetIsRenderFirst(bool first)	{ _isRenderFirst = first; }
};


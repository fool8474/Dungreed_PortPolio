#pragma once
#include "Skill.h"

enum ITEMCLASS
{
	IC_NORMAL, IC_ADVANCED, IC_RARE, IC_LEGENDARY
};

enum ITEMTYPE
{
	IT_WEAPON_ONEHAND, IT_WEAPON_TWOHAND, IT_SUBWEAPON, IT_ACCESORRY
};

enum WEAPONTYPE
{
	WT_NEAR, WT_RANGE, WT_CHARGE, WT_SPEAR, WT_KATANA, WT_NOWEAPON
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
private:
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

	vector<SubOption>	_subOption;			// ���� �ɼ� ���
	bool				_useAtkSpeed;		// ���� �ӵ��� ����Ѵ�
	
	// ������ // 
	float				_chargePercent;		// ������ ��������
	
	// ���Ÿ� //
	int					_initNumOfBullet;	// �ʱ� �Ѿ� ����
	int					_curNumOfBullet;	// ���� �Ѿ� ����
	int					_reloadTime;		// ������ �ð�
	Bullet*				_bullet;			// ��� �Ѿ�
	float				_accuracy;			// ���� ��Ȯ��
	int					_buyPrice;			// ���� ���� (�Ǹ� ���� : ���� ���� * 0.5)
	bool				_isBulletInfinite;	// źâ�� ��������
	
public:

	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();
	void EquipUnEquip(SubOption subOption, bool isEquip);
};


#pragma once
#include "Object.h"
#include "inventory.h"
#include "Item.h"
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
	float			_trueDamage;			// ���� ������
	float			_atkSpeed;				// ���ݼӵ�
	float			_realCriticalPercent;	// ũ��Ƽ��
	float			_criticalDamage;		// ũ��Ƽ�� ������
	float			_dashDamage;			// �뽬 ���ݷ�
	float			_reloadTime;			// �������� �ɸ��� �ð�

	// - ǥ���� ��ġ (���) 					
	int				_initHp;				// �ʱ� ü��
	int				_hp;					// ü��
	float			_realDefence;			// ����
	float			_realEvasion;			// ȸ��
	float			_toughness;				// ������
	float			_block;					// ����
	
	// - ������ ��ġ (����)
	float			_angle;					// ���� ����   
	float			_criticalPercent;		// ũ��Ƽ�� (��ȯ)
	int				_finalDamage;			// ���� ������ �߰���
	float			_finalDamagePercent;	// ���� ������ �߰��� (����)
	float			_reloadSpeed;			// ������ �ӵ� �߰���
	float			_fireAccuracy;			// ���� ��Ȯ��

	// - ������ ��ġ (���)
	float			_defence;				// ����� (��ȯ)
	float			_evasion;				// ȸ���� (��ȯ)
	int				_maxHp;					// �ִ� ü�� �߰���
	float			_maxHpPercent;			// �ִ� �ַ� �߰��� (����)

	// �Ӽ� //
	bool			_immuneFire;			// ȭ�� �鿪
	bool			_immuneIce;				// �ñ� �鿪
	bool			_immuneElectric;		// ���� �鿪
	bool			_immunePosion;			// �ߵ� �鿪
	int				_toFire;				// ���� �� ȭ�� Ȯ��
	int				_toIce;					// ���� �� �ñ� Ȯ��
	int				_toElectric;			// ���� �� ���� Ȯ��
	int				_toPosion;				// ���� �� �ߵ� Ȯ��
	int				_fireDamage;			// ȭ�� ���ݷ�
	int				_iceDamage;				// �ñ� ���ݷ�
	int				_elecDamage;			// ���� ���ݷ�
	int				_posionDamage;			// �ߵ� ���ݷ�

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

	// ���� //
	Inventory*		_inven;					// �κ��丮
	Item*			_weapons[2];			// ���ݹ���
	Item*			_subWaepons[2];			// ��������
	vector<Item*>	_vAccessories;			// �Ǽ�������
	bool			_isUseFirstWeapon;		// ù��° ���⸦ �����ϰ� �ִ���

	// ��Ÿ //						 
	// - ǥ���� ��ġ
	int				_satiety;				// ������
	int				_money;					// ��
	int				_level;					// ����
	
											// - ������ ��ġ
	int				_experience;			// ����ġ
	int				_needExperience;		// �ʿ� ����ġ
	float			_goldDrop;				// �� �����

	
public:

	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	Move();				//�÷��̾� ������
	virtual void	pixelCollision();	//�ȼ��浹
	virtual void	dash();

	int getHp() { return _hp; }
	float getPower() { return _power; }
	float getAtkSpeed() { return _atkSpeed; }
	float getEvasion() { return _realEvasion; }
	float getBlock() { return _block; }
	float getToughness() { return _toughness; }
	float getTrueDamage() { return _trueDamage; }
	float getCritical() { return _realCriticalPercent; }
	float getCriticalDamage() { return _criticalDamage; }
	float getDashDamage() { return _dashDamage; }
	
};
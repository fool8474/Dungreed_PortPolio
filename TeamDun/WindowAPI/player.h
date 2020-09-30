#pragma once
#include "Object.h"

//ĳ���� ����
enum PLAYERSTATE
{
	PS_IDLE,PS_JUMP,PS_MOVE,PS_DIE,
};


class Player : public Object
{
private:
	int			_count;				//������ ���� ī��Ʈ(�ӵ�����)
	bool		_isLeft;			//�������� (�ƴҽ� ������)
	bool		_jump;				//������ �ߴ���
	PLAYERSTATE	_state;				//ĳ���� ����
	RECT		_player;			//�÷��̾�
	float		_hp;				//ü��
	float		_numberOfDashes;	//�뽬 Ƚ��
	float		_speed;				//�̵��ӵ�
	float		_gravity;
	float		_jumpPower;
	float		_angle;
	int			_satiety;			//������
	float		_damage;			//���� ���ݷ�
	float		_power;				//����
	float		_defense;			//����
	float		_atkSpeed;			//���ݼӵ�
	float		_evasion;			//ȸ��
	float		_block;				//����
	float		_toughness;			//������
	float		_trueDamage;		//���� ������
	float		_critical;			//ũ��Ƽ��
	float		_criticalDamage;	//ũ��Ƽ�� ������
	float		_dashDamage;		//�뽬 ���ݷ�

	RECT		_collider[8];		//�ȼ��浹��
	float		_probeBottom;		//�ȼ��浹����ǥ
	float		_probeTop;		//�ȼ��浹����ǥ

public:

	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	Move();

	float getHp() { return _hp; }
	float getDamage() { return _damage; }
	float getPower() { return _power; }
	float getAtkSpeed() { return _atkSpeed; }
	float getEvasion() { return _evasion; }
	float getBlock() { return _block; }
	float getToughness() { return _toughness; }
	float getTrueDamage() { return _trueDamage; }
	float getCritical() { return _critical; }
	float getCriticalDamage() { return _criticalDamage; }
	float getDashDamage() { return _dashDamage; }
	
};
#pragma once
#include "Object.h"
#include "Effect.h"

enum ENEMYSTATE {
	ES_IDLE, ES_MOVE, ES_ATTACK
};

class Enemy : public Object
{
protected :
	int				_Damage;				// ���� ������
	int				_minDamage;				// �ּ� ������
	int				_maxDamage;				// �ִ� ������
	int				_power;					// ����
	float			_atkSpeed;				// ���ݼӵ�
	int				_initHp;				// �ʱ� ü��
	float			_realDefence;			// ����
	image*			_hpBar1;
	image*			_hpBar2;
	int				_hpBarAlpha;

	ENEMYSTATE		_state;				// ���� ����
	int				_attackCoolTime;	// ���� ��Ÿ��
	int				_useBulletId;		// ����ϴ� �Ҹ� ID
	float			_moveSpeed;			// �̵��ӵ�
	float			_gravity;			// ���� �߷°�
	int				_count;				// �ִϸ��̼� �� ī��Ʈ
	int				_index;				// �ִϸ��̼� �� �ε���
	bool			_isLeft;			// �ִϸ��̼��� �����̳�?
	bool			_isSpawned;			// ���� �����Ǿ�����
	Effect*			_spawnEffect;		// ���� ����Ʈ


public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	
	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	SpawnEnemy();
	virtual void	SpawnAnimation();
	virtual void	GetDamage();
	void			HpBarDelete();
	// GETSET //
	int		GetAttackCoolTime() { return _attackCoolTime; }
	float	GetMoveSpeed()		{ return _moveSpeed; }
	bool	GetIsSpawned()		{ return _isSpawned; }
	int		GetHpBarAlphe()		{ return _hpBarAlpha; }

	void	SetHpBarAlpha(int hpBarAlpha) { _hpBarAlpha = hpBarAlpha; }
	void	SetAttackCoolTime(int coolTime)	{ _attackCoolTime = coolTime; }
	void	SetMoveSpeed(float speed)		{ _moveSpeed = speed; }
};
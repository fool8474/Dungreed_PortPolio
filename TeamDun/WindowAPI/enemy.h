#pragma once
#include "Object.h"

enum ENEMYSTATE {
	ES_IDLE, ES_MOVE, ES_ATTACK
};

class Enemy : public Object
{
protected :
	ENEMYSTATE		_state;				// ���� ����
	RECT			_body;				// �浹ü
	int				_attackCoolTime;	// ���� ��Ÿ��
	int				_useBulletId;		// ����ϴ� �Ҹ� ID
	float			_moveSpeed;			// �̵��ӵ�
	float			_gravity;			// ���� �߷°�
	int				_count;				// �ִϸ��̼� �� ī��Ʈ
	int				_index;				// �ִϸ��̼� �� �ε���

public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	
	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();

	// GETSET //
	RECT getBody() { _body; }
	int getAttackCoolTime() { _attackCoolTime; }
	float getMoveSpeed() { _moveSpeed; }

	void setBody(RECT rc) { _body = rc; }
	void setAttackCoolTime(int coolTime) { _attackCoolTime = coolTime; }
	void setMoveSpeed(float speed) { _moveSpeed = speed; }
};
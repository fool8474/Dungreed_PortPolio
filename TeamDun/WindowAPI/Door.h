#pragma once
#include "Object.h"
class Door : public Object
{
private :
	DIRECTION	_dir;
	bool		_isActivated;	// Ȱ��ȭ�� ���¶��
	bool		_isSpawning;	// �����Ǿ ���̴� ���¶��

public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();

	// GETSET //
	void		SetDirection(DIRECTION dir)		{ _dir = dir; }
	void		SetIsActivated(bool isActive)	{ _isActivated = isActive; }
	void		SetIsSpawning(bool isSpawn)		{ _isSpawning = isSpawn; }
	DIRECTION	GetDirection()					{ return _dir; }
	bool		GetIsActivated()				{ return _isActivated; }
};


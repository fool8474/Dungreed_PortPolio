#pragma once
#include "Object.h"

//��ȣ�ۿ��� �ʿ����� ���� �̹������� NPC ���� Ŭ���� �Դϴ� (Ÿ��)

enum TOWNNPCSTATE
{
	TNS_IDLE, TNS_RUN
};
class townNPCimage : public Object
{
private:
	TOWNNPCSTATE	_state;
	bool			_isLeft;
	int				_count;
	int				_index;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
};
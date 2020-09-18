#pragma once
#include "gameNode.h"

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC
};

class Object : public gameNode
{
public :
	float		_x;				// ��ġ X 
	float		_y;				// ��ġ Y
	OBJECTTYPE	_type;			// ������Ʈ Ÿ��
	int			_spawnTime;		// ���� �ð�
};


#pragma once

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC, OT_OBSTACLE, OT_BREAKABLE
};

class Object 
{
private :
	float			_x;				// ��ġ X 
	float			_y;				// ��ġ Y
	OBJECTTYPE		_type;			// ������Ʈ Ÿ��
	int				_spawnTime;		// ���� �ð�
	vector<image*>	_vImages;		// �̹�����

public :
	// GETSET //
	int GetX() { return _x; }
	void SetX(int x) { _x = x; }
	int GetY() { return _y; }
	void SetY(int y) { _y = y; }
	OBJECTTYPE GetType() { return _type; }
	void SetType(OBJECTTYPE type) { _type = type; }
	image* GetImage(int index) { return _vImages[index]; }
	void Setimage(int index, image* img) { _vImages[index] = img; }
};
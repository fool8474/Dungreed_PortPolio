#pragma once

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC, OT_OBSTACLE, OT_BREAKABLE, OT_ETC
};

class Object 
{
private :
	int				_id;			// ID
	string			_name;			// �̸�
	OBJECTTYPE		_type;			// ������Ʈ Ÿ��
	vector<image*>	_vImages;		// �̹�����
	float			_x;				// ��ġ X 
	float			_y;				// ��ġ Y
	int				_useImage;		// ������� �̹���
	int				_frameX;		// ���� ������ X
	int				_frameY;		// ���� ������ Y
	int				_spawnTime;		// ���� �ð�

public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	// GETSET //
	string		GetName()						{ return _name; }
	int			GetX()							{ return _x; }
	int			GetY()							{ return _y; }
	OBJECTTYPE	GetType()						{ return _type; }
	image*		GetImage(int index)				{ return _vImages[index]; }
	int			GetUseImage()					{ return _useImage; }
	int			GetFrameX()						{ return _frameX; }
	int			GetFrameY()						{ return _frameY; }

	void		SetName(string name)			{ _name = name; }
	void		SetX(int x)						{ _x = x; }
	void		SetY(int y)						{ _y = y; }
	void		SetType(OBJECTTYPE type)		{ _type = type; }
	void		Setimage(int index, image* img) { _vImages[index] = img; }
	void		SetUseImage(int index)			{ _useImage = index; }
	void		SetFrameX(int x)				{ _frameX = x; }
	void		SetFrameY(int y)				{ _frameY = y; }
	void		SetSpawnTime(int time)			{ _spawnTime = time; }
};
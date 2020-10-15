#pragma once
enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC, OT_OBSTACLE, OT_BREAKABLE, OT_ETC
};

class FieldMap;
class Object
{
protected:
	int				_id;					// ID
	string			_name;					// �̸�
	OBJECTTYPE		_type;					// ������Ʈ Ÿ��
	vector<image*>	_vImages;				// �̹�����
	vector<string>	_vImageNames;			// �̹��� �̸���
	float			_x;						// ��ġ X 
	float			_y;						// ��ġ Y
	int				_useImage;				// ������� �̹���
	int				_frameX;				// ���� ������ X
	int				_frameY;				// ���� ������ Y
	int				_spawnTime;				// ���� �ð�
	int				_frameTimer;			// ������ Ÿ�̸�
	int				_HP;					// ������Ʈ HP;
	RECT			_body;					// �浹ü
	FieldMap*		_belongMap;				// ���� ���� �� ����
	bool			_isDead;				// �׾�����(�ı��Ǿ�����) ����
	int				_renderOrder;			// ���� ���� �Ұ�����
	
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	CheckCollision();
	virtual void	GetDamage();
	// GETSET //
	int				GetHP()				{ return _HP; }
	int				GetId()				{ return _id; }
	string			GetName()			{ return _name; }
	vector<string>	GetImgNames()		{ return _vImageNames; }
	int				GetX()				{ return _x; }
	int				GetY()				{ return _y; }
	OBJECTTYPE		GetType()			{ return _type; }
	image*			GetImage(int index) { return _vImages[index]; }
	int				GetUseImage()		{ return _useImage; }
	int				GetFrameX()			{ return _frameX; }
	int				GetFrameY()			{ return _frameY; }
	RECT			GetBody()			{ return _body; }
	int				GetSpawnTime()		{ return _spawnTime; }
	FieldMap*		GetBelongMap()		{ return _belongMap; }
	bool			GetIsDead()			{ return _isDead; }
	int				GetRenderIndex()	{ return _renderOrder; }

	void			SetHp(int hp)						{ _HP = hp; }
	void			SetName(string name)				{ _name = name; }
	void			SetX(int x)							{ _x = x; }
	void			SetY(int y)							{ _y = y; }
	void			SetType(OBJECTTYPE type)			{ _type = type; }
	void			Setimage(int index, image* img)		{ _vImages[index] = img; }
	void			SetUseImage(int index)				{ _useImage = index; }
	void			SetFrameX(int x)					{ _frameX = x; }
	void			SetFrameY(int y)					{ _frameY = y; }
	void			SetFrameTimer(int timer)			{ _frameTimer = timer; }
	void			SetSpawnTime(int time)				{ _spawnTime = time; }
	void			SetBelongMap(FieldMap* map)			{ _belongMap = map; }
	virtual void	SetIsDead(bool dead)				{ _isDead = dead; }
	void			SetBody(RECT rect)					{ _body = rect; }
	void			SetBodyPos()						{ _body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight()); }

	void			SetRenderIndex(int isFront)			{ _renderOrder = isFront; }
};
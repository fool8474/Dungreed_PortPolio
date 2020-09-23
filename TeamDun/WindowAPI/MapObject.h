#pragma once

/// <summary>
/// �������� �����Ϳ����� ����� ������Ʈ
/// </summary>
class MapObject
{
public :
	int			_id;				// ������Ʈ ���̵�
	float		_x;					// X
	float		_y;					// Y
	int			_spawnTime;			// ���� �ð�
	int			_page;				// ������

	image*		_image;
	int			_animationTimer;	// �ִϸ��̼� Ÿ�̸�
	int			_frameX;			// �ִϸ��̼� ������ X
	int			_frameY;			// �ִϸ��̼� ������ Y
	int			_alpha;

public :
	HRESULT init(int id, float x, float y, int page);
	void update();
	void render(HDC hdc);
	void release();

	void Animation();
	void SetSpawnTime(int spawnTime) { _spawnTime = spawnTime; }
};
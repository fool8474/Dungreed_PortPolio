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
	image		_img;				// �̹���

	int			_animationTimer;	// �ִϸ��̼� Ÿ�̸�
	int			_frameX;			// �ִϸ��̼� ������ X
	int			_frameY;			// �ִϸ��̼� ������ Y

private :
	void Animation();
	void SetSpawnTime(int spawnTime) { _spawnTime = spawnTime; }
};
#pragma once

// ��ƼŬ �ϳ��ϳ��� �Ǵ� Ŭ����
class particle
{
public:
	float			_x;				// ���� ��ġ X
	float			_y;				// ���� ��ġ Y
	float			_xSpeed;		// ���� �ӵ� X
	float			_ySpeed;		// ���� �ӵ� Y
	float			_speedChangerX;	// �ӵ� ������ X
	float			_speedChangerY;	// �ӵ� ������ Y
	float			_angle;			// ����
	float			_angleChanger;	// ���� ������
	float			_alpha;			// ���İ�
	float			_alphaChanger;	// ���İ� ������
	float			_scale;			// ������
	float			_scaleChanger;	// ������ ������
	int				_time;			// �� ��ƼŬ�� ����ִ� �ð� (�� �ð� �ڿ� �����) 
	image*			_image;			// ���õ� �̹���

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	// �������� ��ƼŬ�� INIT
	void initParticle(
		float x, float y, 
		float speedChangerX, float speedChangerY, float xSpeed, float ySpeed, 
		float angleChanger, float angle, 
		float alphaChanger, float alpha, 
		float scaleChanger, float scale,
		float time, 
		string name);
};
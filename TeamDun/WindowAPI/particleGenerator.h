#pragma once
#include "particle.h"

// ��ƼŬ�� Ÿ��
enum GENERATETYPE 
{
	REGULARGEN,	// ������ �ֱ⸶�� ���������� �����ȴ�
	RANDOMGEN,	// ������ �ֱ⸶�� ���������� �����ȴ�
	ONETIME		// �ѹ��� ���ÿ� �����ȴ�
};

// ���� �ð����� Ÿ�Կ� ���� ��ƼŬ�� ������Ű�� ��ƼŬ ������
class ParticleGenerator
{
public:

	// Speed
	float			_xSpeed;
	float			_ySpeed;
	float			_xSpeedRandom;
	float			_ySpeedRandom; 
	float			_speedChangerX;
	float			_speedChangerY;
	
	// Scale
	float			_scale;
	float			_scaleRandom;
	float			_scaleChanger;

	// Angle
	float			_angle;
	float			_angleRandom;
	float			_angleChanger;

	// XY ��ǥ
	float			_particleX;
	float			_particleY;
	float			_particleXRandom;
	float			_particleYRandom;
	
	// ALPHA
	float			_alpha;
	float			_alphaRandom;
	float			_alphaChanger;
	
	// ��ƼŬ ���� �ð�
	int				_particleTime;
	int				_particleTimeRandom;

	// PARTICLE GENERATOR
	GENERATETYPE	_generateType;		// ��ƼŬ�� ���� Ÿ��
	int				_initGenTime;		// �ʱ� ���� �ð�
	int				_genTime;			// �ʱ� ���� �ð��� �������� �ΰ��� �� (�������� �����ð�)
	int				_genTimeRandom;		// �����Ǵ� �ð��� ������ ����
	float			_genX;				// ��ƼŬ �������� ��ġ X
	float			_genY;				// ��ƼŬ �������� ��ġ Y
	int				_genLiveTime;		// ��ƼŬ �����Ⱑ ����ִ� �ð�
	int				_multipleGenerate;	// �ѹ��� ��� ��ƼŬ�� �����ɰ�����
	vector<string>	_vImageName;		// ��ƼŬ�� ���� �̹��� ���

	bool			_isGenerateOnce;	// �ѹ� �����Ǿ����� ���� (ONETIME TYPE���� ���)

	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void initGenerator(GENERATETYPE genType = GENERATETYPE::REGULARGEN, int genLiveTime = 1000, int genTime = 10, int gentimeRandom = 0, int multipleGenerate = 1, vector<string> imageName = vector<string>{ "" });
	void initPos(float genX = 0, float genY = 0, float xRandom = 0, float yRandom = 0);
	void initSpeed(float speedX = 3, float speedY = 3, float speedRandomX = 0, float speedRandomY = 0, float speedChangerX = 0, float speedChangerY = 0);
	void initAngle(float angle = 0, float angleRandom = PI*2, float angleChanger = 0);
	void initScale(float scale = 1, float scaleRandom = 0, float scaleChanger = 0);
	void initAlpha(float alpha = 255, float alphaRandom = 0, float alphaChanger = 0);
	void initTime(int particleTime = 20, int particleTimeRandom = 0);

	void SetGenTimeRandom(int genTimeRandom) { _genTimeRandom = genTimeRandom; }

	void initParticle(particle* curParticle);
};


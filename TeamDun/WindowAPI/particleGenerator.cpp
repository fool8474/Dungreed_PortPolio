#include "stdafx.h"
#include "particleGenerator.h"

void ParticleGenerator::release()
{
}

void ParticleGenerator::update()
{
	if (!_isOff)
	{
		_genLiveTime--;	// �������� ����
		_genTime--;		// �������� Ÿ�̸�

		if (_genTime < 0) // Ÿ�̸Ӱ� 0���� �۾����� ��ƼŬ�� �����Ѵ�
		{
			switch (_generateType)
			{
			case REGULARGEN: // ���� �ð� ���� Ÿ��
				_genTime = _initGenTime;
				for (int i = 0; i < _multipleGenerate; i++) // _multipleGenerate�� ��ŭ �����Ѵ�
				{
					initParticle(PARTICLEMANAGER->AddNewParticle());
				}
				break;
			case RANDOMGEN: // ���� �ð� ���� Ÿ��
				_genTime = _initGenTime + RANDOM->range(-_genTimeRandom, _genTimeRandom);
				for (int i = 0; i < _multipleGenerate; i++)
				{
					initParticle(PARTICLEMANAGER->AddNewParticle());
				}
				break;
			case ONETIME: // 1ȸ�� ���� Ÿ��
				if (!_isGenerateOnce)
				{
					for (int i = 0; i < _multipleGenerate; i++)
					{
						initParticle(PARTICLEMANAGER->AddNewParticle());
					}
					_isGenerateOnce = true;	// 1ȸ �����ߴٴ� ���� �˸�
					_genLiveTime = 0; // ������ �ڿ��� �ٷ� ��������� ó���Ѵ�
				}
				break;
			}
		}
	}
}

void ParticleGenerator::render(HDC hdc)
{
	// ������� ������ ���� ����! �Ƹ���.
}

void ParticleGenerator::initGenerator(GENERATETYPE genType, int genLiveTime, int genTime, int gentimeRandom, int multipleGenerate, vector<string> imageName)
{
	_generateType = genType;
	_genLiveTime = genLiveTime;
	_initGenTime = _genTime = genTime;
	_genTimeRandom = gentimeRandom;
	_multipleGenerate = multipleGenerate;
	_vImageName = imageName;

	initPos();
	initSpeed();
	initAngle();
	initScale();
	initAlpha();
	initTime();

	_isGenerateOnce = false;
}

void ParticleGenerator::initPos(float genX, float genY, float xRandom, float yRandom)
{
	_genX = _particleX = genX;
	_genY = _particleY = genY;
	_particleXRandom = xRandom;
	_particleYRandom = yRandom;
}

void ParticleGenerator::initSpeed(float speedX, float speedY, float speedRandomX, float speedRandomY, float speedChangerX, float speedChangerY)
{
	_xSpeed = speedX;
	_ySpeed = speedY;
	_xSpeedRandom = speedRandomX;
	_ySpeedRandom = speedRandomY;
	_speedChangerX = speedChangerX;
	_speedChangerY = speedChangerY;
}

void ParticleGenerator::initAngle(float angle, float angleRandom, float angleChanger)
{
	_angle = angle;
	_angleRandom = angleRandom;
	_angleChanger = angleChanger;
}

void ParticleGenerator::initScale(float scale, float scaleRandom, float scaleChanger)
{
	_scale = scale;
	_scaleRandom = scaleRandom;
	_scaleChanger = scaleChanger;
}

void ParticleGenerator::initAlpha(float alpha, float alphaRandom, float alphaChanger)
{
	_alpha = alpha;
	_alphaRandom = alphaRandom;
	_alphaChanger = alphaChanger;
}

void ParticleGenerator::initTime(int particleTime, int particleTimeRandom)
{
	_particleTime = particleTime;
	_particleTimeRandom = particleTimeRandom;
}

void ParticleGenerator::initParticle(particle* curParticle)
{
	curParticle->initParticle(
		_particleX + RANDOM->range(-_particleXRandom / 2, _particleXRandom / 2),			// X��ǥ�� ������ �߰�
		_particleY + RANDOM->range(-_particleYRandom / 2, _particleYRandom / 2),			// Y��ǥ�� ������ �߰�
		_speedChangerX, _speedChangerY,														// ���ǵ� XY ��ȭ��
		_xSpeed + RANDOM->range(-_xSpeedRandom / 2, _xSpeedRandom / 2),						// X���ǵ� ������ �߰�
		_ySpeed + RANDOM->range(-_ySpeedRandom / 2, _ySpeedRandom / 2),						// Y���ǵ� ������ �߰�
		_angleChanger,																		// ������ ��ȭ��
		_angle + RANDOM->range(-_angleRandom / 2, _angleRandom / 2),						// ������ ������ �߰�
		_alphaChanger,																		// ���İ� ��ȭ��
		_alpha + RANDOM->range(-_alphaRandom / 2, _alphaRandom / 2),						// ���İ� ������ �߰�
		_scaleChanger,																		// ũ�� XY ��ȭ��
		_scale + RANDOM->range(-_scaleRandom / 2, _scaleRandom / 2),						// ũ�� X ������ �߰�
		_particleTime + RANDOM->range(-_particleTimeRandom / 2, _particleTimeRandom / 2),	// ��ƼŬ ���� �ð��� ������ �߰�
		_vImageName[RANDOM->range((int)_vImageName.size())]									// �̹��� �� �ϳ��� ������ ��ƼŬ�� �Է�
	);
}

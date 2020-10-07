#pragma once
#include "singletonBase.h"
#include "particleGenerator.h"
#include "ObjectPooler.h"

class ParticleManager : public singletonBase <ParticleManager> // �̱��� �Ŵ���
{
private :
	objectPool<particle>		_opParticle;	// ��ƼŬ���� ObjectPool�� �̿��� �����Ѵ�
	vector<ParticleGenerator*>	_vGenerators;	// ��ƼŬ �������� ���
	vector<particle*>			_vParticles;	// ��ƼŬ�� ���
	
public:

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// �������� ��ƼŬ �������� �ʱ�ȭ
	
	// �����⸦ �����
	void AddGenerator(ParticleGenerator* gen);

	// ��ƼŬ�� ObjectPooler�κ��� �޾ƿ´�
	particle* AddNewParticle();

	vector<ParticleGenerator*>& GetGenerators() { return _vGenerators; }
	vector<particle*>& GetParticles() { return _vParticles; }
};
#include "stdafx.h"
#include "ParticleManager.h"

void ParticleManager::init()
{
	_opParticle.SetSize(4000); // ObjectPooler �ʱ�ȭ (4000���� �̸� �����س���)
}

void ParticleManager::release()
{
	for (int i = 0; i < _vGenerators.size(); i++)
	{
		_vGenerators[i]->release();
		SAFE_DELETE(_vGenerators[i]);
	}

	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->release();
		SAFE_DELETE(_vParticles[i]);
	}

	releaseSingleton();
}

void ParticleManager::update()
{
	for (int i = 0; i < _vGenerators.size(); i++) // ��������� ������Ʈ
	{
		_vGenerators[i]->update();

		if (_vGenerators[i]->_genLiveTime < 0) // ������ ���� �����⸦ �����Ѵ�
		{
			_vGenerators.erase(_vGenerators.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < _vParticles.size(); i++) // ��ƼŬ���� ������Ʈ
	{
		_vParticles[i]->update();

		if (_vParticles[i]->_time < 0) // ������ ���� ��ƼŬ�� �����Ѵ�
		{
			_opParticle.ReturnObject(_vParticles[i]);	// ObjectPooler�� �ٽ� ��ƼŬ�� ����ִ´�
			_vParticles.erase(_vParticles.begin() + i);	// �ش� ��ƼŬ�� ���ͷκ��� �����Ѵ�
			i--;
		}
	}
}

void ParticleManager::render(HDC hdc)
{
		
	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->render(hdc); // ��ƼŬ���� �����ϵ��� �Ѵ�
	}
}

void ParticleManager::AddGenerator(ParticleGenerator* gen)
{
	_vGenerators.push_back(gen);
}

particle* ParticleManager::AddNewParticle()
{
	_vParticles.push_back(_opParticle.PopObject()); // ObjectPooler�κ��� ��ƼŬ�� �ϳ� �޾ƿ� ��ƼŬ ��Ͽ� �ִ´�
	return _vParticles[_vParticles.size() - 1];		// ��� ���� �ָ� �������ش�
}

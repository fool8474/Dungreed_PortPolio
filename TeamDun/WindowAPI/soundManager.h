#pragma once
#include "singletonBase.h"
/*FMOD ����ϱ� ���� ���̺귯�� �߰�*/
#include "FMOD/inc/fmod.hpp"
#pragma comment (lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;
//=============================================================
//	## soundManager ## (���� �Ŵ���)
//=============================================================

//����� ������� (���尹���� 30�� �Ѿ�� ũ�⸦ �� �÷���� �Ѵ�)
#define SOUNDBUFFER 450

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;		//�ý��� Ŭ����
	Sound** _sound;			//���� Ŭ����
	Channel** _channel;		//ä�� Ŭ����

	arrSound _mTotalSound;	//�ʿ� ��Ƶ� �����

	vector<string> _vStarts;	// ��� ������� �ֵ�
	vector<string> _bgmStrings;	// BGM ��Ʈ�� ���
	int	_fadeOutCount;
	int _fadeInCount;
public:
	HRESULT init();
	void release();
	void update();

	//���� �߰� (Ű��, �����̸�, BGM?, ������ų�ų�)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	void play(string keyName, float volume = 0.5f, bool useOverlapVolumeDown = false, bool useFadeIn = true);


	//���� ����
	void stop(string keyName);
	//���� �Ͻ�����
	void pause(string keyName);
	//���� �ٽ����
	void resume(string keyName);

	//�÷��� ���̳�?
	bool isPlaySound(string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound(string keyName);

	void StopAllBGM(bool useFadeIN = true);
	void FadeInBGM();
	void FadeOutBGM();
};
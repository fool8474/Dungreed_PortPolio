#pragma once
#include "singletonBase.h"
#include "FMOD/inc/fmod.hpp"
#pragma comment (lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;

//����� �������, �����Ӱ� �������� ��
#define SOUNDBUFFER 450

/// <summary>
/// ���带 �����ϴ� ����Ŵ���, FMOD�� ���.
/// </summary>
class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System*			_system;		//�ý��� Ŭ����
	Sound**			_sound;			//���� Ŭ����
	Channel**		_channel;		//ä�� Ŭ����

	arrSound		_mTotalSound;	//�ʿ� ��Ƶ� �����

	vector<string>	_vStarts;		// ��� ������� �ֵ�
	vector<string>	_bgmStrings;	// BGM ��Ʈ�� ���
	int				_fadeOutCount;	// ���̵� �ƿ� ī��Ʈ
	int				_fadeInCount;	// ���̵� �� ī��Ʈ
public:

	// �⺻ //
	HRESULT init();
	void release();
	void update();

	// ��� //
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);
	void play(string keyName, float volume = 0.5f, bool useOverlapVolumeDown = false, bool useFadeIn = true);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
	void StopAllBGM(bool useFadeIN = true);
	void FadeInBGM();
	void FadeOutBGM();
};
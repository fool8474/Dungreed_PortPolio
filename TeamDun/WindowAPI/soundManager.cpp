#include "stdafx.h"
#include "soundManager.h"

HRESULT soundManager::init()
{
	//FMOD �ý����� �����Ѵ�
	System_Create(&_system);

	//����, ä�μ� ����
	_system->init(SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� Ŭ���� �����Ҵ�
	_sound = new Sound * [SOUNDBUFFER];
	_channel = new Channel * [SOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * SOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * SOUNDBUFFER);

	//Fade In / Out
	_fadeOutCount = 0;
	_fadeInCount = 0;
	return S_OK;
}

void soundManager::release()
{
	//���� �� ä�� ����
	if (_sound != NULL || _channel != NULL)
	{
		for (int i = 0; i < SOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE_ARRAY(_sound);
	SAFE_DELETE_ARRAY(_channel);

	//�ý��� �ݱ�
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update()
{
	_system->update();
	FadeOutBGM();
	FadeInBGM();
}

/// <summary>
/// ���� �߰�
/// </summary>
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{

	if (loop) // BGM�� �ַ� ����ϴ� Loop
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]); // �Ѱ��� ���ϸ��� ���
			_bgmStrings.push_back(soundName);
		}
		else // ȿ���� Loop�� ���� ����.
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
			_bgmStrings.push_back(soundName);
		}
	}
	else // ȿ������ �ַ� ����ϴ� No Loop
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));	//�ʿ� ���带 Ű���� �Բ� ��Ƶд�
}

/// <summary>
/// ���带 ���
/// </summary>
void soundManager::play(string keyName, float volume, bool useOverlapVolumeDown, bool useFadeIn)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			FMOD_MODE mode;
			_channel[count]->getMode(&mode);
			if (mode == 131274) // LOOP�ϴ¾ָ� (BGM)
			{
				_vStarts.push_back(keyName);
				if(useFadeIn) _channel[count]->setVolume(0); // ���̵����� ����ϴ� ��� �ʱ� ���带 0����
				else _channel[count]->setVolume(0.5f); // �ƴϸ� default ������
			} 

			else // ȿ�����̸�
			{
				if (useOverlapVolumeDown) // ���� ��ĥ �� ���� �ٿ� ����Ѵٸ�
				{
					if(isPlaySound(keyName)) // ������� �����
						_channel[count]->setVolume(volume * 0.5f); // �� �� ���� ����� ���� ����ǵ���
					else
						_channel[count]->setVolume(volume); // �׳� ����ϵ���
				}
				else
				{
					_channel[count]->setVolume(volume);
				}
			}

			break;
		}
	}
}

/// <summary>
/// ���带 �����Ѵ�
/// </summary>
void soundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->stop();
		}
	}
}

/// <summary>
/// ���带 �Ͻ������Ѵ�
/// </summary>
void soundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ�����
			_channel[count]->setPaused(true);
		}
	}
}

/// <summary>
/// ���带 �簳�Ѵ�
/// </summary>
void soundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �ٽ����
			_channel[count]->setPaused(false);
		}
	}
}

/// <summary>
/// ���� ���尡 �÷��������� Ȯ���Ѵ�.
/// </summary>
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->getPaused(&isPlay);
			break;
		}
	}
	return !isPlay;
}

/// <summary>
/// ���� ���尡 �Ͻ����������� Ȯ���Ѵ�.
/// </summary>
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ�����
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

/// <summary>
/// ��� BGM�� �������ִ� ���
/// </summary>
void soundManager::StopAllBGM(bool useFadeIn)
{
	_vStarts.clear();

	_fadeOutCount = 150;
	if(useFadeIn) _fadeInCount = 150;
}

/// <summary>
/// BGM ���̵� ��
/// </summary>
void soundManager::FadeInBGM()
{
	if (_fadeInCount > 0 && _fadeOutCount == 0)
	{
		int count = 0;
		for (int i = 0; i < _vStarts.size(); i++)
		{
			_fadeInCount--;

			arrSoundIter iter = _mTotalSound.begin();
			for (iter; iter != _mTotalSound.end(); ++iter, count++)
			{
				FMOD_MODE mode;
				_channel[count]->getMode(&mode);
				if (mode == 131274) // LOOP�ϴ¾ָ� (BGM)
				{
					for (int i = 0; i < _vStarts.size(); i++) // ���ҽ�Ű�� ���� �ֵ� ����Ʈ
					{
						if (_vStarts[i].compare(iter->first) == 0)
						{
							float volume;
							_channel[count]->getVolume(&volume);

							if (volume < 50)
							{
								_channel[count]->setVolume(volume + 0.5f / 150); // ���� �������� õõ�� ������ ���δ�.
							}
						}
					}
				}
			}
		}

		if (_fadeInCount == 0)
		{
			_vStarts.clear();
		}
	}

}

/// <summary>
/// BGM ���̵� �ƿ�
/// </summary>
void soundManager::FadeOutBGM()
{
	int count = 0;

	if (_fadeOutCount > 0)
	{
		_fadeOutCount--;

		arrSoundIter iter = _mTotalSound.begin();
		for (iter; iter != _mTotalSound.end(); ++iter, count++)
		{
			bool playSound = false;
			FMOD_MODE mode;
			_channel[count]->getMode(&mode);
			if (mode == 131274) // LOOP�ϴ¾ָ� (BGM)
			{
				for (int i = 0; i < _vStarts.size(); i++) // ���ҽ�Ű�� ���� �ֵ� ����Ʈ
				{
					if (_vStarts[i].compare(iter->first) == 0) 
					{
						playSound = true;
						break;
					}
				}

				if (playSound)
				{
					continue;
				}

				else
				{
					float volume;
					_channel[count]->getVolume(&volume);

					if (volume > 0)
					{
						_channel[count]->setVolume(volume - 0.5f / 150); // ���� �������� õõ�� ������ ���δ�.
					}
				}
			}
		}
	}
}
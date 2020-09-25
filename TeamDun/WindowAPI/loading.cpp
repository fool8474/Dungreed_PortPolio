#include "stdafx.h"
#include "loading.h"

/////////////////////////////// LOADITEM ���� //////////////////////////////////////////////

/// <summary>
/// �ʱ�ȭ - ����
/// </summary>
HRESULT LoadItem::init(string keyName, string soundName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_soundResource.keyName = keyName;
	_soundResource.fileName = soundName;
	_soundResource.isBGM = bgm;
	_soundResource.isLoop = loop;

	return S_OK;
}

/// <summary>
/// �ʱ�ȭ - �̹��� 1 (�⺻)
/// </summary>
HRESULT LoadItem::init(string strKey, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

/// <summary>
/// �ʱ�ȭ - �̹��� 2 (���� �̸� �� ������ ���� �߰�)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

/// <summary>
/// �ʱ�ȭ - �̹��� 3 (����� ��ǥ �߰�)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

/// <summary>
/// �ʱ�ȭ - ������ �̹��� 1 (�⺻)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;
	_imageResource.isRotate = isRotate;

	return S_OK;
}

/// <summary>
/// �ʱ�ȭ - ������ �̹��� 2 (����� ��ǥ �߰�)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;
	_imageResource.isRotate = isRotate;
	return S_OK;
}

/////////////////////////////// LOADING ���� //////////////////////////////////////////////

HRESULT Loading::init()
{
	return S_OK;
}

void Loading::release()
{
	for (int i = 0; i < _vLoadItem.size(); i++) SAFE_DELETE(_vLoadItem[i]);
}

void Loading::update()
{
}

void Loading::render()
{
}

/// <summary>
/// �ε� - ����
/// </summary>
void Loading::LoadSound(string keyName, string soundName, bool bgm, bool loop)
{
	LoadItem*item = new LoadItem;
	item->init(keyName, soundName, bgm, loop); // ������ �ʱ�ȭ�� ���� ��
	_vLoadItem.push_back(item);	// vLoadItem�� �߰�
}

/// <summary>
/// �ε� - �̹��� 1 (�⺻)
/// </summary>
void Loading::LoadNormalImage(string strKey, int width, int height)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

/// <summary>
/// �ε� - �̹��� 2 (���� �̸� �� ������ ���� �߰�)
/// </summary>
void Loading::LoadNormalImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

/// <summary>
/// �ε� - �̹��� 3 (����� ��ǥ �߰�)
/// </summary>
void Loading::LoadNormalImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

/// <summary>
/// �ε� - ������ �̹��� 1 (�⺻)
/// </summary>
void Loading::LoadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor, isRotate);
	
	_vLoadItem.push_back(item);
}

/// <summary>
/// �ε� - ������ �̹��� 2 (����� ��ǥ �߰�)
/// </summary>
void Loading::LoadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, width, x, y, height, frameX, frameY, isTrans, transColor, isRotate);
	_vLoadItem.push_back(item);
}

/// <summary>
/// �ش� �������� Ÿ�Կ� ���߾� IMAGEMANAGER�� SOUNDMANAGER�� �߰��ϴ� �۾��� �ǽ��Ѵ�.
/// </summary>
void Loading::LoadingDone(LoadItem* item)
{
	// �������� Ÿ�Կ� ���߾� ADD �۾��� �̷�����.
	switch (item->getLoadKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
			_curKey = img.keyName;
		}
		break;
		
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
			_curKey = img.keyName;
		}
		break;
		
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
			_curKey = img.keyName;
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
			_curKey = img.keyName;
			if (img.isRotate) IMAGEMANAGER->MakeRotateImage(_curKey); // ȸ���Ѵٸ� ȸ������ ���ش�.
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
			_curKey = img.keyName;
			if (img.isRotate) IMAGEMANAGER->MakeRotateImage(_curKey); // ȸ���Ѵٸ� ȸ������ ���ش�.
		}
		break;

		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.keyName, sound.fileName, sound.isBGM, sound.isLoop);
			_curKey = sound.keyName;
		}
		break;
	}
}



#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::init(string keyName, string soundName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_soundResource.keyName = keyName;
	_soundResource.fileName = soundName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

HRESULT loadItem::init(string strKey, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
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

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
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

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
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

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
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

//=============================================================
//	## loading ## (�ε�Ŭ���� - �ε�ȭ�� �����ϱ�, �ε���, ��׶���)
//=============================================================
HRESULT loading::init()
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addFrameImage("bgLoadingScene", "Images/LOADING.bmp", WINSIZEX * 6, WINSIZEY, 6, 1);
	//�ε��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("loadingBarFront", "loadingBarFront.bmp", 620, 200);
	IMAGEMANAGER->addImage("loadingBarBack", "loadingBarBack.bmp", 620, 200);
	IMAGEMANAGER->addFrameImage("number", "Images/number.bmp", 220, 28, 10, 1);

	//�ε��� Ŭ���� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack");
	//�ε��� ��ġ �ʱ�ȭ
	_loadingBar->setPos(410, 210);

	//���� ������
	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	//�ε��� ����
	SAFE_DELETE(_loadingBar);
	
}

void loading::update()
{
	//�ε��� Ŭ���� ������Ʈ
	_loadingBar->update();
	this->animation();
}

void loading::render()
{
	//�ε��� Ŭ���� ����
	_loadingBar->render();
	//��׶��� �̹��� ����
	_background->frameRender(getMemDC(), 0, 0);
	textOut(getMemDC(), _loadingBar->getX() + 250, _loadingBar->getY() + 330, text.c_str(), text.length());
}

void loading::animation()
{
	_count++;
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > _background->getMaxFrameX())
		{
			_index = 0;
		}
		_background->setFrameX(_index);
	}
}

void loading::loadSound(string keyName, string soundName, bool bgm, bool loop)
{
	loadItem*item = new loadItem;
	item->init(keyName, soundName, bgm, loop);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor, isRotate);
	
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, x, y, height, frameX, frameY, isTrans, transColor, isRotate);
	_vLoadItem.push_back(item);
}

bool loading::loadingDone()
{
	//�ε��Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
			text = img.keyName;
		}
		break;
		
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
			text = img.keyName;
		}
		break;
		
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
			text = img.keyName;
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
			text = img.keyName;
			if (img.isRotate) IMAGEMANAGER->MakeRotateImage(text);
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
			text = img.keyName;
			if (img.isRotate) IMAGEMANAGER->MakeRotateImage(text);
		}
		break;

		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.keyName, sound.fileName, sound.bgm, sound.loop);
			text = sound.keyName;
		}
		break;
	}
	
	//���� ������ ����
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);

	return false;
}



#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	this->deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);
	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}
	
	img->setKey(strKey);

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}
	
	img->setKey(strKey);

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ�
	//���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�ҵ��� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		//key->first => Ű
		return key->second; //�ش� ������ = ��(�̹��� Ŭ����)
	}

	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ� �̹����� ��������
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL imageManager::deleteAll()
{
	//�� ��ü�� ���鼭 �ϳ��� ���� �����
	mapImageIter iter = _mImageList.begin();

	//for (;;) => while(true)
	for (;iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	//�� ��ü�� ����
	_mImageList.clear();

	return true;
}

//=============================================================
//	## �Ϲݷ��� ##
//=============================================================
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//=============================================================
//	## ���ķ��� ##
//=============================================================
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::stretchRender(string strKey, HDC hdc, int destX, int destY, float scaleX, float scaleY)
{
	image* img = findImage(strKey);
	if (img) img->stretchRender(hdc, destX, destY, scaleX, scaleY);
}

//=============================================================
//	## �����ӷ��� ##
//=============================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

//=============================================================
//	## �����Ӿ��ķ��� ##
//=============================================================
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int alpha)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

//=============================================================
//	## �������� ##
//=============================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//�̹��� ã�Ƽ� �׳� �̹���Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

void imageManager::frameStretchRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY)
{
	image* img = findImage(strKey);
	if (img) img->frameStretchRender(hdc, destX, destY, currentFrameX, currentFrameY, scaleX, scaleY);
}

void imageManager::MakeRotateImage(string strKey)
{
	image* img = findImage(strKey);
	int x, y;
	int orig_x, orig_y;
	int pixel;

	for (int frameX = 1; frameX < 12; frameX++)
	{
		double radian = (frameX * 30 * PI / 180.0);
		double cc = cos(radian), ss = sin(-radian);
		double xcenter = (double)img->getFrameWidth() / 2.0, ycenter = (double)img->getFrameHeight() / 2.0;

		for (y = 0; y < img->getFrameHeight(); y++)
		{
			for (x = 0; x < img->getFrameWidth(); x++)
			{
				orig_x = (int)(xcenter + ((double)y - ycenter) * ss + ((double)x - xcenter) * cc);
				orig_y = (int)(ycenter + ((double)y - ycenter) * cc - ((double)x - xcenter) * ss);
				pixel = 0;

				if ((orig_y >= 0 && orig_y < img->getFrameHeight()) && (orig_x >= 0 && orig_x < img->getFrameWidth())) 
					SetPixel(img->getMemDC(), frameX * img->getFrameWidth() + x, y, GetPixel(img->getMemDC(), orig_x, orig_y));
			} 
		}
	}
}
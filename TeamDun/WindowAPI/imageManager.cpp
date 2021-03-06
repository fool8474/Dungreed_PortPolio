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

image* imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);
	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	//if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);

	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.erase(strKey);
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);

	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);

	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면
	//새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으니 새로 생성후 초기화 하자
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	img->setKey(strKey);

	//맵이미지 리스트에 추가
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았따면 이미지클래스 리턴
	if (key != _mImageList.end())
	{
		//key->first => 키
		return key->second; //해당 데이터 = 값(이미지 클래스)
	}

	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 이미지를 삭제하자
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 해제
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL imageManager::deleteAll()
{
	//맵 전체를 돌면서 하나씩 전부 지운다
	mapImageIter iter = _mImageList.begin();

	//for (;;) => while(true)
	for (; iter != _mImageList.end();)
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
	//맵 전체를 삭제
	_mImageList.clear();

	return true;
}

//=============================================================
//	## 일반렌더 ##
//=============================================================
void imageManager::render(string strKey, HDC hdc, int destX, int destY, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, angle);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, angle);
}

//=============================================================
//	## 알파렌더 ##
//=============================================================
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha, angle);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha, angle);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha, angle);
}

void imageManager::stretchRender(string strKey, HDC hdc, int destX, int destY, float scaleX, float scaleY, float angle)
{
	image* img = findImage(strKey);
	if (img) img->stretchRender(hdc, destX, destY, scaleX, scaleY, angle);
}

//=============================================================
//	## 프레임렌더 ##
//=============================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, angle);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY , angle);
}

//=============================================================
//	## 프레임알파렌더 ##
//=============================================================
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int alpha,float angle)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha , angle);
}

void imageManager::frameStretchAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle)
{
	image* img = findImage(strKey);
	if (img) img->frameStretchAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, scaleX, scaleY, alpha ,angle);
}

//=============================================================
//	## 루프렌더 ##
//=============================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//이미지 찾아서 그냥 이미지클래스의 함수를 실행한다
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
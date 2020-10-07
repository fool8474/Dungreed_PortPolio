#pragma once
#include "singletonBase.h"
#include "image.h"
//=============================================================
//	## imageManager ##
//=============================================================

class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<string, image*> mapImageList;			//������ ���� �̹������
	typedef map<string, image*>::iterator mapImageIter;	//������ ���� �̹�������� �ݺ���

private:
	//map<string, image*> _mImageList;
	mapImageList _mImageList;	//���� �̹���Ŭ������ ���� STL��

public:
	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init();
	//�̹��� �Ŵ��� ����
	void release();

	//�� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//�̹��� ���Ϸ� �ʱ�ȭ
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	//�̹��� Ű������ ã��
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü����
	BOOL deleteAll();

//=============================================================
//	## �Ϲݷ��� ##
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0, float angle = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float angle = 0);

//=============================================================
//	## ���ķ��� ##
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha, float angle = 0);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha, float angle = 0);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, float angle = 0);

//=============================================================
//	## �����ӷ��� ##
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY, float angle = 0);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle = 0);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int alpha,float angle = 0);
	void frameStretchAlphaRender(string strKey ,HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle = 0);

//=============================================================
//	## ��Ʈ��ġ����##
//=============================================================
	void stretchRender(string strKey, HDC hdc, int destX, int destY, float scaleX, float scaleY, float angle = 0);

//=============================================================
//	## �������� ##
//=============================================================
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void frameStretchRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY);

//=============================================================
//  ## ȸ�� ����� ##
//=============================================================
	void MakeRotateImage(string strKey);

	imageManager() {}
	~imageManager() {}
};
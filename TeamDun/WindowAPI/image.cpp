#include "stdafx.h"
#include "image.h"
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL)
{
}
image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//�����̸�
	_fileName = NULL;
	//����Ű �÷� ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���Ϸ� �ʱ�ȭ
HRESULT image::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//���ĺ��� �ʱ�ȭ
HRESULT image::initForAlphaBlend()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ� �ʱ�ȭ
	//BlendOp => ����� AC_SRC_OVER�� ��밡��
	//BlendFlags => �׳� 0����, ���� �� ��, ���� OS���� ����ߴٰ� ��
	//AlphaFormat => 24bit���� 0, 32bit���� AC_SRC_ALPHA ����ϸ� ������ �����̰� ��� �츰 �׳� 0 
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//0 ~ 255 => 255�϶� ��������
	//_blendFunc.SourceConstantAlpha = 255;

	//���ĺ��� �̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width * 10, _imageInfo->height * 10);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX * 10;
	_blendImage->height = WINSIZEY * 10;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretchBlend()
{
	HDC hdc = GetDC(_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_FILE;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width * 10, _imageInfo->height * 10);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX * 10;
	_stretchImage->height = WINSIZEY * 10;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForRotateBlend()
{
	HDC hdc = GetDC(_hWnd);

	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_FILE;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)LoadImage(_hInstance, _fileName, IMAGE_BITMAP, _imageInfo->width, _imageInfo->height, LR_LOADFROMFILE);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = _imageInfo->width;
	_rotateImage->height = _imageInfo->height;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//����
void image::release()
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo != nullptr)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//���� �÷�Ű �ʱ�ȭ
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	//���ĺ��� �̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_blendImage != nullptr)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_blendImage);
	}

	if (_stretchImage != nullptr)
	{
		SelectObject(_stretchImage->hMemDC, _stretchImage->hOBit);
		DeleteObject(_stretchImage->hBit);
		DeleteDC(_stretchImage->hMemDC);

		SAFE_DELETE(_stretchImage);
	}
}

//����(���� ���ϴ� ��ǥ�� ����ض�, �Ϲ������� �츮�� RECT�� LT��ǥ�� �̹����� ���δ�)
void image::render(HDC hdc, int destX, int destY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	
	if (_isTrans)//���� ���ְ� ���
	{
		if (angle != 0.f)
		{
			RotateHDC(hdc, angle);
			GdiTransparentBlt(
				hdc,				//������ ����� DC
				destX,				//������ ��ǥ ����X
				destY,				//������ ��ǥ ����Y
				_imageInfo->width,	//������ �̹��� ����ũ��
				_imageInfo->height,	//������ �̹��� ����ũ��
				_rotateImage->hMemDC,	//����� ��� DC
				0, 0,				//����� ����� ��������
				_imageInfo->width,	//���� ���� ����ũ��
				_imageInfo->height,	//���� ���� ����ũ��
				_transColor);		//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
		}
			//GdiTransparentBlt : ��Ʈ�� �̹����� Ư�������� �����ϰ� ���� ���ִ� �Լ�
		else
		{
			GdiTransparentBlt(
				hdc,				//������ ����� DC
				destX,				//������ ��ǥ ����X
				destY,				//������ ��ǥ ����Y
				_imageInfo->width,	//������ �̹��� ����ũ��
				_imageInfo->height,	//������ �̹��� ����ũ��
				_imageInfo->hMemDC,	//����� ��� DC
				0, 0,				//����� ����� ��������
				_imageInfo->width,	//���� ���� ����ũ��
				_imageInfo->height,	//���� ���� ����ũ��
				_transColor);		//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
		}
	}
	else//���� �̹��� �״�� ���
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ�� �̹����� Ư�������� �����ϰ� ���� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			sourWidth,			//������ �̹��� ����ũ��
			sourHeight,			//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			sourX, sourY,		//����� ����� ��������
			sourWidth,			//���� ���� ����ũ��
			sourHeight,			//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC => ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::stretchRender(HDC hdc, int destX, int destY, float scaleX, float scaleY)
{
	if (!_stretchImage) this->initForStretchBlend();

	if (_isTrans) //���� ���ְ� ���
	{
		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, destX, destY, SRCCOPY);

		// ���� ���̰ų� ���̰�
		StretchBlt(
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_stretchImage->hMemDC,
			0, 0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_transColor);
	}

	else//���� �̹��� �״�� ���
	{
		StretchBlt(hdc, destX, destY, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchAlphaRender(HDC hdc, int destX, int destY, float scaleX, float scaleY, BYTE alpha)
{
	if (!_stretchImage) this->initForStretchBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //���� ���ְ� ���
	{

		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, destX, destY, SRCCOPY);

		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, destX, destY, SRCCOPY);
		// ���� ���̰ų� ���̰�
		StretchBlt(
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_stretchImage->hMemDC,
			0, 0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			_blendImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY, _blendFunc);


	}
	else//���� �̹��� �״�� ���
	{
		StretchBlt(hdc, destX, destY, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ��DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ���� �� => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//2
		//GdiTransparentBlt : ��Ʈ�� �̹����� Ư�������� �����ϰ� ���� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,						//������ ��ǥ ����X
			0,						//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		//3
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,						//������ ��ǥ ����X
			0,						//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,						//������ ��ǥ ����X
			0,						//������ ��ǥ ����Y
			sourWidth,				//������ �̹��� ����ũ��
			sourHeight,				//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX, sourY,			//����� ����� ��������
			sourWidth,				//���� ���� ����ũ��
			sourHeight,				//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		GdiAlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha , float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	//�̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width + destX, _imageInfo->height + destY,
			hdc, 0, 0, SRCCOPY);


		if (angle != 0)RotateHDC(hdc, angle);
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,		//������ �̹��� ����ũ��
			angle == 0? _imageInfo->hMemDC:_rotateImage->hMemDC,		//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//����� ����� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ����� ��������			
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}

	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY , float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	if (_isTrans)//���� ���ְ� ���
	{
		if (angle != 0)RotateHDC(hdc, angle);
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,	//������ �̹��� ����ũ��
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//����� ����� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ����� ��������			
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);				//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	//�̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (_isTrans)//���� ���ְ� ���
	{
		if (angle != 0)RotateHDC(hdc, angle);
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,	//������ �̹��� ����ũ��
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//����� ����� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ����� ��������			
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);				//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameStretchRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	//�̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (!_stretchImage) this->initForStretchBlend();

	if (_isTrans) //���� ���ְ� ���
	{
		if (angle != 0)RotateHDC(hdc, angle);
		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, 0, 0, SRCCOPY);

		// ���� ���̰ų� ���̰�
		StretchBlt(
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY
		);

		// �� �ڿ� ����ȭ�Ѵ�
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_stretchImage->hMemDC,
			_imageInfo->frameWidth * currentFrameX * scaleX,
			_imageInfo->frameHeight * currentFrameY * scaleY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_transColor);
	}
	else//���� �̹��� �״�� ���
	{
		StretchBlt(hdc, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameStretchAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle )
{
	if (_rotateImage == nullptr) initForRotateBlend();
	//�̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (!_stretchImage) this->initForStretchBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //���� ���ְ� ���
	{
		if (angle != 0)RotateHDC(hdc, angle);
		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX + destX, _imageInfo->height * scaleY + destY,
			hdc, 0, 0, SRCCOPY);
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width * scaleX + destX, _imageInfo->height * scaleY + destY,
			hdc, 0, 0, SRCCOPY);

		// ���� ���̰ų� ���̰�
		StretchBlt(
			_stretchImage->hMemDC,
			destX,
			destY,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY
		);

		// �� �ڿ� ����ȭ�Ѵ�
		GdiTransparentBlt(
			_blendImage->hMemDC,
			destX,
			destY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_stretchImage->hMemDC,
			(_imageInfo->frameWidth * currentFrameX * scaleX) + destX,
			(_imageInfo->frameHeight * currentFrameY * scaleY) + destY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_blendImage->hMemDC, destX + (_imageInfo->frameWidth * currentFrameX * scaleX), destY + (_imageInfo->frameHeight * currentFrameY * scaleY),
			_imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY, _blendFunc);
	}
	else // Ȯ��� ���ĸ� ���� �� (����ȭ�� ����)
	{
		StretchBlt(_blendImage->hMemDC, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth * scaleX, currentFrameY * _imageInfo->frameHeight * scaleY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY, SRCCOPY);

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_blendImage->hMemDC, destX + (currentFrameX * _imageInfo->frameWidth * scaleX), destY + (currentFrameY * _imageInfo->frameHeight * scaleY),
			_imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY, _blendFunc);
	}


}

//��������
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//������(offset)�� �Ϲ������� ���� ������Ʈ �ȿ��� ������Ʈ ó������ �־��� ��ҳ� Ư�� ���������� ������
		//offset�� � Ư���� ������ �ణ ���̰� ���� �� �Ǵ� �� ���� ��ü�� �ǹ�(���̿� ���� ������)

		//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(�Ϲݷ���-�̹����߶󼭺��̱�)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(���ķ���-�̹����߶󼭺��̱�)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void image::RotateHDC(HDC hdc, float angle)
{
	HBITMAP hTempBitmap, hOldBitmap;

	if (_rotateImage == nullptr) initForRotateBlend();

	hTempBitmap = GetRotatedBitmap(hdc, angle);
	hOldBitmap = (HBITMAP)SelectObject(_rotateImage->hMemDC, hTempBitmap);
}


HBITMAP image::GetRotatedBitmap(HDC hdc, float angle)
{
	HDC destDC = CreateCompatibleDC(hdc);											// ȸ���� ��Ʈ���� ��¹��� DC   
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, getWidth(), getHeight());		// ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� �ڵ�   

	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);                  // ȸ���� ��Ʈ���� ��¹��� DC��, ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� ����   

	HBRUSH hbrBack = CreateSolidBrush(RGB(255, 0, 255));                            // ȸ������ ����, ���鿵���� ĥ�� �귯���ڵ� ����   
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);							// �귯���ڵ� ����   
	PatBlt(destDC, 0, 0, getWidth(), getHeight(), PATCOPY);							// ���õ� �귯�÷�, ȸ���� ��Ʈ���� ��¹��� DC��, �̸� ������ ä�� ����   
	DeleteObject(SelectObject(destDC, hbrOld));                                     // �귯�� ����   

	float cosine = (float)cos(angle);												// ȸ���̵���ȯ ��Ŀ� �� cos��Ÿ ���� ����          
	float sine = (float)sin(angle);													// ȸ���̵���ȯ ��Ŀ� �� sin��Ÿ ���� ����   

	SetGraphicsMode(destDC, GM_ADVANCED);                                           // ������ ��ǥ���� ȸ���� ���Ͽ�, �׷��ȸ�带 Ȯ����� �����մϴ�.(�䱸����:��98,NT�̻�)   
	
	XFORM xform;                                                                    // �������� ǥ���ϴ� 3��3���� ��� ����   
	xform.eM11 = cosine;                                                            // 1�� 1�� ���� ���� (ȸ������)   
	xform.eM12 = sine;                                                              // 1�� 2�� ���� ���� (ȸ������)   
	xform.eM21 = -sine;                                                             // 2�� 1�� ���� ���� (ȸ������)   
	xform.eM22 = cosine;                                                            // 2�� 2�� ���� ���� (ȸ������)   
	xform.eDx = (FLOAT)getWidth() / 2.0f;                                           // 3�� 1�� ���� ���� (X�� �̵� ����)   
	xform.eDy = (FLOAT)getHeight() / 2.0f;                                          // 3�� 2�� ���� ���� (Y�� �̵� ����)   

	SetWorldTransform(destDC, &xform);

	// ȸ���� �޸�DC��, ȸ���� �̹����� ���   

	BitBlt(destDC, -(getWidth()/2.0f), -(getHeight()/2.0f), getWidth(), getHeight(), getMemDC(), 0, 0, SRCCOPY);
	
	SelectObject(destDC, hbmOldDest);
	DeleteObject(destDC);
	
	return hbmResult;
}
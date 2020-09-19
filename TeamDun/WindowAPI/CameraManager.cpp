#include "stdafx.h"
#include "cameraManager.h"


HRESULT CameraManager::init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY)
{
	// MOVE //
	_pivotX = pivotX;
	_pivotY = pivotY;
	_maxX = maxX;
	_maxY = maxY;
	_minX = minX;
	_minY = minY;
	_initDistanceX = _distanceX = disX;
	_initDistanceY = _distanceY = disY;

	// SHAKE // 
	_shakeTimer = 0;
	_shakePowerX = 0;
	_shakePowerY = 0;
	_shakeX = 0;
	_shakeY = 0;
	_tempShakeX = 0;
	_tempShakeY = 0;

	_cameraRect = RectMake(_pivotX - disX, _pivotY - disY, WINSIZEX, WINSIZEY);

	return S_OK;
}

void CameraManager::update()
{
	Shaker();
}

void CameraManager::MovePivot(float x, float y)
{
	_pivotX = x;
	_pivotY = y;
	_cameraRect = RectMake(_pivotX - _initDistanceX, _pivotY - _initDistanceY, WINSIZEX, WINSIZEY);
	//_pivotX - _initDistanceX -> _initDistance = Pivot�� ȭ�鿡�� ǥ�õ� ��ġ, _pivotX = ���� ���� X�� ��ǥ
		//_pivotX - _initDistanceX =           _INITDISTANCE = WINSIZEX/2 , _PIVOTX = WINSIZEX/2 + 100
	if (_cameraRect.left <= _minX) // LEFT�� �ּҰ� �Ǹ�
	{
		_cameraRect.left = _minX; // ī�޶� ��Ʈ�� �ּҿ� �����ش�
		_cameraRect.right = _minX + WINSIZEX;
	}
	if (_cameraRect.right >= _maxX) // RIGHT�� �ִ밡 �Ǹ�
	{
		_cameraRect.right = _maxX; // ī�޶� ��Ʈ�� �ִ뿡 �����ش�
		_cameraRect.left = _maxX - WINSIZEX;
	}
	if (_cameraRect.top <= _minY)
	{
		_cameraRect.top = _minY;
		_cameraRect.bottom = _minY - WINSIZEY;
	}
	if (_cameraRect.bottom >= _maxY)
	{
		_cameraRect.bottom = _maxY;
		_cameraRect.top = _maxY - WINSIZEY;
	}

	// SHAKE ����
	OffsetRect(&_cameraRect, _shakeX, _shakeY);
}

// MOVEPIVOTLERP :: �ε巴�� �����̰� �Ѵ�
void CameraManager::MovePivotLerp(float x, float y, float lerpSpeed)
{
	
	MovePivot(
		(x - _pivotX) / lerpSpeed + _pivotX, 
		(y - _pivotY) / lerpSpeed + _pivotY
	);
}

void CameraManager::MovePivotRegular(float x, float y, float moveSpeed)
{
	int yDis = abs(y - _pivotY);
	int xDis = abs(x - _pivotX);
	int ySpeed = y >= _pivotY ? abs(moveSpeed) : -abs(moveSpeed);
	int xSpeed = x >= _pivotX ? abs(moveSpeed) : -abs(moveSpeed);
	
	if (yDis < abs(moveSpeed)) ySpeed = ySpeed > 0 ? yDis : -yDis;
	if (xDis < abs(moveSpeed)) xSpeed = xSpeed > 0 ? xDis : -xDis;

	MovePivot(
		_pivotX + xSpeed, _pivotY + ySpeed
	);
}

void CameraManager::Shake(float shakePowerX, float shakePowerY, int shakeTime, int shakeCycle)
{
	_shakePowerX = shakePowerX;
	_shakePowerY = shakePowerY;
	_shakeTimer = shakeTime;
	_shakeCycleTimer = _shakeCycle = shakeCycle;
}

void CameraManager::ZoomInOut(HDC hdc, int destX, int destY, int sourX, int sourY, float scale)
{
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (scale < 0) scale = 0;

	StretchBlt(
		hdc,
		GetRelativeX(_pivotX) + sourX - (WINSIZEX * scale/2), GetRelativeY(_pivotY) +sourY - (WINSIZEY * scale/2),
		WINSIZEX * scale, WINSIZEY * scale,
		hdc,
		0,0,
		WINSIZEX, WINSIZEY,
		SRCCOPY
	);
}

void CameraManager::Shaker()
{
	if (_shakeTimer > 0)
	{
		// _shakeTimer�� ����ũ�� �Ͼ �ð�
		// _shakeCycleTimer�� n�����Ӹ��� �ѹ��� ����ũ�� �Ͼ��
		_shakeTimer--;
		_shakeCycleTimer--;
		
		if (_shakeCycleTimer < 0)
		{
			if (_shakeCycle == 0)
			{
				_shakeX = RANDOM->range(-_shakePowerX, _shakePowerX);
				_shakeY = RANDOM->range(-_shakePowerY, _shakePowerY);
			}

			else
			{
				_shakeX = _tempShakeX;
				_shakeY = _tempShakeY;

				_shakeX = (_tempShakeX - _shakeX) / _shakeCycle + _shakeX;
				_shakeY = (_tempShakeY - _shakeY) / _shakeCycle + _shakeY;

				_tempShakeX = RANDOM->range(-_shakePowerX, _shakePowerX);
				_tempShakeY = RANDOM->range(-_shakePowerY, _shakePowerY);

			}
			
			_shakeCycleTimer = _shakeCycle;
		}

		else // SHAKE�� �ֱ⸶�� �ڿ������� �̵��ϵ���
		{
			_shakeX = (_tempShakeX - _shakeX) / _shakeCycle + _shakeX;
			_shakeY = (_tempShakeY - _shakeY) / _shakeCycle + _shakeY;
			// LERP
		}

		if (_shakeTimer == 0)
		{
			_shakePowerX = 0;
			_shakePowerY = 0;
			_shakeX = 0;
			_shakeY = 0;
		}
	}
}

void CameraManager::Render(HDC hdc, image* ig, int destX, int destY)
{
	ig->render(hdc, GetRelativeX(destX), GetRelativeY(destY));
}

void CameraManager::FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY)
{
	ig->frameRender(hdc, GetRelativeX(destX), GetRelativeY(destY), frameX, frameY);
}

void CameraManager::StretchRender(HDC hdc, image* ig, int destX, int destY, float scale)
{
	ig->stretchRender(hdc, GetRelativeX(destX), GetRelativeY(destY), scale);
}

void CameraManager::AlphaRender(HDC hdc, image* ig, int destX, int destY, BYTE alpha)
{
	ig->alphaRender(hdc, GetRelativeX(destX), GetRelativeY(destY), alpha);
}

void CameraManager::Rectangle(HDC hdc, RECT rc)
{
	::Rectangle(hdc, GetRelativeX(rc.left), GetRelativeY(rc.top), GetRelativeX(rc.right), GetRelativeY(rc.bottom));
}

void CameraManager::RectangleMake(HDC hdc, int left, int top, int width, int height)
{
	::RectangleMake(hdc, GetRelativeX(left), GetRelativeY(top), width, height);
}

void CameraManager::TextDraw(HDC hdc, int destX, int destY, LPCSTR lpstring, int c)
{
	TextOut(hdc, GetRelativeX(destX), GetRelativeY(destY), lpstring, c);
}

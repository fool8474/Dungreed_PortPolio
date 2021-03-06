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
	_shakeCycleTimer = 0;
	_shakeCycle = 0;

	// ZOOM //
	_zoomTargetX = 0;
	_zoomTargetY = 0; 
	// zoom 미사용

	_cameraRect = RectMake(_pivotX - disX, _pivotY - disY, WINSIZEX, WINSIZEY);

	return S_OK;
}

void CameraManager::update()
{
	Shaker();
}

/// <summary>
/// x, y로 피벗을 움직이도록 하고, 이때 Camera가 제한을 넘지 못하도록 한다.
/// </summary>
void CameraManager::MovePivot(float x, float y)
{
	_pivotX = x;
	_pivotY = y;
	_cameraRect = RectMake(_pivotX - _initDistanceX, _pivotY - _initDistanceY, WINSIZEX, WINSIZEY);
	//_pivotX - _initDistanceX -> _initDistance = Pivot이 화면에서 표시될 위치, _pivotX = 현재 따라갈 X의 좌표
	//_pivotX - _initDistanceX = _INITDISTANCE = WINSIZEX/2 , _PIVOTX = WINSIZEX/2 + 100
	
	if (_cameraRect.left <= _minX) // LEFT가 최소가 되면
	{
		_cameraRect.left = _minX; // 카메라 렉트를 최소에 맞춰준다
		_cameraRect.right = _minX + WINSIZEX;
	}
	if (_cameraRect.right >= _maxX) // RIGHT가 최대가 되면
	{
		_cameraRect.right = _maxX; // 카메라 렉트를 최대에 맞춰준다
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

	// SHAKE 관련
	OffsetRect(&_cameraRect, _shakeX, _shakeY);
}


/// <summary>
/// 카메라를 부드럽게 움직이게 한다.
/// </summary>
void CameraManager::MovePivotLerp(float x, float y, float lerpSpeed)
{

	MovePivot(
		(x - _pivotX) / lerpSpeed + _pivotX,
		(y - _pivotY) / lerpSpeed + _pivotY // lerp 속도에 맞춰 천천히 움직이도록 한다.
	);
}

/// <summary>
/// 일정한 속도로 카메라를 움직이도록 한다.
/// </summary>
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

/// <summary>
/// 흔들림 지수를 정해준다.
/// </summary>
void CameraManager::Shake(float shakePowerX, float shakePowerY, int shakeTime, int shakeCycle)
{
	_shakePowerX = shakePowerX;
	_shakePowerY = shakePowerY;
	_shakeTimer = shakeTime;
	_shakeCycleTimer = _shakeCycle = shakeCycle;
}

/// <summary>
/// 줌인 줌아웃을 실시한다 (버그)
/// </summary>
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

/// <summary>
/// 매프레임 흔들림 적용
/// </summary>
void CameraManager::Shaker()
{
	if (_shakeTimer > 0)
	{
		// _shakeTimer는 쉐이크가 일어날 시간
		// _shakeCycleTimer는 n프레임마다 한번씩 쉐이크가 일어나게
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

		else // SHAKE를 주기마다 자연스럽게 이동하도록
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

/// <summary>
/// 렌더 관련
/// </summary>

void CameraManager::LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, GetRelativeX(startX), GetRelativeY(startY), NULL);
	LineTo(hdc, GetRelativeX(endX), GetRelativeY(endY));
}

void CameraManager::Render(HDC hdc, image* ig, int destX, int destY, float angle)
{
	ig->render(hdc, GetRelativeX(destX), GetRelativeY(destY), angle);
}

void CameraManager::FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float angle)
{
	ig->frameRender(hdc, GetRelativeX(destX), GetRelativeY(destY), frameX, frameY ,angle);
}

void CameraManager::StretchRender(HDC hdc, image* ig, int destX, int destY, float scaleX, float scaleY, float angle)
{
	ig->stretchRender(hdc, GetRelativeX(destX), GetRelativeY(destY), scaleX, scaleY, angle);
}

void CameraManager::StretchAlphaRender(HDC hdc, image * ig, int destX, int destY, float scaleX, float scaleY, BYTE alpha, float angle)
{
	ig->stretchAlphaRender(hdc, GetRelativeX(destX), GetRelativeY(destY), scaleX, scaleY, alpha, angle);
}

void CameraManager::FrameStretchRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float scaleX, float scaleY, float angle)
{
	ig->frameStretchRender(hdc, GetRelativeX(destX), GetRelativeY(destY), frameX, frameY, scaleX, scaleY ,angle);
}

void CameraManager::FrameStretchAlphaRender(HDC hdc, image * ig, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle)
{
	ig->frameStretchAlphaRender(hdc, GetRelativeX(destX), GetRelativeY(destY), currentFrameX, currentFrameY, scaleX, scaleY, alpha,angle);
}

void CameraManager::AlphaRender(HDC hdc, image* ig, int destX, int destY, BYTE alpha, float angle)
{
	ig->alphaRender(hdc, GetRelativeX(destX), GetRelativeY(destY), alpha, angle);
}

void CameraManager::alphaRender(HDC hdc, image* ig, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, float angle)
{
	ig->alphaRender(hdc, GetRelativeX(destX), GetRelativeY(destY), sourX,sourY,sourWidth,sourHeight , alpha, angle);
}

void CameraManager::FrameAlphaRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, BYTE alpha , float angle)
{
	ig->frameAlphaRender(hdc, GetRelativeX(destX), GetRelativeY(destY), frameX, frameY, alpha, angle);
}

void CameraManager::Rectangle(HDC hdc, RECT rc)
{
	::Rectangle(hdc, GetRelativeX(rc.left), GetRelativeY(rc.top), GetRelativeX(rc.right), GetRelativeY(rc.bottom));
}

void CameraManager::RectangleMake(HDC hdc, int left, int top, int width, int height)
{
	::RectangleMake(hdc, GetRelativeX(left), GetRelativeY(top), width, height);
}

void CameraManager::TextDraw(HDC hdc, int destX, int destY, LPCSTR lpstring, int c, int r, int g, int b)
{
	
	HFONT OldFont, hFont;
	hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
	SetTextColor(hdc, RGB(r,g,b));
	OldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, GetRelativeX(destX), GetRelativeY(destY), lpstring, c);

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);

}

void CameraManager::TextInit(HDC hdc, float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort, COLORREF color)
{
	HFONT hFont;
	HFONT OldFont;

	RECT rc = RectMake(GetRelativeX(x), GetRelativeY(y), xSize, ySize);

	string fontName = "";
	POINT framePt;
	switch (font) // 폰트 종류에 따라
	{
	case PIX:
		switch (size) // 폰트 크기에 따라
		{
		case WS_BIG:
			hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
			break;
		case WS_MIDDLE:
			hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
			break;
		case WS_SMALL:
			hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
			break;
		case WS_SMALLEST:
			hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
			break;
		case WS_MIDDLESMALL:
			hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
		} // 폰트를 결정
		break;
	}
	
	float curX = GetRelativeX(x);
	SetTextColor(hdc, color);
	OldFont = (HFONT)SelectObject(hdc, hFont);
	
	
	
	switch (sort) // 정렬 방식에 따라
	{
	case WSORT_LEFT: // 좌측 정렬
		DrawText(hdc, text.substr(0, text.length()).c_str(), -1, &rc, DT_LEFT | DT_WORDBREAK); // 좌측정렬 & 멀티라인
		break;
	
	case WSORT_MIDDLE: // 가운데 정렬
		DrawText(hdc, text.substr(0, text.length()).c_str(), -1, &rc, DT_CENTER | DT_WORDBREAK); // 가운데정렬 & 멀티라인
		break;
	
	case WSORT_RIGHT: // 우측 정렬
		DrawText(hdc, text.substr(0, text.length()).c_str(), -1, &rc, DT_RIGHT | DT_WORDBREAK); // 우측정렬 & 멀티라인
		break;
	}
	
	
	
	SelectObject(hdc, OldFont);
	DeleteObject(hFont);
	

	
}


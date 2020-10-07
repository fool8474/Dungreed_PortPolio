#pragma once
#include "singletonBase.h"
#include "image.h"

class CameraManager : public singletonBase<CameraManager>
{
private:

	// CAMERAFOLLOW //
	RECT	_cameraRect;		// ���� ī�޶��� ��ǥ (RelativeX, Y�� ���Ҷ� ���)
	float	_pivotX;			// ���� ī�޶� �߽����� ����ִ� PIVOT X
	float	_pivotY;			// ���� ī�޶� �߽����� ����ִ� PIVOT Y
	float	_maxX;				// ī�޶� �ִ��� ���󰡴� �Ÿ� X
	float	_maxY;				// ī�޶� �ִ��� ���󰡴� �Ÿ� Y
	float	_minX;				// ī�޶� �ּ��� ���󰡴� �Ÿ� X
	float	_minY;				// ī�޶� �ּ��� ���󰡴� �Ÿ� X
	float	_distanceX;
	float	_distanceY;
	float	_initDistanceX;		// ���� WINSIZEX/2�� ��� (pivot ������ ��ġ)
	float	_initDistanceY;		// ���� WINSIZEY/2�� ��� (pivot ������ ��ġ)

	// CAMERASHAKE //
	float	_shakeX;			// ����ũ X
	float	_shakeY;			// ����ũ Y
	float	_tempShakeX;		// ����ũ ������ X
	float	_tempShakeY;		// ����ũ ������ Y
	float	_shakePowerX;		// ��� ���� X
	float	_shakePowerY;		// ��� ���� Y
	int		_shakeTimer;		// ��� �ð�
	int		_shakeCycleTimer;	// ��� ����Ŭ Ÿ�̸�
	int		_shakeCycle;		// ��� ����Ŭ
	
	void Shaker();

	// ZOOM //
	float	_zoomTargetX;		// ���� ��ġ�� �� ��� X
	float	_zoomTargetY;		// ���� ��ġ�� �� ��� Y

public:
	CameraManager() {
		_cameraRect = { 0,0,0,0 };
		_pivotX = 0.f;
		_pivotY = 0.f;
		_maxX = 0.f;
		_maxY = 0.f;
		_minX = 0.f;
		_minY = 0.f;
		_distanceX = 0.f;
		_distanceY = 0.f;
		_initDistanceX = 0.f;
		_initDistanceY = 0.f;
	}
	~CameraManager() {}

	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY);
	void update();

	// RENDER //
	void Render(HDC hdc, image* ig, int destX, int destY);
	void AlphaRender(HDC hdc, image * ig, int destX, int destY, BYTE alpha);
	void StretchRender(HDC hdc, image* ig, int destX, int destY, float scaleX, float scaleY);
	void StretchAlphaRender(HDC hdc,image* ig, int destX, int destY, float scaleX, float scaleY, BYTE alpha);
	void FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float angle = 0);
	void FrameAlphaRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, BYTE alpha, float angle = 0 );
	void FrameStretchRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float scaleX, float scaleY, float angle = 0);
	void FrameStretchAlphaRender(HDC hdc, image* ig, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle = 0);
	void Rectangle(HDC hdc, RECT rc);
	void RectangleMake(HDC hdc, int left, int top, int width, int height);
	void TextDraw(HDC hdc, int destX, int destY, LPCSTR lpstring, int c, int r = 0, int g = 0, int b = 0);
	
	// ��� // 
	void MovePivot(float x, float y);
	void MovePivotLerp(float x, float y, float lerpSpeed = 10.f);
	void MovePivotRegular(float x, float y, float moveSpeed);
	void Shake(float shakePowerX, float shakePowerY, int shakeTime, int shakeCycle = 0);
	void ZoomInOut(HDC hdc, int destX, int destY, int sourX, int sourY, float scale);
	
	// ���Ǽ� //
	float	GetRelativeX(float x)				{ return x - _cameraRect.left; }
	float	GetRelativeY(float y)				{ return y - _cameraRect.top; }
	float	GetAbsoluteX(float x)				{ return x + _cameraRect.left; }
	float	GetAbsoluteY(float y)				{ return y + _cameraRect.top; }
	POINT	GetAbsolutePoint(long x, long y)	{ return POINT{ x + _cameraRect.left, y + _cameraRect.top }; }
	
	// GETSET //
	float	GetPivotX()		{ return _pivotX; }
	float	GetPivotY()		{ return _pivotY; }
	float	GetDistanceX()	{ return _distanceX; }
	float	GetDistanceY()	{ return _distanceY; }
	RECT	GetRect()		{ return _cameraRect; }
};
#pragma once
#include "UIFrame.h"

/// <summary>
/// UIImage�� �̹��� ǥ���� Ưȭ�� UI�̴�.
/// </summary>
class UIImage : public UIFrame // UIFrame�� ��ӹ޾� UIFrame�� ����� ��� �̿��� �� �ִ�.
{
private:
	bool	_useFrameImage;	// FrameImage ��� ����
	int		_frameX;		// FrameX
	int		_frameY;		// FrameY
	int		_alpha;			// alpha
	int		_frameTimer;	// timer

public:
	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY, float scaleX = 1, float scaleY = 1, int alpha = 255);
	virtual void update();
	void Animation();
	virtual void render(HDC hdc);
	
	int GetAlpha() { return _alpha; }

	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
	void SetAlpha(int alpha) { _alpha = alpha; }
};

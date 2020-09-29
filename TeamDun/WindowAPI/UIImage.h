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

	// �ȳ��ϼ���
public:
	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY, float scaleX = 1, float scaleY = 1);
	virtual void render(HDC hdc);

	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
};

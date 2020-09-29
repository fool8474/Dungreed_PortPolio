#pragma once
#include "UIFrame.h"
class UIProgressBar : public UIFrame
{
private:
	image*	_backImg;
	float	_fillX;
	float	_initX;
	float	_fillPercent;
	float   _imgFillX;

public:
	virtual HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, string imageName2, float scaleX = 1.0f, float scaleY = 1.0f);
	virtual void render(HDC hdc);
	virtual void update();
	void FillCheck(float initX, float fillX);
};


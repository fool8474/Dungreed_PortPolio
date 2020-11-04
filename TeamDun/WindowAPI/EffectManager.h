#pragma once
#include "singletonBase.h"
#include "Effect.h"
#include "cameraText.h"
class EffectManager : public singletonBase<EffectManager>
{
private :
	vector<Effect*> _vEffect;
	vector<cameraText*>_vCameraText;

public :
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	Effect* AddEffect(float x, float y, string imgName, int animSpeed, int frameX = 0, int frameY = 0, bool isLoop = false, int alpha = 255, float angle = 0, float scaleX = 1, float scaleY = 1, bool isAlpha = false, bool useCamera = false, bool isFirstViewing = true, string effectSound = "", float damage = 0, bool isCenter = false, bool isEffectAngle = true);
	cameraText* AddCameraText(float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort = WORDSORT::WSORT_LEFT, COLORREF color = RGB(255, 255, 255));
	void DeleteEffect();
	void DeleteText();
	vector<Effect*>& GetVEffect() { return _vEffect; }
	vector<cameraText*>& GetVCamerText() { return _vCameraText; }
	void HitEffect();
};


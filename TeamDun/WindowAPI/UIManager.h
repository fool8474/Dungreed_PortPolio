#pragma once
#include "singletonBase.h"
#include "UIText.h"
#include "UIImage.h"
#include "UIScroll.h" 

/// <summary>
/// UI��ü�� �����ϴ� �Ŵ����̴�.
/// </summary>
class UIManager : public singletonBase<UIManager>
{

public :
	vector<UIImage*>	_vItemToBag;	// ���ÿ�
	UIFrame*			_GameFrame;		// ���ÿ�
	UIFrame*			_PlayerFrame;	// ���ÿ�

public :
	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();

	UIFrame* GetGameFrame()		{ return _GameFrame; }
	UIFrame* GetPlayerFrame()	{ return _PlayerFrame; }
};


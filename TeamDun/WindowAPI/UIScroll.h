#pragma once
#include "UIFrame.h"

/// <summary>
/// UIScroll�� ��ũ�� �ٿ� Ưȭ�� UI�̴�.
/// </summary>
class UIScroll : public UIFrame // UIFrame�� ��ӹ޾� UIFrame�� ��ɵ鵵 ��� �̿��� �� �ִ�.
{
private :
	UIFrame*	_target;		// Scroll�� ������ Ÿ�� UI
	float		_scrollPercent;	// Scroll�� �󸶸�ŭ �����Դ��� ����
	bool		_isVertical;	// Scroll�� ���θ�

	void CalculateScrollBarPercent();
	
public :

	virtual	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName);
	virtual void update();

	UIFrame* GetTarget() { return _target; }
	float GetScrollPercent() { return _scrollPercent; }

	void SetTarget(UIFrame* target) { _target = target; }
	void SetScroll(float percent) { _scrollPercent = percent; }
	void SetIsVertical(bool vertical) { _isVertical = vertical; }
	void MoveScrollBar();
};


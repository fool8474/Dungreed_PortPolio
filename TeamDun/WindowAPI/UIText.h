#pragma once
#include "UIManager.h"
#include "UIFrame.h"

// ������ ũ��
enum WORDSIZE
{
	WS_BIG, WS_MIDDLE, WS_SMALL, WS_SMALLEST
};

// ���ڰ� �ִϸ��̼����� ������ �ӵ�
enum WORDANIMATIONSPEED
{
	WAS_FAST, WAS_MIDDLE, WAS_SLOW
};

// ���ڰ� � ������ �ϰ� �ִ���
enum WORDSORT
{
	WSORT_LEFT, WSORT_MIDDLE, WSORT_RIGHT
};

// ��Ʈ ����
enum FONT
{
	PIX
};


// ttf ���� �׽�Ʈ �� ���� ����
/// <summary>
/// UIText�� UIFrame�� ����Ͽ� UIFrame�� ��ɵ� ����ϸ�, Text�� ���� ��� ���� �����Ѵ�.
/// </summary>
class UIText : public UIFrame 
{
private:
	string				_text;					// �� TextUI�� ����
	WORDSIZE			_wordSize;				// �� TextUI�� ũ��
	WORDSORT			_wordSort;				// �� TextUI�� ���� ���
	FONT				_font;					// �� TextUI�� ����� ��Ʈ
	bool				_isAnimation;			// �� TextUI�� Animation�� ����ϴ���
	WORDANIMATIONSPEED	_animationSpeed;		// �� TextUI�� Animation �ӵ�
	COLORREF			_color;					// �� TextUI�� ��
	int					_cntPos;				// ���� ������� ��ġ 
	int					_animationTimer;		// �ִϸ��̼� Ÿ�̸�
	int					_initAnimationTimer;	// �ʱ� �ִϸ��̼� Ÿ�̸�
public:
	string GetText() { return _text; }
	bool GetIsAnimation() { return _isAnimation; }
	WORDSIZE GetWordSize() { return _wordSize; }

	void SetText(string text) { _text = text; }
	
	virtual void init(string name, float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort = WORDSORT::WSORT_LEFT, COLORREF color = RGB(255,255,255), bool isAnimation = false, WORDANIMATIONSPEED speed = WORDANIMATIONSPEED::WAS_MIDDLE);
	virtual void render(HDC hdc);
};

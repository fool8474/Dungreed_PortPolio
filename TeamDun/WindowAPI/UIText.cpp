#include "stdafx.h"
#include "UIText.h"

/// <summary>
/// �ʱ�ȭ
/// </summary>
/// <param name="text">�ؽ�Ʈ ����</param>
/// <param name="font">�۾�ü</param>
/// <param name="size">ũ��</param>
/// <param name="sort">���� ���</param>
/// <param name="space">�ڰ�</param>
/// <param name="isAnimation">�ִϸ��̼� ����</param>
/// <param name="speed">�ִϸ��̼� �ӵ�</param>
void UIText::init(string name, float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort, COLORREF color, bool isAnimation, WORDANIMATIONSPEED speed)
{
	UIFrame::init(name, x, y, xSize, ySize, "");
	_text = text;
	_wordSize = size;
	_wordSort = sort;
	_font = font;
	_isAnimation = isAnimation;
	_animationSpeed = speed;
	_color = color;
	
	switch (speed) // �ִϸ��̼� �ӵ��� ���� �ִϸ��̼� Ÿ�̸� ����
	{
	case WORDANIMATIONSPEED::WAS_FAST:
		_initAnimationTimer = _animationTimer = 1;
		break;

	case WORDANIMATIONSPEED::WAS_MIDDLE:
		_initAnimationTimer = _animationTimer = 3;
		break;

	case WORDANIMATIONSPEED::WAS_SLOW:
		_initAnimationTimer = _animationTimer = 5;
		break;
	}
}

void UIText::render(HDC hdc)
{

	HFONT hFont;
	HFONT OldFont;

	if (_isViewing) // ���̴� ���¶��
	{
		string fontName = "";
		POINT framePt;
		switch (_font) // ��Ʈ ������ ����
		{
		case PIX:
			switch (_wordSize) // ��Ʈ ũ�⿡ ����
			{
			case WS_BIG: 
				hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo�ձٸ�"); 
				break;
			case WS_MIDDLE: 
				hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo�ձٸ�"); 
				break;
			case WS_SMALL: 
				hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo�ձٸ�"); 
				break;
			case WS_SMALLEST:
				hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo�ձٸ�");
			} // ��Ʈ�� ����
			break;
		}

		float curX = _x;
		SetTextColor(hdc, _color);
		OldFont = (HFONT)SelectObject(hdc, hFont);

		if (!_isAnimation) _cntPos = _text.length(); // �ִϸ��̼��� �ƴϸ� ������ ��� ��µǰ�

		switch (_wordSort) // ���� ��Ŀ� ����
		{
		case WSORT_LEFT: // ���� ����
			DrawText(hdc, _text.substr(0, _cntPos).c_str(), -1, &_interactRect, DT_LEFT | DT_WORDBREAK ); // �������� & ��Ƽ����
			break;

		case WSORT_MIDDLE: // ��� ����
			DrawText(hdc, _text.substr(0, _cntPos).c_str(), -1, &_interactRect, DT_CENTER | DT_WORDBREAK); // ������� & ��Ƽ����
			break;

		case WSORT_RIGHT: // ���� ����
			DrawText(hdc, _text.substr(0, _cntPos).c_str(), -1, &_interactRect, DT_RIGHT | DT_WORDBREAK); // �������� & ��Ƽ����
			break;
		}

		if (_cntPos < _text.length()) // �ִϸ��̼��̸� ��� ��ġ�� ���� ���δ�.
		{
			_animationTimer--;
			if (_animationTimer == 0) // �ִϸ��̼� �ӵ��� ���� �ٸ� Ÿ�̸�
			{
				_animationTimer = _initAnimationTimer;
				_cntPos++;
			}
		}

		SelectObject(hdc, OldFont);
		DeleteObject(hFont);

		if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);
	}
}

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
void UIText::init(string name, float x, float y, string text, FONT font, WORDSIZE size, WORDSORT sort, int space, bool isAnimation, WORDANIMATIONSPEED speed)
{
	UIFrame::init(name, x, y, 0, 0, "");
	_text = text;
	_wordSize = size;
	_wordSort = sort;
	_font = font;
	_isAnimation = isAnimation;
	_animationSpeed = speed;
	_space = space;
}

void UIText::render(HDC hdc)
{
	if (_isViewing) // ���̴� ���¶��
	{
		string fontName = "";
		POINT framePt;
		switch (_font) // ��Ʈ ������ ����
		{
		case PIX:
			switch (_wordSize) // ��Ʈ ũ�⿡ ����
			{
			case WS_BIG: fontName = "Font_Word_Pix_Big"; break;
			case WS_MIDDLE: fontName = "Font_Word_Pix_Middle"; break;
			case WS_SMALL: fontName = "Font_Word_Pix_Small"; break;
			} // ������ �̹����� �����Ѵ�
			break;
		}

		float curX = _x;

		switch (_wordSort) // ���� ��Ŀ� ����
		{
		case WSORT_LEFT: // ���� ����
			for (int i = 0; i < _text.length(); i++)
			{
				framePt = GetWordFramePosition(_text[i]); // ���� char�� ���� �ش� ���ڿ� �´� �̹����� �������� �޾ƿ´�.
				IMAGEMANAGER->findImage(fontName)->frameRender(hdc, curX, _y, framePt.x, framePt.y); // �޾ƿ� �����Ӱ� ���ص� �̹����� ������� �̹����� �׸���
				curX += IMAGEMANAGER->findImage(fontName)->getFrameWidth() - _space; // ���� ���ڸ� ����ϱ� ���� X��ġ�� �ڰ��� ���� ũ�⿡ ���߾� �����Ѵ�.
			}
			break;

		case WSORT_MIDDLE: // �̱���
			break;

		case WSORT_RIGHT: // ���� ����
			for (int i = _text.length()-1; i >= 0; i--)
			{
				framePt = GetWordFramePosition(_text[i]);
				IMAGEMANAGER->findImage(fontName)->frameRender(hdc, curX, _y, framePt.x, framePt.y);
				curX -= IMAGEMANAGER->findImage(fontName)->getFrameWidth() + _space;
			}
			break;
		}

		if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);
	}
}

/// <summary>
/// ���� char�� �´� �̹����� ������ ��ǥ�� ����
/// </summary>
POINT UIText::GetWordFramePosition(char ch)
{
	POINT pt;

	if (isalpha(ch)) // ���ĺ��̶��
	{
		ch = toupper(ch); // �빮��ȭ ��Ų��. 
	}

	switch (ch)
	{
	case 'A': pt = { 0,0 }; break;
	case 'B': pt = { 1,0 }; break;
	case 'C': pt = { 2,0 }; break;
	case 'D': pt = { 3,0 }; break;
	case 'E': pt = { 4,0 }; break;
	case 'F': pt = { 5,0 }; break;
	case 'G': pt = { 6,0 }; break;
	case 'H': pt = { 7,0 }; break;
	case 'I': pt = { 8,0 }; break;
	case 'J': pt = { 9,0 }; break;
	case 'K': pt = { 10,0 }; break;
	case 'L': pt = { 11,0 }; break;
	case 'M': pt = { 12,0 }; break;
	case 'N': pt = { 13,0 }; break;
	case 'O': pt = { 14,0 }; break;
	case 'P': pt = { 15,0 }; break;
	case 'Q': pt = { 16,0 }; break;
	case 'R': pt = { 17,0 }; break;
	case 'S': pt = { 18,0 }; break;
	case 'T': pt = { 19,0 }; break;
	case 'U': pt = { 20,0 }; break;
	case 'V': pt = { 21,0 }; break;
	case 'W': pt = { 22,0 }; break;
	case 'X': pt = { 23,0 }; break;
	case 'Y': pt = { 24,0 }; break;
	case 'Z': pt = { 25,0 }; break;
	case '1': pt = { 0,1 }; break;
	case '2': pt = { 1,1 }; break;
	case '3': pt = { 2,1 }; break;
	case '4': pt = { 3,1 }; break;
	case '5': pt = { 4,1 }; break;
	case '6': pt = { 5,1 }; break;
	case '7': pt = { 6,1 }; break;
	case '8': pt = { 7,1 }; break;
	case '9': pt = { 8,1 }; break;
	case '0': pt = { 9,1 }; break;
	case '(': pt = { 0,2 }; break;
	case ')': pt = { 1,2 }; break;
	case '%': pt = { 2,2 }; break;
	case '+': pt = { 3,2 }; break;
	case '-': pt = { 4,2 }; break;
	case '=': pt = { 5,2 }; break;
	case '&': pt = { 6,2 }; break;
	case '$': pt = { 7,2 }; break;
	case '/': pt = { 8,2 }; break;
	case '#': pt = { 12,2 }; break;
	case '@': pt = { 13,2 }; break;
	case '?': pt = { 14,2 }; break;
	case '!': pt = { 15,2 }; break;
	case '<': pt = { 16,2 }; break;
	case '>': pt = { 17,2 }; break;
	case ':': pt = { 18,2 }; break;
	case ';': pt = { 19,2 }; break;
	default: pt = { 20,1 }; break;
	}

	return pt;
}

#include "stdafx.h"
#include "UIManager.h"

/// <summary>
/// ���ӿ��� ���� UI���� �ʱ�ȭ��Ų��. ���׸���� ���� �������̱� ������ _GameFrame �������� �ΰ� ������ UIManager�� ���Ӱ� Init�Ѵ�.
/// </summary>
HRESULT UIManager::init()
{
	_GameFrame = new UIFrame();
	_GameFrame->init("mainFrame", 0, 0, 1920, 1080, "");
	_GameFrame->SetIsViewing(true);

	// TEXT �׽�Ʈ��
	UIText* text;

	/*text = new UIText();
	text->init("testText", 600, 500, 300, 50, 
		"�ؽ�Ʈ �׽�Ʈ���Դϴ�. ���ڴ� SMALLEST, ������ ����, ���� ���, �ִϸ��̼��� �����Դϴ�.", 
		FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(255,255,255), true, WORDANIMATIONSPEED::WAS_FAST);
	_GameFrame->AddFrame(text);

	text = new UIText();
	text->init("testText", 600, 550, 300, 50, 
		"�ؽ�Ʈ �׽�Ʈ���Դϴ�. ���ڴ� SMALLEST, ������ ���, ���� ��Ȳ��, �ִϸ��̼��� �߰��Դϴ�.", 
		FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE, RGB(243, 151, 101), true, WORDANIMATIONSPEED::WAS_MIDDLE);
	_GameFrame->AddFrame(text);

	text = new UIText();
	text->init("testText", 600, 600, 300, 50, 
		"�ؽ�Ʈ �׽�Ʈ���Դϴ�. ���ڴ� SMALLEST, ������ ������, ���� �����, �ִϸ��̼��� �����Դϴ�.", 
		FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_RIGHT, RGB(200, 191, 231), true, WORDANIMATIONSPEED::WAS_SLOW);
	_GameFrame->AddFrame(text);*/

	return S_OK;
}

/// <summary>
/// UIManager�� ��� UI���� ������Ʈ�Ѵ�.
/// </summary>
void UIManager::update()
{
	_GameFrame->update();
}

/// <summary>
/// UIManager�� ��� UI���� �����Ѵ�.
/// </summary>
void UIManager::render(HDC hdc)
{
	_GameFrame->render(hdc);
}

/// <summary>
/// UIManager�� ��� UI���� �������Ѵ�.
/// </summary>
void UIManager::release()
{
	_GameFrame->release();
}
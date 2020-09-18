#include "stdafx.h"
#include "UIManager.h"

/// <summary>
/// ���ӿ��� ���� UI���� �ʱ�ȭ��Ų��. ���׸���� ���� �������̱� ������ _GameFrame �������� �ΰ� ������ UIManager�� ���Ӱ� Init�Ѵ�.
/// </summary>
HRESULT UIManager::init()
{
	// ��� ���� (�Ĵ¸��࿡�� ���� UI [�̹����� �����Ͱ� ��� ������ �ȵ�, � ������ �ڵ带 ��� �ϴ����� Ȯ��])

	// ���� ��ü�� ���� UI (����)
	_GameFrame = new UIFrame();
	_GameFrame->init("mainFrame", 0, 0, 1920, 1080, "");
	_GameFrame->SetIsViewing(true);

	// ���� UI Image
	UIImage* back = new UIImage();
	back->init("mainFrame_backpack", 70, WINSIZEY - 160, IMAGEMANAGER->findImage("UI_Bag")->getWidth(), IMAGEMANAGER->findImage("UI_Bag")->getHeight(), "UI_Bag", false, 0, 0);
	back->SetIsViewing(true);

	// Stage ǥ�ÿ� UI Text
	UIText* stage = new UIText();
	stage->init("stage", 700, 20, "STAGE 1", FONT::PIX, WORDSIZE::WS_BIG);
	
	// ���� �̵� �Ÿ� ǥ�ÿ� UI Text
	UIText* m = new UIText();
	m->init("m", 1200, 20, "0m", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
	
	// ���� �������� �ڽ����� ����� ��������, �̵� �Ÿ��� �ִ´�.
	_GameFrame->AddFrame(back);	
	_GameFrame->AddFrame(stage);
	_GameFrame->AddFrame(m);

	// �÷��̾� ������ Ʋ
	_PlayerFrame = new UIFrame();
	_PlayerFrame->init("playerFrame", 200, 200, IMAGEMANAGER->findImage("UI_Menu")->getWidth(), IMAGEMANAGER->findImage("UI_Menu")->getHeight(), "UI_Menu");
	_PlayerFrame->SetIsMoveToDrag(true);

	// �κ��丮
	UIFrame* inven = new UIFrame();
	inven->init("playerFrame_inventory", 20, 44, IMAGEMANAGER->findImage("UI_Inven")->getWidth(), IMAGEMANAGER->findImage("UI_Inven")->getHeight(), "UI_Inven");
	inven->SetIsViewing(false);
	
	// ����
	UIFrame* craft = new UIFrame();
	craft->init("playerFrame_craft", 19, 37, IMAGEMANAGER->findImage("UI_Craft")->getWidth(), IMAGEMANAGER->findImage("UI_Craft")->getHeight(), "UI_Craft");
	craft->SetIsViewing(false);
	craft->SetUseOutsideLimit(true);
	
	// �� ������ Ʋ
	UIFrame* money = new UIFrame();
	money->init("playerFrame_money", 1300, 0, IMAGEMANAGER->findImage("UI_Money")->getWidth(), IMAGEMANAGER->findImage("UI_Money")->getHeight(), "UI_Money");
	money->SetIsViewing(true);
	
	// �÷��̾� �������� �ȿ� �κ��丮�� ����, ���� �ִ´�. ���� �ٸ� cpp ���Ͽ��� �̵��� �ȿ� �ڽ����� ������ ��� �̹���, �ؽ�Ʈ ���� ���� �ȴ�.
	_PlayerFrame->AddFrame(inven);
	_PlayerFrame->AddFrame(craft);
	_PlayerFrame->AddFrame(money);
	
	// �� ��Ȳ �ؽ�Ʈ
	UIText* moneyText = new UIText();
	moneyText->init("moneyText", IMAGEMANAGER->findImage("UI_Money")->getWidth() - 65, IMAGEMANAGER->findImage("UI_Money")->getHeight() - 55, "0", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT, -6);
	moneyText->SetIsViewing(true);
	money->AddFrame(moneyText); // �� ������ Ʋ�� �ڽ����� ���� �� �ؽ�Ʈ�� �ִ´�.

	return S_OK;
}

/// <summary>
/// UIManager�� ��� UI���� ������Ʈ�Ѵ�.
/// </summary>
void UIManager::update()
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->update();
	}

	_GameFrame->update();
	_PlayerFrame->update();
}

/// <summary>
/// UIManager�� ��� UI���� �����Ѵ�.
/// </summary>
void UIManager::render(HDC hdc)
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->render(hdc);
	}

	_GameFrame->render(hdc);
	_PlayerFrame->render(hdc);
}

/// <summary>
/// UIManager�� ��� UI���� �������Ѵ�.
/// </summary>
void UIManager::release()
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->release();
	}

	_GameFrame->release();
	_PlayerFrame->release();
}
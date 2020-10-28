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
}
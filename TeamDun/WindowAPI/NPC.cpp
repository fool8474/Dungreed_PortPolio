#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isInteracting = false;
	_isActivating = false;

	return S_OK;
}

/// <summary>
/// DATAMANAGER���� �ҷ��� �� init ������ �͵鸸 init�Ѵ�.
/// </summary>
void NPC::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void NPC::release()
{
}

void NPC::update()
{
	CollisionInteraction();
	PressActivateKey();
	Animation();
}

void NPC::CollisionInteraction()
{
	_interactRect = RectMake(_x - 50, _y - 50, _vImages[_useImage]->getFrameWidth() + 100, _vImages[_useImage]->getFrameHeight() + 100);

	RECT temp;
	if (IntersectRect(&temp, &_interactRect, &ENTITYMANAGER->getPlayer()->GetBody()))
	{
		_isInteracting = true;
	}

	else
	{
		_isInteracting = false;
	}
}

/// <summary>
/// Ű�� ���� ��ȣ�ۿ��� �����Ѵ�.
/// </summary>
void NPC::PressActivateKey()
{
	if (_isInteracting && INPUT->GetKeyDown('F'))
	{
		ShowConversation();
	}
}

/// <summary>
/// ��ȭ�� On/Off�Ѵ�.
/// </summary>
void NPC::ShowConversation()
{
	if (_useConv && !_isActivating)
	{
		SetConvUI();
		_convFrame->ToggleIsViewing();

		if(_useSelect) _selectFrame->ToggleIsViewing();
	}

	else
	{
		Activate();
	}
}

/// <summary>
/// ��ȭâ�� �ؽ�Ʈ ���빰���� �����Ѵ�.
/// </summary>
void NPC::SetConvUI()
{
	dynamic_cast<UIText*>(_convFrame->GetChild("name"))->SetText(_npcName);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[RANDOM->range((int)_vConvTexts.size())]);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetCntPos(0);

	if (_useSelect)
	{
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected1")->GetChild("text"))->SetText(_vSelectTexts[0]);
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected2")->GetChild("text"))->SetText(_vSelectTexts[1]);
		_selectFrame->GetChild("selected1")->SetImage(nullptr);
		_selectFrame->GetChild("selected2")->SetImage(nullptr);
	}
}

/// <summary>
/// ��ȭ�� �����Ѵ�. �̶� �������� ������ �Ϳ� ���� ������ �߰��ȴ�.
/// </summary>
void NPC::Conversation()
{
	// ���� ���� �ʿ�
}

/// <summary>
/// �������� ��ȣ�ۿ��� ����
/// </summary>
void NPC::Activate()
{
	// ���� ���� �ʿ�
}

void NPC::render(HDC hdc)
{
	Object::render(hdc);

	if (_isInteracting)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void NPC::Animation()
{
	_frameTimer++;

	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX >= _vImages[_useImage]->getMaxFrameX()) _frameX = 0;
	}
}

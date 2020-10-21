#include "stdafx.h"
#include "Boutique.h"

HRESULT Boutique::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_npcName = "��ν�";
	_vConvTexts = vector<string>
	{
		"�� �������� �غ�� �Ǽ̽��ϱ�?",
	};
	_vSelectTexts = vector<string>
	{
		"�ǻ��",
		"�ƹ��͵�"
	};

	_useConv = true;
	_useSelect = true;
	_isUsing = false;
	_isOpen = false;

	return S_OK;
}

void Boutique::update()
{
	NPC::update();
	if (_selectFrame->GetIsViewing() && !_isUsing)
	{
		Conversation();
	}
}

void Boutique::Conversation()
{
	
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{

		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			_isOpen = true;
		}
	}
	else _selectFrame->GetChild("selected1")->SetImage(nullptr);

	if (PtInRect(&_selectFrame->GetChild("selected2")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected2")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			_isUsing = false;
		}
	}
	else _selectFrame->GetChild("selected2")->SetImage(nullptr);

	if (_isOpen)
	{
		_isOpen = false;
		Boutique::Activate();
	}
}

void Boutique::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void Boutique::release()
{
	NPC::release();
}

void Boutique::render(HDC hdc)
{
	NPC::render(hdc);
}


void Boutique::Activate()
{
	_isActivating = !_isActivating;

	UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->ToggleIsViewing();
	_isUsing = UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetIsViewing();

	for (int i = 0; i < 13; i++)
	{
		UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
	}
}

void Boutique::Animation()
{
	NPC::Animation();
}
#include "stdafx.h"
#include "HungryFountain.h"

HRESULT HungryFountain::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_npcName = "����� �м�";
	_vConvTexts = vector<string>
	{
		"ĢĢ�� ������ ����� �м��̴�. �Ը��� ������ �� ����.",
		"�̹� ������ȴ�."
	};
	_vSelectTexts = vector<string>
	{
		"�Դ´�.",
		"���� �ʴ´�."
	};

	_isTalked = false;
	_useConv = true;
	_useSelect = true;
	_isActivated = false;
	return S_OK;
}

void HungryFountain::update()
{
	NPC::update();
	if (_selectFrame->GetIsViewing() && _isUsing)
	{
		Conversation();
	}
}

void HungryFountain::SetConvUI()
{
	dynamic_cast<UIText*>(_convFrame->GetChild("name"))->SetText(_npcName);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[0]);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetCntPos(0);

	if (!_isTalked)
	{
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected1")->GetChild("text"))->SetText(_vSelectTexts[0]);
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected2")->GetChild("text"))->SetText(_vSelectTexts[1]);
		_selectFrame->GetChild("selected1")->SetImage(nullptr);
		_selectFrame->GetChild("selected2")->SetImage(nullptr);
	}
	else
	{
		dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[1]);
		_selectFrame->SetIsViewing(false);
	}
}

void HungryFountain::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			this->Activate();
			_isTalked = true;
			_useSelect = false;
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
}

void HungryFountain::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void HungryFountain::release()
{
	NPC::release();
}

void HungryFountain::render(HDC hdc)
{
	NPC::render(hdc);
}

void HungryFountain::Activate()
{
	if (!_isActivated)
	{
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("descriptionText"))->SetText("�����������, ü���� ���������ϴ�.");
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("descriptionText"))->SetColor(RGB(208, 162, 0));
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("descriptionText"))->SetViewingTimer(180);

		_isActivating = !_isActivating;
		SOUNDMANAGER->play("NPC_�������_ȣ��");

		int satiety = ENTITYMANAGER->getPlayer()->GetSatiety() - 20;
		if (satiety < 0)
			satiety = 0;
		ENTITYMANAGER->getPlayer()->SetSatiety(satiety);

		int hp = ENTITYMANAGER->getPlayer()->GetHP() - 35;
		if (hp <= 0)
			hp = 1;
		ENTITYMANAGER->getPlayer()->SetHp(hp);

		_useImage = 1;
		_isUsing = true;
		_isActivated = true;
	}

	else
	{
		_isActivating = !_isActivating;
	}
}

void HungryFountain::Animation()
{
	NPC::Animation();
}
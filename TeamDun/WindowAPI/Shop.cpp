#include "stdafx.h"
#include "Shop.h"
#include "inventory.h"

HRESULT Shop::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	_npcName = "ũ��";
	_vConvTexts = vector<string>{
		"���� �Ǵ�. ���� �غ��س���.",
		"�ݰ���. ���� �͵� �����Դ�.",
		"���� ��� ���� �����Ŵ�."
	};

	_vSelectTexts = vector<string>{
		"����",
		"�ƹ��͵�"
	};

	_useConv = true;
	_useSelect = true;

	return S_OK;
}

void Shop::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			Activate();
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
		}
	}
	else _selectFrame->GetChild("selected2")->SetImage(nullptr);

}

void Shop::update()
{
	NPC::update();

	if (_selectFrame->GetIsViewing())
	{
		Conversation();
	}

	if (_shopBase->GetIsViewing())
	{
		if (_checkSellFrame->GetIsViewing())
		{
			CheckToSell();
		}
		else
		{
			BuyItem();
			if (_invenFrame->GetIsViewing()) SellItem();
		}
	}
}

void Shop::release()
{
	NPC::release();
}

void Shop::render(HDC hdc)
{
	NPC::render(hdc);
}

void Shop::Animation()
{
	NPC::Animation();
}

/// <summary>
/// DATAMANAGER���� �ҷ��� �� init ������ �͵鸸 init�Ѵ�.
/// </summary>
void Shop::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");

	_inven = ENTITYMANAGER->getPlayer()->GetInventory();
	_shopBase = UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase");
	_invenFrame = UIMANAGER->GetGameFrame()->GetChild("InventoryFrame");
	_checkSellFrame = UIMANAGER->GetGameFrame()->GetChild("CheckSell");
}

/// <summary>
/// �ʱ�ȭ�� Shop�� ������ �����۵��� �����ϰ�, �ʿ� �������� �����Ѵ�.
/// </summary>
void Shop::SetShopItem()
{
	_curToolTipItem = nullptr;
	_toolTipFinalY = 0;
	_toolTipIndex = 0;

	int itemSize = RANDOM->range(4, 6);
	for (int i = 0; i < itemSize; i++)
	{
		_vItemList.push_back(DATAMANAGER->GetItemById(RANDOM->range(DATAMANAGER->GetItemMinId(), DATAMANAGER->GetItemMaxId())));
	}
}

/// <summary>
/// �ʱ�ȭ Ȥ�� ������ ���Ž� ���Ӱ� UI�� ���ġ
/// </summary>
void Shop::ReNewUI()
{
	_shopBase->GetVChildFrames().clear(); // Frame ���θ� ������ ��

	for (int i = 0; i < _vItemList.size(); i++) // �� �������� �߰��Ѵ�
	{
		Item* item = _vItemList[i];

		int nameR = 255, nameG = 255, nameB = 255;
		switch (item->GetItemClass())
		{
		case ITEMCLASS::IC_NORMAL: nameR = 255, nameG = 255, nameB = 255; break;
		case ITEMCLASS::IC_ADVANCED: nameR = 112, nameG = 146, nameB = 190; break;
		case ITEMCLASS::IC_RARE: nameR = 232, nameG = 239, nameB = 90; break;
		case ITEMCLASS::IC_LEGENDARY: nameR = 237, nameG = 9, nameB = 138; break;
		}
		UIFrame* shopItem = new UIFrame();
		shopItem->init("ShopItem" + to_string(i), 20, 100 + i * IMAGEMANAGER->findImage("ShopItem")->getHeight(), IMAGEMANAGER->findImage("ShopItem")->getWidth(), IMAGEMANAGER->findImage("ShopItem")->getHeight(), "ShopItem");
		_shopBase->AddFrame(shopItem);

		UIFrame* itemImageFrame = new UIFrame();
		itemImageFrame->init("itemImageFrame", 0, 10, 57, 57, item->GetInvenImageName());
		shopItem->AddFrame(itemImageFrame);

		UIText* itemName = new UIText();
		itemName->init("itemName", 75, 12, 500, 50, item->GetName(), FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(nameR, nameG, nameB));
		shopItem->AddFrame(itemName);

		UIText* itemPrice = new UIText();
		itemPrice->init("itemPrice", 81, 41, 200, 40, to_string(item->GetBuyPrice()), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_RIGHT);
		shopItem->AddFrame(itemPrice);
	}

	UIImage* uiToolTip = new UIImage();
	uiToolTip->init("itemToolTip", 0, 0, 400, 500, "ToolTipCover", false, 0, 0, 4.0f, 5.0f, 130);
	_shopBase->AddFrame(uiToolTip);
	
	uiToolTip->SetIsViewing(false);
}

/// <summary>
/// �κ��丮���� ������ �� �������� �Ǹ��� �� �ֵ��� ����
/// </summary>
void Shop::SellItem()
{
	if (INPUT->GetIsRButtonClicked())
	{
		for (int i = 0; i < _inven->GetVItemList().size(); i++)
		{
			Item* item = _inven->GetVItemList()[i];
			if (PtInRect(&_invenFrame->GetChild("itemFrame_" + to_string(i))->GetRect(), _ptMouse))
			{
				_checkSellFrame->SetIsViewing(true);
				_selectedItem = item;
				_index = i;
				RenewCheckUI();
				break;
			}
		}
	}
}

/// <summary>
/// üũ �������� �ؽ�Ʈ�� ����
/// </summary>
void Shop::RenewCheckUI()
{
	dynamic_cast<UIText*>(_checkSellFrame->GetChild("text"))->SetText(_selectedItem->GetName() + "��(��) �Ǹ��Ͻðڽ��ϱ�?\n(���� : " + to_string(_selectedItem->GetSellPrice()) + "G)");
}

/// <summary>
/// üũ ȭ���� ������, �Է��� �޾� �Ǹ��ϰų� ���ư� �� �ְ���
/// </summary>
void Shop::CheckToSell()
{
	if (INPUT->GetIsLButtonClicked()) // ��ư Ŭ��
	{
		if (PtInRect(&_checkSellFrame->GetChild("yes")->GetRect(), _ptMouse))
		{
			ActivateSell();
		}

		else if (PtInRect(&_checkSellFrame->GetChild("no")->GetRect(), _ptMouse))
		{
			_selectedItem = nullptr;
			_index = 0;
			_checkSellFrame->SetIsViewing(false);
		}
	}

	else if (INPUT->GetKeyDown(VK_RETURN)) // ����
	{
		ActivateSell();
	}
}

/// <summary>
/// �Ǹ��ϴ� �˰���
/// </summary>
void Shop::ActivateSell()
{
	SOUNDMANAGER->play("NPC_�����Ǹ�");
	ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() + _selectedItem->GetSellPrice());
	_inven->GetVItemList().erase(_inven->GetVItemList().begin() + _index);
	_inven->ReloadUIImages();

	_selectedItem = nullptr;
	_index = 0;
	_checkSellFrame->SetIsViewing(false);
}

/// <summary>
/// ��Ŭ���� ���� ���ǿ� �´´ٸ� �������� �絵�� ��
/// </summary>
void Shop::BuyItem()
{
	UIImage* uiToolTip = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase")->GetChild("itemToolTip"));

	Item* item = nullptr;
	for (int i = 0; i < _vItemList.size(); i++)
	{
		if (PtInRect(&_shopBase->GetChild("ShopItem" + to_string(i))->GetRect(), _ptMouse))
		{
			item = _vItemList[i];
			_toolTipIndex = i;
			if (INPUT->GetIsRButtonClicked())
			{
				if (ENTITYMANAGER->getPlayer()->GetMoney() >= _vItemList[i]->GetBuyPrice()) // ���� ���
				{
					if (_inven->AddItem(_vItemList[i]) == true) // �ִ´뿡 �����ϸ�
					{
						SOUNDMANAGER->play("NPC_�����Ǹ�");
						ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - _vItemList[i]->GetBuyPrice());
						_vItemList.erase(_vItemList.begin() + i);
						ReNewUI();
					}
				}
			}
			break;
		}
	}

	if (item != nullptr)
	{
		uiToolTip->MoveFrameChild((_ptMouse.x) - uiToolTip->GetX(), (_ptMouse.y + (_toolTipIndex > 2 ? -_toolTipFinalY : 0) ) - uiToolTip->GetY());
		uiToolTip->SetIsViewing(true);
		
		if(item != _curToolTipItem)	InitToolTipItem(item);
	}

	else
	{
		uiToolTip->SetIsViewing(false);
	}
}

/// <summary>
/// Shop�� UI�� OnOff��
/// </summary>
void Shop::Activate()
{
	ReNewUI();
	_isActivating = !_isActivating;
	_shopBase->ToggleIsViewing();
	UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->SetIsViewing(_shopBase->GetIsViewing());
	_checkSellFrame->SetIsViewing(false);
}

/// <summary>
/// Inventory�� Tooltip�� ����. Shop�� ToolTip
/// </summary>
void Shop::InitToolTipItem(Item* item)
{
	_curToolTipItem = item;

	UIImage* uiToolTip = dynamic_cast<UIImage*>(_shopBase->GetChild("itemToolTip"));
	uiToolTip->GetVChildFrames().clear();

	// �̸� ��
	int nameR = 255, nameG = 255, nameB = 255;
	switch (item->GetItemClass())
	{
	case ITEMCLASS::IC_NORMAL: nameR = 255, nameG = 255, nameB = 255; break;
	case ITEMCLASS::IC_ADVANCED: nameR = 112, nameG = 146, nameB = 190; break;
	case ITEMCLASS::IC_RARE: nameR = 232, nameG = 239, nameB = 90; break;
	case ITEMCLASS::IC_LEGENDARY: nameR = 237, nameG = 9, nameB = 138; break;
	}

	// �̸�
	UIText* itemName = new UIText();
	itemName->init("itemName", 0, 10, 400, 200, item->GetName(), FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(nameR, nameG, nameB));
	uiToolTip->AddFrame(itemName);

	// �̹��� ������
	UIFrame* imgFrame = new UIFrame();
	imgFrame->init("imgFrame", 10, 50, IMAGEMANAGER->findImage("IconWhite")->getWidth(), IMAGEMANAGER->findImage("IconWhite")->getHeight(), "IconWhite");
	uiToolTip->AddFrame(imgFrame);

	// ������ �̹���
	UIFrame* itemImage = new UIFrame();
	itemImage->init("itemImage", 0, 0, item->GetInvenImage()->getWidth(), item->GetInvenImage()->getHeight(), item->GetInvenImageName());
	imgFrame->AddFrame(itemImage);

	// ���ݷ�
	if (item->GetMinAtk() != 0 && item->GetMaxAtk() != 0)
	{
		UIText* attack = new UIText();
		attack->init("attack", 75, 50, 80, 80, "���ݷ� : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(attack);

		UIText* attackValue = new UIText();
		attackValue->init("attackValue", 155, 50, 200, 80, to_string_with_precision(item->GetMinAtk(), 0) + " ~ " + to_string_with_precision(item->GetMaxAtk(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(attackValue);
	}

	// ���ݼӵ�
	if (item->GetAtkSpeed() != 0)
	{
		UIText* attackSpd = new UIText();
		attackSpd->init("attackSpd", 75, 70, 200, 80, "�ʴ� ���� Ƚ�� : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(attackSpd);

		UIText* attackSpdValue = new UIText();
		attackSpdValue->init("attackSpdValue", 225, 70, 200, 80, to_string_with_precision(item->GetAtkSpeed(), 2), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(attackSpdValue);
	}

	// ����
	if (item->GetDefence() != 0)
	{
		UIText* def = new UIText();
		def->init("def", 75, 90, 200, 80, "���� : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(def);

		UIText* defValue = new UIText();
		defValue->init("defValue", 155, 90, 200, 80, to_string_with_precision(item->GetDefence(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(defValue);
	}

	// �߰� �ɼ�
	for (int i = 0; i < item->GetSubOptions().size(); i++)
	{
		SubOption* option = item->GetSubOptions()[i];

		int optionR = 255, optionG = 255, optionB = 255;
		if (option->_optionPower < 0) optionR = 255, optionG = 0, optionB = 0;
		if (option->_optionPower > 0) optionR = 0, optionG = 255, optionB = 0;

		UIText* startText = new UIText();
		startText->init("��" + to_string(i), 15, 120 + i * 15, 30, 30, "��", FONT::PIX, WORDSIZE::WS_SMALLEST);
		uiToolTip->AddFrame(startText);

		UIText* descript = new UIText();
		descript->init("descript" + to_string(i), 30, 122 + i * 15, 370, 30, OptionString(option), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT,
			RGB(optionR, optionG, optionB));
		uiToolTip->AddFrame(descript);
	}

	_toolTipFinalY = item->GetSubOptions().size() * 20 + 122;

	// ������ Ŭ����
	string itemClassString = "�Ϲ� ������";
	switch (item->GetItemClass())
	{
	case ITEMCLASS::IC_NORMAL: itemClassString = "�Ϲ� ������"; break;
	case ITEMCLASS::IC_ADVANCED: itemClassString = "��� ������";  break;
	case ITEMCLASS::IC_RARE: itemClassString = "��� ������"; break;
	case ITEMCLASS::IC_LEGENDARY: itemClassString = "���� ������"; break;
	}

	UIText* itemClass = new UIText();
	itemClass->init("itemClass", 10, _toolTipFinalY + 5, 150, 30, itemClassString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(120, 120, 120));
	uiToolTip->AddFrame(itemClass);

	// ������ ����
	string itemKindString = "��չ���";
	switch (item->GetitemType())
	{
	case ITEMTYPE::IT_WEAPON_ONEHAND: itemKindString = "�Ѽչ���"; break;
	case ITEMTYPE::IT_WEAPON_TWOHAND: itemKindString = "��չ���"; break;
	case ITEMTYPE::IT_SUBWEAPON: itemKindString = "�������"; break;
	case ITEMTYPE::IT_ACCESORRY: itemKindString = "�Ǽ�����"; break;
	}

	UIText* itemKind = new UIText();
	itemKind->init("itemKind", 10, _toolTipFinalY + 20, 150, 30, itemKindString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(120, 120, 120));
	uiToolTip->AddFrame(itemKind);
	_toolTipFinalY += 15;

	// ���
	string weaponkindString = "";
	switch (item->GetWeaponType())
	{
	case WEAPONTYPE::WT_CHARGE: weaponkindString = "#������"; break;
	case WEAPONTYPE::WT_KATANA: weaponkindString = "#īŸ��"; break;
	case WEAPONTYPE::WT_PISTOL: weaponkindString = "#����"; break;
	case WEAPONTYPE::WT_SPEAR: weaponkindString = "#â"; break;
	}

	if (weaponkindString != "")
	{
		UIText* tag = new UIText();
		tag->init("tag", 10, _toolTipFinalY + 25, 100, 30, weaponkindString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(162, 210, 148));
		uiToolTip->AddFrame(tag);
		_toolTipFinalY += 20;
	}

	// ��ų
	if (item->GetSkill() != nullptr)
	{
		UIImage* skillFrame = new UIImage();
		skillFrame->init("skillFrame", 10, _toolTipFinalY + 25, 280, 55, "ToolTipSkillCover", false, 0, 0, 280 / 30.f, 55 / 30.f, 80);
		uiToolTip->AddFrame(skillFrame);
		UIFrame* skillImage = new UIFrame();
		skillImage->init("skillImage", 2, 2, 51, 51, item->GetSkill()->GetImageName(), 51.f / 57, 51.f / 57);
		skillFrame->AddFrame(skillImage);
		UIText* skillName = new UIText();
		skillName->init("skillName", 55, 2, 300, 80, item->GetSkill()->GetName(), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		skillFrame->AddFrame(skillName);
		UIText* skillDescription = new UIText();
		skillDescription->init("skillDescription", 55, 22, 220, 120, item->GetSkill()->GetDescription(), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT);
		skillFrame->AddFrame(skillDescription);
		UIText* skillCoolTime = new UIText();
		skillCoolTime->init("skillCoolTime", 257, 39, 20, 30, to_string_with_precision(item->GetSkill()->GetCoolTime(), 1), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_RIGHT, RGB(221, 173, 103));
		skillFrame->AddFrame(skillCoolTime);
		_toolTipFinalY += 45;
	}

	// ����
	UIText* description = new UIText();
	description->init("description", 10, _toolTipFinalY + 45, 350, 200, item->GetDescription(), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(208, 247, 252));
	uiToolTip->AddFrame(description);
	_toolTipFinalY += (item->GetDescription().length() / 22) * 10 + 70;

	if (_shopBase->GetIsViewing())
	{
		UIFrame* moneyImg = new UIFrame();
		moneyImg->init("moneyImg", 352, _toolTipFinalY - 2, 19, 19, "moneyUI");
		uiToolTip->AddFrame(moneyImg);

		UIText* sellMoney = new UIText();
		sellMoney->init("sellMoney", 250, _toolTipFinalY, 100, 50, to_string_with_precision(item->GetSellPrice(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_RIGHT);
		uiToolTip->AddFrame(sellMoney);
	}

	_toolTipFinalY += 30;
	uiToolTip->SetScaleY(_toolTipFinalY / 100.f);
}

/// <summary>
/// Inventory�� OptionString�� ����. Shop��.
/// </summary>
string Shop::OptionString(SubOption* option)
{
	string optionResult = "";

	if (option->_optionPower != 0)
	{
		optionResult += (option->_optionPower >= 0 ? "+" : "") + to_string_with_precision(option->_optionPower, 0);

		switch (option->_optionId)
		{
		case POWER:
			optionResult += " ����";
			break;
		case ATKSPEED:
			optionResult += "% ���ݼӵ�";
			break;
		case DASHATK:
			optionResult += "% �뽬 ���ݷ�";
			break;
		case DEFENCE:
			optionResult += " ����";
			break;
		case BLOCK:
			optionResult += " ����";
			break;
		case CRITICALPERCENT:
			optionResult += " ũ��Ƽ��";
			break;
		case CRITICALDAMAGE:
			optionResult += " ũ��Ƽ�� ������";
			break;
		case MINDAMAGE:
			optionResult += " �ּ� ������";
			break;
		case MAXDAMAGE:
			optionResult += " �ִ� ������";
			break;
		case FINALDAMAGEPERCENT:
			optionResult += "% ���� ������";
			break;
		case FINALDAMAGE:
			optionResult += " ���� ������";
			break;
		case TOUGHNESS:
			optionResult += " ������";
			break;
		case TRUEDAMAGE:
			optionResult += " ���� ������";
			break;
		case MAXHP:
			optionResult += " �ִ� ü��";
			break;
		case MAXHPPERCENT:
			optionResult += "% �ִ� ü��";
			break;
		case EVADE:
			optionResult += " ȸ��";
			break;
		case MOVESPEED:
			optionResult += "% �̵��ӵ�";
			break;
		case JUMPPOWER:
			optionResult += " ������";
			break;
		case GOLDDROP:
			optionResult += "% ��� ���";
			break;
		case RELOADSPEED:
			optionResult += "% ������ �ӵ�";
			break;
		case DASHCOUNT:
			optionResult += " �뽬 Ƚ��";
			break;
		case ACCURACY:
			optionResult += " ���� ��Ȯ��";
			break;
		case FIREDAMAGE:
			optionResult += " ȭ�� ����";
			break;
		case ICEDAMAGE:
			optionResult += " �ñ� ����";
			break;
		case ELECDAMAGE:
			optionResult += " ���� ����";
			break;
		case POSIONDAMAGE:
			optionResult += " �ߵ� ����";
			break;
		case STUNDAMAGE:
			optionResult += " ���� ����";
		default:
			break;
		}
	}

	switch (option->_optionId)
	{
	case IMMUNEFIRE:
		optionResult += "ȭ�� �鿪";
		break;
	case IMMUNEICE:
		optionResult += "�ñ� �鿪";
		break;
	case IMMUNEELEC:
		optionResult += "���� �鿪";
		break;
	case IMMUNEPOSION:
		optionResult += "�ߵ� �鿪";
		break;
	case IMMUNESTUN:
		optionResult += "���� �鿪";
		break;
	case TOFIRE:
		optionResult += "ȭ�� �ο�";
		break;
	case TOICE:
		optionResult += "�ñ� �ο�";
		break;
	case TOELEC:
		optionResult += "���� �ο�";
		break;
	case TOPOSION:
		optionResult += "�ߵ� �ο�";
		break;
	case TOSTUN:
		optionResult += "���� �ο�";
	}

	if (option->_description != ".")
		optionResult += option->_description;

	return optionResult;
}
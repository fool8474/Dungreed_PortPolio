#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{

	INPUT->init();
	UIMANAGER->init();
	initUI();

	_p = new Player();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);
	_p->init();

	MAPMANAGER->init();

	
	PARTICLEMANAGER->init();
	EFFECTMANAGER->init();

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	_vCharName = vector<string>{ "���谡", "�Ǳ��� ���", "������ ������", "�ٸ���", "ȫ��", "��Ű����", 
							     "���̴� H", "������ �Ƿ翧", "����� ��", "�׶׺�", "���˻�", "�ΰ� �󽽸�", "������ ����" };
	_CharExplanation = vector<string>{ "������ Ž���ϱ� ���� �� �ʺ� ���谡","�Ǳ� ������ �θ�, ����� ���","Ȳ�߸� ���������� �ܷο� ������",
									   "�䳢�� ������ �ʰ�, ���� ǥ���� ������!","�� �ʸӷ�...��ȭ�ϰ� ���� ������, �״�?","��..��..�ô����̶�! ��!",
									   "���� �����,\n��𿡼��� �޸��� �ʹ�.","���� ���⵵ ��������.\n���� ��ǰ�� õ������.","������ ������ ���� ����ִ� ����",
									   "�� �޸����� ��������,\n �ֵθ��� �� ��ô ���Ұſ���.","��Ȱ�� �� ����� �ǹ��ϴ� ���� �ƴϵ���.",
									   "���˿� ��������� �� ���� ����̴�.","���� ��� ������ ��������� �ֹ���. �� ��� �ؾ��� ��ǰ�̶�� �Ѵ�."};
	_CharAbility = vector<string>{ "","","�� ���� ������: ���� �±װ� ���� ���⸦ ����ϸ� ������ 50 ����մϴ�",
									  "�� ����: ���� �ݰ� �ȿ� ���� �ִٸ� ������ -20 �����մϴ�.",
									  "�� ǥ��: ���� �����ϸ� ������ 6�÷��ִ� ǥ���� ����ϴ�.(�ִ� 10��)",
									  "�� �ݳ�: ���� �����ų� óġ�ϸ� �ݳ븦 ȹ���մϴ�. �ݳ� ��ġ�� �� ���� ����\n�ð� ���� ���ݼӵ��� 100% ����մϴ�.",
									  "�� �ӵ���: ���� �ӵ��� ����� ������ �ִ� +50���� ȹ���մϴ�.",
									  "�� ���൵��: ������ �ִ� ������ 1���� ���� +4, ���� -2, ü��-1��\nȹ���մϴ�. (���� ���� ������ ����)","",
									  "�� Ǯ����: ���� ���⸦ ����ϸ� ������ 30 ����մϴ�.",
									  "�� ��Ȱ�� ����: ü���� 40���� �����˴ϴ�. �������� 2ȸ ��Ȱ�� �� �ֽ��ϴ�.",
									  "�� ���: ������ ó���� ������ �ִ� ü�� ����, �ִ� ü�� -45 �����մϴ�.",
									  "�� ��ȣ�� ����" };
	_CharFirstStat = vector<string>{ "","�� +10 ����","�� -15 �ִ� ü��","�� -30 �ִ� ü��","�� -15 �ִ� ü��","�� -20 ����","�� +22% �̵��ӵ�","","�� +1 �뽬 Ƚ��","�� -20% �̵��ӵ�","","","�� ���� ��Ȯ�� +33"};
	_CharSecondStat = vector<string>{"","�� -10 �ִ� ü��","�� -15 ����","�� +40 ����","�� -5 ȸ��","�� -5 ����","�� -2 ������","�� -12 ȸ��","�� -25 ũ��Ƽ��","�� -10% ���ݼӵ�","","","�� +33 �ִ� ü��"};

	_scrollTimer = 0;
	_mouseLocation = 0;

	CAMERAMANAGER->init(0, 0, 15000, 15000, -300, -300, WINSIZEX / 2, WINSIZEY / 2);
	return S_OK;
}

void gameScene::initUI()
{
	DungeonMapUIInit();

	// WarDrobe Frame //
	UIFrame* warDrobeFrame = new UIFrame();
	warDrobeFrame->init("warDrobeFrame", 0, 0, IMAGEMANAGER->findImage("ScreenCover")->getWidth(), IMAGEMANAGER->findImage("ScreenCover")->getHeight(), "ScreenCover");
	UIMANAGER->GetGameFrame()->AddFrame(warDrobeFrame);
	warDrobeFrame->SetIsViewing(false);

	UIFrame* warDrobetitle = new UIFrame();
	warDrobetitle->init("CostumeBase_0", 250, 0, IMAGEMANAGER->findImage("CostumeBase_0")->getWidth(), IMAGEMANAGER->findImage("CostumeBase_0")->getHeight(), "CostumeBase_0");
	warDrobeFrame->AddFrame(warDrobetitle);

	UIFrame* baseFrame = new UIFrame();
	baseFrame->init("Base", -50, 87, IMAGEMANAGER->findImage("Base")->getWidth(), IMAGEMANAGER->findImage("Base")->getHeight(), "Base", 7, 1.63);
	warDrobeFrame->AddFrame(baseFrame);

	UIFrame* costumeExplanationFrame = new UIFrame();
	costumeExplanationFrame->init("CostumeBase_1", 0, 400, IMAGEMANAGER->findImage("CostumeBase_1")->getWidth(), IMAGEMANAGER->findImage("CostumeBase_1")->getHeight(), "CostumeBase_1", 1.5, 2.5);
	warDrobeFrame->AddFrame(costumeExplanationFrame);

	UIFrame* costumeExplanationBox = new UIFrame();
	costumeExplanationBox->init("SlotDeleteButton_Rev", 500, 180, IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getWidth(), IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getHeight(), "SlotDeleteButton_Rev", 0.6, 0.7);
	costumeExplanationFrame->AddFrame(costumeExplanationBox);

	UIFrame* costumeExplanationSecondBox = new UIFrame();
	costumeExplanationSecondBox->init("SlotDeleteButton_Rev", 1375, 80, IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getWidth(), IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getHeight(), "SlotDeleteButton_Rev", 0.6, 1.2);
	costumeExplanationFrame->AddFrame(costumeExplanationSecondBox);

	for (int i = 0; i < 13; i++)
	{
		UIFrame* warDrobeBox = new UIFrame();
		warDrobeBox->init("CostumeBack" + to_string(i), 220 * i, 5, IMAGEMANAGER->findImage("CostumeBack")->getWidth(), IMAGEMANAGER->findImage("CostumeBack")->getHeight(), "CostumeBack", 1, 1);
		baseFrame->AddFrame(warDrobeBox);
	}

	for (int i = 0; i < 13; i++)
	{
		UIFrame* warDrobeCharFrame = new UIFrame();
		warDrobeCharFrame->init("CostumeUnlocked" + to_string(i), 220 * i + 10, 15, IMAGEMANAGER->findImage("CostumeUnlocked")->getWidth(), IMAGEMANAGER->findImage("CostumeUnlocked")->getHeight(), "CostumeUnlocked");
		baseFrame->AddFrame(warDrobeCharFrame);

		UIImage* warDrobeCharBoxIg = new UIImage();
		warDrobeCharBoxIg->init("char", 77, 180, 51, 63, "", false, 0, 0);
		warDrobeCharFrame->AddFrame(warDrobeCharBoxIg);
	}

	for (int i = 0; i < 13; i++)
	{
		UIFrame* costumeFrame = new UIFrame();
		costumeFrame->init("CostumeOver" + to_string(i), 220 * i + 10, 15, IMAGEMANAGER->findImage("CostumeOver")->getWidth(), IMAGEMANAGER->findImage("CostumeOver")->getHeight(), "CostumeOver");
		baseFrame->AddFrame(costumeFrame);
	}

	UIFrame* adventurer = new UIFrame();
	adventurer->init("adventurer", 75, 180, IMAGEMANAGER->findImage("adventurer")->getWidth(), IMAGEMANAGER->findImage("adventurer")->getHeight(), "adventurer");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(0))->AddFrame(adventurer);

	UIFrame* sheeting = new UIFrame();
	sheeting->init("sheeting", 75, 178, IMAGEMANAGER->findImage("sheeting")->getWidth(), IMAGEMANAGER->findImage("sheeting")->getHeight(), "sheeting");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(1))->AddFrame(sheeting);

	UIFrame* gunman = new UIFrame();
	gunman->init("gunman", 70, 175, IMAGEMANAGER->findImage("gunman")->getWidth(), IMAGEMANAGER->findImage("gunman")->getHeight(), "gunman");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(2))->AddFrame(gunman);

	UIFrame* alice = new UIFrame();
	alice->init("alice", 75, 180, IMAGEMANAGER->findImage("alice")->getWidth(), IMAGEMANAGER->findImage("alice")->getHeight(), "alice");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(3))->AddFrame(alice);

	UIFrame* redlotus = new UIFrame();
	redlotus->init("redlotus", 75, 180, IMAGEMANAGER->findImage("redlotus")->getWidth(), IMAGEMANAGER->findImage("redlotus")->getHeight(), "redlotus");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(4))->AddFrame(redlotus);

	UIFrame* lkinabear = new UIFrame();
	lkinabear->init("lkinabear", 75, 180, IMAGEMANAGER->findImage("lkinabear")->getWidth(), IMAGEMANAGER->findImage("lkinabear")->getHeight(), "lkinabear");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(5))->AddFrame(lkinabear);

	UIFrame* riderH = new UIFrame();
	riderH->init("riderH", 55, 180, IMAGEMANAGER->findImage("riderH")->getWidth(), IMAGEMANAGER->findImage("riderH")->getHeight(), "riderH");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(6))->AddFrame(riderH);

	UIFrame* criminal = new UIFrame();
	criminal->init("criminal", 75, 180, IMAGEMANAGER->findImage("criminal")->getWidth(), IMAGEMANAGER->findImage("criminal")->getHeight(), "criminal");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(7))->AddFrame(criminal);

	UIFrame* pick = new UIFrame();
	pick->init("pick", 75, 180, IMAGEMANAGER->findImage("pick")->getWidth(), IMAGEMANAGER->findImage("pick")->getHeight(), "pick");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(8))->AddFrame(pick);

	UIFrame* fasto = new UIFrame();
	fasto->init("fasto",75,180, IMAGEMANAGER->findImage("fasto")->getWidth(), IMAGEMANAGER->findImage("fasto")->getHeight(), "fasto");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(9))->AddFrame(fasto);

	UIFrame* horseman = new UIFrame();
	horseman->init("horseman", 75, 180, IMAGEMANAGER->findImage("horseman")->getWidth(), IMAGEMANAGER->findImage("horseman")->getHeight(), "horseman");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(10))->AddFrame(horseman);

	UIFrame* humanlasley = new UIFrame();
	humanlasley->init("humanlasley", 75, 180, IMAGEMANAGER->findImage("humanlasley")->getWidth(), IMAGEMANAGER->findImage("humanlasley")->getHeight(), "humanlasley");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(11))->AddFrame(humanlasley);

	UIFrame* masterchef = new UIFrame();
	masterchef->init("masterchef", 75, 180, IMAGEMANAGER->findImage("masterchef")->getWidth(), IMAGEMANAGER->findImage("masterchef")->getHeight(), "masterchef");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(12))->AddFrame(masterchef);

	
	UIText* charNameText = new UIText();
	charNameText->init("charNameText", 50, 100, 400, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 204, 0));
	costumeExplanationFrame->AddFrame(charNameText);

	UIText* CharExplanationText = new UIText();
	CharExplanationText->init("CharExplanationText", 50, 200, 400, 50, "", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharExplanationText);

	UIText* CharAbilityText = new UIText();
	CharAbilityText->init("CharAbilityText", 550, 150, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(0, 255, 0));
	costumeExplanationFrame->AddFrame(CharAbilityText);

	UIText* _CharFirstStat = new UIText();
	_CharFirstStat->init("CharFirstStat", 550, 200, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255,255));
	costumeExplanationFrame->AddFrame(_CharFirstStat);

	UIText* _CharSecondStat = new UIText();
	_CharSecondStat->init("CharSecondStat", 550, 250, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(_CharSecondStat);

	InventoryUIInit();
}

void gameScene::DungeonMapUIInit()
{
	// DungeonMap Frame //
	UIImage* allMapFrame = new UIImage();
	allMapFrame->init("allMapFrame", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", false, 0, 0, 1, 1, 80);
	UIMANAGER->GetGameFrame()->AddFrame(allMapFrame);

	UIFrame* mapUpperImg = new UIFrame();
	mapUpperImg->init("mapUpperImg", 0, 0, IMAGEMANAGER->findImage("MapBase_1_0")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_0")->getHeight(), "MapBase_1_0", 1.0f, 1.0f);
	allMapFrame->AddFrame(mapUpperImg);

	UIFrame* mapFrame = new UIFrame();
	mapFrame->init("mapFrame", 130, 180, IMAGEMANAGER->findImage("MapBase_1_1")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_1")->getHeight(), "MapBase_1_1", 1.5f, 1.4f);
	mapFrame->SetUseOutsideLimit(true);
	allMapFrame->AddFrame(mapFrame);

	allMapFrame->SetIsViewing(false);
}

void gameScene::InventoryUIInit()
{
	// Inventory Frame //
	UIFrame* InventoryFrame = new UIFrame();
	InventoryFrame->init("InventoryFrame", 1000, 170, IMAGEMANAGER->findImage("InventoryBase_2")->getWidth(), IMAGEMANAGER->findImage("InventoryBase_2")->getHeight(), "InventoryBase_2");
	UIMANAGER->GetGameFrame()->AddFrame(InventoryFrame);

	UIFrame* weaponImageFrame = new UIFrame();
	weaponImageFrame->init("curWeapon_1", 48, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageFrame);

	UIFrame* weaponImageSubFrame = new UIFrame();
	weaponImageSubFrame->init("curWeaponSub_1", 114, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageSubFrame);

	UIFrame* weaponImageFrame2 = new UIFrame();
	weaponImageFrame2->init("curWeapon_2", 210, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageFrame2);

	UIFrame* weaponImageSubFrame2 = new UIFrame();
	weaponImageSubFrame2->init("curWeaponSub_2", 276, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageSubFrame2);

	int accesorySize = 4;
	for (int i = 0; i < accesorySize; i++)
	{
		UIFrame* accesory = new UIFrame();
		accesory->init("accesoryFrame_" + to_string(i), (i * (IMAGEMANAGER->findImage("accessory")->getWidth() + 8)) + 65 - (accesorySize - 4) * (IMAGEMANAGER->findImage("accessory")->getWidth() / 2 + 4)
			, 190, IMAGEMANAGER->findImage("accessory")->getWidth(), IMAGEMANAGER->findImage("accessory")->getHeight(), "accessory");
		InventoryFrame->AddFrame(accesory);

		UIFrame* itemImageFrame = new UIFrame();
		itemImageFrame->init("itemImageFrame", 0, 0, 57, 57, "");
		accesory->AddFrame(itemImageFrame);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			UIFrame* itemFrame = new UIFrame();
			itemFrame->init("itemFrame_" + to_string(i * 5 + j), (j * (IMAGEMANAGER->findImage("IconGray")->getWidth() + 8) + 32), 280 + (i * (IMAGEMANAGER->findImage("IconGray")->getHeight() + 8)), IMAGEMANAGER->findImage("IconGray")->getWidth(), IMAGEMANAGER->findImage("IconGray")->getHeight(), "IconGray");
			InventoryFrame->AddFrame(itemFrame);

			UIFrame* itemImageFrame = new UIFrame();
			itemImageFrame->init("itemImageFrame", 0, 0, 57, 57, "");
			itemFrame->AddFrame(itemImageFrame);
		}
	}

	UIText* moneyText = new UIText();
	moneyText->init("moneyText", 10, 502, 300, 100, "0", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_RIGHT, RGB(255, 255, 255));
	InventoryFrame->AddFrame(moneyText);

	InventoryFrame->SetIsViewing(false);


	UIText* accessFullText = new UIText();
	accessFullText->init("isFullText", 350, 200, 800, 200, "�κ��丮 ����� ������ �� �����ϴ�.", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(200, 30, 30));
	UIMANAGER->GetGameFrame()->AddFrame(accessFullText);
	accessFullText->SetIsViewing(false);

	UIText* accessEqualText = new UIText();
	accessEqualText->init("isEqualText", 350, 200, 800, 200, "���� �������� ������ �� �����ϴ�.", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(200, 30, 30));
	UIMANAGER->GetGameFrame()->AddFrame(accessEqualText);
	accessEqualText->SetIsViewing(false);
}

void gameScene::release()
{
	ENTITYMANAGER->release();
	ENTITYMANAGER->releaseSingleton();
	MAPMANAGER->release();
	MAPMANAGER->releaseSingleton();
	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();
	PARTICLEMANAGER->release();
	PARTICLEMANAGER->releaseSingleton();
}

void gameScene::update()
{
	INPUT->update();

	if (INPUT->GetKeyDown(VK_BACK))
	{
		UIMANAGER->_GameFrame->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("����ȭ��");
	}

	MAPMANAGER->update();
	CAMERAMANAGER->MovePivotLerp(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), 5.f);
	ENTITYMANAGER->update();
	EFFECTMANAGER->update();
	PARTICLEMANAGER->update();
	UIMANAGER->update();

	if (INPUT->GetKeyDown('P'))
	{
		UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->ToggleIsViewing();
		for (int i = 0; i < 13; i++)
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
		}
	}

	if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetRect(), _ptMouse) && INPUT->GetKey(VK_LBUTTON))
	{
		_scrollTimer++;
		if (_scrollTimer == 10)
		{
			_mouseLocation = _ptMouse.x;
		}
		
		else if(_scrollTimer > 10)
		{
			for (int i = 0; i < 13; i++)
			{
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeBack" + to_string(i))->MoveFrameChild(_ptMouse.x-_mouseLocation, 0);
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->MoveFrameChild(_ptMouse.x-_mouseLocation, 0);
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->MoveFrameChild(_ptMouse.x-_mouseLocation, 0);
			}
			_mouseLocation = _ptMouse.x;
		}
	}

	if (INPUT->GetKeyUp(VK_LBUTTON))
	{
		_scrollTimer = 0;
		_mouseLocation = 0;
	}

	if (INPUT->GetKeyDown('V'))
	{
		UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->ToggleIsViewing();
	}

	for (int i = 0; i < 13; i++)
	{
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->GetRect(), _ptMouse))
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(true);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("charNameText"))->SetText(_vCharName[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharExplanationText"))->SetText(_CharExplanation[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharAbilityText"))->SetText(_CharAbility[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharFirstStat"))->SetText(_CharFirstStat[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharSecondStat"))->SetText(_CharSecondStat[i]);
		}
		else
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
	}
}

void gameScene::render()
{
	MAPMANAGER->render(getMemDC());
	UIMANAGER->render(getMemDC());

	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));

	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

	string n = to_string((int)CAMERAMANAGER->GetAbsoluteX(_ptMouse.x)) + " " + to_string((int)CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));

	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, n.c_str(), n.length());
}

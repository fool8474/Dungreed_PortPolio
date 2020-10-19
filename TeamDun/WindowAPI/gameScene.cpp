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
	_scrollTimer = 0;
	_mouseLocation = 0;

	InitWardrobeString();
	CAMERAMANAGER->init(0, 0, 6720, 15000, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
	return S_OK;
}

void gameScene::InitWardrobeString()
{
	_vCharName = vector<string>{ "���谡", "�Ǳ��� ���", "������ ������", "�ٸ���", "ȫ��", "��Ű����",
								 "���̴� H", "������ �Ƿ翧", "����� ��", "�׶׺�", "���˻�", "�ΰ� �󽽸�", "������ ����" };
	_CharExplanation = vector<string>{ "������ Ž���ϱ� ���� �� �ʺ� ���谡","�Ǳ� ������ �θ�, ����� ���","Ȳ�߸� ���������� �ܷο� ������",
									   "�䳢�� ������ �ʰ�, ���� ǥ���� ������!","�� �ʸӷ�...��ȭ�ϰ� ���� ������, �״�?","��..��..�ô����̶�! ��!",
									   "���� �����,\n��𿡼��� �޸��� �ʹ�.","���� ���⵵ ��������.\n���� ��ǰ�� õ������.","������ ������ ���� ����ִ� ����",
									   "�� �޸����� ��������,\n �ֵθ��� �� ��ô ���Ұſ���.","��Ȱ�� �� ����� �ǹ��ϴ� ���� �ƴϵ���.",
									   "���˿� ��������� �� ���� ����̴�.","���� ��� ������ ��������� �ֹ���. �� ��� �ؾ��� ��ǰ�̶�� �Ѵ�." };
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
	_CharFirstStat = vector<string>{ "","�� +10 ����","�� -15 �ִ� ü��","�� -30 �ִ� ü��","�� -15 �ִ� ü��","�� -20 ����","�� +22% �̵��ӵ�","","�� +1 �뽬 Ƚ��","�� -20% �̵��ӵ�","","","�� ���� ��Ȯ�� +33" };
	_CharSecondStat = vector<string>{ "","�� -10 �ִ� ü��","�� -15 ����","�� +40 ����","�� -5 ȸ��","�� -5 ����","�� -2 ������","�� -12 ȸ��","�� -25 ũ��Ƽ��","�� -10% ���ݼӵ�","","","�� +33 �ִ� ü��" };

}

void gameScene::initUI()
{
	MainGameFrameInit();
	DungeonMapUIInit();
	InventoryUIInit();
	CharUIInit();
	RestaurantUIInit();
	ShopUIInit();
	WardrobeUIInit();
	ConversationUIInit();
	GetItemUIInit();
	TraitUIInit();
	BossHpUIInit();
}

void gameScene::MainGameFrameInit()
{
	UIFrame* container = new UIFrame();
	container->init("swapContainer", WINSIZEX - 180, WINSIZEY - 150, 200, 200, "");
	UIMANAGER->GetGameFrame()->AddFrame(container);

	UIFrame* weapon1 = new UIFrame();
	weapon1->init("weapon2", 50, 0, IMAGEMANAGER->findImage("EquippedWeaponBase")->getWidth(), IMAGEMANAGER->findImage("EquippedWeaponBase")->getHeight(), "EquippedWeaponBase");
	container->AddFrame(weapon1);

	UIFrame* image1 = new UIFrame();
	image1->init("image", 0, 0, 0, 0, "");
	weapon1->AddFrame(image1);

	UIFrame* weapon2 = new UIFrame();
	weapon2->init("weapon1", 0, 50, IMAGEMANAGER->findImage("EquippedWeaponBase")->getWidth(), IMAGEMANAGER->findImage("EquippedWeaponBase")->getHeight(), "EquippedWeaponBase");
	container->AddFrame(weapon2);

	UIFrame* image2 = new UIFrame();
	image2->init("image", 0, 0, 0, 0, "");
	weapon2->AddFrame(image2);

	UIFrame* hpFrame = new UIFrame();
	hpFrame->init("hpFrame", 20, 20, 0, 0, "");
	UIMANAGER->GetGameFrame()->AddFrame(hpFrame);

	UIProgressBar* hpBar1 = new UIProgressBar();
	hpBar1->init("hpBarPros", 42, 0, 180, 48, "LifeBar", "PlayerLifeBackGray_2");
	hpFrame->AddFrame(hpBar1);

	UIImage* hpWave = new UIImage();
	hpWave->init("Wave", 193, 0, 159, 48, "LifeWave", true, 0, 0);
	hpFrame->AddFrame(hpWave);

	UIFrame* hpBar0 = new UIFrame();
	hpBar0->init("hpBarLeft", 0, 0, 63, 48, "PlayerLifeBackGray_1");
	hpFrame->AddFrame(hpBar0);

	UIText* level = new UIText();
	level->init("level", 0, 12, 70, 48, "0", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE);
	hpFrame->AddFrame(level);

	UIText* hp = new UIText();
	hp->init("hp", 63, 12, 159, 48, "100 / 100", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE);
	hpFrame->AddFrame(hp);

	UIFrame* hpFrameBar0 = new UIFrame();
	hpFrameBar0->init("hpBarFrame1", 0, 0, 63, 48, "PlayerLifeBase_1");
	hpFrame->AddFrame(hpFrameBar0);

	UIFrame* hpFrameBar1 = new UIFrame();
	hpFrameBar1->init("hpBarFrame2", 63, 0, 159, 48, "PlayerLifeBase_2");
	hpFrame->AddFrame(hpFrameBar1);

	UIFrame* dashUI = new UIFrame();
	dashUI->init("dashFrame", 20, 70, 0, 0, "");
	UIMANAGER->GetGameFrame()->AddFrame(dashUI);

	UIFrame* leftDownUI = new UIFrame();
	leftDownUI->init("leftDown", 20, WINSIZEY - 80, 0, 0, "");
	UIMANAGER->GetGameFrame()->AddFrame(leftDownUI);

	UIFrame* coin = new UIFrame();
	coin->init("Coin", 0, 8, 0, 0, "Coin");
	leftDownUI->AddFrame(coin);

	UIText* coinText = new UIText();
	coinText->init("CoinText", 22, 8, 120, 30, "12345", FONT::PIX, WORDSIZE::WS_SMALL);
	leftDownUI->AddFrame(coinText);

	UIFrame* food = new UIFrame();
	food->init("Food", 0, 29, 0, 0, "Food");
	leftDownUI->AddFrame(food);

	UIText* foodText = new UIText();
	foodText->init("FoodText", 22, 29, 120, 30, "100 / 125", FONT::PIX, WORDSIZE::WS_SMALL);
	leftDownUI->AddFrame(foodText);

	container->SetIsViewing(true);
	hpFrame->SetIsViewing(true);
}

void gameScene::GetItemUIInit()
{
	UIImage* getFrame = new UIImage();
	getFrame->init("itemGetFrame", WINSIZEX / 2 - 250, WINSIZEY - 220, 500, 150, "ScreenCover", false, 0, 0, 2.5f, 0.75f, 180);
	UIMANAGER->GetGameFrame()->AddFrame(getFrame);

	UIFrame* itemImage = new UIFrame();
	itemImage->init("image", 30, 30, IMAGEMANAGER->findImage("DemonSword_Drop")->getFrameWidth() * 3.0f, IMAGEMANAGER->findImage("DemonSword_Drop")->getFrameHeight() * 3.0f, "DemonSword_Drop", 3.0f, 3.0f);
	getFrame->AddFrame(itemImage);

	UIText* itemGet = new UIText();
	itemGet->init("getText", 200, 20, 300, 50, "������ ȹ��", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE);
	getFrame->AddFrame(itemGet);

	UIText* name = new UIText();
	name->init("name", 200, 70, 300, 50, "���� ������", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_MIDDLE);
	getFrame->AddFrame(name);

	getFrame->SetIsViewing(false);
}

void gameScene::ConversationUIInit()
{
	UIFrame* convFrame = new UIFrame();
	convFrame->init("convFrame", 0, 530, 1440, 800, "ConversationUI");
	UIMANAGER->GetGameFrame()->AddFrame(convFrame);

	UIText* name = new UIText();
	name->init("name", 30, 30, 800, 100, "", FONT::PIX, WORDSIZE::WS_BIGGEST, WORDSORT::WSORT_LEFT, RGB(241, 182, 158));
	convFrame->AddFrame(name);

	UIText* text = new UIText();
	text->init("text", 30, 100, 1380, 250, "", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_LEFT, RGB(255, 255, 255), true, WORDANIMATIONSPEED::WAS_FAST);
	convFrame->AddFrame(text);

	UIFrame* selectFrame = new UIFrame();
	selectFrame->init("selectFrame", 1150, 390, 266, 125, "SelectUI", 1.0f, 1.0f);
	UIMANAGER->GetGameFrame()->AddFrame(selectFrame);

	UIFrame* selectedFrame = new UIFrame();
	selectedFrame->init("selected1", 17, 19, 232, 44, "SelectedFrame");
	selectFrame->AddFrame(selectedFrame);

	UIFrame* selectedFrame2 = new UIFrame();
	selectedFrame2->init("selected2", 17, 63, 232, 44, "SelectedFrame");
	selectFrame->AddFrame(selectedFrame2);

	UIText* selectOne = new UIText();
	selectOne->init("text", 0, 10, 232, 24, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE);
	selectedFrame->AddFrame(selectOne);

	UIText* selectTwo = new UIText();
	selectTwo->init("text", 0, 10, 232, 24, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE);
	selectedFrame2->AddFrame(selectTwo);

	convFrame->SetIsViewing(false);
	selectFrame->SetIsViewing(false);
}

void gameScene::RestaurantUIInit()
{
	UIImage* _restaurantBase = new UIImage();
	_restaurantBase->init("_restaurantBase", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", true, 0, 0, 10.0f, 10.0f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantBase);

	UIText* full = new UIText();
	full->init("full", 0, 200, WINSIZEX, 500, "�谡 �ҷ� ������ ���� �� �����ϴ�.", FONT::PIX, WORDSIZE::WS_BIGGEST, WORDSORT::WSORT_MIDDLE, RGB(207, 18, 18));
	UIMANAGER->GetGameFrame()->AddFrame(full);
	full->SetIsViewing(false);

	UIText* noMoney = new UIText();
	noMoney->init("noMoney", 0, 200, WINSIZEX, 500, "�������� �����մϴ�!", FONT::PIX, WORDSIZE::WS_BIGGEST, WORDSORT::WSORT_MIDDLE, RGB(207, 18, 18));
	UIMANAGER->GetGameFrame()->AddFrame(noMoney);
	noMoney->SetIsViewing(false);

	UIImage* _foodImg = new UIImage();
	_foodImg->init("_foodImg", 870, 350, 219, 144, "", false, 0, 0, 1.4f, 1.4f, 255);
	UIMANAGER->GetGameFrame()->AddFrame(_foodImg);
	_foodImg->SetIsViewing(false);

	_restaurantBase->SetIsViewing(false);
}

void gameScene::WardrobeUIInit()
{
	// WarDrobe Frame //
	UIFrame* warDrobeFrame = new UIFrame();
	warDrobeFrame->init("warDrobeFrame", 0, 0, 1440, 1080, "ScreenCover", 7.2f, 4.f);
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
	fasto->init("fasto", 75, 185, IMAGEMANAGER->findImage("fasto")->getWidth(), IMAGEMANAGER->findImage("fasto")->getHeight(), "fasto");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(9))->AddFrame(fasto);

	UIFrame* horseman = new UIFrame();
	horseman->init("horseman", 75, 175, IMAGEMANAGER->findImage("horseman")->getWidth(), IMAGEMANAGER->findImage("horseman")->getHeight(), "horseman");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(10))->AddFrame(horseman);

	UIFrame* humanlasley = new UIFrame();
	humanlasley->init("humanlasley", 75, 180, IMAGEMANAGER->findImage("humanlasley")->getWidth(), IMAGEMANAGER->findImage("humanlasley")->getHeight(), "humanlasley");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(11))->AddFrame(humanlasley);

	UIFrame* masterchef = new UIFrame();
	masterchef->init("masterchef", 70, 170, IMAGEMANAGER->findImage("masterchef")->getWidth(), IMAGEMANAGER->findImage("masterchef")->getHeight(), "masterchef");
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

	UIText* CharFirstStat = new UIText();
	CharFirstStat->init("CharFirstStat", 550, 200, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharFirstStat);

	UIText* CharSecondStat = new UIText();
	CharSecondStat->init("CharSecondStat", 550, 250, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharSecondStat);

}

void gameScene::DungeonMapUIInit()
{
	// DungeonMap Frame //
	UIImage* allMapFrame = new UIImage();
	allMapFrame->init("allMapFrame", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", false, 0, 0, 1440 / 200.f, 800 / 200.f);
	UIMANAGER->GetGameFrame()->AddFrame(allMapFrame);

	UIFrame* mapUpperImg = new UIFrame();
	mapUpperImg->init("mapUpperImg", 0, 0, IMAGEMANAGER->findImage("MapBase_1_0")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_0")->getHeight(), "MapBase_1_0");
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
	InventoryFrame->SetUseOutsideLimit(false);
	UIMANAGER->GetGameFrame()->AddFrame(InventoryFrame);

	UIFrame* weaponImageFrame = new UIFrame();
	weaponImageFrame->init("curWeapon_1", 48, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageFrame);

	UIFrame* weaponImageSubFrame = new UIFrame();
	weaponImageSubFrame->init("curWeaponSub_1", 110, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageSubFrame);

	UIFrame* weaponImageFrame2 = new UIFrame();
	weaponImageFrame2->init("curWeapon_2", 210, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageFrame2);

	UIFrame* weaponImageSubFrame2 = new UIFrame();
	weaponImageSubFrame2->init("curWeaponSub_2", 268, 105, 57, 57, "");
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
	moneyText->init("moneyText", 5, 505, 300, 100, "0", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_RIGHT, RGB(255, 255, 255));
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


	/////////// TOOLTIP /////////////

	UIImage* uiToolTip = new UIImage();
	uiToolTip->init("itemToolTip", 0, 0, 400, 500, "ToolTipCover", false, 0, 0, 4.0f, 5.0f, 130);
	uiToolTip->SetUseOutsideLimit(false);
	InventoryFrame->AddFrame(uiToolTip);
}

void gameScene::TraitUIInit()
{
	UIImage* traitBase = new UIImage();
	traitBase->init("allTraitFrame", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", false, 0, 0, 1440 / 200.f, 800 / 200.f);
	UIMANAGER->GetGameFrame()->AddFrame(traitBase);

	UIImage* tooltipFrame = new UIImage();
	tooltipFrame->init("traitToolTip", 0, 0, 200, 100, "ToolTipCover", false, 0, 0, 2.0f, 1.0f, 80);
	UIMANAGER->GetGameFrame()->AddFrame(tooltipFrame);

	UIText* tooltipDiscript = new UIText();
	tooltipDiscript->init("description", 10, 10, 190, 90, "", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	tooltipFrame->AddFrame(tooltipDiscript);

	tooltipFrame->SetIsViewing(false);
	traitBase->SetIsViewing(false);
}

void gameScene::ShopUIInit()
{
	UIFrame* shopBase = new UIFrame();
	shopBase->init("DungeonShopBase", 0, 100, IMAGEMANAGER->findImage("DungeonShopBase")->getWidth(), IMAGEMANAGER->findImage("DungeonShopBase")->getHeight(), "DungeonShopBase");
	UIMANAGER->GetGameFrame()->AddFrame(shopBase);

	UIFrame* checkSell = new UIFrame();
	checkSell->init("CheckSell", WINSIZEX / 2 - IMAGEMANAGER->findImage("BaseType2")->getWidth() / 2 * 1.5f, WINSIZEY / 2 - IMAGEMANAGER->findImage("BaseType2")->getHeight() / 2, IMAGEMANAGER->findImage("BaseType2")->getWidth(), IMAGEMANAGER->findImage("BaseType2")->getHeight(), "BaseType2", 1.5f, 1.0f);
	UIMANAGER->GetGameFrame()->AddFrame(checkSell);

	UIText* checkText = new UIText();
	checkText->init("text", 20, 15, 300, 200, "", FONT::PIX, WORDSIZE::WS_MIDDLE);
	checkSell->AddFrame(checkText);

	UIFrame* checkOK = new UIFrame();
	checkOK->init("yes", 110, 138, 113, 45, "YesOrNo", 0.9f, 0.9f);
	checkSell->AddFrame(checkOK);

	UIText* YES = new UIText();
	YES->init("text", 0, 10, 113 * 0.9f, 30, "��", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_MIDDLE);
	checkOK->AddFrame(YES);

	UIFrame* checkNo = new UIFrame();
	checkNo->init("no", 215, 138, 113, 45, "YesOrNo", 0.9f, 0.9f);
	checkSell->AddFrame(checkNo);

	UIText* NO = new UIText();
	NO->init("text", 0, 10, 113 * 0.9f, 30, "�ƴϿ�", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_MIDDLE);
	checkNo->AddFrame(NO);

	checkSell->SetIsViewing(false);
	shopBase->SetIsViewing(false);
}

void gameScene::CharUIInit()
{
	UIFrame* charFrame = new UIFrame();
	charFrame->init("charFrame", 50, 250, IMAGEMANAGER->findImage("Base")->getWidth() * 2.0f, IMAGEMANAGER->findImage("Base")->getHeight() * 2.0f, "Base", 2.0f, 2.0f);
	UIMANAGER->GetGameFrame()->AddFrame(charFrame);

	UIText* statusText = new UIText();
	statusText->init("statusText", 80, 20, 300, 100, "STATUS", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE);
	charFrame->AddFrame(statusText);

	UIFrame* powerImg = new UIFrame();
	powerImg->init("powerImg", 20, 60, 63, 63, "Stat_Power", 0.8f, 0.8f);
	charFrame->AddFrame(powerImg);

	UIText* powerText = new UIText();
	powerText->init("powerText", 80, 77, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(powerText);

	UIFrame* defImg = new UIFrame();
	defImg->init("defImg", 20, 120, 63, 63, "Stat_Def", 0.8f, 0.8f);
	charFrame->AddFrame(defImg);

	UIText* defText = new UIText();
	defText->init("defText", 80, 137, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(defText);

	UIFrame* toughImg = new UIFrame();
	toughImg->init("toughImg", 125, 120, 63, 63, "Stat_Tough", 0.8f, 0.8f);
	charFrame->AddFrame(toughImg);

	UIText* toughText = new UIText();
	toughText->init("toughText", 185, 137, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(toughText);

	UIFrame* blockImg = new UIFrame();
	blockImg->init("blockImg", 230, 120, 63, 63, "Stat_Block", 0.8f, 0.8f);
	charFrame->AddFrame(blockImg);

	UIText* blockText = new UIText();
	blockText->init("blockText", 290, 137, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(blockText);

	UIFrame* criImg = new UIFrame();
	criImg->init("criImg", 20, 180, 63, 63, "Stat_Critical", 0.8f, 0.8f);
	charFrame->AddFrame(criImg);

	UIText* criText = new UIText();
	criText->init("criText", 80, 197, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(criText);

	UIFrame* criDmgImg = new UIFrame();
	criDmgImg->init("criDmgImg", 125, 180, 63, 63, "Stat_CriticalDmg", 0.8f, 0.8f);
	charFrame->AddFrame(criDmgImg);

	UIText* criDmgText = new UIText();
	criDmgText->init("criDmgText", 185, 197, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(criDmgText);

	UIFrame* evadeImg = new UIFrame();
	evadeImg->init("evadeImg", 230, 180, 63, 63, "Stat_Evade", 0.8f, 0.8f);
	charFrame->AddFrame(evadeImg);

	UIText* evadeText = new UIText();
	evadeText->init("evadeText", 290, 197, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(evadeText);

	UIFrame* moveSpeedImg = new UIFrame();
	moveSpeedImg->init("moveSpeedImg", 20, 240, 63, 63, "Stat_MoveSpeed", 0.8f, 0.8f);
	charFrame->AddFrame(moveSpeedImg);

	UIText* moveSpeedText = new UIText();
	moveSpeedText->init("moveSpeedText", 80, 257, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(moveSpeedText);

	UIFrame* atkSpeedImg = new UIFrame();
	atkSpeedImg->init("atkSpeedImg", 125, 240, 63, 63, "Stat_AtkSpeed", 0.8f, 0.8f);
	charFrame->AddFrame(atkSpeedImg);

	UIText* atkSpeedText = new UIText();
	atkSpeedText->init("atkSpeedText", 185, 257, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(atkSpeedText);

	UIFrame* reloadImg = new UIFrame();
	reloadImg->init("reloadImg", 230, 240, 63, 63, "Stat_Reload", 0.8f, 0.8f);
	charFrame->AddFrame(reloadImg);

	UIText* reloadText = new UIText();
	reloadText->init("reloadText", 290, 257, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(reloadText);

	UIFrame* dashImg = new UIFrame();
	dashImg->init("dashImg", 20, 300, 63, 63, "Stat_Dash", 0.8f, 0.8f);
	charFrame->AddFrame(dashImg);

	UIText* dashText = new UIText();
	dashText->init("dashText", 80, 317, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(dashText);

	UIFrame* trueDamageImg = new UIFrame();
	trueDamageImg->init("trueDamageImg", 125, 300, 63, 63, "Stat_TrueDamage", 0.8f, 0.8f);
	charFrame->AddFrame(trueDamageImg);

	UIText* trueDamageText = new UIText();
	trueDamageText->init("trueDamageText", 185, 317, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(trueDamageText);

	UIFrame* burnImg = new UIFrame();
	burnImg->init("burnImg", 335, 120, 51, 51, "Stat_Burn", 0.8f, 0.8f);
	charFrame->AddFrame(burnImg);

	UIText* burnText = new UIText();
	burnText->init("burnText", 387, 132, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(burnText);

	UIFrame* poisonImg = new UIFrame();
	poisonImg->init("poisonImg", 335, 170, 51, 51, "Stat_Poison", 0.8f, 0.8f);
	charFrame->AddFrame(poisonImg);

	UIText* poisonText = new UIText();
	poisonText->init("poisonText", 387, 182, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(poisonText);

	UIFrame* coldImg = new UIFrame();
	coldImg->init("coldImg", 335, 220, 51, 51, "Stat_Cold", 0.8f, 0.8f);
	charFrame->AddFrame(coldImg);

	UIText* coldText = new UIText();
	coldText->init("coldText", 387, 232, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(coldText);

	UIFrame* elecImg = new UIFrame();
	elecImg->init("elecImg", 335, 270, 51, 51, "Stat_Shock", 0.8f, 0.8f);
	charFrame->AddFrame(elecImg);

	UIText* elecText = new UIText();
	elecText->init("elecText", 387, 282, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(elecText);

	UIFrame* stunImg = new UIFrame();
	stunImg->init("stunImg", 335, 320, 51, 51, "Stat_Stun", 0.8f, 0.8f);
	charFrame->AddFrame(stunImg);

	UIText* stunText = new UIText();
	stunText->init("stunText", 387, 332, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(stunText);

	UIImage* tooltipFrame = new UIImage();
	tooltipFrame->init("toolTipFrame", 0, 0, 50, 50, "ToolTipCover", false, 0, 0, 1.0f, 1.0f, 80);
	charFrame->AddFrame(tooltipFrame);

	UIText* tooltipTitle = new UIText();
	tooltipTitle->init("title", 10, 10, 270, 120, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_LEFT, RGB(255, 238, 184));
	tooltipFrame->AddFrame(tooltipTitle);

	UIText* tooltipDiscript = new UIText();
	tooltipDiscript->init("discription", 10, 60, 270, 150, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	tooltipFrame->AddFrame(tooltipDiscript);

	UIText* tooltipGray = new UIText();
	tooltipGray->init("additional", 10, 130, 270, 150, "", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(170, 170, 170));
	tooltipFrame->AddFrame(tooltipGray);

	charFrame->SetIsViewing(false);
}

void gameScene::BossHpUIInit()
{
	UIFrame* BossLifeBackImg = new UIFrame();
	BossLifeBackImg->init("BossLifeBack", WINSIZEX / 2 - 300, WINSIZEY - 80, IMAGEMANAGER->findImage("BossLifeBack")->getWidth(), IMAGEMANAGER->findImage("BossLifeBack")->getHeight(), "BossLifeBack");
	UIMANAGER->GetGameFrame()->AddFrame(BossLifeBackImg);

	UIProgressBar* BossLifeImg = new UIProgressBar();
	BossLifeImg->init("BossLife", 106, 0, IMAGEMANAGER->findImage("BossLife")->getWidth(), IMAGEMANAGER->findImage("BossLife")->getHeight(), "BossLife", "");
	BossLifeBackImg->AddFrame(BossLifeImg);
	
	UIFrame* BossLifeBaseImg = new UIFrame();
	BossLifeBaseImg->init("BossLifeBase", -106, 0, IMAGEMANAGER->findImage("BossLifeBase")->getWidth(), IMAGEMANAGER->findImage("BossLifeBase")->getHeight(), "BossLifeBase");
	BossLifeImg->AddFrame(BossLifeBaseImg);

	BossLifeBackImg->SetIsViewing(false);
}

void gameScene::release()
{
	if (ENTITYMANAGER != nullptr)
	{
		ENTITYMANAGER->release();
		ENTITYMANAGER->releaseSingleton();
	}

	if (MAPMANAGER != nullptr)
	{
		MAPMANAGER->release();
		MAPMANAGER->releaseSingleton();
	}

	if (EFFECTMANAGER != nullptr)
	{
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
	}

	if (PARTICLEMANAGER != nullptr)
	{
		PARTICLEMANAGER->release();
		PARTICLEMANAGER->releaseSingleton();
	}

	if (UIMANAGER != nullptr)
	{
		UIMANAGER->release();
		UIMANAGER->releaseSingleton();
	}
}


void gameScene::UpdateWardrobeUI()
{
	if (INPUT->GetKeyDown('P'))
	{
		UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->ToggleIsViewing();
		for (int i = 0; i < 13; i++)
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
		}
	}

	if (UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetIsViewing() == true)
	{
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetRect(), _ptMouse) && INPUT->GetKey(VK_LBUTTON))
		{
			_scrollTimer++;
			if (_scrollTimer == 1)
			{
				_mouseLocation = _ptMouse.x;
			}

			else if (_scrollTimer > 1)
			{
				for (int i = 0; i < 13; i++)
				{
					UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeBack" + to_string(i))->MoveFrameChild(_ptMouse.x - _mouseLocation, 0);
					UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->MoveFrameChild(_ptMouse.x - _mouseLocation, 0);
					UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->MoveFrameChild(_ptMouse.x - _mouseLocation, 0);
				}
				_mouseLocation = _ptMouse.x;
			}
		}

		if (INPUT->GetIsLButtonUp())
		{
			_scrollTimer = 0;
			_mouseLocation = 0;
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
		for (int i = 0; i < 13; i++)
		{
			if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->GetRect(), _ptMouse) && INPUT->GetIsRButtonClicked())
			{
				// ���°�

				int curHp = ENTITYMANAGER->getPlayer()->GetHP();
				image* curIg = ENTITYMANAGER->getPlayer()->GetImage(0);

				if (curIg == IMAGEMANAGER->findImage("sheetingIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetDefence(ENTITYMANAGER->getPlayer()->GetDefence() - 10);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() + 10);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
				}
				else if (curIg == IMAGEMANAGER->findImage("gunmanIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetDefence(ENTITYMANAGER->getPlayer()->GetDefence() + 15);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() + 15);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
				}
				else if (curIg == IMAGEMANAGER->findImage("aliceIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetPower(ENTITYMANAGER->getPlayer()->GetPower() - 40);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() + 30);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
				}
				else if (curIg == IMAGEMANAGER->findImage("redlotusIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() + 15);
					ENTITYMANAGER->getPlayer()->SetEvasion(ENTITYMANAGER->getPlayer()->GetEvasion() + 5);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
				}
				else if (curIg == IMAGEMANAGER->findImage("lkinabearIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetDefence(ENTITYMANAGER->getPlayer()->GetDefence() + 5);
					ENTITYMANAGER->getPlayer()->SetPower(ENTITYMANAGER->getPlayer()->GetPower() + 20);
				}
				else if (curIg == IMAGEMANAGER->findImage("riderHIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetMoveSpeedPer(ENTITYMANAGER->getPlayer()->GetMoveSpeedPer() - 22);
					ENTITYMANAGER->getPlayer()->SetToughness(ENTITYMANAGER->getPlayer()->GetToughness() + 2);
				}
				else if (curIg == IMAGEMANAGER->findImage("criminalldle"))
				{
					ENTITYMANAGER->getPlayer()->SetEvasion(ENTITYMANAGER->getPlayer()->GetEvasion() + 12);
				}
				else if (curIg == IMAGEMANAGER->findImage("pickIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetCriDamage(ENTITYMANAGER->getPlayer()->GetCriDamage() + 25);
					ENTITYMANAGER->getPlayer()->SubMaxDash();
				}
				else if (curIg == IMAGEMANAGER->findImage("fastoIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetMoveSpeedPer(ENTITYMANAGER->getPlayer()->GetMoveSpeedPer() + 20);
					ENTITYMANAGER->getPlayer()->SetAtkSpeedPer(ENTITYMANAGER->getPlayer()->GetAtkSpeedPer() + 10);
				}

				else if (curIg == IMAGEMANAGER->findImage("horsemanIdle"))
				{
					/*
					ENTITYMANAGER->getPlayer()->SetInitHp(100);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					*/
				}

				else if (curIg == IMAGEMANAGER->findImage("humanlasleyIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() + 45);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
				}
				else if (curIg == IMAGEMANAGER->findImage("masterchefIdle"))
				{
					ENTITYMANAGER->getPlayer()->SetFireAccuracy(ENTITYMANAGER->getPlayer()->GetFireAccuracy() - 33);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() + 33);
					curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
				}


				// �Դ°�
				switch (i)
				{
				case 0:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("baseCharIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("baseCharRun"));
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 1:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("sheetingIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("sheetingRun"));
					ENTITYMANAGER->getPlayer()->SetDefence(ENTITYMANAGER->getPlayer()->GetDefence() + 10);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() - 10);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 2:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("gunmanIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("gunmanRun"));
					ENTITYMANAGER->getPlayer()->SetDefence(ENTITYMANAGER->getPlayer()->GetDefence() - 15);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() - 15);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp()) 
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 3:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("aliceIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("aliceRun"));
					ENTITYMANAGER->getPlayer()->SetPower(ENTITYMANAGER->getPlayer()->GetPower() + 40);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() - 30);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp()) 
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 4:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("redlotusIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("redlotusRun"));
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() - 15);
					ENTITYMANAGER->getPlayer()->SetEvasion(ENTITYMANAGER->getPlayer()->GetEvasion() - 5);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 5:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("lkinabearIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("lkinabearRun"));
					ENTITYMANAGER->getPlayer()->SetDefence(ENTITYMANAGER->getPlayer()->GetDefence() - 5);
					ENTITYMANAGER->getPlayer()->SetPower(ENTITYMANAGER->getPlayer()->GetPower() - 20);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 6:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("riderHIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("riderHRun"));
					ENTITYMANAGER->getPlayer()->SetMoveSpeed(ENTITYMANAGER->getPlayer()->GetMoveSpeed() + 22);
					ENTITYMANAGER->getPlayer()->SetToughness(ENTITYMANAGER->getPlayer()->GetToughness() - 2);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 7:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("criminalldle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("criminalRun"));
					ENTITYMANAGER->getPlayer()->SetEvasion(ENTITYMANAGER->getPlayer()->GetEvasion() - 12);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 8:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("pickIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("pickRun"));
					ENTITYMANAGER->getPlayer()->SetCriDamage(ENTITYMANAGER->getPlayer()->GetCriDamage() - 25);
					ENTITYMANAGER->getPlayer()->AddMaxDash();
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 9:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("fastoIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("fastoRun"));
					ENTITYMANAGER->getPlayer()->SetMoveSpeed(ENTITYMANAGER->getPlayer()->GetMoveSpeed() - 20);
					ENTITYMANAGER->getPlayer()->SetAtkSpeed(ENTITYMANAGER->getPlayer()->GetAtkSpeed() - 10);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 10:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("horsemanIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("horsemanRun"));
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 11:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("humanlasleyIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("humanlasleyRun"));
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() - 45);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp())
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;
				case 12:
					ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("masterchefIdle"));
					ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("masterchefRun"));
					ENTITYMANAGER->getPlayer()->SetFireAccuracy(ENTITYMANAGER->getPlayer()->GetFireAccuracy() + 33);
					ENTITYMANAGER->getPlayer()->SetInitHp(ENTITYMANAGER->getPlayer()->GetInitHp() - 33);
					if (curHp > ENTITYMANAGER->getPlayer()->GetInitHp()) 
						curHp = ENTITYMANAGER->getPlayer()->GetInitHp();
					ENTITYMANAGER->getPlayer()->SetHp(curHp);
					break;

				default:
					break;
				}
			}
		}
	}
}

void gameScene::update()
{
	SOUNDMANAGER->update();
	CAMERAMANAGER->update();
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

	UpdateWardrobeUI();

	if (INPUT->GetKeyDown('V'))
	{
		SOUNDMANAGER->play("�κ��丮����");
		UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->ToggleIsViewing();
	}

	if (INPUT->GetKeyDown('C'))
	{
		SOUNDMANAGER->play("�κ��丮����");
		UIMANAGER->GetGameFrame()->GetChild("charFrame")->ToggleIsViewing();
	}

	if (INPUT->GetKeyDown('O'))
	{
		SOUNDMANAGER->play("�κ��丮����");
		UIMANAGER->GetGameFrame()->GetChild("allTraitFrame")->ToggleIsViewing();
		ENTITYMANAGER->getPlayer()->ReInitTraitUI();
	}
}

void gameScene::render()
{
	MAPMANAGER->render(getMemDC());
	UIMANAGER->render(getMemDC());

	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));

	IMAGEMANAGER->findImage("ShootingCursor2")->stretchRender(getMemDC(), _ptMouse.x - 22, _ptMouse.y - 22, 0.8f, 0.8f);

	string n = to_string((int)CAMERAMANAGER->GetAbsoluteX(_ptMouse.x)) + " " + to_string((int)CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));

	// TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, n.c_str(), n.length());

	if (MAPMANAGER->GetStageChanger()->GetIsChangingStage())
	{
		MAPMANAGER->GetStageChanger()->render(getMemDC());
	}
}


void gameScene::doubleClick()
{
	if (_clicked)
	{
		_clickTimer++;
		if (_clickTimer > 10)
		{
			_clickTimer = 0;
			_clicked = false;
		}
	}
	if (INPUT->GetIsLButtonClicked())
	{
		if (!_clicked)
		{
			for (int i = 0; i < 13; i++)
			{
				UIFrame* clickFrame = UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i));

				if (PtInRect(&clickFrame->GetRect(), _ptMouse))
				{
					_clickTimer = 0;
					_clicked = false;
				}
			}
		}
	}
}


#include "stdafx.h"
#include "Restaurant.h"

HRESULT Restaurant::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	_exitRect = RectMake(WINSIZEX - 120, 30, 66 * 1.4, 57 * 1.4);

	_npcName = "ȣ����ī";
	_vConvTexts = vector<string>
	{
		"������ � �丮�� ��÷� ���̳���?"
	};
	_vSelectTexts = vector<string>
	{
		"������",
		"�ƹ��͵�"
	};

	_useConv = true;
	_useSelect = true;

	return S_OK;
}

void Restaurant::update()
{
	NPC::update();

	if (_selectFrame->GetIsViewing())
	{
		Conversation();
	}
}

void Restaurant::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);

			this->Activate();
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

void Restaurant::release()
{
	NPC::release();
}

void Restaurant::render(HDC hdc)
{
	NPC::render(hdc);
	CAMERAMANAGER->Rectangle(hdc, _exitRect);
}

void Restaurant::Activate()
{
	NPC::Activate();
	ReNewUI();
}

void Restaurant::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");

	//_restaurantBase = UIMANAGER->GetGameFrame()->GetChild("ScreenCover");
	//_restaurantLabel = UIMANAGER->GetGameFrame()->GetChild("Label");
	//_restaurantFoodBase = UIMANAGER->GetGameFrame()->GetChild("RestaurantTable");
	//_wholeFoodFrame = UIMANAGER->GetGameFrame()->GetChild("Base_0");
	//_foodFrameSelected = UIMANAGER->GetGameFrame()->GetChild("RestaurantMenu_Withoutmoney_Selected");
	//_exit = UIMANAGER->GetGameFrame()->GetChild("Xbutton");
	//_satiation = UIMANAGER->GetGameFrame()->GetChild("restaurantSatiation");
}

void Restaurant::SetRestaurantFood()
{
	//_vFoodName = vector<string>{ "��� ������", "���� ����", "�𷰽� ����", "�ſ� �ҽ� ��Ʈ��", "�ſ� ġŲ ��Ʃ", "��", "��ä ��� ����", "���� ���� ��",
	//	"���� ����", "�ϵ��� ����", "�丶�����", "�׸��� �� ���ɷ�", "���� ����", "����� ��Ű", "�����̵�", "����", "�̳�Ÿ��罺 ������ũ", "�����", 
	//	"���� Ƣ��" "�ó��� ��", "���� �ҽ� ��Ʈ��", "��� ����", "���ݸ� ��Ű", "�޺���̼� ����", "Ư�� ��� �丮", "���� ����", "ź���" };

	//_vFoodFirstStat = vector<string>{ "�� +7 ����","�� +12 ũ��Ƽ�� ������","�� +15 ����","�� +27 ����","�� +11 ����","�� +8 ����","�� +12 ����","",
	//	"�� +7 ����","�� +8 ����", "�� +10 ����","�� +13 ����","�� +1 �뽬 Ƚ��", "�� +3 ���� ������", "�� +33% ���� �ӵ�", "�� +33% ������ �ӵ�",
	//	"�� ���� ���� �� 10s ���� ���� 50 ���� (���� ���ð� 35s)", "�� �������� ������ HP�� ��Ȱ", "�� �׼����� ���� 1�� �߰�", "�� +7 ����",
	//	"�� +20% �̵� �ӵ�", "�� +20 ����", "�� +30 �ִ� ü��", "�� ��� ȹ�� �ø��� �߰��� 4 ��带 �� ȹ��", "�� +45% ũ��Ƽ�� ������",
	//	"�� +3 ������", "�� ���ο� ������ �̵��� ������ �پ��� ������ +1", "�� -20 ������ ����" };

	//_vFoodSecondStat = vector<string>{ "�� +11 �ִ� ü��","�� +10 ũ��Ƽ�� ������","�� +12 �ִ� ü��", " ","�� +13 ����","�� +10 ����","�� +12 �ִ� ü��",
	//	"�� +12 ����", "�� +9% �ִ� ü��","�� +7 ȸ��","�� +9 ũ��Ƽ��"," ", "�� +7 ����", " ", " ", "�� +7 ����", " ", "�� +7 ����", "�� +11 ũ��Ƽ��", 
	//	"�� +12% ���� �ӵ�", "�� +5 ����" , " ", "�� +7 ����" , " ", " ", " ", " " };

	//_vFoodThirdStat = vector<string>{ " ","�� +8 ũ��Ƽ��","�� +6 ����"," ","�� +7 ȸ��"," ","�� +12 ũ��Ƽ��","�� +12 ũ��Ƽ��", " "," "," "," ", " "," ",
	//	" "," "," ","�� +7 �ִ� ü��", "�� +2 ������, +2 ���� ������" , "�� +12% ������ �ӵ�", "�� +5 ũ��Ƽ��, +5 ȸ��", " ", " ", " ", " ", " ", " " };

	_vFoodName = vector<string>{ "�ϵ��� ����", "�ſ� ġŲ ��Ʃ", "�𷰽� ����" };
	_vFoodFirstStat = vector<string>{ "�� +12 ����", "�� +10 ����", "�� +15 ����" };
	_vFoodSecondStat = vector<string>{ "�� +5 ȸ��", "�� +3 ����", "�� +7 �ִ� ü��" };
	_vFoodThirdStat = vector<string>{ "", "�� +5 ȸ��", "�� +5 ����" };

	_vFoodHeal = vector<string>{ "12%", "12%", "12%" };
	_vFoodSatiation = vector<string>{ "59", "58", "64" };
	_vFoodPrice = vector<string>{ "550", "610", "610" };
}

void Restaurant::BuyFood()
{
	ENTITYMANAGER->getPlayer()->GetMoney();

	switch (_food)
	{
	case F_SOUP:
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - 550);
		break;
	case F_STEW:
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - 610);
		break;
	case F_BURGER:
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - 610);
		break;
	default:
		break;
	}
}

void Restaurant::ReNewUI()
{
	UIImage* _restaurantBase = new UIImage();
	_restaurantBase->init("restaurantBase", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", true, 0, 0, 10.0f, 10.0f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantBase);

	UIImage* _restaurantLabel = new UIImage();
	_restaurantLabel->init("restaurantLabel", 0, 0, 960, 96, "Label", true, 0, 0, 1.5f, 1.5f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantLabel);

	UIImage* _restaurantFoodBase = new UIImage();
	_restaurantFoodBase->init("restaurantFoodBase", WINSIZEX / 2 - 100, 150, 1719, 390, "RestaurantTable", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantFoodBase);

	UIImage* _wholeFoodFrame = new UIImage();
	_wholeFoodFrame->init("wholeFoodFrame", 50, 150, 333, 396, "Base_0", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_wholeFoodFrame);

	UIImage* _exit = new UIImage();
	_exit->init("wholeFoodFrame", WINSIZEX - 120, 30, 66, 57, "Xbutton", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_exit);

	UIImage* _satiation = new UIImage();
	_satiation->init("satiation", 50, WINSIZEY - 85, 333, 51, "restaurantSatiation", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_satiation);

	UIImage* _foodIcon = new UIImage();
	_foodIcon->init("foodIcon", 75, WINSIZEY - 77, 51, 42, "FoodIcon", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_foodIcon);

	UIImage* _money = new UIImage();
	_money->init("money", WINSIZEX - 300, WINSIZEY - 90, 200, 51, "restaurantMoney", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_money);

	UIText* moneyText = new UIText();
	moneyText->init("moneyText", WINSIZEX - 220, WINSIZEY - 72, 120, 30, "10000", FONT::PIX, WORDSIZE::WS_BIG);
	UIMANAGER->GetGameFrame()->AddFrame(moneyText);

	UIText* satiationText = new UIText();
	satiationText->init("satiationText", 250, WINSIZEY - 68, 500, 30, " 0 / 150 ", FONT::PIX, WORDSIZE::WS_BIG);
	UIMANAGER->GetGameFrame()->AddFrame(satiationText);

	for (int i = 0; i < 3; i++)
	{
		UIImage* _foodFrame = new UIImage();
		_foodFrame->init("foodFrame", 68, 170 + i * 165, 297, 114, "RestaurantMenu_Withoutmoney", true, 0, 0, 1.45f, 1.4f);
		UIMANAGER->GetGameFrame()->AddFrame(_foodFrame);
	}
}
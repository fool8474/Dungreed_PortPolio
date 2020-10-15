#include "stdafx.h"
#include "Restaurant.h"

HRESULT Restaurant::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_frameX, _frameY = _frameTimer = 0;

	//_foodFrameSelected = UIMANAGER->GetGameFrame()->GetChild("RestaurantMenu_Withoutmoney_Selected");

	return S_OK;
}

void Restaurant::update()
{
	NPC::update();

	if (_isInteracting && INPUT->GetKeyDown('F'))
	{
		this->Activate();
	}
}

void Restaurant::release()
{
	NPC::release();
}

void Restaurant::render(HDC hdc)
{
	NPC::render(hdc);
}

void Restaurant::Activate()
{
	NPC::Activate();
	ReNewUI();
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

}

void Restaurant::BuyFood()
{
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

	for (int i = 0; i < 3; i++)
	{
		UIImage* _foodFrame = new UIImage();
		_foodFrame->init("foodFrame", 68, 170 + i * 165, 297, 114, "RestaurantMenu_Withoutmoney", true, 0, 0, 1.45f, 1.4f);
		UIMANAGER->GetGameFrame()->AddFrame(_foodFrame);
	}
}
#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	_loading = new Loading();
	_loading->init();

	SOUNDMANAGER->init();
	SOUNDMANAGER->addSound("��Ʈ�� ����", "Sounds/Effect/��Ʈ�� ����.wav", false, false);
	SOUNDMANAGER->play("��Ʈ�� ����");

	IMAGEMANAGER->addImage("loadingBarFront", "loadingBarFront.bmp", 620, 200);
	IMAGEMANAGER->addImage("loadingBarBack", "loadingBarBack.bmp", 620, 200);

	_background = IMAGEMANAGER->addFrameImage("bgLoadingScene", "Images/LOADING.bmp", WINSIZEX * 6, WINSIZEY, 6, 1);
	_loadingBar = new progressBar;
	_currentGauge = 0;

	_loadingBar->init("loadingBarFront", "loadingBarBack");
	_loadingBar->setPos(410, 210);

	this->loadingImage();
	this->loadingSound();
	this->loadingFont();
	return S_OK;
}

void loadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	SOUNDMANAGER->update();

	_loading->update();
	_loadingBar->update();
	this->animation();

	// �̹��� �ε尡 �Ϸ�Ǹ� �̵�
	if (_currentGauge >= _loading->GetLoadItem().size())
	{
		LoadData();
		SCENEMANAGER->loadScene("����ȭ��");
	}
	
	// �ƴ϶�� ����ؼ� �ҷ�����
	else
	{
		for (int i = 0; i < 12; i++)
		{
			LoadItem* item = _loading->GetLoadItem()[_currentGauge];
			_loading->LoadingDone(item);
			_currentGauge++;
			if (_currentGauge >= _loading->GetLoadItem().size()) break;
		}
		_loadingBar->setGauge(_loading->GetLoadItem().size(), _currentGauge);
	}
}

void loadingScene::render()
{
	_loading->render();

	_loadingBar->render();
	_background->frameRender(getMemDC(), 0, 0);
	textOut(getMemDC(), _loadingBar->getX() + 250, _loadingBar->getY() + 330, _loading->GetCurKey().c_str(), _loading->GetCurKey().length());

	IMAGEMANAGER->frameRender("number", getMemDC(), 710, 500,(int)((float)_currentGauge /(float)_loading->GetLoadItem().size()*100) % 10, 0);
	if ((int)((float)_currentGauge *(100 / (float)_loading->GetLoadItem().size()) / 10) > 0)
	IMAGEMANAGER->frameRender("number", getMemDC(), 690, 500, (float)_currentGauge *(100/(float)_loading->GetLoadItem().size()) / 10, 0);
}

/// <summary>
/// CSV�����͵��� �ҷ��´�
/// </summary>
void loadingScene::LoadData()
{
	DATAMANAGER->Init();
	DATAMANAGER->GetUIBrushToolGridData();
	DATAMANAGER->GetObjectData();
	DATAMANAGER->GetItemData();
}

/// <summary>
/// �ε�â�� �ִϸ��̼��� �����Ѵ�.
/// </summary>
void loadingScene::animation()
{
	_animationCount++;
	if (_animationCount % 10 == 0)
	{
		_animationFrame++;
		if (_animationFrame > _background->getMaxFrameX())
		{
			_animationFrame = 0;
		}
		_background->setFrameX(_animationFrame);
	}
}

void loadingScene::loadingFont()
{
	AddFontResource("Font/HS�ܿﴫ��ü.ttf");
	AddFontResource("Font/BMYEONSUNG_ttf.ttf");
	AddFontResource("Font/neodgm.ttf");
}

void loadingScene::loadingImage()
{
	// STAGE 1 GRID //
	_loading->LoadNormalImage("Stage1_Tile0", "Images/1Floor/Basic_H_Type2_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile1", "Images/1Floor/Basic_H_Type2_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile2", "Images/1Floor/Basic_H_Type2_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile3", "Images/1Floor/Basic_H_Type2_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile4", "Images/1Floor/Basic_H_Type2_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile5", "Images/1Floor/Basic_H_Type2_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile6", "Images/1Floor/Basic_H_Type2_6.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile7", "Images/1Floor/Basic_H_Type2_7.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile8", "Images/1Floor/Basic_H_Type2_8.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile9", "Images/1Floor/BasicStone_BottomCenter.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile10", "Images/1Floor/BasicStone_TopCenter_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile11", "Images/1Floor/BasicStone_TopCenter_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile12", "Images/1Floor/1FloorTileLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile13", "Images/1Floor/1FloorTileMiddle.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile14", "Images/1Floor/1FloorTileRight.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile15", "Images/1Floor/Tile_H1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile16", "Images/1Floor/Tile_H3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile17", "Images/1Floor/Tile_H4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile18", "Images/1Floor/Tile_H5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile19", "Images/1Floor/Tile_H7.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile20", "Images/1Floor/Tile_H9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile21", "Images/1Floor/Tile_H10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile22", "Images/1Floor/Tile_H11.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile23", "Images/1Floor/Tile_H12.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile24", "Images/1Floor/Tile_H14.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile25", "Images/1Floor/Tile_Marble_Stair_BottomLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile26", "Images/1Floor/Tile_Marble_Stair_BottomRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile27", "Images/1Floor/Tile_Marble_Stair_TopLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile28", "Images/1Floor/Tile_Marble_Stair_TopRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile29", "Images/1Floor/Tile_Stair_BottomLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile30", "Images/1Floor/Tile_Stair_BottomRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile31", "Images/1Floor/Tile_Stair_TopLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile32", "Images/1Floor/Tile_Stair_TopRight.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile33", "Images/1Floor/Tile_Slim_Bottom.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile34", "Images/1Floor/Tile_Slim_BottomCenter.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile35", "Images/1Floor/Tile_Slim_Left.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile36", "Images/1Floor/Tile_Slim_MiddleRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile37", "Images/1Floor/Tile_Slim_Right.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile38", "Images/1Floor/Tile_Slim_Top.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile39", "Images/1Floor/Wall_Basic_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile40", "Images/1Floor/Wall_Basic_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile41", "Images/1Floor/Wall_Basic_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile42", "Images/1Floor/Wall_Basic_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile43", "Images/1Floor/Wall_Basic_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile44", "Images/1Floor/Wall_Basic_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile45", "Images/1Floor/Wall_Basic_12.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile46", "Images/1Floor/Wall_Basic_13.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile47", "Images/1Floor/Wall_Basic_14.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile48", "Images/1Floor/Wall_Basic_6.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile49", "Images/1Floor/Wall_Basic_8.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile50", "Images/1Floor/Wall_Basic_15.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile51", "Images/1Floor/Wall_Basic_16.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile52", "Images/1Floor/Wall_Basic_9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile53", "Images/1Floor/Wall_Basic_10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile54", "Images/1Floor/Wall_Basic_11.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile55", "Images/1Floor/Wall_Basic_Ceiling_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile56", "Images/1Floor/Wall_Basic_Ceiling_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile57", "Images/1Floor/Wall_Basic_Ceiling_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile58", "Images/1Floor/Wall_Basic_Ceiling_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile59", "Images/1Floor/Wall_Basic_Ceiling_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile60", "Images/1Floor/Wall_Basic_Ceiling_5.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile61", "Images/1Floor/Wall_Type2_StairLeft.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile62", "Images/1Floor/Wall_Cracked_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile63", "Images/1Floor/Wall_Cracked_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile64", "Images/1Floor/Wall_Cracked_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile65", "Images/1Floor/Wall_Cracked_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile66", "Images/1Floor/Wall_Cracked_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile67", "Images/1Floor/Wall_Cracked_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile68", "Images/1Floor/Wall_Cracked_6.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile69", "Images/1Floor/Wall_H0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile70", "Images/1Floor/Wall_H1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile71", "Images/1Floor/Wall_H2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile72", "Images/1Floor/Wall_H3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile73", "Images/1Floor/Wall_H4_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile74", "Images/1Floor/Wall_H4_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile75", "Images/1Floor/Wall_H6.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile76", "Images/1Floor/Wall_H8.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile77", "Images/1Floor/Wall_H9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile78", "Images/1Floor/Wall_H10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile79", "Images/1Floor/Wall_H11.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile80", "Images/1Floor/Wall_H12.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile81", "Images/1Floor/Cave_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile82", "Images/1Floor/Cave_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile83", "Images/1Floor/Ceil_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile84", "Images/1Floor/Ceil_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile85", "Images/1Floor/Ceil_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile86", "Images/1Floor/Ceil_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile87", "Images/1Floor/Pillar_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile88", "Images/1Floor/Pillar_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile89", "Images/1Floor/Pillar_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile90", "Images/1Floor/Pillar_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile91", "Images/1Floor/Pillar_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile92", "Images/1Floor/Pillar_6.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile93", "Images/1Floor/Wall_Chain_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile94", "Images/1Floor/Wall_Chain_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile95", "Images/1Floor/Wall_Basic_Statue_Bottom_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile96", "Images/1Floor/Wall_Basic_Statue_Bottom_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile97", "Images/1Floor/Wall_Basic_Statue_Bottom_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile98", "Images/1Floor/Wall_Basic_Statue_Bottom_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile99", "Images/1Floor/Wall_Sewer_Botom.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile100", "Images/1Floor/Wall_Sewer_Botom_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile101", "Images/1Floor/Wall_Sewer_Round_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile102", "Images/1Floor/Wall_Sewer_Round_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile103", "Images/1Floor/Wall_Sewer_Round_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile104", "Images/1Floor/Wall_Sewer_Round_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile105", "Images/1Floor/wallLeft_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile106", "Images/1Floor/wallLeft_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile107", "Images/1Floor/wallLeft_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile108", "Images/1Floor/wallLeft_4.bmp", 48, 48, true, RGB(255, 0, 255));

	// STAGE ALL GRID //
	_loading->LoadNormalImage("HivePlarformTile", "Images/AllFloor/HivePlarformTile.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OneWayPlatform", "Images/AllFloor/OneWayPlatform.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_0", "Images/AllFloor/SecondFloor_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_1", "Images/AllFloor/SecondFloor_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_2", "Images/AllFloor/SecondFloor_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_3", "Images/AllFloor/SecondFloor_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_0", "Images/AllFloor/WoodenBridge_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_1", "Images/AllFloor/WoodenBridge_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_2", "Images/AllFloor/WoodenBridge_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_3", "Images/AllFloor/WoodenBridge_3.bmp", 48, 48, true, RGB(255, 0, 255));


	// OBJECT //
	_loading->LoadNormalImage("BigBox0", "Images/Object/BigBox0.bmp", 69, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Bone0", "Images/Object/Bone0.bmp", 36, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Bone1", "Images/Object/Bone1.bmp", 42, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Box0", "Images/Object/Box0.bmp", 48, 36, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrum0", "Images/Object/OakDrum0.bmp", 39, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Skull0", "Images/1Floor/Skull0.bmp", 30, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Skull1", "Images/1Floor/Skull1.bmp", 45, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stone_1", "Images/AllFloor/Stone_1.bmp", 60, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stone_2", "Images/AllFloor/Stone_2.bmp", 60, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stone_3", "Images/AllFloor/Stone_3.bmp", 60, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Table0", "Images/AllFloor/Table0.bmp", 135, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable_0", "Images/AllFloor/TortureTable_0.bmp", 135, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable_1", "Images/AllFloor/TortureTable_1.bmp", 135, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable1_0", "Images/AllFloor/TortureTable1_0.bmp", 33, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable1_1", "Images/AllFloor/TortureTable1_1.bmp", 42, 18, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Down", "Images/Object/Door_Down.bmp", 4416, 58, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Up", "Images/Object/Door_Up.bmp", 4416, 58, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Left", "Images/Object/Door_Left.bmp", 1656, 240, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Right", "Images/Object/Door_Right.bmp", 1656, 240, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Down_Idle", "Images/Object/Door_Down_Idle.bmp", 192, 58, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Up_Idle", "Images/Object/Door_Up_Idle.bmp", 192, 58, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Left_Idle", "Images/Object/Door_Left_Idle.bmp", 72, 240, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Right_Idle", "Images/Object/Door_Right_Idle.bmp", 72, 240, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TrainingSchool", "Images/Object/TrainingSchool.bmp", 810, 231, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GoldCoin", "Images/Object/GoldCoin.bmp", 168, 21, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Bullion", "Images/Object/Bullion.bmp", 420, 27, 7, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FairyL00", "Images/Object/FairyL00.bmp", 1152, 75, 16, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FairyM00", "Images/Object/FairyM00.bmp", 960, 60, 16, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FairyS00", "Images/Object/FairyS00.bmp", 432, 33, 16, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FairyXL00", "Images/Object/FairyXL00.bmp", 1440, 90, 16, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GreenFairy00", "Images/Object/GreenFairy00.bmp", 1440, 90, 16, 1, true, RGB(255, 0, 255));

	// STAGE 1 //
	_loading->LoadNormalImage("Door0_Closed", "Images/1Floor/Door0_Closed.bmp", 171, 195, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door0_Open", "Images/1Floor/Door0_Open.bmp", 171, 195, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Torch0", "Images/1Floor/Torch0.bmp", 528, 75, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CandleOff0", "Images/1Floor/CandleOff0.bmp", 15, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CandleOff1", "Images/1Floor/CandleOff1.bmp", 15, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CandleOff2", "Images/1Floor/CandleOff2.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("CandleOn00", "Images/1Floor/CandleOn00.bmp", 90, 45, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("CandleOn10", "Images/1Floor/CandleOn10.bmp", 90, 33, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("CandleOn20", "Images/1Floor/CandleOn20.bmp", 216, 51, 6, 1, true, RGB(255, 0, 255));

	// NPC //
	_loading->LoadFrameImage("StrawberryFountain0", "Images/Object/StrawberryFountain0.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StrawberryFountain1", "Images/Object/StrawberryFountain1.bmp", 96, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WormPassage00", "Images/Object/WormPassage00.bmp", 81, 93, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("WormPassageEat00", "Images/Object/WormPassageEat00.bmp", 648, 93, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("WormPassageIdle00", "Images/Object/WormPassageIdle00.bmp", 729, 93, 9, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("PinkTresureClosed00", "Images/Object/PinkTresureClosed00.bmp", 396, 63, 12, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("PinkTresureOpened00", "Images/Object/PinkTresureOpened00.bmp", 396, 63, 12, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("PinkTresureOpened00", "Images/Object/PinkTresureOpened00.bmp", 396, 63, 12, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RareTresureClosed", "Images/Object/RareTresureClosed.bmp", 93, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RareTresureOpened", "Images/Object/RareTresureOpened.bmp", 93, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("GrayTresureClosed", "Images/Object/GrayTresureClosed.bmp", 63, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("GrayTresureOpen", "Images/Object/GrayTresureOpen.bmp", 63, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StashClosed", "Images/Object/StashClosed.bmp", 84, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StashOpened", "Images/Object/StashOpened.bmp", 84, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("YellowTresureClosed", "Images/Object/YellowTresureClosed.bmp", 117, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("YellowTresureOpened", "Images/Object/YellowTresureOpened.bmp", 117, 69, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_Giant", "Images/NPC/NPC_Giant.bmp", 588, 144, 4, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DungeonIngurgitate", "Images/NPC/DungeonIngurgitate.bmp", 19125, 255, 51, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonInn", "Images/NPC/DungeonInn.bmp", 594, 276, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_NeighboringVillager", "Images/NPC/NPC_NeighboringVillager.bmp", 270, 69, 6, 1, true, RGB(255, 0, 255));

	// FOOD //
	_loading->LoadNormalImage("01_Bread", "Images/food/01_Bread.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("02_FriedEgg", "Images/food/02_FriedEgg.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("03_GrilledMushroom", "Images/food/03_GrilledMushroom.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("04_TamatoSoup", "Images/food/04_TamatoSoup.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("05_OnionSoup", "Images/food/05_OnionSoup.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("06_PeaSoup", "Images/food/06_PeaSoup.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("07_VegetableSalsaSoup", "Images/food/07_VegetableSalsaSoup.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("08_Lemonade", "Images/food/08_Lemonade.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("09_DeluxeBurger", "Images/food/09_DeluxeBurger.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("10_ChocolateCookie", "Images/food/10_ChocolateCookie.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("11_HotChickenStew", "Images/food/11_HotChickenStew.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("12_RaspberryCookie", "Images/food/12_RaspberryCookie.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("13_GriffonEggOmelette", "Images/food/13_GriffonEggOmelette.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("14_GarlicMeatball", "Images/food/14_GarlicMeatball.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("15_Bibimbap", "Images/food/15_Bibimbap.bmp", 192, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("16_MinotaursSteak", "Images/food/16_MinotaursSteak.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("17_SpecialtyCookedMeat", "Images/food/17_SpecialtyCookedMeat.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("18_StrawberryPie", "Images/food/18_StrawberryPie.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("19_SeasoningSmallBird", "Images/food/19_SeasoningSmallBird.bmp", 231, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("20_Beer", "Images/food/20_Beer.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("21_CombinationPizza", "Images/food/21_CombinationPizza.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("22_SmokedSalmon", "Images/food/22_SmokedSalmon.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("23_FriedShrimp", "Images/food/23_FriedShrimp.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("24_GrilledEel", "Images/food/24_GrilledEel.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("25_CinnamonRoll", "Images/food/25_CinnamonRoll.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("26_SparklingWater", "Images/food/26_SparklingWater.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("97_SweetMeatball", "Images/food/97_SweetMeatball.bmp", 219, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("98_HotMeatball", "Images/food/98_HotMeatball.bmp", 219, 144, true, RGB(255, 0, 255));

	// OBSTACLE //

	_loading->LoadNormalImage("gear", "Images/Object/gear.bmp", 108, 108, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Gear_Small", "Images/Object/Gear_Small.bmp", 69, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Gear_Small_Small", "Images/Object/Gear_Small_Small.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SpikePlatform1", "Images/1Floor/SpikePlatform1.bmp", 288, 48, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Spike", "Images/AllFloor/Spike.bmp", 48, 48, true, RGB(255, 0, 255));

	// ETC //
	_loading->LoadNormalImage("SpawnMonsterPos", "Images/Etc/SpawnMonsterPos.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SpawnBoxPos", "Images/Etc/SpawnBoxPos.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SpawnPixiePos", "Images/Etc/SpawnPixiePos.bmp", 48, 48, true, RGB(255, 0, 255));

	// UI //  
	_loading->LoadNormalImage("UIBaseBig", "Images/UI/Base.bmp", 500, 300, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UIBaseMiddle", "Images/UI/Base.bmp", 222 * 2, 189 * 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UIBaseSmall", "Images/UI/Base.bmp", 222, 189, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UpButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RightButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DownButton", "Images/UI/FullWindowExitButton.bmp", 66, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("LeftButton", "Images/UI/FullWindowExitButton.bmp", 66, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("mapWidthBox", "Images/UI/AbilityTextBar.bmp", 120, 100, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("mapHeightBox", "Images/UI/AbilityTextBar.bmp", 120, 100, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShortcutKeyGround", "Images/UI/AltarButton1.bmp", 800, 87, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShortcutKey1", "Images/UI/IconGray.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShortcutKey2", "Images/UI/IconWhite1.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityTextBar", "Images/UI/AbilityTextBar.bmp", 33, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_avarice_5_1", "Images/UI/ICON/Trait_avarice_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_avarice_5_2", "Images/UI/ICON/Trait_avarice_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_avarice_10_1", "Images/UI/ICON/Trait_avarice_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_avarice_10_2", "Images/UI/ICON/Trait_avarice_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_avarice_20_1", "Images/UI/ICON/Trait_avarice_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_avarice_20_2", "Images/UI/ICON/Trait_avarice_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Concentration_5_1", "Images/UI/ICON/Trait_Concentration_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Concentration_5_2", "Images/UI/ICON/Trait_Concentration_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Concentration_10_1", "Images/UI/ICON/Trait_Concentration_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Concentration_10_2", "Images/UI/ICON/Trait_Concentration_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Concentration_20_1", "Images/UI/ICON/Trait_Concentration_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Concentration_20_2", "Images/UI//ICON/Trait_Concentration_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_craving_5_1", "Images/UI/ICON/Trait_craving_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_craving_5_2", "Images/UI/ICON/Trait_craving_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_craving_10_1", "Images/UI/ICON/Trait_craving_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_craving_10_2", "Images/UI/ICON/Trait_craving_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_craving_20_1", "Images/UI/ICON/Trait_craving_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_craving_20_2", "Images/UI/ICON/Trait_craving_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Def_5_1", "Images/UI/ICON/Trait_Def_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Def_5_2", "Images/UI/ICON/Trait_Def_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Def_10_1", "Images/UI/ICON/Trait_Def_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Def_10_2", "Images/UI/ICON/Trait_Def_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Def_20_1", "Images/UI/ICON/Trait_Def_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Def_20_2", "Images/UI/ICON/Trait_Def_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Mystery_5_1", "Images/UI/ICON/Trait_Mystery_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Mystery_5_2", "Images/UI/ICON/Trait_Mystery_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Mystery_10_1", "Images/UI/ICON/Trait_Mystery_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Mystery_10_2", "Images/UI/ICON/Trait_Mystery_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Mystery_20_1", "Images/UI/ICON/Trait_Mystery_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Mystery_20_2", "Images/UI/ICON/Trait_Mystery_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Power_5_1", "Images/UI/ICON/Trait_Power_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Power_5_2", "Images/UI/ICON/Trait_Power_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Power_10_1", "Images/UI/ICON/Trait_Power_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Power_10_2", "Images/UI/ICON/Trait_Power_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Power_20_1", "Images/UI/ICON/Trait_Power_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Power_20_2", "Images/UI/ICON/Trait_Power_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Speed_5_1", "Images/UI/ICON/Trait_Speed_5_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Speed_5_2", "Images/UI/ICON/Trait_Speed_5_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Speed_10_1", "Images/UI/ICON/Trait_Speed_10_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Speed_10_2", "Images/UI/ICON/Trait_Speed_10_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Speed_20_1", "Images/UI/ICON/Trait_Speed_20_1.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Trait_Speed_20_2", "Images/UI/ICON/Trait_Speed_20_2.bmp", 42, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButton_Arcane", "Images/UI/AbilityBackgroundButton_Arcane.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButton_Greed", "Images/UI/AbilityBackgroundButton_Greed.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButton_Patience", "Images/UI/AbilityBackgroundButton_Patience.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButton_Swiftness", "Images/UI/AbilityBackgroundButton_Swiftness.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButton_Wrath", "Images/UI/AbilityBackgroundButton_Wrath.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButtonDisable_Arcane", "Images/UI/AbilityBackgroundButtonDisable_Arcane.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButtonDisable_Greed", "Images/UI/AbilityBackgroundButtonDisable_Greed.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButtonDisable_Patience", "Images/UI/AbilityBackgroundButtonDisable_Patience.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButtonDisable_Swiftness", "Images/UI/AbilityBackgroundButtonDisable_Swiftness.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackgroundButtonDisable_Wrath", "Images/UI/AbilityBackgroundButtonDisable_Wrath.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("accessoryZone", "Images/UI/accessoryZone.bmp", 96, 75, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AltarButton0", "Images/UI/AltarButton0.bmp", 300, 90, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AltarButton1", "Images/UI/AltarButton1.bmp", 266, 87, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AltarGaugeBase", "Images/UI/AltarGaugeBase.bmp", 116, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AnvilCloseButton", "Images/UI/AnvilCloseButton.bmp", 39, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AnvilCloseButtonSelected", "Images/UI/AnvilCloseButtonSelected.bmp", 39, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AnvilUI", "Images/UI/AnvilUI.bmp", 408, 153, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Base", "Images/UI/Base.bmp", 222, 189, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("baseFrame", "Images/UI/baseFrame.bmp", 1440, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Base_0", "Images/UI/Base_0.bmp", 333, 396, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Base_1", "Images/UI/Base_1.bmp", 333, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Base_2", "Images/UI/Base_2.bmp", 339, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Base_3", "Images/UI/Base_3.bmp", 579, 396, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BasicCursor", "Images/UI/BasicCursor.bmp", 27, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BossLifeBack", "Images/UI/BossLifeBack.bmp", 375, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BossLifeBase", "Images/UI/BossLifeBase.bmp", 375, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BuildCompleteBase_0", "Images/UI/BuildCompleteBase_0.bmp", 176, 98, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BuildCompleteBase_1", "Images/UI/BuildCompleteBase_1.bmp", 381, 294, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BuildMenu", "Images/UI/BuildMenu.bmp", 858, 105, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BuildMenu_Selected", "Images/UI/BuildMenu_Selected.bmp", 858, 105, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Choice", "Images/UI/Choice.bmp", 27, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Clear", "Images/UI/Clear.bmp", 192, 30, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeBack", "Images/UI/CostumeBack.bmp", 222, 297, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeBase_0", "Images/UI/CostumeBase_0.bmp", 960, 87, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeBase_1", "Images/UI/CostumeBase_1.bmp", 960, 150, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeEquipped", "Images/UI/CostumeEquipped.bmp", 204, 285, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeLocked", "Images/UI/CostumeLocked.bmp", 204, 285, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeOver", "Images/UI/CostumeOver.bmp", 204, 285, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CostumeUnlocked", "Images/UI/CostumeUnlocked.bmp", 204, 285, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DashBase", "Images/UI/DashBase.bmp", 27, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DashBaseLeftEnd", "Images/UI/DashBaseLeftEnd.bmp", 6, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DashBaseRightEnd", "Images/UI/DashBaseRightEnd.bmp", 6, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DashCount", "Images/UI/DashCount.bmp", 27, 12, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DashCountBase_0", "Images/UI/DashCountBase_0.bmp", 33, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DemensionVault0", "Images/UI/DemensionVault0.bmp", 99, 99, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DemensionVault1", "Images/UI/DemensionVault1.bmp", 99, 99, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DemensionVault1_test", "Images/UI/DemensionVault1_test.bmp", 198, 99, 2, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DemensionVault1_test2", "Images/UI/DemensionVault1_test2.bmp", 792, 792, 8, 8, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonMenu 1", "Images/UI/DungeonMenu 1.bmp", 960, 120, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonMenu 2", "Images/UI/DungeonMenu 2.bmp", 12, 337, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonShopBase", "Images/UI/DungeonShopBase.bmp", 366, 564, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Empty", "Images/UI/Empty.bmp", 96, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("EndurancePain", "Images/UI/EndurancePain.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("EquippedWeaponBase", "Images/UI/EquippedWeaponBase.bmp", 102, 72, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ExplorationFailure.korean", "Images/UI/ExplorationFailure.korean.bmp", 960, 108, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ExplorationSuccess.korean", "Images/UI/ExplorationSuccess.korean.bmp", 960, 108, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("FullWindowExitButton", "Images/UI/FullWindowExitButton.bmp", 66, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("FullWindowExitButton_Selected", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IconGray", "Images/UI/IconGray.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IconWhite 1", "Images/UI/IconWhite 1.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IconWhite", "Images/UI/IconWhite.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IconWhite_Trans", "Images/UI/IconWhite_Trans.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IconYellow_Trans", "Images/UI/IconYellow_Trans.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OptionArrow0", "Images/UI/OptionArrow0.bmp", 51, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OptionArrow1", "Images/UI/OptionArrow1.bmp", 51, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Result_0", "Images/UI/Result_0.bmp", 432, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Result_1", "Images/UI/Result_1.bmp", 432, 147, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Result_2", "Images/UI/Result_2.bmp", 150, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ScrollRect", "Images/UI/ScrollRect.bmp", 906, 396, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SlotDeleteButton", "Images/UI/SlotDeleteButton.bmp", 186, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SlotDeleteButton_Rev", "Images/UI/SlotDeleteButton_Rev.bmp", 51, 186, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_0", "Images/UI/AbilityBackground_0.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_1", "Images/UI/AbilityBackground_1.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_Arcane", "Images/UI/AbilityBackground_Arcane.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_Greed", "Images/UI/AbilityBackground_Greed.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_Patience", "Images/UI/AbilityBackground_Patience.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_Swiftness", "Images/UI/AbilityBackground_Swiftness.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityBackground_Wrath", "Images/UI/AbilityBackground_Wrath.bmp", 200, 350, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("AbilityTItle", "Images/UI/AbilityTItle.bmp", 1440, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("accessory", "Images/UI/accessory.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("accessorySelect", "Images/UI/accessorySelect.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("InventoryBase_2", "Images/UI/InventoryBase_2.bmp", 369, 564, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Item_0", "Images/UI/Item_0.bmp", 351, 438, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Item_1", "Images/UI/Item_1.bmp", 351, 438, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Item_2", "Images/UI/Item_2.bmp", 351, 438, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("JournalTitle", "Images/UI/JournalTitle.bmp", 243, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("KeyMappingButtonOn", "Images/UI/KeyMappingButtonOn.bmp", 141, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("KeyMappingButtonSelect", "Images/UI/KeyMappingButtonSelect.bmp", 141, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("KeyMappingHead", "Images/UI/KeyMappingHead.bmp", 315, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Label", "Images/UI/Label.bmp", 960, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("LevelUp", "Images/UI/LevelUp.bmp", 339, 135, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("LevelUpAltar", "Images/UI/LevelUpAltar.bmp", 247, 26, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("list_Item_1", "Images/UI/list_Item_1.bmp", 522, 87, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("list_Item", "Images/UI/list_Item.bmp", 534, 363, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("list_Set", "Images/UI/list_Set.bmp", 534, 363, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MainLogo", "Images/UI/MainLogo.bmp", 468, 225, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MapBase_1_0", "Images/UI/MapBase_1_0.bmp", 1440, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MapBase_1_1", "Images/UI/MapBase_1_1.bmp", 780, 396, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MisticAnvil", "Images/UI/MisticAnvil.bmp", 195, 162, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MisticPot", "Images/UI/MisticPot.bmp", 180, 240, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_L", "Images/UI/Mouse_L.bmp", 33, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_L_Drag", "Images/UI/Mouse_L_Drag.bmp", 75, 84, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_Move", "Images/UI/Mouse_Move.bmp", 75, 84, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_R", "Images/UI/Mouse_R.bmp", 33, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_R_Dash", "Images/UI/Mouse_R_Dash.bmp", 51, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_Wheel", "Images/UI/Mouse_Wheel.bmp", 33, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Mouse_WheelClick", "Images/UI/Mouse_WheelClick.bmp", 33, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OptionArrow1White", "Images/UI/OptionArrow1White.bmp", 51, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OptionBase2", "Images/UI/OptionBase2.bmp", 960, 90, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OptionSoundBar", "Images/UI/OptionSoundBar.bmp", 339, 15, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PlayerLifeBack", "Images/UI/PlayerLifeBack.bmp", 222, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PlayerLifeBase_1", "Images/UI/PlayerLifeBase_1.bmp", 222, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RedPill", "Images/UI/RedPill.bmp", 198, 198, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RedWarningOnHit_0", "Images/UI/RedWarningOnHit_0.bmp", 480, 540, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RedWarningOnHit_1", "Images/UI/RedWarningOnHit_1.bmp", 480, 540, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadFX0", "Images/UI/ReloadFX0.bmp", 81, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadFX1", "Images/UI/ReloadFX1.bmp", 81, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadFX2", "Images/UI/ReloadFX2.bmp", 81, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadFX3", "Images/UI/ReloadFX3.bmp", 81, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadPoint", "Images/UI/ReloadPoint.bmp", 9, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RestaurantLifeBase", "Images/UI/RestaurantLifeBase.bmp", 165, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RestaurantLifeBaseBack", "Images/UI/RestaurantLifeBaseBack.bmp", 165, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RestaurantMenu", "Images/UI/RestaurantMenu.bmp", 297, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RestaurantMenu_Selected", "Images/UI/RestaurantMenu_Selected.bmp", 297, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RestaurantMenu_Withoutmoney", "Images/UI/RestaurantMenu_Withoutmoney.bmp", 431, 160, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RestaurantMenu_Withoutmoney_Selected", "Images/UI/RestaurantMenu_Withoutmoney_Selected.bmp", 431, 160, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RestaurantTable", "Images/UI/RestaurantTable.bmp", 1719, 390, 3, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Right", "Images/UI/Right.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Room", "Images/UI/Room.bmp", 72, 72, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ScroolBarBase", "Images/UI/ScroolBarBase.bmp", 21, 9, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ScroolBarHandle", "Images/UI/ScroolBarHandle.bmp", 9, 9, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Set_0", "Images/UI/Set_0.bmp", 351, 438, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Set_1", "Images/UI/Set_1.bmp", 351, 438, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Set_2", "Images/UI/Set_2.bmp", 351, 438, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShieldBase", "Images/UI/ShieldBase.bmp", 156, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShootingCursor1", "Images/UI/ShootingCursor1.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShootingCursor2", "Images/UI/ShootingCursor2.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShopBase", "Images/UI/ShopBase.bmp", 366, 564, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShopItem", "Images/UI/ShopItem.bmp", 321, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShopItem_Selected", "Images/UI/ShopItem_Selected.bmp", 321, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Skill_0", "Images/UI/Skill_0.bmp", 318, 165, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SlotBase", "Images/UI/SlotBase.bmp", 288, 429, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SlotBase_Selected", "Images/UI/SlotBase_Selected.bmp", 288, 429, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StashBase", "Images/UI/StashBase.bmp", 360, 540, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TeamLogo0", "Images/UI/TeamLogo0.bmp", 177, 192, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TeamLogo1", "Images/UI/TeamLogo1.bmp", 177, 192, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TeamLogo2", "Images/UI/TeamLogo2.bmp", 177, 192, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TextBox", "Images/UI/TextBox.bmp", 36, 36, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tip", "Images/UI/Tip.bmp", 153, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Title", "Images/UI/Title.bmp", 960, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("town", "Images/UI/town.bmp", 696, 120, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tutorial_Altar", "Images/UI/Tutorial_Altar.bmp", 210, 222, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tutorial_DashAttack", "Images/UI/Tutorial_DashAttack.bmp", 144, 180, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tutorial_GoToTownPortal", "Images/UI/Tutorial_GoToTownPortal.bmp", 231, 144, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tutorial_Wheel", "Images/UI/Tutorial_Wheel.bmp", 87, 117, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UnlockMessage", "Images/UI/UnlockMessage.bmp", 3, 93, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WeaponSelect0", "Images/UI/WeaponSelect0.bmp", 141, 90, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WeaponSelect1", "Images/UI/WeaponSelect1.bmp", 141, 90, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("X", "Images/UI/X.bmp", 39, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Xbutton", "Images/UI/Xbutton.bmp", 92, 79, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("����", "Images/UI/����.bmp", 960, 540, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ScreenCover", "Images/UI/ScreenCover.bmp", 200, 200, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ToolTipCover", "Images/UI/ToolTipCover.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ToolTipSkillCover", "Images/UI/ToolTipSkillCover.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Room_Line_LR", "Images/UI/Room_Line_LR.bmp", 42, 8, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Room_Line_UD", "Images/UI/Room_Line_UD.bmp", 8, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Room_Selected", "Images/UI/Room_Selected.bmp", 72, 72, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Room_MouseHovered", "Images/UI/Room_MouseHovered.bmp", 72, 72, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("moneyUI", "Images/UI/moneyUI.bmp", 19, 19, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BaseType2", "Images/UI/BaseType2.bmp", 222, 189, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("YesOrNo", "Images/UI/YesOrNo.bmp", 113, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ConversationUI", "Images/UI/ConversationUI.bmp", 1440, 270, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SelectUI", "Images/UI/SelectUI.bmp", 266, 125, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SelectedFrame", "Images/UI/SelectedFrame.bmp", 232, 44, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("LifeBar", "Images/UI/LifeBar.bmp", 180, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PlayerLifeBackGray_1", "Images/UI/PlayerLifeBackGray_1.bmp", 63, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PlayerLifeBackGray_2", "Images/UI/PlayerLifeBackGray_2.bmp", 180, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PlayerLifeBase_1", "Images/UI/PlayerLifeBase_1.bmp", 63, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PlayerLifeBase_2", "Images/UI/PlayerLifeBase_2.bmp", 159, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("restaurantSatiation", "Images/UI/restaurantSatiation.bmp", 333, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("restaurantMoney", "Images/UI/restaurantMoney.bmp", 200, 51, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LifeWave", "Images/UI/LifeWave.bmp", 203, 48, 7, 1, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("CheckImage", "Images/GridBound.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CheckImageRed", "Images/GridBoundRed.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("FrontCloud", "Images/villageFloor/FrontCloud.bmp", 2556, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MidCloud0", "Images/villageFloor/MidCloud0.bmp", 2556, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BackCloud", "Images/villageFloor/BackCloud.bmp", 2844, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("hit", "Images/UI/hit.bmp", 1440, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HpBar1", "Images/HpBar1.bmp", 75, 20, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HpBar2", "Images/HpBar2.bmp", 75,20, true, RGB(255, 0, 255));

	// ICON //
	_loading->LoadNormalImage("brushCursor", "Images/UI/ICON/Brush.bmp", 35, 35, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("paintCursor", "Images/UI/ICON/paintCursor.bmp", 27, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("eraserCursor", "Images/UI/ICON/eraserIcon.bmp", 30, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("fillIcon", "Images/UI/ICON/fillIcon.bmp", 36, 44, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("loadIcon", "Images/UI/ICON/loadIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("loadIcon", "Images/UI/ICON/loadIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("saveIcon", "Images/UI/ICON/saveIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("fillRectIcon", "Images/UI/ICON/fillRectIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("floodFillIcon", "Images/UI/ICON/floodFillIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("sizeUpDownIcon", "Images/UI/ICON/SizeUpDown.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("undoIcon", "Images/UI/ICON/Undo.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("colMinusIcon", "Images/UI/ICON/ColMinus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("colPlusIcon", "Images/UI/ICON/ColPlus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("rowMinusIcon", "Images/UI/ICON/RowMinus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("rowPlusIcon", "Images/UI/ICON/RowPlus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("paintIcon", "Images/UI/ICON/paint.bmp", 45, 46, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("eraseIcon", "Images/UI/ICON/eraseIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Exit", "Images/UI/ICON/Exit.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Block", "Images/UI/ICON/Stat_Block.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Critical", "Images/UI/ICON/Stat_Critical.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_CriticalDmg", "Images/UI/ICON/Stat_CriticalDmg.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Dash", "Images/UI/ICON/Stat_Dash.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Def", "Images/UI/ICON/Stat_Def.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Evade", "Images/UI/ICON/Stat_Evade.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_MoveSpeed", "Images/UI/ICON/Stat_MoveSpeed.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Power", "Images/UI/ICON/Stat_Power.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Reload", "Images/UI/ICON/Stat_Reload.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Tough", "Images/UI/ICON/Stat_Tough.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_TrueDamage", "Images/UI/ICON/Stat_TrueDamage.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_AtkSpeed", "Images/UI/ICON/Stat_AtkSpeed.bmp", 63, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Burn", "Images/UI/ICON/Stat_Burn.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Cold", "Images/UI/ICON/Stat_Cold.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Poison", "Images/UI/ICON/Stat_Poison.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Shock", "Images/UI/ICON/Stat_Shock.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stat_Stun", "Images/UI/ICON/Stat_Stun.bmp", 51, 51, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Keyboard_F", "Images/UI/ICON/Keyboard_F.bmp", 39, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Keyboard_R", "Images/UI/ICON/Keyboard_R.bmp", 39, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Food", "Images/UI/ICON/Food.bmp", 17, 14, true, RGB(255,0,255));
	_loading->LoadNormalImage("FoodIcon", "Images/UI/ICON/FoodIcon.bmp", 51, 42, true, RGB(255,0,255));
	_loading->LoadNormalImage("Coin", "Images/UI/ICON/Coin.bmp", 19, 19, true, RGB(255,0,255));
	_loading->LoadNormalImage("Fairy", "Images/UI/ICON/Fairy.bmp", 17, 14, true, RGB(255,0,255));
	_loading->LoadNormalImage("EnteranceMap", "Images/UI/ICON/EnteranceMap.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("ExitMap", "Images/UI/ICON/ExitMap.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("FairyMap", "Images/UI/ICON/FairyMap.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("FoodMap", "Images/UI/ICON/FoodMap.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Hungry", "Images/UI/ICON/Hungry.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("PlagueDocter", "Images/UI/ICON/PlagueDocter.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Pot", "Images/UI/ICON/Pot.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("ShopMap", "Images/UI/ICON/ShopMap.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Slot", "Images/UI/ICON/Slot.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Worm", "Images/UI/ICON/Worm.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Worm_Selected", "Images/UI/ICON/Worm_Selected.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Altar", "Images/UI/ICON/Altar.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Anvil", "Images/UI/ICON/Anvil.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Berry", "Images/UI/ICON/Berry.bmp", 24, 24, true, RGB(255,0,255));
	_loading->LoadNormalImage("Chest", "Images/UI/ICON/Chest.bmp", 24, 24, true, RGB(255,0,255));


	_loading->LoadNormalImage("BossLifeBack", "Images/Monster/Boss/BossLifeBack.bmp", 600, 77, true, RGB(255,0,255));
	_loading->LoadNormalImage("BossLifeBase", "Images/Monster/Boss/BossLifeBase.bmp", 600, 77, true, RGB(255,0,255));
	_loading->LoadNormalImage("BossLife", "Images/Monster/Boss/BossLifeRed.bmp", 480, 77, true, RGB(255,0,255));


	_loading->LoadNormalImage("gameStart1", "Images/UI/gameStart1.bmp", 158, 47, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("gameStart0", "Images/UI/gameStart0.bmp", 158, 47, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("quit", "Images/UI/quit.bmp", 158, 47, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("quit2", "Images/UI/quit2.bmp", 158, 47, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("mapTool", "Images/UI/mapTool.bmp", 158, 47, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("mapTool2", "Images/UI/mapTool2.bmp", 158, 47, true, RGB(255, 0, 255));

	// TOWN //
	_loading->LoadNormalImage("bridgeTileLeft1", "Images/villageFloor/townBridge/1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft2", "Images/villageFloor/townBridge/2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft3", "Images/villageFloor/townBridge/3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft4", "Images/villageFloor/townBridge/4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft5", "Images/villageFloor/townBridge/5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft6", "Images/villageFloor/townBridge/6.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft7", "Images/villageFloor/townBridge/7.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft8", "Images/villageFloor/townBridge/8.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft9", "Images/villageFloor/townBridge/9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft10", "Images/villageFloor/townBridge/10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft11", "Images/villageFloor/townBridge/11.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft12", "Images/villageFloor/townBridge/12.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft13", "Images/villageFloor/townBridge/13.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft14", "Images/villageFloor/townBridge/14.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft15", "Images/villageFloor/townBridge/15.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft16", "Images/villageFloor/townBridge/16.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft17", "Images/villageFloor/townBridge/17.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft18", "Images/villageFloor/townBridge/18.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft19", "Images/villageFloor/townBridge/19.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft20", "Images/villageFloor/townBridge/20.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft21", "Images/villageFloor/townBridge/21.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft22", "Images/villageFloor/townBridge/22.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft23", "Images/villageFloor/townBridge/23.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("bridgeTileRight1", "Images/villageFloor/townBridge/24.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight2", "Images/villageFloor/townBridge/25.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight3", "Images/villageFloor/townBridge/26.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight4", "Images/villageFloor/townBridge/27.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight5", "Images/villageFloor/townBridge/28.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight6", "Images/villageFloor/townBridge/29.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight7", "Images/villageFloor/townBridge/30.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight8", "Images/villageFloor/townBridge/31.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight9", "Images/villageFloor/townBridge/32.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight10", "Images/villageFloor/townBridge/33.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight11", "Images/villageFloor/townBridge/34.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight12", "Images/villageFloor/townBridge/35.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight13", "Images/villageFloor/townBridge/36.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight14", "Images/villageFloor/townBridge/37.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight15", "Images/villageFloor/townBridge/38.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight16", "Images/villageFloor/townBridge/39.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight17", "Images/villageFloor/townBridge/40.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight18", "Images/villageFloor/townBridge/41.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight19", "Images/villageFloor/townBridge/42.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight20", "Images/villageFloor/townBridge/43.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight21", "Images/villageFloor/townBridge/44.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight22", "Images/villageFloor/townBridge/45.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight23", "Images/villageFloor/townBridge/46.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight24", "Images/villageFloor/townBridge/47.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight25", "Images/villageFloor/townBridge/48.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight26", "Images/villageFloor/townBridge/49.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight27", "Images/villageFloor/townBridge/50.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight28", "Images/villageFloor/townBridge/51.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight29", "Images/villageFloor/townBridge/52.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight30", "Images/villageFloor/townBridge/53.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight31", "Images/villageFloor/townBridge/54.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight32", "Images/villageFloor/townBridge/55.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight33", "Images/villageFloor/townBridge/56.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("bridgeSecondFloor1", "Images/villageFloor/townBridge/secondFloor_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeSecondFloor2", "Images/villageFloor/townBridge/secondFloor_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeSecondFloor3", "Images/villageFloor/townBridge/secondFloor_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeSecondFloor4", "Images/villageFloor/townBridge/secondFloor_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair1", "Images/villageFloor/townBridge/Town_LeftStair.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair2", "Images/villageFloor/townBridge/Town_RightStair.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair3", "Images/villageFloor/townBridge/TownBasic_StairL.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair4", "Images/villageFloor/townBridge/TownBasic_StairR.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("dirtFloor1", "Images/villageFloor/townBridge/Dirt_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor2", "Images/villageFloor/townBridge/Dirt_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor3", "Images/villageFloor/townBridge/Dirt_H_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor4", "Images/villageFloor/townBridge/Dirt_H_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor5", "Images/villageFloor/townBridge/Dirt_H_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor6", "Images/villageFloor/townBridge/Dirt_H_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor7", "Images/villageFloor/townBridge/Dirt_H_12.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor8", "Images/villageFloor/townBridge/Dirt_H_13.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor9", "Images/villageFloor/townBridge/Dirt_H_StairL.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor10", "Images/villageFloor/townBridge/Dirt_H_StairL2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor11", "Images/villageFloor/townBridge/Dirt_H_StairR.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor12", "Images/villageFloor/townBridge/Dirt_H_StairR2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor13", "Images/villageFloor/townBridge/DirtToBaicT2_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor14", "Images/villageFloor/townBridge/DirtToBaicT2_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor15", "Images/villageFloor/townBridge/DirtToTown_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor16", "Images/villageFloor/townBridge/DirtToTown_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor17", "Images/villageFloor/townBridge/DirtToGrass_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor18", "Images/villageFloor/townBridge/DirtToGrass_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor19", "Images/villageFloor/townBridge/Grass_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor20", "Images/villageFloor/townBridge/Grass_H_1_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor21", "Images/villageFloor/townBridge/Grass_H_1_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor22", "Images/villageFloor/townBridge/Grass_H_1_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor23", "Images/villageFloor/townBridge/Grass_H_1_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor24", "Images/villageFloor/townBridge/Grass_H_1_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor25", "Images/villageFloor/townBridge/Grass_H_StairL.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor26", "Images/villageFloor/townBridge/Grass_H_StairR.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor27", "Images/villageFloor/townBridge/Grass_H_StairL2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor28", "Images/villageFloor/townBridge/Grass_H_StairR2.bmp", 48, 48, true, RGB(255, 0, 255));

	// TOWN IMAGE //
	_loading->LoadNormalImage("StreetLight", "Images/villageFloor/StreetLight.bmp", 93, 171, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Target", "Images/villageFloor/Target.bmp", 219, 72, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TrainingSchool", "Images/villageFloor/TrainingSchool.bmp", 810, 231, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Grass0", "Images/villageFloor/Grass0.bmp", 132, 30, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Grass1", "Images/villageFloor/Grass1.bmp", 132, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Grass2", "Images/villageFloor/Grass2.bmp", 285, 75, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonSignLeft", "Images/villageFloor/DungeonSignLeft.bmp", 60, 66, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonSignRight", "Images/villageFloor/DungeonSignRight.bmp", 60, 66, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Well", "Images/villageFloor/Well.bmp", 147, 147, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Wagon", "Images/villageFloor/Wagon.bmp", 216, 87, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TreeHouse", "Images/villageFloor/TreeHouse.bmp", 411, 387, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StreetLight_1", "Images/villageFloor/StreetLight_1.bmp", 39, 141, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StreetLight_2", "Images/villageFloor/StreetLight_2.bmp", 39, 141, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Fence", "Images/villageFloor/Fence.bmp", 588, 162, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BlackSmith", "Images/villageFloor/BlackSmith.bmp", 492, 390, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BlackSmithDisplay", "Images/villageFloor/BlackSmithDisplay.bmp", 567, 78, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Boutique", "Images/villageFloor/Boutique.bmp", 747, 471, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("FirearmsCase", "Images/villageFloor/FirearmsCase.bmp", 135, 72, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Gunsmith", "Images/villageFloor/Gunsmith.bmp", 653, 359, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("PrayStatue", "Images/villageFloor/PrayStatue.bmp", 54, 93, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Shop", "Images/villageFloor/Shop.bmp", 564, 356, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tree0", "Images/villageFloor/Tree0.bmp", 156, 183, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Tree1", "Images/villageFloor/Tree1.bmp", 201, 231, true, RGB(255, 0, 255));

	// TOWN NPC //
	_loading->LoadFrameImage("NPC_Trainee", "Images/villageFloor/NPC/image/NPC_Trainee.bmp", 462, 66, 7, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_AthenaIdle", "Images/villageFloor/NPC/image/NPC_AthenaIdle.bmp", 450, 156, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_AthenaMove", "Images/villageFloor/NPC/image/NPC_AthenaMove.bmp", 450, 156, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_ButlerIdle", "Images/villageFloor/NPC/image/NPC_ButlerIdle.bmp", 180, 138, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_ButlerMove", "Images/villageFloor/NPC/image/NPC_ButlerMove.bmp", 216, 138, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_DeerFarmIdle", "Images/villageFloor/NPC/image/NPC_DeerFarmIdle.bmp", 450, 192, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_DeerFarmMove", "Images/villageFloor/NPC/image/NPC_DeerFarmMove.bmp", 450, 192, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_Jpage", "Images/villageFloor/NPC/image/NPC_Jpage.bmp", 2700, 111, 20, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_JukToIdle", "Images/villageFloor/NPC/image/NPC_JukToIdle.bmp", 1260, 222, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_JukToMove", "Images/villageFloor/NPC/image/NPC_JukToMove.bmp", 882, 222, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_KnightIdle", "Images/villageFloor/NPC/image/NPC_KnightIdle.bmp", 306, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_KnightMove", "Images/villageFloor/NPC/image/NPC_KnightMove.bmp", 306, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("PistolMan", "Images/villageFloor/NPC/image/PistolMan.bmp", 306, 108, 6, 1, true, RGB(255, 0, 255));

	_loading->LoadFrameImage("DungeonEat", "Images/villageFloor/NPC/DungeonEat.bmp", 9828, 255, 28, 1, true, RGB(255, 0, 255));

	// MONSTER //
	_loading->LoadFrameImage("SealStone", "Images/Monster/SealStone.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("AbyssBansheeIdle", "Images/Monster/AbyssBansheeIdle.bmp", 360, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("AbyssBansheeAttack", "Images/Monster/AbyssBansheeAttack.bmp", 726, 132, 11, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BansheeIdle", "Images/Monster/BansheeIdle.bmp", 360, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BansheeAttack", "Images/Monster/BansheeAttack.bmp", 360, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatRedIdle", "Images/Monster/BatRedIdle.bmp", 558, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatRedAttack", "Images/Monster/BatRedAttack.bmp", 930, 120, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatIdle", "Images/Monster/BatIdle.bmp", 558, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BombBat", "Images/Monster/BombBat.bmp", 342, 72, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BombBatExplosionBegin", "Images/Monster/BombBatExplosionBegin.bmp", 1377, 81, 18, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GiantBat", "Images/Monster/GiantBat.bmp", 1239, 210, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GiantBatAttack", "Images/Monster/GiantBatAttack.bmp", 1770, 234, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RedGiantBat", "Images/Monster/RedGiantBat.bmp", 1239, 210, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RedGiantBatAttack", "Images/Monster/RedGiantBatAttack.bmp", 1770, 234, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LilithIdle", "Images/Monster/LilithIdle.bmp", 936, 156, 12, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LilithCatch", "Images/Monster/LilithCatch.bmp", 156, 156, 2, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LilithMove", "Images/Monster/LilithMove.bmp", 468, 156, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LittleGhost", "Images/Monster/LittleGhost.bmp", 360, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LittleGhostAttack", "Images/Monster/LittleGhostAttack.bmp", 180, 120, 3, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelSwordEffect", "Images/Monster/SkelSwordEffect.bmp", 222, 80, 3, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SwordSkelIdle", "Images/Monster/SwordSkelIdle.bmp", 84, 114, 2, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SwordSkelWalk", "Images/Monster/SwordSkelWalk.bmp", 252, 114, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SwordSkelCorpse", "Images/Monster/SwordSkelCorpse.bmp", 33, 24, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BowSkelIdle", "Images/Monster/BowSkelIdle.bmp", 84, 114, 2, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BowSkelCorpse", "Images/Monster/BowSkelCorpse.bmp", 33, 24, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelSword", "Images/Monster/SkelSword.bmp", 90, 90, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelBow", "Images/Monster/SkelBow.bmp", 342, 51, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelArrow", "Images/Monster/SkelArrow.bmp", 39, 39, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelArrowEffect", "Images/Monster/SkelArrowEffect.bmp", 720, 168, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelDogIdle", "Images/Monster/SkelDogIdle.bmp", 300, 108, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelDogRun", "Images/Monster/SkelDogRun.bmp", 420, 108, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelDogDie", "Images/Monster/SkelDogDie.bmp", 60, 108, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BigWhiteSkelIdle", "Images/Monster/BigWhiteSkelIdle.bmp", 594, 288, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BigWhiteSkelMove", "Images/Monster/BigWhiteSkelMove.bmp", 594, 288, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BigWhiteSkelAttack", "Images/Monster/BigWhiteSkelAttack.bmp", 2196, 288, 12, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursIdle", "Images/Monster/MinotaursIdle.bmp", 936, 300, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursCharge", "Images/Monster/MinotaursCharge.bmp", 1272, 300, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursAttack", "Images/Monster/MinotaursAttack.bmp", 1176, 300, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursBuff", "Images/Monster/MinotaursBuff.bmp", 1728, 87, 12, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursDashEffect", "Images/Monster/MinotaursDashEffect.bmp", 2136, 216, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("IceBat", "Images/Monster/IceBat.bmp", 558, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("IceBatAttack", "Images/Monster/IceBatAttack.bmp", 900, 120, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FireBat", "Images/Monster/FireBat.bmp", 558, 126, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FireBatAttack", "Images/Monster/FireBatAttack.bmp", 930, 126, 10, 2, true, RGB(255, 0, 255));

	// BOSS //
	_loading->LoadFrameImage("SkellBossIdle", "Images/Monster/Boss/SkellBossIdle.bmp", 2100, 285, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossIdleHit", "Images/Monster/Boss/SkellBossIdleHit.bmp", 2100, 285, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossAttack", "Images/Monster/Boss/SkellBossAttack.bmp", 2100, 384, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossAttackHit", "Images/Monster/Boss/SkellBossAttackHit.bmp", 2100, 384, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossBack", "Images/Monster/Boss/SkellBossBack.bmp", 1470, 144, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossDead", "Images/Monster/Boss/SkellBossDead.bmp", 210, 231, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossDead0", "Images/Monster/Boss/SkellBossDead0.bmp", 147, 93, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossDeadParticle0", "Images/Monster/Boss/SkellBossDeadParticle0.bmp", 18, 12, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossDeadParticle1", "Images/Monster/Boss/SkellBossDeadParticle1.bmp", 18, 12, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossDeadParticle2", "Images/Monster/Boss/SkellBossDeadParticle2.bmp", 30, 36, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossDeadParticle3", "Images/Monster/Boss/SkellBossDeadParticle3.bmp", 27, 36, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossLaserBody", "Images/Monster/Boss/SkellBossLaserBody.bmp", 672, 294, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossLaserHead", "Images/Monster/Boss/SkellBossLaserHead.bmp", 567, 264, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossLeftHandAttack", "Images/Monster/Boss/SkellBossLeftHandAttack.bmp", 3510, 213, 18, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossLeftHandIdle", "Images/Monster/Boss/SkellBossLeftHandIdle.bmp", 1710, 189, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossRightHandAttack", "Images/Monster/Boss/SkellBossRightHandAttack.bmp", 3510, 213, 18, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossRightHandIdle", "Images/Monster/Boss/SkellBossRightHandIdle.bmp", 1710, 189, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossParticle", "Images/Monster/Boss/SkellBossParticle.bmp", 720, 90, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossSword", "Images/Monster/Boss/SkellBossSword.bmp", 13344, 278, 48, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossSword0", "Images/Monster/Boss/SkellBossSword0.bmp", 92, 92, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SkellBossSwordFire", "Images/Monster/Boss/SkellBossSwordFire.bmp", 92, 92, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BossSwordHitDown", "Images/Monster/Boss/BossSwordHitDown.bmp", 765, 66, 5, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BossSwordHitUp", "Images/Monster/Boss/BossSwordHitUp.bmp", 765, 66, 5, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BossSwordHitLeft", "Images/Monster/Boss/BossSwordHitLeft.bmp", 330, 153, 5, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BossSwordHitRight", "Images/Monster/Boss/BossSwordHitRight.bmp", 330, 153, 5, 1, true, RGB(255, 0, 255));
	
	_loading->LoadFrameImage("BossBullet", "Images/Monster/Boss/BossBullet.bmp", 156, 39, 4, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BossBulletEffect", "Images/Monster/Boss/BossBulletEffect.bmp", 744, 93, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("destroyEffect", "Images/Monster/Boss/destroyEffect.bmp", 558, 186, 3, 1, true, RGB(255, 0, 255));

	// BACKGROUND //
	_loading->LoadNormalImage("BackFloorBack1", "Images/1Floor/Basic_H_Type2_4.bmp", 1, 1);
	_loading->LoadNormalImage("SubBGStage1", "Images/1Floor/SubBGStage1.bmp", 960, 540, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TownBG_Day", "Images/villageFloor/TownBG_Day.bmp", 960, 1200, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TownLayer_Day", "Images/villageFloor/TownLayer_Day.bmp", 960, 1200, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Sky_Day", "Images/villageFloor/Sky_Day.bmp", 1440, 800, true, RGB(255, 0, 255));

	// ITEM //
	_loading->LoadFrameImage("BasicShortSword_New", "Images/item/BasicShortSword_New.bmp", 90, 90, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BasicShortSword_inven", "Images/item/BasicShortSword_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DemonSword", "Images/item/DemonSword.bmp", 107, 213, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DemonSword_inven", "Images/item/DemonSword_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DemonSword_Drop", "Images/item/DemonSword_Drop.bmp", 62, 21, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DemonSword_Slash", "Images/item/DemonSword_Slash.bmp", 924, 264, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Colt", "Images/item/Colt.bmp", 107, 213, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Colt_inven", "Images/item/Colt_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Colt_Drop", "Images/item/Colt_Drop.bmp", 58, 37, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MainGauche", "Images/item/MainGauche.bmp", 57, 114, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MainGauche_inven", "Images/item/MainGauche_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SilverEaring_inven", "Images/item/SilverEaring_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SilverRing_inven", "Images/item/SilverRing_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BloodOfSrobeo", "Images/item/BloodOfSrobeo.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ChainArmor", "Images/item/ChainArmor.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BloodStoneRing", "Images/item/BloodStoneRing.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BloodStoneNecklace", "Images/item/BloodStoneNecklace.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BombPouch", "Images/item/BombPouch.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ClothArmor", "Images/item/ClothArmor.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Bullion_Silver_Inven", "Images/item/Bullion_Silver_Inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Bullion_Silver", "Images/item/Bullion_Silver.bmp", 60, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CarpCoinPurse", "Images/item/CarpCoinPurse.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Cintamani", "Images/item/Cintamani.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BlessOfSage", "Images/item/BlessOfSage.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CowLeather", "Images/item/CowLeather.bmp", 57, 57, true, RGB(255, 0, 255));

	// BULLET //
	_loading->LoadFrameImage("BatBullet", "Images/Monster/Bullet/BatBullet.bmp", 210, 42, 5, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatBulletHit", "Images/Monster/Bullet/BatBulletHit.bmp", 546, 78, 7, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BansheeBulletIdle", "Images/Monster/Bullet/BansheeBulletIdle.bmp", 180, 81, 3, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BansheeBulletHit", "Images/Monster/Bullet/BansheeBulletHit.bmp", 420, 81, 7, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Bullet01", "Images/Weapon/bullet/Bullet01.bmp", 42, 42, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Bullet02", "Images/Weapon/bullet/Bullet02.bmp", 27, 27, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BulletEffect01", "Images/Weapon/bullet/BulletEffect01.bmp", 270, 45, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("IceBullet", "Images/Monster/Bullet/IceBullet.bmp", 45, 45,1,1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("IceBulletHit", "Images/Monster/Bullet/IceBulletHit.bmp", 225, 75,3,1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FireBatBullet", "Images/Monster/Bullet/FireBatBullet.bmp", 345, 69,5,1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("FireBatBullet0", "Images/Monster/Bullet/FireBatBullet0.bmp", 135, 45,3,1, true, RGB(255, 0, 255));
	

	// EFFECT //
	_loading->LoadFrameImage("monsterSpawnEffect", "Images/Etc/monsterSpawnEffect.bmp", 1302, 93, 14, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DieEffect", "Images/Effect/DieEffect.bmp", 1320, 120, 11, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("HongRyunEffect", "Images/Effect/HongRyunEffect.bmp", 510, 30, 10, 1, true, RGB(255, 0, 255));

	// PARTICLE //
	_loading->LoadNormalImage("SqaureParticle", "Images/Particle/SqaureParticle.bmp", 15, 15, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_2", "Images/Particle/SqaureParticle_2.bmp", 22, 22, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_3", "Images/Particle/SqaureParticle_3.bmp", 28, 28, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_4", "Images/Particle/SqaureParticle_4.bmp", 5, 5, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BigBoxParticle0_0", "Images/object/BigBoxParticle0_0.bmp", 30, 54, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BigBoxParticle0_1", "Images/object/BigBoxParticle0_1.bmp", 24, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BigBoxParticle0_2", "Images/object/BigBoxParticle0_2.bmp", 33, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BigBoxParticle0_3", "Images/object/BigBoxParticle0_3.bmp", 12, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BigBoxParticle0_4", "Images/object/BigBoxParticle0_4.bmp", 42, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BigBoxParticle0_5", "Images/object/BigBoxParticle0_5.bmp", 27, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_0", "Images/object/BoxParticle0_0.bmp", 30, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_1", "Images/object/BoxParticle0_1.bmp", 21, 30, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_2", "Images/object/BoxParticle0_2.bmp", 15, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_3", "Images/object/BoxParticle0_3.bmp", 12, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_4", "Images/object/BoxParticle0_4.bmp", 21, 12, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_5", "Images/object/BoxParticle0_5.bmp", 27, 12, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BoxParticle0_6", "Images/object/BoxParticle0_6.bmp", 12, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrumParticle0_0", "Images/object/OakDrumParticle0_0.bmp", 30, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrumParticle0_1", "Images/object/OakDrumParticle0_1.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrumParticle0_2", "Images/object/OakDrumParticle0_2.bmp", 12, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrumParticle0_3", "Images/object/OakDrumParticle0_3.bmp", 18, 9, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrumParticle0_4", "Images/object/OakDrumParticle0_4.bmp", 15, 24, true, RGB(255, 0, 255));

	// MINIMAP //
	_loading->LoadNormalImage("MiniMapPixel", "Images/MiniMapPixel.bmp", 5, 5);
	_loading->LoadNormalImage("MiniMapEnemy", "Images/MiniMapEnemy.bmp", 7, 7);
	_loading->LoadNormalImage("MiniMapPlayer", "Images/MiniMapPlayer.bmp", 9,9);
	_loading->LoadNormalImage("MiniMapDoor", "Images/MiniMapDoor.bmp", 5,5);
	_loading->LoadNormalImage("MiniMapfairyIcon", "Images/MiniMapfairyIcon.bmp", 12,12);
	_loading->LoadNormalImage("MiniMapTresure", "Images/MiniMapTresure.bmp", 15, 9);
	_loading->LoadNormalImage("MiniMapWorm", "Images/MiniMapWorm.bmp", 11, 13, true, RGB(255, 0, 255));

	// COLLISIONIMAGE //
	_loading->LoadNormalImage("Half", "Images/GridPixelCollision/Half.bmp", 48, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Half_Red_CollisionStairLeft", "Images/GridPixelCollision/Half_Red_CollisionStairLeft.bmp", 48, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Half_Red_CollisionStairRight", "Images/GridPixelCollision/Half_Red_CollisionStairRight.bmp", 48, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HalfPlatformSecondFloor", "Images/GridPixelCollision/HalfPlatformSecondFloor.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HalfPlatformStone", "Images/GridPixelCollision/HalfPlatformStone.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HalfPlatformWood", "Images/GridPixelCollision/HalfPlatformWood.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("No_Collision", "Images/GridPixelCollision/No_Collision.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionAll", "Images/GridPixelCollision/Red_CollisionAll.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairLeft", "Images/GridPixelCollision/Red_CollisionStairLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairLeft_2", "Images/GridPixelCollision/Red_CollisionStairLeft_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairRight", "Images/GridPixelCollision/Red_CollisionStairRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairRight_2", "Images/GridPixelCollision/Red_CollisionStairRight_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Blue_CollisionStairLeft", "Images/GridPixelCollision/Blue_CollisionStairLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Blue_CollisionStairRight", "Images/GridPixelCollision/Blue_CollisionStairRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("VillageHalf", "Images/GridPixelCollision/VillageHalf.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll", "Images/GridPixelCollision/Green_CollisionAll.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll2", "Images/GridPixelCollision/Green_CollisionAll2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll3", "Images/GridPixelCollision/Green_CollisionAll3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll4", "Images/GridPixelCollision/Green_CollisionAll4.bmp", 48, 48, true, RGB(255, 0, 255));

	// PLAYER IDLE //
	_loading->LoadFrameImage("baseCharIdle", "Images/player/baseCharIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("sheetingIdle", "Images/player/sheetingIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("gunmanIdle", "Images/player/gunmanIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("aliceIdle", "Images/player/aliceIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("redlotusIdle", "Images/player/redlotusIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("lkinabearIdle", "Images/player/lkinabearIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("riderHIdle", "Images/player/riderHIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("criminalldle", "Images/player/criminalldle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("pickIdle", "Images/player/pickIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("fastoIdle", "Images/player/fastoIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("horsemanIdle", "Images/player/horsemanIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("humanlasleyIdle", "Images/player/humanlasleyIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("masterchefIdle", "Images/player/masterchefIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("bearIdle", "Images/player/bearIdle.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("baseCharEffect", "Images/player/baseCharEffect.bmp", 285, 132, 5, 2, true, RGB(255, 0, 255));

	// RUN //
	_loading->LoadFrameImage("baseCharRun", "Images/player/baseCharRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("sheetingRun", "Images/player/sheetingRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("gunmanRun", "Images/player/gunmanRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("aliceRun", "Images/player/aliceRun.bmp", 468, 150, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("redlotusRun", "Images/player/redlotusRun.bmp", 468, 150, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("lkinabearRun", "Images/player/lkinabearRun.bmp", 468, 150, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("riderHRun", "Images/player/riderHRun.bmp", 468, 150, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("criminalRun", "Images/player/criminalRun.bmp", 468, 150, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("pickRun", "Images/player/pickRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("fastoRun", "Images/player/fastoRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("horsemanRun", "Images/player/horsemanRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("humanlasleyRun", "Images/player/humanlasleyRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("masterchefRun", "Images/player/masterchefRun.bmp", 624, 150, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("bearRun", "Images/player/bearRun.bmp", 468, 150, 6, 2, true, RGB(255, 0, 255));

	// DIE //
	_loading->LoadFrameImage("baseCharDie", "Images/player/baseCharDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("sheetingDie", "Images/player/sheetingDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("gunmanDie", "Images/player/gunmanDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("aliceDie", "Images/player/aliceDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("redlotusDie", "Images/player/redlotusDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("lkinabearDie", "Images/player/lkinabearDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("riderHDie", "Images/player/riderHDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("criminalDie", "Images/player/criminalDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("pickDie", "Images/player/pickDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("fastoDie", "Images/player/fastoDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("horsemanDie", "Images/player/horsemanDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("humanlaselyDie", "Images/player/humanlaselyDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("masterchefDie", "Images/player/masterchefDie.bmp", 78, 75, 1, 1, true, RGB(255, 0, 255));

	//��Ű���� �ɷ� �̹���
	_loading->LoadNormalImage("IkinaBack", "Images/Iknabear/IkinaBack.bmp", 39, 24);
	_loading->LoadNormalImage("IkinaBase", "Images/Iknabear/IkinaBase.bmp", 57, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IkinaBearFace", "Images/Iknabear/IkinaBearFace.bmp", 57, 48, true, RGB(255, 0, 255));

	_loading->LoadFrameImage("AliceZone", "Images/player/AliceZone.bmp", 630, 315, 2, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RunEffect", "Images/player/RunEffect.bmp", 240, 96, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("stun", "Images/player/stun.bmp", 234, 27, 6, 1, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("PixelMapIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
	_loading->LoadNormalImage("MiniMapGroundIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
	_loading->LoadNormalImage("Layer1MapIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
	_loading->LoadNormalImage("Layer2MapIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));

	// COUSTUME //
	_loading->LoadNormalImage("adventurer", "Images/Costume/adventurer.bmp", 51, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("sheeting", "Images/Costume/sheeting.bmp", 51, 66, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("gunman", "Images/Costume/gunman.bmp", 63, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("alice", "Images/Costume/alice.bmp", 51, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("redlotus", "Images/Costume/redlotus.bmp", 57, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("lkinabear", "Images/Costume/lkinabear.bmp", 57, 66, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("riderH", "Images/Costume/riderH.bmp", 78, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("criminal", "Images/Costume/criminal.bmp", 45, 63, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("pick", "Images/Costume/pick.bmp", 54, 66, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("fasto", "Images/Costume/fasto.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("horseman", "Images/Costume/horseman.bmp", 54, 69, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("humanlasley", "Images/Costume/humanlasley.bmp", 54, 66, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("masterchef", "Images/Costume/masterchef.bmp", 57, 75, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{

	// BGM //
	_loading->LoadSound("0.Town", "Sounds/BGM/0.Town.wav", true, true);
	_loading->LoadSound("1.JailBoss", "Sounds/BGM/1.JailBoss.wav", true, true);
	_loading->LoadSound("1.JailField", "Sounds/BGM/1.JailField.wav", true, true);
	_loading->LoadSound("ambience_arskami", "Sounds/BGM/ambience_arskami.wav", true, true);
	_loading->LoadSound("ambience_town", "Sounds/BGM/ambience_town.wav", true, true);
	_loading->LoadSound("ambience_prison", "Sounds/BGM/ambience_prison.wav", true, true);
	_loading->LoadSound("Credit", "Sounds/BGM/Credit.wav", true, true);
	_loading->LoadSound("credit2", "Sounds/BGM/credit2.wav", true, true);
	_loading->LoadSound("Foodshop", "Sounds/BGM/Foodshop.wav", true, true);
	_loading->LoadSound("Shop", "Sounds/BGM/Shop.wav", true, true);
	_loading->LoadSound("title", "Sounds/BGM/title.wav", true, true);

	
	_loading->LoadSound("2.IceBoss", "Sounds/BGM/2.IceBoss.wav", true, true);
	_loading->LoadSound("2.IceField", "Sounds/BGM/2.IceField.wav", true, true);
	_loading->LoadSound("3.jungleboss", "Sounds/BGM/3.jungleboss.wav", true, true);
	_loading->LoadSound("3.junglefield", "Sounds/BGM/3.junglefield.wav", true, true);
	_loading->LoadSound("4.lavaboss", "Sounds/BGM/4.lavaboss.wav", true, true);
	_loading->LoadSound("4.lavafield", "Sounds/BGM/4.lavafield.wav", true, true);
	_loading->LoadSound("5.ForestBoss", "Sounds/BGM/5.ForestBoss.wav", true, true);
	_loading->LoadSound("5.forestfield", "Sounds/BGM/5.forestfield.wav", true, true);
	_loading->LoadSound("6.desertboss", "Sounds/BGM/6.desertboss.wav", true, true);
	_loading->LoadSound("6.desertfield", "Sounds/BGM/6.desertfield.wav", true, true);
	_loading->LoadSound("7.arsha", "Sounds/BGM/7.arsha.wav", true, true);
	_loading->LoadSound("8.kaminela", "Sounds/BGM/8.kaminela.wav", true, true);
	_loading->LoadSound("actiongyoza", "Sounds/BGM/actiongyoza.wav", true, true);
	_loading->LoadSound("ambience_desert", "Sounds/BGM/ambience_desert.wav", true, true);
	_loading->LoadSound("ambience_ericha", "Sounds/BGM/ambience_ericha.wav", true, true);
	_loading->LoadSound("ambience_forest", "Sounds/BGM/ambience_forest.wav", true, true);
	_loading->LoadSound("ambience_ice", "Sounds/BGM/ambience_ice.wav", true, true);
	_loading->LoadSound("ambience_jungle", "Sounds/BGM/ambience_jungle.wav", true, true);
	_loading->LoadSound("ambience_magma", "Sounds/BGM/ambience_magma.wav", true, true);
	_loading->LoadSound("erichaphase3_final", "Sounds/BGM/erichaphase3_final.wav", true, true);
	_loading->LoadSound("erichaphase12_final", "Sounds/BGM/erichaphase12_final.wav", true, true);
	_loading->LoadSound("firegolem_v02", "Sounds/BGM/firegolem_v02.wav", true, true);
	

	// EFFECT //

	_loading->LoadSound("����_��ȹ��", "Sounds/Effect/����_��ȹ��.wav", false, false);
	_loading->LoadSound("arshasnowstaff_1_TaskStage_Start", "Sounds/Effect/arshasnowstaff_1_TaskStage_Start.wav", false, false);
	_loading->LoadSound("charged ������ ������»���", "Sounds/Effect/charged ������ ������»���.wav", false, false);
	_loading->LoadSound("coin", "Sounds/Effect/coin.wav", false, false);
	_loading->LoadSound("devana_center5lasers", "Sounds/Effect/devana_center5lasers.wav", false, false);
	_loading->LoadSound("devana_movinglaser", "Sounds/Effect/devana_movinglaser.wav", false, false);
	_loading->LoadSound("devana_pyo", "Sounds/Effect/devana_pyo.wav", false, false);
	_loading->LoadSound("devana_spin", "Sounds/Effect/devana_spin.wav", false, false);
	_loading->LoadSound("dungoolsword", "Sounds/Effect/dungoolsword.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Attack_Ice_Arrow_kaminelacrystal", "Sounds/Effect/Fantasy_Game_Attack_Ice_Arrow_kaminelacrystal.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Attack_Magic_Arrow_C", "Sounds/Effect/Fantasy_Game_Attack_Magic_Arrow_C.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Footstep_Dirt_Heavy_E", "Sounds/Effect/Fantasy_Game_Footstep_Dirt_Heavy_E.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Inventory_Material_Stone_Touch_4_Magic", "Sounds/Effect/Fantasy_Game_Inventory_Material_Stone_Touch_4_Magic.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Item_Collect_Dark_Magic_A", "Sounds/Effect/Fantasy_Game_Item_Collect_Dark_Magic_A.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Item_Collect_Dark_Magic_B", "Sounds/Effect/Fantasy_Game_Item_Collect_Dark_Magic_B.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Item_Collect_Magic_K", "Sounds/Effect/Fantasy_Game_Item_Collect_Magic_K.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Item_Crafting_Sword_A", "Sounds/Effect/Fantasy_Game_Item_Crafting_Sword_A.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Item_Totem_Scroll_C", "Sounds/Effect/Fantasy_Game_Item_Totem_Scroll_C.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Item_Totem_Scroll_D", "Sounds/Effect/Fantasy_Game_Item_Totem_Scroll_D.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Magic_Fire_Instant_Cast_Spell_D", "Sounds/Effect/Fantasy_Game_Magic_Fire_Instant_Cast_Spell_D.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Magic_Possession_Spell-impact", "Sounds/Effect/Fantasy_Game_Magic_Possession_Spell-impact.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Material_Stone_Pick_Up_4", "Sounds/Effect/Fantasy_Game_Material_Stone_Pick_Up_4.wav", false, false);
	_loading->LoadSound("Fantasy_Game_UI_Lightning_Select", "Sounds/Effect/Fantasy_Game_UI_Lightning_Select.wav", false, false);
	_loading->LoadSound("Fantasy_Game_UI_Shadow_Select", "Sounds/Effect/Fantasy_Game_UI_Shadow_Select.wav", false, false);
	_loading->LoadSound("Fantasy_Game_Water_Bolt_2_kaminelaBlink", "Sounds/Effect/Fantasy_Game_Water_Bolt_2_kaminelaBlink.wav", false, false);
	_loading->LoadSound("fire", "Sounds/Effect/fire.wav", false, false);
	_loading->LoadSound("fireball_Bart_K", "Sounds/Effect/fireball_Bart_K.wav", false, false);
	_loading->LoadSound("fireball_blast_projectile_spell_06", "Sounds/Effect/fireball_blast_projectile_spell_06.wav", false, false);
	_loading->LoadSound("fireball_impact_burn_01", "Sounds/Effect/fireball_impact_burn_01.wav", false, false);
	_loading->LoadSound("fireball_impact_burn_03", "Sounds/Effect/fireball_impact_burn_03.wav", false, false);
	_loading->LoadSound("fireball_impact_burn_03_BeetleEx", "Sounds/Effect/fireball_impact_burn_03_BeetleEx.wav", false, false);
	_loading->LoadSound("fireball_impact_burn_04_TriFire", "Sounds/Effect/fireball_impact_burn_04_TriFire.wav", false, false);
	_loading->LoadSound("gas_large_flame_ignite_01", "Sounds/Effect/gas_large_flame_ignite_01.wav", false, false);
	_loading->LoadSound("GrowAbility", "Sounds/Effect/GrowAbility.wav", false, false);
	_loading->LoadSound("hardmode off", "Sounds/Effect/hardmode off.wav", false, false);
	_loading->LoadSound("hardmode on", "Sounds/Effect/hardmode on.wav", false, false);
	_loading->LoadSound("heartbeat", "Sounds/Effect/heartbeat.wav", false, false);
	_loading->LoadSound("Hit_Monster", "Sounds/Effect/Hit_Monster.wav", false, false);
	_loading->LoadSound("Hit_Player", "Sounds/Effect/Hit_Player.wav", false, false);
	_loading->LoadSound("ice", "Sounds/Effect/ice.wav", false, false);
	_loading->LoadSound("ice_blast_projectile_spell_01", "Sounds/Effect/ice_blast_projectile_spell_01.wav", false, false);
	_loading->LoadSound("ice_blast_projectile_spell_02", "Sounds/Effect/ice_blast_projectile_spell_02.wav", false, false);
	_loading->LoadSound("ice_blast_projectile_spell_04", "Sounds/Effect/ice_blast_projectile_spell_04.wav", false, false);
	_loading->LoadSound("ice_spell_forming_shards_01", "Sounds/Effect/ice_spell_forming_shards_01.wav", false, false);
	_loading->LoadSound("ice_spell_forming_shards_02", "Sounds/Effect/ice_spell_forming_shards_02.wav", false, false);
	_loading->LoadSound("ice_spell_forming_shards_03", "Sounds/Effect/ice_spell_forming_shards_03.wav", false, false);
	_loading->LoadSound("ice_spell_forming_shards_04", "Sounds/Effect/ice_spell_forming_shards_04.wav", false, false);
	_loading->LoadSound("ice_spell_freeze_frost_01", "Sounds/Effect/ice_spell_freeze_frost_01.wav", false, false);
	_loading->LoadSound("ice_spell_freeze_frost_02_iceslime", "Sounds/Effect/ice_spell_freeze_frost_02_iceslime.wav", false, false);
	_loading->LoadSound("ice_spell_freeze_small_02", "Sounds/Effect/ice_spell_freeze_small_02.wav", false, false);
	_loading->LoadSound("ice_spell_freeze_small_04", "Sounds/Effect/ice_spell_freeze_small_04.wav", false, false);
	_loading->LoadSound("iceball", "Sounds/Effect/iceball.wav", false, false);
	_loading->LoadSound("joejoon", "Sounds/Effect/joejoon.wav", false, false);
	_loading->LoadSound("light_in_dark_spell_01_Dungreed_Spell", "Sounds/Effect/light_in_dark_spell_01_Dungreed_Spell.wav", false, false);
	_loading->LoadSound("livna_attack", "Sounds/Effect/livna_attack.wav", false, false);
	_loading->LoadSound("livna_debris", "Sounds/Effect/livna_debris.wav", false, false);
	_loading->LoadSound("milkbudan deal", "Sounds/Effect/milkbudan deal.wav", false, false);
	_loading->LoadSound("milkbudan heal", "Sounds/Effect/milkbudan heal.wav", false, false);
	_loading->LoadSound("NPC_�Ǽ�", "Sounds/Effect/NPC_�Ǽ�.wav", false, false);
	_loading->LoadSound("NPC_�������_���ñ�", "Sounds/Effect/NPC_�������_���ñ�.wav", false, false);
	_loading->LoadSound("NPC_���", "Sounds/Effect/NPC_���.wav", false, false);
	_loading->LoadSound("NPC_�������ڿ���", "Sounds/Effect/NPC_�������ڿ���.wav", false, false);
	_loading->LoadSound("NPC_����������", "Sounds/Effect/NPC_����������.wav", false, false);
	_loading->LoadSound("NPC_�����Ǹ�", "Sounds/Effect/NPC_�����Ǹ�.wav", false, false);
	_loading->LoadSound("NPC_���Ըӽ�", "Sounds/Effect/NPC_���Ըӽ�.wav", false, false);
	_loading->LoadSound("NPC_�Ĵ�_���ñ�", "Sounds/Effect/NPC_�Ĵ�_���ñ�.wav", false, false);
	_loading->LoadSound("NPC_�Ĵ�_���ñ�2", "Sounds/Effect/NPC_�Ĵ�_���ñ�2.wav", false, false);
	_loading->LoadSound("NPC_���ֻ��ڿ���", "Sounds/Effect/NPC_���ֻ��ڿ���.wav", false, false);
	_loading->LoadSound("NPC_�ູ", "Sounds/Effect/NPC_�ູ.wav", false, false);
	_loading->LoadSound("NPC_�Ʒü�_Ư�����", "Sounds/Effect/NPC_�Ʒü�_Ư�����.wav", false, false);
	_loading->LoadSound("NPC_�Ʒü�_Ư�����2", "Sounds/Effect/NPC_�Ʒü�_Ư�����2.wav", false, false);
	_loading->LoadSound("PEEP", "Sounds/Effect/PEEP.wav", false, false);
	_loading->LoadSound("SF_����EMP", "Sounds/Effect/SF_����EMP.wav", false, false);
	_loading->LoadSound("Skorpion-Kibblesbob", "Sounds/Effect/Skorpion-Kibblesbob.wav", false, false);
	_loading->LoadSound("��ȭ�ϴµ��� �Ҹ�", "Sounds/Effect/��ȭ�ϴµ��� �Ҹ�.wav", false, false);
	_loading->LoadSound("��ģ���̾", "Sounds/Effect/��ģ���̾.wav", false, false);
	_loading->LoadSound("��ĥ�� �ڸ��� �Ҹ�", "Sounds/Effect/��ĥ�� �ڸ��� �Ҹ�.wav", false, false);
	_loading->LoadSound("��ĥ��_�Դ�_�Ҹ�", "Sounds/Effect/��ĥ��_�Դ�_�Ҹ�.wav", false, false);
	_loading->LoadSound("�ȴ¼Ҹ� (1)", "Sounds/Effect/�ȴ¼Ҹ� (1).wav", false, false);
	_loading->LoadSound("�ȴ¼Ҹ� (2)", "Sounds/Effect/�ȴ¼Ҹ� (2).wav", false, false);
	_loading->LoadSound("�ȴ¼Ҹ� (3)", "Sounds/Effect/�ȴ¼Ҹ� (3).wav", false, false);
	_loading->LoadSound("�ȴ¼Ҹ� (4)", "Sounds/Effect/�ȴ¼Ҹ� (4).wav", false, false);
	_loading->LoadSound("����_BLOCK", "Sounds/Effect/����_BLOCK.wav", false, false);
	_loading->LoadSound("����_LEVELUP", "Sounds/Effect/����_LEVELUP.wav", false, false);
	_loading->LoadSound("����_����_����������", "Sounds/Effect/����_����_����������.wav", false, false);
	_loading->LoadSound("����_����������", "Sounds/Effect/����_����������.wav", false, false);
	_loading->LoadSound("����_��¢", "Sounds/Effect/����_��¢.wav", false, false);
	_loading->LoadSound("����_���⽺��", "Sounds/Effect/����_���⽺��.wav", false, false);
	_loading->LoadSound("����_����", "Sounds/Effect/����_����.wav", false, false);
	_loading->LoadSound("����_�÷ð�����Ŭ����", "Sounds/Effect/����_�÷ð�����Ŭ����.wav", false, false);
	_loading->LoadSound("����_�÷ñغ�", "Sounds/Effect/����_�÷ñغ�.wav", false, false);
	_loading->LoadSound("����_���������� (1)", "Sounds/Effect/����_���������� (1).wav", false, false);
	_loading->LoadSound("����_���������� (2)", "Sounds/Effect/����_���������� (2).wav", false, false);
	_loading->LoadSound("����_����������", "Sounds/Effect/����_����������.wav", false, false);
	_loading->LoadSound("����_Ŭ����", "Sounds/Effect/����_Ŭ����.wav", false, false);
	_loading->LoadSound("����_�۹�����", "Sounds/Effect/����_�۹�����.wav", false, false);
	_loading->LoadSound("������������", "Sounds/Effect/������������.wav", false, false);
	_loading->LoadSound("�뽬�Ҹ�", "Sounds/Effect/�뽬�Ҹ�.wav", false, false);
	_loading->LoadSound("�����̵�", "Sounds/Effect/�����̵�.wav", false, false);
	_loading->LoadSound("��Ʈ��", "Sounds/Effect/��Ʈ��.wav", false, false);
	_loading->LoadSound("���μ��� (1)", "Sounds/Effect/���μ��� (1).wav", false, false);
	_loading->LoadSound("���μ��� (2)", "Sounds/Effect/���μ��� (2).wav", false, false);
	_loading->LoadSound("���μ���", "Sounds/Effect/���μ���.wav", false, false);
	_loading->LoadSound("���μ���_õ��ġ�µ���", "Sounds/Effect/���μ���_õ��ġ�µ���.wav", false, false);
	_loading->LoadSound("�εο�", "Sounds/Effect/�εο�.wav", false, false);
	_loading->LoadSound("��ٹ̴Ϻ���_�ڷ���Ʈ", "Sounds/Effect/��ٹ̴Ϻ���_�ڷ���Ʈ.wav", false, false);
	_loading->LoadSound("���ε�_�⺻", "Sounds/Effect/���ε�_�⺻.wav", false, false);
	_loading->LoadSound("���ε�_ª��", "Sounds/Effect/���ε�_ª��.wav", false, false);
	_loading->LoadSound("�Դ���Ż����������", "Sounds/Effect/�Դ���Ż����������.wav", false, false);
	_loading->LoadSound("�۸��� �п�", "Sounds/Effect/�۸��� �п�.wav", false, false);
	_loading->LoadSound("����_�ü�_�߻�", "Sounds/Effect/����_�ü�_�߻�.wav", false, false);
	_loading->LoadSound("����_�ü�_�޿�", "Sounds/Effect/����_�ü�_�޿�.wav", false, false);
	_loading->LoadSound("����_���_������", "Sounds/Effect/����_���_������.wav", false, false);
	_loading->LoadSound("����_���������", "Sounds/Effect/����_���������.wav", false, false);
	_loading->LoadSound("����_�κ����_¢��", "Sounds/Effect/����_�κ����_¢��.wav", false, false);
	_loading->LoadSound("����_���ڵ��", "Sounds/Effect/����_���ڵ��.wav", false, false);
	_loading->LoadSound("����_���� (1)", "Sounds/Effect/����_���� (1).wav", false, false);
	_loading->LoadSound("����_���� (2)", "Sounds/Effect/����_���� (2).wav", false, false);
	_loading->LoadSound("����_���", "Sounds/Effect/����_���.wav", false, false);
	_loading->LoadSound("����_���� (1)", "Sounds/Effect/����_���� (1).wav", false, false);
	_loading->LoadSound("����_���� (2)", "Sounds/Effect/����_���� (2).wav", false, false);
	_loading->LoadSound("����_���� (3)", "Sounds/Effect/����_���� (3).wav", false, false);
	_loading->LoadSound("����_���� (4)", "Sounds/Effect/����_���� (4).wav", false, false);
	_loading->LoadSound("����_��� (1)", "Sounds/Effect/����_��� (1).wav", false, false);
	_loading->LoadSound("����_��� (2)", "Sounds/Effect/����_��� (2).wav", false, false);
	_loading->LoadSound("����_���", "Sounds/Effect/����_���.wav", false, false);
	_loading->LoadSound("����_����������", "Sounds/Effect/����_����������.wav", false, false);
	_loading->LoadSound("����_����������2", "Sounds/Effect/����_����������2.wav", false, false);
	_loading->LoadSound("����_���¢�� (1)", "Sounds/Effect/����_���¢�� (1).wav", false, false);
	_loading->LoadSound("����_���¢�� (2)", "Sounds/Effect/����_���¢�� (2).wav", false, false);
	_loading->LoadSound("����_���¢�� (3)", "Sounds/Effect/����_���¢�� (3).wav", false, false);
	_loading->LoadSound("����_����ź�߻��_�߻�", "Sounds/Effect/����_����ź�߻��_�߻�.wav", false, false);
	_loading->LoadSound("����_���⸦�������µ巡��", "Sounds/Effect/����_���⸦�������µ巡��.wav", false, false);
	_loading->LoadSound("����_�ɸ����ν�_��", "Sounds/Effect/����_�ɸ����ν�_��.wav", false, false);
	_loading->LoadSound("����_ū�Ẕ́��_����", "Sounds/Effect/����_ū�Ẕ́��_����.wav", false, false);
	_loading->LoadSound("����_ū���_¢��", "Sounds/Effect/����_ū���_¢��.wav", false, false);
	_loading->LoadSound("����_ū����", "Sounds/Effect/����_ū����.wav", false, false);
	_loading->LoadSound("����_Ʈ������", "Sounds/Effect/����_Ʈ������.wav", false, false);
	_loading->LoadSound("����_��ź����", "Sounds/Effect/����_��ź����.wav", false, false);
	_loading->LoadSound("����_AK", "Sounds/Effect/����_AK.wav", false, false);
	_loading->LoadSound("����_M1Garand", "Sounds/Effect/����_M1Garand.wav", false, false);
	_loading->LoadSound("����_M1Garand���ε�", "Sounds/Effect/����_M1Garand���ε�.wav", false, false);
	_loading->LoadSound("����_M4A1", "Sounds/Effect/����_M4A1.wav", false, false);
	_loading->LoadSound("����_RPG", "Sounds/Effect/����_RPG.wav", false, false);
	_loading->LoadSound("����_UZI �߻�", "Sounds/Effect/����_UZI �߻�.wav", false, false);
	_loading->LoadSound("����_��Ʋ���ǹ߻�", "Sounds/Effect/����_��Ʋ���ǹ߻�.wav", false, false);
	_loading->LoadSound("����_��Ʋ������ȭ", "Sounds/Effect/����_��Ʋ������ȭ.wav", false, false);
	_loading->LoadSound("����_����", "Sounds/Effect/����_����.wav", false, false);
	_loading->LoadSound("����_����2", "Sounds/Effect/����_����2.wav", false, false);
	_loading->LoadSound("����_�������_����", "Sounds/Effect/����_�������_����.wav", false, false);
	_loading->LoadSound("����_�������_��ų", "Sounds/Effect/����_�������_��ų.wav", false, false);
	_loading->LoadSound("����_��Ÿ (1)", "Sounds/Effect/����_��Ÿ (1).wav", false, false);
	_loading->LoadSound("����_��Ÿ (2)", "Sounds/Effect/����_��Ÿ (2).wav", false, false);
	_loading->LoadSound("����_��Ÿ (3)", "Sounds/Effect/����_��Ÿ (3).wav", false, false);
	_loading->LoadSound("����_��Ÿ (4)", "Sounds/Effect/����_��Ÿ (4).wav", false, false);
	_loading->LoadSound("����_��Ÿ (5)", "Sounds/Effect/����_��Ÿ (5).wav", false, false);
	_loading->LoadSound("����_��Ÿ (6)", "Sounds/Effect/����_��Ÿ (6).wav", false, false);
	_loading->LoadSound("����_������", "Sounds/Effect/����_������.wav", false, false);
	_loading->LoadSound("����_����Ź�ѹ߻���", "Sounds/Effect/����_����Ź�ѹ߻���.wav", false, false);
	_loading->LoadSound("����_����ҵ�", "Sounds/Effect/����_����ҵ�.wav", false, false);
	_loading->LoadSound("����_�μհ�", "Sounds/Effect/����_�μհ�.wav", false, false);
	_loading->LoadSound("����_��Ź�ѹ߻���", "Sounds/Effect/����_��Ź�ѹ߻���.wav", false, false);
	_loading->LoadSound("����_����� �����", "Sounds/Effect/����_����� �����.wav", false, false);
	_loading->LoadSound("����_������", "Sounds/Effect/����_������.wav", false, false);
	_loading->LoadSound("����_���þȷ귿_����", "Sounds/Effect/����_���þȷ귿_����.wav", false, false);
	_loading->LoadSound("����_�������߻�", "Sounds/Effect/����_�������߻�.wav", false, false);
	_loading->LoadSound("����_�����Ǿ�", "Sounds/Effect/����_�����Ǿ�.wav", false, false);
	_loading->LoadSound("����_�𽺹��׼���", "Sounds/Effect/����_�𽺹��׼���.wav", false, false);
	_loading->LoadSound("����_��帮�� (1)", "Sounds/Effect/����_��帮�� (1).wav", false, false);
	_loading->LoadSound("����_��帮�� (2)", "Sounds/Effect/����_��帮�� (2).wav", false, false);
	_loading->LoadSound("����_���ſ��ֵθ�", "Sounds/Effect/����_���ſ��ֵθ�.wav", false, false);
	_loading->LoadSound("����_���� �Ѹ�", "Sounds/Effect/����_���� �Ѹ�.wav", false, false);
	_loading->LoadSound("����_�����ö��̳�����", "Sounds/Effect/����_�����ö��̳�����.wav", false, false);
	_loading->LoadSound("����_�θ޶��迭", "Sounds/Effect/����_�θ޶��迭.wav", false, false);
	_loading->LoadSound("����_�����ε���", "Sounds/Effect/����_�����ε���.wav", false, false);
	_loading->LoadSound("����_�����ε���_����", "Sounds/Effect/����_�����ε���_����.wav", false, false);
	_loading->LoadSound("����_��ź��", "Sounds/Effect/����_��ź��.wav", false, false);
	_loading->LoadSound("����_����", "Sounds/Effect/����_����.wav", false, false);
	_loading->LoadSound("����_�����Ǵ��Ǵ�", "Sounds/Effect/����_�����Ǵ��Ǵ�.wav", false, false);
	_loading->LoadSound("����_�������������� (1)", "Sounds/Effect/����_�������������� (1).wav", false, false);
	_loading->LoadSound("����_�������������� (2)", "Sounds/Effect/����_�������������� (2).wav", false, false);
	_loading->LoadSound("����_���", "Sounds/Effect/����_���.wav", false, false);
	_loading->LoadSound("����_�������۹߻�", "Sounds/Effect/����_�������۹߻�.wav", false, false);
	_loading->LoadSound("����_��������", "Sounds/Effect/����_��������.wav", false, false);
	_loading->LoadSound("����_�����Ӹ���Ŀ", "Sounds/Effect/����_�����Ӹ���Ŀ.wav", false, false);
	_loading->LoadSound("����_���ְ˿����ǽ���", "Sounds/Effect/����_���ְ˿����ǽ���.wav", false, false);
	_loading->LoadSound("����_���ְ�ȿ����", "Sounds/Effect/����_���ְ�ȿ����.wav", false, false);
	_loading->LoadSound("����_����âȿ��", "Sounds/Effect/����_����âȿ��.wav", false, false);
	_loading->LoadSound("����_��������", "Sounds/Effect/����_��������.wav", false, false);
	_loading->LoadSound("����_ä��", "Sounds/Effect/����_ä��.wav", false, false);
	_loading->LoadSound("����_īŸ�� (1)", "Sounds/Effect/����_īŸ�� (1).wav", false, false);
	_loading->LoadSound("����_īŸ�� (2)", "Sounds/Effect/����_īŸ�� (2).wav", false, false);
	_loading->LoadSound("����_īŸ�� (3)", "Sounds/Effect/����_īŸ�� (3).wav", false, false);
	_loading->LoadSound("����_Į������", "Sounds/Effect/����_Į������.wav", false, false);
	_loading->LoadSound("����_ĳ��߻� (1)", "Sounds/Effect/����_ĳ��߻� (1).wav", false, false);
	_loading->LoadSound("����_ĳ��߻� (2)", "Sounds/Effect/����_ĳ��߻� (2).wav", false, false);
	_loading->LoadSound("����_ĳ��߻� (3)", "Sounds/Effect/����_ĳ��߻� (3).wav", false, false);
	_loading->LoadSound("����_ũ�ν�����", "Sounds/Effect/����_ũ�ν�����.wav", false, false);
	_loading->LoadSound("����_���ļ�ũ", "Sounds/Effect/����_���ļ�ũ.wav", false, false);
	_loading->LoadSound("����_�������� (1)", "Sounds/Effect/����_�������� (1).wav", false, false);
	_loading->LoadSound("����_�������� (2)", "Sounds/Effect/����_�������� (2).wav", false, false);
	_loading->LoadSound("����_��ź�߻��", "Sounds/Effect/����_��ź�߻��.wav", false, false);
	_loading->LoadSound("����_���ν�Ʈ���", "Sounds/Effect/����_���ν�Ʈ���.wav", false, false);
	_loading->LoadSound("����_�ǽ��� (1)", "Sounds/Effect/����_�ǽ��� (1).wav", false, false);
	_loading->LoadSound("����_�ǽ��� (2)", "Sounds/Effect/����_�ǽ��� (2).wav", false, false);
	_loading->LoadSound("����_�ذ�հ�", "Sounds/Effect/����_�ذ�հ�.wav", false, false);
	_loading->LoadSound("����_��ī����", "Sounds/Effect/����_��ī����.wav", false, false);
	_loading->LoadSound("����_ȣ���̱ǹ�", "Sounds/Effect/����_ȣ���̱ǹ�.wav", false, false);
	_loading->LoadSound("����_ȭ������", "Sounds/Effect/����_ȭ������.wav", false, false);
	_loading->LoadSound("����_Ȱ�߻�", "Sounds/Effect/����_Ȱ�߻�.wav", false, false);
	_loading->LoadSound("���Ⱑ�¼Ҹ�", "Sounds/Effect/���Ⱑ�¼Ҹ�.wav", false, false);
	_loading->LoadSound("�����ֵθ��ٶ��Ҹ���", "Sounds/Effect/�����ֵθ��ٶ��Ҹ���.wav", false, false);
	_loading->LoadSound("���𰡿���", "Sounds/Effect/���𰡿���.wav", false, false);
	_loading->LoadSound("�� ����", "Sounds/Effect/�� ����.wav", false, false);
	_loading->LoadSound("���� �۵��ϴ� �Ҹ�", "Sounds/Effect/���� �۵��ϴ� �Ҹ�.wav", false, false);
	_loading->LoadSound("��������", "Sounds/Effect/��������.wav", false, false);
	_loading->LoadSound("�̿���", "Sounds/Effect/�̿���.wav", false, false);
	_loading->LoadSound("�ٶ��� ������ �ֵθ���", "Sounds/Effect/�ٶ��� ������ �ֵθ���.wav", false, false);
	_loading->LoadSound("�����¼Ҹ�", "Sounds/Effect/�����¼Ҹ�.wav", false, false);
	_loading->LoadSound("����_��������_�߻�", "Sounds/Effect/����_��������_�߻�.wav", false, false);
	_loading->LoadSound("����_��������_����ȿ����", "Sounds/Effect/����_��������_����ȿ����.wav", false, false);
	_loading->LoadSound("����_�󽽸�_����������", "Sounds/Effect/����_�󽽸�_����������.wav", false, false);
	_loading->LoadSound("����_�󽽸�_��ŸŬ", "Sounds/Effect/����_�󽽸�_��ŸŬ.wav", false, false);
	_loading->LoadSound("����_�󽽸�_����", "Sounds/Effect/����_�󽽸�_����.wav", false, false);
	_loading->LoadSound("����_������_����", "Sounds/Effect/����_������_����.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_���Ǽ�ȯ", "Sounds/Effect/����_�Ƹ���_���Ǽ�ȯ.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_�Ҹ��߻�", "Sounds/Effect/����_�Ƹ���_�Ҹ��߻�.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_����ȯ", "Sounds/Effect/����_�Ƹ���_����ȯ.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_������", "Sounds/Effect/����_�Ƹ���_������.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_���׸��ö����", "Sounds/Effect/����_�Ƹ���_���׸��ö����.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_�Ҳɹ߻�", "Sounds/Effect/����_�Ƹ���_�Ҳɹ߻�.wav", false, false);
	_loading->LoadSound("����_�Ƹ���_��� (1)", "Sounds/Effect/����_�Ƹ���_��� (1).wav", false, false);
	_loading->LoadSound("����_�Ƹ���_��� (2)", "Sounds/Effect/����_�Ƹ���_��� (2).wav", false, false);
	_loading->LoadSound("����_�Ƹ���_��� (3)", "Sounds/Effect/����_�Ƹ���_��� (3).wav", false, false);
	_loading->LoadSound("����_�Ƹ���_��� (4)", "Sounds/Effect/����_�Ƹ���_��� (4).wav", false, false);
	_loading->LoadSound("����_�Ƹ���_��� (5)", "Sounds/Effect/����_�Ƹ���_��� (5).wav", false, false);
	_loading->LoadSound("����_�Ƹ���_�ָ�ġ��", "Sounds/Effect/����_�Ƹ���_�ָ�ġ��.wav", false, false);
	_loading->LoadSound("����_������_������ũ����", "Sounds/Effect/����_������_������ũ����.wav", false, false);
	_loading->LoadSound("����_������_���¢�����޼Ҹ�", "Sounds/Effect/����_������_���¢�����޼Ҹ�.wav", false, false);
	_loading->LoadSound("����_����ī_��������", "Sounds/Effect/����_����ī_��������.wav", false, false);
	_loading->LoadSound("����_����ī_����ߺ����� (1)", "Sounds/Effect/����_����ī_����ߺ����� (1).wav", false, false);
	_loading->LoadSound("����_����ī_����ߺ����� (2)", "Sounds/Effect/����_����ī_����ߺ����� (2).wav", false, false);
	_loading->LoadSound("����_����ī_�帱", "Sounds/Effect/����_����ī_�帱.wav", false, false);
	_loading->LoadSound("����_����ī_������ũ����", "Sounds/Effect/����_����ī_������ũ����.wav", false, false);
	_loading->LoadSound("����_����ī_��Ҽ�ȯ", "Sounds/Effect/����_����ī_��Ҽ�ȯ.wav", false, false);
	_loading->LoadSound("����_����ī_���¢�� (1)", "Sounds/Effect/����_����ī_���¢�� (1).wav", false, false);
	_loading->LoadSound("����_����ī_���¢�� (2)", "Sounds/Effect/����_����ī_���¢�� (2).wav", false, false);
	_loading->LoadSound("����_����ī_���¢��", "Sounds/Effect/����_����ī_���¢��.wav", false, false);
	_loading->LoadSound("����_����ī_�ڷ���Ʈ", "Sounds/Effect/����_����ī_�ڷ���Ʈ.wav", false, false);
	_loading->LoadSound("����_�����_�ٿ;�", "Sounds/Effect/����_�����_�ٿ;�.wav", false, false);
	_loading->LoadSound("����_�����_������ũ��ȯ", "Sounds/Effect/����_�����_������ũ��ȯ.wav", false, false);
	_loading->LoadSound("����_�����_���ð�", "Sounds/Effect/����_�����_���ð�.wav", false, false);
	_loading->LoadSound("����_ī�̳ڶ�_2������", "Sounds/Effect/����_ī�̳ڶ�_2������.wav", false, false);
	_loading->LoadSound("����_ī�̳ڶ�_����", "Sounds/Effect/����_ī�̳ڶ�_����.wav", false, false);
	_loading->LoadSound("����_ī�̳ڶ�_������", "Sounds/Effect/����_ī�̳ڶ�_������.wav", false, false);
	_loading->LoadSound("����_ī�̳ڶ�_���", "Sounds/Effect/����_ī�̳ڶ�_���.wav", false, false);
	_loading->LoadSound("����_ī�̳ڶ�_���Ž�", "Sounds/Effect/����_ī�̳ڶ�_���Ž�.wav", false, false);
	_loading->LoadSound("����_ī�̳ڶ�_�����Ʈ����", "Sounds/Effect/����_ī�̳ڶ�_�����Ʈ����.wav", false, false);
	_loading->LoadSound("���������幮", "Sounds/Effect/���������幮.wav", false, false);
	_loading->LoadSound("��ȣ������", "Sounds/Effect/��ȣ������.wav", false, false);
	_loading->LoadSound("�ұ��ѹٶ��̺Ҿ�´�", "Sounds/Effect/�ұ��ѹٶ��̺Ҿ�´�.wav", false, false);
	_loading->LoadSound("�ҵ���", "Sounds/Effect/�ҵ���.wav", false, false);
	_loading->LoadSound("������", "Sounds/Effect/������.wav", false, false);
	_loading->LoadSound("������������", "Sounds/Effect/������������.wav", false, false);
	_loading->LoadSound("�������", "Sounds/Effect/�������.wav", false, false);
	_loading->LoadSound("���µ��ѼҸ� (1)", "Sounds/Effect/���µ��ѼҸ� (1).wav", false, false);       //�븮�� �Ѿ���
	_loading->LoadSound("���µ��ѼҸ� (2)", "Sounds/Effect/���µ��ѼҸ� (2).wav", false, false);
	_loading->LoadSound("��Ʈȿ��", "Sounds/Effect/��Ʈȿ��.wav", false, false);
	_loading->LoadSound("����ġ ��", "Sounds/Effect/����ġ ��.wav", false, false);
	_loading->LoadSound("����ġ�Ҹ�", "Sounds/Effect/����ġ�Ҹ�.wav", false, false);
	_loading->LoadSound("���丮_������ (1)", "Sounds/Effect/���丮_������ (1).wav", false, false);
	_loading->LoadSound("���丮_������ (2)", "Sounds/Effect/���丮_������ (2).wav", false, false);
	_loading->LoadSound("���丮_������ (3)", "Sounds/Effect/���丮_������ (3).wav", false, false);

	_loading->LoadSound("��������", "Sounds/Effect/��������.wav", false, false);

	_loading->LoadSound("�����Ӻ�", "Sounds/Effect/�����Ӻ�.wav", false, false);
	_loading->LoadSound("�ǹ�����", "Sounds/Effect/�ǹ�����.wav", false, false);
	_loading->LoadSound("�������ݶ� (1)", "Sounds/Effect/�������ݶ� (1).wav", false, false);
	_loading->LoadSound("�������ݶ� (2)", "Sounds/Effect/�������ݶ� (2).wav", false, false);
	_loading->LoadSound("�������ݶ� (3)", "Sounds/Effect/�������ݶ� (3).wav", false, false);
	_loading->LoadSound("�������ݶ� (4)", "Sounds/Effect/�������ݶ� (4).wav", false, false);
	_loading->LoadSound("������_HARNESSMAGIC", "Sounds/Effect/������_HARNESSMAGIC.wav", false, false);
	_loading->LoadSound("������_PHAX", "Sounds/Effect/������_PHAX.wav", false, false);
	_loading->LoadSound("������_RADDRAGONKILLER", "Sounds/Effect/������_RADDRAGONKILLER.wav", false, false);
	_loading->LoadSound("������_������˽�ų", "Sounds/Effect/������_������˽�ų.wav", false, false);
	_loading->LoadSound("������_�ռҵ彺ų", "Sounds/Effect/������_�ռҵ彺ų.wav", false, false);
	_loading->LoadSound("������_���̽�����", "Sounds/Effect/������_���̽�����.wav", false, false);
	_loading->LoadSound("������_������_�Ǹ��Ǽ�", "Sounds/Effect/������_������_�Ǹ��Ǽ�.wav", false, false);

	_loading->LoadSound("������_������ݱ�", "Sounds/Effect/������_������ݱ�.wav", false, false);
	_loading->LoadSound("������_��Ʈ��", "Sounds/Effect/������_��Ʈ��.wav", false, false);
	_loading->LoadSound("������_Ÿ���ǵ彺ų", "Sounds/Effect/������_Ÿ���ǵ彺ų.wav", false, false);
	_loading->LoadSound("������_��ź�ٱ���", "Sounds/Effect/������_��ź�ٱ���.wav", false, false);
	_loading->LoadSound("����������", "Sounds/Effect/����������.wav", false, false);
	_loading->LoadSound("������ȹ��", "Sounds/Effect/������ȹ��.wav", false, false);
	_loading->LoadSound("���渶�������߻���", "Sounds/Effect/���渶�������߻���.wav", false, false);
	_loading->LoadSound("���������º��μ���", "Sounds/Effect/���������º��μ���.wav", false, false);
	_loading->LoadSound("����ī��⵹�μ��� (1)", "Sounds/Effect/����ī��⵹�μ��� (1).wav", false, false);
	_loading->LoadSound("����ī��⵹�μ��� (2)", "Sounds/Effect/����ī��⵹�μ��� (2).wav", false, false);
	_loading->LoadSound("������Ʈ_HPȸ��", "Sounds/Effect/������Ʈ_HPȸ��.wav", false, false);
	_loading->LoadSound("������Ʈ_����_�ı�_�����۷���", "Sounds/Effect/������Ʈ_����_�ı�_�����۷���.wav", false, false);
	_loading->LoadSound("������Ʈ_���ڿ���", "Sounds/Effect/������Ʈ_���ڿ���.wav", false, false);
	_loading->LoadSound("������Ʈ_���ڿ���_���žƴ�", "Sounds/Effect/������Ʈ_���ڿ���_���žƴ�.wav", false, false);
	_loading->LoadSound("������Ʈ_�������ڿ���", "Sounds/Effect/������Ʈ_�������ڿ���.wav", false, false);
	_loading->LoadSound("������Ʈ_��μ� (1)", "Sounds/Effect/������Ʈ_��μ� (1).wav", false, false);
	_loading->LoadSound("������Ʈ_��μ� (2)", "Sounds/Effect/������Ʈ_��μ� (2).wav", false, false);
	_loading->LoadSound("������Ʈ_��μ� (3)", "Sounds/Effect/������Ʈ_��μ� (3).wav", false, false);
	_loading->LoadSound("�����PPTȿ����", "Sounds/Effect/�����PPTȿ����.wav", false, false);
	_loading->LoadSound("���", "Sounds/Effect/���.wav", false, false);
	_loading->LoadSound("���ļ��� (1)", "Sounds/Effect/���ļ��� (1).wav", false, false);
	_loading->LoadSound("���ļ��� (2)", "Sounds/Effect/���ļ��� (2).wav", false, false);
	_loading->LoadSound("���ļ��� (3)", "Sounds/Effect/���ļ��� (3).wav", false, false);
	_loading->LoadSound("�̷�����_����ħ", "Sounds/Effect/�̷�����_����ħ.wav", false, false);
	_loading->LoadSound("�κ��丮����", "Sounds/Effect/�κ��丮����.wav", false, false);
	_loading->LoadSound("��ֹ�_���ÿ�", "Sounds/Effect/��ֹ�_���ÿ�.wav", false, false);
	_loading->LoadSound("�����ɲ���", "Sounds/Effect/�����ɲ���.wav", false, false);
	_loading->LoadSound("����", "Sounds/Effect/����.wav", false, false);
	_loading->LoadSound("�����ѷ������߻�", "Sounds/Effect/�����ѷ������߻�.wav", false, false);
	_loading->LoadSound("����", "Sounds/Effect/����.wav", false, false);
	_loading->LoadSound("¡�ۺ� (1)", "Sounds/Effect/¡�ۺ� (1).wav", false, false);
	_loading->LoadSound("¡�ۺ� (2)", "Sounds/Effect/¡�ۺ� (2).wav", false, false);
	_loading->LoadSound("¡�ۺ� (3)", "Sounds/Effect/¡�ۺ� (3).wav", false, false);
	_loading->LoadSound("ª�Խ�¼Ҹ�", "Sounds/Effect/ª�Խ�¼Ҹ�.wav", false, false);
	_loading->LoadSound("õ�ջ�", "Sounds/Effect/õ�ջ�.wav", false, false);
	_loading->LoadSound("ġ�µ���SF�Ҹ�", "Sounds/Effect/ġ�µ���SF�Ҹ�.wav", false, false);
	_loading->LoadSound("Źġ�¼Ҹ�", "Sounds/Effect/Źġ�¼Ҹ�.wav", false, false);
	_loading->LoadSound("��Ż����", "Sounds/Effect/��Ż����.wav", false, false);
	_loading->LoadSound("���� (1)", "Sounds/Effect/���� (1).wav", false, false);
	_loading->LoadSound("���� (2)", "Sounds/Effect/���� (2).wav", false, false);
	_loading->LoadSound("����_ª��", "Sounds/Effect/����_ª��.wav", false, false);
	_loading->LoadSound("����_ŭ", "Sounds/Effect/����_ŭ.wav", false, false);
	_loading->LoadSound("��ź�Ҹ�", "Sounds/Effect/��ź�Ҹ�.wav", false, false);
	_loading->LoadSound("ǳ�����Ҹ� LONG", "Sounds/Effect/ǳ�����Ҹ� LONG.wav", false, false);
	_loading->LoadSound("����", "Sounds/Effect/����.wav", false, false);
	_loading->LoadSound("����", "Sounds/Effect/����.wav", false, false);
	_loading->LoadSound("�ֵθ���_������ (1)", "Sounds/Effect/�ֵθ���_������ (1).wav", false, false);
	_loading->LoadSound("�ֵθ���_������ (2)", "Sounds/Effect/�ֵθ���_������ (2).wav", false, false);
	_loading->LoadSound("�ֵθ���_������ (3)", "Sounds/Effect/�ֵθ���_������ (3).wav", false, false);
	_loading->LoadSound("�ֵθ���_������ (4)", "Sounds/Effect/�ֵθ���_������ (4).wav", false, false);
	_loading->LoadSound("�ֵθ���_������ (5)", "Sounds/Effect/�ֵθ���_������ (5).wav", false, false);
	_loading->LoadSound("�ֵθ���_���ѹٶ�", "Sounds/Effect/�ֵθ���_���ѹٶ�.wav", false, false);
	_loading->LoadSound("�ֵθ���_���ſ� (1)", "Sounds/Effect/�ֵθ���_���ſ� (1).wav", false, false);
	_loading->LoadSound("�ֵθ���_���ſ� (2)", "Sounds/Effect/�ֵθ���_���ſ� (2).wav", false, false);
	_loading->LoadSound("�ֵθ���_���ſ� (3)", "Sounds/Effect/�ֵθ���_���ſ� (3).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (1)", "Sounds/Effect/�ֵθ���_��ô������ (1).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (2)", "Sounds/Effect/�ֵθ���_��ô������ (2).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (3)", "Sounds/Effect/�ֵθ���_��ô������ (3).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (4)", "Sounds/Effect/�ֵθ���_��ô������ (4).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (5)", "Sounds/Effect/�ֵθ���_��ô������ (5).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (6)", "Sounds/Effect/�ֵθ���_��ô������ (6).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (7)", "Sounds/Effect/�ֵθ���_��ô������ (7).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������ (8)", "Sounds/Effect/�ֵθ���_��ô������ (8).wav", false, false);

	_loading->LoadSound("�ֵθ���_��ô������2 (1)", "Sounds/Effect/�ֵθ���_��ô������2 (1).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������2 (2)", "Sounds/Effect/�ֵθ���_��ô������2 (2).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������2 (3)", "Sounds/Effect/�ֵθ���_��ô������2 (3).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������2 (4)", "Sounds/Effect/�ֵθ���_��ô������2 (4).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������2 (5)", "Sounds/Effect/�ֵθ���_��ô������2 (5).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������2 (6)", "Sounds/Effect/�ֵθ���_��ô������2 (6).wav", false, false);
	_loading->LoadSound("�ֵθ���_��ô������2 (7)", "Sounds/Effect/�ֵθ���_��ô������2 (7).wav", false, false);
	_loading->LoadSound("�ֵθ���_���r������2 (8)", "Sounds/Effect/�ֵθ���_���r������2 (8).wav", false, false);

}

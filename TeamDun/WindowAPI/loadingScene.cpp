#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	_loading = new Loading();
	_loading->init();

	SOUNDMANAGER->init();
	SOUNDMANAGER->addSound("ÀÎÆ®·Î »ç¿îµå", "Sounds/Effect/ÀÎÆ®·Î »ç¿îµå.wav", false, false);
	SOUNDMANAGER->play("ÀÎÆ®·Î »ç¿îµå");

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

	_text[0] = "´øÀüÀÌ ±¤³ªµµ·Ï Ã»¼ÒÇÏ´Â Áß...";
	_text[1] = "°ð Á×À» ÇØ°ñº´»çµéÀ» À§·ÎÇÏ´Â Áß...";
	_text[2] = "¹ÚÁã³óÀå¿¡¼­ ¹ÚÁã È¸À¯ÇÏ´Â Áß...";
	_text[3] = "¹Ì³ëÅ¸¿ì¸£½º¿Í ´Þ¸®±â ¿¬½ÀÇÏ´Â Áß...";
	_text[4] = "½ÅÀü¿¡¼­ ±¤¶õÀÇ Á¦»ç ÆÄÆ¼ Áñ±â´Â Áß...";
	_text[5] = "¹«±â»ó ¾Õ¿¡¼­ ÇÏ³ª ´õ ´Þ¶ó µûÁö´Â Áß...";
	_text[6] = "ÄÚµùÇÏ°í ¹ã»õ´Ù Áö°¢ÇÏ´Â Áß...";
	_text[7] = "´ø±×¸®µå ¿øÀÛ ÇÃ·¹ÀÌÇÏ´Ù ¸àÅ»ƒÆÁö´Â Áß..";
	_text[8] = "¹ê½ÃÀÇ ¶óÀÌºê°ø¿¬ °¨»óÇÏ´Â Áß...";
	_text[9] = "ºê·£Ä¡ º´ÇÕÇÏ´Ù ÇÁ·ÎÁ§Æ® ÅÍÁö´Â Áß...";
	_text[10] = "½Ä´ç ÀÌ¸ðÀÇ ÀýÂù À½½Ä ¸ÔÀ¸¸ç ´«¹° Èê¸®´Â Áß...";
	_text[11] = "ÇØ°ñ °­¾ÆÁö ºÐ¾ç¹Þ´Â Áß...";

	for (int i = 0; i < 50; i++)
	{
		int j = RANDOM->range(12);
		int k = RANDOM->range(12);
		string temp = _text[j];
		_text[j] = _text[k];
		_text[k] = temp;
	}

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

	// ÀÌ¹ÌÁö ·Îµå°¡ ¿Ï·áµÇ¸é ÀÌµ¿
	if (_currentGauge >= _loading->GetLoadItem().size())
	{
		LoadData();
		SCENEMANAGER->loadScene("½ÃÀÛÈ­¸é");
	}
	
	// ¾Æ´Ï¶ó¸é °è¼ÓÇØ¼­ ºÒ·¯¿À±â
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

	int percent = (int)((float)_currentGauge *(100 / (float)_loading->GetLoadItem().size() / 10));
	RECT rect = RectMake(0, 530, WINSIZEX, 300);

	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "NeoµÕ±Ù¸ð");
	HFONT OldFont;

	SetTextColor(getMemDC(), RGB(255,255,255));
	OldFont = (HFONT)SelectObject(getMemDC(), hFont);
	DrawText(getMemDC(), _text[percent].c_str(), -1, &rect, DT_CENTER | DT_WORDBREAK);
	IMAGEMANAGER->frameRender("number", getMemDC(), 710, 500,(int)((float)_currentGauge /(float)_loading->GetLoadItem().size()*100) % 10, 0);
	if ((int)((float)_currentGauge *(100 / (float)_loading->GetLoadItem().size()) / 10) > 0)
	IMAGEMANAGER->frameRender("number", getMemDC(), 690, 500, (float)_currentGauge *(100/(float)_loading->GetLoadItem().size()) / 10, 0);
	SelectObject(getMemDC(), OldFont);
	DeleteObject(hFont);
}

/// <summary>
/// CSVµ¥ÀÌÅÍµéÀ» ºÒ·¯¿Â´Ù
/// </summary>
void loadingScene::LoadData()
{
	DATAMANAGER->Init();
	DATAMANAGER->GetUIBrushToolGridData();
	DATAMANAGER->GetObjectData();
	DATAMANAGER->GetItemData();
}

/// <summary>
/// ·ÎµùÃ¢ÀÇ ¾Ö´Ï¸ÞÀÌ¼ÇÀ» °ü¸®ÇÑ´Ù.
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
	AddFontResource("Font/HS°Ü¿ï´«²ÉÃ¼.ttf");
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
	_loading->LoadNormalImage("InDungeonShop", "Images/NPC/InDungeonShop.bmp", 303, 81, true, RGB(255, 0, 255));

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
	_loading->LoadFrameImage("HungryFountain0", "Images/NPC/HungryFountain0.bmp", 384, 129, 4, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HungryFountain1", "Images/NPC/HungryFountain1.bmp", 96, 129, true, RGB(255, 0, 255));
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
	_loading->LoadNormalImage("Door_PrevDoor", "Images/1Floor/Door_PrevDoor.bmp", 119, 136, true, RGB(255, 0, 255));
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
	_loading->LoadNormalImage("MovePos", "Images/Etc/MovePos.bmp", 48, 48, true, RGB(255, 0, 255));

	// UI //  
	_loading->LoadNormalImage("ItemX", "Images/UI/ItemX.bmp", 57, 57, true, RGB(255, 0, 255));
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
	_loading->LoadNormalImage("¿¹½Ã", "Images/UI/¿¹½Ã.bmp", 960, 540, true, RGB(255, 0, 255));
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
	_loading->LoadNormalImage("satiation", "Images/UI/satiation.bmp", 1, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SatiationProgressBar", "Images/UI/SatiationProgressBar.bmp", 337, 46, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ThankYou.korean", "Images/UI/ThankYou.korean.bmp", 297, 57, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("ShieldBack", "Images/UI/ShieldBack.bmp", 156, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShieldFull", "Images/UI/ShieldFull.bmp", 156, 27, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("CheckImage", "Images/GridBound.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CheckImageRed", "Images/GridBoundRed.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("FrontCloud", "Images/villageFloor/FrontCloud.bmp", 2556, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MidCloud0", "Images/villageFloor/MidCloud0.bmp", 2556, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BackCloud", "Images/villageFloor/BackCloud.bmp", 2844, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("hit", "Images/UI/hit.bmp", 1440, 800, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HpBar1", "Images/HpBar1.bmp", 75, 20, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HpBar2", "Images/HpBar2.bmp", 75,20, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadBar", "Images/UI/ReloadBar.bmp", 6,9, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ReloadBase", "Images/UI/ReloadBase.bmp", 69,3, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("ReloadEffect", "Images/UI/ReloadEffect.bmp", 324, 27, 4, 1, true, RGB(255, 0, 255));

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
	_loading->LoadNormalImage("Temple", "Images/villageFloor/Temple.bmp", 723, 369, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TempleFront", "Images/villageFloor/TempleFront.bmp", 579, 357, true, RGB(255, 0, 255));

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

	_loading->LoadFrameImage("NPC_Commander", "Images/villageFloor/NPC/NPC_Commander.bmp", 414, 150, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_Boutique", "Images/villageFloor/NPC/NPC_Boutique.bmp", 210, 138, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_BlackSmith", "Images/villageFloor/NPC/NPC_BlackSmith.bmp", 432, 156, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_Merchant", "Images/villageFloor/NPC/NPC_Merchant.bmp", 234, 126, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("PistolMan", "Images/villageFloor/NPC/image/PistolMan.bmp", 306, 108, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_Builder", "Images/villageFloor/NPC/NPC_Builder.bmp", 252, 138, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("NPC_Temple", "Images/villageFloor/NPC/NPC_Temple.bmp", 216, 126, 6, 2, true, RGB(255, 0, 255));

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
	_loading->LoadNormalImage("BasicShortSword_New", "Images/item/BasicShortSword_New.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BasicShortSword_inven", "Images/item/BasicShortSword_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BasicShortSword_drop", "Images/item/BasicShortSword_drop.bmp", 57, 32, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BasicShortSwordEffect", "Images/item/BasicShortSwordEffect.bmp", 300, 108, 3, 1, true, RGB(255, 0, 255));
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
	_loading->LoadFrameImage("MagicShield", "Images/item/MagicShield.bmp", 57, 114, 1,2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MagicShield_inv", "Images/item/MagicShield_inv.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DwarvenArmor", "Images/item/DwarvenArmor.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SandBag", "Images/item/SandBag.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Dicegod'sTrick", "Images/item/Dicegod'sTrick.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MiniSlimeMaker", "Images/item/MiniSlimeMaker.bmp", 1044, 144, 12, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MiniSlimeBullet", "Images/item/MiniSlimeBullet.bmp", 792, 168, 12, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MiniSlimeMaker_inven", "Images/item/MiniSlimeMaker_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GreatBow", "Images/item/GreatBow.bmp", 342, 51,6,1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("GreatBow_Inven", "Images/item/GreatBow_Inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("RingOfSpeed", "Images/item/RingOfSpeed.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CharmOfAttack", "Images/item/CharmOfAttack.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CharmOfMadness", "Images/item/CharmOfMadness.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BambooSword", "Images/item/BambooSword.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BambooSword_drop", "Images/item/BambooSword_drop.bmp", 60, 32, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("BambooSword_inven", "Images/item/BambooSword_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BambooSword_Effect", "Images/item/BambooSword_Effect.bmp", 300, 108, 3, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Monocle", "Images/item/Monocle.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Katana", "Images/item/Katana.bmp", 130, 260, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Katana_inven", "Images/item/Katana_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Katana_drop", "Images/item/Katana_drop.bmp", 81, 32, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("KatanaSwing", "Images/item/KatanaSwing.bmp", 2570, 378, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Shamshir", "Images/item/Shamshir.bmp", 130, 260, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Shamshir_drop", "Images/item/Shamshir_drop.bmp", 72, 32, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Shamshir_inven", "Images/item/Shamshir_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Saber", "Images/item/Saber.bmp", 130, 260, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Saber_drop", "Images/item/Saber_drop.bmp", 72, 32, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Saber_inven", "Images/item/Saber_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Rapier", "Images/item/Rapier.bmp", 120, 120, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Rapier_drop", "Images/item/Rapier_drop.bmp", 66, 32, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Rapier_inven", "Images/item/Rapier_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RapierEffect", "Images/item/RapierEffect.bmp", 1920, 480, 4, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShortSpear", "Images/item/ShortSpear.bmp", 140, 140, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShortSpear_inven", "Images/item/ShortSpear_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("ShortSpear_drop", "Images/item/ShortSpear_drop.bmp", 84, 32, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Stab", "Images/item/Stab.bmp", 480, 120, 4, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Gwendolyn", "Images/item/Gwendolyn.bmp", 200, 200, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Gwendolyn_drop", "Images/item/Gwendolyn_drop.bmp", 120, 32, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Gwendolyn_inven", "Images/item/Gwendolyn_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GwendolynEffect", "Images/item/GwendolynEffect.bmp", 720, 240, 3, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MagnifyingGlass", "Images/item/MagnifyingGlass.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MultiBullet", "Images/item/MultiBullet.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Lala'sMagicWand_inven", "Images/item/Lala'sMagicWand_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Lala'sMagicWand", "Images/item/Lala'sMagicWand.bmp", 70, 70, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Autopistol", "Images/item/Autopistol.bmp", 69, 138, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Autopistol_drop", "Images/item/Autopistol_drop.bmp", 48, 24, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Autopistol_inven", "Images/item/Autopistol_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Canon_drop", "Images/item/Canon_drop.bmp", 57, 30, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Canon_inven", "Images/item/Canon_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Canon", "Images/item/Canon.bmp", 63, 126,1,2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Rifle", "Images/item/Rifle.bmp", 111, 222, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Rifle_drop", "Images/item/Rifle_drop.bmp", 57, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Rifle_inven", "Images/item/Rifle_inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Canon_bullet", "Images/item/Canon_bullet.bmp", 66, 72, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("boom", "Images/item/boom.bmp", 2484, 219, 12, 1, true, RGB(255, 0, 255));

	// SKILL //
	_loading->LoadNormalImage("Skill_lala", "Images/item/Skill_lala.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StrawBerry", "Images/item/StrawBerry.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TigarsHammer", "Images/item/TigarsHammer.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("GoldenCandy", "Images/item/GoldenCandy.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MetalBoomerang", "Images/item/MetalBoomerang.bmp", 93, 186, 1,2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("MetalBoomerang_Inven", "Images/item/MetalBoomerang_Inven.bmp", 57, 57, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MetalBoomerangSpin", "Images/item/MetalBoomerangSpin.bmp", 222, 111, 2, 1, true, RGB(255, 0, 255));

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
	_loading->LoadFrameImage("Bomb0", "Images/item/Bomb0.bmp", 225, 48,5,1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BulletFX0103", "Images/item/BulletFX0103.bmp", 924, 120,7,1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("StarBullet", "Images/item/StarBullet.bmp", 168, 39, 4,1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("StarBulletFX", "Images/item/StarBulletFX.bmp", 777, 111, 7,1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("StarBulletParticle", "Images/item/StarBulletParticle.bmp", 42, 39, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SilverBullet", "Images/item/SilverBullet.bmp", 35, 35, true, RGB(255, 0, 255));

	// EFFECT //
	_loading->LoadFrameImage("monsterSpawnEffect", "Images/Etc/monsterSpawnEffect.bmp", 1302, 93, 14, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("DieEffect", "Images/Effect/DieEffect.bmp", 1320, 120, 11, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("HongRyunEffect", "Images/Effect/HongRyunEffect.bmp", 510, 30, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RegenerationSkin", "Images/Effect/RegenerationSkin.bmp", 561, 60, 17, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GuardBreak", "Images/Effect/GuardBreak.bmp", 864, 96, 9, 1, true, RGB(255, 0, 255));

	// PARTICLE //
	_loading->LoadNormalImage("SqaureParticle", "Images/Particle/SqaureParticle.bmp", 15, 15, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_2", "Images/Particle/SqaureParticle_2.bmp", 22, 22, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_3", "Images/Particle/SqaureParticle_3.bmp", 28, 28, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_4", "Images/Particle/SqaureParticle_4.bmp", 5, 5, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SqaureParticle_5", "Images/Particle/SqaureParticle_5.bmp", 5, 5, true, RGB(255, 0, 255));
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

	//ÀÌÅ°³ª°õ ´É·Â ÀÌ¹ÌÁö
	_loading->LoadNormalImage("IkinaBack", "Images/Iknabear/IkinaBack.bmp", 39, 24);
	_loading->LoadNormalImage("IkinaBase", "Images/Iknabear/IkinaBase.bmp", 57, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("IkinaBearFace", "Images/Iknabear/IkinaBearFace.bmp", 57, 48, true, RGB(255, 0, 255));

	// PLAYER EFFECT //
	_loading->LoadFrameImage("AliceZone", "Images/player/AliceZone.bmp", 630, 315, 2, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RunEffect", "Images/player/RunEffect.bmp", 240, 96, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("stun", "Images/player/stun.bmp", 234, 27, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("StateFireEffect", "Images/Effect/StateFireEffect.bmp", 90, 39, 6, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("baseCharEffect", "Images/player/baseCharEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("sheetingEffect", "Images/player/sheetingEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("gunmanEffect", "Images/player/gunmanEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("aliceEffect", "Images/player/aliceEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("redlotusEffect", "Images/player/redlotusEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("lkinabearEffect", "Images/player/lkinabearEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("riderHEffect", "Images/player/riderHEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("criminalEffect", "Images/player/criminalEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("pickEffect", "Images/player/pickEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("fastoEffect", "Images/player/fastoEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("horsemanEffect", "Images/player/horsemanEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("humanlasleyEffect", "Images/player/humanlasleyEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("masterchefEffect", "Images/player/masterchefEffect.bmp", 390, 150, 5, 2, true, RGB(255, 0, 255));


	// MAPIMAGE //
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
	

	// EFFECT //

	_loading->LoadSound("°ÔÀÓ_µ·È¹µæ", "Sounds/Effect/°ÔÀÓ_µ·È¹µæ.wav", false, false);
	_loading->LoadSound("arshasnowstaff_1_TaskStage_Start", "Sounds/Effect/arshasnowstaff_1_TaskStage_Start.wav", false, false);
	_loading->LoadSound("charged ÃæÀüÇü ±â¸ðÀ¸´Â»ç¿îµå", "Sounds/Effect/charged ÃæÀüÇü ±â¸ðÀ¸´Â»ç¿îµå.wav", false, false);
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
	_loading->LoadSound("NPC_°Ç¼³", "Sounds/Effect/NPC_°Ç¼³.wav", false, false);
	_loading->LoadSound("NPC_¸ð·ç", "Sounds/Effect/NPC_¸ð·ç.wav", false, false);
	_loading->LoadSound("NPC_º¸½º»óÀÚ¿­±â", "Sounds/Effect/NPC_º¸½º»óÀÚ¿­±â.wav", false, false);
	_loading->LoadSound("NPC_»óÁ¡À½½ÄÁ¡", "Sounds/Effect/NPC_»óÁ¡À½½ÄÁ¡.wav", false, false);
	_loading->LoadSound("NPC_»óÁ¡ÆÇ¸Å", "Sounds/Effect/NPC_»óÁ¡ÆÇ¸Å.wav", false, false);
	_loading->LoadSound("NPC_½½·Ô¸Ó½Å", "Sounds/Effect/NPC_½½·Ô¸Ó½Å.wav", false, false);
	_loading->LoadSound("NPC_ÀúÁÖ»óÀÚ¿­±â", "Sounds/Effect/NPC_ÀúÁÖ»óÀÚ¿­±â.wav", false, false);
	_loading->LoadSound("NPC_Ãàº¹", "Sounds/Effect/NPC_Ãàº¹.wav", false, false);
	_loading->LoadSound("NPC_ÈÆ·Ã¼Ò_Æ¯¼ºÂï±â", "Sounds/Effect/NPC_ÈÆ·Ã¼Ò_Æ¯¼ºÂï±â.wav", false, false);
	_loading->LoadSound("NPC_ÈÆ·Ã¼Ò_Æ¯¼ºÂï±â2", "Sounds/Effect/NPC_ÈÆ·Ã¼Ò_Æ¯¼ºÂï±â2.wav", false, false);
	_loading->LoadSound("PEEP", "Sounds/Effect/PEEP.wav", false, false);
	_loading->LoadSound("SF_½¯µåEMP", "Sounds/Effect/SF_½¯µåEMP.wav", false, false);
	_loading->LoadSound("Skorpion-Kibblesbob", "Sounds/Effect/Skorpion-Kibblesbob.wav", false, false);
	_loading->LoadSound("°­È­ÇÏ´ÂµíÇÑ ¼Ò¸®", "Sounds/Effect/°­È­ÇÏ´ÂµíÇÑ ¼Ò¸®.wav", false, false);
	_loading->LoadSound("°ÅÄ£ÆÄÀÌ¾îº¼", "Sounds/Effect/°ÅÄ£ÆÄÀÌ¾îº¼.wav", false, false);
	_loading->LoadSound("°ÅÄ¥°Ô ÀÚ¸£´Â ¼Ò¸®", "Sounds/Effect/°ÅÄ¥°Ô ÀÚ¸£´Â ¼Ò¸®.wav", false, false);
	_loading->LoadSound("°È´Â¼Ò¸® (1)", "Sounds/Effect/°È´Â¼Ò¸® (1).wav", false, false);
	_loading->LoadSound("°È´Â¼Ò¸® (2)", "Sounds/Effect/°È´Â¼Ò¸® (2).wav", false, false);
	_loading->LoadSound("°È´Â¼Ò¸® (3)", "Sounds/Effect/°È´Â¼Ò¸® (3).wav", false, false);
	_loading->LoadSound("°È´Â¼Ò¸® (4)", "Sounds/Effect/°È´Â¼Ò¸® (4).wav", false, false);
	_loading->LoadSound("°ÔÀÓ_BLOCK", "Sounds/Effect/°ÔÀÓ_BLOCK.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_LEVELUP", "Sounds/Effect/°ÔÀÓ_LEVELUP.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_´øÀü_¹®¿­¸²´ÝÈû", "Sounds/Effect/°ÔÀÓ_´øÀü_¹®¿­¸²´ÝÈû.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_´øÀü³ª°¡±â", "Sounds/Effect/°ÔÀÓ_´øÀü³ª°¡±â.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_µØÂ¢", "Sounds/Effect/°ÔÀÓ_µØÂ¢.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_¹«±â½º¿Ò", "Sounds/Effect/°ÔÀÓ_¹«±â½º¿Ò.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_º¹±Í", "Sounds/Effect/°ÔÀÓ_º¹±Í.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_½Ã·Ã°£´ÜÇÑÅ¬¸®¾î", "Sounds/Effect/°ÔÀÓ_½Ã·Ã°£´ÜÇÑÅ¬¸®¾î.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_½Ã·Ã±Øº¹", "Sounds/Effect/°ÔÀÓ_½Ã·Ã±Øº¹.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_¾ÆÀÌÅÛÀåÂø (1)", "Sounds/Effect/°ÔÀÓ_¾ÆÀÌÅÛÀåÂø (1).wav", false, false);
	_loading->LoadSound("°ÔÀÓ_¾ÆÀÌÅÛÀåÂø (2)", "Sounds/Effect/°ÔÀÓ_¾ÆÀÌÅÛÀåÂø (2).wav", false, false);
	_loading->LoadSound("°ÔÀÓ_¾ÆÀÌÅÛÀåÂø", "Sounds/Effect/°ÔÀÓ_¾ÆÀÌÅÛÀåÂø.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_Å¬¸®¾î", "Sounds/Effect/°ÔÀÓ_Å¬¸®¾î.wav", false, false);
	_loading->LoadSound("°ÔÀÓ_ÅÛ¹ö¸®±â", "Sounds/Effect/°ÔÀÓ_ÅÛ¹ö¸®±â.wav", false, false);
	_loading->LoadSound("±âÂ÷Áö³ª°¡À¯", "Sounds/Effect/±âÂ÷Áö³ª°¡À¯.wav", false, false);
	_loading->LoadSound("´ë½¬¼Ò¸®", "Sounds/Effect/´ë½¬¼Ò¸®.wav", false, false);
	_loading->LoadSound("´øÀüÀÌµ¿", "Sounds/Effect/´øÀüÀÌµ¿.wav", false, false);
	_loading->LoadSound("µ¶Æ®·¦", "Sounds/Effect/µ¶Æ®·¦.wav", false, false);
	_loading->LoadSound("µ¹ºÎ¼ö±â (1)", "Sounds/Effect/µ¹ºÎ¼ö±â (1).wav", false, false);
	_loading->LoadSound("µ¹ºÎ¼ö±â (2)", "Sounds/Effect/µ¹ºÎ¼ö±â (2).wav", false, false);
	_loading->LoadSound("µ¹ºÎ¼ö±â", "Sounds/Effect/µ¹ºÎ¼ö±â.wav", false, false);
	_loading->LoadSound("µ¹ºÎ¼ö±â_ÃµµÕÄ¡´ÂµíÇÑ", "Sounds/Effect/µ¹ºÎ¼ö±â_ÃµµÕÄ¡´ÂµíÇÑ.wav", false, false);
	_loading->LoadSound("µÎµÎ¿ì", "Sounds/Effect/µÎµÎ¿ì.wav", false, false);
	_loading->LoadSound("¶ó¹Ù¹Ì´Ïº¸½º_ÅÚ·¹Æ÷Æ®", "Sounds/Effect/¶ó¹Ù¹Ì´Ïº¸½º_ÅÚ·¹Æ÷Æ®.wav", false, false);
	_loading->LoadSound("¸®·Îµå_±âº»", "Sounds/Effect/¸®·Îµå_±âº».wav", false, false);
	_loading->LoadSound("¸®·Îµå_ÂªÀº", "Sounds/Effect/¸®·Îµå_ÂªÀº.wav", false, false);
	_loading->LoadSound("¸Ô´ÂÆ÷Å»Äô¿À¸£³»¸²", "Sounds/Effect/¸Ô´ÂÆ÷Å»Äô¿À¸£³»¸².wav", false, false);
	_loading->LoadSound("¸Û¸ÛÀÌ ¿Ð¿Ð", "Sounds/Effect/¸Û¸ÛÀÌ ¿Ð¿Ð.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_±Ã¼ö_¹ß»ç", "Sounds/Effect/¸ó½ºÅÍ_±Ã¼ö_¹ß»ç.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_±Ã¼ö_ÂÞ¿í", "Sounds/Effect/¸ó½ºÅÍ_±Ã¼ö_ÂÞ¿í.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_±â°è_¿òÁ÷ÀÓ", "Sounds/Effect/¸ó½ºÅÍ_±â°è_¿òÁ÷ÀÓ.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_µµ¸¶¹ì¹öÆÛ", "Sounds/Effect/¸ó½ºÅÍ_µµ¸¶¹ì¹öÆÛ.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_·Îº¿´ó´ó_Â¢±â", "Sounds/Effect/¸ó½ºÅÍ_·Îº¿´ó´ó_Â¢±â.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¸®ÀÚµå¸Ç", "Sounds/Effect/¸ó½ºÅÍ_¸®ÀÚµå¸Ç.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹ÚÁã (1)", "Sounds/Effect/¸ó½ºÅÍ_¹ÚÁã (1).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹ÚÁã (2)", "Sounds/Effect/¸ó½ºÅÍ_¹ÚÁã (2).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹ê½Ã", "Sounds/Effect/¸ó½ºÅÍ_¹ê½Ã.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹öÆÛ (1)", "Sounds/Effect/¸ó½ºÅÍ_¹öÆÛ (1).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹öÆÛ (2)", "Sounds/Effect/¸ó½ºÅÍ_¹öÆÛ (2).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹öÆÛ (3)", "Sounds/Effect/¸ó½ºÅÍ_¹öÆÛ (3).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¹öÆÛ (4)", "Sounds/Effect/¸ó½ºÅÍ_¹öÆÛ (4).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_»ç¸Á (1)", "Sounds/Effect/¸ó½ºÅÍ_»ç¸Á (1).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_»ç¸Á (2)", "Sounds/Effect/¸ó½ºÅÍ_»ç¸Á (2).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_»ç¸Á", "Sounds/Effect/¸ó½ºÅÍ_»ç¸Á.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_½¦µµ¿ìÀ¯·É", "Sounds/Effect/¸ó½ºÅÍ_½¦µµ¿ìÀ¯·É.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_½¦µµ¿ìÀ¯·É2", "Sounds/Effect/¸ó½ºÅÍ_½¦µµ¿ìÀ¯·É2.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¿ïºÎÂ¢À½ (1)", "Sounds/Effect/¸ó½ºÅÍ_¿ïºÎÂ¢À½ (1).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¿ïºÎÂ¢À½ (2)", "Sounds/Effect/¸ó½ºÅÍ_¿ïºÎÂ¢À½ (2).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_¿ïºÎÂ¢À½ (3)", "Sounds/Effect/¸ó½ºÅÍ_¿ïºÎÂ¢À½ (3).wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_À¯µµÅº¹ß»ç±â_¹ß»ç", "Sounds/Effect/¸ó½ºÅÍ_À¯µµÅº¹ß»ç±â_¹ß»ç.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_Àü±â¸¦¸·³¯¸®´Âµå·¡°ï", "Sounds/Effect/¸ó½ºÅÍ_Àü±â¸¦¸·³¯¸®´Âµå·¡°ï.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_ÄÉ¸£º£·Î½º_ºÒ", "Sounds/Effect/¸ó½ºÅÍ_ÄÉ¸£º£·Î½º_ºÒ.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_Å«°Å¹Ì±â°è_Á¡ÇÁ", "Sounds/Effect/¸ó½ºÅÍ_Å«°Å¹Ì±â°è_Á¡ÇÁ.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_Å«´ó´ó_Â¢±â", "Sounds/Effect/¸ó½ºÅÍ_Å«´ó´ó_Â¢±â.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_Å«¹ÚÁã", "Sounds/Effect/¸ó½ºÅÍ_Å«¹ÚÁã.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_Æ®·ÑÁ×À½", "Sounds/Effect/¸ó½ºÅÍ_Æ®·ÑÁ×À½.wav", false, false);
	_loading->LoadSound("¸ó½ºÅÍ_ÆøÅº¹ÚÁã", "Sounds/Effect/¸ó½ºÅÍ_ÆøÅº¹ÚÁã.wav", false, false);
	_loading->LoadSound("¹«±â_AK", "Sounds/Effect/¹«±â_AK.wav", false, false);
	_loading->LoadSound("¹«±â_M1Garand", "Sounds/Effect/¹«±â_M1Garand.wav", false, false);
	_loading->LoadSound("¹«±â_M1Garand¸®·Îµå", "Sounds/Effect/¹«±â_M1Garand¸®·Îµå.wav", false, false);
	_loading->LoadSound("¹«±â_M4A1", "Sounds/Effect/¹«±â_M4A1.wav", false, false);
	_loading->LoadSound("¹«±â_RPG", "Sounds/Effect/¹«±â_RPG.wav", false, false);
	_loading->LoadSound("¹«±â_UZI ¹ß»ç", "Sounds/Effect/¹«±â_UZI ¹ß»ç.wav", false, false);
	_loading->LoadSound("¹«±â_°³Æ²¸µ°Ç¹ß»ç", "Sounds/Effect/¹«±â_°³Æ²¸µ°Ç¹ß»ç.wav", false, false);
	_loading->LoadSound("¹«±â_°³Æ²¸µ°ÇÁ¡È­", "Sounds/Effect/¹«±â_°³Æ²¸µ°ÇÁ¡È­.wav", false, false);
	_loading->LoadSound("¹«±â_±ÇÃÑ", "Sounds/Effect/¹«±â_±ÇÃÑ.wav", false, false);
	_loading->LoadSound("¹«±â_±ÇÃÑ2", "Sounds/Effect/¹«±â_±ÇÃÑ2.wav", false, false);
	_loading->LoadSound("¹«±â_±â°øÅæÆÄ_°ø°Ý", "Sounds/Effect/¹«±â_±â°øÅæÆÄ_°ø°Ý.wav", false, false);
	_loading->LoadSound("¹«±â_±â°øÅæÆÄ_½ºÅ³", "Sounds/Effect/¹«±â_±â°øÅæÆÄ_½ºÅ³.wav", false, false);
	_loading->LoadSound("¹«±â_±âÅ¸ (1)", "Sounds/Effect/¹«±â_±âÅ¸ (1).wav", false, false);
	_loading->LoadSound("¹«±â_±âÅ¸ (2)", "Sounds/Effect/¹«±â_±âÅ¸ (2).wav", false, false);
	_loading->LoadSound("¹«±â_±âÅ¸ (3)", "Sounds/Effect/¹«±â_±âÅ¸ (3).wav", false, false);
	_loading->LoadSound("¹«±â_±âÅ¸ (4)", "Sounds/Effect/¹«±â_±âÅ¸ (4).wav", false, false);
	_loading->LoadSound("¹«±â_±âÅ¸ (5)", "Sounds/Effect/¹«±â_±âÅ¸ (5).wav", false, false);
	_loading->LoadSound("¹«±â_±âÅ¸ (6)", "Sounds/Effect/¹«±â_±âÅ¸ (6).wav", false, false);
	_loading->LoadSound("¹«±â_³ªÆÈÃÑ", "Sounds/Effect/¹«±â_³ªÆÈÃÑ.wav", false, false);
	_loading->LoadSound("¹«±â_´úµÐÅ¹ÇÑ¹ß»çÀ½", "Sounds/Effect/¹«±â_´úµÐÅ¹ÇÑ¹ß»çÀ½.wav", false, false);
	_loading->LoadSound("¹«±â_µ¥¸ó¼Òµå", "Sounds/Effect/¹«±â_µ¥¸ó¼Òµå.wav", false, false);
	_loading->LoadSound("¹«±â_µÎ¼Õ°Ë", "Sounds/Effect/¹«±â_µÎ¼Õ°Ë.wav", false, false);
	_loading->LoadSound("¹«±â_µÐÅ¹ÇÑ¹ß»çÀ½", "Sounds/Effect/¹«±â_µÐÅ¹ÇÑ¹ß»çÀ½.wav", false, false);
	_loading->LoadSound("¹«±â_¶ó¶óÀÇ ¿ä¼úºÀ", "Sounds/Effect/¹«±â_¶ó¶óÀÇ ¿ä¼úºÀ.wav", false, false);
	_loading->LoadSound("¹«±â_¶óÀÌÇÃ", "Sounds/Effect/¹«±â_¶óÀÌÇÃ.wav", false, false);
	_loading->LoadSound("¹«±â_·¯½Ã¾È·ê·¿_½ÇÆÐ", "Sounds/Effect/¹«±â_·¯½Ã¾È·ê·¿_½ÇÆÐ.wav", false, false);
	_loading->LoadSound("¹«±â_·¹ÀÌÀú¹ß»ç", "Sounds/Effect/¹«±â_·¹ÀÌÀú¹ß»ç.wav", false, false);
	_loading->LoadSound("¹«±â_·¹ÀÌÇÇ¾î", "Sounds/Effect/¹«±â_·¹ÀÌÇÇ¾î.wav", false, false);
	_loading->LoadSound("¹«±â_¸ð½º¹ö±×¼¦°Ç", "Sounds/Effect/¹«±â_¸ð½º¹ö±×¼¦°Ç.wav", false, false);
	_loading->LoadSound("¹«±â_¸óµå¸®¾Æ (1)", "Sounds/Effect/¹«±â_¸óµå¸®¾Æ (1).wav", false, false);
	_loading->LoadSound("¹«±â_¸óµå¸®¾Æ (2)", "Sounds/Effect/¹«±â_¸óµå¸®¾Æ (2).wav", false, false);
	_loading->LoadSound("¹«±â_¹«°Å¿îÈÖµÎ¸§", "Sounds/Effect/¹«±â_¹«°Å¿îÈÖµÎ¸§.wav", false, false);
	_loading->LoadSound("¹«±â_¹°ÃÑ »Ñ¸²", "Sounds/Effect/¹«±â_¹°ÃÑ »Ñ¸².wav", false, false);
	_loading->LoadSound("¹«±â_¹öÅÍÇÃ¶óÀÌ³ªÀÌÇÁ", "Sounds/Effect/¹«±â_¹öÅÍÇÃ¶óÀÌ³ªÀÌÇÁ.wav", false, false);
	_loading->LoadSound("¹«±â_ºÎ¸Þ¶û°è¿­", "Sounds/Effect/¹«±â_ºÎ¸Þ¶û°è¿­.wav", false, false);
	_loading->LoadSound("¹«±â_ºûÀÇÀÎµµÀÚ", "Sounds/Effect/¹«±â_ºûÀÇÀÎµµÀÚ.wav", false, false);
	_loading->LoadSound("¹«±â_ºûÀÇÀÎµµÀÚ_ÃæÀü", "Sounds/Effect/¹«±â_ºûÀÇÀÎµµÀÚ_ÃæÀü.wav", false, false);
	_loading->LoadSound("¹«±â_»êÅºÃÑ", "Sounds/Effect/¹«±â_»êÅºÃÑ.wav", false, false);
	_loading->LoadSound("¹«±â_»õÃÑ", "Sounds/Effect/¹«±â_»õÃÑ.wav", false, false);
	_loading->LoadSound("¹«±â_»ø·¯¸Ç´õÀÇ´«", "Sounds/Effect/¹«±â_»ø·¯¸Ç´õÀÇ´«.wav", false, false);
	_loading->LoadSound("¹«±â_¼±·¹ÀÌÀú¶óÀÌÇÃ (1)", "Sounds/Effect/¹«±â_¼±·¹ÀÌÀú¶óÀÌÇÃ (1).wav", false, false);
	_loading->LoadSound("¹«±â_¼±·¹ÀÌÀú¶óÀÌÇÃ (2)", "Sounds/Effect/¹«±â_¼±·¹ÀÌÀú¶óÀÌÇÃ (2).wav", false, false);
	_loading->LoadSound("¹«±â_¼è³ú", "Sounds/Effect/¹«±â_¼è³ú.wav", false, false);
	_loading->LoadSound("¹«±â_½º³ªÀÌÆÛ¹ß»ç", "Sounds/Effect/¹«±â_½º³ªÀÌÆÛ¹ß»ç.wav", false, false);
	_loading->LoadSound("¹«±â_½º³ªÀÌÇÎ", "Sounds/Effect/¹«±â_½º³ªÀÌÇÎ.wav", false, false);
	_loading->LoadSound("¹«±â_½½¶óÀÓ¸ÞÀÌÄ¿", "Sounds/Effect/¹«±â_½½¶óÀÓ¸ÞÀÌÄ¿.wav", false, false);
	_loading->LoadSound("¹«±â_¿ìÁÖ°Ë¿ìÁÖÀÇ½ÉÀå", "Sounds/Effect/¹«±â_¿ìÁÖ°Ë¿ìÁÖÀÇ½ÉÀå.wav", false, false);
	_loading->LoadSound("¹«±â_¿ìÁÖ°ËÈ¿°úÀ½", "Sounds/Effect/¹«±â_¿ìÁÖ°ËÈ¿°úÀ½.wav", false, false);
	_loading->LoadSound("¹«±â_¿îµð³×Ã¢È¿°ú", "Sounds/Effect/¹«±â_¿îµð³×Ã¢È¿°ú.wav", false, false);
	_loading->LoadSound("¹«±â_ÂûÁø¹«±â", "Sounds/Effect/¹«±â_ÂûÁø¹«±â.wav", false, false);
	_loading->LoadSound("¹«±â_Ã¤Âï", "Sounds/Effect/¹«±â_Ã¤Âï.wav", false, false);
	_loading->LoadSound("¹«±â_Ä«Å¸³ª (1)", "Sounds/Effect/¹«±â_Ä«Å¸³ª (1).wav", false, false);
	_loading->LoadSound("¹«±â_Ä«Å¸³ª (2)", "Sounds/Effect/¹«±â_Ä«Å¸³ª (2).wav", false, false);
	_loading->LoadSound("¹«±â_Ä«Å¸³ª (3)", "Sounds/Effect/¹«±â_Ä«Å¸³ª (3).wav", false, false);
	_loading->LoadSound("¹«±â_Ä®´øÁö±â", "Sounds/Effect/¹«±â_Ä®´øÁö±â.wav", false, false);
	_loading->LoadSound("¹«±â_Ä³³í¹ß»ç (1)", "Sounds/Effect/¹«±â_Ä³³í¹ß»ç (1).wav", false, false);
	_loading->LoadSound("¹«±â_Ä³³í¹ß»ç (2)", "Sounds/Effect/¹«±â_Ä³³í¹ß»ç (2).wav", false, false);
	_loading->LoadSound("¹«±â_Ä³³í¹ß»ç (3)", "Sounds/Effect/¹«±â_Ä³³í¹ß»ç (3).wav", false, false);
	_loading->LoadSound("¹«±â_Å©·Î½ºº¸¿ì", "Sounds/Effect/¹«±â_Å©·Î½ºº¸¿ì.wav", false, false);
	_loading->LoadSound("¹«±â_ÅæÆÄ¼îÅ©", "Sounds/Effect/¹«±â_ÅæÆÄ¼îÅ©.wav", false, false);
	_loading->LoadSound("¹«±â_ÆßÇÁ¼¦°Ç (1)", "Sounds/Effect/¹«±â_ÆßÇÁ¼¦°Ç (1).wav", false, false);
	_loading->LoadSound("¹«±â_ÆßÇÁ¼¦°Ç (2)", "Sounds/Effect/¹«±â_ÆßÇÁ¼¦°Ç (2).wav", false, false);
	_loading->LoadSound("¹«±â_ÆøÅº¹ß»ç±â", "Sounds/Effect/¹«±â_ÆøÅº¹ß»ç±â.wav", false, false);
	_loading->LoadSound("¹«±â_ÇÁ·Î½ºÆ®³ë¹Ù", "Sounds/Effect/¹«±â_ÇÁ·Î½ºÆ®³ë¹Ù.wav", false, false);
	_loading->LoadSound("¹«±â_ÇÇ½ºÅç (1)", "Sounds/Effect/¹«±â_ÇÇ½ºÅç (1).wav", false, false);
	_loading->LoadSound("¹«±â_ÇÇ½ºÅç (2)", "Sounds/Effect/¹«±â_ÇÇ½ºÅç (2).wav", false, false);
	_loading->LoadSound("¹«±â_ÇØ°ñ¿Õ°Ë", "Sounds/Effect/¹«±â_ÇØ°ñ¿Õ°Ë.wav", false, false);
	_loading->LoadSound("¹«±â_ÇìÄ«Å×ÃÑ", "Sounds/Effect/¹«±â_ÇìÄ«Å×ÃÑ.wav", false, false);
	_loading->LoadSound("¹«±â_È£¶ûÀÌ±Ç¹ý", "Sounds/Effect/¹«±â_È£¶ûÀÌ±Ç¹ý.wav", false, false);
	_loading->LoadSound("¹«±â_È­¿°¹æ»ç±â", "Sounds/Effect/¹«±â_È­¿°¹æ»ç±â.wav", false, false);
	_loading->LoadSound("¹«±â_È°¹ß»ç", "Sounds/Effect/¹«±â_È°¹ß»ç.wav", false, false);
	_loading->LoadSound("¹«±â°¡´Â¼Ò¸®", "Sounds/Effect/¹«±â°¡´Â¼Ò¸®.wav", false, false);
	_loading->LoadSound("¹«±âÈÖµÎ¸§¹Ù¶÷¼Ò¸®Áß", "Sounds/Effect/¹«±âÈÖµÎ¸§¹Ù¶÷¼Ò¸®Áß.wav", false, false);
	_loading->LoadSound("¹«¾ð°¡¿¡Âñ¸²", "Sounds/Effect/¹«¾ð°¡¿¡Âñ¸².wav", false, false);
	_loading->LoadSound("¹° ¸ÂÀ½", "Sounds/Effect/¹° ¸ÂÀ½.wav", false, false);
	_loading->LoadSound("¹º°¡ ÀÛµ¿ÇÏ´Â ¼Ò¸®", "Sounds/Effect/¹º°¡ ÀÛµ¿ÇÏ´Â ¼Ò¸®.wav", false, false);
	_loading->LoadSound("¹º°¡Æø¹ß", "Sounds/Effect/¹º°¡Æø¹ß.wav", false, false);
	_loading->LoadSound("¹Ì¿¹¿õ", "Sounds/Effect/¹Ì¿¹¿õ.wav", false, false);
	_loading->LoadSound("¹Ù¶÷À» °¡¸£´Â ÈÖµÎ¸£±â", "Sounds/Effect/¹Ù¶÷À» °¡¸£´Â ÈÖµÎ¸£±â.wav", false, false);
	_loading->LoadSound("¹ú³ª´Â¼Ò¸®", "Sounds/Effect/¹ú³ª´Â¼Ò¸®.wav", false, false);
	_loading->LoadSound("º¸½º_´ÏÇÃÇìÀÓ_¹ß»ç", "Sounds/Effect/º¸½º_´ÏÇÃÇìÀÓ_¹ß»ç.wav", false, false);
	_loading->LoadSound("º¸½º_´ÏÇÃÇìÀÓ_½ÃÀÛÈ¿°úÀ½", "Sounds/Effect/º¸½º_´ÏÇÃÇìÀÓ_½ÃÀÛÈ¿°úÀ½.wav", false, false);
	_loading->LoadSound("º¸½º_¶ó½½¸®_Â÷¿ø°¡¸£±â", "Sounds/Effect/º¸½º_¶ó½½¸®_Â÷¿ø°¡¸£±â.wav", false, false);
	_loading->LoadSound("º¸½º_¶ó½½¸®_ÅÙÅ¸Å¬", "Sounds/Effect/º¸½º_¶ó½½¸®_ÅÙÅ¸Å¬.wav", false, false);
	_loading->LoadSound("º¸½º_¶ó½½¸®_Æø¹ß", "Sounds/Effect/º¸½º_¶ó½½¸®_Æø¹ß.wav", false, false);
	_loading->LoadSound("º¸½º_º§¸®¾Ë_¿ôÀ½", "Sounds/Effect/º¸½º_º§¸®¾Ë_¿ôÀ½.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£»þ_¹ßÆÇ¼ÒÈ¯", "Sounds/Effect/º¸½º_¾Æ¸£»þ_¹ßÆÇ¼ÒÈ¯.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£»þ_ºÒ¸´¹ß»ç", "Sounds/Effect/º¸½º_¾Æ¸£»þ_ºÒ¸´¹ß»ç.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£»þ_Àû¼ÒÈ¯", "Sounds/Effect/º¸½º_¾Æ¸£»þ_Àû¼ÒÈ¯.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_·¹ÀÌÀú", "Sounds/Effect/º¸½º_¾Æ¸£Å×_·¹ÀÌÀú.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_¸¶±×¸¶¿Ã¶ó¿À±â", "Sounds/Effect/º¸½º_¾Æ¸£Å×_¸¶±×¸¶¿Ã¶ó¿À±â.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_ºÒ²É¹ß»ç", "Sounds/Effect/º¸½º_¾Æ¸£Å×_ºÒ²É¹ß»ç.wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_»ç¸Á (1)", "Sounds/Effect/º¸½º_¾Æ¸£Å×_»ç¸Á (1).wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_»ç¸Á (2)", "Sounds/Effect/º¸½º_¾Æ¸£Å×_»ç¸Á (2).wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_»ç¸Á (3)", "Sounds/Effect/º¸½º_¾Æ¸£Å×_»ç¸Á (3).wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_»ç¸Á (4)", "Sounds/Effect/º¸½º_¾Æ¸£Å×_»ç¸Á (4).wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_»ç¸Á (5)", "Sounds/Effect/º¸½º_¾Æ¸£Å×_»ç¸Á (5).wav", false, false);
	_loading->LoadSound("º¸½º_¾Æ¸£Å×_ÁÖ¸ÔÄ¡±â", "Sounds/Effect/º¸½º_¾Æ¸£Å×_ÁÖ¸ÔÄ¡±â.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Â÷_½ºÆÄÀÌÅ©°ø°Ý", "Sounds/Effect/º¸½º_¿¡¸®Â÷_½ºÆÄÀÌÅ©°ø°Ý.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Â÷_¿ïºÎÂ¢À»¶§µÞ¼Ò¸®", "Sounds/Effect/º¸½º_¿¡¸®Â÷_¿ïºÎÂ¢À»¶§µÞ¼Ò¸®.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_´ÙÀ½ÆÐÅÏ", "Sounds/Effect/º¸½º_¿¡¸®Ä«_´ÙÀ½ÆÐÅÏ.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_´ë±âÁßº®Âö±â (1)", "Sounds/Effect/º¸½º_¿¡¸®Ä«_´ë±âÁßº®Âö±â (1).wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_´ë±âÁßº®Âö±â (2)", "Sounds/Effect/º¸½º_¿¡¸®Ä«_´ë±âÁßº®Âö±â (2).wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_µå¸±", "Sounds/Effect/º¸½º_¿¡¸®Ä«_µå¸±.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_½ºÆÄÀÌÅ©°ø°Ý", "Sounds/Effect/º¸½º_¿¡¸®Ä«_½ºÆÄÀÌÅ©°ø°Ý.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_¾îµÒ¼ÒÈ¯", "Sounds/Effect/º¸½º_¿¡¸®Ä«_¾îµÒ¼ÒÈ¯.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_¿ïºÎÂ¢À½ (1)", "Sounds/Effect/º¸½º_¿¡¸®Ä«_¿ïºÎÂ¢À½ (1).wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_¿ïºÎÂ¢À½ (2)", "Sounds/Effect/º¸½º_¿¡¸®Ä«_¿ïºÎÂ¢À½ (2).wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_¿ïºÎÂ¢À½", "Sounds/Effect/º¸½º_¿¡¸®Ä«_¿ïºÎÂ¢À½.wav", false, false);
	_loading->LoadSound("º¸½º_¿¡¸®Ä«_ÅÚ·¹Æ÷Æ®", "Sounds/Effect/º¸½º_¿¡¸®Ä«_ÅÚ·¹Æ÷Æ®.wav", false, false);
	_loading->LoadSound("º¸½º_¿£ºñ·Ï_²Ù¿Í¾Ó", "Sounds/Effect/º¸½º_¿£ºñ·Ï_²Ù¿Í¾Ó.wav", false, false);
	_loading->LoadSound("º¸½º_¿£ºñ·Ï_½º³×ÀÌÅ©¼ÒÈ¯", "Sounds/Effect/º¸½º_¿£ºñ·Ï_½º³×ÀÌÅ©¼ÒÈ¯.wav", false, false);
	_loading->LoadSound("º¸½º_¿£ºñ·Ï_½ºÆÃ°Å", "Sounds/Effect/º¸½º_¿£ºñ·Ï_½ºÆÃ°Å.wav", false, false);
	_loading->LoadSound("º¸½º_Ä«¹Ì³Ú¶ó_2ÆäÀÌÁî", "Sounds/Effect/º¸½º_Ä«¹Ì³Ú¶ó_2ÆäÀÌÁî.wav", false, false);
	_loading->LoadSound("º¸½º_Ä«¹Ì³Ú¶ó_¹«¾ð°¡", "Sounds/Effect/º¸½º_Ä«¹Ì³Ú¶ó_¹«¾ð°¡.wav", false, false);
	_loading->LoadSound("º¸½º_Ä«¹Ì³Ú¶ó_¹ßÂ÷±â", "Sounds/Effect/º¸½º_Ä«¹Ì³Ú¶ó_¹ßÂ÷±â.wav", false, false);
	_loading->LoadSound("º¸½º_Ä«¹Ì³Ú¶ó_»ç¸Á", "Sounds/Effect/º¸½º_Ä«¹Ì³Ú¶ó_»ç¸Á.wav", false, false);
	_loading->LoadSound("º¸½º_Ä«¹Ì³Ú¶ó_½º¸Å½¬", "Sounds/Effect/º¸½º_Ä«¹Ì³Ú¶ó_½º¸Å½¬.wav", false, false);
	_loading->LoadSound("º¸½º_Ä«¹Ì³Ú¶ó_Çï°ÔÀÌÆ®¿ÀÇÂ", "Sounds/Effect/º¸½º_Ä«¹Ì³Ú¶ó_Çï°ÔÀÌÆ®¿ÀÇÂ.wav", false, false);
	_loading->LoadSound("º¸½º¹æÀÔÀå¹®", "Sounds/Effect/º¸½º¹æÀÔÀå¹®.wav", false, false);
	_loading->LoadSound("º¸È£¸·±úÁü", "Sounds/Effect/º¸È£¸·±úÁü.wav", false, false);
	_loading->LoadSound("ºÒ±æÇÑ¹Ù¶÷ÀÌºÒ¾î¿Â´Ù", "Sounds/Effect/ºÒ±æÇÑ¹Ù¶÷ÀÌºÒ¾î¿Â´Ù.wav", false, false);
	_loading->LoadSound("ºÒµ¢ÀÌ", "Sounds/Effect/ºÒµ¢ÀÌ.wav", false, false);
	_loading->LoadSound("ºñÇÁÀ½", "Sounds/Effect/ºñÇÁÀ½.wav", false, false);
	_loading->LoadSound("»þ¶ó¶ö¶ó¶ö¶ö¶ó", "Sounds/Effect/»þ¶ó¶ö¶ó¶ö¶ö¶ó.wav", false, false);
	_loading->LoadSound("»þ¹æ»þ¹æ", "Sounds/Effect/»þ¹æ»þ¹æ.wav", false, false);
	_loading->LoadSound("¼¯´ÂµíÇÑ¼Ò¸® (1)", "Sounds/Effect/¼¯´ÂµíÇÑ¼Ò¸® (1).wav", false, false);       //¹ë¸®¾Ë ÃÑ¾ËÀÓ
	_loading->LoadSound("¼¯´ÂµíÇÑ¼Ò¸® (2)", "Sounds/Effect/¼¯´ÂµíÇÑ¼Ò¸® (2).wav", false, false);
	_loading->LoadSound("¼¼Æ®È¿°ú", "Sounds/Effect/¼¼Æ®È¿°ú.wav", false, false);
	_loading->LoadSound("½ºÀ§Ä¡ ¶£", "Sounds/Effect/½ºÀ§Ä¡ ¶£.wav", false, false);
	_loading->LoadSound("½ºÀ§Ä¡¼Ò¸®", "Sounds/Effect/½ºÀ§Ä¡¼Ò¸®.wav", false, false);
	_loading->LoadSound("½ºÅä¸®_°á°è´À³¦ (1)", "Sounds/Effect/½ºÅä¸®_°á°è´À³¦ (1).wav", false, false);
	_loading->LoadSound("½ºÅä¸®_°á°è´À³¦ (2)", "Sounds/Effect/½ºÅä¸®_°á°è´À³¦ (2).wav", false, false);
	_loading->LoadSound("½ºÅä¸®_°á°è´À³¦ (3)", "Sounds/Effect/½ºÅä¸®_°á°è´À³¦ (3).wav", false, false);

	_loading->LoadSound("½ºÆù¸ó½ºÅÍ", "Sounds/Effect/½ºÆù¸ó½ºÅÍ.wav", false, false);

	_loading->LoadSound("½½¶óÀÓº¼", "Sounds/Effect/½½¶óÀÓº¼.wav", false, false);
	_loading->LoadSound("½Ç¹ö¶óÀÓ", "Sounds/Effect/½Ç¹ö¶óÀÓ.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÀÛÄÝ¶óº¸ (1)", "Sounds/Effect/¾ÆÀÌÀÛÄÝ¶óº¸ (1).wav", false, false);
	_loading->LoadSound("¾ÆÀÌÀÛÄÝ¶óº¸ (2)", "Sounds/Effect/¾ÆÀÌÀÛÄÝ¶óº¸ (2).wav", false, false);
	_loading->LoadSound("¾ÆÀÌÀÛÄÝ¶óº¸ (3)", "Sounds/Effect/¾ÆÀÌÀÛÄÝ¶óº¸ (3).wav", false, false);
	_loading->LoadSound("¾ÆÀÌÀÛÄÝ¶óº¸ (4)", "Sounds/Effect/¾ÆÀÌÀÛÄÝ¶óº¸ (4).wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_HARNESSMAGIC", "Sounds/Effect/¾ÆÀÌÅÛ_HARNESSMAGIC.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_PHAX", "Sounds/Effect/¾ÆÀÌÅÛ_PHAX.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_RADDRAGONKILLER", "Sounds/Effect/¾ÆÀÌÅÛ_RADDRAGONKILLER.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_µµ±úºñ°Ë½ºÅ³", "Sounds/Effect/¾ÆÀÌÅÛ_µµ±úºñ°Ë½ºÅ³.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_·Õ¼Òµå½ºÅ³", "Sounds/Effect/¾ÆÀÌÅÛ_·Õ¼Òµå½ºÅ³.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_¸ÞÀÌ½º½ºÅÏ", "Sounds/Effect/¾ÆÀÌÅÛ_¸ÞÀÌ½º½ºÅÏ.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_¾ÆÀÌÅÛ_¾Ç¸¶ÀÇ¼Õ", "Sounds/Effect/¾ÆÀÌÅÛ_¾ÆÀÌÅÛ_¾Ç¸¶ÀÇ¼Õ.wav", false, false);

	_loading->LoadSound("¾ÆÀÌÅÛ_Àü±âÃæ°Ý±â", "Sounds/Effect/¾ÆÀÌÅÛ_Àü±âÃæ°Ý±â.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_Á¦Æ®ÆÑ", "Sounds/Effect/¾ÆÀÌÅÛ_Á¦Æ®ÆÑ.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_Å¸¿ö½Çµå½ºÅ³", "Sounds/Effect/¾ÆÀÌÅÛ_Å¸¿ö½Çµå½ºÅ³.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛ_ÆøÅº¹Ù±¸´Ï", "Sounds/Effect/¾ÆÀÌÅÛ_ÆøÅº¹Ù±¸´Ï.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛÀåÂø", "Sounds/Effect/¾ÆÀÌÅÛÀåÂø.wav", false, false);
	_loading->LoadSound("¾ÆÀÌÅÛÈ¹µæ", "Sounds/Effect/¾ÆÀÌÅÛÈ¹µæ.wav", false, false);
	_loading->LoadSound("¾ÏÈæ¸¶¹ý°°Àº¹ß»çÀ½", "Sounds/Effect/¾ÏÈæ¸¶¹ý°°Àº¹ß»çÀ½.wav", false, false);
	_loading->LoadSound("¿¡¸®Â÷°¡´Âº®ºÎ¼ö±â", "Sounds/Effect/¿¡¸®Â÷°¡´Âº®ºÎ¼ö±â.wav", false, false);
	_loading->LoadSound("¿¡¸®Ä«´ë±âµ¹ºÎ¼ö±â (1)", "Sounds/Effect/¿¡¸®Ä«´ë±âµ¹ºÎ¼ö±â (1).wav", false, false);
	_loading->LoadSound("¿¡¸®Ä«´ë±âµ¹ºÎ¼ö±â (2)", "Sounds/Effect/¿¡¸®Ä«´ë±âµ¹ºÎ¼ö±â (2).wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_HPÈ¸º¹", "Sounds/Effect/¿ÀºêÁ§Æ®_HPÈ¸º¹.wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_º¸½º_ÆÄ±«_¾ÆÀÌÅÛ·çÆÃ", "Sounds/Effect/¿ÀºêÁ§Æ®_º¸½º_ÆÄ±«_¾ÆÀÌÅÛ·çÆÃ.wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_»óÀÚ¿ÀÇÂ", "Sounds/Effect/¿ÀºêÁ§Æ®_»óÀÚ¿ÀÇÂ.wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_»óÀÚ¿ÀÇÂ_º°°Å¾Æ´Ô", "Sounds/Effect/¿ÀºêÁ§Æ®_»óÀÚ¿ÀÇÂ_º°°Å¾Æ´Ô.wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_Àü¼³»óÀÚ¿ÀÇÂ", "Sounds/Effect/¿ÀºêÁ§Æ®_Àü¼³»óÀÚ¿ÀÇÂ.wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_ÅëºÎ¼û (1)", "Sounds/Effect/¿ÀºêÁ§Æ®_ÅëºÎ¼û (1).wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_ÅëºÎ¼û (2)", "Sounds/Effect/¿ÀºêÁ§Æ®_ÅëºÎ¼û (2).wav", false, false);
	_loading->LoadSound("¿ÀºêÁ§Æ®_ÅëºÎ¼û (3)", "Sounds/Effect/¿ÀºêÁ§Æ®_ÅëºÎ¼û (3).wav", false, false);
	_loading->LoadSound("¿ä¼úºÀPPTÈ¿°úÀ½", "Sounds/Effect/¿ä¼úºÀPPTÈ¿°úÀ½.wav", false, false);
	_loading->LoadSound("¿ì¿õ", "Sounds/Effect/¿ì¿õ.wav", false, false);
	_loading->LoadSound("ÀÌ·±Àú·±_¹ø°³Ä§", "Sounds/Effect/ÀÌ·±Àú·±_¹ø°³Ä§.wav", false, false);
	_loading->LoadSound("ÀÎº¥Åä¸®¿­±â", "Sounds/Effect/ÀÎº¥Åä¸®¿­±â.wav", false, false);
	_loading->LoadSound("Àå¾Ö¹°_°¡½Ã¿Â", "Sounds/Effect/Àå¾Ö¹°_°¡½Ã¿Â.wav", false, false);
	_loading->LoadSound("Àü±âÂÉ²¿¹Ì", "Sounds/Effect/Àü±âÂÉ²¿¹Ì.wav", false, false);
	_loading->LoadSound("Á¡ÇÁ", "Sounds/Effect/Á¡ÇÁ.wav", false, false);
	_loading->LoadSound("ÁßÈÄÇÑ·¹ÀÌÀú¹ß»ç", "Sounds/Effect/ÁßÈÄÇÑ·¹ÀÌÀú¹ß»ç.wav", false, false);
	_loading->LoadSound("ÁöÁø", "Sounds/Effect/ÁöÁø.wav", false, false);
	_loading->LoadSound("Â¡±Ûº§ (1)", "Sounds/Effect/Â¡±Ûº§ (1).wav", false, false);
	_loading->LoadSound("Â¡±Ûº§ (2)", "Sounds/Effect/Â¡±Ûº§ (2).wav", false, false);
	_loading->LoadSound("Â¡±Ûº§ (3)", "Sounds/Effect/Â¡±Ûº§ (3).wav", false, false);
	_loading->LoadSound("Âª°Ô½î´Â¼Ò¸®", "Sounds/Effect/Âª°Ô½î´Â¼Ò¸®.wav", false, false);
	_loading->LoadSound("ÃµµÕ»õ", "Sounds/Effect/ÃµµÕ»õ.wav", false, false);
	_loading->LoadSound("Ä¡´ÂµíÇÑSF¼Ò¸®", "Sounds/Effect/Ä¡´ÂµíÇÑSF¼Ò¸®.wav", false, false);
	_loading->LoadSound("Å¹Ä¡´Â¼Ò¸®", "Sounds/Effect/Å¹Ä¡´Â¼Ò¸®.wav", false, false);
	_loading->LoadSound("Æ÷Å»¿­¸²", "Sounds/Effect/Æ÷Å»¿­¸².wav", false, false);
	_loading->LoadSound("Æø¹ß (1)", "Sounds/Effect/Æø¹ß (1).wav", false, false);
	_loading->LoadSound("Æø¹ß (2)", "Sounds/Effect/Æø¹ß (2).wav", false, false);
	_loading->LoadSound("Æø¹ß_ÂªÀ½", "Sounds/Effect/Æø¹ß_ÂªÀ½.wav", false, false);
	_loading->LoadSound("Æø¹ß_Å­", "Sounds/Effect/Æø¹ß_Å­.wav", false, false);
	_loading->LoadSound("ÆøÅº¼Ò¸®", "Sounds/Effect/ÆøÅº¼Ò¸®.wav", false, false);
	_loading->LoadSound("Ç³°æÁ¾¼Ò¸® LONG", "Sounds/Effect/Ç³°æÁ¾¼Ò¸® LONG.wav", false, false);
	_loading->LoadSound("ÈÄÀÕ", "Sounds/Effect/ÈÄÀÕ.wav", false, false);
	_loading->LoadSound("ÈÄÀ×", "Sounds/Effect/ÈÄÀ×.wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_°¡º­¿ò (1)", "Sounds/Effect/ÈÖµÎ¸£±â_°¡º­¿ò (1).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_°¡º­¿ò (2)", "Sounds/Effect/ÈÖµÎ¸£±â_°¡º­¿ò (2).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_°¡º­¿ò (3)", "Sounds/Effect/ÈÖµÎ¸£±â_°¡º­¿ò (3).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_°¡º­¿ò (4)", "Sounds/Effect/ÈÖµÎ¸£±â_°¡º­¿ò (4).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_°¡º­¿ò (5)", "Sounds/Effect/ÈÖµÎ¸£±â_°¡º­¿ò (5).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_°­ÇÑ¹Ù¶÷", "Sounds/Effect/ÈÖµÎ¸£±â_°­ÇÑ¹Ù¶÷.wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«°Å¿ò (1)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«°Å¿ò (1).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«°Å¿ò (2)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«°Å¿ò (2).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«°Å¿ò (3)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«°Å¿ò (3).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (1)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (1).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (2)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (2).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (3)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (3).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (4)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (4).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (5)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (5).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (6)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (6).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (7)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (7).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (8)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò (8).wav", false, false);

	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (1)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (1).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (2)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (2).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (3)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (3).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (4)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (4).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (5)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (5).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (6)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (6).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (7)", "Sounds/Effect/ÈÖµÎ¸£±â_¹«Ã´°¡º­¿ò2 (7).wav", false, false);
	_loading->LoadSound("ÈÖµÎ¸£±â_¹««r°¡º­¿ò2 (8)", "Sounds/Effect/ÈÖµÎ¸£±â_¹««r°¡º­¿ò2 (8).wav", false, false);

	_loading->LoadSound("NPC_·¹½ºÅä¶û_±îÀñ", "Sounds/Effect/NPC_·¹½ºÅä¶û_±îÀñ.wav", false, false);
	_loading->LoadSound("NPC_·¹½ºÅä¶û_²Ü²©", "Sounds/Effect/NPC_·¹½ºÅä¶û_²Ü²©.wav", false, false);
	_loading->LoadSound("NPC_·¹½ºÅä¶û_¿ÍÀÛ", "Sounds/Effect/NPC_·¹½ºÅä¶û_¿ÍÀÛ.wav", false, false);
	_loading->LoadSound("NPC_·¹½ºÅä¶û_­h", "Sounds/Effect/NPC_·¹½ºÅä¶û_­h.wav", false, false);
	_loading->LoadSound("NPC_·¹½ºÅä¶û_Äí½¹", "Sounds/Effect/NPC_·¹½ºÅä¶û_Äí½¹.wav", false, false);
	_loading->LoadSound("NPC_·¹½ºÅä¶û_È£·Ï", "Sounds/Effect/NPC_·¹½ºÅä¶û_È£·Ï.wav", false, false);
	_loading->LoadSound("NPC_·¹½ºÅä¶û_ÈÄ·è", "Sounds/Effect/NPC_·¹½ºÅä¶û_ÈÄ·è.wav", false, false);
}

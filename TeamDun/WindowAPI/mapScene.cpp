#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	UIMANAGER->init();

	// ���� �� ũ�� ���� //
	_heightNum = 10;
	_widthNum = 10;
	_isSettingPage = true;

	// ȸ�� TESTER // 
	_rotateTester = 0;
	_rotTimer = 0;

	// UI BRUSH TOOL //
	_uiBrushTool = new uibrushTool();
	_uiBrushTool->init();
	_uiBrushTool->SetMapScene(this);

	// MAP //
	_mapTool = new MapTool();

	// FILL (�ι����� ä���)
	_isFillClicked = false;

	UIInit();

	return S_OK;
}

/// <summary>
/// MAPSCENE�� ���� UI�� �ʱ�ȭ�մϴ�.
/// </summary>
void mapScene::UIInit()
{
	UIFrame* setSizeFrame = new UIFrame();
	setSizeFrame->init("sizeFrame", 100, 100, IMAGEMANAGER->findImage("UIBaseBig")->getWidth(), IMAGEMANAGER->findImage("UIBaseBig")->getHeight(), "UIBaseBig");
	UIMANAGER->GetGameFrame()->AddFrame(setSizeFrame);

	UIImage* setUpFrame = new UIImage();
	setUpFrame->init("UpButtonFrame", 860, 380, IMAGEMANAGER->findImage("UpButton")->getWidth(), IMAGEMANAGER->findImage("UpButton")->getHeight(), "UpButton", false, 0, 0);
	setSizeFrame->AddFrame(setUpFrame);

	UIImage* setDownFrame = new UIImage();
	setDownFrame->init("DownButtonFrame", 860, 450, IMAGEMANAGER->findImage("DownButton")->getWidth(), IMAGEMANAGER->findImage("DownButton")->getHeight(), "DownButton", false, 0, 0);
	setSizeFrame->AddFrame(setDownFrame);

	UIImage* setLeftFrame = new UIImage();
	setLeftFrame->init("LeftButtonFrame", 860, 190, IMAGEMANAGER->findImage("LeftButton")->getWidth(), IMAGEMANAGER->findImage("LeftButton")->getHeight(), "LeftButton", false, 0, 0);
	setSizeFrame->AddFrame(setLeftFrame);

	UIImage* setRightFrame = new UIImage();
	setRightFrame->init("RightButtonFrame", 860, 120, IMAGEMANAGER->findImage("RightButton")->getWidth(), IMAGEMANAGER->findImage("RightButton")->getHeight(), "RightButton", false, 0, 0);
	setSizeFrame->AddFrame(setRightFrame);

	UIImage* setHeightBoxFrame = new UIImage();
	setHeightBoxFrame->init("HeightBox", 600, 390, IMAGEMANAGER->findImage("mapHeightBox")->getWidth(), IMAGEMANAGER->findImage("mapHeightBox")->getHeight(), "mapHeightBox", false, 0, 0);
	setSizeFrame->AddFrame(setHeightBoxFrame);

	UIImage* setWidthBoxFrame = new UIImage();
	setWidthBoxFrame->init("WidthBox", 600, 130, IMAGEMANAGER->findImage("mapWidthBox")->getWidth(), IMAGEMANAGER->findImage("mapWidthBox")->getHeight(), "mapWidthBox", false, 0, 0);
	setSizeFrame->AddFrame(setWidthBoxFrame);

	UIText* widthText = new UIText();
	widthText->init("Word", -200, 40, 200, 50, "����", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setHeightBoxFrame->AddFrame(widthText);

	UIText* heightText = new UIText();
	heightText->init("Word", -200, 40, 200, 50, "����", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setWidthBoxFrame->AddFrame(heightText);

	UIText* setHeightNumFrame = new UIText();
	setHeightNumFrame->init("Word", 0, 40, 200, 50, to_string(_heightNum), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setHeightBoxFrame->AddFrame(setHeightNumFrame);

	UIText* setWidthNumFrame = new UIText();
	setWidthNumFrame->init("Word", 0, 40, 200, 50, to_string(_widthNum), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setWidthBoxFrame->AddFrame(setWidthNumFrame);
}

void mapScene::release()
{
}

void mapScene::update()
{
	UIMANAGER->update();

	if (_isSettingPage) // �� ������ ���� ��
	{
		SetMapSize();
	}

	else
	{
		GetUiBrush();
		Paint();
		RemovePaint();
		FillAll();
		FillSquareRange();
		FloodFill();
		AddMapLine();
		saveData();
		loadData();
	}
}

/// <summary>
/// �ش� ���콺 �����Ͱ� ��ġ�� �κ��� ĥ�Ѵ�
/// </summary>
void mapScene::Paint()
{
	if (_targetImage != nullptr)
	{
		if (INPUT->GetKeyDown(VK_RBUTTON))
		{
			_mapTool->EveSaveData();//��ư�� ������ �������� ������ ������ ����
		}

		if (INPUT->GetKey(VK_RBUTTON))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid) grid->_img = _targetImage;
		}
	}
}

/// <summary>
/// ���콺 ������ ���� Ÿ���� �̻������ �ٲ۴�
/// </summary>
void mapScene::RemovePaint()
{
	if (_targetImage != nullptr)
	{
		if (INPUT->GetKeyDown(VK_SPACE))
		{
			_mapTool->EveSaveData(); //��ư�� ������ �������� ������ ������ ����
		}

		if (INPUT->GetKey(VK_SPACE))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid)
			{
				grid->_img = nullptr;
			}
		}
	}
}

/// <summary>
/// �ι��� ���� �Է��� �簢 ������ŭ�� ĥ�Ѵ�
/// </summary>
void mapScene::FillSquareRange()
{
	if (_targetImage != nullptr && INPUT->GetKeyDown('A'))
	{

		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{

			if (_isFillClicked == false)
			{
				_clickedPointOne = POINT{ grid->_xIndex, grid->_yIndex };
				_isFillClicked = true;
			}

			else
			{
				_mapTool->EveSaveData();
				_clickedPointTwo = POINT{ grid->_xIndex, grid->_yIndex };
				_mapTool->GridRange(_clickedPointOne.x, _clickedPointOne.y, _clickedPointTwo.x, _clickedPointTwo.y);
				_isFillClicked = false;
			}
		}
	}
}

/// <summary>
/// �ֺ��� �˻��Ͽ� ���� Ÿ�ϸ� ĥ�ϵ��� �Ѵ�
/// </summary>
void mapScene::FloodFill()
{
	if (_targetImage != nullptr && INPUT->GetKeyDown('O'))
	{
		_mapTool->EveSaveData();
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			if (grid->_img != _targetImage)
			{
				_mapTool->FloodFill(grid->_img, grid->_xIndex, grid->_yIndex);
			}
		}
	}
}

/// <summary>
/// ��� Ÿ���� ä�쵵�� �Ѵ�
/// </summary>
void mapScene::FillAll()
{
	if (_targetImage != nullptr && INPUT->GetKeyDown('P'))
	{
		_mapTool->EveSaveData();
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			_mapTool->FillAll();
		}
	}
}

/// <summary>
/// �Է��� ���� brush�� �����ϵ��� �Ѵ�
/// </summary>
void mapScene::GetUiBrush()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		_uiBrushTool->mouseCollisionCheck();
	}
}

/// <summary>
/// �ʱ⿡ �� ����� ���ϵ��� �Ѵ�
/// </summary>
void mapScene::SetMapSize()
{
	if (INPUT->GetKeyDown(VK_TAB))
	{
		_mapTool->init(_widthNum, _heightNum);
		_mapTool->SetMapScene(this);
		_isSettingPage = false;
		UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->SetIsViewing(false);
	}

	//10���ڸ� ���� ��� ���ϰ� �ϴ°� ����
	/*UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("HeightBox")->GetChild("Word2")->SetIsViewing(false, false);*/

	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("sizeFrame");
	if (PtInRect(&frame->GetChild("UpButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
	{
		_heightNum++;
		dynamic_cast<UIText*>(frame->GetChild("HeightBox")->GetChild("Word"))->SetText(to_string(_heightNum));
	}
	if (PtInRect(&frame->GetChild("DownButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
	{
		_heightNum--;
		if (_heightNum < 1) _heightNum = 1;
		dynamic_cast<UIText*>(frame->GetChild("HeightBox")->GetChild("Word"))->SetText(to_string(_heightNum));
	}
	if (PtInRect(&frame->GetChild("RightButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
	{
		_widthNum++;
		dynamic_cast<UIText*>(frame->GetChild("WidthBox")->GetChild("Word"))->SetText(to_string(_widthNum));
	}
	if (PtInRect(&frame->GetChild("LeftButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
	{
		_widthNum--;
		if (_widthNum < 1) _widthNum = 1;
		dynamic_cast<UIText*>(frame->GetChild("WidthBox")->GetChild("Word"))->SetText(to_string(_widthNum));
	}
}

void mapScene::saveData()
{
	if (INPUT->GetKeyDown('S'))
	{
		_mapTool->SaveData();
	}
}

/// <summary>
/// ���� ũ�⸦ �����Ѵ�
/// </summary>
void mapScene::AddMapLine()
{
	if (INPUT->GetKeyDown('T'))
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineAddCol();
	}

	if (INPUT->GetKeyDown('Y'))
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineAddRow();
	}

	if (INPUT->GetKeyDown('G'))
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineRemoveCol();
	}

	if (INPUT->GetKeyDown('H'))
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineRemoveRow();
	}
}

/// <summary>
/// �� �ε� �� ������Ҹ� �Ѵ�
/// </summary>
void mapScene::loadData()
{
	if (INPUT->GetKeyDown('L'))
	{
		_mapTool->EveSaveData();
		_mapTool->LoadData();
	}

	if (INPUT->GetKeyDown('R'))
	{
		_mapTool->EveLoadData();
	}
}

void mapScene::render()
{
	_uiBrushTool->render();
	_mapTool->render();

	if (_targetImage) _targetImage->alphaRender(getMemDC(), _ptMouse.x, _ptMouse.y, 128);

	UIMANAGER->render(getMemDC());


	// ȸ���ǵ� //
	/*
	_rotTimer++;
	IMAGEMANAGER->findImage("DCutter")->frameRender(getMemDC(), 0, 0, _rotateTester, 0);
	 IMAGEMANAGER->findImage("WoodenQuarterStaff")->frameRender(getMemDC(), 500, 0, _rotateTester, 0);
	 IMAGEMANAGER->findImage("WoodenQuarterStaff_Short")->frameRender(getMemDC(), 1000, 0, _rotateTester, 0);
	if (_rotTimer > 5)
	{
		_rotTimer = 0;
		_rotateTester = _rotateTester + 1 >= 12 ? 0 : _rotateTester + 1;
	}
	*/
}

#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	UIMANAGER->init();

	// ī�޶� //
	_pivot = POINT{ _widthNum / 2 * 48, _heightNum / 2 * 48 };
	CAMERAMANAGER->init(_pivot.x, _pivot.y, 50000, 50000, -50000, -50000, WINSIZEX / 2, WINSIZEY / 2);
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

	// FILL (�ι����� ä���) //
	_isFillClicked = false;

	// SAVE LOAD //
	_hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL | ES_RIGHT, 500, 500, 200, 50, _hWnd, (HMENU)100, _hInstance, NULL);
	ShowWindow(_hEdit, SW_HIDE);
	_isEditerViewing = false;
	_isLoad = false;

	// UI //
	UIInit();

	return S_OK;
}

/// <summary>
/// MAPSCENE�� ���� UI�� �ʱ�ȭ�մϴ�.
/// </summary>
void mapScene::UIInit()
{
	UIFrame* setShortcutKeyFrame = new UIFrame();
	setShortcutKeyFrame->init("ShortcutKeyFrame", 60, WINSIZEY - 100, IMAGEMANAGER->findImage("ShortcutKeyGround")->getWidth(), IMAGEMANAGER->findImage("ShortcutKeyGround")->getHeight(), "ShortcutKeyGround");
	UIMANAGER->GetGameFrame()->AddFrame(setShortcutKeyFrame);

	for (int i = 0; i < 10; i++)
	{
		UIFrame* setShortcutKeyBox = new UIFrame();
		setShortcutKeyBox->init("shortcutBox" + to_string(i), 100 + 70 * i, 15, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
		setShortcutKeyFrame->AddFrame(setShortcutKeyBox);

		UIImage* setShortcutKeyIg = new UIImage();
		setShortcutKeyIg->init("Ig", 4, 4, 48, 48, "", false, 0, 0);
		setShortcutKeyBox->AddFrame(setShortcutKeyIg);
	}

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

	UIFrame* saveLoadFrame = new UIFrame();
	saveLoadFrame->init("saveLoadFrame", 100, 100, IMAGEMANAGER->findImage("UIBaseBig")->getWidth(), IMAGEMANAGER->findImage("UIBaseBig")->getHeight(), "UIBaseBig");
	UIMANAGER->GetGameFrame()->AddFrame(saveLoadFrame);
	saveLoadFrame->SetIsViewing(false);

	UIText* saveLoadText = new UIText();
	saveLoadText->init("SaveLoader", 200, 200, 200, 100, "SAVE", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	saveLoadFrame->AddFrame(saveLoadText);

	UIFrame* ShortcutFrame = new UIFrame();
	ShortcutFrame->init("ShortcutFrame", 60, 0, IMAGEMANAGER->findImage("ShortcutKeyGround")->getWidth(), IMAGEMANAGER->findImage("ShortcutKeyGround")->getHeight(), "ShortcutKeyGround");
	UIMANAGER->GetGameFrame()->AddFrame(ShortcutFrame);

	for (int i = 0; i < 9; i++)
	{
		UIFrame* setShortcutKeyBox = new UIFrame();
		setShortcutKeyBox->init("shortcutBox" + to_string(i), 100 + 80 * i, 15, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
		ShortcutFrame->AddFrame(setShortcutKeyBox);

		UIImage* setShortcutKeyIg = new UIImage();
		setShortcutKeyIg->init("Ig", 4, 4, 48, 48, "", false, 0, 0);
		setShortcutKeyBox->AddFrame(setShortcutKeyIg);

		UIText* text = new UIText();
		switch (i)
		{
		case 0:
			text->init("Text", 0, 16, 48, 24, "SAVE", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 1:
			text->init("Text", 0, 16, 48, 24, "LOAD", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 2:
			text->init("Text", 0, 16, 48, 24, "PAINT", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 3:
			text->init("Text", 0, 16, 48, 24, "ERASE", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 4:
			text->init("Text", 0, 16, 48, 24, "FILL", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 5:
			text->init("Text", 0, 16, 48, 24, "RECT", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 6:
			text->init("Text", 0, 16, 48, 24, "FLOOD", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 7:
			text->init("Text", 0, 16, 48, 24, "SIZE", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 8:
			text->init("Text", 0, 16, 48, 24, "UNDO", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		}
		setShortcutKeyIg->AddFrame(text);
	}

	UIFrame* adjustSizeFrame = new UIFrame();
	adjustSizeFrame->init("ShortSizeFrame", -100, 60, IMAGEMANAGER->findImage("AltarButton0")->getWidth(), IMAGEMANAGER->findImage("AltarButton0")->getHeight(), "AltarButton0");
	UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->AddFrame(adjustSizeFrame);

	for (int i = 0; i < 4; i++)
	{
		UIFrame* setSizeBoxFrame = new UIFrame();
		setSizeBoxFrame->init("shortSizeBox" + to_string(i), 70 * i, 15, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
		adjustSizeFrame->AddFrame(setSizeBoxFrame);

		UIImage* setSizeBoxImg = new UIImage();
		setSizeBoxImg->init("Ig", 4, 4, 48, 48, "", false, 0, 0);
		setSizeBoxFrame->AddFrame(setSizeBoxImg);

		UIText* text = new UIText();

		switch (i)
		{
		case 0:
			text->init("Text", 0, 16, 48, 24, "AddCol", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 1:
			text->init("Text", 0, 16, 48, 24, "AddRow", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 2:
			text->init("Text", 0, 16, 48, 24, "RemoveCol", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		case 3:
			text->init("Text", 0, 16, 48, 24, "RemoveRow", FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
			break;
		}
		setSizeBoxImg->AddFrame(text);
	}
	UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(false);
}

void mapScene::release()
{
}

void mapScene::update()
{
	UIMANAGER->update();
	InputCheck();

	if (_isSettingPage) // �� ������ ���� ��
	{
		SetMapSize();
	}

	else
	{
		_uiBrushTool->update();
		CheckShortCutBtnCollision();
		DoClickByType();
		GetUiBrush();
		ToolMovePage();

		UpdateFillSquareRange();
		SaveLoadMap();
		CameraMove();
		SaveShortcutKey();
		LoadShortcutKey();

		CAMERAMANAGER->MovePivot(_pivot.x, _pivot.y);
	}
}

void mapScene::InputCheck()
{
	_isLeftClicked = false;
	_isRightClicked = false;

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		_isLeftClicked = true;
	}

	if (INPUT->GetKeyDown(VK_RBUTTON)) _isRightClicked = true;
}

/// <summary>
/// �ش� ���콺 �����Ͱ� ��ġ�� �κ��� ĥ�Ѵ�
/// </summary>
void mapScene::Paint()
{
	// _mapTool->EveSaveData();//��ư�� ������ �������� ������ ������ ����
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid) grid->_img = _targetImage;
}

/// <summary>
/// ���콺 ������ ���� Ÿ���� �̻������ �ٲ۴�
/// </summary>
void mapScene::RemovePaint()
{
	// _mapTool->EveSaveData(); //��ư�� ������ �������� ������ ������ ����
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid)
	{
		grid->_img = nullptr;
	}
}

void mapScene::UpdateFillSquareRange()
{
	if (_isFillClicked)
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if(grid != nullptr) _mapTool->PreviewGridRange(_clickedPointOne.x, _clickedPointOne.y, grid->_xIndex, grid->_yIndex, 150);
	}
}

/// <summary>
/// �ι��� ���� �Է��� �簢 ������ŭ�� ĥ�Ѵ�
/// </summary>
void mapScene::FillSquareRange()
{
	if (_isFillClicked == false)
	{
		if (_targetImage != nullptr)
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid)
			{
				_clickedPointOne = POINT{ grid->_xIndex, grid->_yIndex };
				_isFillClicked = true;
			}
		}
	}

	else if (_isFillClicked)
	{
		if (_targetImage != nullptr)
		{
			Grid* grid = _mapTool->mouseCollisionCheck();

			if (grid)
			{
				_clickedPointTwo = POINT{ grid->_xIndex, grid->_yIndex };
				_mapTool->GridRange(_clickedPointOne.x, _clickedPointOne.y, _clickedPointTwo.x, _clickedPointTwo.y);
				_isFillClicked = false;
				for (int i = 0; i < _mapTool->GetGrid().size(); i++)
				{
					for (int j = 0; j < _mapTool->GetGrid()[i].size(); j++)
					{
						_mapTool->GetGrid()[i][j]->_alpha = 30;
					}
				}
			}
		}
	}
}

void mapScene::CheckShortCutBtnCollision()
{
	if (_isLeftClicked)
	{
		UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame");
		for (int i = 0; i < 9; i++)
		{
			if (PtInRect(&frame->GetChild("shortcutBox" + to_string(i))->GetRect(), _ptMouse))
			{
				switch (i)
				{
				case 0:
					CallSaveEditor(); break;
				case 1:
					CallLoadEditor(); break;
				case 2:
					_brushType = BRUSHTYPE::BT_PAINT; break;
				case 3:
					_brushType = BRUSHTYPE::BT_ERASE; break;
				case 4:
					FillAll(); break;
				case 5:
					_brushType = BRUSHTYPE::BT_FILLRECT; break;
				case 6:
					_brushType = BRUSHTYPE::BT_FLOODFILL; break;
				case 7:
					AddRemoveLine(); break;
				case 8:
					Undo(); break;
				}
			}
			//_mapTool->EveSaveData(); //��ư�� ������ �������� ������ ������ ����
		}

		if (_isEditerViewing == true)
		{
			UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame");
			
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&frame->GetChild("shortSizeBox" + to_string(i))->GetRect(), _ptMouse))
				{
					switch (i)
					{
					case 0:
						AddMapLine(0);
						break;
					case 1:
						AddMapLine(1);
						break;
					case 2:
						AddMapLine(2);
						break;
					case 3:
						AddMapLine(3);
						break;
					}
				}
			}
			return;
		}
	}
}

void mapScene::DoClickByType()
{
	if (_isLeftClicked)
	{
		switch (_brushType)
		{
		case BT_FILLRECT:
			if (_targetImage) FillSquareRange();
			break;
		case BT_FLOODFILL:
			if (_targetImage) FloodFill();
			break;
		}
	}

	if (INPUT->GetKey(VK_LBUTTON))
	{
		switch (_brushType)
		{
		case BT_PAINT:
			if (_targetImage) Paint();
			break;
		case BT_ERASE:
			RemovePaint();
			break;
		}
	}
}

void mapScene::ToolMovePage()
{
	if (_uiBrushTool->GetPage() > 0 && PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("arrowLeft")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		_uiBrushTool->SetPage(_uiBrushTool->GetPage() - 1);
		_uiBrushTool->PageViewChange();
	}

	if (_uiBrushTool->GetPage() < _uiBrushTool->GetUiBrushGrid().size() - 1 && PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("arrowRight")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		_uiBrushTool->SetPage(_uiBrushTool->GetPage() + 1);
		_uiBrushTool->PageViewChange();
	}
}

/// <summary>
/// �ֺ��� �˻��Ͽ� ���� Ÿ�ϸ� ĥ�ϵ��� �Ѵ�
/// </summary>
void mapScene::FloodFill()
{
	// _mapTool->EveSaveData();
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid)
	{
		if (grid->_img != _targetImage)
		{
			_mapTool->FloodFill(grid->_img, grid->_xIndex, grid->_yIndex);
		}
	}
}

/// <summary>
/// ��� Ÿ���� ä�쵵�� �Ѵ�
/// </summary>
void mapScene::FillAll()
{
	// _mapTool->EveSaveData();
	_mapTool->FillAll();
}

/// <summary>
/// �Է��� ���� brush�� �����ϵ��� �Ѵ�
/// </summary>
void mapScene::GetUiBrush()
{
	if (_isLeftClicked)
	{
		_uiBrushTool->MenuCollisionCheck();
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
		_pivot.x = _widthNum * 48 / 2;
		_pivot.y = _heightNum * 48 / 2;
		_uiBrushTool->UIInit();
	}

	//10���ڸ� ���� ��� ���ϰ� �ϴ°� ����
	/*UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("HeightBox")->GetChild("Word2")->SetIsViewing(false, false);*/

	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("sizeFrame");
	if (PtInRect(&frame->GetChild("UpButtonFrame")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		_heightNum++;
		dynamic_cast<UIText*>(frame->GetChild("HeightBox")->GetChild("Word"))->SetText(to_string(_heightNum));
	}
	if (PtInRect(&frame->GetChild("DownButtonFrame")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		_heightNum--;
		if (_heightNum < 1) _heightNum = 1;
		dynamic_cast<UIText*>(frame->GetChild("HeightBox")->GetChild("Word"))->SetText(to_string(_heightNum));
	}
	if (PtInRect(&frame->GetChild("RightButtonFrame")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		_widthNum++;
		dynamic_cast<UIText*>(frame->GetChild("WidthBox")->GetChild("Word"))->SetText(to_string(_widthNum));
	}
	if (PtInRect(&frame->GetChild("LeftButtonFrame")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		_widthNum--;
		if (_widthNum < 1) _widthNum = 1;
		dynamic_cast<UIText*>(frame->GetChild("WidthBox")->GetChild("Word"))->SetText(to_string(_widthNum));
	}
}

void mapScene::CallSaveEditor()
{
	if (!_isEditerViewing || _isLoad)
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(true);
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->GetChild("SaveLoader"))->SetText("SAVE");
		_isEditerViewing = true;
		ShowWindow(_hEdit, SW_SHOW);
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(false);
		_isEditerViewing = false;
		ShowWindow(_hEdit, SW_HIDE);
	}
	_isLoad = false;
}

void mapScene::CallLoadEditor()
{
	if (!_isEditerViewing || !_isLoad)
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(true);
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->GetChild("SaveLoader"))->SetText("LOAD");
		_isEditerViewing = true;
		ShowWindow(_hEdit, SW_SHOW);
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(false);
		_isEditerViewing = false;
		ShowWindow(_hEdit, SW_HIDE);
	}
	_isLoad = true;
}

/// <summary>
/// ���� ũ�⸦ �����Ѵ�
/// </summary>
void mapScene::AddMapLine(int type)
{
	if (type == 0)
	{
		//_mapTool->EveSaveData();
		_mapTool->MapLineAddCol();
	}

	if (type == 1)
	{
		//_mapTool->EveSaveData();
		_mapTool->MapLineAddRow();
	}

	if (type == 2)
	{
		//_mapTool->EveSaveData();
		_mapTool->MapLineRemoveCol();
	}

	if (type == 3)
	{
		//_mapTool->EveSaveData();
		_mapTool->MapLineRemoveRow();
	}
}

/// <summary>
/// ������Ҹ� �Ѵ�
/// </summary>
void mapScene::Undo()
{
	_mapTool->EveLoadData();
}

void mapScene::render()
{
	_mapTool->render();
	_uiBrushTool->render();

	Grid* targetGrid = _mapTool->mouseCollisionCheck();
	if (_targetImage && targetGrid) CAMERAMANAGER->AlphaRender(getMemDC(), _targetImage, targetGrid->_rc.left, targetGrid->_rc.top, 100);
	if (_targetObject) _targetObject->_image->alphaRender(getMemDC(), _ptMouse.x, _ptMouse.y, 100);
	
	UIMANAGER->render(getMemDC());

	string n = to_string(_ptMouse.x) + " " + to_string(_ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, n.c_str(), n.length());
}

void mapScene::CameraMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		_pivot.x -= 30;
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		_pivot.x += 30;
	}
	if (INPUT->GetKey(VK_UP))
	{
		_pivot.y -= 30;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		_pivot.y += 30;
	}
}

void mapScene::SaveLoadMap()
{
	if (_isEditerViewing && INPUT->GetKeyDown(VK_RETURN))
	{
		GetWindowText(_hEdit, _fileName, 128);
		if (!_isLoad)
		{
			_mapTool->SaveData(_fileName);
		}

		else
		{
			// _mapTool->EveSaveData();
			_mapTool->LoadData(_fileName);
		}
	}
}

void mapScene::AddRemoveLine()
{
	if (!_isEditerViewing || INPUT->GetKeyDown(VK_LBUTTON))
	{
		UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(true);
		_isEditerViewing = true;
	}
	else
	{
		UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(false);
		_isEditerViewing = false;
	}
}

void mapScene::SaveShortcutKey()
{
	for (int i = 0; i < 10; i++)
	{
		if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('0' + i))
		{
			UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame")->GetChild("shortcutBox" + to_string(i))->GetChild("Ig")->SetImage(_targetImage);
		}
	}
}

void mapScene::LoadShortcutKey()
{
	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame");
	for (int i = 0; i < 10; i++)
	{
		if (frame->GetChild("shortcutBox" + to_string(i))->GetChild("Ig")->GetImage() != nullptr)
		{
			if (INPUT->GetKeyDown('0' + i))
			{
				_targetImage = frame->GetChild("shortcutBox" + to_string(i))->GetChild("Ig")->GetImage();
			}
		}
	}
}

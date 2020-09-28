#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	UIMANAGER->init();
	ShowCursor(false);

	// ī�޶� //
	_pivot = POINT{ _widthNum / 2 * 48, _heightNum / 2 * 48 };
	CAMERAMANAGER->init(_pivot.x, _pivot.y, 50000, 50000, -50000, -50000, WINSIZEX / 2, WINSIZEY / 2);
	// ���� �� ũ�� ���� //
	_heightNum = 50;
	_widthNum = 50;
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

	// SUB WINDOW //
	_hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL | ES_RIGHT, WINSIZEX / 2 - 95, WINSIZEY / 2, 200, 25, _hWnd, (HMENU)100, _hInstance, NULL);
	ShowWindow(_hEdit, SW_HIDE);
	_isSaveLoaderOn = false;
	_isLoad = false;

	_hMonsterSpawnTime = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL | ES_RIGHT, WINSIZEX / 2 - 95, WINSIZEY / 2, 80, 25, _hWnd, (HMENU)100, _hInstance, NULL);
	ShowWindow(_hMonsterSpawnTime, SW_HIDE);
	_isMonsterSettingOn = false;

	// SAVELOAD //
	_autoSaveCount = 1;

	// UI //
	UIInit();
	_isSizeAdjustOpened = false;

	_cursorImageStrings.push_back("BasicCursor");
	_cursorImageStrings.push_back("brushCursor");
	_cursorImageStrings.push_back("paintCursor");
	_cursorImageStrings.push_back("eraserCursor");

	_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[0]);

	return S_OK;
}

/// <summary>
/// MAPSCENE�� ���� UI�� �ʱ�ȭ�մϴ�.
/// </summary>
void mapScene::UIInit()
{
	UIFrame* setShortcutKeyFrame = new UIFrame();
	setShortcutKeyFrame->init("ShortcutKeyFrame", 300, WINSIZEY - 150, IMAGEMANAGER->findImage("ShortcutKeyGround")->getWidth(), IMAGEMANAGER->findImage("ShortcutKeyGround")->getHeight(), "ShortcutKeyGround");
	UIMANAGER->GetGameFrame()->AddFrame(setShortcutKeyFrame);
	setShortcutKeyFrame->SetIsViewing(false);

	for (int i = 1; i < 11; i++)
	{
		UIFrame* setShortcutKeyBox = new UIFrame();
		setShortcutKeyBox->init("shortcutBox" + to_string(i - 1), 55 + 70 * (i - 1), 15, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
		setShortcutKeyFrame->AddFrame(setShortcutKeyBox);

		UIImage* setShortcutKeyIg = new UIImage();
		setShortcutKeyIg->init("Ig", 4, 4, 48, 48, "", false, 0, 0);
		setShortcutKeyBox->AddFrame(setShortcutKeyIg);

		UIText* setShortcutKeyNum = new UIText();
		setShortcutKeyNum->init("shorcutNum", 17, 30, 50, 50, to_string(i % 10), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
		setShortcutKeyIg->AddFrame(setShortcutKeyNum);
	}

	UIFrame* setSizeFrame = new UIFrame();
	setSizeFrame->init("sizeFrame", WINSIZEX / 2 - 250, WINSIZEY / 2 - 150, IMAGEMANAGER->findImage("UIBaseBig")->getWidth(), IMAGEMANAGER->findImage("UIBaseBig")->getHeight(), "UIBaseBig");
	UIMANAGER->GetGameFrame()->AddFrame(setSizeFrame);

	UIImage* setUpFrame = new UIImage();
	setUpFrame->init("UpButtonFrame", 180, 100, IMAGEMANAGER->findImage("UpButton")->getWidth(), IMAGEMANAGER->findImage("UpButton")->getHeight(), "UpButton", false, 0, 0);
	setSizeFrame->AddFrame(setUpFrame);

	UIImage* setDownFrame = new UIImage();
	setDownFrame->init("DownButtonFrame", 180, 170, IMAGEMANAGER->findImage("DownButton")->getWidth(), IMAGEMANAGER->findImage("DownButton")->getHeight(), "DownButton", false, 0, 0);
	setSizeFrame->AddFrame(setDownFrame);

	UIImage* setLeftFrame = new UIImage();
	setLeftFrame->init("LeftButtonFrame", 400, 170, IMAGEMANAGER->findImage("LeftButton")->getWidth(), IMAGEMANAGER->findImage("LeftButton")->getHeight(), "LeftButton", false, 0, 0);
	setSizeFrame->AddFrame(setLeftFrame);

	UIImage* setRightFrame = new UIImage();
	setRightFrame->init("RightButtonFrame", 400, 100, IMAGEMANAGER->findImage("RightButton")->getWidth(), IMAGEMANAGER->findImage("RightButton")->getHeight(), "RightButton", false, 0, 0);
	setSizeFrame->AddFrame(setRightFrame);

	UIImage* setHeightBoxFrame = new UIImage();
	setHeightBoxFrame->init("HeightBox", 50, 130, IMAGEMANAGER->findImage("mapHeightBox")->getWidth(), IMAGEMANAGER->findImage("mapHeightBox")->getHeight(), "mapHeightBox", false, 0, 0);
	setSizeFrame->AddFrame(setHeightBoxFrame);

	UIImage* setWidthBoxFrame = new UIImage();
	setWidthBoxFrame->init("WidthBox", 270, 130, IMAGEMANAGER->findImage("mapWidthBox")->getWidth(), IMAGEMANAGER->findImage("mapWidthBox")->getHeight(), "mapWidthBox", false, 0, 0);
	setSizeFrame->AddFrame(setWidthBoxFrame);

	UIText* widthText = new UIText();
	widthText->init("Word", -40, -50, 200, 50, "����", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setHeightBoxFrame->AddFrame(widthText);

	UIText* heightText = new UIText();
	heightText->init("Word", -40, -50, 200, 50, "����", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setWidthBoxFrame->AddFrame(heightText);

	UIText* setHeightNumFrame = new UIText();
	setHeightNumFrame->init("Word", -40, 30, 200, 50, to_string(_heightNum), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setHeightBoxFrame->AddFrame(setHeightNumFrame);

	UIText* setWidthNumFrame = new UIText();
	setWidthNumFrame->init("Word", -40, 30, 200, 50, to_string(_widthNum), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setWidthBoxFrame->AddFrame(setWidthNumFrame);

	UIFrame* saveLoadFrame = new UIFrame();
	saveLoadFrame->init("saveLoadFrame", WINSIZEX / 2 - 170, WINSIZEY / 2 - 130, IMAGEMANAGER->findImage("UIBaseBig")->getWidth(), IMAGEMANAGER->findImage("UIBaseBig")->getHeight(), "UIBaseBig", 0.7, 0.7f);
	UIMANAGER->GetGameFrame()->AddFrame(saveLoadFrame);
	saveLoadFrame->SetIsViewing(false);

	UIText* saveLoadText = new UIText();
	saveLoadText->init("SaveLoader", 75, 60, 200, 100, "SAVE", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	saveLoadFrame->AddFrame(saveLoadText);

	UIFrame* ShortcutFrame = new UIFrame();
	ShortcutFrame->init("ShortcutFrame", 300, 50, IMAGEMANAGER->findImage("ShortcutKeyGround")->getWidth(), IMAGEMANAGER->findImage("ShortcutKeyGround")->getHeight(), "ShortcutKeyGround");
	UIMANAGER->GetGameFrame()->AddFrame(ShortcutFrame);
	ShortcutFrame->SetIsViewing(false);

	for (int i = 0; i < 9; i++)
	{
		UIFrame* setShortcutKeyBox = new UIFrame();
		setShortcutKeyBox->init("shortcutBox" + to_string(i), 50 + 80 * i, 15, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
		ShortcutFrame->AddFrame(setShortcutKeyBox);

		UIImage* setShortcutKeyIg = new UIImage();
		setShortcutKeyIg->init("Ig", 4, 4, 48, 48, "", false, 0, 0);
		setShortcutKeyBox->AddFrame(setShortcutKeyIg);

		UIFrame* SaveIcon = new UIFrame();
		UIFrame* loadIcon = new UIFrame();
		UIFrame* FillRectIcon = new UIFrame();
		UIFrame* FillIcon = new UIFrame();
		UIFrame* FloodFillIcon = new UIFrame();
		UIFrame* SizeUpDownIcon = new UIFrame();
		UIFrame* UndoIcon = new UIFrame();
		UIFrame* PaintIcon = new UIFrame();
		UIFrame* EraseIcon = new UIFrame();

		switch (i)
		{
		case 0:
			SaveIcon->init("saveIcon", 5, 4, IMAGEMANAGER->findImage("saveIcon")->getWidth(), IMAGEMANAGER->findImage("saveIcon")->getHeight(), "saveIcon", 0.8f, 0.8f);
			setShortcutKeyIg->AddFrame(SaveIcon);
			break;
		case 1:
			loadIcon->init("loadIcon", 5, 4, IMAGEMANAGER->findImage("loadIcon")->getWidth(), IMAGEMANAGER->findImage("loadIcon")->getHeight(), "loadIcon", 0.8f, 0.8f);
			setShortcutKeyIg->AddFrame(loadIcon);
			break;
		case 2:
			PaintIcon->init("paintIcon", 3, 2, IMAGEMANAGER->findImage("paintIcon")->getWidth(), IMAGEMANAGER->findImage("paintIcon")->getHeight(), "paintIcon");
			setShortcutKeyIg->AddFrame(PaintIcon);
			break;
		case 3:
			EraseIcon->init("eraseIcon", 5, 5, IMAGEMANAGER->findImage("eraseIcon")->getWidth(), IMAGEMANAGER->findImage("eraseIcon")->getHeight(), "eraseIcon");
			setShortcutKeyIg->AddFrame(EraseIcon);
			break;
		case 4:
			FillIcon->init("fillIcon", 7, 3, IMAGEMANAGER->findImage("fillIcon")->getWidth(), IMAGEMANAGER->findImage("fillIcon")->getHeight(), "fillIcon");
			setShortcutKeyIg->AddFrame(FillIcon);
			break;
		case 5:
			FillRectIcon->init("fillRectIcon", 5, 5, IMAGEMANAGER->findImage("fillRectIcon")->getWidth(), IMAGEMANAGER->findImage("fillRectIcon")->getHeight(), "fillRectIcon", 0.8f, 0.8f);
			setShortcutKeyIg->AddFrame(FillRectIcon);
			break;
		case 6:
			FloodFillIcon->init("floodFillIcon", 5, 5, IMAGEMANAGER->findImage("floodFillIcon")->getWidth(), IMAGEMANAGER->findImage("floodFillIcon")->getHeight(), "floodFillIcon", 0.8f, 0.8f);
			setShortcutKeyIg->AddFrame(FloodFillIcon);
			break;
		case 7:
			SizeUpDownIcon->init("sizeUpDownIcon", 0, 0, IMAGEMANAGER->findImage("sizeUpDownIcon")->getWidth(), IMAGEMANAGER->findImage("sizeUpDownIcon")->getHeight(), "sizeUpDownIcon");
			setShortcutKeyIg->AddFrame(SizeUpDownIcon);
			break;
		case 8:
			UndoIcon->init("undoIcon", 5, 5, IMAGEMANAGER->findImage("undoIcon")->getWidth(), IMAGEMANAGER->findImage("undoIcon")->getHeight(), "undoIcon", 0.8f, 0.8f);
			setShortcutKeyIg->AddFrame(UndoIcon);
			break;
		}
	}

	UIFrame* adjustSizeFrame = new UIFrame();
	adjustSizeFrame->init("ShortSizeFrame", -120, 70, IMAGEMANAGER->findImage("AltarButton0")->getWidth(), IMAGEMANAGER->findImage("AltarButton0")->getHeight(), "AltarButton0");
	UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->AddFrame(adjustSizeFrame);
	for (int i = 0; i < 4; i++)
	{
		UIFrame* setSizeBoxFrame = new UIFrame();
		setSizeBoxFrame->init("shortSizeBox" + to_string(i), 17 + 70 * i, 16, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
		adjustSizeFrame->AddFrame(setSizeBoxFrame);

		UIImage* setSizeBoxImg = new UIImage();
		setSizeBoxImg->init("Ig", 4, 4, 48, 48, "", false, 0, 0);
		setSizeBoxFrame->AddFrame(setSizeBoxImg);

		UIFrame* ColMinusIcon = new UIFrame();
		UIFrame* ColPlusIcon = new UIFrame();
		UIFrame* RowMinusIcon = new UIFrame();
		UIFrame* RowPlusIcon = new UIFrame();

		switch (i)
		{
		case 0:
			ColPlusIcon->init("colPlusIcon", 0, 0, IMAGEMANAGER->findImage("colPlusIcon")->getWidth(), IMAGEMANAGER->findImage("colPlusIcon")->getHeight(), "colPlusIcon");
			setSizeBoxImg->AddFrame(ColPlusIcon);
			break;
		case 1:
			RowPlusIcon->init("rowPlusIcon", 0, 0, IMAGEMANAGER->findImage("rowPlusIcon")->getWidth(), IMAGEMANAGER->findImage("rowPlusIcon")->getHeight(), "rowPlusIcon");
			setSizeBoxImg->AddFrame(RowPlusIcon);
			break;
		case 2:
			ColMinusIcon->init("colMinusIcon", 0, 0, IMAGEMANAGER->findImage("colMinusIcon")->getWidth(), IMAGEMANAGER->findImage("colMinusIcon")->getHeight(), "colMinusIcon");
			setSizeBoxImg->AddFrame(ColMinusIcon);
			break;
		case 3:
			RowMinusIcon->init("rowMinusIcon", -1, 2, IMAGEMANAGER->findImage("rowMinusIcon")->getWidth(), IMAGEMANAGER->findImage("rowMinusIcon")->getHeight(), "rowMinusIcon");
			setSizeBoxImg->AddFrame(RowMinusIcon);
			break;
		}
	}
	UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(false);

	UIText* layerText = new UIText();
	layerText->init("LayerChecker", WINSIZEX - 360, WINSIZEY - 50, 300, 50, "Layer Main", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT, RGB(255, 255, 255));
	UIMANAGER->GetGameFrame()->AddFrame(layerText);
	layerText->SetIsViewing(false);

	UIText* floodFillText = new UIText();
	floodFillText->init("useTwoLayer", 10, WINSIZEY - 50, 300, 50, "Use Two Layer", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	UIMANAGER->GetGameFrame()->AddFrame(floodFillText);
	floodFillText->SetIsViewing(false);

	UIFrame* setSpawnTimeFrame = new UIFrame();
	setSpawnTimeFrame->init("spawnFrame", WINSIZEX / 2 - 250, WINSIZEY / 2 - 150, IMAGEMANAGER->findImage("UIBaseBig")->getWidth(), IMAGEMANAGER->findImage("UIBaseBig")->getHeight(), "UIBaseBig", 0.4, 0.3);
	UIMANAGER->GetGameFrame()->AddFrame(setSpawnTimeFrame);
	setSpawnTimeFrame->SetIsViewing(false);

	UIText* spawnText = new UIText();
	spawnText->init("text", 0, 10, 200, 100, "�����ð� �Է�", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setSpawnTimeFrame->AddFrame(spawnText);

	UIFrame* exitFrame = new UIFrame();
	exitFrame->init("exitFrame", 30, WINSIZEY - 100, IMAGEMANAGER->findImage("ShortcutKey1")->getWidth(), IMAGEMANAGER->findImage("ShortcutKey1")->getHeight(), "ShortcutKey1");
	UIMANAGER->GetGameFrame()->AddFrame(exitFrame);

	UIImage* exitTextImg = new UIImage();
	exitTextImg->init("img", 4, 4, 48, 48, "Exit", false, 0, 0);
	exitFrame->AddFrame(exitTextImg);
}

void mapScene::release()
{
	_mapTool->release();
	_uiBrushTool->release();

	SAFE_DELETE(_mapTool);
	SAFE_DELETE(_uiBrushTool);
	SAFE_DELETE(_targetObject);
}

void mapScene::update()
{
	UIMANAGER->update();
	InputCheck();
	ExitCheck();

	if (_isSettingPage) // �� ������ ���� ��
	{
		SetMapSize();
	}

	else
	{
		AutoSave();
		_mapTool->update();
		_uiBrushTool->update();

		if (!_isSaveLoaderOn && !_isMonsterSettingOn)
		{
			CheckShortCutBtnCollision();
			DoClickByType();
			GetUiBrush();
			RemoveCurrentTile();
			ToolMovePage();
			UpdateFillSquareRange();
			SaveLoadMap();
			CameraMove();
			SaveShortcutKey();
			LoadShortcutKey();
			ShortcutKey();
			SetLayer();
			ShowUseTwoLayer();
			PlaceObject();
			EraseObject();
			SetMonsterPage();
			ZoomInOut();
		}

		if (_isMonsterSettingOn) // ���� ���� �������� ����������
		{
			InMonsterSetPage();
		}

		if (_isSaveLoaderOn) // ���̺� �ε� �������� ����������
		{
			SaveLoadMap();
		}

		CAMERAMANAGER->MovePivot(_pivot.x, _pivot.y);
	}
}

void mapScene::AutoSave()
{
	_autoSaveCount++;

	if (_autoSaveCount % 3000 == 0)
	{
		SYSTEMTIME timer;
		GetLocalTime(&timer);
		string time = "AutoSave/" + to_string(timer.wYear) + to_string(timer.wMonth) + to_string(timer.wDay) + to_string(timer.wHour) + to_string(timer.wMinute) + to_string(timer.wSecond) + "_AutoSave";
		_autoSaveCount = 0;
		_mapTool->SaveData(time);
	}
}

/// <summary>
/// INPUT �ߺ� üũ ������ ���� ���� �Լ�
/// </summary>
void mapScene::InputCheck()
{
	_isLeftClicked = false;
	_isRightClicked = false;
	_isEnterPressed = false;

	if (INPUT->GetKeyDown(VK_LBUTTON)) _isLeftClicked = true;
	if (INPUT->GetKeyDown(VK_RBUTTON)) _isRightClicked = true;
	if (INPUT->GetKeyDown(VK_RETURN)) _isEnterPressed = true;
}

void mapScene::ExitCheck()
{
	if (_isLeftClicked && PtInRect(&UIMANAGER->GetGameFrame()->GetChild("exitFrame")->GetRect(), _ptMouse))
	{
		UIMANAGER->GetGameFrame()->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

/// <summary>
/// ����Ű�� �Է¹޾� ���� ���� �������� ����
/// </summary>
void mapScene::SetMonsterPage()
{
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown(VK_SPACE))
	{
		for (int i = 0; i < _mapTool->GetVObject().size(); i++)
		{
			if (PtInRect(&_mapTool->GetVObject()[i]->_body, CAMERAMANAGER->GetAbsolutePoint(_ptMouse.x, _ptMouse.y)))
			{
				if (DATAMANAGER->GetObjectById(_mapTool->GetVObject()[i]->_id)->GetType() == OBJECTTYPE::OT_MONSTER)
				{
					ShowWindow(_hMonsterSpawnTime, SW_SHOW);
					_isMonsterSettingOn = true;
					_currentMonsterIndex = i;
					SetWindowText(_hMonsterSpawnTime, to_string(_mapTool->GetVObject()[i]->_spawnTime).c_str());
					UIMANAGER->GetGameFrame()->GetChild("spawnFrame")->SetIsViewing(true);
					UIMANAGER->GetGameFrame()->GetChild("spawnFrame")->MoveFrameToXY(_ptMouse.x, _ptMouse.y);
					SetWindowPos(_hMonsterSpawnTime, _hMonsterSpawnTime, _ptMouse.x + 60, _ptMouse.y + 50, 80, 25, SWP_NOZORDER);
					return;
				}
			}
		}
	}
}

/// <summary>
/// ���� ���� �������� �������� �� �Է��� �޵��� �Ѵ�. 
/// </summary>
void mapScene::InMonsterSetPage()
{
	if (_isMonsterSettingOn)
	{
		if (_isEnterPressed)
		{
			GetWindowText(_hMonsterSpawnTime, _spawnTime, 128);
			_mapTool->GetVObject()[_currentMonsterIndex]->_spawnTime = atoi(_spawnTime);
			ShowWindow(_hMonsterSpawnTime, SW_HIDE);
			_isMonsterSettingOn = false;
			UIMANAGER->GetGameFrame()->GetChild("spawnFrame")->SetIsViewing(false);
		}

		if (INPUT->GetKeyDown(VK_TAB))
		{
			ShowWindow(_hMonsterSpawnTime, SW_HIDE);
			_isMonsterSettingOn = false;
			UIMANAGER->GetGameFrame()->GetChild("spawnFrame")->SetIsViewing(false);
		}
	}
}

/// <summary>
/// Ŭ���� ���� ������Ʈ�� ��ġ�Ѵ�.
/// </summary>
void mapScene::PlaceObject()
{
	if (_targetObject != nullptr && _isLeftClicked)
	{
		if (!PtInRect(&UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame")->GetRect(), _ptMouse)
			&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetRect(), _ptMouse)
			&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetRect(), _ptMouse)
			&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("gridBtn")->GetRect(), _ptMouse)
			&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("objBtn")->GetRect(), _ptMouse)
			) // UI���� �浹 üũ
		{
			int absPtX = CAMERAMANAGER->GetAbsoluteX(_ptMouse.x);
			int absPtY = CAMERAMANAGER->GetAbsoluteY(_ptMouse.y);

			// �׸��� ���� �ȿ��� ��ġ�ǵ���
			if (absPtX >= 0 && absPtY >= 0 && absPtY < _mapTool->GetGrid().size() * _mapTool->getZoomHeight() && absPtX < _mapTool->GetGrid()[0].size() * _mapTool->getZoomWidth())
			{
				Grid* grid = _mapTool->mouseCollisionCheck();

				MapObject* obj = new MapObject(*_targetObject); // ���� �����Ͽ� ���Ӱ� �ּ� �Ҵ�

				obj->_x = absPtX;
				obj->_y = absPtY;
				obj->_initX = absPtX / _mapTool->getZoomWidth() * 48;
				obj->_initY = absPtY / _mapTool->getZoomHeight() * 48;
				obj->_alpha = 255;
				obj->_mapTool = _mapTool;
				_mapTool->GetVObject().push_back(obj);
			}
		}
	}
}

/// <summary>
/// ��Ŭ���� ���� ������Ʈ�� �����.
/// </summary>
void mapScene::EraseObject()
{
	for (int i = 0; i < _mapTool->GetVObject().size(); i++)
	{
		if (_isRightClicked)
		{
			if (PtInRect(&_mapTool->GetVObject()[i]->_body, CAMERAMANAGER->GetAbsolutePoint(_ptMouse.x, _ptMouse.y)))
			{
				_mapTool->GetVObject().erase(_mapTool->GetVObject().begin() + i);
				break;
			}
		}
	}
}

/// <summary>
/// ����� �޴� ��ư���� �浹�� �˻��� ����� �۵���Ų��.
/// </summary>
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
					_brushType = BRUSHTYPE::BT_PAINT;
					_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[1]);
					break;
				case 3:
					_brushType = BRUSHTYPE::BT_ERASE;
					_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[3]);
					break;
				case 4:
					FillAll(); break;
				case 5:
					_brushType = BRUSHTYPE::BT_FILLRECT;
					_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[2]);
					break;
				case 6:
					_brushType = BRUSHTYPE::BT_FLOODFILL;
					_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[2]);
					break;
				case 7:
					SwitchSizeFrame(); break;
				case 8:
					Undo(); break;
				}
			}
		}

		if (_isSizeAdjustOpened == true)
		{
			UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame");

			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&frame->GetChild("shortSizeBox" + to_string(i))->GetRect(), _ptMouse))
				{
					switch (i)
					{
					case 0:	AddMapLine(0); break;
					case 1: AddMapLine(1); break;
					case 2:	AddMapLine(2); break;
					case 3:	AddMapLine(3); break;
					}
				}
			}
			return;
		}
	}
}

/// <summary>
/// ���� �귯�� Ÿ�Կ� ���� ��ȣ�ۿ��� �ǽ��Ѵ�.
/// </summary>
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
		case BT_PAINT:
			if (_targetImage) PaintSaver();
			break;
		case BT_ERASE:
			EraseSaver();
			break;
		case BT_PIPETTE:
			Pipette();
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

/// <summary>
/// ����Ʈ ���� ������ҿ� �۾� ���̹�
/// </summary>
void mapScene::PaintSaver()
{
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid)
	{
		_mapTool->EveSaveData();
	}
}

/// <summary>
/// ���� ���� ������ҿ� �۾� ���̹� 
/// </summary>
void mapScene::EraseSaver()
{
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid)
	{
		_mapTool->EveSaveData();
	}
}

/// <summary>
/// �ش� ���콺 �����Ͱ� ��ġ�� �κ��� ĥ�Ѵ�
/// </summary>
void mapScene::Paint()
{
	Grid* grid = _mapTool->mouseCollisionCheck(1);

	if (grid)
	{
		if (_targetImage != nullptr)
		{
			if (_mapTool->getIsLayer() == true)
				grid->_img = _targetImage;
			else
				grid->_img2 = _targetImage;
		}
	}
}

/// <summary>
/// ���콺 ������ ���� Ÿ���� �����
/// </summary>
void mapScene::RemovePaint()
{
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid)
	{
		if (_mapTool->getIsLayer() == true) // ���� ���̾� 1�� �����ߴٸ�
			grid->_img = nullptr;
		else // ���̾� 2�� �����ߴٸ�
			grid->_img2 = nullptr;
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
			_mapTool->EveSaveData();
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
						_mapTool->GetGrid()[i][j]->_alpha = 70;
					}
				}
			}
		}
	}
}

/// <summary>
/// ù��° �簢 ���� ����Ʈ ������ �̷��� ���� �̸����� ����
/// </summary>
void mapScene::UpdateFillSquareRange()
{
	if (_isFillClicked)
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid != nullptr) _mapTool->PreviewGridRange(_clickedPointOne.x, _clickedPointOne.y, grid->_xIndex, grid->_yIndex, 150);
	}
}

/// <summary>
/// �ֺ��� �˻��Ͽ� ���� Ÿ�ϸ� ĥ�ϵ��� �Ѵ�
/// </summary>
void mapScene::FloodFill()
{
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid && _targetImage != nullptr)
	{
		_mapTool->EveSaveData();
		if (_mapTool->getIsLayer())
			_mapTool->FloodFill(grid->_img, grid->_xIndex, grid->_yIndex);
		else
			_mapTool->FloodFill(grid->_img2, grid->_xIndex, grid->_yIndex);
	}
}

/// <summary>
/// ��� Ÿ���� ä�쵵�� �Ѵ�
/// </summary>
void mapScene::FillAll()
{
	_mapTool->EveSaveData();
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
/// �ʱ� �� ������ ���ϴ� �Լ�
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
		UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->SetIsViewing(true);
		UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame")->SetIsViewing(true);
		UIMANAGER->GetGameFrame()->GetChild("LayerChecker")->SetIsViewing(true);
		UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(false);
	}

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

/// <summary>
/// ���̺� â�� ON/OFF
/// </summary>
void mapScene::CallSaveEditor()
{
	if (!_isSaveLoaderOn || _isLoad)
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(true);
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->GetChild("SaveLoader"))->SetText("SAVE");
		_isSaveLoaderOn = true;
		ShowWindow(_hEdit, SW_SHOW);
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(false);
		_isSaveLoaderOn = false;
		ShowWindow(_hEdit, SW_HIDE);
	}
	_isLoad = false;
}

/// <summary>
/// �ε� â�� ON/OFF
/// </summary>
void mapScene::CallLoadEditor()
{
	if (!_isSaveLoaderOn || !_isLoad)
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(true);
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->GetChild("SaveLoader"))->SetText("LOAD");
		_isSaveLoaderOn = true;
		ShowWindow(_hEdit, SW_SHOW);
	}

	else
	{
		UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(false);
		_isSaveLoaderOn = false;
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
		_mapTool->EveSaveData();
		_mapTool->MapLineAddCol();
	}

	if (type == 1)
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineAddRow();
	}

	if (type == 2)
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineRemoveCol();
	}

	if (type == 3)
	{
		_mapTool->EveSaveData();
		_mapTool->MapLineRemoveRow();
	}
}

/// <summary>
/// ������� �۵�
/// </summary>
void mapScene::Undo()
{
	_mapTool->EveLoadData();
}

/// <summary>
/// Ű�� �Է¹޾� ī�޶� �����δ�.
/// </summary>
void mapScene::CameraMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		_pivot.x -= 30 * (_mapTool->getZoomWidth() / 48);
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		_pivot.x += 30 * (_mapTool->getZoomWidth() / 48);
	}
	if (INPUT->GetKey(VK_UP))
	{
		_pivot.y -= 30 * (_mapTool->getZoomWidth() / 48);
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		_pivot.y += 30 * (_mapTool->getZoomWidth() / 48);
	}
}

/// <summary>
/// ���� �������� �Է��� �޾� ���̺� �� �ε带 �ǽ��Ѵ�.
/// </summary>
void mapScene::SaveLoadMap()
{
	if (_isSaveLoaderOn)
	{
		if (_isEnterPressed)
		{
			GetWindowText(_hEdit, _fileName, 128);
			if (!_isLoad)
			{
				_mapTool->SaveData(_fileName);
			}

			else
			{
				_mapTool->EveSaveData();
				_mapTool->LoadData(_fileName);
			}

			_isSaveLoaderOn = false;
			ShowWindow(_hEdit, SW_HIDE);
			UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(false);
		}

		if (INPUT->GetKeyDown(VK_TAB))
		{
			_isSaveLoaderOn = false;
			ShowWindow(_hEdit, SW_HIDE);
			UIMANAGER->GetGameFrame()->GetChild("saveLoadFrame")->SetIsViewing(false);
		}
	}
}

/// <summary>
/// ��ư �浹�� �˻��� ������ ���� �޴��� ON/OFF�Ѵ�.
/// </summary>
void mapScene::SwitchSizeFrame()
{

	if (!_isSizeAdjustOpened || INPUT->GetKeyDown(VK_LBUTTON))
	{
		UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(true);
		_isSizeAdjustOpened = true;
	}
	else
	{
		UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->SetIsViewing(false);
		_isSizeAdjustOpened = false;
	}
}

/// <summary>
/// �ش� ���콺 �����Ͱ� ��ġ�� ���� Ÿ���� ������.
/// </summary>
void mapScene::Pipette()
{
	Grid* grid = _mapTool->mouseCollisionCheck();
	if (grid)
	{
		if (_mapTool->getIsLayer() == true)
			_targetImage = grid->_img;
		else
			_targetImage = grid->_img2;
	}
}

/// <summary>
/// ����Ű�� ���� ������ Ÿ���� �����.
/// </summary>
void mapScene::RemoveCurrentTile()
{
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown(VK_F3))
	{
		_targetImage = nullptr;
		_targetObject = nullptr;
		_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[0]);
	}
}

/// <summary>
/// �ΰ��� ���̾ ����ϴ��� �����ش�.
/// </summary>
void mapScene::ShowUseTwoLayer()
{
	if (_brushType == BRUSHTYPE::BT_FLOODFILL)
	{
		UIText* text = dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("useTwoLayer"));
		text->SetIsViewing(true);
		if (_mapTool->getUseTwoLayer())
		{
			text->SetText("useTwoLayer");
		}

		else
		{
			text->SetText("useOneLayer");
		}
	}

	else
	{
		UIText* text = dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("useTwoLayer"));
		text->SetIsViewing(false);
	}
}

/// <summary>
/// ����Ű�� ����� �����Ѵ�.
/// </summary>
void mapScene::ShortcutKey()
{
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown(VK_F1))
	{
		CallSaveEditor();
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown(VK_F2))
	{
		CallLoadEditor();
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown(VK_F4)) // FloodFill�� �� ���̾ ��� ����Ұ����� ����
	{
		_mapTool->setUseTwolayer(!_mapTool->getUseTwoLayer());
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('G'))
	{
		AddMapLine(0);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('H'))
	{
		AddMapLine(1);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('B'))
	{
		AddMapLine(2);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('N'))
	{
		AddMapLine(3);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('U'))
	{
		FillAll();
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('Z'))
	{
		Undo();
	}

	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SaveLoadMap();
	}

	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('P'))
	{
		_brushType = BRUSHTYPE::BT_PAINT;
		_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[1]);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('E'))
	{
		_brushType = BRUSHTYPE::BT_ERASE;
		_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[3]);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('A'))
	{
		_brushType = BRUSHTYPE::BT_FILLRECT;
		_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[2]);
	}
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('O'))
	{
		_brushType = BRUSHTYPE::BT_FLOODFILL;
		_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[2]);
	}

	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('I'))
	{
		_brushType = BRUSHTYPE::BT_PIPETTE;
		_cursorImage = IMAGEMANAGER->findImage(_cursorImageStrings[0]);
	}
}

/// <summary>
/// ���ã�� Ÿ���� �����Ѵ�.
/// </summary>
void mapScene::SaveShortcutKey()
{
	for (int i = 1; i < 11; i++)
	{
		if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('0' + i % 10))
		{
			UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame")->GetChild("shortcutBox" + to_string(i - 1))->GetChild("Ig")->SetImage(_targetImage);
		}
	}
}

/// <summary>
/// ���ã�� Ÿ���� �ҷ��´�.
/// </summary>
void mapScene::LoadShortcutKey()
{
	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame");
	for (int i = 1; i < 11; i++)
	{
		if (frame->GetChild("shortcutBox" + to_string(i - 1))->GetChild("Ig")->GetImage() != nullptr)
		{
			if (INPUT->GetKeyDown('0' + i % 10))
			{
				_targetImage = frame->GetChild("shortcutBox" + to_string(i - 1))->GetChild("Ig")->GetImage();
			}
		}
	}
}

/// <summary>
/// ���̾ ����Ī�Ѵ�
/// </summary>
void mapScene::SetLayer()
{
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetKeyDown('L'))
	{
		if (_mapTool->getIsLayer() == false)
		{
			_mapTool->setIsLayer(true);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("LayerChecker"))->SetText("Layer Main");
		}
		else
		{
			_mapTool->setIsLayer(false);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("LayerChecker"))->SetText("Layer Back");
		}
	}
}

/// <summary>
/// ���콺 �ٷ� ���� / �ܾƿ��� �ǽ�
/// </summary>
void mapScene::ZoomInOut()
{
	if (_mouseWheel == 1)
	{
		_mapTool->setZoomHeight(_mapTool->getZoomHeight() + 5);
		_mapTool->setZoomWidth(_mapTool->getZoomWidth() + 5);
		_mapTool->SetMap();
	}
	if (_mouseWheel == -1)
	{
		_mapTool->setZoomHeight(_mapTool->getZoomHeight() - 5);
		_mapTool->setZoomWidth(_mapTool->getZoomWidth() - 5);
		_mapTool->SetMap();
	}
}

/// <summary>
/// UIBrushTool�� ������ ����
/// </summary>
void mapScene::ToolMovePage()
{
	if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("arrowLeft")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		if (_uiBrushTool->GetIsObject() && _uiBrushTool->GetObjPage() > 0)
			_uiBrushTool->SetObjPage(_uiBrushTool->GetObjPage() - 1);

		if (!_uiBrushTool->GetIsObject() && _uiBrushTool->GetGridPage() > 0)
			_uiBrushTool->SetGridPage(_uiBrushTool->GetGridPage() - 1);

		_uiBrushTool->PageViewChange();
	}

	if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("arrowRight")->GetRect(), _ptMouse) && _isLeftClicked)
	{
		if (_uiBrushTool->GetIsObject() && _uiBrushTool->GetObjPage() < _uiBrushTool->GetUiObjectGrid().size() - 1)
			_uiBrushTool->SetObjPage(_uiBrushTool->GetObjPage() + 1);
		if (!_uiBrushTool->GetIsObject() && _uiBrushTool->GetGridPage() < _uiBrushTool->GetUiBrushGrid().size() - 1)
			_uiBrushTool->SetGridPage(_uiBrushTool->GetGridPage() + 1);

		_uiBrushTool->PageViewChange();
	}
}

void mapScene::render()
{
	_mapTool->render();
	_uiBrushTool->render();

	Grid* targetGrid = _mapTool->mouseCollisionCheck();
	if (_targetImage && targetGrid) CAMERAMANAGER->StretchAlphaRender(getMemDC(), _targetImage, targetGrid->_rc.left, targetGrid->_rc.top, _mapTool->getZoomWidth() / 48, _mapTool->getZoomHeight() / 48, 100);
	if (_targetObject)
	{
		if (_targetObject->_image->getMaxFrameX() == 0) _targetObject->_image->stretchAlphaRender(getMemDC(), _ptMouse.x, _ptMouse.y, _mapTool->getZoomWidth() / 48, _mapTool->getZoomHeight() / 48, 100);
		else _targetObject->_image->frameStretchAlphaRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0, _mapTool->getZoomWidth() / 48, _mapTool->getZoomHeight() / 48, 100);
	}
	UIMANAGER->render(getMemDC());

	_cursorImage->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

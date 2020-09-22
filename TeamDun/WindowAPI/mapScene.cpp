#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	UIMANAGER->init();

	// ī�޶� //
	_pivot = POINT{ _widthNum / 2 * 48, _heightNum / 2 * 48 };
	CAMERAMANAGER->init(_pivot.x, _pivot.y, 15000, 15000, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
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

	/*setShortcutKeyFrame->GetChild("shortcutBox0")->GetChild("Ig")->SetImage()*/

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
		GetUiBrush();
		Paint();
		RemovePaint();
		FillAll();
		FillSquareRange();
		FloodFill();
		AddMapLine();
		CallSaveLoadEditor();
		SaveLoadMap();
		Undo();
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

	if (INPUT->GetKeyDown(VK_LBUTTON)) _isLeftClicked = true;
	if (INPUT->GetKeyDown(VK_RBUTTON)) _isRightClicked = true;
}

/// <summary>
/// �ش� ���콺 �����Ͱ� ��ġ�� �κ��� ĥ�Ѵ�
/// </summary>
void mapScene::Paint()
{
	if (_targetImage != nullptr)
	{
		if (_isRightClicked)
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
	if (_targetImage != nullptr && INPUT->GetKeyDown('I'))
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
	if (_isLeftClicked)
	{
		_uiBrushTool->mouseCollisionCheck();
		_uiBrushTool->MenuCollisionCheck();
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

void mapScene::CallSaveLoadEditor()
{
	if (INPUT->GetKeyDown(VK_F1))
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

	if (INPUT->GetKeyDown(VK_F2))
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
/// ������Ҹ� �Ѵ�
/// </summary>
void mapScene::Undo()
{
	if (INPUT->GetKeyDown('R'))
	{
		_mapTool->EveLoadData();
	}
}

void mapScene::render()
{
	_mapTool->render();
	_uiBrushTool->render();

	Grid* targetGrid = _mapTool->mouseCollisionCheck();
	if(targetGrid) _targetImage->alphaRender(getMemDC(), targetGrid->_rc.left, targetGrid->_rc.top, 100);

	UIMANAGER->render(getMemDC());
}

void mapScene::CameraMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		_pivot.x -= 5;
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		_pivot.x += 5;
	}
	if (INPUT->GetKey(VK_UP))
	{
		_pivot.y -= 5;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		_pivot.y += 5;
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
			_mapTool->EveSaveData();
			_mapTool->LoadData(_fileName);
		}
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

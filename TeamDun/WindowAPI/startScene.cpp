#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	//��Ʈ ��ġ �ʱ�ȭ
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 500, 200, 100);
	_rc2 = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 300, 200, 100);
	ShowCursor(false);
	return S_OK;
}

void startScene::release()
{
	
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("����ȭ��");
		}

		if (PtInRect(&_rc2, _ptMouse))
		{
			SCENEMANAGER->loadScene("�ʾ�");
		}
	}
}

void startScene::render()
{
	Rectangle(getMemDC(), _rc);
	Rectangle(getMemDC(), _rc2);

	TextOut(getMemDC(), _rc.left + 80, _rc.top + 50, "START", strlen("START"));
	TextOut(getMemDC(), _rc2.left + 80, _rc2.top + 50, "MAPTOOL", strlen("MAPTOOL"));

	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

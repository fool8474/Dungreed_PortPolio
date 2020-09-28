#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();

	SCENEMANAGER->addScene("����ȭ��", new startScene());
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene());
	SCENEMANAGER->addScene("����ȭ��", new gameScene());
	SCENEMANAGER->addScene("�ʾ�", new mapScene());
	SCENEMANAGER->loadScene("�ε�ȭ��");

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SetBkMode(getMemDC(), TRANSPARENT);
	// ============================================= //
	
	SCENEMANAGER->render();
	// ============================================= //
	this->getBackBuffer()->render(getHDC());
}

#pragma once
#include "gameNode.h"

/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ ������ϸ� �̰��� �߰��Ѵ�*/
#include "loadingScene.h"
#include "mapScene.h"
#include "startScene.h"
#include "gameScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();
};
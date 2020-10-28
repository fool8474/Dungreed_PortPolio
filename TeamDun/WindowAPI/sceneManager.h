#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:	
	mSceneList _mSceneList;			//������ ��(ȭ��)���� ��Ƶ� ��
	gameNode* _currentScene;		//�����

public:
	// �⺻ //
	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
	HRESULT init();
	void release();
	void update();
	void render();

	// �� ����
	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT loadScene(string sceneName);

};


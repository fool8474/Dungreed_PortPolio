#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update(); // ������ ���� ������Ʈ
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render(); // ������ ���� ����
}

/// <summary>
/// �̸��� Scene class�� �޾� �ʿ� �߰��Ѵ�.
/// </summary>
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

/// <summary>
/// �̸��� �޾� �ش� ������ �����Ѵ�.
/// </summary>
HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return E_FAIL;
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_NOTIMPL;
}

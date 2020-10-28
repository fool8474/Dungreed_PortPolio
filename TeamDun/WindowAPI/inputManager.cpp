#include "stdafx.h"
#include "inputManager.h"

HRESULT inputManager::init()
{
	//Ű���� ���� �������� ���� ���·� �ʱ�ȭ
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}
			
	_clickTimer = 0;
	_isOnceClicked = false;
	_isLButtonClicked = false;
	_isRButtonClicked = false;
	_isEscapePressed = false;
	return S_OK;
}

void inputManager::update()
{
	FrameKeyInputChecker();

	if (_isOnceClicked)
	{
		_clickTimer++;
		if (_clickTimer > 30)
		{
			_clickTimer = 0;
			_isOnceClicked = false;
		}
	}
}

/// <summary>
/// �� �������� üũ�ؾ��� ���콺 �� Ű���� �Է��� ������Ʈ�Ѵ�.
/// </summary>
void inputManager::FrameKeyInputChecker()
{
	// �ʱ�ȭ
	_isLButtonClicked = false;
	_isRButtonClicked = false;
	_isLButtonUp = false;
	_isEscapePressed = false;

	// ������Ʈ
	if (GetKeyDown(VK_LBUTTON)) _isLButtonClicked = true;
	if (GetKeyDown(VK_RBUTTON)) _isRButtonClicked = true;
	if (GetKeyDown(VK_ESCAPE)) _isEscapePressed = true;
	if (GetKeyUp(VK_LBUTTON)) _isLButtonUp = true;
	
	if (_mouseWheel == _prevMouseWheel) _mouseWheel = 0; // ���콺 ���� ������ ������ �Էµ��� �ʾҴ� ����
	_prevMouseWheel = _mouseWheel;
}

void inputManager::release()
{
}

/// <summary>
/// Ű�� ��� ������ �ִ��� üũ
/// </summary>
bool inputManager::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

/// <summary>
/// �̹� �����ӿ� Ű�� ������ �����ߴ��� üũ
/// </summary>
bool inputManager::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}

	return false;
}

/// <summary>
/// �̹� �����ӿ� Ű�� �´��� üũ
/// </summary>
bool inputManager::GetKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}

	return false;
}

/// <summary>
/// Ű ���°� �ٲ������ üũ
/// </summary>
bool inputManager::GetToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}

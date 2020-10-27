#pragma once
#include "singletonBase.h"
//=============================================================
//	## input ## �Է¸Ŵ��� (Ű����, ���콺��ư)
//=============================================================

#define KEYMAX 256

class inputManager : public singletonBase <inputManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

	bool _isOnceClicked;
	int	_clickTimer;
	int _prevMouseWheel;

	bool _isLButtonClicked;
	bool _isRButtonClicked;
	bool _isLButtonUp;
	bool _isEscapePressed;

public:
	//�Է¸Ŵ��� �ʱ�ȭ
	HRESULT init();
	//�Է¸Ŵ��� ����
	void update();
	void release();

	//Ű�� ��� ���� �ֳ�?
	bool GetKey(int key);
	//Ű�� �ѹ��� ���ȳ�?
	bool GetKeyDown(int key);
	//Ű�� �ѹ� ���ȴ� �����?
	bool GetKeyUp(int key);
	//���Ű��? (����� ����Ƽ���� �̱���� ����)
	bool GetToggleKey(int key);

	bool GetIsLButtonUp() { return _isLButtonUp; }
	bool GetIsOnceClicked() { return _isOnceClicked; }
	int GetClickTimer() { return _clickTimer; }
	bool GetIsLButtonClicked() { return _isLButtonClicked; }
	bool GetIsRButtonClicked() { return _isRButtonClicked; }
	bool GetIsEscapeKeyPressed() { return _isEscapePressed; }
	void SetIsOnceClicked(bool isOnceClicked) { _isOnceClicked = isOnceClicked; }
	void SetClickTimer(int clickTimer) { _clickTimer = clickTimer; }
	inputManager() {}
	~inputManager() {}
};
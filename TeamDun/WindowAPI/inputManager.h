#pragma once
#include "singletonBase.h"
//=============================================================
//	## input ## �Է¸Ŵ��� (Ű����, ���콺��ư)
//=============================================================

#define KEYMAX 256
class inputManager : public singletonBase <inputManager>
{
private:
	bool	_keyUp[KEYMAX];
	bool	_keyDown[KEYMAX];

	bool	_isOnceClicked;
	int		_clickTimer;
	int		_prevMouseWheel;

	// �̹� �������� INPUT ��� //
	bool	_isLButtonClicked;
	bool	_isRButtonClicked;
	bool	_isLButtonUp;
	bool	_isEscapePressed;

	// ������ Ű üĿ //
	void FrameKeyInputChecker();

public:
	// �⺻ //
	inputManager() {}
	~inputManager() {}
	HRESULT init();
	void update();
	void release();

	// Ű �Է� ���� //
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	bool GetToggleKey(int key);

	// GETSET //
	bool	GetIsLButtonUp()						{ return _isLButtonUp; }
	bool	GetIsOnceClicked()						{ return _isOnceClicked; }
	int		GetClickTimer()							{ return _clickTimer; }
	bool	GetIsLButtonClicked()					{ return _isLButtonClicked; }
	bool	GetIsRButtonClicked()					{ return _isRButtonClicked; }
	bool	GetIsEscapeKeyPressed()					{ return _isEscapePressed; }
	
	void	SetIsOnceClicked(bool isOnceClicked)	{ _isOnceClicked = isOnceClicked; }
	void	SetClickTimer(int clickTimer)			{ _clickTimer = clickTimer; }
};
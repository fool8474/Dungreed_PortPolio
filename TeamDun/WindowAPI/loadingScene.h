#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	Loading*	_loading;

	// ���� ���� //
	progressBar*	_loadingBar;		// �ε���
	int				_currentGauge;		// �ε��� ������ ��
	int				_animationCount;	// �ε��� �̹��� �ִϸ��̼� ���
	int				_animationFrame;	// �ε��� �̹��� ������
	image*			_background;		// ��׶��� �̹���

public:
	HRESULT init();
	void	release();
	void	update();
	void	render();

	void animation();

	void loadingFont();
	void loadingImage();
	void loadingSound();

	// GETSET //
	int getCurrentGauge() { return _currentGauge; }
};


#include "stdafx.h"
#include "UIProgressBar.h"

HRESULT UIProgressBar::init(string name, float x, float y, float sizeX, float sizeY, string imageName, string imageName2)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName, 1, 1);

	_backImg = IMAGEMANAGER->findImage(imageName2);
	_fillPercent = 0;
	_imgFillX = 0;
	return S_OK;
}

void UIProgressBar::render(HDC hdc)
{
	if (_isViewing) // ���̴� �����̸�
	{
		if (_isChild && _useOutsideLimit && _isOutside) {} // �ڽ��̸�, ���������� ����߰� �θ��� ������ �Ѿ��ٸ� �׸��� ����.

		else // �װ� �ƴ϶��
		{
			for (int i = 0; i < _vChildFrames.size(); i++)
			{
				if (_vChildFrames[i]->GetRenderBeforeParent()) // �θ� ���� ���� �����Ǵ� �ڽ��̶��
					_vChildFrames[i]->render(hdc);
			}

			if (_image != nullptr)
			{
				_backImg->render(hdc, _x, _y);
				_image->render(hdc, _x, _y, 0, 0, _imgFillX, _backImg->getHeight()); // �׸���
			}

			if (INPUT->GetKey(VK_F3)) Rectangle(hdc, _interactRect); // P�� ���� ���¶�� �浹 ������ �׸���

			for (int i = 0; i < _vChildFrames.size(); i++) // �ڽ� ���� �׸���
			{
				if (!_vChildFrames[i]->GetRenderBeforeParent()) // �θ� ���� �Ŀ� �����Ǵ� �ڽ��̶��
					_vChildFrames[i]->render(hdc);
			}
		}
	}
}

void UIProgressBar::update()
{
	UIFrame::update();
}

void UIProgressBar::FillCheck(float initX, float fillX)
{
	_fillPercent = fillX / initX;
	_imgFillX = _fillPercent * _backImg->getWidth();
}
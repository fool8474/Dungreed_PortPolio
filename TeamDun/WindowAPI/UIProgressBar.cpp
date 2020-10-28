#include "stdafx.h"
#include "UIProgressBar.h"

HRESULT UIProgressBar::init(string name, float x, float y, float sizeX, float sizeY, string imageName, string backImgName)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName, 1, 1);

	_backImg = IMAGEMANAGER->findImage(backImgName);
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

			if (_backImg != nullptr)
			{
				_backImg->render(hdc, _x, _y);
			}

			if (_image != nullptr)
			{
				_image->render(hdc, _x, _y, 0, 0, _imgFillX, _image->getHeight()); // �׸���
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

/// <summary>
/// Progressbar�� ä������ ������ ���Ѵ�.
/// </summary>
void UIProgressBar::FillCheck(float initX, float fillX)
{
	_fillPercent = fillX / initX; // ������ ���ϰ�
	_imgFillX = _fillPercent * (_backImg == nullptr ? _image->getWidth() : _backImg->getWidth()); // �̹����� ũ�⿡ �԰��Ͽ� ä���� ������ ���Ѵ�.
}


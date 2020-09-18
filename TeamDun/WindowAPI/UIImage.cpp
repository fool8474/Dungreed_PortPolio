#include "stdafx.h"
#include "UIImage.h"

/// <summary>
/// �ʱ�ȭ
/// </summary>
/// <param name="useFrameImage">FrameImage ��� ����</param>
/// <param name="frameX">frame x index</param>
/// <param name="frameY">frame y index</param>
/// <returns></returns>
HRESULT UIImage::init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName);
	
	_useFrameImage = useFrameImage;
	_frameX = frameX;
	_frameY = frameY;
	
	return S_OK;
}

void UIImage::render(HDC hdc)
{
	if (_isViewing)	// ���̴� ����
	{
		if (_isChild && _useOutsideLimit && _isOutside) {} // �ڽ��̰� �θ��� ������ �����ٸ�

		else // �����ϴ� ���̽�
		{
			if (_image != nullptr)
			{
				if (_useFrameImage) // ������ �̹��� ����
				{
					_image->frameRender(hdc, _x, _y, _frameX, _frameY);
				}

				else // �̻���
				{
					_image->render(hdc, _x, _y);
				}
			}

			if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect); // P�� ���� ��ȣ�ۿ� Rect ���

			for (int i = 0; i < _vChildFrames.size(); i++) // �ڽĵ� ����
			{
				_vChildFrames[i]->render(hdc);
			}
		}
	}
}

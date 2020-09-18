#include "stdafx.h"
#include "UIFrame.h"

/// <summary>
/// �ʱ�ȭ 
/// </summary>
/// <param name="name">UI�� �̸�</param>
/// <param name="x">UI�� ��ġ X (�ڽ��̶�� �θ� ���� �����ǥ)</param>
/// <param name="y">UI�� ��ġ Y (�ڽ��̶�� �θ� ���� �����ǥ)</param>
/// <param name="sizeX"UI�� ũ�� X></param>
/// <param name="sizeY">UI�� ũ�� Y</param>
/// <param name="imageName">�̹��� �̸�</param>
/// <returns></returns>
HRESULT UIFrame::init(string name, float x, float y, float sizeX, float sizeY, string imageName)
{
	_name = name;
	_x = x;
	_y = y;
	_sizeX = sizeX;
	_sizeY = sizeY;
	_image = IMAGEMANAGER->findImage(imageName);
	_interactRect = RectMake(_x, _y, _sizeX, _sizeY);
	_parent = nullptr;

	_isSelected = false;
	_selectTimer = 0;
	_moveStartX = 0;
	_moveStartY = 0;
	_useOutsideLimit = false;
	_isMoveToDrag = false;
	SetIntersectRect();

	return S_OK;
}

void UIFrame::update()
{
	MoveFrame();

	for (int i = 0; i < _vChildFrames.size(); i++) // �ڽ� �����ӵ鵵 ��� ������Ʈ ��Ų��.
	{
		_vChildFrames[i]->update();
	}

	CheckIsOutside();
}

/// <summary>
/// UI�� �������� �ȵ����� Toggle�������� ó���Ѵ�.
/// </summary>
void UIFrame::ToggleIsViewing()
{
	_isViewing = !_isViewing;

	for (int i = 0; i < _vChildFrames.size(); i++) // �ڽ� �����ӵ鵵 ��� Viewing �Ӽ��� Toggle��Ų��.
	{
		_vChildFrames[i]->ToggleIsViewing();
	}
}

/// <summary>
/// UI�� �������� �ȵ����� Set�Ѵ�.
/// </summary>
/// <param name="isViewing"></param>
/// <param name="withChild"></param>
void UIFrame::SetIsViewing(bool isViewing, bool withChild)
{
	_isViewing = isViewing;

	if (withChild)
	{
		for (int i = 0; i < _vChildFrames.size(); i++)
		{
			_vChildFrames[i]->SetIsViewing(isViewing, withChild);
		}
	}
}

/// <summary>
/// �� UI�� �ڽ��� �߰��Ѵ�
/// </summary>
/// <param name="frame">�߰��� �ڽ� UI</param>
void UIFrame::AddFrame(UIFrame* frame)
{
	frame->_isChild = true;			
	frame->_isViewing = _isViewing;	// isViewing�� ���Ͻ�Ų�� (�θ� �Ⱥ��̸� �ڽĵ� �Ⱥ��̰�, ���̸� ���̰�)
	frame->_parent = this;

	// �����ǥ (�θ� X Y�� ��������, �ڽ��� X Y�� �����ȴ� ex) �θ� ��ǥ : (100, 200), �ڽ� ��ǥ : (50, 50) -> �ڽ� ��ǥ ���� (150, 250) 
 	frame->SetX(_x + frame->GetX());	// �θ� X + �ڽ� X
	frame->SetY(_y + frame->GetY());	// �θ� Y + �ڽ� Y
	frame->SetIntersectRect();			

	AddChildMap(frame->GetName(), frame);	// ChildMap�� Key : �̸�, Value : �ڽ��� �� �������� �ִ´�.
	_vChildFrames.push_back(frame);			// vector���� �־��ش�.
}
 
/// <summary>
/// UI�� �ڽİ� �Բ� �̵���Ų��
/// </summary>
void UIFrame::MoveFrame()
{
	if (!_isChild && _isViewing && _isMoveToDrag) // ���̴� �����̸� �巡�׷� �̵��ϴ°��� �����ϰ� �̰��� ���� �����϶�
	{
		if (PtInRect(&_interactRect, _ptMouse) && INPUT->GetKey(VK_LBUTTON)) // �����ϰ�
		{
			_selectTimer++;

			if (_selectTimer == 10) // �ð��� 10 ������
			{
				_moveStartX = _ptMouse.x;
				_moveStartY = _ptMouse.y;
				_savedX = _x;
				_savedY = _y;
				_isSelected = true; // �� UI�� �����̵��� �����մϴ�
			}
		}

		if (_isSelected) // �����̵��� ������ UI�� ���ؼ�
		{
			// (���� ���콺 ��ġ - ó���� ���콺 ��ġ) = �󸶳� �̵��ߴ���
			// _saved = ó�� UI�� ��ġ
			int newX = _savedX + (_ptMouse.x - _moveStartX); // ó�� UI�� ��ġ + ���콺 �̵��Ÿ�
			int newY = _savedY + (_ptMouse.y - _moveStartY);

			for (int i = 0; i < _vChildFrames.size(); i++) // �ڽĵ� ���� �̵���Ų��
			{
				MoveFrameChild(newX - _x, newY - _y);
			}

			_x = newX;
			_y = newY;
			_interactRect = RectMake(_x, _y, _sizeX, _sizeY);
		}

		if (!INPUT->GetKey(VK_LBUTTON)) // ���콺�� ����
		{
			_isSelected = false; // ������ ����
			_selectTimer = 0;
		}
	}
}

/// <summary>
/// �θ� ���������� �ڽĵ� �׿� �����Ͽ� ���� �Ÿ���ŭ �̵��ϰ� �Ѵ�
/// </summary>
void UIFrame::MoveFrameChild(float x, float y)
{
	_x += x;
	_y += y;
	_interactRect = RectMake(_x, _y, _sizeX, _sizeY);

	for (int i = 0; i < _vChildFrames.size(); i++) // �ڽ��� �ڽĵ� ���������� �̵��Ѵ�
	{
		_vChildFrames[i]->MoveFrameChild(x, y);
	}
}

/// <summary>
/// �ڽ��� �θ��� ������ �������� �׽�Ʈ
/// </summary>
void UIFrame::CheckIsOutside()
{
	if (_isChild) // �ڽ��̶��
	{
		if (_x < _parent->GetX() || _y < _parent->GetY() ||
			_x + _sizeX > _parent->GetX() + _parent->GetSizeX() ||
			_y + _sizeY > _parent->GetY() + _parent->GetSizeY()) // �ڽ��� ��ġ�� �θ��� ��ġ�� �Ѿ����
		{
			_isOutside = true; // �ܺη� �����ٰ� ����
		}

		else
		{
			_isOutside = false; // ���ο� �����Ѵ� ����
		}
	}
}

void UIFrame::render(HDC hdc)
{
	if (_isViewing) // ���̴� �����̸�
	{
		if (_isChild && _useOutsideLimit && _isOutside) {} // �ڽ��̸�, ���������� ����߰� �θ��� ������ �Ѿ��ٸ� �׸��� ����.

		else // �װ� �ƴ϶��
		{
			if (_image != nullptr) _image->render(hdc, _x, _y); // �׸���
			if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect); // P�� ���� ���¶�� �浹 ������ �׸���

			for (int i = 0; i < _vChildFrames.size(); i++) // �ڽ� ���� �׸���
			{
				_vChildFrames[i]->render(hdc);
			}
		}
	}
}

void UIFrame::release()
{
	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->release();
	}
}

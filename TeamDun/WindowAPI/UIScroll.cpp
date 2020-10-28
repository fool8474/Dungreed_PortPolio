#include "stdafx.h"
#include "UIScroll.h"

/// <summary>
/// �ʱ�ȭ
/// </summary>
HRESULT UIScroll::init(string name, float x, float y, float sizeX, float sizeY, string imageName)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName);

	_target = nullptr;
	_scrollPercent = 0.f;
	_isVertical = true;

	return S_OK;
}

void UIScroll::update()
{
	MoveFrame(); 
	MoveScrollBar();

	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->update();	
	}

	CheckIsOutside();
}

/// <summary>
/// ��ũ�ѹٸ� �̵���Ų��
/// </summary>
void UIScroll::MoveScrollBar()
{
	if (_isVertical) // ���� ���̽�
	{
		if (PtInRect(&_parent->GetRect(), _ptMouse)) // �θ� UI�� ���콺�� ��ģ ���¿���
		{
			float prevY = _y;
			if (_mouseWheel == 1) // ���콺 ���� �ø���
			{
				_y = _y - (_parent->GetSizeY() * 0.03f); // ��ũ���� ��ü �������� 0.03��ŭ �ø���
				if (_y < _parent->GetY())
				{
					_y = _parent->GetY();
				} // ���� ����

				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			else if (_mouseWheel == -1) // ���콺 ���� ������
			{
				_y = _y + (_parent->GetSizeY() * 0.03f); // ��ũ���� ��ü �������� 0.03��ŭ ������
				if (_y + _image->getHeight() > _parent->GetSizeY() + _parent->GetY())
				{
					_y = _parent->GetSizeY() + _parent->GetY() - _image->getHeight();
				} // ���� ����

				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			if (prevY != _y) // ���� ��ũ���� �������ٸ�
			{
				for (int i = 0; i < _vChildFrames.size(); i++)
				{
					MoveFrameChild(0, _y - prevY); // �ڽĵ鵵 �����δ�
				}
			}
		}
	}
	
	else // ���� ���̽�
	{
		if (PtInRect(&_parent->GetRect(), _ptMouse)) // �θ� UI�� ���콺�� ��ģ ���¿���
		{
			float prevX = _x;
			if (_mouseWheel == 1) // ���콺 ���� �ø���
			{
				_x = _x - (_parent->GetSizeX() * 0.03f); // ��ũ���� ��ü �������� 0.03��ŭ �ø���

				if (_x < _parent->GetX())
				{
					_x = _parent->GetX();
				} // ���� ����

				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			else if (_mouseWheel == -1) // ���콺 ���� ������
			{
				_x = _x + (_parent->GetSizeX() * 0.03f); // ��ũ���� ��ü �������� 0.03��ŭ ������
				if (_x + _image->getWidth() > _parent->GetSizeX() + _parent->GetX())
				{
					_x = _parent->GetSizeX() + _parent->GetX() - _image->getWidth();
				} // ���� ����
				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			if (prevX != _x) // ���� ��ũ���� �������ٸ�
			{
				for (int i = 0; i < _vChildFrames.size(); i++)
				{
					MoveFrameChild(_x - prevX, 0); // �ڽĵ鵵 �����δ�
				}
			}
		}
	}
}

/// <summary>
/// ���� ��ũ���� ��ġ�� ���� Ÿ���� �ڽĵ� ���� �����δ�
/// </summary>
void UIScroll::CalculateScrollBarPercent()
{
	if (_isVertical)  // ���� ���̽�
	{
		float _prevScrollPercent = _scrollPercent;
		_scrollPercent = (_y - _parent->GetY()) / (_parent->GetSizeY() - _image->getHeight()); // ���� ���

		float maxY = INT_MIN;
		float minY = INT_MAX;
		for (int i = 0; i < _target->GetVChildFrames().size(); i++)
		{

			if (_target->GetVChildFrames()[i] == this) continue; // ����ó��

			UIFrame* tempFrame = _target->GetVChildFrames()[i];
			if (tempFrame->GetY() > maxY) maxY = tempFrame->GetY(); // ���� �Ʒ� ��ġ�� UI
			if (tempFrame->GetY() < minY) minY = tempFrame->GetY(); // ���� �� ��ġ�� UI
		}

		// maxY - minY = �ڽ� UI�� �� �Ÿ�
		float moveY = _scrollPercent * (maxY - minY) - _prevScrollPercent * (maxY - minY); // ������ ��ũ�� ��ġ�� ���� ��ũ�� ��ġ�� ����ؼ� �󸶸�ŭ target�� �ڽĵ��� �̵����Ѿ� �ϴ��� �����Ѵ�.

		for (int i = 0; i < _target->GetVChildFrames().size() - 1; i++) // ���� -1�� �� �ִ��� ���ȳ� (���� ������ ���� ����)
		{
			if (_target->GetVChildFrames()[i] == this) continue; // ����ó��
			_target->GetVChildFrames()[i]->MoveFrameChild(0, -moveY); // �̵��Ÿ���ŭ �ݴ�������� �ڽĵ��� ������ (��ũ�� ���� -> �ڽ� �ö�)
		}
	}
	
	else // ���� ���̽�
	{
		float _prevScrollPercent = _scrollPercent;
		_scrollPercent = (_x - _parent->GetX()) / (_parent->GetSizeX() - _image->getWidth());

		float maxX = INT_MIN;
		float minX = INT_MAX;
		for (int i = 0; i < _target->GetVChildFrames().size(); i++)
		{
			if (_target->GetVChildFrames()[i] == this) continue;

			UIFrame* tempFrame = _target->GetVChildFrames()[i];
			if (tempFrame->GetX() > maxX) maxX = tempFrame->GetX();
			if (tempFrame->GetX() < minX) minX = tempFrame->GetX();
		}

		float moveX = _scrollPercent * (maxX - minX) - _prevScrollPercent * (maxX - minX);

		for (int i = 0; i < _target->GetVChildFrames().size() - 1; i++)
		{
			if (_target->GetVChildFrames()[i] == this) continue; 
			_target->GetVChildFrames()[i]->MoveFrameChild(-moveX, 0);
		}
	}
}


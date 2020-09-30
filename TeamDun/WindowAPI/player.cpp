#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{

	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1


	_x = 300;
	_y = WINSIZEY/2;
	_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	
	_useImage = 0;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	
	_frameX = 0;
	_frameY = 0;
	_gravity = 0.3f;
	_jumpPower = 7.0f;

	_downJmpTimer = 0;
	return S_OK;
	
}

void Player::update()
{


	_isJump = false;
	if (INPUT->GetKey('A'))
	{
		_isLeft = true;
		_state = PS_MOVE;
		_x -= 5;
		_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('A'))
	{
	
		_state = PS_IDLE;
	}
	if (INPUT->GetKey('D'))
	{
		_isLeft = false;
		_state = PS_MOVE;
		_x += 5;
		_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
	}

	if (INPUT->GetKeyDown(VK_SPACE))
	{
		_isJump = true;
		

	}
	if ( INPUT->GetKey('S') && _isJump)
	{
		_downJump = true;
		_jumpPower = -3;
	}
	if (_isJump && !_downJump)
	{
		_jumpPower = 10;
		_y -= _jumpPower;
		_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	}


	if (_downJump)
	{
		_downJmpTimer++;
		if (_downJmpTimer > 20)
		{
			_downJmpTimer = 0;
			_downJump = false;
		}
	}
	//////////////////////////// �ȼ��浹 //////////////////////////////
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	bool isCollide = false; // �浹 �ߴ��� ����
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;
	

	COLORREF colorRightBottom1;
	COLORREF colorRightBottom2;

	for (int i = _probeBottom - 15; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _x+ IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth()/2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0)) // ������ �ȼ��浹�� ���� ��Ҵ�
		{
			isCollide = true; // �浹������ �긦 ON
			_jumpPower = -2;	  // ���������� �ڿ������� �������� �ϱ����� �����Ŀ� �ʱ�ȭ

			//if (i == _probeBottom - 15) // �� ������ �浹���� ���� ���� ����
			//{
			//	if (_isLeft) _x += 5;
			//	else _x -= 5;
			//}s 
			_y = i - IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();// �ö󰣴�
			
			break;
		}
	
		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false ) // �Ķ��� �ȼ��浹�� ���� ��Ұ� �������� ���¶��
		{
			isCollide = true;		// �浹������ �긦 ON
			_jumpPower = -2;		// ���������� �ڿ������� �������� �ϱ����� �����Ŀ� �ʱ�ȭ
			
			_y = i - IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();// �ö󰣴�
			
			break;
		}
	}

	for (int i = _y+15 ;i > _y -5; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _x +6, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);	

		
		if ((r == 255 && g == 0 && b == 0)) // ������ �ȼ��浹�� ���� ��Ҵ�
		{
			_jumpPower = -2;
			_y = i+5 ;

			break;
		}
	}
	for (int i = _y + 15; i > _y - 4; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth()-6, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if ((r == 255 && g == 0 && b == 0)) // ������ �ȼ��浹�� ���� ��Ҵ�
		{
			_jumpPower = -2;
			_y = i + 5;

			break;
		}
	}
	if (!isCollide) //�浹������ �ʴٸ�
	{
		_y -= _jumpPower;			//�߷�����
		_jumpPower -= _gravity;

		_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}

	for (int i = _x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 15; i < _x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(),i, _probeBottom-2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ( (r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;
			
			if (_RightCollision1 &&_RightCollision2)
			{
				_x = i - IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth();

			}
			break;
		}
		
	}
	for (int i = _x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() - 15; i < _x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;
			_x = i - IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth();

		
			break;
		}
	}

	//���ʾƷ�
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), i, _probeBottom -2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision1 = true;

			if (_leftCollision1 &&_leftCollision2)
			{
				_x = i - IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth();

			}

			break;
		}
	}
	//������
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), i,_y+2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision2 = true;
			_x = i;

			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////
	Animation();
}

void Player::release()
{
}

void Player::render(HDC hdc)
{
	switch (_state)
	{
	case PS_IDLE:
		CAMERAMANAGER->FrameRender(hdc,IMAGEMANAGER->findImage("baseCharIdle"), _x, _y,_frameX,_frameY);
		break;
	case PS_JUMP:
		CAMERAMANAGER->FrameRender(hdc, IMAGEMANAGER->findImage("baseCharIdle"), _x, _y, _frameX, _frameY);
		break;
	case PS_MOVE:
		CAMERAMANAGER->FrameRender(hdc,IMAGEMANAGER->findImage("baseCharRun"), _x, _y,_frameX,_frameY);
		break;
	case PS_DIE:
		break;
	default:
		break;
	}
	//CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
}

void Player::Animation()
{
	switch (_state)
	{
	case PS_IDLE:
		_useImage = 0;

		break;
	case PS_JUMP:
		_useImage = 1;
		break;
	case PS_MOVE:
		_useImage = 1;
		
		break;
	case PS_DIE:
		break;
	default:
		break;
	}

	if (_isLeft)
	{
		_frameTimer++;
		_frameY = 1;
		if (_frameTimer > 5)
		{
			_frameTimer = 0;
			_frameX--;

			if (_frameX < 0)
			{
				_frameX = _vImages[_useImage]->getMaxFrameX();  //�����
			}
		}
	}
	else
	{
		_frameTimer++;
		_frameY = 0;
		if (_frameTimer > 5)
		{
			_frameTimer = 0;
			_frameX++;
			if (_frameX > _vImages[_useImage]->getMaxFrameX())
			{
				_frameX = 0;
			}
		}

	}
	
}

void Player::Move()
{
}


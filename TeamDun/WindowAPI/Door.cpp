#include "stdafx.h"
#include "Door.h"

HRESULT Door::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	_isActivated = false;
	_isSpawning = false;
	return S_OK;
}

void Door::update()
{
	Object::update();
	Animation();
}

void Door::release()
{
	Object::release();
}

void Door::render(HDC hdc)
{
	if (_isSpawning) CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
}

void Door::Animation()
{
	if (_isActivated) // Ȱ��ȭ�� ����
	{
		_frameTimer++;
		if (_frameTimer > 5)
		{
			_frameTimer = 0;
			_frameX++;
			if (_frameX > 14) _frameX = 7;
		}
	}

	else
	{
		if (_isSpawning) 
		{
			_frameTimer++;
			if (_frameTimer > 5)
			{
				_frameX++;
				if (_frameX <= 6) // ��ȯ �� -> ��ȯ �Ϸ�
				{
					if (_frameX == 6)
					{
						_isActivated = true;
					}
				}

				else // ��ȯ �Ϸ� -> �����
				{
					if (_frameX >= _vImages[_useImage]->getMaxFrameX())
					{
						_isActivated = false;
						_isSpawning = false;
						_frameX = 0;
						_belongMap->MakeNearTileCollision(this, false);
					}
				}

				_frameTimer = 0;
			}
		}
	}
}

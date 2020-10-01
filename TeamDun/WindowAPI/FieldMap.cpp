#include "stdafx.h"
#include "FieldMap.h"

HRESULT FieldMap::init(string fileName)
{
	_fileName = fileName;
	_spawnTimer = 0;
	LoadMap();
	return S_OK;
}

/// <summary>
/// ������ ���� �ε��Ͽ� Ÿ�ϰ� ������Ʈ�� ��ġ�سִ´�.
/// </summary>
void FieldMap::LoadMap()
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + ".mapData");
	vector<vector<string>> stringData2 = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + "2.mapData");

	if (stringData.size() == 0 || stringData2.size() == 0)
	{
		cout << _fileName << " load Failed" << endl;
		return;
	} // �ش� �� �ҷ����⿡ ������ ���

	_vMapData.clear();

	for (int i = 0; i < stringData.size(); i++)
	{
		vector<Tile*> tileLine;
		for (int j = 0; j < stringData[i].size(); j++)
		{
			Tile* tile = new Tile();
			if (stringData[i][j] == "-1") tile->_img = nullptr;
			else
			{
				tile->_img = IMAGEMANAGER->findImage(stringData[i][j]);
				RECT rc;
				rc = RectMake(10 + j * 5, 10 + i * 5, 5, 5); // ��ĭ�� 5�ȼ��̱� ������ �ø�������� �̹����� ���� �ٲ���մϴ�
				_vMiniRc.push_back(rc);
			}
			if (stringData2[i][j] == "-1") tile->_img2 = nullptr;
			else tile->_img2 = IMAGEMANAGER->findImage(stringData2[i][j]);
			tile->_x = j * 48;
			tile->_y = i * 48;

			if (stringData[i][j] == "-1") tile->_collisionImage = nullptr;	// Ÿ���� ���ٸ� �浹ü�� ����.
			else tile->_collisionImage = DATAMANAGER->GetGridDataByName(stringData[i][j])->_colImage; // �浹ü�� ������ �̹����� �ִ´�.

			tileLine.push_back(tile);
		}
		_vMapData.push_back(tileLine);
	}

	_vObjs.clear();
	vector<vector<string>> objData = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + "_Objs.mapData");
	for (int i = 0; i < objData.size(); i++)
	{
		Object* obj;
		// BEFORE OBJECT LOAD
		switch (stoi(objData[i][0]))
		{
		case 1500:// ū �ذ�
			obj = new BigWhiteSkel(*dynamic_cast<BigWhiteSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1501:// �̳�Ÿ�츣��
			obj = new Minotaurs(*dynamic_cast<Minotaurs*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 701: // ���
			obj = new LittleGhost(*dynamic_cast<LittleGhost*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 702: // ���� ����
			obj = new RedBat(*dynamic_cast<RedBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 2000: // ���� ����
			obj = new Belial(*dynamic_cast<Belial*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 514: // �� ����
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 515: // �� ������
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 516: // �� ����
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 517: // �� �Ʒ���
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 2500: // ���� ������
			obj = new MonsterSpawner(*dynamic_cast<MonsterSpawner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<MonsterSpawner*>(obj)->SetBelongMap(this);
			break;

		default:
			obj = new Object(*DATAMANAGER->GetObjectById(stoi(objData[i][0])));
			break;
		}
		obj->SetX(stof(objData[i][1]) * 48);
		obj->SetY(stof(objData[i][2]) * 48);
		obj->SetSpawnTime(stoi(objData[i][3]));


		// AFTER OBJECT LOAD
		switch (stoi(objData[i][0]))
		{
		case 514: case 515: case 516: case 517: // �� Case
			MakeDoor(dynamic_cast<Door*>(obj));
			break;
		}

		_vObjs.push_back(obj);
	}
}

/// <summary>
/// ���� ����� �ش� ���� �ֺ� Ÿ���� ó���Ѵ� 
/// </summary>
void FieldMap::MakeDoor(Door* door)
{
	int x = (door->GetX() + door->GetImage(0)->getWidth() / 2) / 48;	// ���� ���� X
	int y = (door->GetY() + door->GetImage(0)->getHeight() / 2) / 48;	// ���� ���� Y

	int pos[4] = { 0,0,0,0 };
	switch (door->GetDirection()) // ���⿡ ���� ������ Ÿ���� ������ �޶�����.
	{
	case DIRECTION::DIR_LEFT:	pos[0] = -3;  pos[1] = 0, pos[2] = -2, pos[3] = 2; break;
	case DIRECTION::DIR_RIGHT:	pos[0] = 0;  pos[1] = 3, pos[2] = -2, pos[3] = 2; break;
	case DIRECTION::DIR_UP:		pos[0] = -2;  pos[1] = 1, pos[2] = -2, pos[3] = 0; break;
	case DIRECTION::DIR_DOWN:	pos[0] = -2;  pos[1] = 1, pos[2] = 0, pos[3] = 2; break;
	}

	for (int i = y + pos[2]; i <= y + pos[3]; i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = x + pos[0]; j <= x + pos[1]; j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;

			// �ֺ� Ÿ���� ����
			_vMapData[i][j]->_img = nullptr;
			_vMapData[i][j]->_img2 = DATAMANAGER->GetGridDataByName("Stage1_Tile43")->_image; 
			_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll");
			
			// ���� ���⿡ ���� �ֺ� Ÿ�� ����
			switch (door->GetDirection())
			{
			case DIRECTION::DIR_LEFT: case DIRECTION::DIR_RIGHT:
				if (i == y + pos[2] && i-1 >= 0)
				{
					_vMapData[i-1][j]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile19")->_image;
					_vMapData[i-1][j]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile19")->_colImage;
				}

				if (i == y + pos[3] && i + 1 < _vMapData.size())
				{
					_vMapData[i+1][j]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile1")->_image;
					_vMapData[i+1][j]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile1")->_colImage;
				}
				break;

			case DIRECTION::DIR_UP:
				if (j == x + pos[0] && j - 1 >= 0)
				{
					_vMapData[i][j - 1]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile5")->_image;
					_vMapData[i][j - 1]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile5")->_colImage;
				}

				if (j == x + pos[1] && j + 1 <= _vMapData[i].size() - 1)
				{
					_vMapData[i][j + 1]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile3")->_image;
					_vMapData[i][j + 1]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile3")->_colImage;
				}

				if (i == y + pos[2] && i - 1 >= 0)
				{
					_vMapData[i - 1][j]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile19")->_image;
					_vMapData[i - 1][j]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile19")->_colImage;
				}
				break;

			case DIRECTION:: DIR_DOWN:
				if (j == x + pos[0] && j - 1 >= 0)
				{
					_vMapData[i][j-1]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile5")->_image;
					_vMapData[i][j-1]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile5")->_colImage;
				}

				if (j == x + pos[1] && j + 1 <= _vMapData[i].size() - 1)
				{
					_vMapData[i][j + 1]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile3")->_image;
					_vMapData[i][j + 1]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile3")->_colImage;
				}

				if (i == y + pos[3] && i + 1 < _vMapData.size())
				{
					_vMapData[i + 1][j]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile1")->_image;
					_vMapData[i + 1][j]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile1")->_colImage;
				}
				break;
			}
		}
	}


}

/// <summary>
/// �ȼ� �ݸ��� �̹����� �׷� �ȼ��浹�� ���� ����� �Լ�
/// </summary>
void FieldMap::PixelCollisionMapGenerate()
{
	Rectangle(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), -10, -10, 10000, 10000); // �ȼ��浹 �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_collisionImage != nullptr)
			{
				_vMapData[i][j]->_collisionImage->render(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y); // �浹�� ��濡 �浹�� Ÿ�� ��ġ
			}
		}
	}
}

/// <summary>
/// �� ��ü Ÿ�� �̹����� �׷� ���� ����� �Լ�
/// </summary>
void FieldMap::GridMapGenerate()
{
	Rectangle(IMAGEMANAGER->findImage("Layer1MapIg")->getMemDC(), -10, -10, 10000, 10000); // �ȼ��浹 �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�
	Rectangle(IMAGEMANAGER->findImage("Layer2MapIg")->getMemDC(), -10, -10, 10000, 10000); // �ȼ��浹 �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�
	Rectangle(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), -10, -10, 10000, 10000); // �̴ϸ� �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_img != nullptr)
			{
				_vMapData[i][j]->_img->render(IMAGEMANAGER->findImage("Layer1MapIg")->getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y); // �浹�� ��濡 �浹�� Ÿ�� ��ġ
			}

			if (_vMapData[i][j]->_img2 != nullptr)
			{
				_vMapData[i][j]->_img2->render(IMAGEMANAGER->findImage("Layer2MapIg")->getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y); // �浹�� ��濡 �浹�� Ÿ�� ��ġ
			}
		}
	}
	for (int i = 0; i < _vMiniRc.size(); i++)
	{
		
		IMAGEMANAGER->findImage("MiniMapPixel")->render(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), _vMiniRc[i].left, _vMiniRc[i].top);
	} // �̴ϸ� ����
}

void FieldMap::update()
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->update();
	}

	SpawnMonsters();
	EFFECTMANAGER->update();
}

void FieldMap::release()
{
}

void FieldMap::render(HDC hdc)
{
	/*
	for (int i = ((CAMERAMANAGER->GetPivotY() - (WINSIZEY / 2)) / 48) - 5; i < ((CAMERAMANAGER->GetPivotY() + (WINSIZEY)) / 48) +5; i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = ((CAMERAMANAGER->GetPivotX() - (WINSIZEX / 2)) / 48) - 5; j < ((CAMERAMANAGER->GetPivotX() + (WINSIZEX)) / 48) + 5; j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;
			if (_vMapData[i][j]->_img2) CAMERAMANAGER->Render(hdc, _vMapData[i][j]->_img2, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
			if (_vMapData[i][j]->_img) CAMERAMANAGER->Render(hdc, _vMapData[i][j]->_img, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
		}
	} // Ÿ�� ����, ���� ������ŭ�� �������ش�.
	*/

	CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("Layer2MapIg"), 0, 0);
	CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("Layer1MapIg"), 0, 0);
	
	IMAGEMANAGER->findImage("MiniMapGroundIg")->render(hdc, 0, 0);
	if (INPUT->GetKey(VK_F1))
	{
		CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("PixelMapIg"), 0, 0);
	} // �ȼ��浹 ����

	/*
	for (int i = 0; i < _vMiniRc.size(); i++)
	{
		IMAGEMANAGER->findImage("MiniMapPixel")->render(hdc, _vMiniRc[i].left, _vMiniRc[i].top);
	} // �̴ϸ� ����
	*/

	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->render(hdc);
	} // ������Ʈ ����
	

	ENTITYMANAGER->render(hdc);
	EFFECTMANAGER->render(hdc);
	// �÷��̾� �� �Ҹ� �� ����
}

/// <summary>
/// ���� Ÿ���� ������Ʈ���� �ð��� ���߾� �����Ѵ�.
/// </summary>
void FieldMap::SpawnMonsters()
{
	if (_isSpawning)
	{
		_spawnTimer++;
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(_vObjs[i]);
				
				if (!enemy->GetIsSpawned() && enemy->GetSpawnTime() <= _spawnTimer)
				{
					enemy->SpawnEnemy();
				}
			}
		}
	}
}
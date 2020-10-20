#include "stdafx.h"
#include "FieldMap.h"
#include "Portal.h"
#include "PixieSpawner.h"
#include "TreasureSpawner.h"

HRESULT FieldMap::init(string fileName)
{
	_fileName = fileName;
	_spawnTimer = 0;
	_visited = false;
	_portal = nullptr;

	_nextMapIndex[0] = -1;
	_nextMapIndex[1] = -1;
	_nextMapIndex[2] = -1;
	_nextMapIndex[3] = -1;
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
		return;
	} // �ش� �� �ҷ����⿡ ������ ���

	_vMapData.clear();
	_backImageEtc = nullptr;
	_backImageMain = nullptr;
	_townBackgroundImg = nullptr;
	_townMountainImg = nullptr;
	_townGrassImg = nullptr;
	
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
				if (_fileName == "stage0_town")
					rc = RectMake(1000 + j * 3, 10 + i * 3, 3, 3); // ��ĭ�� 5�ȼ��̱� ������ �ø�������� �̹����� ���� �ٲ���մϴ�
				else
				{
					rc = RectMake(1000 + j * 5, 10 + i * 5, 5, 5); // ��ĭ�� 5�ȼ��̱� ������ �ø�������� �̹����� ���� �ٲ���մϴ�
				}
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

	if (_stage == 1 || _stage == 2)
	{
		_backImageEtc = IMAGEMANAGER->findImage("BackFloorBack1");
		_backImageMain = IMAGEMANAGER->findImage("SubBGStage1");
	}
	if (_stage == 0)
	{
		_townBackgroundImg = IMAGEMANAGER->findImage("Sky_Day");
		_townMountainImg = IMAGEMANAGER->findImage("TownBG_Day");
		_townGrassImg = IMAGEMANAGER->findImage("TownLayer_Day");
		_backImageEtc = IMAGEMANAGER->findImage("BackFloorBack1");
	}
}

void FieldMap::LoadObject()
{
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

		case 702: // ���� ����
			obj = new RedBat(*dynamic_cast<RedBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 704: // ���� ����
			obj = new IceBat(*dynamic_cast<IceBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 705: // �� ����
			obj = new FireBat(*dynamic_cast<FireBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 2000: // ������
			obj = new Belial(*dynamic_cast<Belial*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1504: // ��ť����
			obj = new Lilith(*dynamic_cast<Lilith*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1505: // ���� ����
			obj = new LittleGhost(*dynamic_cast<LittleGhost*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1506:// �ذ� ������
			obj = new SkelDog(*dynamic_cast<SkelDog*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1507:// Į �ذ�
			obj = new SwordSkel(*dynamic_cast<SwordSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1508:// Ȱ �ذ�
			obj = new BowSkel(*dynamic_cast<BowSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;

		case 1502: // ���
			obj = new Banshee(*dynamic_cast<Banshee*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1509: //���� ū����
			obj = new RedGiantBat(*dynamic_cast<RedGiantBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1510: //���� ū����
			obj = new PurpleGiantBat(*dynamic_cast<PurpleGiantBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
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
			break;
		case 2502: // �Ƚ� ������
			obj = new PixieSpawner(*dynamic_cast<PixieSpawner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			_pixieSpawner = dynamic_cast<PixieSpawner*>(obj);
			break;
		case 2503: // ���� ������
			obj = new TreasureSpawner(*dynamic_cast<TreasureSpawner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			_treasureSpawner = dynamic_cast<TreasureSpawner*>(obj);
			break;
		case 10: // ����
			obj = new Shop(*dynamic_cast<Shop*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Shop*>(obj)->initSecond();
			dynamic_cast<Shop*>(obj)->SetShopItem();
			dynamic_cast<Shop*>(obj)->ReNewUI();
			break;
		case 12 : // �� �� �Ĵ� ���� ����
			obj = new Restaurant(*dynamic_cast<Restaurant*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Restaurant*>(obj)->initSecond();
			dynamic_cast<Restaurant*>(obj)->SetRestaurantFood();
			dynamic_cast<Restaurant*>(obj)->ReNewUI();
			break;
		case 0: // ��Ż
			obj = new Portal(*dynamic_cast<Portal*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Portal*>(obj)->initSecond();
			_portal = dynamic_cast<Portal*>(obj);
			break;

		case 2: // ��������
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 3: // �������
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 4: // ȸ������
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 5: // ��������
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 6: // �ݻ�����
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 7: // ���� �������� ��
			obj = new StageDoor(*dynamic_cast<StageDoor*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<StageDoor*>(obj)->initSecond();
			break;
		case 100: // ū �ڽ�
			obj = new Box(*dynamic_cast<Box*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 101: // ���� �ڽ�
			obj = new Box(*dynamic_cast<Box*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 102: // ��ũ��
			obj = new Box(*dynamic_cast<Box*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		default:
			obj = new Object(*DATAMANAGER->GetObjectById(stoi(objData[i][0])));
			break;
		}
		obj->SetX(stof(objData[i][1]) * 48);
		obj->SetY(stof(objData[i][2]) * 48);
		obj->SetSpawnTime(stoi(objData[i][3]));
		obj->SetBelongMap(this);
		obj->SetBodyPos();

		bool CheckRollBack = false;
		// AFTER OBJECT LOAD
		switch (stoi(objData[i][0]))
		{
		case 514: // �� ����
			if (_nextMapIndex[DIRECTION::DIR_LEFT] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 515: // �� ������
			if (_nextMapIndex[DIRECTION::DIR_RIGHT] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 516: // �� ����
			if (_nextMapIndex[DIRECTION::DIR_UP] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 517: // �� �Ʒ���
			if (_nextMapIndex[DIRECTION::DIR_DOWN] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 2000: // ������
			dynamic_cast<Belial*>(obj)->SetAfterSpawn();
			break;
		}

		_vObjs.push_back(obj);
		if (CheckRollBack)
		{
			_vObjs.erase(_vObjs.end() - 1);
		}
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
			switch (door->GetDirection()) // ���⿡ ���� �浹�ȼ� ����
			{
			case DIRECTION::DIR_LEFT:
				_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll");
				break;
			case DIRECTION::DIR_RIGHT:
				_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll2");
				break;
			case DIRECTION::DIR_UP:
				_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll3");
				break;
			case DIRECTION::DIR_DOWN:
				_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll4");
				break;
			}

			// ���� ���⿡ ���� �ֺ� Ÿ�� ����
			switch (door->GetDirection())
			{
			case DIRECTION::DIR_LEFT: case DIRECTION::DIR_RIGHT:
				if (i == y + pos[2] && i - 1 >= 0)
				{
					_vMapData[i - 1][j]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile19")->_image;
					_vMapData[i - 1][j]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile19")->_colImage;
				}

				if (i == y + pos[3] && i + 1 < _vMapData.size())
				{
					_vMapData[i + 1][j]->_img = DATAMANAGER->GetGridDataByName("Stage1_Tile1")->_image;
					_vMapData[i + 1][j]->_collisionImage = DATAMANAGER->GetGridDataByName("Stage1_Tile1")->_colImage;
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

			case DIRECTION::DIR_DOWN:
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
/// �����ʿ� �����ܵ��� ��ġ�ϱ� ���� �����۾�
/// </summary>
int FieldMap::CheckDungeonMapIcons()
{
	_hasPixie = false;
	_hasTreasure = false;

	int count = 0;
	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetId() >= 2 && _vObjs[i]->GetId() <= 6) // ����
		{
			if (!dynamic_cast<Treasure*>(_vObjs[i])->GetIsOpened())
			{
				count++;
				_hasTreasure = true;
				break;
			}
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetId() >= 13 && _vObjs[i]->GetId() <= 17) // �Ƚ�
		{
			count++;
			_hasPixie = true;
		}
	}

	return count;
}

void FieldMap::release()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			SAFE_DELETE(_vMapData[i][j]);
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->release();
		SAFE_DELETE(_vObjs[i]);
	}
}

/// <summary>
/// �� ����/���� �� �ֺ� Ÿ���� �ȼ��浹 �¿����� �Ѵ�.
/// </summary>
void FieldMap::MakeNearTileCollision(Door* door, bool isActivate)
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

	// �ֺ� Ÿ�ϵ��� ���� �ش� Ÿ�ϵ��� �浹 ������ �ٲ۴�.
	for (int i = y + pos[2]; i <= y + pos[3]; i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = x + pos[0]; j <= x + pos[1]; j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;

			if (isActivate)
			{
				_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Red_CollisionAll");
			}
			else
			{
				switch (door->GetDirection()) // ���⿡ ���� �浹�ȼ� ����
				{
				case DIRECTION::DIR_LEFT:
					_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll");
					break;
				case DIRECTION::DIR_RIGHT:
					_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll2");
					break;
				case DIRECTION::DIR_UP:
					_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll3");
					break;
				case DIRECTION::DIR_DOWN:
					_vMapData[i][j]->_collisionImage = IMAGEMANAGER->findImage("Green_CollisionAll4");
					break;
				}
			}
		}
	}

	PixelCollisionMapGenerate();
}

/// <summary>
/// �ȼ� �ݸ��� �̹����� �׷� �ȼ��浹�� ���� ����� �Լ�
/// </summary>
void FieldMap::PixelCollisionMapGenerate()
{
	IMAGEMANAGER->addImage("PixelMapIg", "Images/PixelMapIg.bmp", _vMapData[0].size() * 48, _vMapData.size() * 48, true, RGB(255, 255, 255));

	image* pixelMapImg = IMAGEMANAGER->findImage("PixelMapIg");
	HDC pixelMapDC = IMAGEMANAGER->findImage("PixelMapIg")->getMemDC();
	Rectangle(pixelMapDC, -10, -10, 10000, 10000); // �ȼ��浹 �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_collisionImage != nullptr)
			{
				_vMapData[i][j]->_collisionImage->render(pixelMapDC, _vMapData[i][j]->_x, _vMapData[i][j]->_y); // �浹�� ��濡 �浹�� Ÿ�� ��ġ
			}

			if (_fileName == "stage0_town")
			{
				if (j > 59 && i == 23 && j < 80)
				{
					IMAGEMANAGER->findImage("Green_CollisionAll")->render(pixelMapDC, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
				}
			}
		}
	}

	SetFastPixel(IMAGEMANAGER->findImage("PixelMapIg"), MAPMANAGER->GetPixelGetter());
}

/// <summary>
/// �� ��ü Ÿ�� �̹����� �׷� ���� ����� �Լ�
/// </summary>
void FieldMap::GridMapGenerate()
{
	HDC pixelMapDC = IMAGEMANAGER->findImage("PixelMapIg")->getMemDC();

	IMAGEMANAGER->addImage("Layer1MapIg", "Images/PixelMapIg.bmp", ((_vMapData[0].size()+15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800), true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("Layer2MapIg", "Images/PixelMapIg.bmp", ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800), true, RGB(255, 255, 255));
	
	Rectangle(IMAGEMANAGER->findImage("Layer1MapIg")->getMemDC(), -10, -10, ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800)); // �ȼ��浹 �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�
	Rectangle(IMAGEMANAGER->findImage("Layer2MapIg")->getMemDC(), -10, -10, ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15)* 48 : 800)); // �ȼ��浹 �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�
	Rectangle(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), -10, -10, ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15)* 48 : 800)); // �̴ϸ� �̹��� ��ȭ���� Ŀ�ٶ� ��� RECT�� ����´�
	
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

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), j * 48, i * 48);
			if (color == RGB(0, 255, 0) || color == RGB(0, 200, 0) || color == RGB(0, 155, 0) || color == RGB(0, 100, 0))
			{
				if (_fileName == "stage0_town") IMAGEMANAGER->findImage("MiniMapDoor")->stretchRender(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), 1000 + j * 3, 10 + i * 3, 0.66f, 0.66f);
				else IMAGEMANAGER->findImage("MiniMapDoor")->render(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), 1000 + j * 5, 10 + i * 5);
			}
		}
	}
}

void FieldMap::update()
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->update();
	}

	SpawnMonsters();
	EraseDeathObject();
	ShotObject();
	CheckNoMonsterInMap();
	EFFECTMANAGER->update();
}

/// <summary>
/// ���� Ȱ��ȭ ���·� �����
/// </summary>
void FieldMap::SetDoorSpawning()
{
	SOUNDMANAGER->play("����_����_����������");

	for (int i = 0; i < _vObjs.size(); i++)
	{
		switch (_vObjs[i]->GetId())
		{
		case 514: case 515: case 516: case 517:
			dynamic_cast<Door*>(_vObjs[i])->SetIsSpawning(true);
			_vObjs[i]->SetUseImage(1);	// Ȱ��ȭ �̹����� ����
			MakeNearTileCollision(dynamic_cast<Door*>(_vObjs[i]), true);
			break;
		}
	}
}

/// <summary>
/// ���� Ÿ���� ������Ʈ���� �ð��� ���߾� �����Ѵ�.
/// </summary>
void FieldMap::SpawnMonsters()
{
	if (_isSpawning && !_isCleared)
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

/// <summary>
/// �ʿ� ���Ͱ� �� ������ ���� ����
/// </summary>
void FieldMap::CheckNoMonsterInMap()
{
	if (_isSpawning && !_isCleared)
	{
		bool isRemainMonster = false;
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER)
			{
				isRemainMonster = true;
				break;
			}
		}

		if (!isRemainMonster) // ���� ���Ͱ� ������
		{
			int satiety = ENTITYMANAGER->getPlayer()->GetSatiety() - 1;
			if (satiety < 0) satiety = 0;
			ENTITYMANAGER->getPlayer()->SetSatiety(satiety);
			SOUNDMANAGER->play("����_����_����������");

			_isCleared = true; // ���͸� ��� �����ߴ� �˸�
			for (int i = 0; i < _vObjs.size(); i++)
			{
				switch (_vObjs[i]->GetId())
				{
				case 514: case 515: case 516: case 517: // �� Case
					dynamic_cast<Door*>(_vObjs[i])->SetIsActivated(false);
					break;
				}
			}

			if (_pixieSpawner != nullptr) // �Ƚ� �����ʰ� �ִٸ�
			{
				if (RANDOM->range(100) < 30)
				{
					_pixieSpawner->SpawnPixie();
					SOUNDMANAGER->play("������Ʈ_���ڿ���", 0.5f, true);
				}
			}

			if (_treasureSpawner != nullptr) // ���� �����ʰ� �ִٸ�
			{
				if (RANDOM->range(100) < 30)
				{
					_treasureSpawner->SpawnTreasure();			
					SOUNDMANAGER->play("������Ʈ_���ڿ���", 0.5f, true);
				}
			}
		}
	}
}

/// <summary>
/// ����� ������Ʈ�� ���ش�.
/// </summary>
void FieldMap::EraseDeathObject()
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetIsDead())
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER)
			{
				ENTITYMANAGER->getPlayer()->DamageUpEnemyKill();
			}

			_vObjs.erase(_vObjs.begin() + i);
			i--;
		}
	}
}

/// <summary>
/// �׽�Ʈ��, ���� ������Ʈ�� �ı���.
/// </summary>
void FieldMap::ShotObject()
{
	if (INPUT->GetKey(VK_CONTROL) && INPUT->GetIsLButtonClicked())
	{
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER || _vObjs[i]->GetType() == OBJECTTYPE::OT_BREAKABLE)
			{
				if (PtInRect(&_vObjs[i]->GetBody(), CAMERAMANAGER->GetAbsolutePoint(_ptMouse.x, _ptMouse.y)))
				{
					_vObjs[i]->SetIsDead(true);
					break;
				}
			}
		}
	}
}

void FieldMap::ChangePlayerByDirection(DIRECTION dir)
{
	ENTITYMANAGER->getPlayer()->SetX(_mapMovePos[dir].x);
	ENTITYMANAGER->getPlayer()->SetY(_mapMovePos[dir].y);
	ENTITYMANAGER->getPlayer()->SetBodyPos();
}

void FieldMap::render(HDC hdc)
{
	if (_backImageMain != nullptr) _backImageMain->loopRender(hdc, &RectMake(0, 0, WINSIZEX, WINSIZEY), CAMERAMANAGER->GetRect().left / 4, CAMERAMANAGER->GetRect().top / 4);

	int mapSizeX = _vMapData[0].size() * 48;
	int mapSizeY = _vMapData.size() * 48;

	if (_stage == 1 || _stage == 2)
	{
		CAMERAMANAGER->StretchRender(hdc, _backImageEtc, -WINSIZEX / 2, -WINSIZEY / 2, WINSIZEX + mapSizeX, WINSIZEY / 2);
		CAMERAMANAGER->StretchRender(hdc, _backImageEtc, -WINSIZEX / 2, 0, WINSIZEX / 2, mapSizeY);
		CAMERAMANAGER->StretchRender(hdc, _backImageEtc, -WINSIZEX / 2, mapSizeY, WINSIZEX + mapSizeX, WINSIZEY / 2);
		CAMERAMANAGER->StretchRender(hdc, _backImageEtc, mapSizeX, 0, WINSIZEX / 2, mapSizeY);
	}

	if (_stage == 0)
	{
		_townBackgroundImg->render(hdc, 0, 0);
		_townMountainImg->loopRender(hdc, &RectMake(0, -300, WINSIZEX, 1200), CAMERAMANAGER->GetRect().left / 4, CAMERAMANAGER->GetRect().top / 8);
		_townGrassImg->loopRender(hdc, &RectMake(0, -200,WINSIZEX, 1000), CAMERAMANAGER->GetRect().left / 2, CAMERAMANAGER->GetRect().top/2);
		CAMERAMANAGER->StretchRender(hdc, _backImageEtc, -WINSIZEX / 2, mapSizeY, WINSIZEX + mapSizeX, WINSIZEY / 2);
	}

	CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("Layer2MapIg"), 0, 0);
	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (!_vObjs[i]->GetRenderIndex() == 0)
			_vObjs[i]->render(hdc);
	} // ������Ʈ ���� 0 ����

	CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("Layer1MapIg"), 0, 0);


	if (INPUT->GetKey(VK_F1))
	{
		CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("PixelMapIg"), 0, 0);
	} // �ȼ��浹 ����

	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetRenderIndex() == 1)
			_vObjs[i]->render(hdc);
	} // ������Ʈ ���� 1 ����

	EFFECTMANAGER->render(hdc);
	ENTITYMANAGER->render(hdc);
	PARTICLEMANAGER->render(hdc);
	// �÷��̾� �� �Ҹ� �� ����

	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetRenderIndex() == 2)
			_vObjs[i]->render(hdc);
	} // ������Ʈ ���� 2 ����


	IMAGEMANAGER->findImage("MiniMapGroundIg")->render(hdc, 0, 0);
	//�̴ϸʿ� �÷��̾� ����
	if (_fileName == "stage0_town")
	{
		IMAGEMANAGER->findImage("MiniMapPlayer")->render(hdc,
			1000 + (float)3 / 48 * ENTITYMANAGER->getPlayer()->GetX(), 10 + (float)3 / 48 * ENTITYMANAGER->getPlayer()->GetY());
	}
	else
	{
		IMAGEMANAGER->findImage("MiniMapPlayer")->render(hdc,
			1000 + (float)5 / 48 * ENTITYMANAGER->getPlayer()->GetX(), 10 + (float)5 / 48 * ENTITYMANAGER->getPlayer()->GetY());
	}

	//�̴ϸʿ� ���� ����
	for (int i = 0; i < _vObjs.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(_vObjs[i]);

		if (_vObjs[i]->GetType() == OT_MONSTER && enemy->GetIsSpawned())
		{
			IMAGEMANAGER->findImage("MiniMapEnemy")->render(hdc,
				1000 + (float)5 / 48 * (_vObjs[i]->GetX() + _vObjs[i]->GetImage(0)->getFrameWidth() / 2),
				10 + (float)5 / 48 * (_vObjs[i]->GetY() + _vObjs[i]->GetImage(0)->getFrameHeight() / 2));
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		//�̴ϸʿ� ���� ����
		if (_vObjs[i]->GetId() >= 2 && _vObjs[i]->GetId() <= 6) // ����
		{
			if (!dynamic_cast<Treasure*>(_vObjs[i])->GetIsOpened())
			{
				IMAGEMANAGER->findImage("MiniMapTresure")->render(hdc,
					1000 + (float)5 / 48 * (_vObjs[i]->GetX() + _vObjs[i]->GetImage(0)->getFrameWidth() / 2) - 8,
					10 + (float)5 / 48 * (_vObjs[i]->GetY() + _vObjs[i]->GetImage(0)->getFrameHeight() / 2) - 4);
			}
		}

		// �̴ϸʿ� �Ƚ� ����
		else if (_vObjs[i]->GetId() >= 13 && _vObjs[i]->GetId() <= 17) // �Ƚ�
		{
			IMAGEMANAGER->findImage("MiniMapfairyIcon")->render(hdc,
				1000 + (float)5 / 48 * (_vObjs[i]->GetX() + _vObjs[i]->GetImage(0)->getFrameWidth() / 2) - 6,
				10 + (float)5 / 48 * (_vObjs[i]->GetY() + _vObjs[i]->GetImage(0)->getFrameHeight() / 2) - 6);
		}

		//�̴ϸʿ� ��Ż ����
		else if (_vObjs[i]->GetId() == 0) // ��Ż
		{
			IMAGEMANAGER->findImage("MiniMapWorm")->render(hdc,
				1000 + (float)5 / 48 * (_vObjs[i]->GetX() + _vObjs[i]->GetImage(0)->getFrameWidth() / 2) - 5,
				10 + (float)5 / 48 * (_vObjs[i]->GetY() + _vObjs[i]->GetImage(0)->getFrameHeight() / 2) - 6);
		}
	}

}

void FieldMap::DoorParticleGenerate()
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		switch (_vObjs[i]->GetId())
		{
		case 514: case 515: case 516: case 517:
			dynamic_cast<Door*>(_vObjs[i])->SetPGenerator();
			break;
		}
	}
}
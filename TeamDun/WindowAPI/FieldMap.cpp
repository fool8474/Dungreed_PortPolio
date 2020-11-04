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
/// 사전에 맵을 로드하여 타일과 오브젝트를 배치해넣는다.
/// </summary>
void FieldMap::LoadMap()
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + ".mapData");
	vector<vector<string>> stringData2 = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + "2.mapData");

	if (stringData.size() == 0 || stringData2.size() == 0)
	{
		return;
	} // 해당 맵 불러오기에 실패한 경우

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
					rc = RectMake(1000 + j * 3, 10 + i * 3, 3, 3); // 한칸당 5픽셀이기 때문에 늘리고싶으면 이미지도 같이 바꿔야합니다
				else
				{
					rc = RectMake(1000 + j * 5, 10 + i * 5, 5, 5); // 한칸당 5픽셀이기 때문에 늘리고싶으면 이미지도 같이 바꿔야합니다
				}
				_vMiniRc.push_back(rc);
			}
			if (stringData2[i][j] == "-1") tile->_img2 = nullptr;
			else tile->_img2 = IMAGEMANAGER->findImage(stringData2[i][j]);
			tile->_x = j * 48;
			tile->_y = i * 48;

			if (stringData[i][j] == "-1") tile->_collisionImage = nullptr;	// 타일이 없다면 충돌체도 없다.
			else tile->_collisionImage = DATAMANAGER->GetGridDataByName(stringData[i][j])->_colImage; // 충돌체를 적당한 이미지로 넣는다.

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
		case 1: // 딸기 분수
			obj = new StrawberryFountain(*dynamic_cast<StrawberryFountain*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<StrawberryFountain*>(obj)->initSecond();
			break;
		case 239: // 배고파 분수
			obj = new HungryFountain(*dynamic_cast<HungryFountain*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<HungryFountain*>(obj)->initSecond();
			break;
		case 1500:// 큰 해골
			obj = new BigWhiteSkel(*dynamic_cast<BigWhiteSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1501:// 미노타우르스
			obj = new Minotaurs(*dynamic_cast<Minotaurs*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 701: // 어비스 밴시
			obj = new AbyssBanshee(*dynamic_cast<AbyssBanshee*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 702: // 붉은 박쥐
			obj = new RedBat(*dynamic_cast<RedBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 703: // 보라 박쥐
			obj = new PurpleBat(*dynamic_cast<PurpleBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 704: // 얼음 박쥐
			obj = new IceBat(*dynamic_cast<IceBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 705: // 불 박쥐
			obj = new FireBat(*dynamic_cast<FireBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 2000: // 벨리알
			obj = new Belial(*dynamic_cast<Belial*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1504: // 서큐버스
			obj = new Lilith(*dynamic_cast<Lilith*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1505: // 작은 유령
			obj = new LittleGhost(*dynamic_cast<LittleGhost*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1506:// 해골 강아지
			obj = new SkelDog(*dynamic_cast<SkelDog*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1507:// 칼 해골
			obj = new SwordSkel(*dynamic_cast<SwordSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1508:// 활 해골
			obj = new BowSkel(*dynamic_cast<BowSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1502: // 밴시
			obj = new Banshee(*dynamic_cast<Banshee*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1509: //빨간 큰박쥐
			obj = new RedGiantBat(*dynamic_cast<RedGiantBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1510: //보라 큰박쥐
			obj = new PurpleGiantBat(*dynamic_cast<PurpleGiantBat*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 514: // 문 왼쪽
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 515: // 문 오른쪽
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 516: // 문 위쪽
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 517: // 문 아래쪽
			obj = new Door(*dynamic_cast<Door*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 2500: // 몬스터 스포너
			obj = new MonsterSpawner(*dynamic_cast<MonsterSpawner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 2502: // 픽시 스포너
			obj = new PixieSpawner(*dynamic_cast<PixieSpawner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			_pixieSpawner = dynamic_cast<PixieSpawner*>(obj);
			break;
		case 2503: // 상자 스포너
			obj = new TreasureSpawner(*dynamic_cast<TreasureSpawner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			_treasureSpawner = dynamic_cast<TreasureSpawner*>(obj);
			break;
		case 2504: // 포지션 무버
			obj = new MovePositioner(*dynamic_cast<MovePositioner*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 10: // 상점
			obj = new Shop(*dynamic_cast<Shop*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Shop*>(obj)->initSecond();
			dynamic_cast<Shop*>(obj)->SetShopItem();
			dynamic_cast<Shop*>(obj)->ReNewUI();
			break;
		case 12: // 밥 잘 파는 예쁜 누나
			obj = new Restaurant(*dynamic_cast<Restaurant*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Restaurant*>(obj)->initSecond();
			dynamic_cast<Restaurant*>(obj)->SetRestaurantFood();
			dynamic_cast<Restaurant*>(obj)->ReNewUI();
			break;
		case 0: // 포탈
			obj = new Portal(*dynamic_cast<Portal*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Portal*>(obj)->initSecond();
			_portal = dynamic_cast<Portal*>(obj);
			break;
		case 2: // 전설상자
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 3: // 레어상자
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 4: // 회색상자
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 5: // 갈색상자
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 6: // 금색상자
			obj = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Treasure*>(obj)->initSecond();
			break;
		case 7: // 다음 스테이지 문
			obj = new StageDoor(*dynamic_cast<StageDoor*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<StageDoor*>(obj)->initSecond();
			break;
		case 100: // 큰 박스
			obj = new Box(*dynamic_cast<Box*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 101: // 작은 박스
			obj = new Box(*dynamic_cast<Box*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 102: // 오크통
			obj = new Box(*dynamic_cast<Box*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 5000: // 보스시체
			obj = new BelialDie(*dynamic_cast<BelialDie*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 230: // 피아트 - 마을 총기상점
			obj = new GunShop(*dynamic_cast<GunShop*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<GunShop*>(obj)->initSecond();
			break;
		case 231: // 카블로비나 - 훈련장 코치
			obj = new Trainer(*dynamic_cast<Trainer*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Trainer*>(obj)->initSecond();
			break;
		case 232: // 블로슈 - 마을 의상실
			obj = new Boutique(*dynamic_cast<Boutique*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Boutique*>(obj)->initSecond();
			break;
		case 234: // 하켄 - 마을 대장장이
			obj = new Smith(*dynamic_cast<Smith*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<Smith*>(obj)->initSecond();
			break;
		case 1003: case 1004: // 가시
			obj = new Spike(*dynamic_cast<Spike*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 1000: case 1001: case 1002: // 기어
			obj = new Gear(*dynamic_cast<Gear*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		case 241: // 이전문
			obj = new PrevDoor(*dynamic_cast<PrevDoor*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			dynamic_cast<PrevDoor*>(obj)->initSecond();
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
		obj->SetNewUid();

		bool CheckRollBack = false;
		// AFTER OBJECT LOAD
		switch (stoi(objData[i][0]))
		{
		case 514: // 문 왼쪽
			if (_nextMapIndex[DIRECTION::DIR_LEFT] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 515: // 문 오른쪽
			if (_nextMapIndex[DIRECTION::DIR_RIGHT] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 516: // 문 위쪽
			if (_nextMapIndex[DIRECTION::DIR_UP] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 517: // 문 아래쪽
			if (_nextMapIndex[DIRECTION::DIR_DOWN] != -1)
				MakeDoor(dynamic_cast<Door*>(obj));
			else CheckRollBack = true;
			break;
		case 2000: // 벨리알
			dynamic_cast<Belial*>(obj)->SetAfterSpawn();
			break;

		}

		_vObjs.push_back(obj);
		if (CheckRollBack)
		{
			_vObjs.erase(_vObjs.end() - 1);
		}
	}

	for (int i = 0; i < GetObjects().size(); i++)
	{
		if (GetObjects()[i]->GetId() == 241)
		{
			for (int j = 0; j < GetObjects().size(); j++)
			{
				if (GetObjects()[j]->GetId() == 2504) // 이동장소
				{
					dynamic_cast<PrevDoor*>(GetObjects()[i])->SetPoint(POINT{ GetObjects()[j]->GetX(), GetObjects()[j]->GetY() - 10 }); // 이동 장소 설정
					break;
				}
			}
		}
	}
}

/// <summary>
/// 문을 만들고 해당 문의 주변 타일을 처리한다 
/// </summary>
void FieldMap::MakeDoor(Door* door)
{
	int x = (door->GetX() + door->GetImage(0)->getWidth() / 2) / 48;	// 문의 중점 X
	int y = (door->GetY() + door->GetImage(0)->getHeight() / 2) / 48;	// 문의 중점 Y

	int pos[4] = { 0,0,0,0 };
	switch (door->GetDirection()) // 방향에 따라 변경할 타일의 범위가 달라진다.
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

			// 주변 타일의 변경
			_vMapData[i][j]->_img = nullptr;
			_vMapData[i][j]->_img2 = DATAMANAGER->GetGridDataByName("Stage1_Tile43")->_image;
			switch (door->GetDirection()) // 방향에 따른 충돌픽셀 설정
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

			// 문의 방향에 따른 주변 타일 변경
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
/// 던전맵에 아이콘들을 배치하기 위한 사전작업
/// </summary>
int FieldMap::CheckDungeonMapIcons()
{
	_hasPixie = false;
	_hasTreasure = false;

	int count = 0;
	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetId() >= 2 && _vObjs[i]->GetId() <= 6) // 상자
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
		if (_vObjs[i]->GetId() >= 13 && _vObjs[i]->GetId() <= 17) // 픽시
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
/// 문 생성/해제 시 주변 타일의 픽셀충돌 온오프를 한다.
/// </summary>
void FieldMap::MakeNearTileCollision(Door* door, bool isActivate)
{
	int x = (door->GetX() + door->GetImage(0)->getWidth() / 2) / 48;	// 문의 중점 X
	int y = (door->GetY() + door->GetImage(0)->getHeight() / 2) / 48;	// 문의 중점 Y

	int pos[4] = { 0,0,0,0 };
	switch (door->GetDirection()) // 방향에 따라 변경할 타일의 범위가 달라진다.
	{
	case DIRECTION::DIR_LEFT:	pos[0] = -3;  pos[1] = 0, pos[2] = -2, pos[3] = 2; break;
	case DIRECTION::DIR_RIGHT:	pos[0] = 0;  pos[1] = 3, pos[2] = -2, pos[3] = 2; break;
	case DIRECTION::DIR_UP:		pos[0] = -2;  pos[1] = 1, pos[2] = -2, pos[3] = 0; break;
	case DIRECTION::DIR_DOWN:	pos[0] = -2;  pos[1] = 1, pos[2] = 0, pos[3] = 2; break;
	}

	// 주변 타일들을 돌며 해당 타일들의 충돌 정보를 바꾼다.
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
				switch (door->GetDirection()) // 방향에 따른 충돌픽셀 설정
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
/// 픽셀 콜리젼 이미지를 그려 픽셀충돌용 맵을 만드는 함수
/// </summary>
void FieldMap::PixelCollisionMapGenerate()
{
	IMAGEMANAGER->addImage("PixelMapIg", "Images/PixelMapIg.bmp", _vMapData[0].size() * 48, _vMapData.size() * 48, true, RGB(255, 255, 255));

	image* pixelMapImg = IMAGEMANAGER->findImage("PixelMapIg");
	HDC pixelMapDC = IMAGEMANAGER->findImage("PixelMapIg")->getMemDC();
	Rectangle(pixelMapDC, -10, -10, 10000, 10000); // 픽셀충돌 이미지 도화지에 커다란 흰색 RECT를 끼얹는다

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_collisionImage != nullptr)
			{
				_vMapData[i][j]->_collisionImage->render(pixelMapDC, _vMapData[i][j]->_x, _vMapData[i][j]->_y); // 충돌용 배경에 충돌용 타일 배치
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
/// 맵 전체 타일 이미지에 그려 맵을 만드는 함수
/// </summary>
void FieldMap::GridMapGenerate()
{
	HDC pixelMapDC = IMAGEMANAGER->findImage("PixelMapIg")->getMemDC();

	IMAGEMANAGER->addImage("Layer1MapIg", "Images/PixelMapIg.bmp", ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800), true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("Layer2MapIg", "Images/PixelMapIg.bmp", ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800), true, RGB(255, 255, 255));

	Rectangle(IMAGEMANAGER->findImage("Layer1MapIg")->getMemDC(), -10, -10, ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800)); // 픽셀충돌 이미지 도화지에 커다란 흰색 RECT를 끼얹는다
	Rectangle(IMAGEMANAGER->findImage("Layer2MapIg")->getMemDC(), -10, -10, ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800)); // 픽셀충돌 이미지 도화지에 커다란 흰색 RECT를 끼얹는다
	Rectangle(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), -10, -10, ((_vMapData[0].size() + 15) * 48 > 1440 ? (_vMapData[0].size() + 15) * 48 : 1440), ((_vMapData.size() + 15) * 48 > 800 ? (_vMapData.size() + 15) * 48 : 800)); // 미니맵 이미지 도화지에 커다란 흰색 RECT를 끼얹는다

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_img != nullptr)
			{
				_vMapData[i][j]->_img->render(IMAGEMANAGER->findImage("Layer1MapIg")->getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y); // 충돌용 배경에 충돌용 타일 배치
			}

			if (_vMapData[i][j]->_img2 != nullptr)
			{
				_vMapData[i][j]->_img2->render(IMAGEMANAGER->findImage("Layer2MapIg")->getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y); // 충돌용 배경에 충돌용 타일 배치
			}
		}
	}

	for (int i = 0; i < _vMiniRc.size(); i++)
	{
		IMAGEMANAGER->findImage("MiniMapPixel")->render(IMAGEMANAGER->findImage("MiniMapGroundIg")->getMemDC(), _vMiniRc[i].left, _vMiniRc[i].top);
	} // 미니맵 렌더

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
/// 문을 활성화 상태로 만든다
/// </summary>
void FieldMap::SetDoorSpawning()
{
	SOUNDMANAGER->play("게임_던전_문열림닫힘");

	for (int i = 0; i < _vObjs.size(); i++)
	{
		switch (_vObjs[i]->GetId())
		{
		case 514: case 515: case 516: case 517:
			dynamic_cast<Door*>(_vObjs[i])->SetIsSpawning(true);
			_vObjs[i]->SetUseImage(1);	// 활성화 이미지로 변경
			MakeNearTileCollision(dynamic_cast<Door*>(_vObjs[i]), true);
			break;
		}
	}
}

/// <summary>
/// 몬스터 타입인 오브젝트들을 시간에 맞추어 스폰한다.
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
/// 맵을 클리어했는지 확인하고 이에 따른 작업을 한다.
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

		if (!isRemainMonster) // 남은 몬스터가 없을때
		{
			int satiety = ENTITYMANAGER->getPlayer()->GetSatiety() - 1;
			if (satiety < 0) satiety = 0;
			ENTITYMANAGER->getPlayer()->SetSatiety(satiety);

			if (ENTITYMANAGER->getPlayer()->GetSpecialAbilityOn(5, 1)) // 특성 - 집중 10레벨
			{
				int hpPlus = ENTITYMANAGER->getPlayer()->GetHP() + 2;
				if (hpPlus > ENTITYMANAGER->getPlayer()->GetMaxHp()) hpPlus = ENTITYMANAGER->getPlayer()->GetMaxHp();
				ENTITYMANAGER->getPlayer()->SetHp(hpPlus);
			}

			SOUNDMANAGER->play("게임_던전_문열림닫힘");

			_isCleared = true; // 몬스터를 모두 정리했다 알림
			for (int i = 0; i < _vObjs.size(); i++)
			{
				switch (_vObjs[i]->GetId())
				{
				case 514: case 515: case 516: case 517: // 문 Case
					dynamic_cast<Door*>(_vObjs[i])->SetIsActivated(false);
					break;
				}
			}

			if (_pixieSpawner != nullptr) // 픽시 스포너가 있다면
			{
				if (RANDOM->range(100) < 30)
				{
					_pixieSpawner->SpawnPixie();
					SOUNDMANAGER->play("오브젝트_상자오픈", 0.5f, true);
				}
			}

			if (_treasureSpawner != nullptr) // 상자 스포너가 있다면
			{
				if (RANDOM->range(100) < 30)
				{
					_treasureSpawner->SpawnTreasure();
					SOUNDMANAGER->play("오브젝트_상자오픈", 0.5f, true);
				}
			}
		}
	}
}

/// <summary>
/// 사망한 오브젝트를 없앤다.
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
/// 테스트용, 쏴서 오브젝트를 파괴함.
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
		_townGrassImg->loopRender(hdc, &RectMake(0, -200, WINSIZEX, 1000), CAMERAMANAGER->GetRect().left / 2, CAMERAMANAGER->GetRect().top / 2);
		CAMERAMANAGER->StretchRender(hdc, _backImageEtc, -WINSIZEX / 2, mapSizeY, WINSIZEX + mapSizeX, WINSIZEY / 2);
	}

	CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("Layer2MapIg"), 0, 0);
	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetRenderIndex() == 0)
			_vObjs[i]->render(hdc);
	} // 오브젝트 렌더 0 렌더

	CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("Layer1MapIg"), 0, 0);


	if (INPUT->GetKey(VK_F1))
	{
		CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("PixelMapIg"), 0, 0);
	} // 픽셀충돌 렌더


	for (int i = 0; i < EFFECTMANAGER->GetVEffect().size(); i++)
	{
		if (!EFFECTMANAGER->GetVEffect()[i]->GetIsFirstViewing())
		{
			EFFECTMANAGER->GetVEffect()[i]->render(hdc);
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetRenderIndex() == 1)
			_vObjs[i]->render(hdc);
	} // 오브젝트 렌더 1 렌더
	for (int i = 0; i < EFFECTMANAGER->GetVCamerText().size(); i++)
	{
		EFFECTMANAGER->GetVCamerText()[i]->render(hdc);
	}
	for (int i = 0; i < EFFECTMANAGER->GetVEffect().size(); i++)
	{
		if (EFFECTMANAGER->GetVEffect()[i]->GetIsFirstViewing())
		{
			EFFECTMANAGER->GetVEffect()[i]->render(hdc);
		}
	}
	ENTITYMANAGER->render(hdc);
	PARTICLEMANAGER->render(hdc);
	// 플레이어 및 불릿 등 렌더

	for (int i = 0; i < _vObjs.size(); i++)
	{
		if (_vObjs[i]->GetRenderIndex() == 2)
			_vObjs[i]->render(hdc);
	} // 오브젝트 렌더 2 렌더


	IMAGEMANAGER->findImage("MiniMapGroundIg")->render(hdc, 0, 0);
	//미니맵에 플레이어 렌더
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

	//미니맵에 몬스터 렌더
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
		//미니맵에 상자 렌더
		if (_vObjs[i]->GetId() >= 2 && _vObjs[i]->GetId() <= 6) // 상자
		{
			if (!dynamic_cast<Treasure*>(_vObjs[i])->GetIsOpened())
			{
				IMAGEMANAGER->findImage("MiniMapTresure")->render(hdc,
					1000 + (float)5 / 48 * (_vObjs[i]->GetX() + _vObjs[i]->GetImage(0)->getFrameWidth() / 2) - 8,
					10 + (float)5 / 48 * (_vObjs[i]->GetY() + _vObjs[i]->GetImage(0)->getFrameHeight() / 2) - 4);
			}
		}

		// 미니맵에 픽시 렌더
		else if (_vObjs[i]->GetId() >= 13 && _vObjs[i]->GetId() <= 17) // 픽시
		{
			IMAGEMANAGER->findImage("MiniMapfairyIcon")->render(hdc,
				1000 + (float)5 / 48 * (_vObjs[i]->GetX() + _vObjs[i]->GetImage(0)->getFrameWidth() / 2) - 6,
				10 + (float)5 / 48 * (_vObjs[i]->GetY() + _vObjs[i]->GetImage(0)->getFrameHeight() / 2) - 6);
		}

		//미니맵에 포탈 렌더
		else if (_vObjs[i]->GetId() == 0) // 포탈
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
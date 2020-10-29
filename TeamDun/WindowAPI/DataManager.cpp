#include "stdafx.h"
#include "DataManager.h"

HRESULT DataManager::Init()
{
	_mGridDataByName = map<string, GridData*>();
	_mGridData = map<int, GridData*>();
	_mObjectData = map<int, Object*>();
	_mMapObjectData = map<int, MapObject*>();
	_mMapItemData = map<int, Item*>();

	_itemMaxId = 0;
	_itemMinId = 0;

	return S_OK;
}

/// <summary>
/// UIBrushTool에 배치하기 위한 GridData들을 불러온다.
/// </summary>
void DataManager::GetUIBrushToolGridData()
{
	vector<vector<string>> gridData = CSVMANAGER->csvLoad("Data/UIBrushToolGrid.csv");

	for (int i = 0; i < gridData.size(); i++)
	{
		GridData* grid = new GridData();

		grid->_x = stoi(gridData[i][1]);
		grid->_y = stoi(gridData[i][2]);
		grid->_page = stoi(gridData[i][3]);
		grid->_image = IMAGEMANAGER->findImage(gridData[i][4]);
		grid->_name = gridData[i][4];
		grid->_colImage = IMAGEMANAGER->findImage(gridData[i][5]);
		_mGridData[stoi(gridData[i][0])] = grid;
		_mGridDataByName[grid->_name] = grid;
	}
}

/// <summary>
/// Object들의 데이터를 불러온다.
/// </summary>
void DataManager::GetObjectData()
{
	// Object 데이터 파트
	vector<vector<string>> objData = CSVMANAGER->csvLoad("Data/ObjectData.csv");

	for (int i = 0; i < objData.size(); i++)
	{
		OBJECTTYPE type;
		if (objData[i][2] == "Breakable")
			type = OBJECTTYPE::OT_BREAKABLE;
		else if (objData[i][2] == "Etc")
			type = OBJECTTYPE::OT_ETC;
		else if (objData[i][2] == "Obstacle")
			type = OBJECTTYPE::OT_OBSTACLE;
		else if (objData[i][2] == "NPC")
			type = OBJECTTYPE::OT_NPC;
		else if (objData[i][2] == "Monster")
			type = OBJECTTYPE::OT_MONSTER;
		else if (objData[i][2] == "Death")
			type = OBJECTTYPE::OT_DEATH;

		/// <summary>
		/// 오브젝트를 추가하고 클래스를 따로 만들었다면 반드시 체크해야할 부분 (ID순)
		/// </summary>
		Object* obj;
		switch (stoi(objData[i][0]))
		{
		case 0: // 포탈
			obj = new Portal(); break;
		case 1: // 딸기 분수
			obj = new StrawberryFountain(); break;
		case 2: // 전설상자
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_LEGENDARY);
			break;
		case 3: // 레어상자
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_BLUE);
			break;
		case 4: // 회색상자
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_GRAY);
			break;
		case 5: // 갈색상자
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_BROWN);
			break;
		case 6: // 금색상자
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_GOLD);
			break;
		case 7: // 다음 스테이지 문
			obj = new StageDoor(); break;
		case 10: // 상점 주인
			obj = new Shop(); break;
		case 12: // 밥 잘 파는 예쁜 누나
			obj = new Restaurant(); break;
		case 13: // 작은 픽시
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::SMALL);
			break;
		case 14: // 중간 픽시
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::MIDDLE);
			break;
		case 15: // 큰 픽시
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::LARGE);
			break;
		case 16: // 매우 큰 픽시
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::XLARGE);
			break;
		case 17: // 매우 큰 픽시
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::GREEN);
			break;
		case 100: // 큰 박스
			obj = new Box();
			dynamic_cast<Box*>(obj)->SetBoxType(BOXTYPE::BOX_BIGBOX);
			dynamic_cast<Box*>(obj)->SetParticle();
			break;
		case 101: // 작은 박스
			obj = new Box();
			dynamic_cast<Box*>(obj)->SetBoxType(BOXTYPE::BOX_SMALLBOX);
			dynamic_cast<Box*>(obj)->SetParticle();
			break;
		case 102: // 오크통
			obj = new Box();
			dynamic_cast<Box*>(obj)->SetBoxType(BOXTYPE::BOX_ORC);
			dynamic_cast<Box*>(obj)->SetParticle();
			break;
		case 230: // 피아트 - 마을 총기상점
			obj = new GunShop(); break;
		case 231: // 카블로비나 - 훈련장 코치
			obj = new Trainer(); break;
		case 232: // 블로슈 - 마을 의상실
			obj = new Boutique(); break;
		case 234: // 하켄 - 마을 대장장이
			obj = new Smith(); break;
		case 239: // 배고파 분수
			obj = new HungryFountain(); break;
		case 241: // 이전무
			obj = new PrevDoor(); break;
		case 514: // 문 왼쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_LEFT);
			break;
		case 515: // 문 오른쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_RIGHT);
			break;
		case 516: // 문 위쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_UP);
			break;
		case 517: // 문 아래쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_DOWN);
			break;
		case 524: // 동전
			obj = new Coin(); break;
		case 701: // 어비스 밴시
			obj = new AbyssBanshee(); break;
		case 702: // 붉은 박쥐
			obj = new RedBat(); break;
		case 703: // 보라 박쥐
			obj = new PurpleBat(); break;
		case 704: // 얼음 박쥐
			obj = new IceBat(); break;
		case 705: // 불박쥐
			obj = new FireBat(); break;
		case 1000: case 1001: case 1002: // 기어
			obj = new Gear(); break;
		case 1003: case 1004: // 가시
			obj = new Spike(); break;
		case 1500:// 큰 해골
			obj = new BigWhiteSkel(); break;
		case 1501:// 미노타우르스
			obj = new Minotaurs(); break;
		case 1502: // 밴시
			obj = new Banshee(); break;
		case 1504:// 서큐버스
			obj = new Lilith(); break;
		case 1505:// 작은 유령
			obj = new LittleGhost(); break;
		case 1506:// 해골 강아지
			obj = new SkelDog();  break;
		case 1507:// 칼 해골
			obj = new SwordSkel(); break;
		case 1508:// 활 해골
			obj = new BowSkel(); break;
		case 1509: // 빨간 큰 박쥐
			obj = new RedGiantBat(); break;
		case 1510: // 보라 큰 박쥐
			obj = new PurpleGiantBat(); break;
		case 2000: // 벨리알
			obj = new Belial(); break;
		case 2500: // 몬스터 스포너
			obj = new MonsterSpawner(); break;
		case 2501: // 마을 - 던전 포탈
			obj = new WormVillage(); break;
		case 2502: // 픽시 스포너
			obj = new PixieSpawner(); break;
		case 2503: // 상자 스포너
			obj = new TreasureSpawner(); break;
		case 2504: // 무브 포지셔너
			obj = new MovePositioner(); break;
		case 5000: // 밸리알 시체
			obj = new BelialDie(); break;
		default:
			obj = new Object();  break;
		}

		obj->init(
			stoi(objData[i][0]),
			objData[i][1],
			type,
			vector<string>{objData[i][3], objData[i][4], objData[i][5] }
		);

		if (obj->GetType() == OT_OBSTACLE) obj->SetRenderIndex(false); // 장애물은 렌더가 벽 뒤로 되도록 함

		_mObjectData[stoi(objData[i][0])] = obj;
	}

	// UIBrushTool에 배치하기 위한 mapObject 데이터 파트
	vector<vector<string>> mapObjData = CSVMANAGER->csvLoad("Data/MapObjectData.csv");
	for (int i = 0; i < mapObjData.size(); i++)
	{
		MapObject* obj = new MapObject();
		obj->init(stoi(mapObjData[i][0]),
			stof(mapObjData[i][1]),
			stof(mapObjData[i][2]),
			stoi(mapObjData[i][3])
		);

		_mMapObjectData[stoi(mapObjData[i][0])] = obj;
	}
}

/// <summary>
/// 아이템 데이터를 불러온다
/// </summary>
void DataManager::GetItemData()
{
	vector<vector<string>> itemData = CSVMANAGER->csvLoad("Data/ItemData.csv");

	for (int i = 0; i < itemData.size(); i++)
	{
		if (i == 0) _itemMinId = stoi(itemData[i][0]);
		if (i == itemData.size() - 1) _itemMaxId = stoi(itemData[i][0]);

		/// <summary>
		/// 아이템을 추가하고 클래스가 존재하면 이곳에 반드시 추가해준다! (ID순)
		/// </summary>
		Item* item;
		switch (stoi(itemData[i][0]))
		{
		case 4000: // 마검 엘레마
			item = new DemonSword(); break;
		case 4001: // 더콜트
			item = new Colt(); break;
		case 4005: // 소르베오의피
			item = new BloodOfSrobeo(); break;
		case 4006: //폭탄주머니
			item = new BombPouch(); break;
		case 4007: // 혈석 반지
			item = new BloodStoneRing(); break;
		case 4015: // 현자의 축복
			item = new BlessOfSage(); break;
		case 4017: // 숏 소드
			item = new BasicShortSword(); break;
		case 4100: // 떡갈나무활
			item = new GreatBow(); break;
		case 4021: // 죽도
			item = new BambooSword(); break;
		case 4023: // 카타나
			item = new Katana(); break;
		case 4024: // 샴쉬르
			item = new Shamshir(); break;
		case 4025: // 세이버
			item = new Saber(); break;
		case 4026: // 돋보기
			item = new MagnifyingGlass(); break;
		case 4028: // 그웬돌린
			item = new Gwendolyn(); break;
		case 4029: // 단창
			item = new ShortSpear(); break;
		case 4030: // 레이피어
			item = new Rapier(); break;
		case 4052: // 난사
			item = new RampageWpn(); break;
		case 4140: // 라라의 요술봉
			item = new LalaMagic(); break;
		case 4031: // MT8 카빈
			item = new Rifle(); break;
		case 4500: // 골든캔디
			item = new GoldenCandy(); break;
		case 5200: // 대포
			item = new Canon(); break;
		case 5201: // 부메랑
			item = new Boomerang(); break;
		default:
			item = new Item(); break;
		}

		// 아이템 타입
		ITEMTYPE itemType = ITEMTYPE::IT_NOTHING;
		if (itemData[i][1] == "한손무기") itemType = ITEMTYPE::IT_WEAPON_ONEHAND;
		else if (itemData[i][1] == "두손무기") itemType = ITEMTYPE::IT_WEAPON_TWOHAND;
		else if (itemData[i][1] == "서브무기") itemType = ITEMTYPE::IT_SUBWEAPON;
		else if (itemData[i][1] == "악세서리") itemType = ITEMTYPE::IT_ACCESORRY;
		else itemType = ITEMTYPE::IT_NOTHING;

		// 무기 타입
		WEAPONTYPE weaponType = WEAPONTYPE::WT_NOWEAPON;
		if (itemData[i][2] == "근접") weaponType = WEAPONTYPE::WT_NEAR;
		else if (itemData[i][2] == "원거리") weaponType = WEAPONTYPE::WT_RANGE;
		else if (itemData[i][2] == "충전형") weaponType = WEAPONTYPE::WT_CHARGE;
		else if (itemData[i][2] == "창") weaponType = WEAPONTYPE::WT_SPEAR;
		else if (itemData[i][2] == "권총") weaponType = WEAPONTYPE::WT_PISTOL;
		else if (itemData[i][2] == "카타나") weaponType = WEAPONTYPE::WT_KATANA;
		else weaponType = WEAPONTYPE::WT_NOWEAPON;

		// 아이템 클래스
		ITEMCLASS itemClass = ITEMCLASS::IC_NORMAL;
		if (itemData[i][6] == "일반") itemClass = ITEMCLASS::IC_NORMAL;
		else if (itemData[i][6] == "고급") itemClass = ITEMCLASS::IC_ADVANCED;
		else if (itemData[i][6] == "희귀") itemClass = ITEMCLASS::IC_RARE;
		else if (itemData[i][6] == "전설") itemClass = ITEMCLASS::IC_LEGENDARY;

		// 스킬 추가 (ID를 통해)
		Skill* skill;
		switch (stoi(itemData[i][3]))
		{
		case 1: // 라라 (유성우)
			skill = new LalaSkill();
			skill->init();
			break;
		default:
			skill = nullptr;
			break;
		}

		// 아이템 초기화
		item->init(stoi(itemData[i][0]), itemType, weaponType, skill,
			itemData[i][4], itemData[i][5], itemClass, stof(itemData[i][7]), stof(itemData[i][8]),
			stof(itemData[i][9]), stoi(itemData[i][10]), stoi(itemData[i][11]),
			stoi(itemData[i][12]), stof(itemData[i][13]), nullptr, stof(itemData[i][15]), stoi(itemData[i][16]),
			stoi(itemData[i][17]), vector<string>{itemData[i][18], itemData[i][19], itemData[i][20]}, itemData[i][21], itemData[i][22]
		);

		// 추가 옵션 파트
		for (int j = 0; j < 3; j++) // CSV에서는 최대 3개지만, 클래스 내부의 init를 통해 얼마든지 추가할 수 있다.
		{
			if (itemData[i][23 + (j * 3)] != ".")
			{
				SubOption* option = new SubOption;

				string optionId = itemData[i][23 + (j * 3)];
				if (optionId == "ACCURACY") option->_optionId = OPTIONTYPE::ACCURACY;
				else if (optionId == "ATKSPEED") option->_optionId = OPTIONTYPE::ATKSPEED;
				else if (optionId == "BLOCK") option->_optionId = OPTIONTYPE::BLOCK;
				else if (optionId == "CRITICALPERCENT") option->_optionId = OPTIONTYPE::CRITICALPERCENT;
				else if (optionId == "CRITICALDAMAGE") option->_optionId = OPTIONTYPE::CRITICALDAMAGE;
				else if (optionId == "DASHATK") option->_optionId = OPTIONTYPE::DASHATK;
				else if (optionId == "DASHCOUNT") option->_optionId = OPTIONTYPE::DASHCOUNT;
				else if (optionId == "DEFENCE") option->_optionId = OPTIONTYPE::DEFENCE;
				else if (optionId == "ETC") option->_optionId = OPTIONTYPE::ETC;
				else if (optionId == "ELECDAMAGE") option->_optionId = OPTIONTYPE::ELECDAMAGE;
				else if (optionId == "EVADE") option->_optionId = OPTIONTYPE::EVADE;
				else if (optionId == "FINALDAMAGE") option->_optionId = OPTIONTYPE::FINALDAMAGE;
				else if (optionId == "FINALDAMAGEPERCENT") option->_optionId = OPTIONTYPE::FINALDAMAGEPERCENT;
				else if (optionId == "FIREDAMAGE") option->_optionId = OPTIONTYPE::FIREDAMAGE;
				else if (optionId == "GOLDDROP") option->_optionId = OPTIONTYPE::GOLDDROP;
				else if (optionId == "ICEDAMAGE") option->_optionId = OPTIONTYPE::ICEDAMAGE;
				else if (optionId == "IMMUNEELEC") option->_optionId = OPTIONTYPE::IMMUNEELEC;
				else if (optionId == "IMMUNEFIRE") option->_optionId = OPTIONTYPE::IMMUNEFIRE;
				else if (optionId == "IMMUNEICE") option->_optionId = OPTIONTYPE::IMMUNEICE;
				else if (optionId == "IMMUNEPOSION") option->_optionId = OPTIONTYPE::IMMUNEPOSION;
				else if (optionId == "IMMUNESTUN") option->_optionId = OPTIONTYPE::IMMUNESTUN;
				else if (optionId == "JUMPPOWER") option->_optionId = OPTIONTYPE::JUMPPOWER;
				else if (optionId == "MAXDAMAGE") option->_optionId = OPTIONTYPE::MAXDAMAGE;
				else if (optionId == "MAXHP") option->_optionId = OPTIONTYPE::MAXHP;
				else if (optionId == "MAXHPPERCENT") option->_optionId = OPTIONTYPE::MAXHPPERCENT;
				else if (optionId == "MINDAMAGE") option->_optionId = OPTIONTYPE::MINDAMAGE;
				else if (optionId == "MOVESPEED") option->_optionId = OPTIONTYPE::MOVESPEED;
				else if (optionId == "POSIONDAMAGE") option->_optionId = OPTIONTYPE::POSIONDAMAGE;
				else if (optionId == "POWER") option->_optionId = OPTIONTYPE::POWER;
				else if (optionId == "RELOADSPEED") option->_optionId = OPTIONTYPE::RELOADSPEED;
				else if (optionId == "STUNDAMAGE") option->_optionId = OPTIONTYPE::STUNDAMAGE;
				else if (optionId == "TOUGHNESS") option->_optionId = OPTIONTYPE::TOUGHNESS;
				else if (optionId == "TOELEC") option->_optionId = OPTIONTYPE::TOELEC;
				else if (optionId == "TOFIRE") option->_optionId = OPTIONTYPE::TOFIRE;
				else if (optionId == "TOICE") option->_optionId = OPTIONTYPE::TOICE;
				else if (optionId == "TOPOSION") option->_optionId = OPTIONTYPE::TOPOSION;
				else if (optionId == "TOSTUN") option->_optionId = OPTIONTYPE::TOSTUN;
				else if (optionId == "TRUEDAMAGE") option->_optionId = OPTIONTYPE::TRUEDAMAGE;

				option->_optionPower = stof(itemData[i][24 + (j * 3)]);
				option->_description = itemData[i][25 + (j * 3)];
				item->AddSubOption(option);
			}
		}

		_mMapItemData[stoi(itemData[i][0])] = item;
	}
}

int	DataManager::GetItemSize()
{
	return _mMapItemData.size();
}

/// <summary>
/// index번째 아이템을 가져온다.
/// </summary>
Item* DataManager::GetItemByIndex(int index)
{
	map<int, Item*>::iterator iter;
	int count = 0;
	for (iter = _mMapItemData.begin(); iter != _mMapItemData.end(); ++iter)
	{
		if (count == index) { return iter->second; }
		count++;
	}

	return nullptr;
}

/// <summary>
/// ID를 통해 아이템을 가져온다.
/// </summary>
Item* DataManager::GetItemById(int id)
{
	Item* rtnItem;
	switch (id)
	{
	case 4000: // 마검 엘레마
		return new DemonSword(*dynamic_cast<DemonSword*>(_mMapItemData[id]));
	case 4001: // 더 콜트
		return new Colt(*dynamic_cast<Colt*>(_mMapItemData[id]));
	case 4005: // 소르베오의피
		return new BloodOfSrobeo(*dynamic_cast<BloodOfSrobeo*>(_mMapItemData[id]));
	case 4006: //폭탄주머니
		return new BombPouch(*dynamic_cast<BombPouch*>(_mMapItemData[id]));
	case 4007: // 혈석 반지
		return new BloodStoneRing(*dynamic_cast<BloodStoneRing*>(_mMapItemData[id]));
	case 4015: // 현자의 축복
		return new BlessOfSage(*dynamic_cast<BlessOfSage*>(_mMapItemData[id]));
	case 4017: // 숏 소드
		return new BasicShortSword(*dynamic_cast<BasicShortSword*>(_mMapItemData[id]));
	case 4021: // 죽도
		return new BambooSword(*dynamic_cast<BambooSword*>(_mMapItemData[id]));
	case 4023: // 카타나
		return new Katana(*dynamic_cast<Katana*>(_mMapItemData[id]));
	case 4024: // 샴쉬르
		return new Shamshir(*dynamic_cast<Shamshir*>(_mMapItemData[id]));
	case 4025: // 세이버
		return new Saber(*dynamic_cast<Saber*>(_mMapItemData[id]));
	case 4026: // 돋보기
		return new MagnifyingGlass(*dynamic_cast<MagnifyingGlass*>(_mMapItemData[id]));
	case 4028: // 그웬돌린
		return new Gwendolyn(*dynamic_cast<Gwendolyn*>(_mMapItemData[id]));
	case 4029: // 단창
		return new ShortSpear(*dynamic_cast<ShortSpear*>(_mMapItemData[id]));
	case 4030: // 레이피어
		return new Rapier(*dynamic_cast<Rapier*>(_mMapItemData[id]));
	case 4031: // MT8 카빈
		return new Rifle(*dynamic_cast<Rifle*>(_mMapItemData[id]));
	case 4052: // 난사
		return new RampageWpn(*dynamic_cast<RampageWpn*>(_mMapItemData[id]));
	case 4100: // 떡갈나무활
		return new GreatBow(*dynamic_cast<GreatBow*>(_mMapItemData[id]));
	case 4140: // 라라의 요술봉
		return new LalaMagic(*dynamic_cast<LalaMagic*>(_mMapItemData[id]));
	case 4500: // 골든캔디
		return new GoldenCandy(*dynamic_cast<GoldenCandy*>(_mMapItemData[id]));
	case 5200: // 대포
		return new Canon(*dynamic_cast<Canon*>(_mMapItemData[id]));
	case 5201: // 부메랑
		return new Boomerang(*dynamic_cast<Boomerang*>(_mMapItemData[id]));
	default:
		return _mMapItemData[id];
	}
}

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
/// UIBrushTool�� ��ġ�ϱ� ���� GridData���� �ҷ��´�.
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
/// Object���� �����͸� �ҷ��´�.
/// </summary>
void DataManager::GetObjectData()
{
	// Object ������ ��Ʈ
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

		Object* obj;
		switch (stoi(objData[i][0]))
		{
		case 1500:// ū �ذ�
			obj = new BigWhiteSkel();
			break;
		case 1501:// �̳�Ÿ�츣��
			obj = new Minotaurs();
			break;
		case 1504:// ��ť����
			obj = new Lilith();
			break;
		case 1505:// ���� ����
			obj = new LittleGhost();
			break;
		case 1506:// �ذ� ������
			obj = new SkelDog();
			break;
		case 1507:// Į �ذ�
			obj = new SwordSkel();
			break;
		case 1508:// Ȱ �ذ�
			obj = new BowSkel();
			break;
		case 1502: // ���
			obj = new Banshee();
			break;
		case 1509: // ���� ū ����
			obj = new RedGiantBat();
			break;
		case 1510: // ���� ū ����
			obj = new PurpleGiantBat();
			break;
		case 702: // ���� ����
			obj = new RedBat();
			break;
		case 704: // ���� ����
			obj = new IceBat();
			break;
		case 705: // �ҹ���
			obj = new FireBat();
			break;
		case 2000: // ������
			obj = new Belial();
			break;
		case 514: // �� ����
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_LEFT);
			break;
		case 515: // �� ������
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_RIGHT);
			break;
		case 516: // �� ����
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_UP);
			break;
		case 517: // �� �Ʒ���
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_DOWN);
			break;
		case 2500: // ���� ������
			obj = new MonsterSpawner();
			break;
		case 2502: // �Ƚ� ������
			obj = new PixieSpawner();
			break;
		case 2503: // ���� ������
			obj = new TreasureSpawner();
			break;
		case 10 : // ���� ����
			obj = new Shop();
			break;
		case 12 : // �� �� �Ĵ� ���� ����
			obj = new Restaurant();
			break;
		case 0 : // ��Ż
			obj = new Portal();
			break;
		case 2 : // ��������
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_LEGENDARY);
			break;
		case 3 : // �������
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_BLUE);
			break;
		case 4: // ȸ������
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_GRAY);
			break;
		case 5: // ��������
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_BROWN);
			break;
		case 6: // �ݻ�����
			obj = new Treasure();
			dynamic_cast<Treasure*>(obj)->SetTreasureType(TREASURETYPE::TST_GOLD);
			break;
		case 7: // ���� �������� ��
			obj = new StageDoor();
			break;
			
		case 524: // ����
			obj = new Coin();
			break;

		case 2501: // ���� - ���� ��Ż
			obj = new WormVillage();
			break;

		case 13: // ���� �Ƚ�
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::SMALL);
			break;

		case 14: // �߰� �Ƚ�
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::MIDDLE);
			break;

		case 15: // ū �Ƚ�
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::LARGE);
			break;

		case 16: // �ſ� ū �Ƚ�
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::XLARGE);
			break;

		case 17: // �ſ� ū �Ƚ�
			obj = new HpPixie();
			dynamic_cast<HpPixie*>(obj)->SetPixType(PIXIETYPE::GREEN);
			break;

		case 100 : // ū �ڽ�
			obj = new Box();
			dynamic_cast<Box*>(obj)->SetBoxType(BOXTYPE::BOX_BIGBOX);
			dynamic_cast<Box*>(obj)->SetParticle();
			break;
		case 101: // ���� �ڽ�
			obj = new Box();
			dynamic_cast<Box*>(obj)->SetBoxType(BOXTYPE::BOX_SMALLBOX);
			dynamic_cast<Box*>(obj)->SetParticle();
			break;
		case 102: // ��ũ��
			obj = new Box();
			dynamic_cast<Box*>(obj)->SetBoxType(BOXTYPE::BOX_ORC);
			dynamic_cast<Box*>(obj)->SetParticle();
			break;
		case 5000:
			obj = new BelialDie();
			break;
		default:
			obj = new Object();
			break;
		}

		obj->init(
			stoi(objData[i][0]),
			objData[i][1],
			type,
			vector<string>{objData[i][3], objData[i][4], objData[i][5] }
		);

		if (obj->GetType() == OT_OBSTACLE)
			obj->SetRenderIndex(false);

		_mObjectData[stoi(objData[i][0])] = obj;
	}

	// UIBrushTool�� ��ġ�ϱ� ���� mapObject ������ ��Ʈ
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

void DataManager::GetItemData()
{
	vector<vector<string>> itemData = CSVMANAGER->csvLoad("Data/ItemData.csv");

	for (int i = 0; i < itemData.size(); i++)
	{
		if (i == 0) _itemMinId = stoi(itemData[i][0]);
		if (i == itemData.size() - 1) _itemMaxId = stoi(itemData[i][0]);

		Item* item;
		switch (stoi(itemData[i][0]))
		{
		case 4000: // ���� ������
			item = new DemonSword();
			break;
		case 4001: // ����Ʈ
			item = new Colt();
			break;
		case 4005: // �Ҹ���������
			item = new BloodOfSrobeo();
			break;
		case 4015: // ������ �ູ
			item = new BlessOfSage();
			break;
		default:
			item = new Item();
			break;
		}

		// ������ Ÿ��
		ITEMTYPE itemType = ITEMTYPE::IT_NOTHING;
		if (itemData[i][1] == "�Ѽչ���") itemType = ITEMTYPE::IT_WEAPON_ONEHAND;
		else if (itemData[i][1] == "�μչ���") itemType = ITEMTYPE::IT_WEAPON_TWOHAND;
		else if (itemData[i][1] == "���깫��") itemType = ITEMTYPE::IT_SUBWEAPON;
		else if (itemData[i][1] == "�Ǽ�����") itemType = ITEMTYPE::IT_ACCESORRY;
		else itemType = ITEMTYPE::IT_NOTHING;

		// ���� Ÿ��
		WEAPONTYPE weaponType = WEAPONTYPE::WT_NOWEAPON;
		if (itemData[i][2] == "����") weaponType = WEAPONTYPE::WT_NEAR;
		else if (itemData[i][2] == "���Ÿ�") weaponType = WEAPONTYPE::WT_RANGE;
		else if (itemData[i][2] == "������") weaponType = WEAPONTYPE::WT_CHARGE;
		else if (itemData[i][2] == "â") weaponType = WEAPONTYPE::WT_SPEAR;
		else if (itemData[i][2] == "����") weaponType = WEAPONTYPE::WT_PISTOL;
		else if (itemData[i][2] == "īŸ��") weaponType = WEAPONTYPE::WT_KATANA;
		else weaponType = WEAPONTYPE::WT_NOWEAPON;

		ITEMCLASS itemClass = ITEMCLASS::IC_NORMAL;
		if (itemData[i][6] == "�Ϲ�") itemClass = ITEMCLASS::IC_NORMAL;
		else if (itemData[i][6] == "���") itemClass = ITEMCLASS::IC_ADVANCED;
		else if (itemData[i][6] == "���") itemClass = ITEMCLASS::IC_RARE;
		else if (itemData[i][6] == "����") itemClass = ITEMCLASS::IC_LEGENDARY;

		Skill* skill;
		switch (stoi(itemData[i][3]))
		{
			// �������� ��ų �߰� (ID�� ����)
		default :
			skill = nullptr;
			break;
		}

		Bullet* bullet;
		switch (stoi(itemData[i][14]))
		{
			// �������� �Ҹ� �߰� (ID�� ����) 
		default :
			bullet = nullptr;
			break;
		}

		item->init(stoi(itemData[i][0]), itemType, weaponType, skill,
			itemData[i][4], itemData[i][5], itemClass, stof(itemData[i][7]), stof(itemData[i][8]),
			stof(itemData[i][9]), stoi(itemData[i][10]), stoi(itemData[i][11]),
			stoi(itemData[i][12]), stof(itemData[i][13]), bullet, stof(itemData[i][15]), stoi(itemData[i][16]),
			stoi(itemData[i][17]), vector<string>{itemData[i][18], itemData[i][19], itemData[i][20]}, itemData[i][21], itemData[i][22]
		);

		for (int j = 0; j < 3; j++)
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

Item* DataManager::GetItemById(int id)
{
	Item* rtnItem;
	switch (id)
	{
	case 4000 : // ���� ������
		return new DemonSword (*dynamic_cast<DemonSword*>(_mMapItemData[id]));
	case 4001 :
		return new Colt(*dynamic_cast<Colt*>(_mMapItemData[id]));
	case 4005: // �Ҹ���������
		return new BloodOfSrobeo(*dynamic_cast<BloodOfSrobeo*>(_mMapItemData[id]));
	case 4015: // ������ �ູ
		return new BlessOfSage(*dynamic_cast<BlessOfSage*>(_mMapItemData[id]));
	default:
		return _mMapItemData[id];
	}
}

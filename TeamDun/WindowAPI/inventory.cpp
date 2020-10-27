#include "stdafx.h"
#include "inventory.h"
#include "player.h"

HRESULT Inventory::init()
{
	_InvenFrame = UIMANAGER->GetGameFrame()->GetChild("InventoryFrame");
	_shopFrame = UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase");
	_swapFrame = UIMANAGER->GetGameFrame()->GetChild("swapContainer");
	_trashFrame = UIMANAGER->GetGameFrame()->GetChild("CheckTrash");
	_invenFullTextOn = false;
	_invenFullTextTimer = 0;

	_p = ENTITYMANAGER->getPlayer();
	return S_OK;
}

void Inventory::update()
{
	CheckInvenText();

	if (_InvenFrame->GetIsViewing())
	{
		if (_trashFrame->GetIsViewing())
		{
			ThrowingOutTrash();
		}

		else
		{
			UpdateMoney();
			EquipItem();
			UnEquipItem();
			ShowToolTip();
			DragItemStart();
			DragItem();
		}
	}
}

void Inventory::render(HDC hdc)
{
}

void Inventory::release()
{
}

void Inventory::UpdateMoney()
{
	dynamic_cast<UIText*>(_InvenFrame->GetChild("moneyText"))->SetText(to_string(_p->GetMoney()));
}

// �������� ��������
void Inventory::ThrowingOutTrash()
{
	if (INPUT->GetIsLButtonClicked())
	{
		if (PtInRect(&_trashFrame->GetChild("yes")->GetRect(), _ptMouse))
		{
			_vInvenItems.erase(_vInvenItems.begin() + _dragIndex);
			EraseDragInfor();
			ReloadUIImages();
			_trashFrame->SetIsViewing(false);
		}

		else if (PtInRect(&_trashFrame->GetChild("no")->GetRect(), _ptMouse))
		{
			EraseDragInfor();
			_trashFrame->SetIsViewing(false);
		}
	}
}

// EquipItemPos�� ���� �˻簡 �Ϸ�� ��Ȳ���� ���Ǵ� ��ġ�� ���� �Լ��̴�.
void Inventory::EquipItemPos(int pos, Item* item, int index, bool isUsed)
{
	_vInvenItems.erase(_vInvenItems.begin() + index);
	if(isUsed) item->EquipUnEquipStatus(true);

	Item* item1 = nullptr;
	Item* item2 = nullptr;

	switch (pos)
	{
	case 0: // WEAPON 1
		if (item->GetitemType() == ITEMTYPE::IT_WEAPON_ONEHAND)
		{
			item1 = _p->SetWeapon(0, item);
			if (item1 != nullptr)
			{
				AddItem(item1);
				if(isUsed) item1->EquipUnEquipStatus(false);
			}
		}

		else if (item->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)
		{
			item1 = _p->SetWeapon(0, item);
			if (item1 != nullptr)
			{
				AddItem(item1);
				if (isUsed) item1->EquipUnEquipStatus(false);
			}
			item2 = _p->SetSubWeapon(0, nullptr);
			if (item2 != nullptr)
			{
				AddItem(item2);
				if (isUsed) item2->EquipUnEquipStatus(false);
			}
		}
		break;

	case 1: // WEAPON 2
		if (item->GetitemType() == ITEMTYPE::IT_WEAPON_ONEHAND)
		{
			item1 = _p->SetWeapon(1, item);
			if (item1 != nullptr)
			{
				AddItem(item1);
				if (isUsed) item1->EquipUnEquipStatus(false);
			}
		}

		else if (item->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)
		{
			item1 = _p->SetWeapon(1, item);
			if (item1 != nullptr)
			{
				AddItem(item1);
				if (isUsed) item1->EquipUnEquipStatus(false);
			}
			item2 = _p->SetSubWeapon(1, nullptr);
			if (item2 != nullptr)
			{
				AddItem(item2);
				if (isUsed) item2->EquipUnEquipStatus(false);
			}
		}
		break;

	case 2: // SUBWEAPON 1
		if (item->GetitemType() == ITEMTYPE::IT_SUBWEAPON)
		{
			item1 = _p->SetSubWeapon(0, item);
			if (item1 != nullptr)
			{
				AddItem(item1);
				if (isUsed) item1->EquipUnEquipStatus(false);
			}
		}
		break;

	case 3: // SUBWEAPON 2
		if (item->GetitemType() == ITEMTYPE::IT_SUBWEAPON)
		{
			item1 = _p->SetSubWeapon(1, item);
			if (item1 != nullptr)
			{
				AddItem(item1);
				if (isUsed) item1->EquipUnEquipStatus(false);
			}
		}
		break;

	default:
		// 4���� �Ǽ����� n
		if (item->GetitemType() == ITEMTYPE::IT_ACCESORRY)
		{
			if (_p->GetVAccessories().size() <= pos - 4) _p->GetVAccessories().push_back(item);

			else
			{
				item1 = _p->SetVAccessory(pos - 4, item);
				if (item1 != nullptr)
				{
					AddItem(item1);
					item1->EquipUnEquipStatus(false);
				}
			}
		}
		break;
	}
}

void Inventory::DragItemStart()
{
	if (_dragItem == nullptr && INPUT->GetKey(VK_LBUTTON))
	{
		if (!_shopFrame->GetIsViewing())
		{
			for (int i = 0; i < _vInvenItems.size(); i++)
			{
				UIFrame* curFrame = _InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame");
				if (PtInRect(&curFrame->GetRect(), _ptMouse))
				{
					_dragItem = _vInvenItems[i];
					_dragIndex = i;

					UIMANAGER->GetGameFrame()->GetChild("itemMouseTracker")->SetImage(_dragItem->GetInvenImage());
					UIMANAGER->GetGameFrame()->GetChild("itemMouseTracker")->SetIsViewing(true);
				}
			}
		}
	}
}

/// <summary>
/// �巡���Ͽ� �������� ���� / ����
/// </summary>
void Inventory::DragItem()
{
	if (_dragItem != nullptr)
	{
		if (INPUT->GetIsRButtonClicked()) // ��Ŭ���� ����
		{
			_dragIndex = -1;
			_dragItem = nullptr;
		}

		if (INPUT->GetIsLButtonUp()) // ���� �� üũ
		{
			UIMANAGER->GetGameFrame()->GetChild("itemMouseTracker")->SetIsViewing(false);
			
			if (PtInRect(&_InvenFrame->GetRect(), _ptMouse)) // �κ� ������ ���̶��
			{
				SOUNDMANAGER->play("����_���������� (2)");
				if (PtInRect(&_InvenFrame->GetChild("curWeapon_1")->GetRect(), _ptMouse) && (_dragItem->GetitemType() == ITEMTYPE::IT_WEAPON_ONEHAND || _dragItem->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND))
				{ // ���� 1
					if (_dragItem->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND && (_p->GetWeapon(0) != nullptr && _vInvenItems.size() >= 15))
					{ // ������
						OnInvenFullText();
					}
					else
						EquipItemPos(0, _vInvenItems[_dragIndex], _dragIndex, _p->GetSelectedWeaponIdx() == 0);
				}

				else if (PtInRect(&_InvenFrame->GetChild("curWeapon_2")-> GetRect(), _ptMouse) && (_dragItem->GetitemType() == ITEMTYPE::IT_WEAPON_ONEHAND || _dragItem->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND))
				{ // ���� 2
					if (_dragItem->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND && (_p->GetWeapon(1) != nullptr && _vInvenItems.size() >= 15))
					{ // ������
						OnInvenFullText();
					}
					else
						EquipItemPos(1, _vInvenItems[_dragIndex], _dragIndex, _p->GetSelectedWeaponIdx() == 1);
				}
				
				else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_1")->GetRect(), _ptMouse) && (_dragItem->GetitemType() == ITEMTYPE::IT_SUBWEAPON))
				{ // ���깫�� 1
					if ((_p->GetWeapon(0) == nullptr || (_p->GetWeapon(0)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)))
					{ // ���깫�⸦ �� �� ���� ����
						OnInvenFullText();
					}

					else if (_p->GetWeapon(0) == nullptr)
					{
						OnInvenFullText();
					}
					else
					{
						if (_p->GetWeapon(0) != nullptr && _p->GetWeapon(0)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND)
						{ // ���� 0�� �ְ� �μչ��Ⱑ �ƴϸ� ��������� �ִٸ�
							EquipItemPos(2, _vInvenItems[_dragIndex], _dragIndex, _p->GetSelectedWeaponIdx() == 0);
						}
					}
				}
				
				else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_2")->GetRect(), _ptMouse) && (_dragItem->GetitemType() == ITEMTYPE::IT_SUBWEAPON))
				{ // ���깫�� 2
					if ((_p->GetWeapon(1) == nullptr || (_p->GetWeapon(1)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)))
					{ // ���깫�⸦ �� �� ���� ����
						OnInvenFullText();
					}

					else if (_p->GetWeapon(1) == nullptr)
					{
						OnInvenFullText();
					}
					else
					{
						if (_p->GetWeapon(1) != nullptr && _p->GetWeapon(1)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND)
						{ // ���� 0�� �ְ� �μչ��Ⱑ �ƴϸ� ��������� �ִٸ�
							EquipItemPos(3, _vInvenItems[_dragIndex], _dragIndex, _p->GetSelectedWeaponIdx() == 1);
						}
					}
				}

				else
				{
					for (int i = 0; i < _p->GetAccesoryCount(); i++)
					{
						if (PtInRect(&_InvenFrame->GetChild("accesoryFrame")->GetChild("accesoryFrame_" + to_string(i))->GetRect(), _ptMouse) && (_dragItem->GetitemType() == ITEMTYPE::IT_ACCESORRY))
						{
							bool equalCheck = false; // ���� ������ �ִ��� üũ
							for (int j= 0; j < _p->GetVAccessories().size(); j++)
							{
								if (_p->GetAccessory(j)->GetId() == _dragItem->GetId())
								{
									OnInvenEqualText();
									equalCheck = true;
									break;
								}
							}

							if (equalCheck) break; // ������ �ִٸ� break
							else EquipItemPos(4+i, _vInvenItems[_dragIndex], _dragIndex, true); // �ƴϸ� ����
							break;
						}
					}
				}

				_dragItem = nullptr;
				EraseDragInfor();
			}

			else
			{
				// ������
				SOUNDMANAGER->play("����_�۹�����");
				_trashFrame->SetIsViewing(true);
			}

			ReloadUIImages();
		}

		else // ������ �̵�
		{
			UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("itemMouseTracker");
			frame->MoveFrameChild((_ptMouse.x) - frame->GetX(), (_ptMouse.y - frame->GetY()));
		}
	}
}

void Inventory::EquipItem()
{
	if (INPUT->GetIsRButtonClicked())
	{
		if (!_shopFrame->GetIsViewing())
		{
			for (int i = 0; i < 15; i++)
			{
				UIFrame* curFrame = _InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame");

				if (PtInRect(&curFrame->GetRect(), _ptMouse))
				{
					if (_vInvenItems.size() > i)
					{
						SOUNDMANAGER->play("����_���������� (2)");
						Item* item = _vInvenItems[i];
						//item->EquipUnEquipStatus(true);

						switch (item->GetitemType())
						{
						case ITEMTYPE::IT_WEAPON_ONEHAND:
							if (_p->GetWeapon(0) == nullptr)
							{ // 0���� ����
								EquipItemPos(0, item, i, _p->GetSelectedWeaponIdx() == 0);
							}
							else if (_p->GetWeapon(1) == nullptr)
							{ // 1���� ����
								EquipItemPos(1, item, i, _p->GetSelectedWeaponIdx() == 1);
							}
							else
							{ // 0���� switch
								EquipItemPos(0, item, i, _p->GetSelectedWeaponIdx() == 0);
							}
							break;

						case ITEMTYPE::IT_WEAPON_TWOHAND:
							if (_p->GetWeapon(0) == nullptr)
							{ // 0���� ����
								EquipItemPos(0, item, i, _p->GetSelectedWeaponIdx() == 0);
							}

							else if (_p->GetWeapon(1) == nullptr)
							{ // 1���� ����
								EquipItemPos(1, item, 1, _p->GetSelectedWeaponIdx() == 1);
							}

							else if (_vInvenItems.size() >= 15)
							{ // ������
								OnInvenFullText();
							}
						
							else
							{ // 0���� switch
								EquipItemPos(0, item, i, _p->GetSelectedWeaponIdx() == 0);
							}
							break;

						case ITEMTYPE::IT_SUBWEAPON:

							if ((_p->GetWeapon(0) == nullptr || (_p->GetWeapon(0)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)) &&
								(_p->GetWeapon(1) == nullptr || (_p->GetWeapon(1)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)))
							{ // ���� �� ���깫�⸦ �� �� ���� ���¶��
								OnInvenFullText();
							}

							else if (_p->GetWeapon(0) != nullptr && _p->GetWeapon(0)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(0) == nullptr)
							{ // ���� 0�� �ְ� �μչ��Ⱑ �ƴϸ�, ��������� ���ٸ�
								EquipItemPos(2, item, i, _p->GetSelectedWeaponIdx() == 0);
							}

							else if (_p->GetWeapon(1) != nullptr && _p->GetWeapon(1)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(1) == nullptr)
							{ // ���� 1�� �ְ� �μչ��Ⱑ �ƴϸ�, ��������� ���ٸ�
								EquipItemPos(3, item, i, _p->GetSelectedWeaponIdx() == 1);
							}

							else
							{
								if (_p->GetWeapon(0) != nullptr && _p->GetWeapon(0)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND)
								{ // ���� 0�� �ְ� �μչ��Ⱑ �ƴϸ� ��������� �ִٸ�
									EquipItemPos(2, item, i, _p->GetSelectedWeaponIdx() == 0);
								}
								else
								{ // ���� 0�� ���ų�, �μչ�����
									OnInvenFullText();
								}
							}
							break;

						case ITEMTYPE::IT_ACCESORRY:
							bool equalCheck = false; // ���� ������ �ִ��� üũ
							for (int i = 0; i < _p->GetVAccessories().size(); i++)
							{
								if (_p->GetAccessory(i)->GetId() == item->GetId())
								{
									OnInvenEqualText();
									equalCheck = true;
									break;
								}
							}

							if (equalCheck) break; // ������ �ִٸ� break

							if (_p->GetVAccessories().size() == _p->GetAccesoryCount())
							{	// ����� �� á�ٸ� ���� ����
								OnInvenFullText();
							}

							else
							{	// �� �ڿ� �Ǽ����� ����
								EquipItemPos(_p->GetVAccessories().size() + 4, item, i, true);
							}
							break;
						}

						ReloadUIImages();
						break;
					}
				}
			}
		}
	}
}

void Inventory::SwitchItem(int num, Item* item, int index)
{
	Item* getItem;
	if (num == 0)
	{
		getItem = _p->GetWeapon(0);
		_p->SetWeapon(0, item);
		_vInvenItems[index] = getItem;
	}

	else if (num == 1)
	{
		getItem = _p->GetSubWeapon(0);
		_p->SetSubWeapon(0, item);
		_vInvenItems[index] = getItem;
	}

	else if (num == 2)
	{
		getItem = _p->GetWeapon(1);
		_p->SetWeapon(1, item);
		_vInvenItems[index] = getItem;
	}

	else if (num == 3)
	{
		getItem = _p->GetSubWeapon(1);
		_p->SetSubWeapon(1, item);
		_vInvenItems[index] = getItem;
	}

	else
	{
		getItem = _p->GetAccessory(num - 4);
		_p->SetVAccessory(num - 4, item);
		_vInvenItems[index] = getItem;
	}
}

void Inventory::UnEquipItem()
{
	if (INPUT->GetIsRButtonClicked())
	{
		if (!_shopFrame->GetIsViewing())
		{
			if (PtInRect(&_InvenFrame->GetChild("curWeapon_1")->GetRect(), _ptMouse) && _p->GetWeapon(0) != nullptr)
			{
				SOUNDMANAGER->play("����_���������� (2)");

				if ((_vInvenItems.size() > 13 && _p->GetWeapon(0)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(0) != nullptr) || _vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetWeapon(0));
					if (_p->GetSelectedWeaponIdx() == 0)	_p->GetWeapon(0)->EquipUnEquipStatus(false);
					_p->SetWeapon(0, nullptr);
					if (_p->GetSubWeapon(0) != nullptr)
					{
						AddItem(_p->GetSubWeapon(0));
						if (_p->GetSelectedWeaponIdx() == 0) _p->GetSubWeapon(0)->EquipUnEquipStatus(false);
						_p->SetSubWeapon(0, nullptr);
					}
				}
			}

			else if (PtInRect(&_InvenFrame->GetChild("curWeapon_2")->GetRect(), _ptMouse) && _p->GetWeapon(1) != nullptr)
			{
				if ((_vInvenItems.size() > 13 && _p->GetWeapon(1)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(1) != nullptr) || _vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetWeapon(1));
					if (_p->GetSelectedWeaponIdx() == 1) _p->GetWeapon(1)->EquipUnEquipStatus(false);
					_p->SetWeapon(1, nullptr);
					if (_p->GetSubWeapon(1) != nullptr)
					{
						AddItem(_p->GetSubWeapon(1));
						if (_p->GetSelectedWeaponIdx() == 1) _p->GetSubWeapon(1)->EquipUnEquipStatus(false);
						_p->SetSubWeapon(1, nullptr);
					}
				}
			}

			else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_1")->GetRect(), _ptMouse) && _p->GetSubWeapon(0) != nullptr)
			{
				if (_vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetSubWeapon(0));
					if (_p->GetSelectedWeaponIdx() == 0) _p->GetSubWeapon(0)->EquipUnEquipStatus(false);
					_p->SetSubWeapon(0, nullptr);
				}
			}

			else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_2")->GetRect(), _ptMouse) && _p->GetSubWeapon(1) != nullptr)
			{
				if (_vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetSubWeapon(1));
					if (_p->GetSelectedWeaponIdx() == 1) _p->GetSubWeapon(1)->EquipUnEquipStatus(false);
					_p->SetSubWeapon(1, nullptr);
				}
			}

			else
			{
				for (int i = 0; i < _p->GetAccesoryCount(); i++)
				{
					if (PtInRect(&_InvenFrame->GetChild("accesoryFrame")->GetChild("accesoryFrame_" + to_string(i))->GetRect(), _ptMouse) && _p->GetVAccessories().size() > i)
					{
						if (_vInvenItems.size() > 14)
						{
							OnInvenFullText();
						}

						else
						{
							AddItem(_p->GetAccessory(i));
							_p->GetAccessory(i)->EquipUnEquipStatus(false);
							_p->GetVAccessories().erase(_p->GetVAccessories().begin() + i);
						}
						break;
					}
				}
			}

			ReloadUIImages();
		}
	}
}

bool Inventory::AddItem(Item* item)
{
	if (_vInvenItems.size() < 15)
	{
		_vInvenItems.push_back(item);
		ReloadUIImages();
		return true;
	}

	return false;
}

void Inventory::SetInventoryAccesoryUI()
{
	Player* p = ENTITYMANAGER->getPlayer();

	_InvenFrame->GetChild("accesoryFrame")->GetVChildFrames().clear();

	for (int i = 0; i < _p->GetAccesoryCount(); i++)
	{
		UIFrame* accesory = new UIFrame();
		accesory->init("accesoryFrame_" + to_string(i), (i * (IMAGEMANAGER->findImage("accessory")->getWidth() + 8)) - (_p->GetAccesoryCount() - 4) * (IMAGEMANAGER->findImage("accessory")->getWidth() / 2 + 4)
			, 0, IMAGEMANAGER->findImage("accessory")->getWidth(), IMAGEMANAGER->findImage("accessory")->getHeight(), "accessory");
		_InvenFrame->GetChild("accesoryFrame")->AddFrame(accesory);

		UIFrame* itemImageFrame = new UIFrame();
		itemImageFrame->init("itemImageFrame", 0, 0, 57, 57, "");
		accesory->AddFrame(itemImageFrame);
	}
}

void Inventory::ReloadUIImages()
{
	Player* p = ENTITYMANAGER->getPlayer();
	_swapFrame->GetChild("weapon1")->GetVChildFrames().clear();
	_swapFrame->GetChild("weapon2")->GetVChildFrames().clear();

	UIFrame* weapon1Swap = new UIFrame();
	_InvenFrame->GetChild("curWeapon_1")->SetImage(nullptr);
	if (p->GetWeapon(0) != nullptr)
	{
		_InvenFrame->GetChild("curWeapon_1")->SetImage(p->GetWeapon(0)->GetInvenImage());
		weapon1Swap->init("image",
			25 - p->GetWeapon(0)->GetDropImage()->getFrameWidth() / 2 * (p->GetWeapon(0)->GetRenderScale() - 1),
			15 - p->GetWeapon(0)->GetDropImage()->getFrameHeight() / 2 * (p->GetWeapon(0)->GetRenderScale() - 1),
			0, 0,
			p->GetWeapon(0)->GetDropImageName(),
			p->GetWeapon(0)->GetRenderScale(),
			p->GetWeapon(0)->GetRenderScale()
		);
	}
	else
	{
		weapon1Swap->init("image", 0, 0, 0, 0, "");
	}

	_swapFrame->GetChild("weapon1")->AddFrame(weapon1Swap);

	UIFrame* weapon2Swap = new UIFrame();
	_InvenFrame->GetChild("curWeapon_2")->SetImage(nullptr);
	if (p->GetWeapon(1) != nullptr)
	{
		_InvenFrame->GetChild("curWeapon_2")->SetImage(p->GetWeapon(1)->GetInvenImage());
		weapon2Swap->init("image",
			25 - p->GetWeapon(1)->GetDropImage()->getFrameWidth() / 2 * (p->GetWeapon(1)->GetRenderScale() - 1),
			15 - p->GetWeapon(1)->GetDropImage()->getFrameHeight() / 2 * (p->GetWeapon(1)->GetRenderScale() - 1),
			p->GetWeapon(1)->GetDropImage()->getFrameWidth() * p->GetWeapon(1)->GetRenderScale(),
			p->GetWeapon(1)->GetDropImage()->getFrameHeight() * p->GetWeapon(1)->GetRenderScale(),
			p->GetWeapon(1)->GetDropImageName(),
			p->GetWeapon(1)->GetRenderScale(),
			p->GetWeapon(1)->GetRenderScale()
		);
	}
	else
	{
		weapon2Swap->init("image", 0, 0, 0, 0, "");
	}

	_swapFrame->GetChild("weapon2")->AddFrame(weapon2Swap);

	
	_InvenFrame->GetChild("curWeaponSub_1")->SetImage(nullptr);
	if (p->GetSubWeapon(0) != nullptr) _InvenFrame->GetChild("curWeaponSub_1")->SetImage(p->GetSubWeapon(0)->GetInvenImage());
	_InvenFrame->GetChild("curWeaponSub_2")->SetImage(nullptr);
	if (p->GetSubWeapon(1) != nullptr) _InvenFrame->GetChild("curWeaponSub_2")->SetImage(p->GetSubWeapon(1)->GetInvenImage());
	

	for (int i = 0; i < p->GetAccesoryCount(); i++)
	{
		_InvenFrame->GetChild("accesoryFrame")->GetChild("accesoryFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(nullptr);
		if (p->GetVAccessories().size() > i && p->GetAccessory(i) != nullptr)
			_InvenFrame->GetChild("accesoryFrame")->GetChild("accesoryFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(p->GetAccessory(i)->GetInvenImage());
	}

	for (int i = 0; i < 15; i++)
	{
		_InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(nullptr);
		if (i < _vInvenItems.size())
			_InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(_vInvenItems[i]->GetInvenImage());
	}
}

void Inventory::OnInvenFullText()
{
	_invenFullTextOn = true;
	_invenFullTextTimer = 0;
	UIMANAGER->GetGameFrame()->GetChild("isFullText")->SetIsViewing(true);
}

void Inventory::OnInvenEqualText()
{
	_invenEqualTextOn = true;
	_invenEqualTextTimer = 0;
	UIMANAGER->GetGameFrame()->GetChild("isEqualText")->SetIsViewing(true);
}

void Inventory::CheckInvenText()
{
	if (_invenFullTextOn)
	{
		_invenFullTextTimer++;
		if (_invenFullTextTimer > 25)
		{
			UIMANAGER->GetGameFrame()->GetChild("isFullText")->SetIsViewing(false);
			_invenFullTextTimer = 0;
			_invenFullTextOn = false;
		}
	}

	if (_invenEqualTextOn)
	{
		_invenEqualTextTimer++;
		if (_invenEqualTextTimer > 25)
		{
			UIMANAGER->GetGameFrame()->GetChild("isEqualText")->SetIsViewing(false);
			_invenEqualTextTimer = 0;
			_invenEqualTextOn = false;
		}
	}
}

void Inventory::SwitchWeapon(int selectedWeapon)
{
	if (selectedWeapon == 0)	//���ù��Ⱑ 0���϶�
	{
		if (_p->GetWeapon(0) != nullptr)	//���ݹ��Ⱑ 0���� �ƴ�
			_p->GetWeapon(0)->EquipUnEquipStatus(true);
		if (_p->GetSubWeapon(0) != nullptr)
			_p->GetSubWeapon(0)->EquipUnEquipStatus(true);
		if (_p->GetWeapon(1) != nullptr)
			_p->GetWeapon(1)->EquipUnEquipStatus(false);
		if (_p->GetSubWeapon(1) != nullptr)
			_p->GetSubWeapon(1)->EquipUnEquipStatus(false);
	}

	else
	{
		if (_p->GetWeapon(0) != nullptr)
			_p->GetWeapon(0)->EquipUnEquipStatus(false);
		if (_p->GetSubWeapon(0) != nullptr)
			_p->GetSubWeapon(0)->EquipUnEquipStatus(false);
		if (_p->GetWeapon(1) != nullptr)
			_p->GetWeapon(1)->EquipUnEquipStatus(true);
		if (_p->GetSubWeapon(1) != nullptr)
			_p->GetSubWeapon(1)->EquipUnEquipStatus(true);
	}
}

void Inventory::InitToolTipItem(Item* item)
{
	_curToolTipItem = item;

	UIImage* uiToolTip = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->GetChild("itemToolTip"));
	uiToolTip->GetVChildFrames().clear();

	// �̸� ��
	int nameR = 255, nameG = 255, nameB = 255;
	switch (item->GetItemClass())
	{
	case ITEMCLASS::IC_NORMAL: nameR = 255, nameG = 255, nameB = 255; break;
	case ITEMCLASS::IC_ADVANCED: nameR = 112, nameG = 146, nameB = 190; break;
	case ITEMCLASS::IC_RARE: nameR = 232, nameG = 239, nameB = 90; break;
	case ITEMCLASS::IC_LEGENDARY: nameR = 237, nameG = 9, nameB = 138; break;
	}

	// �̸�
	UIText* itemName = new UIText();
	itemName->init("itemName", 0, 10, 400, 200, item->GetName(), FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(nameR, nameG, nameB));
	uiToolTip->AddFrame(itemName);

	// �̹��� ������
	UIFrame* imgFrame = new UIFrame();
	imgFrame->init("imgFrame", 10, 50, IMAGEMANAGER->findImage("IconWhite")->getWidth(), IMAGEMANAGER->findImage("IconWhite")->getHeight(), "IconWhite");
	uiToolTip->AddFrame(imgFrame);

	// ������ �̹���
	UIFrame* itemImage = new UIFrame();
	itemImage->init("itemImage", 0, 0, item->GetInvenImage()->getWidth(), item->GetInvenImage()->getHeight(), item->GetInvenImageName());
	imgFrame->AddFrame(itemImage);

	// ���ݷ�
	if (item->GetMinAtk() != 0 && item->GetMaxAtk() != 0)
	{
		UIText* attack = new UIText();
		attack->init("attack", 75, 50, 80, 80, "���ݷ� : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(attack);

		UIText* attackValue = new UIText();
		attackValue->init("attackValue", 155, 50, 200, 80, to_string_with_precision(item->GetMinAtk(), 0) + " ~ " + to_string_with_precision(item->GetMaxAtk(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(attackValue);
	}

	// ���ݼӵ�
	if (item->GetAtkSpeed() != 0)
	{
		UIText* attackSpd = new UIText();
		attackSpd->init("attackSpd", 75, 70, 200, 80, "�ʴ� ���� Ƚ�� : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(attackSpd);

		UIText* attackSpdValue = new UIText();
		attackSpdValue->init("attackSpdValue", 225, 70, 200, 80, to_string_with_precision(item->GetAtkSpeed(), 2), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(attackSpdValue);
	}

	// ����
	if (item->GetDefence() != 0)
	{
		UIText* def = new UIText();
		def->init("def", 75, 90, 200, 80, "���� : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(def);

		UIText* defValue = new UIText();
		defValue->init("defValue", 155, 90, 200, 80, to_string_with_precision(item->GetDefence(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(defValue);
	}

	// �߰� �ɼ�
	for (int i = 0; i < item->GetSubOptions().size(); i++)
	{
		SubOption* option = item->GetSubOptions()[i];

		int optionR = 255, optionG = 255, optionB = 255;
		if (option->_optionPower < 0) optionR = 255, optionG = 0, optionB = 0;
		if (option->_optionPower > 0) optionR = 0, optionG = 255, optionB = 0;

		UIText* startText = new UIText();
		startText->init("��" + to_string(i), 15, 120 + i * 15, 30, 30, "��", FONT::PIX, WORDSIZE::WS_SMALLEST);
		uiToolTip->AddFrame(startText);

		UIText* descript = new UIText();
		descript->init("descript" + to_string(i), 30, 122 + i * 15, 370, 30, OptionString(option), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT,
			RGB(optionR, optionG, optionB));
		uiToolTip->AddFrame(descript);
	}

	_toolTipFinalY = item->GetSubOptions().size() * 20 + 122;

	// ������ Ŭ����
	string itemClassString = "�Ϲ� ������";
	switch (item->GetItemClass())
	{
	case ITEMCLASS::IC_NORMAL: itemClassString = "�Ϲ� ������"; break;
	case ITEMCLASS::IC_ADVANCED: itemClassString = "��� ������";  break;
	case ITEMCLASS::IC_RARE: itemClassString = "��� ������"; break;
	case ITEMCLASS::IC_LEGENDARY: itemClassString = "���� ������"; break;
	}

	UIText* itemClass = new UIText();
	itemClass->init("itemClass", 10, _toolTipFinalY + 5, 150, 30, itemClassString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(120, 120, 120));
	uiToolTip->AddFrame(itemClass);

	// ������ ����
	string itemKindString = "��չ���";
	switch (item->GetitemType())
	{
	case ITEMTYPE::IT_WEAPON_ONEHAND: itemKindString = "�Ѽչ���"; break;
	case ITEMTYPE::IT_WEAPON_TWOHAND: itemKindString = "��չ���"; break;
	case ITEMTYPE::IT_SUBWEAPON: itemKindString = "�������"; break;
	case ITEMTYPE::IT_ACCESORRY: itemKindString = "�Ǽ�����"; break;
	}

	UIText* itemKind = new UIText();
	itemKind->init("itemKind", 10, _toolTipFinalY + 20, 150, 30, itemKindString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(120, 120, 120));
	uiToolTip->AddFrame(itemKind);
	_toolTipFinalY += 15;

	// ���
	string weaponkindString = "";
	switch (item->GetWeaponType())
	{
	case WEAPONTYPE::WT_CHARGE: weaponkindString = "#������"; break;
	case WEAPONTYPE::WT_KATANA: weaponkindString = "#īŸ��"; break;
	case WEAPONTYPE::WT_PISTOL: weaponkindString = "#����"; break;
	case WEAPONTYPE::WT_SPEAR: weaponkindString = "#â"; break;
	}

	if (weaponkindString != "")
	{
		UIText* tag = new UIText();
		tag->init("tag", 10, _toolTipFinalY + 25, 100, 30, weaponkindString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(162, 210, 148));
		uiToolTip->AddFrame(tag);
		_toolTipFinalY += 20;
	}

	// ��ų
	if (item->GetSkill() != nullptr)
	{
		UIImage* skillFrame = new UIImage();
		skillFrame->init("skillFrame", 10, _toolTipFinalY + 25, 280, 55, "ToolTipSkillCover", false, 0, 0, 280 / 30.f, 55 / 30.f, 80);
		uiToolTip->AddFrame(skillFrame);
		UIFrame* skillImage = new UIFrame();
		skillImage->init("skillImage", 2, 2, 51, 51, item->GetSkill()->GetImageName(), 51.f / 57, 51.f / 57);
		skillFrame->AddFrame(skillImage);
		UIText* skillName = new UIText();
		skillName->init("skillName", 55, 2, 300, 80, item->GetSkill()->GetName(), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		skillFrame->AddFrame(skillName);
		UIText* skillDescription = new UIText();
		skillDescription->init("skillDescription", 55, 22, 220, 120, item->GetSkill()->GetDescription(), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT);
		skillFrame->AddFrame(skillDescription);
		UIText* skillCoolTime = new UIText();
		skillCoolTime->init("skillCoolTime", 257, 39, 60, 30, to_string_with_precision(item->GetSkill()->GetCoolTime()/60, 1), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_RIGHT, RGB(221, 173, 103));
		skillFrame->AddFrame(skillCoolTime);
		_toolTipFinalY += 45;
	}

	// ����
	UIText* description = new UIText();
	description->init("description", 10, _toolTipFinalY + 45, 350, 200, item->GetDescription(), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(208, 247, 252));
	uiToolTip->AddFrame(description);
	_toolTipFinalY += (item->GetDescription().length() / 22) * 10 + 70;

	if (_shopFrame->GetIsViewing())
	{
		UIFrame* moneyImg = new UIFrame();
		moneyImg->init("moneyImg", 352, _toolTipFinalY - 2, 19, 19, "moneyUI");
		uiToolTip->AddFrame(moneyImg);

		UIText* sellMoney = new UIText();
		sellMoney->init("sellMoney", 250, _toolTipFinalY, 100, 50, to_string_with_precision(item->GetSellPrice(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_RIGHT);
		uiToolTip->AddFrame(sellMoney);
	}

	_toolTipFinalY += 30;
	uiToolTip->SetScaleY(_toolTipFinalY / 100.f);
}

string Inventory::OptionString(SubOption* option)
{
	string optionResult = "";

	if (option->_optionPower != 0)
	{
		optionResult += (option->_optionPower >= 0 ? "+" : "") + to_string_with_precision(option->_optionPower, 0);

		switch (option->_optionId)
		{
		case POWER:
			optionResult += " ����";
			break;
		case ATKSPEED:
			optionResult += "% ���ݼӵ�";
			break;
		case DASHATK:
			optionResult += "% �뽬 ���ݷ�";
			break;
		case DEFENCE:
			optionResult += " ����";
			break;
		case BLOCK:
			optionResult += " ����";
			break;
		case CRITICALPERCENT:
			optionResult += " ũ��Ƽ��";
			break;
		case CRITICALDAMAGE:
			optionResult += " ũ��Ƽ�� ������";
			break;
		case MINDAMAGE:
			optionResult += " �ּ� ������";
			break;
		case MAXDAMAGE:
			optionResult += " �ִ� ������";
			break;
		case FINALDAMAGEPERCENT:
			optionResult += "% ���� ������";
			break;
		case FINALDAMAGE:
			optionResult += " ���� ������";
			break;
		case TOUGHNESS:
			optionResult += " ������";
			break;
		case TRUEDAMAGE:
			optionResult += " ���� ������";
			break;
		case MAXHP:
			optionResult += " �ִ� ü��";
			break;
		case MAXHPPERCENT:
			optionResult += "% �ִ� ü��";
			break;
		case EVADE:
			optionResult += " ȸ��";
			break;
		case MOVESPEED:
			optionResult += "% �̵��ӵ�";
			break;
		case JUMPPOWER:
			optionResult += " ������";
			break;
		case GOLDDROP:
			optionResult += "% ��� ���";
			break;
		case RELOADSPEED:
			optionResult += "% ������ �ӵ�";
			break;
		case DASHCOUNT:
			optionResult += " �뽬 Ƚ��";
			break;
		case ACCURACY:
			optionResult += " ���� ��Ȯ��";
			break;
		case FIREDAMAGE:
			optionResult += " ȭ�� ����";
			break;
		case ICEDAMAGE:
			optionResult += " �ñ� ����";
			break;
		case ELECDAMAGE:
			optionResult += " ���� ����";
			break;
		case POSIONDAMAGE:
			optionResult += " �ߵ� ����";
			break;
		case STUNDAMAGE:
			optionResult += " ���� ����";
		default:
			break;
		}
	}

	switch (option->_optionId)
	{
	case IMMUNEFIRE:
		optionResult += "ȭ�� �鿪";
		break;
	case IMMUNEICE:
		optionResult += "�ñ� �鿪";
		break;
	case IMMUNEELEC:
		optionResult += "���� �鿪";
		break;
	case IMMUNEPOSION:
		optionResult += "�ߵ� �鿪";
		break;
	case IMMUNESTUN:
		optionResult += "���� �鿪";
		break;
	case TOFIRE:
		optionResult += "ȭ�� �ο�";
		break;
	case TOICE:
		optionResult += "�ñ� �ο�";
		break;
	case TOELEC:
		optionResult += "���� �ο�";
		break;
	case TOPOSION:
		optionResult += "�ߵ� �ο�";
		break;
	case TOSTUN:
		optionResult += "���� �ο�";
	}

	if (option->_description != ".")
		optionResult += option->_description;

	return optionResult;
}

void Inventory::EraseDragInfor()
{
	_dragIndex = -1;
	_dragItem = nullptr;
}

void Inventory::ShowToolTip()
{
	Item* item = nullptr;
	bool isEquipped = true;

	UIImage* uiToolTip = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->GetChild("itemToolTip"));

	for (int i = 0; i < _vInvenItems.size(); i++)
	{
		UIFrame* curFrame = _InvenFrame->GetChild("itemFrame_" + to_string(i));
		if (PtInRect(&curFrame->GetRect(), _ptMouse))
		{
			item = _vInvenItems[i];
			isEquipped = false;
			break;
		}
	}

	for (int i = 0; i < _p->GetVAccessories().size(); i++)
	{
		UIFrame* curFrame = _InvenFrame->GetChild("accesoryFrame")->GetChild("accesoryFrame_" + to_string(i));
		if (PtInRect(&curFrame->GetRect(), _ptMouse))
		{
			item = _p->GetAccessory(i);
			break;
		}
	}
	if (PtInRect(&_InvenFrame->GetChild("curWeapon_1")->GetRect(), _ptMouse))
	{
		if (_p->GetWeapon(0) != nullptr)
			item = _p->GetWeapon(0);
	}
	else if (PtInRect(&_InvenFrame->GetChild("curWeapon_2")->GetRect(), _ptMouse))
	{
		if (_p->GetWeapon(1) != nullptr)
			item = _p->GetWeapon(1);
	}
	else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_1")->GetRect(), _ptMouse))
	{
		if (_p->GetSubWeapon(0) != nullptr)
			item = _p->GetSubWeapon(0);
	}
	else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_2")->GetRect(), _ptMouse))
	{
		if (_p->GetSubWeapon(1) != nullptr)
			item = _p->GetSubWeapon(1);
	}

	if (item != nullptr)
	{
		if (item != _curToolTipItem)
		{
			InitToolTipItem(item);
		}

		uiToolTip->MoveFrameChild((_ptMouse.x - 300) - uiToolTip->GetX(), (_ptMouse.y - (isEquipped ? 0 : _toolTipFinalY)) - uiToolTip->GetY());
		uiToolTip->SetIsViewing(true);
	}

	else
	{
		uiToolTip->SetIsViewing(false);
	}
}
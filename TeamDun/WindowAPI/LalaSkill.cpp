#include "stdafx.h"
#include "LalaSkill.h"

HRESULT LalaSkill::init()
{
	_id = 1;
	_name = "������";
	_coolTime = 720;
	_description = "�ѹ��� ���� ���� �߻��մϴ�.";
	_image = IMAGEMANAGER->findImage("Skill_lala");
	_imageName = "Skill_lala";
	_parent = nullptr;
	_curCoolTime = 0;

	return S_OK;
}

void LalaSkill::update()
{
	CoolTimeChecker();
}

void LalaSkill::release()
{
}

void LalaSkill::render(HDC hdc)
{
}

void LalaSkill::Activate()
{
	cout << _curCoolTime << endl;
	if (_curCoolTime == 0)
	{
		SOUNDMANAGER->play("����_����� �����");
		
		for (int i = 0; i < 6; i++)
		{
			Bullet* bullet = ENTITYMANAGER->makeBullet("StarBullet", "StarBulletFX", BT_PLAYER, -20 + _parent->GetAngleCheckPosX() + cosf(_parent->GetAngle()) * 50, -30 + _parent->GetAngleCheckPosY() - sinf(_parent->GetAngle()) * 50, _parent->GetAngle() + RANDOM->range((float)-PI/4, (float)PI/4),
				10, 10, 1500, true, _parent->GetAngle(), BST_TRACE);
			bullet->SetUseTraceImage("StarBulletParticle");
			bullet->SetParticleTime(1);
			bullet->SetUseTraceParticle(true);
			bullet->SetTraceAlphaChanger(10);
			bullet->SetUseWallCollision(false);
		}

		_curCoolTime = _coolTime;
	}
}
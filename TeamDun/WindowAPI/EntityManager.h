#pragma once

#include "singletonBase.h"
#include "Bullet.h"
#include "player.h"

class EntityManager : public singletonBase<EntityManager>
{
private :
	vector<Object*>		_vObjs;
	vector<Bullet*>		_vBullets;
	Player*				_p;
	WormVillage*		_wormVillage;

public :
	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();

	// GETSET //
	vector<Object*>&	getVObjs()		{ return _vObjs; }
	vector<Bullet*>&	getVBullets()	{ return _vBullets; }
	Player*				getPlayer()		{ return _p; }
	WormVillage*		GetWormVillage() { return _wormVillage; }
	void				setPlayer(Player* p) { _p = p; }
	
	Bullet* makeBullet(const char* imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle, float damage, float speed, float maxDis, bool isFrame, float igAngle = 0, BULLETSPEEDTYPE speedtype = BST_NOMAL, string effectSound = "", bool isEffectAngle = true);
	void eraseBullet();
	void HitBullet();
};


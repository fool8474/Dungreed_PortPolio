#pragma once
enum BULLETSPEEDTYPE
{
	BST_NOMAL,
	BST_SLOW,
	BST_FAST,
	BST_GRAVITY,
	BST_CHARGE,
	BST_RETURN,
	BST_TRACE
};
enum BULLETTYPE
{
	BT_NOMAL,
	BT_NOCOL,
	BT_PLAYER,
	BT_PLAYERNOCOL
};

class Bullet
{
private :
	BULLETTYPE		_type;
	BULLETSPEEDTYPE _speedType;
	image*			_ig;
	string			_effectIgName;
	string			_effectSound;
	RECT			_rc;
	float			_x;
	float			_y;
	float			_startX;
	float			_startY;
	float			_angle;
	float			_speed;
	float			_igAngle;
	int				_frameX;
	int				_frameY;
	int				_frameTimer;
	float			_distance;
	float			_maxDistance;
	float			_damage;
	float			_jumpPower;
	float			_gravity;
	float			_scale;
	int				_particleTimer;
	bool			_useTraceParticle;
	string			_useTraceImage;
	bool			_isFrame;
	bool			_isDead;
	int				_particleTime;
	float			_traceAlphaChanger;
	float			_angleChanger;
	float			_angleChangerTrace;
	bool			_useWallCollision;
	Object*			_target;
	bool			_isEffectAngle;
	bool			_isResetUid;
	vector<int>		_vUid;
public :
	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void GenerateTraceParticle();
	void makeBullet(const char* imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle, float damage, float speed, float maxDis, bool isFrame, float igAngle = 0, BULLETSPEEDTYPE speedtype = BST_NOMAL, string effectSound = "", bool isEffectAngle = true);

	void moveBullet();
	void Animation();
	void speedTypeMove();
	

	////GetSet
	vector<int>& getSUid() { return _vUid; }
	BULLETTYPE getType() { return _type; }
	BULLETSPEEDTYPE getSpeedType() {return _speedType;}
	image* getIg() { return _ig; }
	string getEffectIgName(){return _effectIgName;}
	string getEffectSound(){return _effectSound;}
	RECT getRc() { return _rc; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getStartX() { return _startX; }
	float getStartY() { return _startY; }
	float getAngle() { return _angle; }
	float getSpeed() { return _speed; }
	int	  getFrameX() { return _frameX; }
	int	  getFrameY() { return _frameY; }
	int	  getFrameTimer() { return _frameTimer; }
	float getDamage() { return _damage; }
	float getDis() { return _distance; }
	float getMaxDis() { return _maxDistance; }
	bool getIsDead() { return _isDead; }
	float getScale(){return _scale;}
	bool getUseWallCollision() { return _useWallCollision; }
	bool getIsEffectAngle() { return _isEffectAngle; }
	void SetType(BULLETTYPE type) {  _type = type; }
	void SetIg(image* ig) { _ig = ig; }
	void SetEffectIgName(string effectname) { _effectIgName = effectname; }
	void SetEffectSound(string effectSound) { _effectSound = effectSound; }
	void SetRc(RECT rc){ _rc = rc; }
	void SetX(float x) {  _x = x; }
	void SetY(float y) {  _y = y; }
	void SetStartX(float startX) {  _startX= startX; }
	void SetStartY(float startY) {  _startY = startY; }
	void SetAngle(float angle){ _angle = angle; }
	void SetSpeed(float speed) {  _speed = speed; }
	void SetFrameX(int frameX) { _frameX = frameX; }
	void SetFrameY(int frameY) {  _frameY = frameY; }
	void SetFrameTimer( int frameTimer) { _frameTimer = frameTimer; }
	void SetDis(float distance) { _distance= distance; }
	void SetMaxDis(float maxDistance) {  _maxDistance = maxDistance; }
	void SetIsDead(bool isDead) { _isDead = isDead; }
	void SetDamage(float damage) { _damage = damage; }
	void SetUseTraceParticle(bool isOn) { _useTraceParticle = isOn; }
	void SetUseTraceImage(string str) { _useTraceImage = str; }
	void SetTraceAlphaChanger(float changer) { _traceAlphaChanger = changer; }
	void SetScale(float scale){ _scale = scale; }
	void SetParticleTime(int time) { _particleTime = time; }
	void SetUseWallCollision(bool use) { _useWallCollision = use; }
};

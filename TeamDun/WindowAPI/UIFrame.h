#pragma once

/// <summary>
/// UIFrame�� UI�� ���ʰ� �� �����̴�. UI �ؽ�Ʈ, ��ũ��, �̹��� �� UI�� ��� ��Ұ� UIFrame�� ����ϰ� �ȴ�.
/// </summary>
class UIFrame
{
protected:
	// �ʼ� ������� //
	string					_name;				// �� UI�� �̸�
	float					_x;					// X ��ġ
	float					_y;					// Y ��ġ
	float					_sizeX;				// X ũ��
	float					_sizeY;				// Y ũ��
	RECT					_interactRect;		// �� UI�� ��ȣ�ۿ� �� RECT
	bool					_isViewing;			// �� UI�� Render�Ǵ���

	image*					_image;				// �� UI�� ���� �̹��� (������ nullptr)
	
	// �θ��ڽ� ���� //
	vector<UIFrame*>		_vChildFrames;		// �ڽ� �����ӵ��� ���Ϳ� ���� ��
	map<string, UIFrame*>	_mChildFrames;		// �ڽ� �����ӵ��� ������ ���� �� (�˻��� �̿�, NAME�� Key�� ��)
	bool					_isChild;			// �� UI�� �ڽ� ����������
	UIFrame*				_parent;			// �� UI�� �θ� ������ (������ nullptr)
	
	/// ���� ��� ���� ///

	// ��ũ�� ���� //
	bool					_isOutside;			// �� �������� �θ� UI Ʋ ������ �������Դ��� (��ũ�ѿ��� �ַ� ���, ���������� �������� ����)
	bool					_useOutsideLimit;	// isOutside ������ ����Ұ�����
	
	// �巡�� ���� //
	bool					_isSelected;		// Ŭ�� ���� ���� ���õ� UI����
	bool					_isMoveToDrag;		// �巡�׸� ���� �̵��� �� �ִ�	 (true�� ��� ���� set�� ���� üũ�������)
	int						_selectTimer;		// ���� �ð����� �ٿ� ���ȴ���
	float					_moveStartX;		// �巡�� �̵� ���� �� �� ó�� �̵� ������ ���� ���콺 ����Ʈ X
	float					_moveStartY;		// �巡�� �̵� ���� �� �� ó�� �̵� ������ ���� ���콺 ����Ʈ Y
	float					_savedX;			// �巡�� �̵� ���� �� �� ó�� �̵� ������ ���� UI ��ġ X
	float					_savedY;			// �巡�� �̵� ���� �� �� ó�� �̵� ������ ���� UI ��ġ Y

	// ���� ���� //
	float					_scaleX;			// Ȯ�� ������ X
	float					_scaleY;			// Ȯ�� ������ Y
	bool					_renderBeforeParent;// �θ𺸴� ���� ������ ������ (�θ� ������)

	// Ÿ�̸� ���� //
	int						_timer;				// Ÿ�̸�
	bool					_isSetTimer;		// Ÿ�̸� ���� ���� 
	// ����� ���� //
	bool					_useDebug;

public:
	virtual HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, float scaleX = 1, float scaleY = 1);
	virtual void render(HDC hdc);
	virtual void update();
	virtual void release();

	virtual void AddChildMap(string name, UIFrame* frame) { _mChildFrames[name] = frame; } // �ڽ� ��� Map�� key = name, value = frame���� �ִ´�.
	virtual void ToggleIsViewing();
	virtual void AddFrame(UIFrame* frame);
	
	void MoveFrame(); // �ڽ� ���� �̵�
	void MoveFrameChild(float x, float y);
	void CheckIsOutside();
	void MoveFrame(float x, float y);
	void MoveFrameToXY(float x, float y);
	void MoveY(int y) { _y += y; } // �ڽ� ������ �̵�
	void SetIntersectRect() { _interactRect = RectMake(_x, _y, _sizeX*_scaleX, _sizeY*_scaleY); }
	void OperateViewingTimer();
	void SetViewingTimer(int timer) { _isSetTimer = true; _timer = timer; SetIsViewing(true);}

	UIFrame* GetChild(string name) { return _mChildFrames[name]; }
	void RemoveChild(string name) { _mChildFrames.erase(name); }

	float GetX() { return _x; }
	float GetY() { return _y; }
	float GetSizeX() { return _sizeX; }
	float GetSizeY() { return _sizeY; }
	string GetName() { return _name; }
	RECT GetRect() { return _interactRect; }
	vector<UIFrame*>& GetVChildFrames() { return _vChildFrames; }
	image* GetImage() { return _image; }
	float GetScaleX() { return _scaleX; }
	float GetScaleY() { return _scaleY; }

	bool GetIsOutside() { return _isOutside; }
	bool GetIsViewing() { return _isViewing; }
	bool GetUseOutsideLimit() { return _useOutsideLimit; }
	bool GetRenderBeforeParent() { return _renderBeforeParent; }

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	void SetIsViewing(bool isViewing, bool withChild = true);
	void SetUseOutsideLimit(bool outside) { _useOutsideLimit = outside; }
	void SetIsMoveToDrag(bool drag) { _isMoveToDrag = drag; }
	void SetImage(image* target) { _image = target; }
	void SetRenderBeforeParent(bool rbp) { _renderBeforeParent = rbp; }
	void SetScaleX(float x) { _scaleX = x; }
	void SetScaleY(float y) { _scaleY = y; }
	void SetUseDebug(bool useDebug) { _useDebug = useDebug; }
};

#pragma once
#include "gameNode.h"
#include "progressBar.h"

//�ε������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//���Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,			//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,			//�Ϲ� �̹���(��ǥ)
	LOAD_KIND_FRAMEIMAGE_0,		//������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,		//������ �̹���(��ǥ)
	LOAD_KIND_SOUND,			//����
	LOAD_KIND_END
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string		keyName;		// �̹��� Ű��
	const char* fileName;		// �̹��� �����̸�
	int			x;				// ��ġ ��ǥ x
	int			y;				// ��ġ ��ǥ y
	int			width;			// ���� ����
	int			height;			// ���� ����
	int			frameX;			// ������ x
	int			frameY;			// ������ y
	bool		isTrans;		// ��� ���� ����
	COLORREF	transColor;		// ��
	bool		isRotate;		// ȸ�� ����
};

//���� ���ҽ� ����ü
struct tagSoundResource
{
	string	keyName;	// ���� Ű��
	string	fileName;	// ���� �����̸�
	bool	isBGM;		// bgm ����
	bool	isLoop;		// ���� ����
};

/// <summary>
/// �ε� �������� �ε��� ���(���� / �̹���)�� ������ �����ϰ� �ִ�.
/// </summary>
class LoadItem
{
private:
	LOAD_KIND			_kind;				// �ε�����
	tagImageResource	_imageResource;		// �̹��� ����
	tagSoundResource	_soundResource;		// ���� ����

public:
	HRESULT init(string keyName, string soundName, bool bgm, bool loop);
	HRESULT init(string strKey, int width, int height);
	HRESULT init(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor = RGB(255,0,255), bool isRotate = false);
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor = RGB(255,0,255), bool isRotate = false);
	
	// GETSET //
	LOAD_KIND			getLoadKind()		{ return _kind; }
	tagImageResource	getImageResource()	{ return _imageResource; }
	tagSoundResource	getSoundResource()	{ return _soundResource; }
};

/// <summary>
/// �ε� Ŭ������ �ε� ������ ���� �ε� ���μ����� �����ϰ� �ִ�.
/// </summary>
class Loading : public gameNode
{
private:

	// �ε� ������ ���� //
	typedef vector<LoadItem*>			vLoadItem;			// �ε� ������ ������ ���� (�̹��� �� ����)
	typedef vector<LoadItem*>::iterator viLoadItem;			// ���� ITR
	vLoadItem							_vLoadItem;			// �ε� ������ ����
	string								_curKey;			// ���� �ε� �������� Ű��

public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	void LoadSound(string keyName, string soundName, bool bgm, bool loop);
	void LoadNormalImage(string strKey, int width, int height);
	void LoadNormalImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0,0,0));
	void LoadNormalImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255,255,255), bool isRotate = false);
	void LoadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255,255,255), bool isRotate = false);
	void LoadingDone(LoadItem* item);

	// GETSET //
	string		GetCurKey()		{ return _curKey; }
	vLoadItem	GetLoadItem()	{ return _vLoadItem; }
};


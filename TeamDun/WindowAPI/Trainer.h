#pragma once
#include "NPC.h"

class Trainer : public NPC
{
private:
	bool			_isOpen;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void CheckEscapePressed();
	virtual void	Activate();
	virtual void	Animation();

	void			Conversation();
	void			initSecond();
};
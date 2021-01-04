#pragma once
#include <stdio.h>
#include "state.h"

class IPopupHandler
{
public:
	virtual void PopupClose(int id) = 0;
};

class Popup : public sdlgx::core::State
{
public:
	Popup();
	~Popup();
	void SetHandler(IPopupHandler* p);

protected:
	IPopupHandler* _handler;
};
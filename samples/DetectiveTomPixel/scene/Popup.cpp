#include "Popup.h"

Popup::Popup() : State()
{}

Popup::~Popup()
{}

void Popup::SetHandler(IPopupHandler* p)
{
	_handler = p;
}
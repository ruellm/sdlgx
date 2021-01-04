#pragma once

#include "GlowButton.h"
#include "uimanager.h"
#include "BoxScroll.h"
#include "SceneFader.h"

class LogScreen :
	public SceneFader,
	sdlgx::gui::IButtonEventHandler 
{
public:
	LogScreen();
	~LogScreen();
	
	virtual void OnInitialize();
	virtual void OnLoad();
	
private:
	GlowButton _back;
	LogScrollBox _scroll_box;
	virtual void OnButtonClick(sdlgx::gui::Button* b);
};
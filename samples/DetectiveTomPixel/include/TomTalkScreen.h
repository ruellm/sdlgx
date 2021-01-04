#pragma once

#include "RectTextButton.h"
#include "uimanager.h"
#include "BoxScroll.h"
#include "SceneFader.h"

class TomTalkScreen :
	public SceneFader,
	sdlgx::gui::IButtonEventHandler
{
public:
	TomTalkScreen();
	~TomTalkScreen();

	virtual void OnInitialize();
	virtual void OnLoad();
	virtual void OnUpdate(float elapsed);

	int GetSelectedIdx();

private:
	int _selected;
	RectTextButton _options[2];

	virtual void OnButtonClick(sdlgx::gui::Button* b);
	virtual void OnInternalDraw();
};
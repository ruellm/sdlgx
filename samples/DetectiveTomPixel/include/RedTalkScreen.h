#pragma once

#include "GlowButton.h"
#include "uimanager.h"
#include "BoxScroll.h"
#include "SceneFader.h"
#include "RectTextButton.h"

class RedTalkScreen :
	public SceneFader,
	sdlgx::gui::IButtonEventHandler
{
public:
	RedTalkScreen();
	~RedTalkScreen();

	virtual void OnInitialize();
	virtual void OnLoad();
	virtual void OnUpdate(float elapsed);

	int GetSelectedIdx();
	bool IsComplete();

private:
	int _selected;
	bool _choice_flag[3];
	RectTextButton _options[3];

	virtual void OnButtonClick(sdlgx::gui::Button* b);

	virtual void OnInternalDraw();
};
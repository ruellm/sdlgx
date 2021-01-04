#pragma once

#include "RectTextButton.h"
#include "uimanager.h"
#include "BoxScroll.h"
#include "SceneFader.h"

class EmmaTalkScreen :
	public SceneFader,
	sdlgx::gui::IButtonEventHandler
{
public:
	EmmaTalkScreen();
	~EmmaTalkScreen();

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
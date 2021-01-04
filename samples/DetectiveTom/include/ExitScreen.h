#pragma once

#include "GlowButton.h"
#include "uimanager.h"
#include "SceneFader.h"

enum ExitStatus {
	EXIT_STATUS_NO = 0,
	EXIT_STATUS_YES,
};

class ExitScreen : public SceneFader,
	sdlgx::gui::IButtonEventHandler
{
public:
	ExitScreen();
	~ExitScreen();

	virtual void OnInitialize();
	virtual void OnInternalDraw();
	enum ExitStatus GetStatus();

private:
	GlowButtonText	_yesBtn;
	GlowButtonText	_noBtn;
	sdlgx::scene::Texture _bg;
	sdlgx::scene::Texture* _text;
	enum ExitStatus _status;


	virtual void OnButtonClick(sdlgx::gui::Button* b);
};
#pragma once

#include "SceneFader.h"
#include "texture.h"
#include "state.h"
#include "GlowButton.h"
#include "CaseFileScreen.h"
#include "LogScreen.h"
#include "ExitScreen.h"
#include "SettingsScreen.h"
#include "zoom_button.h"

class PauseMenu 
	: public SceneFader, 
	public sdlgx::gui::IButtonEventHandler,
	public IPopupHandler
{
public:
	PauseMenu();
	~PauseMenu();

	virtual void OnInitialize();
	virtual void OnLoad();
	virtual void OnUpdate(float elapsed);
	bool OnEvent(SDL_Event* e);
	void ForceShowOption(int index);
	void ForceClearPopup();
	CaseFileScreen* GetCaseFileMenu();

private:
	sdlgx::scene::Texture _black_lines_bg;
	virtual void OnInternalDraw();
	virtual void OnButtonClick(sdlgx::gui::Button* b);
	virtual void PopupClose(int id);

	sdlgx::gui::ZoomButton _back;
	sdlgx::gui::ZoomButton _options[5];
	State*	_popup;

	CaseFileScreen _casefile;
	LogScreen _logScreen;
	ExitScreen _exitScreen;
	SettingScreen _settingScreen;
};
#pragma once

#include "state.h"
#include "texture.h"
#include "GlowButton.h"
#include "Popup.h"
#include "SettingsScreen.h"

class MainMenuState 
	: public sdlgx::core::State, 
	public sdlgx::gui::IButtonEventHandler,
	public IPopupHandler
{
public:
	MainMenuState();
	~MainMenuState();

	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);

private:
	sdlgx::scene::Texture _texture;
	GlowButtonText	_newgameBtn;
	GlowButtonText	_loadgameBtn;
	GlowButtonText	_settingsBtn;
	sdlgx::core::State* _pop_up;
	SettingScreen _settingScreen;
	virtual void OnButtonClick(sdlgx::gui::Button* b);
	
	//inherited IPopupHandler 
	virtual void PopupClose(int id);
};


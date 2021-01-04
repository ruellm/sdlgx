#pragma once

#include "state.h"
#include "button.h"
#include "texture.h"
#include "GlowButton.h"
#include "PauseMenu.h"
#include "Popup.h"
#include "sprite_sheet.h"

class GameState 
	: public sdlgx::core::State, 
	public sdlgx::gui::IButtonEventHandler,
	public IPopupHandler 
{

public:
	GameState();
	~GameState();

	//----------------------------------------
	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);
	//----------------------------------------

private:
	
	sdlgx::scene::Texture	_background;
	GlowButton _pinButton;

	sdlgx::core::State* _pop_up;
	PauseMenu _pauseMenu;
	
	//Sample spritesheet
	sdlgx::scene::SpriteSheet tom;
	sdlgx::scene::Texture	_textBox;

	//inherited IButtonEventHandler 
	virtual void OnButtonClick(sdlgx::gui::Button* b);

	//inherited IPopupHandler 
	virtual void PopupClose(int id);

};
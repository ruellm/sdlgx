#pragma once

#include "SceneFader.h"
#include "button.h"
#include "ScrollBar.h"
#include "Texture.h"
#include "ComboBox.h"
#include "GlowButton.h"

class SettingScreen
	: public SceneFader,
	sdlgx::gui::IButtonEventHandler {

public:
	SettingScreen();
	~SettingScreen();

	//----------------------------------------
	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);	
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);
	//----------------------------------------

private:
	virtual void OnInternalDraw();
	virtual void OnButtonClick(sdlgx::gui::Button* b);
	
	ScrollBar _scrollbar[4];
	ComboBox _combobox;
	GlowButton _back;
	sdlgx::scene::Texture* _text[5];
};
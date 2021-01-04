#pragma once

#include "state.h"
#include "texture.h"
#include "button.h"
#include "sprite_sheet.h"
#include "ScrollBar.h"
#include "GlowButton.h"
#include "ComboBox.h"

class MainScene : sdlgx::core::State, sdlgx::gui::IButtonEventHandler
{
public:
	MainScene();
	~MainScene();

	//----------------------------------------
	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);

	virtual bool OnKeyDown(SDL_Keycode sym);
	//----------------------------------------
	
	virtual void OnButtonClick(sdlgx::gui::Button* b);

private:
	sdlgx::scene::Texture m_texture;
	sdlgx::gui::Button button1;
	sdlgx::gui::Button button2;
	sdlgx::scene::SpriteSheet heart;

	//cached text
	sdlgx::scene::Texture* m_hello_world;

	GlowButton backbutton;
	ScrollBar scrollbar;
	ComboBox combobox;
};


#pragma once
#include "state.h"
#include "texture.h"
#include "resource.h"
#include "sprite_sheet.h"

class PixelTestState : sdlgx::core::State
{
public:
	PixelTestState();
	~PixelTestState();

	//----------------------------------------
	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);
	bool OnKeyDown(SDL_Keycode sym);

private:
	sdlgx::scene::Texture _background;
	sdlgx::scene::Texture _filter;
	sdlgx::scene::Texture _textbox;
	sdlgx::scene::SpriteSheet sprite;
};


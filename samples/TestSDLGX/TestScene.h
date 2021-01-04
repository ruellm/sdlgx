#pragma once

#include "state.h"
#include "texture.h"
#include "resource.h"

class TestScene : sdlgx::core::State, public sdlgx::resource::IResourceHandler
{
public:
	TestScene();
	~TestScene();

	//----------------------------------------
	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw( );
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);

	virtual bool OnKeyDown(SDL_Keycode sym);
	//----------------------------------------

	virtual void OnResourceLoad(int index);

private:
	sdlgx::scene::Texture m_texture;
	bool resource_loaded;


};


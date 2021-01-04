#pragma once

#include "state.h"
#include "resource.h"

class LoadingState : public sdlgx::core::State,
	public sdlgx::resource::IResourceHandler
{
public:
	LoadingState();
	~LoadingState();

	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	virtual void OnClose();
	virtual bool OnKeyDown(SDL_Keycode sym);

private:
	virtual void OnResourceLoad(int index);
};


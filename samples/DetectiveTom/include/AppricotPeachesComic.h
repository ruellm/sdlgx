#pragma once

#pragma once

#include "uimanager.h"
#include "SceneFader.h"
#include "texture.h"

class AppricotPeachesComic :
	public SceneFader
{
public:
	AppricotPeachesComic();
	~AppricotPeachesComic();

	virtual void OnInitialize();
	virtual void OnLoad();
	virtual void OnUpdate(float elapsed);

private:
	sdlgx::scene::Texture _texture[3];
	int _curr_idx;
	Uint32 _lastTime;
	float _frame_alpha;
	int _state;
	virtual void OnInternalDraw();
};

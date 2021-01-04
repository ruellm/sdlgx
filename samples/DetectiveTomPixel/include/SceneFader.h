#pragma once

#include "texture.h"
#include "state.h"
#include "Popup.h"

class SceneFader : public Popup
{
public:
	SceneFader();
	~SceneFader();
	
	void Load(int width, int height);
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	void Show();
	void Hide();
	
protected:
	float _alpha;
	float _step;
	sdlgx::scene::Texture _texture;
	
protected:
	void Set();
	void UnSet();
	virtual void OnInternalDraw();

	enum SceneFaderState {
		SCENEFADER_STATE_DEFAULT = 0,
		SCENEFADER_STATE_FADEIN,
		SCENEFADER_STATE_READY,
		SCENEFADER_STATE_FADEOUT,
	};

	SceneFaderState _internal_state;
};
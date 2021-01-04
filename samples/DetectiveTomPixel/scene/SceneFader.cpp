#include "SceneFader.h"
#include "engine.h"
using namespace sdlgx::core;

SceneFader::SceneFader() 
	:_internal_state(SCENEFADER_STATE_DEFAULT), _alpha(0.0f),
	_step(5.0f), Popup()
{}

SceneFader::~SceneFader()
{
	
}

void SceneFader::Load(int width, int height)
{
	_texture.Create(width, height);
	_texture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void SceneFader::OnUpdate(float elapsed)
{
	Popup::OnUpdate(elapsed);
	if (_internal_state == SCENEFADER_STATE_FADEOUT)
	{
		_alpha -= (_step * elapsed);
		if (_alpha <= 0) {
			_internal_state = SCENEFADER_STATE_DEFAULT;
			_alpha = 0.0f;

			if (_handler != NULL) {
				_handler->PopupClose(GetStateID());
			}
		}
	}else if(_internal_state == SCENEFADER_STATE_FADEIN){
		_alpha += (_step * elapsed);
		if (_alpha >= 1.0) {
			_internal_state = SCENEFADER_STATE_READY;
			_alpha = 1.0f;
		}
	}
}

void SceneFader::OnDraw()
{
	Set();
	OnInternalDraw();
	UnSet();
}

void SceneFader::OnInternalDraw()
{
	Popup::OnDraw();
}

void SceneFader::Show()
{
	_internal_state = SCENEFADER_STATE_FADEIN;
}

void SceneFader::Hide()
{
	_internal_state = SCENEFADER_STATE_FADEOUT;
}

void SceneFader::Set()
{
	_texture.SetAlpha(_alpha * 255);
	_texture.SetRenderTarget();
}

void SceneFader::UnSet()
{
	_texture.UnSetRenderTarget();
	_texture.Draw(0, 0);
}

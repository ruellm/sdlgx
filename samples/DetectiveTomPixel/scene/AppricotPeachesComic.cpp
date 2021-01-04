#include "AppricotPeachesComic.h"
#include "definitions.h"
#include "engine.h"
#include "font.h"

using namespace sdlgx::core;
using namespace sdlgx::scene;

AppricotPeachesComic::AppricotPeachesComic() : SceneFader(),
	_frame_alpha(0)
{
	SetID(APPRICOT_PEACHES_COMIC);
}

AppricotPeachesComic::~AppricotPeachesComic()
{}

void AppricotPeachesComic::OnInitialize()
{
	SceneFader::Load(0, 0);
#if 0
	int resid[] = {
		APPRICOT_PEACHES_COMIC1,
		APPRICOT_PEACHES_COMIC2,
		APPRICOT_PEACHES_COMIC3,
	};

	int x = 25;
	int width = 604;
	int allowance = 30;
	for (int i = 0;i < 3;i++) {
		_texture[i].LoadFromResource(resid[i]);
		_texture[i].SetCoordinates(x, 75);
		_texture[i].SetAlpha(0);
		x += (width + allowance);
	}
#endif
}

void AppricotPeachesComic::OnLoad()
{
	_curr_idx = 0;
	_frame_alpha = 0;
	_state = 0;

	//////////////////////////////////////////////////////
	//TEMPORARY UNTIL NEW COMICS
	_lastTime = SDL_GetTicks();
	//////////////////////////////////////////////////////
}

void AppricotPeachesComic::OnUpdate(float elapsed)
{
	if (_internal_state != SCENEFADER_STATE_READY) {
		SceneFader::OnUpdate(elapsed);
		return;
	}
#if 0
	if (_state == 0)
	{
		_frame_alpha += (500) * elapsed;
		if (_frame_alpha > 255) {
			_frame_alpha = 255;
			_state = 1;
			_lastTime = SDL_GetTicks();
		}	

		_texture[_curr_idx].SetBlendMode(SDL_BLENDMODE_BLEND);
		_texture[_curr_idx].SetAlpha(_frame_alpha);
	}

	else if (_state == 1) {
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _lastTime) / 1000.0f;
		float pausetime = 2.0f;
		if (_curr_idx == 2)
			pausetime = 5.0f;

		if (diff >= pausetime) {
			_curr_idx++;
			if (_curr_idx < 3)
			{
				_state = 0;
				_frame_alpha = 0;
			}
			else {
				_curr_idx = 2;
				_state = -1;
				Hide();
			}
		}
	}
#endif
	SceneFader::OnUpdate(elapsed);

	//////////////////////////////////////////////////////
	//TEMPORARY UNTIL NEW COMICS
	Uint32 currentTime = SDL_GetTicks();
	float diff = (currentTime - _lastTime) / 1000.0f;

	if (diff >= 4.0) {
		Hide();
	}
	//////////////////////////////////////////////////////
}

void AppricotPeachesComic::OnInternalDraw()
{
	
	
	SDL_SetRenderDrawColor(CURRENT_RENDERER, 0, 0, 0, 255);
	SDL_Rect rect = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT };
	SDL_RenderFillRect(CURRENT_RENDERER, &rect);
	SDLGX_DrawTextCenter(LOGICAL_WIDTH / 2, LOGICAL_HEIGHT / 2, "COMICS HERE", 0, 40, { 255,255,255 });
	
#if 0
	for (int i = 0; i <= _curr_idx;i++) {
		_texture[i].Draw();
	}
#endif
}
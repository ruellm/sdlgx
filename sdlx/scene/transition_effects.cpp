#include "transition_effects.h"
#include "engine.h"

using namespace sdlgx::scene;
using namespace sdlgx::core;

TransitionEffects::TransitionEffects()
{
}


TransitionEffects::~TransitionEffects()
{
}

bool TransitionEffects::OnEvent(SDL_Event * e)
{
	//NO EVENT for transitions
	return false;
}

/**/
/**/
/**/

FadeTransition::FadeTransition() 
	:_new_state(NULL), _alpha(1.0f),
	_transition (0), _diff(3.0f),
	_now(NULL)
{
	//...
}

FadeTransition::~FadeTransition()
{}

void FadeTransition::Initialize(State* o, State* n, State** c)
{
	_texture.Create();
	_texture.SetBlendMode(SDL_BLENDMODE_BLEND);
	_new_state = n;
	_current = c;
	_transition = 1;
	_old_state = o;
	_now = o;
}

void FadeTransition::OnUpdate(float elapsed)
{
	if (_transition != 0) {
		if (_transition == 1) {
			_alpha -= (_diff * elapsed);
			if (_alpha <= 0) {
				_transition = 2;
				_alpha = 0;	

				_old_state->OnUnload();				
				_new_state->Launch();
				_now = _new_state;
			}
		}
		else if (_transition == 2) {
			_alpha += (_diff * elapsed);
			if (_alpha >= 1.0) {
				_transition = 3;
				_alpha = 1.0;

				(*_current) = _new_state;
				delete this;
			}
		}
	}
}

void FadeTransition::OnDraw()
{
	_texture.SetAlpha(_alpha * 255);
	_texture.SetRenderTarget();
	SDL_SetRenderDrawColor(CURRENT_RENDERER, 0, 0, 0, 0xFF);
	SDL_RenderClear(CURRENT_RENDERER);
	_now->OnDraw();
	_texture.UnSetRenderTarget();
	_texture.Draw(0, 0);
}

void FadeTransition::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	_red = r;
	_green = g;
	_blue = b;
}

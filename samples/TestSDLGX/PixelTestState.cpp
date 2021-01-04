#include "PixelTestState.h"
#include "engine.h"

using namespace sdlgx::core;
using namespace sdlgx::gui;
using namespace sdlgx::scene;


PixelTestState::PixelTestState() 
	: State(3)
{
}


PixelTestState::~PixelTestState()
{
}

void PixelTestState::OnLoad()
{
	_background.LoadFromResource(14);
	_filter.LoadFromResource(15);
	_textbox.LoadFromResource(16);

	sprite.LoadFromResource(17);
	sprite.Set(5, 10, true);

}

void PixelTestState::OnInitialize()
{}

void PixelTestState::OnUpdate(float elapsed)
{
	sprite.OnUpdate(elapsed);
}

void PixelTestState::OnDraw()
{
	int back_y = (LOGICAL_HEIGHT / 2) - (_background._height / 2);
	_background.Draw((LOGICAL_WIDTH / 2) - (_background._width / 2), back_y);
	_filter.Draw(0, 0);

	sprite.SetCoordinates(0, (back_y + _background.GetHeight()) - sprite.GetHeight());
	sprite.OnDraw();
	_textbox.Draw(0, LOGICAL_HEIGHT - _textbox.GetHeight());
}

void PixelTestState::OnClose()
{}

bool PixelTestState::OnEvent(SDL_Event* e)
{
	return State::OnEvent(e);
}

bool PixelTestState::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_ESCAPE) {
		Engine::GetInstance()->Shutdown();
		return true;
	}
	return false;
}

#include "GameState.h"
#include "definitions.h"
#include "uimanager.h"
#include "engine.h"
#include "font.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;
using namespace sdlgx::scene;

GameState::GameState()
	: State(GAME_STATE), _pop_up(NULL)
{
}

GameState::~GameState()
{	
	SAFE_DELETE(_uimanager);
}

void GameState::OnLoad()
{
	
}

void GameState::OnInitialize()
{
	_uimanager = new UIManager();
	_background.LoadFromResource(TEST_BG_IMG);

	_pinButton.Load(PIN_BUTTON_IMG, PIN_BUTTON_IMG);
	_pinButton.SetGlowImage(PIN_GLOW_IMG);
	_pinButton.SetHandler(this);
	_pinButton.SetID(0);
	_pinButton.SetCoordinates(20,20);
	_uimanager->Add(&_pinButton);

	_pauseMenu.SetHandler(this);

	tom.LoadFromResource(SAMPLE_TOM_SPRITE_SHEET);
	tom.Set(6, 5, true);
	tom.SetCoordinates(300, 0);

	_textBox.LoadFromResource(TEXT_BOX_IMG);
	_textBox.SetCoordinates(0,0);
}

void GameState::OnUpdate(float elapsed)
{
	if (_pop_up != NULL) {
		_pop_up->OnUpdate(elapsed);
		return;
	}

	_uimanager->OnUpdate(elapsed);
	tom.OnUpdate(elapsed);
}

void GameState::OnDraw()
{
	_background.Draw(0,0);
	
	if (_pop_up != NULL) {
		_pop_up->OnDraw();
		return;
	}

	_uimanager->OnDraw();
	tom.OnDraw();

	_textBox.Draw();

	SDLGX_DrawText(220,740, "Tom", FONT_MYRIADPRO_REGULAR, 50, { 0,0,0 });
	SDLGX_DrawText(198, 850, "Are we gonna play or what?", FONT_MYRIADPRO_REGULAR, 50, { 79,202,255 });

}

void GameState::OnClose()
{

}

bool GameState::OnEvent(SDL_Event* e)
{
	if (_pop_up != NULL) {
		return _pop_up->OnEvent(e);
	}
	return State::OnEvent(e);
}

void GameState::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID())
	{
	case 0:// Pin button
		_pop_up = &_pauseMenu;
		_pauseMenu.Launch();
		_pauseMenu.Show();
		break;
	}
}

void GameState::PopupClose(int id)
{
	_pop_up = NULL;
}
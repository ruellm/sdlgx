#include "MainMenuState.h"
#include "definitions.h"
#include "uimanager.h"
#include "engine.h"

using namespace sdlgx::core;
using namespace sdlgx::gui;
using namespace sdlgx::scene;

MainMenuState::MainMenuState() 
	: State(MAIN_MENU_STATE), _pop_up(NULL)
{
}

MainMenuState::~MainMenuState()
{
	SAFE_DELETE(_uimanager);
}

void MainMenuState::OnLoad()
{
}

void MainMenuState::OnInitialize()
{
	_uimanager = new UIManager();
	_texture.LoadFromResource(MAIN_MENU_BG_IMG);
	
	int button_height = 127;
	int button_width = 870;
	int x = LOGICAL_WIDTH - button_width- 50;
	int y = 400;
	SDL_Color idle = { 255,255,255 };
	SDL_Color hover = { 255,0,0 };

	char text[][10] = {
		"New Game",
		"Load Game",
		"Settings"
	};

	GlowButtonText* buttons[3] = {
		&_newgameBtn,
		&_loadgameBtn,
		&_settingsBtn
	};

	GlowButtonText* currp = NULL;
	for (int i = 0; i < 3;i++) {
		currp = buttons[i];

		currp->Load(BUTTON_870x127_IMG, BUTTON_870x127_IMG);
		currp->SetGlowImage(BUTTON_870x127_HOVER_IMG, 1);
		currp->SetTextParam( text[i], FONT_MYRIADPRO_REGULAR, 60, idle, hover);
		currp->_x = x;
		currp->_y = y;
		currp->SetID(i);
		currp->SetHandler(this);
		_uimanager->Add(currp);
	
		y += button_height + 50;
	}
	
	_settingScreen.SetHandler(this);

}


void MainMenuState::OnUpdate(float elapsed)
{
	if (_pop_up != NULL) {
		_pop_up->OnUpdate(elapsed);
		return;
	}

	_uimanager->OnUpdate(elapsed);
}

void MainMenuState::OnDraw()
{
	_texture.Draw(0, 0);
	
	if (_pop_up != NULL) {
		_pop_up->OnDraw();
		return;
	}

	_uimanager->OnDraw();
}

void MainMenuState::OnClose()
{
}

bool MainMenuState::OnEvent(SDL_Event* e)
{
	if (_pop_up != NULL) {
		return _pop_up->OnEvent(e);
	}
	return State::OnEvent(e);
}


void MainMenuState::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID())
	{
	case 0: // New Game
		Engine::GetInstance()->ChangeState(PRELUDE_DIALOG_STATE, TRANSITION_FADE);
		break;
	case 2: // Settings
 		//Engine::GetInstance()->ChangeState(SETTINGS_STATE, TRANSITION_FADE);		
		_pop_up = &_settingScreen;
		_settingScreen.Launch();
		_settingScreen.Show();
		break;
	}
}

void MainMenuState::PopupClose(int id)
{
	_pop_up = NULL;
}
#include "PauseMenu.h"
#include "definitions.h"
#include "engine.h"
#include "uimanager.h"

using namespace sdlgx::core;
using namespace sdlgx::scene;
using namespace sdlgx::gui;

PauseMenu::PauseMenu()
	: SceneFader(), _popup(NULL)
{
	SetID(PAUSE_MENU);
}

PauseMenu::~PauseMenu()
{
	SAFE_DELETE(_uimanager);
}

void PauseMenu::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();

	_black_lines_bg.LoadFromResource(BLACK_LINES_OVERLAY_IMG);

	_back.Load(BACK_BUTTON_IMG);
	_back.SetCoordinates(8, LOGICAL_HEIGHT - (46/*iamge height*/));
	_back.SetHandler(this);
	_back.SetID(0);
	_uimanager->Add(&_back);

	int gap = 20;
	int width = 95;
	int total_width = (width + gap) * 5;
	int x = (LOGICAL_WIDTH / 2) - (total_width / 2);
	int y = (LOGICAL_HEIGHT/2) - (95/2);

	int resource[5] = {
		CASEFILE_BUTTON_IMG,
		SAVELOG_BUTTON_IMG,
		LOGS_BUTTON_IMG,
		SETTINGS_BUTTON_IMG,
		EXIT_BUTTON_IMG
	};

	for (int m = 0; m < 5; m++) {
		_options[m].Load(resource[m]);
		_options[m].SetCoordinates(x, y);
		_options[m].SetID(1 + m);
		_options[m].SetHandler(this);
		_uimanager->Add(&_options[m]);

		x += width + gap;
	}

	_casefile.SetHandler(this);
	_logScreen.SetHandler(this);
	_exitScreen.SetHandler(this);
	_settingScreen.SetHandler(this);
}

void PauseMenu::OnLoad()
{
	//...
}

void PauseMenu::OnUpdate(float elapsed)
{
	if (_internal_state != SCENEFADER_STATE_READY) {
		SceneFader::OnUpdate(elapsed);
		return;
	}

	if (_popup != NULL) {
		_popup->OnUpdate(elapsed);
		return;
	}

	_uimanager->OnUpdate(elapsed);
}

void PauseMenu::OnInternalDraw()
{
	_black_lines_bg.Draw(0, 0);
	
	if (_popup != NULL) {
		_popup->OnDraw();
		return;
	}

	_uimanager->OnDraw();
}

bool PauseMenu::OnEvent(SDL_Event* e)
{
	if (_popup != NULL) {
		return _popup->OnEvent(e);
	}

	return SceneFader::OnEvent(e);
}

void PauseMenu::OnButtonClick(sdlgx::gui::Button* b)
{
	ForceShowOption(b->GetID());
}

void PauseMenu::ForceClearPopup()
{
	_popup = NULL;
}

void PauseMenu::PopupClose(int id)
{
	_popup = NULL;
	switch (id)
	{
	case EXIT_SCREEN:
		if (_exitScreen.GetStatus() == EXIT_STATUS_YES) {
			Engine::GetInstance()->Shutdown();
		}
		
		break;
	}
}


void PauseMenu::ForceShowOption(int index)
{
	switch (index) {
	case 0: // back button
		Hide();
		break;
	case 1:	// case file
		_popup = &_casefile;
		_casefile.Launch();
		_casefile.Show();
		break;

#if 0 // -- Disable for now
	case 3: // log screen
		_popup = &_logScreen;
		_logScreen.Launch();
		_logScreen.Show();
		break;
	case 4:  // settings screen
		_popup = &_settingScreen;
		_settingScreen.Launch();
		_settingScreen.Show();
		break;
	case 5: //Exit Screen
		_popup = &_exitScreen;
		_exitScreen.Launch();
		_exitScreen.Show();
		break;
#endif
	}
}

CaseFileScreen* 
PauseMenu::GetCaseFileMenu()
{
	return &_casefile;
}
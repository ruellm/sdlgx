#include "LogScreen.h"
#include "UIManager.h"
#include "definitions.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;

LogScreen::LogScreen() : SceneFader()
{
	SetID(LOG_SCREEN);
}

LogScreen::~LogScreen()
{
	SAFE_DELETE(_uimanager);
}

void LogScreen::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();

	_back.Load(BACK_BUTTON_IDLE, BACK_BUTTON_IDLE);
	_back.SetGlowImage(BACK_BUTTON_GLOW);
	_back.SetCoordinates(50, LOGICAL_HEIGHT - 200);
	_back.SetHandler(this);
	_back.SetID(0);
	_uimanager->Add(&_back);

	
	_scroll_box.Init();
	_scroll_box.Load();
	_scroll_box.SetCoordinates(350, 80);
	_uimanager->Add(&_scroll_box);	
}

void LogScreen::OnLoad()
{
	
}

void LogScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID()) {
	case 0:	//back button
		Hide();
		break;
	}
}
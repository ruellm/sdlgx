#include "TomTalkScreen.h"
#include "UIManager.h"
#include "definitions.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;

TomTalkScreen::TomTalkScreen() : SceneFader()
{
	SetID(TOMTALK_SCREEN);
}

TomTalkScreen::~TomTalkScreen()
{
	SAFE_DELETE(_uimanager);
}

void TomTalkScreen::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();

	int button_height = 134;
	char options[][16] = { "Guilty","He didn't do it"};

	int x = 600;
	int y = 200;

	for (int i = 0; i < 2; i++) {
		_options[i].Load(FINAL_BOX_MENU_IMG, FINAL_BOX_MENU_IMG);
		_options[i].SetGlowImage(FINAL_BOX_MENU_GLOW_IMG, 1);
		_options[i].SetTextParam(options[i], FONT_MYRIADPRO_REGULAR, 60, { 255,255,255 }, { 0,0,255 });
		_options[i]._x = x;
		_options[i]._y = y;
		_options[i].SetID(i);
		_options[i].SetHandler(this);
		_uimanager->Add(&_options[i]);

		y += button_height + 50;
	}
}

void TomTalkScreen::OnLoad()
{

}

void TomTalkScreen::OnUpdate(float elapsed)
{
	SceneFader::OnUpdate(elapsed);
	_uimanager->OnUpdate(elapsed);
}

void TomTalkScreen::OnInternalDraw()
{
	_uimanager->OnDraw();
}

void TomTalkScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	_selected = b->GetID();
	Hide();
}

int TomTalkScreen::GetSelectedIdx()
{
	return _selected;
}

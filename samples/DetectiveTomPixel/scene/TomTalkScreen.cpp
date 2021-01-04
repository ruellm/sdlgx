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

	int button_width = 300;
	int button_height = 50;
	int gap = 20;
	char options[][16] = { "Guilty","He didn't do it" };

	int x = 234;
	int y = 62;

	for (int i = 0; i < 2; i++) {
		_options[i].Set(x, y, button_width, button_height);
		_options[i].SetRectColor(255, 255, 255);
		_options[i].SetHighlightColor(0, 0, 240);
		_options[i].SetTextParam(options[i], FONT_MANASPACE, 20, { 255,255,255 }, { 255,0,0 });
		_options[i]._x = x;
		_options[i]._y = y;
		_options[i].SetID(i);
		_options[i].SetHandler(this);
		_uimanager->Add(&_options[i]);

		y += button_height + gap;
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

#include "EmmaTalkScreen.h"
#include "UIManager.h"
#include "definitions.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;

EmmaTalkScreen::EmmaTalkScreen() : SceneFader()
{
	SetID(EMMATALK_SCREEN);

	_choice_flag[0] = false;
	_choice_flag[1] = false;
	_choice_flag[2] = false;

}

EmmaTalkScreen::~EmmaTalkScreen()
{
	SAFE_DELETE(_uimanager);
}

void EmmaTalkScreen::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();

	int button_width = 300;
	int button_height = 50;
	int gap = 20;
	char options[][15] = { "The Victim","The Suspect","The Murder" };

	int x = 109;
	int y = 56;

	for (int i = 0; i < 3; i++) {
		
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

void EmmaTalkScreen::OnLoad()
{

}

void EmmaTalkScreen::OnUpdate(float elapsed)
{
	SceneFader::OnUpdate(elapsed);
	_uimanager->OnUpdate(elapsed);
}

void EmmaTalkScreen::OnInternalDraw()
{
	_uimanager->OnDraw();
}

void EmmaTalkScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	_selected = b->GetID();
	_choice_flag[_selected] = true;
	//Hide();

	if (_handler != NULL) {
		_handler->PopupClose(GetStateID());
	}
}

int EmmaTalkScreen::GetSelectedIdx()
{
	return _selected;
}

bool EmmaTalkScreen::IsComplete()
{
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		if (_choice_flag[i])
			cnt++;
	}

	if (cnt >= 3)
		return true;
	return false;
}
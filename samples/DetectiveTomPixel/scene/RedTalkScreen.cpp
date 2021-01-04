#include "RedTalkScreen.h"
#include "UIManager.h"
#include "definitions.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;

RedTalkScreen::RedTalkScreen() : SceneFader()
{
	SetID(REDTALK_SCREEN);

	_choice_flag[0] = false;
	_choice_flag[1] = false;
	_choice_flag[2] = false;

}

RedTalkScreen::~RedTalkScreen()
{
	SAFE_DELETE(_uimanager);
}

void RedTalkScreen::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();

	char options[][21] = { "Peaches and Apricots","Poison","Teacher's death" };

	int button_width = 300;
	int button_height = 50;
	int gap = 20;
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

	_options[2].SetVisible(false);
}

void RedTalkScreen::OnLoad()
{
	if (_choice_flag[0] && _choice_flag[1])
		_options[2].SetVisible(true);
}

void RedTalkScreen::OnUpdate(float elapsed)
{
	SceneFader::OnUpdate(elapsed);
	_uimanager->OnUpdate(elapsed);
}

void RedTalkScreen::OnInternalDraw()
{
	_uimanager->OnDraw();
}

void RedTalkScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	_selected = b->GetID();
	_choice_flag[_selected] = true;
	
	Hide();
}

int RedTalkScreen::GetSelectedIdx()
{
	return _selected;
}

bool RedTalkScreen::IsComplete()
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
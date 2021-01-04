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

	int button_height = 134;
	char options[][21] = { "Peaches and Apricots","Poison","Teacher's death" };

	int x = 100;
	int y = 200;

	for (int i = 0; i < 3; i++) {
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
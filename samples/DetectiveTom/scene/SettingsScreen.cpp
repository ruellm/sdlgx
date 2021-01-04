#include "SettingsScreen.h"
#include "definitions.h"
#include "uimanager.h"
#include "font.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::scene;
using namespace sdlgx::core;

SettingScreen::SettingScreen()
{
	SetID(SETTINGS_SCREEN);
	for (int i = 0;i < 5;i++) {
		_text[i] = NULL;
	}
}

SettingScreen::~SettingScreen()
{
	SAFE_DELETE(_uimanager);

	for (int i = 0;i < 5;i++) {
		SAFE_DELETE(_text[i]);
	}
}

void SettingScreen::OnLoad()
{}

void SettingScreen::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();

	char text[][20] = {
		"SFX:",
		"BGM:",
		"Voices:",
		"Text Speed:",
		"Screen Reso:"
	};

	int sy = 140;
	int gap = 30;
	int cx = (LOGICAL_WIDTH / 2) - 130;

	for (int m = 0;m < 5;m++) {
		_text[m] = SDLGX_GetText(text[m], FONT_MYRIADPRO_REGULAR, 50, { 255,255,255 });
		
		if (m < 4) {
			_scrollbar[m].SetBarImage(SETTINGS_BAR_IMG);
			_scrollbar[m].SetThumbImage(SETTINGS_BAR_DRAG_IMG);
			_scrollbar[m].SetType(SCROLLBAR_HORIZONTAL);
			_scrollbar[m].SetButton1Param(LEFT_BUTTON_IMG, LEFT_BUTTON_GLOW_IMG);
			_scrollbar[m].SetButton2Param(RIGHT_BUTTON_IMG, RIGHT_BUTTON_GLOW_IMG);			
			_scrollbar[m].SetCoordinates(cx + gap, sy);
			_scrollbar[m].Refresh();
			_uimanager->Add(&_scrollbar[m]);
		}
		else {
			char values[][20] = {
				"item1",
				"item2",
				"item3",
				"item4",
			};

			_combobox.Load(values, 4);
			_combobox.SetCoordinates(cx + gap+60, sy);
			_combobox.SetTextBoxImg(DROP_DOWN_TXTBOX_IMG);
			_combobox.SetToggleButton(DOWN_BUTTON_IMG, DOWN_BUTTON_TOGLD_IMG, DROP_DOWN_GLOW_IMG);
			_uimanager->Add(&_combobox);
		}

		_text[m]->SetCoordinates(cx - _text[m]->GetWidth(), sy+20);		
		sy += 120;
	}

	_back.Load(BACK_BUTTON_IDLE, BACK_BUTTON_IDLE);
	_back.SetGlowImage(BACK_BUTTON_GLOW);
	_back.SetCoordinates(50, LOGICAL_HEIGHT - 200);
	_back.SetHandler(this);
	_back.SetID(0);
	_uimanager->Add(&_back);
}

void SettingScreen::OnUpdate(float elapsed)
{
	SceneFader::OnUpdate(elapsed);
	_uimanager->OnUpdate(elapsed);
}

void SettingScreen::OnInternalDraw()
{	
//	SDL_SetRenderDrawColor(CURRENT_RENDERER, 0, 0, 0, 0xFF);
//	SDL_RenderFillRect(CURRENT_RENDERER, NULL);
	for (int m = 0;m < 5;m++) {
		_text[m]->Draw();
	}
	_uimanager->OnDraw();
}

void SettingScreen::OnClose()
{

}

bool SettingScreen::OnEvent(SDL_Event* e)
{
	return State::OnEvent(e);
}

void SettingScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID())
	{
	case 0://back
		//Engine::GetInstance()->ChangeState(MAIN_MENU_STATE, TRANSITION_FADE);
		Hide();
		break;
	}
}
#include "ExitScreen.h"
#include "definitions.h"
#include "uimanager.h"
#include "engine.h"
#include "font.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;
using namespace sdlgx::scene;

ExitScreen::ExitScreen():
	_status(EXIT_STATUS_NO),
	_text(NULL)
{
	SetID(EXIT_SCREEN);
}

ExitScreen::~ExitScreen()
{
	SAFE_DELETE(_text);
	SAFE_DELETE(_uimanager);
}

void ExitScreen::OnInitialize()
{
	SceneFader::Load(0, 0);
	_uimanager = new UIManager();
	_bg.LoadFromResource(EXIT_WINDOW_IMG);
	
	int x = (LOGICAL_WIDTH / 2) - (_bg.GetWidth() / 2);
	int y = (LOGICAL_HEIGHT / 2) - (_bg.GetHeight() / 2);
	_bg.SetCoordinates(x, y);

	_text = SDLGX_GetText("ARE YOU SURE YOU WANT TO QUIT?", FONT_MYRIADPRO_REGULAR, 50, { 79,202,255 });
	x = (LOGICAL_WIDTH / 2) - (_text->GetWidth() / 2);
	_text->SetCoordinates(x, y + 200);

	int gap = 250;
	int buttonWidth = 247;
	int totalwidth = (buttonWidth + gap) * 2;
	int buttonX = (LOGICAL_WIDTH / 2) - (totalwidth/2);
	int buttonY = y + 400;
	
	_yesBtn.Load(YES_NO_BUTTON_IMG, YES_NO_BUTTON_IMG);
	_yesBtn.SetGlowImage(YES_NO_BUTTON_GLOW_IMG, 1);
	_yesBtn.SetTextParam("YES", FONT_MYRIADPRO_REGULAR, 60, { 79,202,255 }, { 255,255,255 });
	_yesBtn._x = buttonX;
	_yesBtn._y = buttonY;
	_yesBtn.SetID(0);
	_yesBtn.SetHandler(this);
	_uimanager->Add(&_yesBtn);

	buttonX += buttonWidth + gap + gap;
	_noBtn.Load(YES_NO_BUTTON_IMG, YES_NO_BUTTON_IMG);
	_noBtn.SetGlowImage(YES_NO_BUTTON_GLOW_IMG, 1);
	_noBtn.SetTextParam("NO", FONT_MYRIADPRO_REGULAR, 60, { 79,202,255 }, { 255,255,255 });
	_noBtn._x = buttonX;
	_noBtn._y = buttonY;
	_noBtn.SetID(1);
	_noBtn.SetHandler(this);
	_uimanager->Add(&_noBtn);

}

void ExitScreen::OnInternalDraw()
{
	_bg.Draw();
	_text->Draw();
	_uimanager->OnDraw();
}

enum ExitStatus ExitScreen::GetStatus()
{
	return _status;
}

void ExitScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	if (b->GetID() == 0)
		_status = EXIT_STATUS_YES;
	else
		_status = EXIT_STATUS_NO;

	Hide();
}


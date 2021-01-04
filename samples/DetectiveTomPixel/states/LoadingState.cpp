#include "LoadingState.h"
#include "definitions.h"
#include "font.h"
#include "engine.h"

using namespace sdlgx::core;
using namespace sdlgx::resource;
using namespace sdlgx::scene;

// Image definitions
ResourceDef img_resource[] = {
	{"images/bg/bg1.png",				TUTORIAL_BG_IMG ,			0, false},
	{ "images/game_screen/xeUgi.png",	IRIS_IMG,					0, false },
	{ "images/common/pixel filter.png",	BLACK_LINES_OVERLAY_IMG, 	0, false },
	{ "images/common/text box.png",		TEXT_BOX_IMG, 				0, false },
	{ "images/common/text box next.png",FORWARD_BUTTON_IMG, 		0, false },
	{ "images/common/pause button.png",	PIN_BUTTON_IMG, 			0, false },
	{ "images/common/back button.png",	BACK_BUTTON_IMG, 			0, false },

	{ "images/pause_menu/pause CaseFile.png",	CASEFILE_BUTTON_IMG, 	0, false },
	{ "images/pause_menu/pause SaveLoad.png",	SAVELOG_BUTTON_IMG, 	0, false },
	{ "images/pause_menu/pause Logs.png",		LOGS_BUTTON_IMG, 		0, false },
	{ "images/pause_menu/pause Settings.png",	SETTINGS_BUTTON_IMG, 	0, false },
	{ "images/pause_menu/pause Exit.png",		EXIT_BUTTON_IMG, 		0, false },

	{ "images/case_file/Case File Description.png",	CASE_FILE_BOX_IMG ,			0,	false},
	{ "images/case_file/case file bar.png",			CASE_FILE_SCROLLBAR_IMG,	0,	false },
	{ "images/case_file/case file scroll bar.png",	CASE_FILE_DRAG_IMG,			0,	false },
	{ "images/case_file/Case File Base.png",			CASE_FILE_BASE_IMG,			0,	false },
	{ "images/case_file/case file left button.png",	CHOICE_SCROLL_LEFT_IMG,			0,	false },
	{ "images/case_file/case file right button.png",	CHOICE_SCROLL_RIGHT_IMG,			0,	false },
	{ "images/case_file/show.png",					SHOW_BUTTON_IMG,			0,	false },
	{ "images/case_file/case file profile clues.png", CLUES_BUTTON_IMG,			0,	false },

};

// Font definitions
struct FontDefinitiion g_fonts[] = {
	{ "fonts/manaspc.ttf", FONT_MANASPACE, 100 }
};

int resource_total = sizeof(img_resource) / sizeof(ResourceDef);
int resource_loaded = 0;

LoadingState::LoadingState() 
	: State(LOADING_STATE)
{
}


LoadingState::~LoadingState()
{
}

void LoadingState::OnLoad()
{

}

void LoadingState::OnInitialize()
{
	SDLGX_InitFontDef(g_fonts, 1);

	ResourceManager::GetInstance()->LoadAsync(img_resource, resource_total,
		this);
}

void LoadingState::OnUpdate(float elapsed)
{
	//...
}

void LoadingState::OnDraw()
{
	float percent = ((float)resource_loaded / (float)resource_total) * 100.0f;
	char text[10];
	sprintf(text, "%.0f%%", percent);
	SDL_Color color = { 255,255,255 };

	int x = (LOGICAL_WIDTH / 2);
	int y = (LOGICAL_HEIGHT / 2);
	SDLGX_DrawTextCenter(x, y, text, FONT_MANASPACE, 25, color);

	if (percent >= 100.0f) {
		SDLGX_DrawTextCenter(x, y + 30, "Press any key to continue...", FONT_MANASPACE, 10, color);
	}
}

void LoadingState::OnClose()
{}

void LoadingState::OnResourceLoad(int index)
{
	resource_loaded++;
}

bool LoadingState::OnKeyDown(SDL_Keycode sym)
{
	if (resource_loaded < resource_total) return true;
	Engine::GetInstance()->ChangeState(PRELUDE_DIALOG_STATE, TRANSITION_FADE);
	return true;
}
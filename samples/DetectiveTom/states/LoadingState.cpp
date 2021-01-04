#include "LoadingState.h"
#include "definitions.h"
#include "font.h"
#include "engine.h"

using namespace sdlgx::core;
using namespace sdlgx::resource;
using namespace sdlgx::scene;

// Image definitions
ResourceDef img_resource[] = {
	{"images/main_menu/Menu Test screen.png",			MAIN_MENU_BG_IMG ,			0, false},
	{"images/gui_common/button870x127.png",				BUTTON_870x127_IMG ,		0, false },
	{"images/gui_common/button870x127_hover.png",		BUTTON_870x127_HOVER_IMG ,	0, false },
	{"images/gui_common/Back Button Aura.png",			BACK_BUTTON_GLOW ,	0 },
	{"images/gui_common/Back Button Idle.png",			BACK_BUTTON_IDLE ,	0 },

	{"images/settings/Bar Drag.png",					SETTINGS_BAR_DRAG_IMG ,		0, false },
	{"images/settings/Bar.png",							SETTINGS_BAR_IMG ,			0, false },
	{"images/settings/Left Button.png",					LEFT_BUTTON_IMG ,			0, false },
	{"images/settings/Right Button.png",				RIGHT_BUTTON_IMG ,			0, false },
	{"images/settings/settings aura left.png",			LEFT_BUTTON_GLOW_IMG ,		0, false },
	{"images/settings/settings aura right.png",			RIGHT_BUTTON_GLOW_IMG ,		0, false },
	{"images/settings/drop down aura.png",				DROP_DOWN_GLOW_IMG ,		0, false },
	{"images/settings/Drop down text box.png",			DROP_DOWN_TXTBOX_IMG ,		0, false },
	{"images/settings/Resolutuon Drop down Idle.png",	DOWN_BUTTON_IMG ,			0, false },
	{"images/settings/Resolution Drop down Toggle.png",	DOWN_BUTTON_TOGLD_IMG ,		0, false },
	//{"images/game_screen/bg/Map final.png",				TEST_BG_IMG ,				0 },
	{"images/game_screen/pin no glow.png",				PIN_BUTTON_IMG ,			0, false },
	{"images/game_screen/Pin Glow.png",					PIN_GLOW_IMG ,				0, false },
	{"images/game_screen/Black lines overlay layer.png",BLACK_LINES_OVERLAY_IMG ,	0, false },
	{"images/pause_menu/Case File button.png",			CASEFILE_BUTTON_IMG,		0, false },
	{"images/pause_menu/Save Load button.png",			SAVELOG_BUTTON_IMG,			0, false },
	{"images/pause_menu/Logs.png",						LOGS_BUTTON_IMG,			0, false },
	{"images/pause_menu/Settings button.png",			SETTINGS_BUTTON_IMG,		0, false },
	{"images/pause_menu/EXIT button.png",				EXIT_BUTTON_IMG,			0, false },
	{"images/pause_menu/Pause Menu Icon Aura.png",		PAUSE_BUTTON_GLOW_IMG,		0, false },
	{"images/case_file/Case File Base.png",				CASE_FILE_BASE_IMG,			0, false },
	{"images/case_file/Back Button Idle.png",			BACK_BUTTON_IMG,			0, false },
	{"images/case_file/Back Button Hover aura.png",		BACK_BUTTON_GLOW_IMG,		0, false },
	{"images/case_file/Choices Scrol rightl.png",		CHOICE_SCROLL_RIGHT_IMG,	0, false },
	{"images/case_file/Choices Scroll.png",				CHOICE_SCROLL_LEFT_IMG,		0, false },
	{ "images/case_file/choices scroll aura.png",		CHOICE_GLOW_IMG,			0, false },
	{ "images/case_file/Case File FG.png",				CASE_FILE_FG_IMG,			0, false },
	{ "images/case_file/sample_case/1.png",				SAMPLE_CASE_1_IMG,			0, false },
	{ "images/case_file/sample_case/2.png",				SAMPLE_CASE_2_IMG,			0, false },
	{ "images/case_file/clues highlight hover.png",		CASE_ITEM_HIGLIGHT_IMG,		0, false },

	{ "images/case_file/Clues.png",						CLUES_BUTTON_IMG,			0, false },
	{ "images/case_file/Clues aura.png",					CLUES_BUTTON_GLOW_IMG,		0, false },
	{ "images/case_file/Profiles.png",					PROFILES_BUTTON_IMG,		0, false },
	{ "images/case_file/Profiles Aura.png",				PROFILES_BUTTON_GLOW_IMG,	0, false },

	{ "images/case_file/Case File Big box.png",			CASE_FILE_BOX_IMG,			0, false },
	{ "images/case_file/Case File Line Drag.png",		CASE_FILE_SCROLLBAR_IMG,	0, false },
	{ "images/case_file/Case File Drag Thumb.png",		CASE_FILE_DRAG_IMG,			0, false },

	{ "images/case_file/sample_case/clues test 1.png",	SAMPLE_CLUES_1_IMG,			0, false },
	{ "images/case_file/sample_case/clues test 2.png",	SAMPLE_CLUES_2_IMG,			0, false },
	{ "images/case_file/sample_case/clues test 3.png",	SAMPLE_CLUES_3_IMG,			0, false },

	{ "images/logs_screen/Logs Scroll Line.png",		LOGS_SCROLL_LINE_IMG,		0, false },
	{ "images/logs_screen/Logs Window.png",				LOGS_WINDOW_IMG,			0, false },
	{ "images/logs_screen/Scroll Drag bar.png",			LOGS_SCROLL_DRAG_IMG,		0, false },

	{ "images/exit_screen/Quin Window.png",				EXIT_WINDOW_IMG,			0, false },
	{ "images/exit_screen/Yes No Button.png",			YES_NO_BUTTON_IMG,			0, false },
	{ "images/exit_screen/Yes No Button Aura.png",		YES_NO_BUTTON_GLOW_IMG,		0, false },

	//{ "images/game_screen/sprites/tom sprite sheet.png",SAMPLE_TOM_SPRITE_SHEET,	0, false },	
	{ "images/game_screen/Final Text Box.png",			TEXT_BOX_IMG,				0, false },

	{ "images/game_screen/Forward Button.png",			FORWARD_BUTTON_IMG,			0, false },
	{ "images/game_screen/Forward Button Hover.png",	FORWARD_HOVER_IMG,			0, false },

	{ "images/game_screen/bg/Tutorial BG.png",			TUTORIAL_BG_IMG,			0, false },
	{ "images/game_screen/xeUgi.png",					IRIS_IMG,					0, false },

	{ "images/game_screen/sprites/Tom.png",				SAMPLE_TOM_SPRITE_SHEET,	0, false },
	{ "images/game_screen/sprites/Emma.png",			SAMPLE_EMMA_SPRITE_SHEET,	0, false },

	{ "images/game_screen/Final Menu Box.png",			FINAL_BOX_MENU_IMG,			0, false },
	{ "images/game_screen/Final Menu Box glow.png",		FINAL_BOX_MENU_GLOW_IMG,	0, false },

	{ "images/evidence/ridgeony_ico.png",				RIDGEONY_IMG,				0, false },
	{ "images/evidence/redyoung_ico.png",				REDYOUNG_IMG,				0, false },
	{ "images/evidence/test result_E.png",				EMMA_TEST_RESULT_IMG,		0, false },
	{ "images/evidence/coffee_ico.png",					CUP_OF_COFFEE_IMG,			0, false },

	{ "images/game_screen/sprites/red.png",				SAMPLE_RED_SPRITE_SHEET,	0, false },
	{ "images/evidence/test result_R.png",				RED_TEST_RESULT_IMG,		0, false },

	{ "images/case_file/Show button.png",				SHOW_BUTTON_IMG,			0, false },
	{ "images/case_file/Show button glow.png",			SHOW_BUTTON_GLOW_IMG,		0, false },

	{ "images/evidence/calling card_ico.png",			CALLING_CARD_IMG,			0, false },
	{ "images/evidence/organizer_ico.png",				ORGANIZER_IMG,				0, false },
	{ "images/evidence/research HCN_ico.png",			HCN_RESEARCH_IMG,			0, false },

	{ "images/comic/0/Apricot Peach comic 1.png",		APPRICOT_PEACHES_COMIC1,	0, false },
	{ "images/comic/0/Apricot Peach comic 2.png",		APPRICOT_PEACHES_COMIC2,	0, false },
	{ "images/comic/0/Apricot Peach comic 3.png",		APPRICOT_PEACHES_COMIC3,	0, false },
	{ "images/evidence/test result_T.png",				TOMS_TEST_RESULT_IMG,		0, false },
	{ "images/evidence/deliveryslip_ico.png",			DELIVERY_SLIP_IMG,		0, false },
	
	{ "images/game_screen/sprites/0/eb_i.png",			BATCH_0_SPRITES + 0,	0, true },
	{ "images/game_screen/sprites/0/eb_m_1.png",		BATCH_0_SPRITES + 1,	0, true },
	{ "images/game_screen/sprites/0/eb_m_2.png",		BATCH_0_SPRITES + 2,	0, true },
	{ "images/game_screen/sprites/0/eb_m_3.png",		BATCH_0_SPRITES + 3,	0, true },
	{ "images/game_screen/sprites/0/Ef_a_1.png",		BATCH_0_SPRITES + 4,	0, true },
	{ "images/game_screen/sprites/0/Ef_a_2.png",		BATCH_0_SPRITES + 5,	0, true },
	{ "images/game_screen/sprites/0/Ef_a_3.png",		BATCH_0_SPRITES + 6,	0, true },
	{ "images/game_screen/sprites/0/Ef_a_4.png",		BATCH_0_SPRITES + 7,	0, true },
	{ "images/game_screen/sprites/0/ef_m_1.png",		BATCH_0_SPRITES + 8,	0, true },
	{ "images/game_screen/sprites/0/ef_m_2.png",		BATCH_0_SPRITES + 9,	0, true },
	{ "images/game_screen/sprites/0/es.png",			BATCH_0_SPRITES + 10,	0, true },
	{ "images/game_screen/sprites/0/esd_b.png",			BATCH_0_SPRITES + 11,	0, true },
	{ "images/game_screen/sprites/0/esd_i.png",			BATCH_0_SPRITES + 12,	0, true },
	{ "images/game_screen/sprites/0/esd_m.png",			BATCH_0_SPRITES + 13,	0, true },
	{ "images/game_screen/sprites/0/et1_i.png",			BATCH_0_SPRITES + 14,	0, true },
	{ "images/game_screen/sprites/0/et1_m_1.png",		BATCH_0_SPRITES + 15,	0, true },
	{ "images/game_screen/sprites/0/et1_m_2.png",		BATCH_0_SPRITES + 16,	0, true },
	{ "images/game_screen/sprites/0/et1_m_3.png",		BATCH_0_SPRITES + 17,	0, true },
	{ "images/game_screen/sprites/0/et2_i_1.png",		BATCH_0_SPRITES + 18,	0, true },
	{ "images/game_screen/sprites/0/et2_i_2.png",		BATCH_0_SPRITES + 19,	0, true },
	{ "images/game_screen/sprites/0/et2_m_1.png",		BATCH_0_SPRITES + 20,	0, true },
	{ "images/game_screen/sprites/0/et2_m_2.png",		BATCH_0_SPRITES + 21,	0, true },
	{ "images/game_screen/sprites/0/et2_m_3.png",		BATCH_0_SPRITES + 22,	0, true },
	{ "images/game_screen/sprites/0/et3_i_1.png",		BATCH_0_SPRITES + 23,	0, true },
	{ "images/game_screen/sprites/0/et3_i_2.png",		BATCH_0_SPRITES + 24,	0, true },
	{ "images/game_screen/sprites/0/et3_i_3.png",		BATCH_0_SPRITES + 25,	0, true },
	{ "images/game_screen/sprites/0/et3_m_1.png",		BATCH_0_SPRITES + 26,	0, true },
	{ "images/game_screen/sprites/0/et3_m_2.png",		BATCH_0_SPRITES + 27,	0, true },
	{ "images/game_screen/sprites/0/et3_m_3.png",		BATCH_0_SPRITES + 28,	0, true },
	{ "images/game_screen/sprites/0/et3_m_4.png",		BATCH_0_SPRITES + 29,	0, true },
	{ "images/game_screen/sprites/0/et_A.png",			BATCH_0_SPRITES + 30,	0, true },
	{ "images/game_screen/sprites/0/et_i.png",			BATCH_0_SPRITES + 31,	0, true },
	{ "images/game_screen/sprites/0/et_m_1.png",		BATCH_0_SPRITES + 32,	0, true },
	{ "images/game_screen/sprites/0/et_m_2.png",		BATCH_0_SPRITES + 33,	0, true },
	{ "images/game_screen/sprites/0/et_m_3.png",		BATCH_0_SPRITES + 34,	0, true },

	{ "images/game_screen/sprites/0/yrf_i.png",			BATCH_0_SPRITES + 35,	0, true },
	{ "images/game_screen/sprites/0/yrf_m.png",			BATCH_0_SPRITES + 36,	0, true },
	{ "images/game_screen/sprites/0/yr_i.png",			BATCH_0_SPRITES + 37,	0, true },
	{ "images/game_screen/sprites/0/yr_t.png",			BATCH_0_SPRITES + 38,	0, true },

	{ "images/game_screen/sprites/0/ytj_1.png",			BATCH_0_SPRITES + 39,	0, true },
	{ "images/game_screen/sprites/0/ytj_2.png",			BATCH_0_SPRITES + 40,	0, true },
	{ "images/game_screen/sprites/0/ytn_a_1.png",		BATCH_0_SPRITES + 41,	0, true },
	{ "images/game_screen/sprites/0/ytn_a_2.png",		BATCH_0_SPRITES + 42,	0, true },
	{ "images/game_screen/sprites/0/ytn_a_3.png",		BATCH_0_SPRITES + 43,	0, true },
	{ "images/game_screen/sprites/0/ytn_l_1.png",		BATCH_0_SPRITES + 44,	0, true },
	{ "images/game_screen/sprites/0/ytn_l_2.png",		BATCH_0_SPRITES + 45,	0, true },
	{ "images/game_screen/sprites/0/ytn_m.png",			BATCH_0_SPRITES + 46,	0, true },
	{ "images/game_screen/sprites/0/yts_1.png",			BATCH_0_SPRITES + 47,	0, true },
	{ "images/game_screen/sprites/0/yts_2.png",			BATCH_0_SPRITES + 48,	0, true },
	{ "images/game_screen/sprites/0/yts_3.png",			BATCH_0_SPRITES + 49,	0, true },
	{ "images/game_screen/sprites/0/yts_4.png",			BATCH_0_SPRITES + 50,	0, true },
	{ "images/game_screen/sprites/0/ytt1_i.png",		BATCH_0_SPRITES + 51,	0, true },
	{ "images/game_screen/sprites/0/ytt1_m_1.png",		BATCH_0_SPRITES + 52,	0, true },
	{ "images/game_screen/sprites/0/ytt1_m_2.png",		BATCH_0_SPRITES + 53,	0, true },
	{ "images/game_screen/sprites/0/ytt2_i.png",		BATCH_0_SPRITES + 54,	0, true },
	{ "images/game_screen/sprites/0/ytt2_m_1.png",		BATCH_0_SPRITES + 55,	0, true },
	{ "images/game_screen/sprites/0/ytt2_m_2.png",		BATCH_0_SPRITES + 56,	0, true },
	{ "images/game_screen/sprites/0/ytt3_i.png",		BATCH_0_SPRITES + 57,	0, true },
	{ "images/game_screen/sprites/0/ytt3_m_1.png",		BATCH_0_SPRITES + 58,	0, true },
	{ "images/game_screen/sprites/0/ytt3_m_2.png",		BATCH_0_SPRITES + 59,	0, true },
	{ "images/game_screen/sprites/0/ytt4_a.png",		BATCH_0_SPRITES + 60,	0, true },
	{ "images/game_screen/sprites/0/ytt4_i.png",		BATCH_0_SPRITES + 61,	0, true },
	{ "images/game_screen/sprites/0/ytt4_m_1.png",		BATCH_0_SPRITES + 62,	0, true },
	{ "images/game_screen/sprites/0/ytt4_m_2.png",		BATCH_0_SPRITES + 63,	0, true },
	{ "images/game_screen/sprites/0/yttk_a_1.png",		BATCH_0_SPRITES + 64,	0, true },
	{ "images/game_screen/sprites/0/yttk_a_2.png",		BATCH_0_SPRITES + 65,	0, true },
	{ "images/game_screen/sprites/0/yttk_i.png",		BATCH_0_SPRITES + 66,	0, true },
	{ "images/game_screen/sprites/0/yttk_m_1.png",		BATCH_0_SPRITES + 67,	0, true },
	{ "images/game_screen/sprites/0/yttk_m_2.png",		BATCH_0_SPRITES + 68,	0, true },
};


// Font definitions
struct FontDefinitiion g_fonts[] = {
	{ "fonts/MyriadPro-Regular.ttf", FONT_MYRIADPRO_REGULAR, 100 }
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

}

void LoadingState::OnDraw()
{
	
	float percent = ((float)resource_loaded / (float)resource_total) * 100.0f;
	char text[10];
	sprintf(text, "%.0f%%", percent);
	SDL_Color color = { 255,255,255 };

	int x = (LOGICAL_WIDTH / 2);
	int y = (LOGICAL_HEIGHT / 2);
	SDLGX_DrawTextCenter(x, y, text, FONT_MYRIADPRO_REGULAR, 100, color);

	if (percent >= 100.0f) {
		SDLGX_DrawTextCenter(x, y + 300, "Press any key to continue...", FONT_MYRIADPRO_REGULAR, 50, color);
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
	Engine::GetInstance()->ChangeState(MAIN_MENU_STATE, TRANSITION_FADE);
	return true;
}
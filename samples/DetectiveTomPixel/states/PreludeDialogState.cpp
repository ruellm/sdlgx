#include "PreludeDialogState.h"
#include "font.h"
#include "engine.h"
#include "definitions.h"
#include "uimanager.h"
#include "FileDialogParser.h"
#include "GameData.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sdlgx::scene;
using namespace sdlgx::core;
using namespace sdlgx::gui;
using namespace sdlgx::resource;

#define PRELUDE_CHARACTER_TOM		0
#define PRELUDE_CHARACTER_EMMA		1
#define PRELUDE_CHARACTER_RED		2


ResourceDef pre_img_resource[] = {
	{ "images/evidence/calling card.png",		CALLING_CARD_IMG ,			0, false },
	{ "images/evidence/coffee.png",				CUP_OF_COFFEE_IMG ,			0, false },
	{ "images/evidence/delivery.png",			DELIVERY_SLIP_IMG ,			0, false },
	//{ "images/evidence/emma profile.png",		TUTORIAL_BG_IMG ,			0, false },
	{ "images/evidence/hcn research.png",		HCN_RESEARCH_IMG ,			0, false },
	{ "images/evidence/organizer.png",		    ORGANIZER_IMG ,				0, false },
	{ "images/evidence/red profile.png",		REDYOUNG_IMG ,				0, false },
	{ "images/evidence/ridge ony profile.png",	RIDGEONY_IMG ,				0, false },
	{ "images/evidence/test result_E.png",		EMMA_TEST_RESULT_IMG ,		0, false },
	{ "images/evidence/test result_R.png",		RED_TEST_RESULT_IMG ,		0, false },
	{ "images/evidence/test result_T.png",		TOMS_TEST_RESULT_IMG ,		0, false },
	//{ "images/evidence/tom profile.png",		TUTORIAL_BG_IMG ,			0, false },
};

extern int resource_total;
extern int resource_loaded;

PreludeDialogState::PreludeDialogState()
	: State(PRELUDE_DIALOG_STATE), _prelude_text(NULL),
	_bg(NULL), _iris_size(100), _pop_up(NULL),
	_evidence(NULL), /*_pause(false),*/ _active_character(-1),
	_next_process(-1)
{
}

PreludeDialogState::~PreludeDialogState()
{
	SAFE_DELETE(_uimanager);
	SAFE_DELETE(_prelude_text);
	SAFE_DELETE(_bg);
	SAFE_DELETE(_evidence);
	ClearCommands(_command_list);
	ClearCommands(_emma_talk_A);
	ClearCommands(_emma_talk_B);
	ClearCommands(_emma_talk_C);
	ClearCommands(_dialog_1_cmd);
	ClearCommands(_dialog_2_cmd);
	ClearCommands(_dialog_3_cmd);	
	ClearCommands(_tom_talk_A);
	ClearCommands(_tom_talk_B);
	ClearCommands(_red_talk_A);
	ClearCommands(_red_talk_B);
	ClearCommands(_red_talk_C);

	for (int i = 0; i < _characters.size();i++) {
		Character* c = _characters.at(i);
		SAFE_DELETE(c);
	}
	
}

void PreludeDialogState::OnLoad()
{
	InitDialog();
	LoadTextIntro();
	LoadCommands();
	InitializePopups();
	TalkScreenBase::Load();
	LoadResource();
}

void PreludeDialogState::OnInitialize()
{

	_uimanager = new UIManager();

	_pinButton.Load(PIN_BUTTON_IMG);
	_pinButton.SetHandler(this);
	_pinButton.SetID(PIN_BUTTON);
	_pinButton.SetCoordinates(8, 8);
	_uimanager->Add(&_pinButton);

	_blackscreen.Create();
}

void PreludeDialogState::OnUpdate(float elapsed)
{
	if (_pop_up) {
		_pop_up->OnUpdate(elapsed);
		//return;
	}

	switch (_state)
	{
	case PRELUDE_RESOURCE_LOADING:
	case PRELUDE_SPRITE_LOADING:
		return;
		
	case PRELUDE_DIAG_STATE_INTRO:
		UpdateTextIntro(elapsed);
		break;
	case PRELUDE_DIAG_STATE_TYPING: {
		UpdateTalkDialog(elapsed);
		
		//draw the characters
		for (int i = 0; i < _characters.size();i++) {
			_characters.at(i)->OnUpdate(elapsed);
		}

		}break;
	case PRELUDE_DIAG_IRIS: {
		_iris_size += 2000 * elapsed;
		
		int end_size = 500;
		if (_iris_size > LOGICAL_WIDTH+ end_size) {
	
			OnPauseDialog(2);
			_iris.Destroy();

			break;
		}
		}break;

	/*case PRELUDE_DIAG_PAUSE: {
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _lastTime) / 1000.0f;
		if (diff >= _pause_value) {
			_state = _save_state;
		}

	}break;
	*/

	case PRELUDE_GENERIC_PAUSE:
	{
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _lastTime) / 1000.0f;
		if (diff >= _pause_value) {
			OnNextProcess();
			_next_process = -1; // reset
		}
	}break;

	/*case PRELUDE_DIAG_PAUSE_0: {	//<-- needs to be reviewed to be common
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _lastTime) / 1000.0f;
		if (diff >= _pause_value) {
			_state = PRELUDE_DIAG_STATE_TYPING;
			ProcessNextCommand();
		}
		else {
			//draw the characters
			for (int i = 0; i < _characters.size();i++) {
				_characters.at(i)->OnUpdate(elapsed);
			}
		}
		
		}break;
		*/
	/*case PRELUDE_APPRPREC_COMIC:
	case PRELUDE_DIAG_TOM_TALK:
	case PRELUDE_DIAG_EMMA_TALK: {
		_pop_up->OnUpdate(elapsed);
		}break;
		*/
	case PRELUDE_DIAG_EMMA_TALK: {
		GetCharacter(PRELUDE_CHARACTER_EMMA)->OnUpdate(elapsed);
	}break;

	case PRELUDE_DIAG_TOM_TALK: {
		GetCharacter(PRELUDE_CHARACTER_TOM)->OnUpdate(elapsed);
	}break;

	case PRELUDE_DIAG_RED_TALK: {
		GetCharacter(PRELUDE_CHARACTER_RED)->OnUpdate(elapsed);
	}break;


	case PRELUDE_EVIDENCE_SHOW: {

		_evidence->OnUpdate(elapsed);
	}break;

	case PRELUDE_PAUSE_MENU:
	{
		_pauseMenu.OnUpdate(elapsed);
	}break;

	case PRELUDE_SCREEN_FADE_IN: {
		int ALPHA_ACCEL = 100;
		_alpha -= (ALPHA_ACCEL*0.1f);
		if (_alpha <= 0) {
			_alpha = 0;
			OnNextProcess();
		}
	
	}break;
	
	case PRELUDE_SCREEN_FADE_OUT: {
		int ALPHA_ACCEL = 100;
		_alpha += (ALPHA_ACCEL*0.1f);
		if (_alpha >= 255) {
			_alpha = 255;
			OnNextProcess();
		}
	}break;


	case PRELUDE_CHARACTERS_FADE: {
		int count = 0;
		
		// process fade out first
		int FADE_ALPHA_ACCEL = 500;
		_mjc_alpha[0] -= (FADE_ALPHA_ACCEL * elapsed);
		_mjc_alpha[1] += (FADE_ALPHA_ACCEL * elapsed);

		if (_mjc_alpha[0] <= 0) {
			_mjc_alpha[0] = 0;
			count++;
		}

		if (_mjc_alpha[1] >= 255) {
			_mjc_alpha[1] = 255;
			count++;
		}

		printf("\n (FADE OUT) MJC[0]=%d", _mjc_alpha[0]);
		printf("\n (FADE IN) MJC[1]=%d", _mjc_alpha[1]);

		for (int i = 0; i < 3;i++) {
			if (characters_fade_OUT_flag[i]) {
				GetCharacter(i)->SetAlpha(_mjc_alpha[0]);
			}
		
			if (characters_fade_IN_flag[i]) {
				GetCharacter(i)->SetAlpha(_mjc_alpha[1]);
			}
		}

		if (count == 2) {

			characters_fade_IN_flag[0] = characters_fade_IN_flag[1] = characters_fade_IN_flag[2] = false;
			characters_fade_OUT_flag[0] = characters_fade_OUT_flag[1] = characters_fade_OUT_flag[2] = false;

			OnNextProcess();
		}

	}break;


	case PRELUDE_SHAKE_SCREEN: {
		Uint32 current = SDL_GetTicks();
		float diff = (current - _lastTime) / 1000.0f;
		if (diff > _shake_time) {
			_shake_x = 0;
			_shake_y = 0;
			_screen_texture.Destroy();

			_state = PRELUDE_DIAG_STATE_TYPING;
			ProcessNextCommand();
		}
		else {
			int targetx = random_number(-_shake_intensity, _shake_intensity);
			int targety = random_number(-_shake_intensity, _shake_intensity);
			float diffx = targetx - _shake_x;
			float diffy = targety - _shake_y;
			float dirx = (diffx >= 0) ? 1 : -1;
			float diry = (diffy >= 0) ? 1 : -1;

			_shake_x += (dirx * 800)* elapsed;
			_shake_y += (diry * 800)* elapsed;

		}


	}break;

	}// end switch

	_uimanager->OnUpdate(elapsed);

	//draw the characters
	for (int i = 0; i < _characters.size();i++) {
		_characters.at(i)->OnUpdate(elapsed);
	}
}

void PreludeDialogState::OnDraw()
{
	switch (_state)
	{
	case PRELUDE_RESOURCE_LOADING:
	case PRELUDE_SPRITE_LOADING:
	{	
		//...
	}return;
	
	case PRELUDE_DIAG_STATE_INTRO:
		DrawTextIntro();
		break;
	case PRELUDE_DIAG_STATE_TYPING: {		
		DrawCommonScene();
		DrawTalkDialog();
		
	}break;
	case PRELUDE_DIAG_IRIS: {
		int X = LOGICAL_WIDTH / 2;
		int Y = LOGICAL_HEIGHT / 2;

		SDL_Rect dest = { X - _iris_size / 2, Y - _iris_size / 2, _iris_size, _iris_size };
		SDL_RenderSetClipRect(CURRENT_RENDERER, &dest);
		DrawCommonScene();
		_iris.Draw(NULL, &dest);
		
		}break;

	case PRELUDE_DIAG_EMMA_TALK: {
		DrawTalkScreen(PRELUDE_CHARACTER_EMMA);

		}break;

	case PRELUDE_DIAG_TOM_TALK: {
		DrawTalkScreen(PRELUDE_CHARACTER_TOM);
	}break;

	case PRELUDE_PAUSE_MENU:
	{
		DrawCommonScene();
		//DrawTalkDialog();
		_pauseMenu.OnDraw();
	}break;

	case PRELUDE_APPRPREC_COMIC: {
		DrawCommonScene();
		_appricot_peaches_comic.OnDraw();
	}break;


	case PRELUDE_FADE_OUT:
	case PRELUDE_FADE_IN: 
	case PRELUDE_SCREEN_FADE_IN: 
	case PRELUDE_SCREEN_FADE_OUT: {
		DrawCommonScene();

		if (_last_state == PRELUDE_DIAG_TOM_TALK) {
			DrawTalkScreen(PRELUDE_CHARACTER_TOM);
		}
		else if (_last_state == PRELUDE_DIAG_EMMA_TALK) {
			DrawTalkScreen(PRELUDE_CHARACTER_EMMA);
		}
		else if (_last_state == PRELUDE_DIAG_RED_TALK) {
			DrawTalkScreen(PRELUDE_CHARACTER_RED);
		}

		SDL_Rect rect = { 0,0, LOGICAL_WIDTH, LOGICAL_HEIGHT };
		_blackscreen.SetBlendMode(SDL_BLENDMODE_BLEND);
		_blackscreen.SetAlpha(_alpha);
		_blackscreen.FillRect(0, 0, 0, 255,&rect);
		_blackscreen.Draw();

	}break;
	
	case PRELUDE_DIAG_RED_TALK: {
		DrawTalkScreen(PRELUDE_CHARACTER_RED);

	}break;

	//////////////////////////////////
	// TEMPORARY
	//////////////////////////////////
	case PRELUDE_END_DEMO: {
		DrawCommonScene();
		SDLGX_DrawTextCenter(LOGICAL_WIDTH / 2, LOGICAL_HEIGHT / 2, "END OF DEMO", 0, 40, { 255,255,255 });

	}break;


	case PRELUDE_SHAKE_SCREEN: {
		_screen_texture.SetRenderTarget();

		DrawCommonScene();

		//if (_talk_state == TALKSCREEN_STATE_PAUSE) {
			DrawTalkDialog();
		//}

		_screen_texture.UnSetRenderTarget();
		_screen_texture.Draw(_shake_x, _shake_y);
	
	}break;

	case PRELUDE_CACHING_SPRITES: {
		SDL_Rect rect = { 0,0, LOGICAL_WIDTH, LOGICAL_HEIGHT };
		_blackscreen.SetBlendMode(SDL_BLENDMODE_BLEND);
		_blackscreen.SetAlpha(255);
		_blackscreen.FillRect(0, 0, 0, 255, &rect);
		_blackscreen.Draw();
	}break;
	
	default: {
		DrawCommonScene();

		if (_talk_state == TALKSCREEN_STATE_PAUSE) {
			DrawTalkDialog();
		}

		if (_evidence) {
			_evidence->OnDraw();

			if (_evidence_state == 2) {
				// Draw text info here
				EvidenceInfo* evidence = GetEvidenceInfo(_evidence->GetType());
				std::string name(evidence->name);


				if (evidence->eclass == EVIDENCE_CLASS_PROFILE)
					name += " was added to Profiles";
				else
					name += " was added to Clues";

				SDLGX_DrawTextCenter(LOGICAL_WIDTH / 2, ICONBOX_HEIGHT + 80,
					name.c_str(), FONT_MANASPACE, 12, { 255, 255, 255 });
			}
		} //end of evidence condition

	}break;

	}// end switch
	 
}
void PreludeDialogState::DrawTalkScreen(int c)
{
	int back_y = (LOGICAL_HEIGHT / 2) - (_bg->_height / 2);
	_bg->Draw((LOGICAL_WIDTH / 2) - (_bg->_width / 2), back_y);

	_black_overlay.Draw();
	if (_pop_up)
	{
		_pop_up->OnDraw();

		GetCharacter(c)->SetActive(true);
		GetCharacter(c)->OnDraw();
	}
}

void PreludeDialogState::OnClose()
{}

bool PreludeDialogState::OnEvent(SDL_Event* e)
{
	bool handled = false;

	if (_pop_up) {
		return _pop_up->OnEvent(e);
	}

	if (_state == PRELUDE_DIAG_STATE_TYPING) {
		handled = HandleUI(e, _talkuimanager);
	}
	/*
	else if (_state == PRELUDE_DIAG_EMMA_TALK 
		|| _state == PRELUDE_DIAG_TOM_TALK ||
		_state == PRELUDE_APPRPREC_COMIC) {
		handled = _pop_up->OnEvent(e);
	}*/

	else if (_state == PRELUDE_PAUSE_MENU) {
		return _pauseMenu.OnEvent(e);		
	}

	if (!handled)
		handled = State::OnEvent(e);
	return handled;
}

void PreludeDialogState::LoadCharacters()
{
	//...
	_curr_character = 0;

	Tom* tom = new Tom();
	tom->Load();
	tom->SetID(PRELUDE_CHARACTER_TOM);
	tom->SetPivot(127, 184);
	//tom->SetCoordinates(0, 42); 

	Emma* emma = new Emma();
	emma->Load();
	//emma->SetCoordinates(486,44);
	emma->SetPivot(559, 188);
	emma->SetID(PRELUDE_CHARACTER_EMMA);
	emma->SetInvert(true);

	RedYoung* red = new RedYoung();
	red->Load();
	red->SetPivot(559, 182);
	red->SetInvert(true);
	red->SetAlpha(0);
	red->_visible = false;
	red->SetID(PRELUDE_CHARACTER_RED);
	_alpha = 0;

	//set all active
	SetAllCharactersActive();	
	
	_characters.push_back(emma);
	_characters.push_back(tom);
	_characters.push_back(red);

	characters_fade_IN_flag[0] = characters_fade_IN_flag[1] = characters_fade_IN_flag[2] = false;
	characters_fade_OUT_flag[0] = characters_fade_OUT_flag[1] = characters_fade_OUT_flag[2] = false;
}

void PreludeDialogState::DrawCommonScene()	
{
	//for this state, null background image means we are still at the
	// un-revealed scene
	if (_bg == NULL) 
		goto dcsexit;

	int back_y = (LOGICAL_HEIGHT / 2) - (_bg->_height / 2);
	_bg->Draw((LOGICAL_WIDTH / 2) - (_bg->_width / 2), back_y);


	if (_state != PRELUDE_DIAG_STATE_INTRO &&
		_state != PRELUDE_DIAG_IRIS)
	{
		_black_overlay.Draw(0,0);
	}

	//draw the characters
	for (int i = 0; i < _characters.size();i++) {
		_characters.at(i)->OnDraw();
	}

dcsexit:
	_uimanager->OnDraw();
}

/**/
/**/
/**/

void PreludeDialogState::LoadTextIntro()
{
	_alpha = 0;
	_prelude_text = SDLGX_GetText("Prologue",
		FONT_MANASPACE, 25, { 255,255,255 });

	_lastTime = 0;
	_prelude_text_dir = 0;			// 0: in, 1: pause
}

void PreludeDialogState::UpdateTextIntro( float elapsed)
{
	int step = 200;
	if (_prelude_text_dir == 0) {
		int nextalpha = _alpha + (step * elapsed);
		if (nextalpha > 255)
		{
			_alpha = 255;
			_prelude_text_dir = 1;
			_lastTime = SDL_GetTicks();
		}
		else {
			_alpha = nextalpha;
		}
	}
	else if (_prelude_text_dir == 1) {
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _lastTime) / 1000.0f;
		if (diff >= 2) {
			_prelude_text_dir = 2;
		}
		
	}if (_prelude_text_dir == 2) {
		int nextalpha = _alpha - (step * elapsed);
		if (nextalpha < 0)
		{
			_alpha = 0;
			GoDialog(_command_list);
		}
		else {
			_alpha = nextalpha;
		}
	}
}

void PreludeDialogState::DrawTextIntro()
{
	int cx = (LOGICAL_WIDTH / 2);
	int cy = (LOGICAL_HEIGHT / 2);
	int x = cx - (_prelude_text->GetWidth() / 2);
	int y = cy - (_prelude_text->GetHeight() / 2);
	_prelude_text->SetBlendMode(SDL_BLENDMODE_BLEND);
	_prelude_text->SetAlpha(_alpha);
	_prelude_text->Draw(x, y);
}

/**/
/**/
/**/
void PreludeDialogState::LoadCommands()
{
	FileDialogParser parser;
	parser.LoadFromFile("scripts/dialog_0.txt", _command_list);
	parser.LoadFromFile("scripts/emma_talk_A.txt", _emma_talk_A);
	parser.LoadFromFile("scripts/emma_talk_B.txt", _emma_talk_B);
	parser.LoadFromFile("scripts/emma_talk_C.txt", _emma_talk_C);
	parser.LoadFromFile("scripts/dialog_1.txt", _dialog_1_cmd);
	parser.LoadFromFile("scripts/dialog_2.txt", _dialog_2_cmd);
	parser.LoadFromFile("scripts/dialog_3.txt", _dialog_3_cmd);
	parser.LoadFromFile("scripts/tom_talk_A.txt", _tom_talk_A);
	parser.LoadFromFile("scripts/tom_talk_B.txt", _tom_talk_B);

	parser.LoadFromFile("scripts/red_talk_A.txt", _red_talk_A);
	parser.LoadFromFile("scripts/red_talk_B.txt", _red_talk_B);
	parser.LoadFromFile("scripts/red_talk_C.txt", _red_talk_C);

#if 0
	Commands* cmd = NULL;

	cmd = new DialogLineCmd();
	DialogLineCmd* tmp = (DialogLineCmd*)cmd;
	tmp->name = "???";
	tmp->line = "The world isn't all black and white, Tom.";
	tmp->display_timesec = 0.5;
	_command_list.push_back(cmd);

	cmd = new CommonCommand(COMMAND_TYPE_PAUSE, DEFAULT_PAUSE_SEC);
	_command_list.push_back(cmd);

	cmd = new DialogLineCmd();
	tmp = (DialogLineCmd*)cmd;
	tmp->name = "???";
	tmp->line = " You have to realize that there are\n people behind actions, and reasons why they do what they do";
	tmp->display_timesec = 0.5;
	_command_list.push_back(cmd);

	cmd = new Commands(COMMAND_TYPE_WAIT);
	_command_list.push_back(cmd);

	cmd = new DialogLineCmd();
	tmp = (DialogLineCmd*)cmd;
	tmp->name = "Tom";
	tmp->line = " So you're saying...";
	tmp->display_timesec = 0.5;
	_command_list.push_back(cmd);

	cmd = new CommonCommand(COMMAND_TYPE_PAUSE, DEFAULT_PAUSE_SEC);
	_command_list.push_back(cmd);

	cmd = new DialogLineCmd();
	tmp = (DialogLineCmd*)cmd;
	tmp->name = "Tom";
	tmp->line = " Not everyone is exactly good, or bad?";
	tmp->display_timesec = 0.5;
	_command_list.push_back(cmd);

	cmd = new Commands(COMMAND_TYPE_WAIT);
	_command_list.push_back(cmd);
#endif

}

void PreludeDialogState::ClearCommands(std::vector<Commands*>& command)
{
	for (int i = 0; i < command.size(); i++) {
		Commands* cmd = command.at(i);
		SAFE_DELETE(cmd);
	}

}

void PreludeDialogState::GoDialog(std::vector<Commands*>& command)
{
	RedirectCommand(command);
	
	_state = PRELUDE_DIAG_STATE_TYPING;
	ProcessNextCommand();
}

void PreludeDialogState::OnScriptEvent(int id)
{
	switch (id)
	{
		case EVENT_IRIS_TRANSITION:
		{
			_bg = new Texture();
			_bg->LoadFromResource(TUTORIAL_BG_IMG);
			_iris.LoadFromResource(IRIS_IMG);
			_state = PRELUDE_DIAG_IRIS;

			_black_overlay.LoadFromResource(BLACK_LINES_OVERLAY_IMG);
			_black_overlay.SetCoordinates(0, 0);

			SetAllCharactersActive();

		}break;

		case EVENT_MUSIC_THINKING: {
			//
			// Change music here
			//
			ProcessNextCommand();
		}break;

		case EVENT_EMMA_TALK: {

			if (!_emma_talk_screen.IsComplete()) 
			{
				_state = PRELUDE_DIAG_EMMA_TALK;
				_pop_up = &_emma_talk_screen;
				_pop_up->Launch();
				((EmmaTalkScreen*)_pop_up)->Show();
			}
			else {

				//_state = PRELUDE_EMMA_OUT_0;
				//_alpha = 255;
				GoDialog(_dialog_1_cmd);
				GetCharacter(PRELUDE_CHARACTER_RED)->SetVisible(true);
			}
		}break;

		case EVENT_SHOW_CASEFILE: {
			g_gameData.next_clue = EVIDENCE_TYPE_EMMA_TEST_RESULT;
			_state = PRELUDE_PAUSE_MENU;
			_pop_up = &_pauseMenu;

			_pauseMenu.Launch();
			_pauseMenu.Show();

			_pauseMenu.ForceShowOption(1);
			_pauseMenu.GetCaseFileMenu()->SetCustomEventHandler(this);
			SetAllCharactersActive();

			//RedirectCommand(_dialog_2_cmd);
			//ProcessNextCommand();

			//_save_state = PRELUDE_DIAG_PAUSE_0;
			//_pause_value = 2.0f;
			//OnPauseDialog(2.0f);
		}break;

		case EVENT_OUT_ALL_CHARACTERS: {
			_state = PRELUDE_FADE_ALL_CHARACTERS;
			_alpha = 255;
			SetAllCharactersActive();

		}break;

		case EVENT_TOM_TALK: {
			_state = PRELUDE_DIAG_TOM_TALK;		

			_pop_up = &_tom_talk_screen;
			_pop_up->Launch();
			((TomTalkScreen*)_pop_up)->Show();

		}break;

		case EVENT_TOM_TALK_COMPLETE: {
			GoDialog(_dialog_3_cmd);
		}break;

#if 0
		case EVENT_TOM_OUT: {
			_state = PRELUDE_TOM_FADE_OUT;
			_alpha = 255;
			GetCharacter(PRELUDE_CHARACTER_TOM)->SetAlpha(_alpha);
			SetAllCharactersActive();
		}break;
#endif

		case EVENT_APPRPREC_COMIC: {
			_state = PRELUDE_APPRPREC_COMIC;
			_pop_up = &_appricot_peaches_comic;
			_appricot_peaches_comic.Launch();
			_appricot_peaches_comic.Show();
		}break;
#if 0		
		case EVENT_FADEOUT: {
			_state = PRELUDE_FADE_OUT;
			_alpha = 0;
		}break;
#endif

		case EVENT_RED_TALK: {
			if (!_red_talk_screen.IsComplete())
			{
				_state = PRELUDE_DIAG_RED_TALK;
				_pop_up = &_red_talk_screen;
				_red_talk_screen.Launch();
				_red_talk_screen.Show();
			}
			else {
				////////////////////////////////////
				// TEMPORAY
				///////////////////////////////////
				_state = PRELUDE_END_DEMO;
				SetAllCharactersActive();
			}
		}break;

		case EVENT_RED_ADD: {
			GetCharacter(PRELUDE_CHARACTER_RED)->SetVisible(true);
			GetCharacter(PRELUDE_CHARACTER_RED)->SetAlpha(0);
			ProcessNextCommand();
		}break;

	} /* end of switch*/
}

void PreludeDialogState::OnPauseDialog(float sec)
{
	_pause_value = sec;
	//_pause = true;
	_lastTime = SDL_GetTicks();

	_state = PRELUDE_GENERIC_PAUSE;
}

void PreludeDialogState::PauseWithTarget(float value,int next_proc)
{
	OnPauseDialog(value);
	_next_process = next_proc;
}

void PreludeDialogState::OnUnPauseDialog()
{
	//...
}

void PreludeDialogState::SetCharacterParam(int id, int sprite_id, int fps, bool actvate)
{
	if (id == -1) return;

	//draw the characters
	for (int i = 0; i < _characters.size();i++) {
		Character* c = _characters.at(i);
		if (c->GetID() == id) {
			_characters.at(i)->SetActive(true);

			if (sprite_id != -1) {
				_characters.at(i)->SetIndex(sprite_id);
				if( fps >= 0)
					_characters.at(i)->SetFPS(fps);
			}
		}
		else {
			_characters.at(i)->SetActive(false);
		}
		
	}

	if (actvate) {
		_active_character = id;
	}
}

void PreludeDialogState::SetCharacterIdleIndex(int id, int sprite_id, int fps)
{
	Character* c = GetCharacter(id);
	if (c) {
		c->SetIdleIndex(sprite_id);
	}
}

void PreludeDialogState::SetEvidence(int id)
{
	_state = PRELUDE_EVIDENCE_SHOW;
	SAFE_DELETE(_evidence);

	_evidence = new IconBox();
	_evidence->SetEventHandler(this);
	_evidence->Load((EvidenceType)id);
	_evidence->ZoomIn(LOGICAL_WIDTH / 2, LOGICAL_HEIGHT / 2);
	_evidence_state = 0; // 1: pause after zoom, 2: pause after move
}

void PreludeDialogState::PopupClose(int id)
{
	_pop_up = NULL;
	switch (id)
	{
		case EMMATALK_SCREEN:
		{
			int selected = _emma_talk_screen.GetSelectedIdx();
			if (selected == 0)
				GoDialog(_emma_talk_A);
			else if (selected == 1)
				GoDialog(_emma_talk_B);
			else
				GoDialog(_emma_talk_C);
		}break;

		case TOMTALK_SCREEN: {
			//...
			int selected = _tom_talk_screen.GetSelectedIdx();
			if (selected == 0) {				
				GoDialog(_tom_talk_A);
			}
			else {
				GoDialog(_tom_talk_B);
			}

		}break;

#if 0
		case PAUSE_MENU:
		{
			_state = _save_state;
			_pop_up = NULL;
		}break;
#endif

		case APPRICOT_PEACHES_COMIC: {
			/*_state = PRELUDE_DIAG_PAUSE_0;
			_pause_value = 3.0f;
			_lastTime = SDL_GetTicks();
			*/
			OnPauseDialog(3.0f);
			SetAllCharactersActive();
			_pop_up = NULL;
		}break;

		case REDTALK_SCREEN: {
			int selected = _red_talk_screen.GetSelectedIdx();
			if (selected == 0)
				GoDialog(_red_talk_A);
			else if (selected == 1)
				GoDialog(_red_talk_B);
			else
				GoDialog(_red_talk_C);
		
		}break;
	}
}

void PreludeDialogState::InitializePopups()
{
	_pauseMenu.SetHandler(this);
	_emma_talk_screen.SetHandler(this);
	_tom_talk_screen.SetHandler(this);
	_appricot_peaches_comic.SetHandler(this);
	_red_talk_screen.SetHandler(this);
}

void PreludeDialogState::OnCustomEvent(void* obj, int type)
{
	switch (type) {
		case ICONBOX_EVT_ZOOM_DONE: {
			_evidence_state = 1; 
			PauseWithTarget(1, 1);
		}break;
		case  ICONBOX_EVT_MOVE_DONE: 
		{
			_evidence_state = 2;
			PauseWithTarget(2, 1);

		}break;

		case ON_CORRECT_CLUE_EVNT: {
		//	_state = PRELUDE_PAUSE_MENU;
			_pauseMenu.ForceClearPopup();
			_pauseMenu.Hide();

			GoDialog(_dialog_2_cmd);

			//_save_state = PRELUDE_DIAG_STATE_TYPING;
			// Temporary
		}break;

		case ON_CACHE_LOADED: {
			_state = PRELUDE_DIAG_STATE_INTRO;
			LoadCharacters();
		}break;
	}
}


void PreludeDialogState::OnButtonClickDefer(sdlgx::gui::Button* b)
{
	switch (b->GetID()) {
		case PIN_BUTTON:
		{
			_save_state = _state;
			_state = PRELUDE_PAUSE_MENU;
			_pauseMenu.Launch();
			_pauseMenu.Show();
		}	break;
	}
}


Character* PreludeDialogState::GetCharacter(int id)
{
	for (int i = 0; i < _characters.size();i++) {
		if (_characters.at(i)->GetID() == id)
			return _characters.at(i);
	}
	return NULL;
}

void PreludeDialogState::OnCompleteScript() 
{
	_state = PRELUDE_DIAG_STATE_NONE;
}

void PreludeDialogState::SetAllCharactersActive() {
	for (int i = 0; i < _characters.size();i++) {
		_characters.at(i)->SetActive(true);
	}
}

void PreludeDialogState::OnWaitCommand()
{
	
}

void PreludeDialogState::OnNextProcess()
{
	switch (_next_process) {
	case 0:  // save state is set
		_state = _save_state;
		break;
	case 1: // Evidence processing
	{
		if (_evidence_state == 1) {
			_evidence->MoveTo(_evidence->_x, 10);
			_state = PRELUDE_EVIDENCE_SHOW;
		}
		else if (_evidence_state == 2) {

			EvidenceType type = _evidence->GetType();
			EvidenceInfo* info = GetEvidenceInfo(type);
			if (info->eclass == EVIDENCE_CLASS_PROFILE) {
				g_gameData.profiles.push_back(type);
			}
			else {
				g_gameData.clues.push_back(type);
			}

			_state = PRELUDE_DIAG_STATE_TYPING;
			ProcessNextCommand();

			SAFE_DELETE(_evidence);
		}
	
	}break;
	
	case 2: {  

		if(_pop_up)
			_pop_up = NULL;
	}break;
	
	case 3: { // Pause after cache load
		PauseWithTarget(0,-1);	
	}break;
	
	default:
		_state = PRELUDE_DIAG_STATE_TYPING;
		ProcessNextCommand();
	}
}


void PreludeDialogState::IdleCharacter()
{
	if (_active_character == -1) return;
	GetCharacter(_active_character)->GoIdle();
}

void PreludeDialogState::GoFadeCharacter(int next_step)
{
	_next_process = next_step;
	_state = PRELUDE_CHARACTERS_FADE;
	_mjc_alpha[0] = 255;
	_mjc_alpha[1] = 0;
}

void PreludeDialogState::FadeCharacter(int id, int dir)
{
	if (id >= 3 || id < 0) return;
	if (dir == 0) {			// fade out
		characters_fade_OUT_flag[id] = true;
		characters_fade_IN_flag[id] = false;
	}
	else {					// fade in
		characters_fade_IN_flag[id] = true;
		characters_fade_OUT_flag[id] = false;
	}
}

void PreludeDialogState::OnShakeScreen(int intensity, float time)
{
	_screen_texture.Destroy();
	_screen_texture.Create();
	_state = PRELUDE_SHAKE_SCREEN;
	_shake_intensity = intensity;
	_shake_x = 0;
	_shake_y = 0;
	_lastTime = SDL_GetTicks();
	SetAllCharactersActive();
	_shake_time = time;
}

bool PreludeDialogState::DeferProcessCommand(Commands* cmd)
{
	switch (cmd->type) {
		case COMMAND_TYPE_FADE: {
			CommandFade* scmd = (CommandFade*)cmd;
			for (int i = 0;i < scmd->sprite_id.size();i++) {
				FadeCharacter(scmd->sprite_id.at(i), scmd->dir);
			}
			GoFadeCharacter();
		}return true;	//async
		case COMMAD_TYPE_SETCHAR_COORD: {
			SetCharacterCoordCmd* scmd = (SetCharacterCoordCmd*)cmd;
			//GetCharacter(scmd->id)->SetCoordinates(scmd->x, scmd->y);
			GetCharacter(scmd->id)->SetPivot(scmd->x, scmd->y);
		}break;
		case COMMAND_TYPE_SETCHAR_INVERT: {
			//id/value
			CommonCommandInt2* scmd = (CommonCommandInt2*)cmd;
			GetCharacter(scmd->val1)->SetInvert((bool)scmd->val2);
		}break;

		case COMMAND_TYPE_SETCHAR_ACTIVE: {
			CommonCommandInt2* scmd = (CommonCommandInt2*)cmd;
			GetCharacter(scmd->val1)->SetActive((bool)scmd->val2);
		}break;
	}

	return false;
}

int LoadSpriteBankThread(void* ptr)
{
	for (int i = 0; i < g_gameData.sprite_bank.size(); i++) {
		SpriteInfo* info = g_gameData.sprite_bank.at(i);
		info->sprite = new SpriteSheet();
		info->sprite->LoadFromFile(info->path.c_str());
		info->sprite->Set(info->frame_count, info->fps, info->loop);
	}

	((PreludeDialogState*)ptr)->OnCustomEvent(NULL, ON_CACHE_LOADED);
	return 0;
}

void PreludeDialogState::LoadSpriteScript(const char* filename)
{
	std::string line;
	ifstream myfile(filename);

	g_gameData.CleanupSpriteBank();

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//path(space)character_id(space)sprite_index(space)fps(space)frame_count(space)loop
			std::vector<std::string> params;
			Utility_StringSpit(line, ' ', params);
			struct SpriteInfo* sprite = new struct SpriteInfo();
			sprite->path = params.at(0);
			
			const char* value = params.at(1).c_str();
			sprite->character_id = atoi(value);

			value = params.at(2).c_str();
			sprite->sprite_index = atoi(value);

			value = params.at(3).c_str();
			sprite->fps = atoi(value);

			value = params.at(4).c_str();
			sprite->frame_count = atoi(value);

			value = params.at(5).c_str();
			sprite->loop= (bool)(atoi(value));

			g_gameData.SaveSprite(sprite);
		}
		myfile.close();
	
		_state = PRELUDE_SPRITE_LOADING;
		SDL_CreateThread(LoadSpriteBankThread, "LoadSpriteBank", (void *)this);

	}
	else {
		fprintf(stderr, "PreludeDialogState::LoadSpriteScript: Unable to load script file: %s\n", filename);
	}
}

void PreludeDialogState::LoadResource()
{
	_state = PRELUDE_RESOURCE_LOADING;

	resource_total = sizeof(pre_img_resource) / sizeof(ResourceDef);
	resource_loaded = 0;
	ResourceManager::GetInstance()->LoadAsync(pre_img_resource, resource_total,
		this);
}

void PreludeDialogState::OnResourceLoad(int index)
{
	resource_loaded++;
	if (resource_loaded >= resource_total) {
		LoadSpriteScript("scripts/sprites_pre.txt");
	}
}
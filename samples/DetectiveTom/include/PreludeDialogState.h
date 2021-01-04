#pragma once

#include "state.h"
#include "texture.h"
#include "Commands.h"
#include "TalkScreenBase.h"
#include "Character.h"
#include "EmmaTalkScreen.h"
#include "TomTalkScreen.h"
#include "RedTalkScreen.h"
#include "IconBox.h"
#include "PauseMenu.h"
#include "AppricotPeachesComic.h"
#include <vector>

typedef enum PrldDiagState
{
	PRELUDE_DIAG_STATE_NONE = 0,
	PRELUDE_DIAG_STATE_INTRO,
	PRELUDE_DIAG_STATE_TYPING,
	PRELUDE_DIAG_IRIS,
	
	
	//PRELUDE_DIAG_PAUSE_0,		// can be useto pause and resume dialog after --> to be deprecated
	//PRELUDE_DIAG_PAUSE,			// General pause screen  -->to be deprecated
	PRELUDE_GENERIC_PAUSE,

	PRELUDE_DIAG_EMMA_TALK,
	PRELUDE_DIAG_TOM_TALK,
	PRELUDE_DIAG_RED_TALK,
	PRELUDE_EVIDENCE_SHOW,
	PRELUDE_EMMA_OUT_0,
	PRELUDE_EMMA_IN_0,
	PRELUDE_PAUSE_MENU,

	////////////////////////////////////////////////////////////
	// to be deprecated
	PRELUDE_REDYOUNG_IN,	
	PRELUDE_FADE_ALL_CHARACTERS,
	PRELUDE_FADE_IN_TOM_EMMA,
	PRELUDE_TOM_FADE_OUT,
	PRELUDE_TOM_FADE_IN,
	////////////////////////////////////////////////////////////
	
	PRELUDE_CHARACTERS_FADE,		// Generic Fade
	
	PRELUDE_SCREEN_FADE_IN,
	PRELUDE_SCREEN_FADE_OUT,

	PRELUDE_APPRPREC_COMIC,
	PRELUDE_FADE_OUT,
	PRELUDE_FADE_IN,
	
	PRELUDE_CACHING_SPRITES,

	PRELUDE_SHAKE_SCREEN,

	//TEMPORARY
	PRELUDE_END_DEMO

}PRELUDE_DIAG_STATE_TYPE;

class PreludeDialogState 
	: public sdlgx::core::State,
	public TalkScreenBase,
	public IPopupHandler,
	public ICustomEvent
{
public:
	PreludeDialogState();
	~PreludeDialogState();

	//----------------------------------------
	virtual void OnLoad();
	virtual void OnInitialize();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
	virtual void OnClose();
	virtual bool OnEvent(SDL_Event* e);
	//----------------------------------------


private:
	PRELUDE_DIAG_STATE_TYPE _state;
	PRELUDE_DIAG_STATE_TYPE _save_state;
	PRELUDE_DIAG_STATE_TYPE _last_state;

	sdlgx::scene::Texture* _bg;
	sdlgx::scene::Texture _black_overlay;
	Uint32 _lastTime;
	sdlgx::core::State* _pop_up;
	GlowButton _pinButton;
	PauseMenu _pauseMenu;

	//----------------------------------------
	// Common state 
	std::vector<Character*> _characters;
	int _curr_character;
	void LoadCharacters();	
	void DrawCommonScene();
	Character* GetCharacter(int id);
	//----------------------------------------

	//----------------------------------------
	// title state declarations
	int _alpha;
	sdlgx::scene::Texture* _prelude_text;
	unsigned short _prelude_text_dir;
	
	void LoadTextIntro();
	void UpdateTextIntro(float elapsed);
	void DrawTextIntro();
	//----------------------------------------

	//----------------------------------------
	// Typing state declarations
	void LoadCommands();
	void ClearCommands(std::vector<Commands*>& command);
	void GoDialog(std::vector<Commands*>& command);
	std::vector<Commands*> _command_list;
	std::vector<Commands*> _dialog_1_cmd;
	std::vector<Commands*> _dialog_2_cmd;
	std::vector<Commands*> _dialog_3_cmd;
	//----------------------------------------

	//----------------------------------------
	// Iris state definition
	sdlgx::scene::Texture _iris;
	int _iris_size;
	//----------------------------------------

	//----------------------------------------
	// Inherited from TalkScreenBase
	virtual void OnScriptEvent(int id);
	virtual void OnPauseDialog(float time);
	virtual void OnUnPauseDialog();
	virtual void SetCharacterParam(int id, int sprite_id, int fps, bool activate = false);
	virtual void SetCharacterIdleIndex(int id, int sprite_id, int fps);

	virtual void SetEvidence(int id);
	virtual void OnButtonClickDefer(sdlgx::gui::Button* b);
	virtual void OnCompleteScript();
	virtual void OnWaitCommand();
	virtual void IdleCharacter();
	virtual void OnShakeScreen(int intensity, float time);
	virtual bool DeferProcessCommand(Commands* cmd);
	//----------------------------------------

	//inherited IPopupHandler 
	virtual void PopupClose(int id);

	//----------------------------------------
	// Emma Talk screen
	EmmaTalkScreen _emma_talk_screen;
	std::vector<Commands*> _emma_talk_A;
	std::vector<Commands*> _emma_talk_B;
	std::vector<Commands*> _emma_talk_C;
	//----------------------------------------

	//----------------------------------------
	// Tom Talk screen
	TomTalkScreen _tom_talk_screen;
	std::vector<Commands*> _tom_talk_A;
	std::vector<Commands*> _tom_talk_B;
	//----------------------------------------

	//----------------------------------------
	// Red Talk screen
	RedTalkScreen _red_talk_screen;
	std::vector<Commands*> _red_talk_A;
	std::vector<Commands*> _red_talk_B;
	std::vector<Commands*> _red_talk_C;
	//----------------------------------------
	
	void InitializePopups();

	//evidence effect
	IconBox* _evidence;
	int _evidence_state;

	//bool _pause;
	float _pause_value;

	// inheirted from ICustomEvent
	virtual void OnCustomEvent(void* obj, int type);
	void SetAllCharactersActive();

	AppricotPeachesComic _appricot_peaches_comic;
	sdlgx::scene::Texture _blackscreen;

	int _active_character;
	int _next_process;

	void PauseWithTarget(float value, int next_proc=-1);
	void OnNextProcess();

	//generic characters fade_in/out
	// can support simultaneous fade
	bool characters_fade_OUT_flag[3];
	bool characters_fade_IN_flag[3];
	int _mjc_alpha[2];					//0: fade out, 1:fade in

	void GoFadeCharacter(int next_step=-1);
	void FadeCharacter(int id, int dir);

	void CacheCommand(std::vector<Commands*>& command);

	// for shake implementation
	sdlgx::scene::Texture _screen_texture;
	int _shake_intensity;
	int _shake_x;
	int _shake_y;
	float _shake_time;

	void DrawTalkScreen(int c);
};
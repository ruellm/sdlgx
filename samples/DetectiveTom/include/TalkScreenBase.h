#pragma once
#include "GlowButton.h"
#include "Commands.h"
#include "texture.h"
#include "uimanager.h"
#include <vector>
#include <string>

#define DEFAULT_PAUSE_SEC 2

typedef enum TalkScreenState
{
	TALKSCREEN_STATE_NONE = 0,
	TALKSCREEN_STATE_PROC_CMD,
	TALKSCREEN_STATE_LETTER_DRAW,
	TALKSCREEN_STATE_LETTER_WAIT,
	TALKSCREEN_STATE_LETTER_TYPING,
	TALKSCREEN_STATE_PAUSE,
	TALKSCREEN_STATE_WAIT,
	TALKSCREEN_STATE_COMPLETE
}TALK_SCREEN_STATE;


class TalkScreenBase 
	: public sdlgx::gui::IButtonEventHandler
{
public:
	TalkScreenBase();
	~TalkScreenBase();

	void RedirectCommand(std::vector<Commands*>& command);
	void Load();
	TalkScreenState UpdateTalkDialog(float elapsed);
	void DrawTalkDialog();
	void StartDialog();
	sdlgx::gui::UIManager* GetUIManager() const;

protected:
	TalkScreenState _talk_state;
	std::vector<Commands*>* _commands_ptr;
	
	void InitDialog();
	sdlgx::gui::UIManager* _talkuimanager;

	virtual void OnScriptEvent(int id);
	virtual void OnPauseDialog(float time);
	virtual void OnUnPauseDialog();
	virtual void SetCharacterParam(int id, int sprite_id, int fps, bool activate = false);
	virtual void SetCharacterIdleIndex(int id, int sprite_id, int fps);
	virtual void SetEvidence(int id);
	virtual void OnCompleteScript();
	virtual void OnShakeScreen(int intensity, float time);

	virtual void OnWaitCommand();
	virtual void IdleCharacter();
	virtual bool DeferProcessCommand(Commands* cmd);
	void ProcessNextCommand();

private:
	sdlgx::scene::Texture _talkbox;
	int _command_idx;
	int _letter_idx;

	float _time_per_char;
	Uint32 _last_time;

	std::string _name;
	std::string _display;
	Commands* _current_cmd;
	GlowButton _fwdbtn;	

	void Clear();

	//inherited IButtonEventHandler 
	virtual void OnButtonClick(sdlgx::gui::Button* b);
	virtual void OnButtonClickDefer(sdlgx::gui::Button* b);
};
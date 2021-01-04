#include "TalkScreenBase.h"
#include "definitions.h"
#include "font.h"
#include "Utility.h"
#include "engine.h"

using namespace sdlgx::core;
using namespace sdlgx::scene;
using namespace sdlgx::gui;

TalkScreenBase::TalkScreenBase() 
	: _talkuimanager(NULL)
{
	InitDialog();
}

TalkScreenBase::~TalkScreenBase()
{
	SAFE_DELETE(_talkuimanager);
}

void TalkScreenBase::Load()
{
	_talkuimanager = new UIManager();
	_talkbox.LoadFromResource(TEXT_BOX_IMG);
	_talkbox.SetCoordinates(
		(LOGICAL_WIDTH/2)-(_talkbox.GetWidth()/2), 
		LOGICAL_HEIGHT- _talkbox.GetHeight()-10
	);

	_fwdbtn.Load(FORWARD_BUTTON_IMG);
	_fwdbtn.SetHandler(this);
	_fwdbtn.SetID(FWD_BUTTON);

	// Deactivate button at start
	_fwdbtn.SetVisible(false);
	_fwdbtn.SetCoordinates(610, 328);
	_talkuimanager->Add(&_fwdbtn);
}

void TalkScreenBase::InitDialog()
{
	_command_idx = -1;
	_letter_idx = -1;
	_talk_state = TALKSCREEN_STATE_NONE;
	_commands_ptr = NULL;
}

TalkScreenState TalkScreenBase::UpdateTalkDialog(float elapsed)
{
	_talkuimanager->OnUpdate(elapsed);
	
	switch (_talk_state) {
	case TALKSCREEN_STATE_LETTER_TYPING: {
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _last_time) / 1000.0f;
		
		if (diff >= _time_per_char) {
			if (_letter_idx + 1 < _display.size()) {
				_letter_idx++;
				_last_time = SDL_GetTicks();
			}
			else {
				ProcessNextCommand();
			}
		}

		}break;

/*	case TALKSCREEN_STATE_PAUSE: {
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _last_time) / 1000.0f;
	
		if (diff >= ((CommonCommand*)_current_cmd)->value) {
			OnUnPauseDialog();
			ProcessNextCommand();
		}
		}break;*/
	}

	return _talk_state;
}

void TalkScreenBase::DrawTalkDialog()
{
	int text_size = 12;

	_talkbox.Draw();
	SDLGX_DrawTextCenter(64, 271, _name.c_str(), FONT_MANASPACE, text_size, { 255,255,255 });

	int startX = 23;
	int startY = 294;
	
	int total_size = 0;
	int current_split_pos = 0;
	int current_split_idx_pos = 0;
	int pos = 0;
	int base = 0;
	int end = 0;
	std::vector<SDL_Point> rangeinfo;

	std::vector<std::string> elems;
	Utility_StringSpit(_display, '\n', elems);

	if (elems.size() == 0) return;

	for (int i = 0; i < elems.size(); i++) {
		std::string item = elems.at(i);
		end = base + item.size();

		if (_letter_idx >= base && _letter_idx <= end) {
			current_split_pos = pos;
		}

		SDL_Point point;
		point.x = base;
		point.y = end;
		rangeinfo.push_back(point);
		base = end + 1;

		pos++;;
	}

	int i = 0;
	while (i <= current_split_pos - 1) {
		std::string text = elems.at(i);
		SDLGX_DrawText(startX, startY, text.c_str(), FONT_MANASPACE, text_size, { 255,255,255 });
		startY += (text_size + 5);
		i++;
	}

	std::string text = elems.at(current_split_pos);
	SDL_Point point = rangeinfo.at(current_split_pos);
	int v1 = (point.y-1) - _letter_idx;
	int numchar = text.size() - v1;
	text = text.substr(0, numchar);
	SDLGX_DrawText(startX, startY, text.c_str(), FONT_MANASPACE, text_size, { 255,255,255 });

	_talkuimanager->OnDraw();
}

void TalkScreenBase::StartDialog()
{
	Clear();
	_command_idx = 0;
	ProcessNextCommand();
}

void TalkScreenBase::RedirectCommand(std::vector<Commands*>& command)
{
	_commands_ptr = &command;
	Clear();
	_command_idx = 0;
}

void TalkScreenBase::ProcessNextCommand()
{
	_talk_state = TALKSCREEN_STATE_PROC_CMD;
	while (_command_idx < _commands_ptr->size())
	{
		_current_cmd = _commands_ptr->at(_command_idx++);
		switch (_current_cmd->type) {
			case COMMAND_TYPE_DIALOGLINE:
			{
				DialogLineCmd* temp = (DialogLineCmd*)_current_cmd;

				_time_per_char = temp->display_timesec / (float)temp->line.size();
				_name = temp->name;
				_display += temp->line;
				_letter_idx++;
				_talk_state = TALKSCREEN_STATE_LETTER_TYPING;

				_last_time = SDL_GetTicks();
				
				_fwdbtn.SetVisible(false);
				SetCharacterParam(temp->id, temp->sprite_id, temp->sprite_fps, true);

			}return; // this command is synchronous

			case COMMAND_TYPE_PAUSE:
			{	_talk_state = TALKSCREEN_STATE_NONE;
				//_last_time = SDL_GetTicks();
				OnPauseDialog(((CommonCommand*)_current_cmd)->value);
			}return; // this command is synchronous
		
			case COMMAND_TYPE_PAUSE_TALK: {
				_talk_state = TALKSCREEN_STATE_PAUSE;
				OnPauseDialog(((CommonCommand*)_current_cmd)->value);				
				IdleCharacter();
			}return;

			case COMMAND_TYPE_WAIT:
				_fwdbtn.SetVisible(true);
				IdleCharacter();

				return;

			case COMMAND_TYPE_EVENT:
			{
				OnScriptEvent(((CommonCommand*)_current_cmd)->value);
			}return; // this command is synchronous;

			case COMMAND_TYPE_EVIDENCE:					
			{
				SetEvidence(((CommonCommand*)_current_cmd)->value);
			}return;

			case COMMAND_TYPE_ENDSCRIPT:
			{
				_talk_state = TALKSCREEN_STATE_COMPLETE;
				OnCompleteScript();
			}return;

			case COMMAND_TYPE_SETCHAR_SPRITE: {
				CharacterSpriteCmd* temp = (CharacterSpriteCmd*)_current_cmd;
				SetCharacterParam(temp->character_id, temp->sprite_id, temp->fps, false);

			}break; // not synchronous

			case COMMAND_TYPE_SETCHAR_IDLE_IDX: {
				CharacterSpriteCmd* temp = (CharacterSpriteCmd*)_current_cmd;
				SetCharacterIdleIndex(temp->character_id, temp->sprite_id, temp->fps);
			}break; //not synchronous

			case COMMAND_TYPE_SHAKE: {
				CommandShake* cmd_shake = (CommandShake*)_current_cmd;
				OnShakeScreen(cmd_shake->intensity,cmd_shake->time );
			}return;

			default:
				//TODO: transfer some of the commands above to "defer" processing
				bool ret = DeferProcessCommand(_current_cmd);
				if (ret)
					return;
				break;
		}
	}
}

void TalkScreenBase::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID()) {
	case FWD_BUTTON:	// Fwd button
		Clear();
		ProcessNextCommand();
		break;
	default:
		OnButtonClickDefer(b);
	}
}

void TalkScreenBase::OnButtonClickDefer(sdlgx::gui::Button* b)
{
	//defer operation to child class
}

void TalkScreenBase::Clear()
{
	_display.clear();
	_last_time = 0;
	_letter_idx = -1;
	_name.clear();
}

sdlgx::gui::UIManager* 
TalkScreenBase::GetUIManager() const
{
	return _talkuimanager;
}

void TalkScreenBase::OnScriptEvent(int id)
{}

void TalkScreenBase::OnPauseDialog(float value)
{}

void TalkScreenBase::OnUnPauseDialog()
{}

void TalkScreenBase::SetCharacterParam(int id, int sprite_id, int fps, bool activate)
{}

void TalkScreenBase::SetCharacterIdleIndex(int id, int sprite_id, int fps)
{}

void TalkScreenBase::SetEvidence(int id)
{}

void TalkScreenBase::OnCompleteScript()
{}

void TalkScreenBase::OnWaitCommand()
{}

void TalkScreenBase::IdleCharacter()
{}

void TalkScreenBase::OnShakeScreen(int intensity, float time)
{}

bool TalkScreenBase::DeferProcessCommand(Commands* cmd)
{
	return false;
}
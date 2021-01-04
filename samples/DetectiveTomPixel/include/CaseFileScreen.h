#pragma once
#include <vector>
#include "SceneFader.h"
#include "texture.h"
#include "state.h"
#include "zoom_button.h"
#include "uibase.h"
#include "uimanager.h"
#include "BoxScroll.h"
#include "TalkScreenBase.h"
#include "Commands.h"
#include "Evidence.h"
#include "CustomEvent.h"

class CaseFileBoxItem 
	: public sdlgx::gui::ZoomButton
{
public:
	CaseFileBoxItem();
	~CaseFileBoxItem();
	virtual void OnDraw();
	virtual void OnUpdate(float elapsed);
	virtual void MoveTo(int x);
	void SetSelected(bool value);
	void SetType(EvidenceType type);
	EvidenceType GetType();

private:
	enum CFBoxItemStatus {
		CFITEM_MOVING = 0,
		CFITEM_FLIP,
		CFITEM_IDLE
	};

	enum CFBoxItemStatus _status;
	int _targetX;
	int _dir;
	bool _selected;
	EvidenceType _type;
	void OnMoveUpdate(float elapsed);
};

enum CaseFileMode
{
	CASE_FILE_MODE_CLUES = 0,
	CASE_FILE_MODE_PROFILE
};

typedef enum CaseFileState
{
	CASEFILE_STATE_NORMAL = 0,
	CASEFILE_STATE_PAUSE,
	CASEFILE_STATE_TYPING
}CASEFILE_STATE;

class CaseFileScreen :
	public SceneFader,
	sdlgx::gui::IButtonEventHandler
{
public:
	CaseFileScreen();
	~CaseFileScreen();

	virtual void OnInitialize();
	virtual void OnLoad();
	virtual void OnUpdate(float elapsed);
	bool OnEvent(SDL_Event* e);
	void SetCustomEventHandler(ICustomEvent* handler);

private:
	sdlgx::scene::Texture _bg;
	sdlgx::scene::Texture _fg;
	sdlgx::gui::ZoomButton  _backBtn;

	CASEFILE_STATE _state;
	bool _first_load;
	Uint32 _lastTime;
	sdlgx::scene::Texture _black_overlay;
	std::vector<Commands*> _command_list;
	TalkScreenBase _talk_screen;
	
	//for case file item manipulation
	sdlgx::gui::ZoomButton _arrow_right, _arrow_left;
	sdlgx::gui::ZoomButton _clues_btn/*, _profiles_btn*/;
	sdlgx::gui::ZoomButton _show_btn;
	int _selected_index;

	std::vector<CaseFileBoxItem*> _list;
	sdlgx::gui::UIManager _listmanager;
	enum CaseFileMode _mode;

	// for scrollbox
	CaseFileScrollBox _scroll_box;
	sdlgx::scene::Texture* _testContent;
	ICustomEvent* _handler;

	void SetErrorString(std::string error);

	virtual void OnInternalDraw();
	virtual void OnButtonClick(sdlgx::gui::Button* b);
	virtual void OnButtonHold(sdlgx::gui::Button* b);

	void Move(int direction);
};

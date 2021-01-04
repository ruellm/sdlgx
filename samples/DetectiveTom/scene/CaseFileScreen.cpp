#include "CaseFileScreen.h"
#include "definitions.h"
#include "UIManager.h"
#include "engine.h"
#include "FileDialogParser.h"
#include "GameData.h"
#include "font.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace sdlgx::gui;
using namespace sdlgx::core;
using namespace sdlgx::scene;

#define ICONBOX_ITEM_ID_BASE 500

CaseFileBoxItem::CaseFileBoxItem() :
	_status(CFITEM_IDLE), _selected(false)
{
	SetID(CASE_FILE_SCREEN);
}

CaseFileBoxItem::~CaseFileBoxItem()
{}

void CaseFileBoxItem::OnUpdate(float elapsed)
{
	if (_status == CFITEM_MOVING) {
		OnMoveUpdate(elapsed);
		return;
	}

	GlowButton::OnUpdate(elapsed);
}

void CaseFileBoxItem::OnDraw()
{
	if (_selected) {
		SDL_Rect rect = { _x - 2, _y - 2, _width + 4, _height + 4 };
		SDL_SetRenderDrawColor(CURRENT_RENDERER, 0, 255, 0, 255);
		SDL_RenderFillRect(CURRENT_RENDERER, &rect);
	}

	GlowButton::OnDraw();
}

void CaseFileBoxItem::MoveTo(int x)
{
	int diff = x - _x;
	_dir = diff / abs(diff);
	_status = CFITEM_MOVING;
	_targetX = x;
}

void CaseFileBoxItem::OnMoveUpdate(float elapsed)
{
	float SPEED = 5;
	int diff = _targetX - _x;
	_x += (diff * SPEED * elapsed);
	if ((_dir > 0 && _x >= _targetX-2) ||
		(_dir < 0 && _x <= _targetX+2)) {
		_x = _targetX;
		_status = CFITEM_IDLE;
	}
}

void CaseFileBoxItem::SetSelected(bool value)
{
	_selected = value;
}

void CaseFileBoxItem::SetType(EvidenceType type)
{
	_type = type;
}

EvidenceType CaseFileBoxItem::GetType()
{
	return _type;
}


/**/
/**/
/**/
CaseFileScreen::CaseFileScreen() 
	: SceneFader(), _mode(CASE_FILE_MODE_CLUES),
	_testContent(NULL), _first_load(true),
	_handler(NULL)
{
	SetID(CASE_FILE_SCREEN);
}

CaseFileScreen::~CaseFileScreen()
{
	SAFE_DELETE(_uimanager);
	SAFE_DELETE(_testContent);

	for (int i = 0; i < _list.size(); i++) {
		CaseFileBoxItem* item = _list.at(i);
		SAFE_DELETE(item);
	}

	for (int i = 0; i < _command_list.size(); i++) {
		Commands* cmd = _command_list.at(i);
		SAFE_DELETE(cmd);
	}
}

void CaseFileScreen::OnInitialize()
{
	/* initialize random seed: */
	srand(time(NULL));

	SceneFader::Load(0, 0);
	_uimanager = new UIManager();
	_bg.LoadFromResource(CASE_FILE_BASE_IMG);
	_fg.LoadFromResource(CASE_FILE_FG_IMG);

	_backBtn.Load(BACK_BUTTON_IMG, BACK_BUTTON_IMG);
	_backBtn.SetGlowImage(BACK_BUTTON_GLOW_IMG);
	_backBtn.SetID(0);
	_backBtn.SetHandler(this);
	_backBtn.SetCoordinates(1402, 980);
	_uimanager->Add(&_backBtn);

	_arrow_right.Load(CHOICE_SCROLL_RIGHT_IMG, CHOICE_SCROLL_RIGHT_IMG);
	_arrow_right.SetGlowImage(CHOICE_GLOW_IMG);
	_arrow_right.SetID(1);
	_arrow_right.SetHandler(this);
	_arrow_right.SetCoordinates(sdlgx::core::LOGICAL_WIDTH - 100, 710);
	_arrow_right.SetHoldThreshold(0.1f);
	_uimanager->Add(&_arrow_right);

	_arrow_left.Load(CHOICE_SCROLL_LEFT_IMG, CHOICE_SCROLL_LEFT_IMG);
	_arrow_left.SetGlowImage(CHOICE_GLOW_IMG);
	_arrow_left.SetID(2);
	_arrow_left.SetHandler(this);
	_arrow_left.SetCoordinates(0, 710);
	_arrow_left.SetHoldThreshold(0.1f);
	_uimanager->Add(&_arrow_left);

	int cx = 1003;
	int y = 500;

	_clues_btn.Load(CLUES_BUTTON_IMG, CLUES_BUTTON_IMG);
	_clues_btn.SetGlowImage(CLUES_BUTTON_GLOW_IMG);
	_clues_btn.SetID(3);
	_clues_btn.SetHandler(this);
	_clues_btn.SetCoordinates(cx - (203/2), y);
	_clues_btn.SetHoldThreshold(0.1f);
	_clues_btn._visible = true;
	_uimanager->Add(&_clues_btn);

	_profiles_btn.Load(PROFILES_BUTTON_IMG, PROFILES_BUTTON_IMG);
	_profiles_btn.SetGlowImage(PROFILES_BUTTON_GLOW_IMG);
	_profiles_btn.SetID(4);
	_profiles_btn.SetHandler(this);
	_profiles_btn.SetCoordinates(cx - (280/2), y);
	_profiles_btn.SetHoldThreshold(0.1f);
	_profiles_btn._visible = false;
	_uimanager->Add(&_profiles_btn);


	_show_btn.Load(SHOW_BUTTON_IMG, SHOW_BUTTON_IMG);
	_show_btn.SetGlowImage(SHOW_BUTTON_GLOW_IMG);
	_show_btn.SetID(5);
	_show_btn.SetHandler(this);
	_show_btn._visible = true;
	_show_btn.SetCoordinates(80, 200);
	_uimanager->Add(&_show_btn);

	char content[][50] = {
		"text 1",
		"text 2",
		"text 3"
	};

	_scroll_box.Init();
	_scroll_box.SetCoordinates(778,55+80);	
	_testContent = CaseFileScrollBox::BuildContent("Title", content, 3);
	_scroll_box.SetContent(_testContent);	
	_uimanager->Add(&_scroll_box);

}

void CaseFileScreen::OnLoad()
{
	/*CONTENT OF THIS FUNCTION is temporary until we have actual data*/
	_listmanager.Clear();
	
	for (int i = 0; i < _list.size(); i++) {
		CaseFileBoxItem* item = _list.at(i);
		SAFE_DELETE(item);
	}
	_list.clear();

	std::vector<enum EvidenceType>* p = &g_gameData.profiles;
	if (_mode == CASE_FILE_MODE_CLUES)
	{
		p = &g_gameData.clues;
	}

	/////////////////////////////////////////////////
	///For testing
	/*
	std::vector<enum EvidenceType> temp;
	temp.push_back(EVIDENCE_TYPE_RIDGEONY);
	temp.push_back(EVIDENCE_TYPE_REDYOUNG);
	temp.push_back(EVIDENCE_TYPE_EMMA_TEST_RESULT);
	temp.push_back(EVIDENCE_TYPE_COFFEE);
	p = &temp;
	/**/
	/////////////////////////////////////////////////

	int count = p->size();
	int box_width = 317;
	int gap = 50;
	int total_width = (box_width * count) + (gap* (count-1));
	int startx = (LOGICAL_WIDTH / 2) - (total_width / 2);
	int y = 585;

	for (int i = 0; i < count;i++) {
		CaseFileBoxItem* item = new CaseFileBoxItem();
		enum EvidenceType type = p->at(i);
		int rid = GetEvidenceResource(type);
		
		item->Load(rid, rid);
		item->SetGlowImage(CASE_ITEM_HIGLIGHT_IMG);
		item->SetID(ICONBOX_ITEM_ID_BASE + i);
		item->SetCoordinates(startx + LOGICAL_WIDTH, y);
		item->MoveTo(startx);
		item->SetHandler(this);
		item->SetType(type);

		// compute coordinates
		_listmanager.Add(item);
		_list.push_back(item);

		startx += box_width + gap;
	}

	if (_first_load) {
		_state = CASEFILE_STATE_PAUSE;
		_lastTime = SDL_GetTicks();
		_first_load = false;
	}
	else {
		_state = CASEFILE_STATE_NORMAL;
	}

	_black_overlay.LoadFromResource(BLACK_LINES_OVERLAY_IMG);
	_black_overlay.SetCoordinates(0, 0);

	_talk_screen.Load();
	FileDialogParser parser;
	parser.LoadFromFile("scripts/casefile.txt", _command_list);
	
	_selected_index = 0;
	if (_list.size() == 0)
		_selected_index = -1;
}

void CaseFileScreen::OnUpdate(float elapsed)
{
	if (_state == CASEFILE_STATE_PAUSE) {
		Uint32 currentTime = SDL_GetTicks();
		float diff = (currentTime - _lastTime) / 1000.0f;
		if (diff >= 2) {
			_state = CASEFILE_STATE_TYPING;
			_talk_screen.RedirectCommand(_command_list);
			_talk_screen.StartDialog();
		}
	}
	else if (_state == CASEFILE_STATE_TYPING) {
		if (_talk_screen.UpdateTalkDialog(elapsed) == TALKSCREEN_STATE_COMPLETE) {
			_state = CASEFILE_STATE_NORMAL;
		}
	}

	SceneFader::OnUpdate(elapsed);
	_uimanager->OnUpdate(elapsed);
	_listmanager.OnUpdate(elapsed);
}

void CaseFileScreen::OnInternalDraw()
{
	_bg.Draw(0,0);
	_fg.Draw(0, 80);
	_listmanager.OnDraw();
	_uimanager->OnDraw();

	if (_list.size() == 0) {
		Texture* t = SDLGX_GetTextCenter(LOGICAL_WIDTH / 2, 750, "List is empty", FONT_MYRIADPRO_REGULAR, 50, { 255,255,255 });
		t->SetBlendMode(SDL_BLENDMODE_BLEND);
		t->SetAlpha(200);
		t->Draw();
		SAFE_DELETE(t);
	}

	if (_state == CASEFILE_STATE_TYPING) {
		_black_overlay.Draw();
		_talk_screen.DrawTalkDialog();
	}

	for (int i = 0;i < _list.size();i++) {
		_list.at(i)->SetSelected(i == _selected_index);
	}

	if (_list.size() > 0) {
		EvidenceType type = _list.at(_selected_index)->GetType();
		////////////////////////
		// TODO
		// Set picture and text on listbox
		///////////////////////
	}
}

void CaseFileScreen::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID()) {
	case 0:	//back button
		Hide();
		break;
	case 3: //clues
		_clues_btn._visible = false;
		_profiles_btn._visible = true;
		_mode = CASE_FILE_MODE_PROFILE;
		//temporary
		OnLoad();
		break;
	case 4:	//Profiles
		_clues_btn._visible = true;
		_profiles_btn._visible = false;
		_mode = CASE_FILE_MODE_CLUES;
		//temporary
		OnLoad();
		break;
	case 5: // Show button
		if (_selected_index != -1)
		{
			EvidenceType type_sel = _list.at(_selected_index)->GetType();
			if (g_gameData.next_clue != _list.at(_selected_index)->GetType())
			{
				std::string errorTom[] = {
					"I don't think that's correct.",
					"Nope, that's not the correct one.",
					"Try again."
				};

				int index = rand() % 3;
				SetErrorString(errorTom[index]);

				_state = CASEFILE_STATE_TYPING;
				_talk_screen.RedirectCommand(_command_list);
				_talk_screen.StartDialog();
			}
			else {
				// close this and close parent
				if (_handler) {
					_handler->OnCustomEvent(this, ON_CORRECT_CLUE_EVNT);
				}
			}
		}
		break;
	}

	if (b->GetID() >= ICONBOX_ITEM_ID_BASE) {
		// what was clicked is item
		printf("\n Evidence item clicked %d", b->GetID());
		int index = b->GetID() - ICONBOX_ITEM_ID_BASE;
		_selected_index = index;
	}
}

void CaseFileScreen::OnButtonHold(sdlgx::gui::Button* b)
{
	switch (b->GetID()) {
	case 1:	  //arrow right
		Move(-1);
		break;
	case 2: //arrow left
		Move(1);
		break;
	}
}

bool CaseFileScreen::OnEvent(SDL_Event* e)
{
	if (_state == CASEFILE_STATE_TYPING) {
		UIManager* uiman = _talk_screen.GetUIManager();
		return State::HandleUI(e, uiman);
	}

	if (State::OnEvent(e))
		return true;
	return State::HandleUI(e, &_listmanager);
}

void CaseFileScreen::Move(int direction)
{
	if (_list.size() == 0)return;
	CaseFileBoxItem* item = _list.at(0);
	
	int bound_x = (LOGICAL_WIDTH / 2) - (item->GetWidth() / 2);

	int step = item->GetWidth();
	for (int i = 0; i < _list.size(); i++) {
		item = _list.at(i);
		int target = item->_x + (step*direction);

		item->MoveTo(target);
	}
}

void CaseFileScreen::SetErrorString(std::string error)
{
	//clear first
	for (int i = 0; i < _command_list.size(); i++) {
		SAFE_DELETE(_command_list.at(i));
	}

	_command_list.clear();

	Commands* cmd = NULL;

	cmd = new DialogLineCmd();
	DialogLineCmd* tmp = (DialogLineCmd*)cmd;
	tmp->name = "Tom";
	tmp->line = error;
	tmp->display_timesec = 0.5;
	_command_list.push_back(cmd);
	
	cmd = new Commands(COMMAND_TYPE_WAIT);
	_command_list.push_back(cmd);

	cmd = new Commands(COMMAND_TYPE_ENDSCRIPT);
	_command_list.push_back(cmd);
}

void CaseFileScreen::SetCustomEventHandler(ICustomEvent* handler)
{
	_handler = handler;
}
#include "state.h"
#include "engine.h"

using namespace sdlgx::core;


State::State():
	m_id(-1),
	m_initialized(false),
   _uimanager(NULL)
{
}

State::State(unsigned short id)
	: m_id(id), m_initialized(false),
	_uimanager(NULL)
{
	//...
}

State::~State()
{
	//...
}

void State::OnUpdate(float elapsed)
{
	if (_uimanager != NULL)
	{
		_uimanager->OnUpdate(elapsed);
	}
}

void State::OnDraw()
{
	if (_uimanager != NULL)
	{
		_uimanager->OnDraw();
	}
}

bool State::HandleUI(SDL_Event* e, 
	sdlgx::gui::UIManager* uimanager)
{
	
	if (uimanager == NULL)
		uimanager = _uimanager;

	if (uimanager == NULL) return false;

	float factorX = CURRENT_GRAPHICS->GetScaleRatioW();
	float factorY = CURRENT_GRAPHICS->GetScaleRatioH();

	switch (e->type) {
		case SDL_MOUSEBUTTONDOWN:
			switch (e->button.button) {
				case SDL_BUTTON_LEFT:
					int mouseX = e->button.x * factorX;
					int mouseY = e->button.y * factorY;
					uimanager->OnMouseDown(mouseX, mouseY);
				break;
			}
		break;
		case SDL_MOUSEBUTTONUP:
			switch (e->button.button) {
				case SDL_BUTTON_LEFT:
					int mouseX = e->button.x * factorX;
					int mouseY = e->button.y * factorY;
					uimanager->OnMouseUp(mouseX, mouseY);
				break;
			}
		break;
		case SDL_MOUSEMOTION:
			int mouseX = e->motion.x * factorX;
			int mouseY = e->motion.y * factorY;
			uimanager->OnMouseMove(mouseX, mouseY);
			break;
	}
	return false;
}

bool State::OnEvent(SDL_Event* e)
{
	bool ret = false;
	switch (e->type) {

		case SDL_KEYDOWN: 
			ret = OnKeyDown(e->key.keysym.sym);
		break;

	case SDL_KEYUP:
		ret = OnKeyUp(e->key.keysym.sym);
		break;
	}

	if (ret) return true;
	ret = HandleUI(e);

	return ret;
}

bool State::OnKeyDown(SDL_Keycode sym) {
	return false;
}

bool State::OnKeyUp(SDL_Keycode sym) {
	return false;
}

void State::Launch()
{
	if (!IsInitialized())
	{
		OnInitialize();
		SetInitialized(true);
	}

	OnLoad();
}
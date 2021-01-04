#include "engine.h"
#include "resource.h"
#include "font.h"

using namespace std;
using namespace sdlgx::core;
using namespace sdlgx::scene;
using namespace sdlgx::resource;

Engine* Engine::m_instance = NULL;

Engine::Engine() : m_graphics(NULL), m_state(NULL), m_transition(NULL)
{
	
}


Engine::~Engine()
{
	m_graphics = NULL;
	m_state = NULL;
	m_transition = NULL;

	State* state = NULL;
	if (m_state_list.first(state))
	{
		do {
			state->OnClose();
			SAFE_DELETE(state);
		} while (m_state_list.getNext(state));
	}
	m_state_list.makeEmpty();
}

Engine* Engine::GetInstance()
{
	if (m_instance == NULL) {
		m_instance = new Engine();
	}
	return m_instance;
}

void Engine::Shutdown()
{
	m_quit = true;
}

void Engine::SetGraphicsSetings(const struct GraphicsSetup& setup)
{
	SAFE_DELETE(m_graphics);
	m_graphics = new Graphics();
	m_graphics->Initialize(setup);
}

void Engine::Run()
{
	Uint32 lastTime=0, currentTime;
	float elapsed = 0.0f;
	m_quit = false;
	SDL_Event event;

	while (!m_quit) {
		currentTime = SDL_GetTicks();
		elapsed = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		///////////////////////////////
		// force 60 FPS
		//elapsed = 1.0f / 60.0f;
		///////////////////////////////

		while (SDL_PollEvent(&event)) {
			OnEvent(&event);
		}

		if (m_state == NULL) continue;
		m_state->OnUpdate(elapsed);

		m_graphics->Clear();		
		m_state->OnDraw( );
		m_graphics->Present();
	}

	SDLGX_FontCleanUp();
	ResourceManager::Cleanup();
	m_graphics->Cleanup();
	SAFE_DELETE(m_graphics);
	SAFE_DELETE(m_instance);
}


void Engine::AddState(State* state)
{
	if (!state)	return;
	m_state_list.insert(state);

	if (m_state == NULL)
	{
		SwitchState(state);
	}
}

void Engine::ChangeState(unsigned short id, TransitionType t)
{
	State* state = NULL;
		
	if (m_state_list.first(state))
	{
		do
		{
			if (state->GetStateID() == id)
			{
				if (m_state == NULL) {
					SwitchState(state);
				}
				else {
					switch (t) {
					case TRANSITION_NONE:
						m_state = state;
						break;
					case TRANSITION_FADE:
						State* o = m_state;
						FadeTransition* trans = new FadeTransition();
						trans->Initialize(o, state, &m_state);
						trans->SetColor(255, 255, 255);
						m_state = trans;
						break;
					}
				}
				return;
			
			}
		} while (m_state_list.getNext(state));
	}
}

void Engine::SwitchState(State* state)
{
	m_state = state;
	m_state->Launch();
}

State* Engine::GetState(unsigned short id)
{
	State* state = NULL;
	if (m_state_list.first(state))
	{
		do
		{
			if (state->GetStateID() == id)
			{				
				return state;
			}
		} while (m_state_list.getNext(state));
	}

	return NULL;
}

void Engine::OnEvent(SDL_Event* event)
{
	//TODO handle default events
	//User requests quit
	if (event->type == SDL_QUIT)
	{
		m_quit = true;
	}
	else if (event->type == SDL_WINDOWEVENT)
	{
		if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			m_graphics->SetResize(true);
		}
		
	}

	if(m_state != NULL)
		m_state->OnEvent(event);
}

///////////////////////////////////////////////
// SDL Game Extenstion framework engine
// v1.0
// Created: August 07, 2016
//			LMP milestone 37, USOUND 36
// Created by: Ruell Magpayo <ruellm@yahoo.com
//
///////////////////////////////////////////////

#pragma once
#include "sdlgx_common.h"
#include "state.h"
#include "graphics.h"
#include "transition_effects.h"
#include "link_list.h"

namespace sdlgx {
	namespace core {

		class SDLGX_API Engine
		{
		public:
			~Engine();			
			static Engine* GetInstance();

			void Shutdown();
			void SetGraphicsSetings(const struct GraphicsSetup& setup);
			void Run();

			void AddState(State* state);
			State* GetState(unsigned short id);
			void SwitchState(State* state);
			void ChangeState(unsigned short id, 
				sdlgx::scene::TransitionType t = sdlgx::scene::TRANSITION_NONE);
			
			
			inline State* GetCurrentState() {
				return m_state;
			}

			inline Graphics* GetGraphics() {
				return m_graphics;
			}

	
		private:
			Engine();
			static Engine* m_instance;			
			Graphics* m_graphics;
			
			bool m_quit;
			State* m_state;
			//sdlgx::<State*> m_state_list;
			sdlgx::common::LinkedList<State*> m_state_list;
			sdlgx::scene::TransitionEffects* m_transition;

			void OnEvent(SDL_Event* event);
			

		};

		#define CURRENT_RENDERER		Engine::GetInstance()->GetGraphics()->GetRenderer()
		#define CURRENT_GRAPHICS		Engine::GetInstance()->GetGraphics()
		#define SCREEN_WIDTH			Engine::GetInstance()->GetGraphics()->GetWidth()
		#define SCREEN_HEIGHT			Engine::GetInstance()->GetGraphics()->GetHeight()
		#define	LOGICAL_WIDTH			Engine::GetInstance()->GetGraphics()->GetLogicalWidth()
		#define	LOGICAL_HEIGHT			Engine::GetInstance()->GetGraphics()->GetLogicalHeight()
	}
}


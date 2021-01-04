#pragma once
#include "sdlgx_common.h"
#include "uimanager.h"

namespace sdlgx {
	namespace core {
		class SDLGX_API State
		{
		public:
			State();
			State(unsigned short id);
			virtual ~State();			

			void Launch();

			inline void SetID(int id){
				m_id = id;
			}

			inline unsigned short int GetStateID() {
				return m_id;
			}

			inline bool IsInitialized() {
				return m_initialized;
			}
			
			inline void SetInitialized(bool val) {
				m_initialized = val;
			}

			virtual void OnInitialize(){}
			virtual void OnLoad() { }
			virtual void OnUpdate(float elapsed);
			virtual void OnDraw();
			virtual void OnUnload() { }
			virtual void OnClose() {}					// partner of unitialize
			virtual bool OnEvent(SDL_Event* e);
			
		protected:
			unsigned short m_id;
			bool m_initialized;
			sdlgx::gui::UIManager* _uimanager;

			virtual bool OnKeyDown(SDL_Keycode sym);
			virtual bool OnKeyUp(SDL_Keycode sym);

			bool HandleUI(SDL_Event* e, 
				sdlgx::gui::UIManager* uimanager = NULL);

		};
	}
}


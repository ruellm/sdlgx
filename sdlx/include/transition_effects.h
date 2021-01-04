#pragma once
#include "sdlgx_common.h"
#include "state.h"
#include "texture.h"

namespace sdlgx {
	namespace scene {
		class SDLGX_API TransitionEffects :
			public sdlgx::core::State
		{
		public:
			TransitionEffects();
			~TransitionEffects();
			virtual bool OnEvent(SDL_Event* e);
		};

		class SDLGX_API FadeTransition 
			: public TransitionEffects
		{
		public: 
			FadeTransition();
			~FadeTransition();
			
			void Initialize(State* o, State* n, State** c);			
			virtual void OnUpdate(float elapsed);
			virtual void OnDraw();
			void SetColor(Uint8 r, Uint8 g, Uint8 b);

		private:
			Texture _texture;
			State* _old_state;
			State* _new_state;
			State** _current;
			State* _now;
			float _alpha;
			short _transition;
			float _diff;

			Uint8 _red;
			Uint8 _green;
			Uint8 _blue;
		};

		enum TransitionType {
			TRANSITION_NONE = 0,
			TRANSITION_FADE = 1
		};
	}
}


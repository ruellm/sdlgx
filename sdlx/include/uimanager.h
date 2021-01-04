#pragma once
#include "sdlgx_common.h"
#include "link_list.h"
#include "uibase.h"

namespace sdlgx {
	namespace gui {
		class SDLGX_API UIManager
		{
		public:
			UIManager();
			~UIManager();

			void Add(UIBase* o);
			void Remove(UIBase* o);
			void Clear();
			void OnMouseMove(int x, int y);
			bool OnMouseDown(int x, int y);
			bool OnMouseUp(int x, int y);
			bool OnKeyDown(int keycode);
			bool OnKeyPress(int keycode);
			void SetFocus(UIBase* control);
			void SetFocusIdx(int idx);
			UIBase* GetByID(int id);

			void OnUpdate(float elapsed);
			void OnDraw();
			
		private:
			sdlgx::common::LinkedList<UIBase*> m_ui_list;
			UIBase* m_focus;
		};
	}
}


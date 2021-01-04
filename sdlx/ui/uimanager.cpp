#include "uimanager.h"

using namespace sdlgx::gui;

UIManager::UIManager() 
	: m_focus(NULL)
{
}

UIManager::~UIManager()
{
	m_focus = NULL;
}

void UIManager::Add(UIBase* o)
{
	int count = m_ui_list.count();
	o->SetIndex(count);
	m_ui_list.insert(o);
}

void UIManager::Remove(UIBase* o)
{
	m_ui_list.remove(o);
}

void UIManager::Clear()
{
	m_ui_list.makeEmpty();
}

void UIManager::OnMouseMove(int x, int y)
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			if (!obj->_visible) continue;
			obj->OnMouseMove(x, y);

			if (x >= obj->_x && x <= obj->_x + obj->_width &&
				(y >= obj->_y && y <= obj->_y + obj->_height)) {
				obj->OnMouseEnterMove(x, y);
			}
			else {
				obj->OnMouseLeave();
			}
		} while (m_ui_list.getNext(obj));
	}
}

bool UIManager::OnMouseDown(int x, int y)
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			if (!obj->_visible) continue;

			if (x >= obj->_x && x <= obj->_x + obj->_width &&
				(y >= obj->_y && y <= obj->_y + obj->_height)) {
				obj->OnMouseDown(x, y);
				return true;
			}
			else {
				obj->OnMouseDownOut(x, y);
			}

		} while (m_ui_list.getNext(obj));
	}
	return false;
}

bool UIManager::OnMouseUp(int x, int y)
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			if (!obj->_visible) continue;

			if (x >= obj->_x && x <= obj->_x + obj->_width &&
				(y >= obj->_y && y <= obj->_y + obj->_height)) {
				obj->OnMouseUp(x, y);
				return true;
			}
			else {
				obj->OnMouseUpOut(x, y);
			}

		} while (m_ui_list.getNext(obj));
	}
	return false;
}

bool UIManager::OnKeyDown(int keycode)
{
	if (m_focus) {
		return m_focus->OnKeyDown(keycode);
	}
	return false;
}

bool UIManager::OnKeyPress(int keycode)
{
	if (m_focus) {
		return m_focus->OnKeyPress(keycode);
	}
	return false;
}

void UIManager::SetFocus(UIBase* control)
{
	m_focus = control;
}

void UIManager::SetFocusIdx(int idx)
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			if (obj->GetIndex() == idx) {
				m_focus = obj;
				break;
			}

		} while (m_ui_list.getNext(obj));
	}
}

UIBase* UIManager::GetByID(int id)
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			if (obj->GetID() == id)
				return obj;

		} while (m_ui_list.getNext(obj));
	}
	return NULL;
}

void UIManager::OnUpdate(float elapsed)
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			obj->OnUpdate(elapsed);
		} while (m_ui_list.getNext(obj));
	}
}

void UIManager::OnDraw()
{
	UIBase* obj = NULL;
	if (m_ui_list.first(obj))
	{
		do {
			
			if (!obj->_visible) continue;			
			obj->OnDraw();

		} while (m_ui_list.getNext(obj));
	}
}
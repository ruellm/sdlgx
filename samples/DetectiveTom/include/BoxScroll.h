#pragma once

#include "ScrollBar.h"
#include "texture.h"

class BoxScroll : public sdlgx::gui::UIBase
{
public:
	BoxScroll();
	virtual ~BoxScroll();

	virtual void OnDraw();
	virtual void OnUpdate(float elapsed);
	void SetBG(int resid);

	void SetContent(sdlgx::scene::Texture* surface);
	sdlgx::scene::Texture* GetContent();

	virtual bool OnMouseMove(int x, int y);
	virtual bool OnMouseDown(int x, int y);
	virtual bool OnMouseUp(int x, int y);
	virtual bool OnMouseUpOut(int x, int y);

	ScrollBar* GetScrollBar();

protected:
	sdlgx::scene::Texture _bg;
	sdlgx::scene::Texture* _window;		// created outside
	int _yoffset;

	ScrollBar _bar;

	int _window_X_offset;
	int _window_Y_offset;
	int _viewport_height;
};

/**/
/**/
/**/
class CaseFileScrollBox : public BoxScroll
{
public:
	CaseFileScrollBox();
	~CaseFileScrollBox();

	void Init();
	virtual void SetCoordinates(int x, int y);

	static sdlgx::scene::Texture* BuildContent(
		char* title,
		char content[][50],
		int count);

};

/**/
/**/
/**/
class LogScrollBox : public BoxScroll
{
public:
	LogScrollBox();
	~LogScrollBox();

	void Init();
	void Load();
	virtual void SetCoordinates(int x, int y);

};
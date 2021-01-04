#pragma once

#include "uibase.h"
#include "texture.h"

class ScrollBar : public sdlgx::gui::UIBase
{
public:
	ScrollBar();
	~ScrollBar();

	void SetBarImage(int resID);
	void SetThumbImage(int resID);	//Temporary, thumb must be a struct

	virtual bool OnMouseMove(int x, int y);
	virtual bool OnMouseDown(int x, int y);
	virtual bool OnMouseUp(int x, int y);

	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();
private:
	sdlgx::scene::Texture _bar;
	
	sdlgx::scene::Texture _thumb; //temporary replace this with a struct later on
	int _thumb_x;
	int _thumb_y;
	int _offset;
	int _old_y;
	bool _is_drag;
	
};


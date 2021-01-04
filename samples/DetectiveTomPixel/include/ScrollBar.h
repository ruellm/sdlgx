#pragma once

#include "uibase.h"
#include "texture.h"
#include "GlowButton.h"

typedef enum _scrollbartype {
	SCROLLBAR_VERTICAL = 0,
	SCROLLBAR_HORIZONTAL
}ScrollBarType;

class ScrollBar : public sdlgx::gui::UIBase, public sdlgx::gui::IButtonEventHandler
{
public:
	ScrollBar();
	~ScrollBar();

	void SetBarImage(int resID);
	void SetThumbImage(int resID);	//Temporary, thumb must be a struct

	virtual bool OnMouseMove(int x, int y);
	virtual bool OnMouseDown(int x, int y);
	virtual bool OnMouseUp(int x, int y);
	virtual bool OnMouseUpOut(int x, int y);

	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();

	void SetType(ScrollBarType type);
	void SetButton1Param(int idle, int glow, float accel=1.0f);
	void SetButton2Param(int idle, int glow, float accel=1.0f);
	void SetGap(int gap);
	void SetStep(int step);
	void Refresh();

	float GetPercentage();

protected:
	sdlgx::scene::Texture _bar;	
	sdlgx::scene::Texture _thumb; //temporary replace this with a struct later on
	GlowButton* _button1;
	GlowButton* _button2;

	int _thumb_x;
	int _thumb_y;
	int _offset;
	int _old_x;
	int _old_y;
	bool _is_drag;
	int _gap;
	int _step;
	int _barx;
	int _bary;
	int _basex;
	int _basey;
	ScrollBarType _type;
		
	virtual void OnButtonClick(sdlgx::gui::Button* b);
};

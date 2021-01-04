#pragma once
#include "button.h"
#include "glow_image.h"

class GlowButton : public sdlgx::gui::Button
{
public:
	GlowButton();
	~GlowButton();

	void SetGlowImage(int resid, float accel=10);

	virtual void OnDraw();
	virtual void OnUpdate(float elapsed);

private:
	sdlgx::scene::GlowImage _glow;

};


class GlowToggleButton
	: public GlowButton
{
public:	
	GlowToggleButton();
	virtual bool OnMouseDown(int x, int y);
	virtual void OnDraw();
	bool IsToggled();
	void SetToggled(bool value);

private:
	bool _toggled;
};

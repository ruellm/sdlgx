#pragma once
#include "button.h"
#include "glow_image.h"
#include <string>

class GlowButton : public sdlgx::gui::Button
{
public:
	GlowButton();
	virtual ~GlowButton();

	void SetGlowImage(int resid, float accel=1);

	virtual void OnDraw();
	virtual void OnUpdate(float elapsed);

private:
	sdlgx::scene::GlowImage _glow;

};

/**/
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

/**/
class GlowButtonText : public GlowButton
{
public:
	GlowButtonText();
	~GlowButtonText();

	void SetTextParam(char* szText, int fontid, int size,
		SDL_Color idle, SDL_Color hover);
	virtual void OnDraw();

private:
	sdlgx::scene::Texture* _idle;
	sdlgx::scene::Texture* _hover;
	std::string _text;
};
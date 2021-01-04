#pragma once
#include "rectangle_button.h"
#include "texture.h"

class RectTextButton : public sdlgx::gui::RectangleButton {
public:
	RectTextButton();
	~RectTextButton();
	virtual void DrawText();
	void SetTextParam(const char* szText,
		int fontid, int size,
		SDL_Color idle, SDL_Color hover);
private:
	sdlgx::scene::Texture* _idle;
	sdlgx::scene::Texture* _hover;
};
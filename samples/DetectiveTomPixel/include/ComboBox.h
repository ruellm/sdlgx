#pragma once
#include "uibase.h"
#include "GlowButton.h"
#include "texture.h"
#include "text_button.h"

#include <vector> 

class ComboBox 
	: public sdlgx::gui::UIBase, public sdlgx::gui::IButtonEventHandler
{
public:
	ComboBox();
	~ComboBox();

	virtual bool OnMouseDown(int x, int y);
	virtual bool OnMouseUp(int x, int y);

	virtual bool OnMouseDownOut(int x, int y);
	virtual bool OnMouseMove(int x, int y);

	virtual void OnUpdate(float elasped);
	virtual void OnDraw();

	void Load(char options[][20], int count);
	void SetToggleButton(int residle, int clicked, int glow);
	void SetTextBoxImg(int resid);

private:
	GlowToggleButton _toggle;	
	sdlgx::scene::Texture _textbox; //replace with own box drawing to save resource
	std::vector<sdlgx::gui::TextButton*> _items;

	virtual void OnButtonClick(sdlgx::gui::Button *b);
};


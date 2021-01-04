#pragma once

#include <vector>
#include "sprite_sheet.h"

class SpriteExtenshion : 
	public sdlgx::scene::SpriteSheet, 
	public sdlgx::scene::ISpriteCallback
{

private:
	std::vector<sdlgx::scene::SpriteSheet*> _list;
	int _current_idx;

public:
	SpriteExtenshion();
	~SpriteExtenshion();
	
	void AddSprite(SpriteSheet* s);
	virtual void SetAlpha(unsigned char alpha);

	virtual void Reset();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw(int x, int y);
	virtual void OnDrawFlip(int x, int y, SDL_RendererFlip flip);
	
	virtual void OnAnimationComplete(sdlgx::scene::SpriteSheet* sprite);
};
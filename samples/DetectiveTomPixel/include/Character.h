#pragma once

#include "sprite_sheet.h"
#include <vector>
#include <string>

struct SpriteInfo
{
	std::string path;
	int character_id;
	int sprite_index;
	int fps;
	int frame_count;
	bool loop;
	sdlgx::scene::SpriteSheet* sprite;

	SpriteInfo() {
		sprite = NULL;
	}
	~SpriteInfo() {
		SAFE_DELETE(sprite);
	}
};

class Character : public sdlgx::core::ObjectBase
{

public:
	Character();
	~Character();

	void SetActive(bool value);
	void SetIndex(int i);
	void SetInvert(bool value);
	void SetAlpha(unsigned char alpha);
	void SetFPS(int value);
	void SetIdleIndex(int index);
	void SetPivot(int x, int y);
	void GoIdle(int index = -1);

	sdlgx::scene::SpriteSheet*	GetCurrentSprite();

	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();

	void LoadSprites(int id);

protected:
private:
	sdlgx::scene::SpriteSheet* _current;
	sdlgx::scene::SpriteSheet** _sprites;
	int _sprite_count;
	int _idleIndex;
	bool _invert;
	unsigned char _alpha;
	int _pivot_x;
	int _pivot_y;
};

/**/
class Tom : public Character 
{
public: 
	virtual void Load();
};

class Emma : public Character
{
public:
	virtual void Load();
};

class RedYoung : public Character
{
public:
	virtual void Load();
};

#include "Character.h"
#include "SpriteExtension.h"
#include "definitions.h"
#include "GameData.h"

using namespace sdlgx::scene;

Character::Character() : 
	_current(NULL), _invert(false), _alpha(255),
	_sprites(NULL), _pivot_x(0), _pivot_y(0)
{
	
}

Character::~Character()
{
	SAFE_DELETE_ARRAY(_sprites);
}


void Character::LoadSprites(int id)
{
	_sprite_count = 0;
	// count total sprites first
	for (int i = 0;i < g_gameData.sprite_bank.size();i++) {
		if (g_gameData.sprite_bank.at(i)->character_id == id) {
			_sprite_count++;
		}
	}

	_sprites = new SpriteSheet*[_sprite_count];
	
	// match the sprite to map
	for (int i = 0;i < g_gameData.sprite_bank.size();i++) {
		SpriteInfo* info = g_gameData.sprite_bank.at(i);
		if (info->character_id == id) {
			_sprites[info->sprite_index] = info->sprite;
		}
	}

}

void Character::SetIndex(int i)
{
	if (i > _sprite_count || i < 0) return;
	_current = _sprites[i];
}

void Character::SetIdleIndex(int index)
{
	_idleIndex = index;
}


void Character::SetInvert(bool value)
{
	_invert = value;
}

void Character::GoIdle(int idx)
{
	int idle = idx;
	if (idx == -1)
		idle = _idleIndex;
	SetIndex(idle);
}

void Character::SetFPS(int value)
{
	if (_current == NULL) return;
	_current->SetFPS(value);
}

sdlgx::scene::SpriteSheet*	
Character::GetCurrentSprite()
{
	return _current;
}

void Character::OnUpdate(float elapsed)
{
	if (_current == NULL) return;
	if (!_visible) return;

	_current->OnUpdate(elapsed);
}

void Character::OnDraw()
{
	if (_current == NULL) return;
	if (!_visible) return;

	int x = _pivot_x - (_current->GetFrameWidth() / 2);
	int y = _pivot_y - (_current->GetHeight() / 2);

	if (_invert)
		_current->OnDrawFlip(x, y, SDL_FLIP_HORIZONTAL);
	else
		_current->OnDraw(x, y);
}

void Character::SetActive(bool value)
{
	if (_current == NULL) return;
	if (_alpha <= 0) return;

	if (value) {
		_current->SetBlendMode(SDL_BLENDMODE_BLEND);
		_current->SetAlpha(255);
	}
	else {
		_current->SetBlendMode(SDL_BLENDMODE_BLEND);
		_current->SetAlpha(100);

		GoIdle();
	}
}

void Character::SetAlpha(unsigned char alpha)
{
	if (_current == NULL) return;
	_current->SetBlendMode(SDL_BLENDMODE_BLEND);
	_current->SetAlpha(alpha);

	_alpha = alpha;	
}

void Character::SetPivot(int x, int y)
{
	_pivot_x = x;
	_pivot_y = y;
}

/**/
/**/
/**/
void Tom::Load()
{
	LoadSprites(CHARACTER_TOM);
}

void Emma::Load()
{
	LoadSprites(CHARACTER_EMMA);
}


void RedYoung::Load()
{
	LoadSprites(CHARACTER_RED);
}

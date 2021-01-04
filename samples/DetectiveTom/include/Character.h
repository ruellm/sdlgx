#pragma once

#include "sprite_sheet.h"
#include "definitions.h"
#include "SDL_thread.h"
#include "CustomEvent.h"
#include <vector>

#define TOM_BASE_BATCH_0		BATCH_0_SPRITES + 39
#define EMMA_BASE_BATCH_0		BATCH_0_SPRITES + 0
#define RED_BASE_BATCH_0		BATCH_0_SPRITES + 35

struct SpriteDefinition
{
	int resid;
	int frame_count;
	int fps;
	bool loop;
};

struct SpriteSplitInfo
{
	bool grouped;
	int count;
	bool loop;
};


struct SpriteCacheInfo
{
	sdlgx::scene::SpriteSheet* sprite;
	int count;
	bool idle;
	SDL_mutex *mutex;

	SpriteCacheInfo() {
		count = 0;
		sprite = NULL;
		idle = false;
		mutex = NULL;
	}

	~SpriteCacheInfo() {
		SAFE_DELETE(sprite);
		if(mutex)
			SDL_DestroyMutex(mutex);
	}
};

#define MAX_CACHE 1
#define MAX_CACHE_IDLE 1

class Character : public sdlgx::core::ObjectBase
{

public:
	Character();
	~Character();

	static void InitializeMutex();
	static void Cleanup();
	static SDL_mutex *_img_mutex;

	void SetActive(bool value);
	void SetIndex(int i);
	void SetInvert(bool value);
	void SetAlpha(unsigned char alpha);
	void SetFPS(int value);
	void SetIdleIndex(int index);
	void GoIdle(int index = -1);

	sdlgx::scene::SpriteSheet*	GetCurrentSprite();

	virtual void Load();
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();

	void InitializeCache(int sprite_count);
	void RefreshCache();
	void CacheIndex(int index);
	void CacheIndexIdle(int index);

	void PreLoadCache();
	void GenerateCache();
	void LoadNextCache();
	bool FreeCache(int index);
	void DoCache(int count);
	void LoadCacheIdle();
	void DisplayCache();
	void ForceLoad();
	void SetCustomEventHandler(ICustomEvent* handler);

protected:
	std::vector<sdlgx::scene::SpriteSheet*> _list;
	sdlgx::scene::SpriteSheet* _current;
	
	bool _invert;
	int _idleIdx;
	int _currIdx;
	struct SpriteDefinition* _sprite_info;
	struct SpriteSplitInfo* _split_info;


	//void LoadSprites(struct SpriteDefinition def[], int n,
		//struct SpriteSplitInfo info[], int n2);

	void Set(struct SpriteDefinition def[], struct SpriteSplitInfo info[]);

	
	//Cache implementation
	SpriteCacheInfo** _cache;
	int _cache_count;
	std::vector<int> _sequence;
	std::vector<int> _sequence_idle;
	int _tail_sequence;
	int _tail_sequence_idle;
	SDL_Thread* _thread;
	SDL_Thread* _threadIdle;
	SDL_Thread* _threadPRELOAD;
	ICustomEvent* _custom_event_handler;
	int _force_load_idx;
	int _curr_cache_idx;
	int _curr_cacheIDLE_idx;
	int _curr_regular_Idx;

	unsigned char _alpha;
private:
	void LoadSprite(int index);
	
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

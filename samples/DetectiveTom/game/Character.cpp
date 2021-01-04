#include "Character.h"
#include "SpriteExtension.h"
#include "definitions.h"

using namespace sdlgx::scene;

struct SpriteSplitInfo g_Tom_0_SplitInfo[] = {
	{true,2, false},	//ytj.png
	{true, 3, true },	//ytn_a.png
	{true, 2, false },	//ytn_l.png
	{false, 1, true },	//ytn_m.png
	{true, 4, false },	//yts.png
	{false, 1, true }, //ytt1_i.png
	{true, 2, true },	//ytt1_m.png
	{false,1, true },	//ytt2_i.png
	{true,2, true },	//ytt2_m.png
	{false,1, true },	//ytt3_i.png
	{true,2, true },	//ytt3_m.png
	{false,1, true },	//ytt4_a.png
	{false,1, true },	//ytt4_i.png
	{true,2, false },	//ytt4_m.png
	{true,2, true },	//yttk_a.png
	{false,1, true },	//yttk_i.png
	{ true,2, true },	//yttk_m.png

};

struct SpriteDefinition g_tom_0[] = {
	{ TOM_BASE_BATCH_0 + 0, 9, 24, false },		//ytj_1.png
	{ TOM_BASE_BATCH_0 + 1, 9, 24, false },		//ytj_2.png

	{ TOM_BASE_BATCH_0 + 2, 10, 24, false },	//ytn_a_1.png
	{ TOM_BASE_BATCH_0 + 3, 10, 24, false },	//ytn_a_2.png
	{ TOM_BASE_BATCH_0 + 4, 10, 24, false },	//ytn_a_3.png

	{ TOM_BASE_BATCH_0 + 5, 12, 24, false },	//ytn_l_1.png
	{ TOM_BASE_BATCH_0 + 6, 12, 24, false },	//ytn_l_2.png

	{ TOM_BASE_BATCH_0 + 7, 12, 24, false },	//ytn_m.png

	{ TOM_BASE_BATCH_0 + 8, 10, 24, false },	//yts_1.png
	{ TOM_BASE_BATCH_0 + 9, 10, 24, false },	//yts_2.png
	{ TOM_BASE_BATCH_0 + 10, 10, 24, false },	//yts_3.png
	{ TOM_BASE_BATCH_0 + 11, 2, 24, false },	//yts_4.png

	{ TOM_BASE_BATCH_0 + 12, 11, 24, false },	//ytt1_i.png

	{ TOM_BASE_BATCH_0 + 13, 9, 24, false },	//ytt1_m_1.png
	{ TOM_BASE_BATCH_0 + 14, 9, 24, false },	//ytt1_m_2.png

	{ TOM_BASE_BATCH_0 + 15, 10, 24, false },	//ytt2_i.png

	{ TOM_BASE_BATCH_0 + 16, 10, 24, false },	//ytt2_m_1.png
	{ TOM_BASE_BATCH_0 + 17, 10, 24, false },	//ytt2_m_2.png

	{ TOM_BASE_BATCH_0 + 18, 10, 24, false },	//ytt3_i.png

	{ TOM_BASE_BATCH_0 + 19, 10, 24, false },	//ytt3_m_1.png
	{ TOM_BASE_BATCH_0 + 20, 10, 24, false },	//ytt3_m_2.png

	{ TOM_BASE_BATCH_0 + 21, 6, 24, false },	//ytt4_a.png
	{ TOM_BASE_BATCH_0 + 22, 10, 24, false },	//ytt4_i.png

	{ TOM_BASE_BATCH_0 + 23, 8, 24, false },	//ytt4_m_1.png
	{ TOM_BASE_BATCH_0 + 24, 8, 24, false },	//ytt4_m_2.png

	{ TOM_BASE_BATCH_0 + 25, 9, 24, false },	//yttk_a_1.png
	{ TOM_BASE_BATCH_0 + 26, 9, 24, false },	//yttk_a_2.png

	{ TOM_BASE_BATCH_0 + 27, 10, 24, false },	//yttk_i.png

	{ TOM_BASE_BATCH_0 + 28, 10, 24, false },	//yttk_m_1.png
	{ TOM_BASE_BATCH_0 + 29, 10, 24, false },	//yttk_m_2.png
};

/*
  Emma sprite index
*/
struct SpriteSplitInfo g_Emma_0_SplitInfo[] = {
	{false, 1, true },		//eb_i.png
	{true, 3, true },		//eb_m.png
	{true, 4, false },		//Ef_a.png
	{true, 2, false },		//ef_m.png
	{false, 1, false },		//es.png
	{false, 1, true },	//esd_b.png
	{false, 1, true },	//esd_i.png
	{false, 1, false },	//esd_m.png
	{false, 1, true },	//et1_i.png
	{true, 3, true },		//et1_m.png
	{true, 2, true },		//et2_i.png
	{true, 3, true },		//et2_m.png
	{true, 3, true },		//et3_i.png
	{true, 4, true },		//et3_m.png
	{false, 1, true },		//et_A.png
	{false, 1, true },		//et_i.png
	{true, 3, true }		//et_m.png
};

struct SpriteDefinition g_Emma_0[] = {
	{ EMMA_BASE_BATCH_0 + 0, 10, 24, false },	//eb_i.png
	{ EMMA_BASE_BATCH_0 + 1, 10, 24, false },	//eb_m_1.png
	{ EMMA_BASE_BATCH_0 + 2, 10, 24, false },	//eb_m_2.png
	{ EMMA_BASE_BATCH_0 + 3, 6, 24, false },	//eb_m_3.png
	{ EMMA_BASE_BATCH_0 + 4, 10, 24, false },	//Ef_a_1.png
	{ EMMA_BASE_BATCH_0 + 5, 10, 24, false },	//Ef_a_2.png
	{ EMMA_BASE_BATCH_0 + 6, 10, 24, false },	//Ef_a_3.png
	{ EMMA_BASE_BATCH_0 + 7, 10, 24, false },	//Ef_a_4.png

	{ EMMA_BASE_BATCH_0 + 8, 9, 24, false },	//ef_m_1.png
	{ EMMA_BASE_BATCH_0 + 9, 9, 24, false },	//ef_m_2.png

	{ EMMA_BASE_BATCH_0 + 10, 11, 24, false },	//es.png
	{ EMMA_BASE_BATCH_0 + 11, 14, 24, false },	//esd_b.png
	{ EMMA_BASE_BATCH_0 + 12, 10, 24, false },	//esd_i.png
	{ EMMA_BASE_BATCH_0 + 13, 12, 24, false },	//esd_m.png	
	{ EMMA_BASE_BATCH_0 + 14, 10, 24, false },	//et1_i.png
	{ EMMA_BASE_BATCH_0 + 15, 12, 24, false },	//et1_m_1.png
	{ EMMA_BASE_BATCH_0 + 16, 12, 24, false },	//et1_m_2.png
	{ EMMA_BASE_BATCH_0 + 17, 12, 24, false },	//et1_m_3.png
	{ EMMA_BASE_BATCH_0 + 18, 10, 24, false },	//et2_i_1.png
	{ EMMA_BASE_BATCH_0 + 19, 11, 24, false },	//et2_i_2.png
	{ EMMA_BASE_BATCH_0 + 20, 10, 24, false },	//et2_m_1.png
	{ EMMA_BASE_BATCH_0 + 21, 10, 24, false },	//et2_m_2.png
	{ EMMA_BASE_BATCH_0 + 22, 6, 24, false },	//et2_m_3.png
	{ EMMA_BASE_BATCH_0 + 23, 10, 24, false },	//et3_i_1.png
	{ EMMA_BASE_BATCH_0 + 24, 10, 24, false },	//et3_i_2.png
	{ EMMA_BASE_BATCH_0 + 25, 9, 24, false },	//et3_i_3.png

	{ EMMA_BASE_BATCH_0 + 26, 10, 24, false },	//et3_m_1.png
	{ EMMA_BASE_BATCH_0 + 27, 10, 24, false },	//et3_m_2.png
	{ EMMA_BASE_BATCH_0 + 28, 10, 24, false },	//et3_m_3.png
	{ EMMA_BASE_BATCH_0 + 29, 4, 24, false },	//et3_m_4.png

	{ EMMA_BASE_BATCH_0 + 30, 10, 24, false },	//et_A.png
	{ EMMA_BASE_BATCH_0 + 31, 12, 24, false },	//et_i.png

	{ EMMA_BASE_BATCH_0 + 32, 10, 24, false },	//et_m_1.png
	{ EMMA_BASE_BATCH_0 + 33, 10, 24, false },	//et_m_2.png
	{ EMMA_BASE_BATCH_0 + 34, 6, 24, false },	//et_m_3.png
};

struct SpriteSplitInfo g_Red_0_SplitInfo[] = {
	{false,1, true },
	{ false,1, true },
	{ false,1, true },
	{ false,1, true },
};

struct SpriteDefinition g_Red_0[] = {
	{ RED_BASE_BATCH_0 + 0, 8, 24, false },		//yrf_i.png
	{ RED_BASE_BATCH_0 + 1, 7, 24, false },		//yrf_m.png
	{ RED_BASE_BATCH_0 + 2, 10, 24, false },	//yr_i.png
	{ RED_BASE_BATCH_0 + 3, 6, 24, false }		//yr_t.png
};


int LoadCacheThread(void* ptr);
int SpriteCacheThread(void* ptr);
int SpriteCacheIDLEThread(void* ptr);
int ForceLoadThread(void* ptr);

SDL_mutex* Character::_img_mutex = NULL;

Character::Character() 
	: _current(NULL), _idleIdx(-1), 
	_sprite_info(NULL), _split_info(NULL),
	_thread(NULL), _currIdx (-1), 
	_custom_event_handler(NULL), _curr_regular_Idx(-1)
{
	_visible = true;
}

Character::~Character()
{
	/*for (int i = 0;i < _list.size(); i++) {
		SpriteSheet* sprite = _list.at(i);
		SAFE_DELETE(sprite);
	}*/
	for (int i = 0; i < _cache_count;i++) {
		SAFE_DELETE(_cache[i]);
	}

	SAFE_DELETE_ARRAY(_cache);

	if (_thread)
	{
		int threadReturnValue = 0;
		SDL_WaitThread(_thread, &threadReturnValue);
		SDL_WaitThread(_threadIdle, &threadReturnValue);
		SDL_WaitThread(_threadPRELOAD, &threadReturnValue);		
	}
}

void Character::InitializeMutex()
{
	_img_mutex = SDL_CreateMutex();
}

void Character::Cleanup()
{
	SDL_DestroyMutex(_img_mutex);
}

void Character::Load()
{
	//...
}


void Character::SetIndex(int i)
{
	
	printf("\n Set Character %d=%d", GetID(), i);

	if (i == -1) {
		return;
	}

	if (_cache[i] == NULL) {
		printf("\n	We Delay, We Force load %d=%d", GetID(), i);
		_force_load_idx = i;
		SDL_CreateThread(ForceLoadThread,
			"ForceLoadThread", (void *)this);
	}

	while (_cache[i] == NULL) {
		SDL_Delay(10);
	}


	if (_curr_regular_Idx != _idleIdx &&
		_curr_regular_Idx != -1 &&
		(_cache[_curr_regular_Idx] && !_cache[_curr_regular_Idx]->idle) &&
		_curr_regular_Idx != i) {
		FreeCache(_curr_regular_Idx);
	}

	_current = _cache[i]->sprite;
	_currIdx = i;
	_curr_regular_Idx = i;
	_current->Reset();
	_curr_cache_idx++;

	if (_curr_cache_idx + 1 < _sequence.size()) {
		int idx_nxt = _sequence.at(_curr_cache_idx + 1);
		if (_cache[idx_nxt] == NULL) {
			_thread = SDL_CreateThread(SpriteCacheThread,
				"SpriteCacheThrd", (void *)this);
		}
	}
}

bool Character::FreeCache(int index)
{
	printf("\n Free Cache enter %d = %d", GetID(), index);

	if (_cache[index] ) {
		bool delete_me = true;
		if (_tail_sequence >= _sequence.size())
			delete_me = false;

		if (delete_me) {
			printf("\nDE-ALLOCATE %d=%d", GetID(), index);
			SAFE_DELETE(_cache[index]);
			_cache[index] = NULL;
			return true;
		}
	}

	return false;
}

void Character::SetIdleIndex(int index)
{
	printf("\n Set Idle %d= %d", GetID(), index);

	if (_idleIdx != -1 && _idleIdx != index &&  index != -1) {
		printf("\n Freeing old Idle %d= %d", GetID(), _idleIdx);
		FreeCache(_idleIdx);
	}

	if (_currIdx == _idleIdx) {
		GoIdle(index);
	}

	_idleIdx = index;
	_curr_cacheIDLE_idx++;
	if (_curr_cacheIDLE_idx + 1 < _sequence_idle.size()) {
		int idx_nxt = _sequence_idle.at(_curr_cacheIDLE_idx + 1);
		if (_cache[idx_nxt] == NULL) {
			_threadIdle = SDL_CreateThread(SpriteCacheIDLEThread,
				"SpriteCacheIDLEThrd", (void *)this);
		}
	}
}

void Character::SetFPS(int value)
{
	_current->SetFPS(value);
}

void Character::SetInvert(bool value)
{
	_invert = value;
}

void Character::GoIdle(int idx)
{
	printf("\nGo IDLE %d=%d", GetID(), _idleIdx);

	int index = _idleIdx;
	if (idx != -1) {
		index = idx;
	}

	if (index == -1)
		return;

	if (_cache[index] == NULL) {
		printf("\n	We Delay, We Force load %d=%d", GetID(), index);
		_force_load_idx = index;
		SDL_CreateThread(ForceLoadThread,
			"ForceLoadThread", (void *)this);
	}

	while (_cache[index] == NULL) {
		SDL_Delay(10);
	}

	_current = _cache[index]->sprite;
	_current->Reset();
	_currIdx = index;
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

	if (_invert)
		_current->OnDrawFlip(this->_x, this->_y, SDL_FLIP_HORIZONTAL);
	else
		_current->OnDraw(this->_x, this->_y);
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


void Character::Set(struct SpriteDefinition def[], 
	struct SpriteSplitInfo info[])
{
	_sprite_info = def;
	_split_info = info;
}

void Character::LoadSprite(int m)
{
	SpriteSheet* sprite = NULL;

	printf("\nLoad Character %d=%d", GetID(), m);
	
	int lock_mutex=SDL_LockMutex(_img_mutex);
	if (lock_mutex < 0) {
		printf("\n ERROR %s", SDL_GetError());
	}
	
	int index = 0;
	for (int i = 0; i < m;i++)
	{
		index += _split_info[i].count;
	}

	if (_split_info[m].grouped) {
		sprite = (SpriteExtenshion*)new SpriteExtenshion();
		for (int z = 0;z < _split_info[m].count;z++) {
			SpriteSheet* child = new SpriteSheet();

			child->LoadFromResource(_sprite_info[index].resid);
			child->Set(_sprite_info[index].frame_count,
				_sprite_info[index].fps, _sprite_info[index].loop);

			((SpriteExtenshion*)sprite)->AddSprite(child);
			sprite->SetLoop(_split_info[m].loop);

			index++;
		}
	}
	else {
		sprite = new SpriteSheet();

		sprite->LoadFromResource(_sprite_info[index].resid);
		sprite->Set(_sprite_info[index].frame_count,
			_sprite_info[index].fps, _sprite_info[index].loop);
	}


	//_current = sprite;
	_cache[m] = new SpriteCacheInfo();
	_cache[m]->sprite = sprite;
	_cache[m]->count = 0;
	_cache[m]->mutex = SDL_CreateMutex();

	DisplayCache();

	SDL_UnlockMutex(_img_mutex);
}

void Character::InitializeCache(int sprite_count)
{
	_cache_count = sprite_count;	
	_cache = NULL;
}

void Character::RefreshCache()
{
	_tail_sequence = 0;
	_tail_sequence_idle = 0;
	_sequence.clear();
	_sequence_idle.clear();
	_curr_cache_idx = -1;
	_curr_cacheIDLE_idx = -1;
	_curr_regular_Idx = -1;
}

void Character::CacheIndex(int index)
{
	_sequence.push_back(index);
}

void Character::CacheIndexIdle(int index)
{
	_sequence_idle.push_back(index);
}

void Character::GenerateCache()
{
	_current = NULL;
	_currIdx = _idleIdx = -1;
	if (_cache != NULL) {
		for (int i = 0; i < _cache_count;i++) {
			SAFE_DELETE(_cache[i]);
		}
		SAFE_DELETE_ARRAY(_cache);
	}

	_cache = new SpriteCacheInfo*[_cache_count];
	for (int i = 0; i < _cache_count;i++)
	{
		_cache[i] = NULL;
	}

	DoCache(0);

	int i = 0;
	LoadCacheIdle();

	if (_custom_event_handler) {
		_custom_event_handler->OnCustomEvent(this, ON_CACHE_LOADED);
	}
}

void Character::DoCache(int cached)
{
	bool loaded = false;

	while (!loaded) {
		if (_tail_sequence >= _sequence.size())
			return;

		int idx = _sequence.at(_tail_sequence++);
		if (idx == -1) continue;

		if (_cache[idx] == NULL)
		{
			printf("\n Cacheing Regular %d= %d", GetID(), idx);
			LoadSprite(idx);
			loaded = true;
		}
	}
}

void Character::PreLoadCache()
{	
	_threadPRELOAD = SDL_CreateThread(LoadCacheThread,
			"LoadCacheThread", (void *)this);
}

void Character::LoadCacheIdle()
{
	bool loaded = false;

	while (!loaded) {
		if (_tail_sequence_idle >= _sequence_idle.size())
			return;

		int idx = _sequence_idle.at(_tail_sequence_idle++);
		if (idx == -1) continue;

		if (idx >= 0 && _cache[idx] == NULL) {
			printf("\n Cacheing IDLE %d= %d", GetID(), idx);
			LoadSprite(idx);
			loaded = true;
		}

		_cache[idx]->idle = true;
	}

	return;
}

void Character::LoadNextCache()
{
	int count = 0;
	for (int i = 0; i < _cache_count;i++) {
		if (_cache[i] && !_cache[i]->idle)
			count++;
	}

	DoCache(count);
}

void Character::DisplayCache()
{
	int count = 0;
	int count_idle = 0;
	for (int i = 0;i < _cache_count;i++)
	{
		if (_cache[i])
			count++;
		if (_cache[i] && _cache[i]->idle)
			count_idle++;
	}

	printf("\n %d Cache summary = %d %d", GetID(), count, count_idle);
}

void Character::SetCustomEventHandler(ICustomEvent* handler)
{
	_custom_event_handler = handler;
}

void Character::ForceLoad()
{
	LoadSprite(_force_load_idx);
}

int LoadCacheThread(void* ptr)
{
	Character* c = (Character*)ptr;
	c->GenerateCache();
	return 0;
}

int SpriteCacheThread(void* ptr)
{
	Character* c = (Character*)ptr;
	c->LoadNextCache();
	return 0;
}

int SpriteCacheIDLEThread(void* ptr)
{
	Character* c = (Character*)ptr;
	c->LoadCacheIdle();
	return 0;
}

int ForceLoadThread(void* ptr)
{
	Character* c = (Character*)ptr;
	c->ForceLoad();
	return 0;
}
/**/
/**/
/**/
void Tom::Load()
{
	Set(g_tom_0, g_Tom_0_SplitInfo);
	InitializeCache(sizeof(g_Tom_0_SplitInfo) / sizeof(struct SpriteSplitInfo));
}

void Emma::Load()
{
	Set(g_Emma_0, g_Emma_0_SplitInfo);
	InitializeCache(sizeof(g_Emma_0_SplitInfo) / sizeof(struct SpriteSplitInfo));

	SetInvert(true);
}


void RedYoung::Load()
{
	Set(g_Red_0, g_Red_0_SplitInfo);
	InitializeCache(sizeof(g_Red_0_SplitInfo) / sizeof(struct SpriteSplitInfo));
	SetInvert(true);
}

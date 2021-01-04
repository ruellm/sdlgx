#include "GameData.h"

struct GameData g_gameData;

void GameData::SaveSprite(SpriteInfo* info)
{
	sprite_bank.push_back(info);
}

void GameData::CleanupSpriteBank()
{
	for (int i = 0; i < sprite_bank.size();i++) {
		SpriteInfo* info = sprite_bank.at(i);
		SAFE_DELETE(info);
	}

	sprite_bank.clear();
}

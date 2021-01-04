#pragma once
#include "Evidence.h"
#include "Character.h"
#include <vector>

struct GameData
{
	enum EvidenceType next_clue;
	std::vector<enum EvidenceType> clues;
	std::vector<enum EvidenceType> profiles;
	std::vector<SpriteInfo*> sprite_bank;

	GameData()
	{
		next_clue = EVIDENCE_TYPE_NONE;
	}

	~GameData()
	{
		CleanupSpriteBank();
	}

	void SaveSprite(SpriteInfo* info);
	void CleanupSpriteBank();
};

extern struct GameData g_gameData;
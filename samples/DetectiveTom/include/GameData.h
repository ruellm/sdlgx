#pragma once
#include "Evidence.h"
#include <vector>

struct GameData
{
	enum EvidenceType next_clue;
	std::vector<enum EvidenceType> clues;
	std::vector<enum EvidenceType> profiles;

	GameData()
	{
		next_clue = EVIDENCE_TYPE_NONE;
	}
};

extern struct GameData g_gameData;
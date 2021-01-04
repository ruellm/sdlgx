#pragma once

enum EvidenceType
{
	EVIDENCE_TYPE_NONE = -1,
	EVIDENCE_TYPE_RIDGEONY,
	EVIDENCE_TYPE_REDYOUNG,
	EVIDENCE_TYPE_EMMA_TEST_RESULT,
	EVIDENCE_TYPE_COFFEE,
	EVIDENCE_TYPE_RED_TEST_RESULT,
	EVIDENCE_TYPE_CALLING_CARD,
	EVIDENCE_TYPE_ORGANIZER,
	EVIDENCE_TYPE_RESEARCH_HCN,
	EVIDENCE_TYPE_TOM_TEST_RESULT,
	EVIDENCE_TYPE_DELIVERY_SLIP
};

enum EvidenceClass
{
	EVIDENCE_CLASS_PROFILE = 0,
	EVIDENCE_CLASS_CLUE
};

struct EvidenceInfo {
	enum EvidenceType type;
	char name[25];
	enum EvidenceClass eclass;
};

EvidenceInfo* GetEvidenceInfo(enum EvidenceType type);
int GetEvidenceResource(EvidenceType resID);
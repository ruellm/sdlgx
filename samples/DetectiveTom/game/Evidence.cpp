#include "Evidence.h"
#include "definitions.h"

struct EvidenceInfo g_evidence_def[] = {
	{ EVIDENCE_TYPE_RIDGEONY, "Ridge Ony", EVIDENCE_CLASS_PROFILE },
	{ EVIDENCE_TYPE_REDYOUNG, "Red Young", EVIDENCE_CLASS_PROFILE },
	{ EVIDENCE_TYPE_EMMA_TEST_RESULT, "Emma's Test Result", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_COFFEE, "Cup of Cofee", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_RED_TEST_RESULT, "Red's Test Result", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_CALLING_CARD, "Calling card", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_ORGANIZER, "Organizer Notes", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_RESEARCH_HCN, "HCN's Research articles", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_TOM_TEST_RESULT, "Tom's Test Result", EVIDENCE_CLASS_CLUE },
	{ EVIDENCE_TYPE_DELIVERY_SLIP, "Delivery Slip", EVIDENCE_CLASS_CLUE },
};


int g_evidence_resource[] = {
	RIDGEONY_IMG,
	REDYOUNG_IMG,
	EMMA_TEST_RESULT_IMG,
	CUP_OF_COFFEE_IMG,
	RED_TEST_RESULT_IMG,
	CALLING_CARD_IMG,
	ORGANIZER_IMG,
	HCN_RESEARCH_IMG,
	TOMS_TEST_RESULT_IMG,
	DELIVERY_SLIP_IMG
};

EvidenceInfo* GetEvidenceInfo(enum EvidenceType type)
{
	return &g_evidence_def[type];
}

int GetEvidenceResource(EvidenceType resID)
{
	return g_evidence_resource[resID];
}
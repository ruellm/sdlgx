// This file must contain the definitions, resources and state ids used in the game
// Created September 3, 2016
#pragma once

//
// State ID Defitinitions
//
#define LOADING_STATE		1
#define MAIN_MENU_STATE		2
#define GAME_STATE			3

//
// Game Screen/case states
//
#define PRELUDE_DIALOG_STATE	4

//
// Pop-up/Scene/sub-state ID definitions
#define PAUSE_MENU				0
#define CASE_FILE_SCREEN		1
#define LOG_SCREEN				2
#define EXIT_SCREEN				3
#define SETTINGS_SCREEN			4
#define EMMATALK_SCREEN			5
#define TOMTALK_SCREEN			6
#define APPRICOT_PEACHES_COMIC	7
#define REDTALK_SCREEN			8
//
// Resource Definitions
//
#define	MAIN_MENU_BG_IMG				0
#define BUTTON_870x127_IMG				1
#define BUTTON_870x127_HOVER_IMG		2
#define SETTINGS_BAR_DRAG_IMG			3
#define SETTINGS_BAR_IMG				4
#define	LEFT_BUTTON_IMG					5
#define RIGHT_BUTTON_IMG				6
#define LEFT_BUTTON_GLOW_IMG			7
#define RIGHT_BUTTON_GLOW_IMG			8
#define DROP_DOWN_GLOW_IMG				9
#define DROP_DOWN_TXTBOX_IMG			10
#define DOWN_BUTTON_IMG					11
#define DOWN_BUTTON_TOGLD_IMG			12
#define BACK_BUTTON_GLOW				13
#define BACK_BUTTON_IDLE				14
#define TEST_BG_IMG						15		//Test background image of game screen
#define PIN_BUTTON_IMG					16
#define PIN_GLOW_IMG					17
#define BLACK_LINES_OVERLAY_IMG			18
#define CASEFILE_BUTTON_IMG				19
#define SAVELOG_BUTTON_IMG				20
#define LOGS_BUTTON_IMG					21
#define SETTINGS_BUTTON_IMG				22
#define EXIT_BUTTON_IMG					23
#define	PAUSE_BUTTON_GLOW_IMG			24
#define CASE_FILE_BASE_IMG				25
#define BACK_BUTTON_IMG					26
#define BACK_BUTTON_GLOW_IMG			27
#define CHOICE_SCROLL_RIGHT_IMG			28
#define CHOICE_SCROLL_LEFT_IMG			29
#define CHOICE_GLOW_IMG					30
#define CASE_FILE_FG_IMG				31

#define SAMPLE_CASE_1_IMG				32
#define SAMPLE_CASE_2_IMG				33
#define CASE_ITEM_HIGLIGHT_IMG			34

#define CLUES_BUTTON_IMG				35
#define CLUES_BUTTON_GLOW_IMG			36
#define PROFILES_BUTTON_IMG				37
#define PROFILES_BUTTON_GLOW_IMG		38

#define SAMPLE_CLUES_1_IMG				39
#define SAMPLE_CLUES_2_IMG				40
#define SAMPLE_CLUES_3_IMG				41

#define CASE_FILE_BOX_IMG				42
#define CASE_FILE_SCROLLBAR_IMG			43
#define CASE_FILE_DRAG_IMG				44

#define LOGS_SCROLL_LINE_IMG			45
#define LOGS_WINDOW_IMG					46
#define LOGS_SCROLL_DRAG_IMG			47

#define EXIT_WINDOW_IMG					48
#define YES_NO_BUTTON_IMG				49
#define YES_NO_BUTTON_GLOW_IMG			50

#define SAMPLE_TOM_SPRITE_SHEET			51		//sample spritesheet
#define TEXT_BOX_IMG					52

#define FORWARD_BUTTON_IMG				53
#define FORWARD_HOVER_IMG				54

#define TUTORIAL_BG_IMG					55
#define IRIS_IMG						56

#define SAMPLE_EMMA_SPRITE_SHEET		57		//sample spritesheet
#define FINAL_BOX_MENU_IMG				58
#define FINAL_BOX_MENU_GLOW_IMG			59

//evidence images
#define RIDGEONY_IMG					60
#define REDYOUNG_IMG					61
#define EMMA_TEST_RESULT_IMG			62
#define	CUP_OF_COFFEE_IMG				63
#define RED_TEST_RESULT_IMG				64
#define CALLING_CARD_IMG				65
#define ORGANIZER_IMG					66
#define HCN_RESEARCH_IMG				67

#define SAMPLE_RED_SPRITE_SHEET			68

#define SHOW_BUTTON_GLOW_IMG			69
#define SHOW_BUTTON_IMG					70

#define APPRICOT_PEACHES_COMIC1			71
#define APPRICOT_PEACHES_COMIC2			72
#define APPRICOT_PEACHES_COMIC3			73
#define TOMS_TEST_RESULT_IMG			74
#define DELIVERY_SLIP_IMG				75

#define BATCH_0_SPRITES					76
#define BATCH_0_SPRITE_COUNT			69

//
// Fonts definitions
//
#define FONT_MYRIADPRO_REGULAR	-1
#define FONT_MANASPACE	0
//
// Game/Script Event definitions
//

//--Prologue/Prelude events
#define EVENT_IRIS_TRANSITION		0
#define EVENT_MUSIC_THINKING		1
#define EVENT_EMMA_TALK				2
#define EVENT_SHOW_CASEFILE			3
#define EVENT_OUT_ALL_CHARACTERS	4
#define EVENT_TOM_TALK				5
#define EVENT_TOM_TALK_COMPLETE		6
#define EVENT_TOM_OUT				7
#define EVENT_APPRPREC_COMIC		8
#define EVENT_FADEOUT				9
#define EVENT_RED_TALK				10
#define EVENT_RED_ADD				11

//
// Custom Event definitions
//
#define ICONBOX_EVT_ZOOM_DONE		100
#define ICONBOX_EVT_MOVE_DONE		101
#define ON_CORRECT_CLUE_EVNT		102
#define ON_CACHE_LOADED				103

//
// Button definitions
//
#define FWD_BUTTON		0
#define PIN_BUTTON		1

//Character definitions IDs
#define CHARACTER_TOM	0
#define CHARACTER_EMMA	1
#define CHARACTER_RED	2


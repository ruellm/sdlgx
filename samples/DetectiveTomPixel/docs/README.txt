Character IDs
	TOM		0
	EMMA	1
	RED		2

EVENT IDs
    EVENT_IRIS_TRANSITION		0
	EVENT_MUSIC_THINKING		1
	EVENT_EMMA_TALK				2
	EVENT_SHOW_CASEFILE			3
	EVENT_OUT_ALL_CHARACTERS	4
	EVENT_TOM_TALK				5
	EVENT_TOM_TALK_COMPLETE		6
	EVENT_TOM_OUT				7
	EVENT_APPRPREC_COMIC		8
	EVENT_FADEOUT				9
	EVENT_RED_TALK				10
	EVENT_RED_ADD				11

EVIDENCE type
	EVIDENCE_TYPE_RIDGEONY			0
	EVIDENCE_TYPE_REDYOUNG			1
	EVIDENCE_TYPE_EMMA_TEST_RESULT	2
	EVIDENCE_TYPE_COFFEE			3
	EVIDENCE_TYPE_RED_TEST_RESULT	4
	EVIDENCE_TYPE_CALLING_CARD		5
	EVIDENCE_TYPE_ORGANIZER			6
	EVIDENCE_TYPE_RESEARCH_HCN		7
	EVIDENCE_TYPE_TOM_TEST_RESULT	8
	EVIDENCE_TYPE_DELIVERY_SLIP		9

IMPORTANT Note on using script;

	1. Each line must end will always end with a new line
	2. Each command ends with a semi-colon ";" 
	3. There should be no spaces in the end of each command
	4. cut a dialog line with a backslash n character "\n", 
	   this will display the next succeeding string on next line
	5. ALL parameters should be separated by tab space after a command
	6. ALL scripts should end with the 'end_script;' command

General Information
	1. Prelude/tutorial scene
		to load sprite sheet, go to scripts/sprites_pre.txt
		parameters;
			filename(space)character_id(space)sprite_index(space)FPS(space)frame count(space)loop
			
			Detail:
				filename 		- the path of the image to load
				character_id 	- the ID of the character this sprite will be used, see above for definitions
				sprite_index	- the ID/order of sprite for a certain character, this is user defined. This should match on the script commands.
				FPS				- the speed of the sprite
				frame_count		- the number of frames
				loop			- set this to "1" if sprite sheets loops, "0" if not.
	
SCRIPT commands
	1. cmd_dialogline -dialog command
		Parameters: 
			id/sprite id/sprite fps/name/dialog time/dialog text
    
	2. cmd_pause - pause the conversation (no talk box)
		Parameters:
			seconds
	3. cmd_pause_talk - pause conversation(with talk box)
		Parameters:
			seconds
	4. cmd_shake - shake screen
		Parameters:
			intensity/time
	5. cmd_setcharidle_idx - setting the idle of character every after dialog	
		Parameters:
			characterid/sprite id/fps
	6. cmd_setsprite - change character sprite
		Parameters:
			characterid/sprite id/fps
	7. cmd_fade - fade a character or characters, direction 0 is fade out, direction 1 is fade intensity/time
		Parameters:
			direction/ids/ids...
	8. cmd_setcharcoord - set the location of characters, this is in pivot space, meaning, this center of the image and NOT the top left
		Parameters
			id/x/y
	9. cmd_wait - wait for user input for "next dialog"
   10. cmd_evidence - display a certain evidence, see above values for evidence type
	   Parameters
			evidence_type
   11. cmd_event - triggers an event in the game, see above event id definitions
		Parameters
			event_id
#pragma once

#include <string>
#include <vector>

typedef enum CommandType
{
	COMMAND_TYPE_NONE = 0,
	COMMAND_TYPE_CHARACTER,
	COMMAND_TYPE_WAIT,
	COMMAND_TYPE_DIALOGLINE,
	COMMAND_TYPE_PAUSE,
	COMMAND_TYPE_EVENT,
	COMMAND_TYPE_EVIDENCE,
	COMMAND_TYPE_SETCHAR_IDLE_IDX,
	COMMAND_TYPE_SETCHAR_SPRITE,
	COMMAND_TYPE_ENDSCRIPT,
	COMMAND_TYPE_PAUSE_TALK,
	COMMAND_TYPE_FADE,
	COMMAD_TYPE_SETCHAR_COORD,
	COMMAND_TYPE_SETCHAR_INVERT,
	COMMAND_TYPE_SETCHAR_ACTIVE,
	COMMAND_TYPE_SHAKE
}COMMAND_TYPE;

struct Commands
{
	COMMAND_TYPE type;
	Commands() {
		type = COMMAND_TYPE_NONE;
	};

	Commands(COMMAND_TYPE val){
		type = val;
	}
};

struct CommonCommand : Commands
{ 
	float value;
	CommonCommand(CommandType t, float v)
	{
		type = t;
		value = v;
	}
};

struct DialogLineCmd : Commands
{
	int id;
	int sprite_id;
	int sprite_fps;

	std::string name;
	std::string line;
	float display_timesec;

	DialogLineCmd()
	{
		type = COMMAND_TYPE_DIALOGLINE;
	}
};

struct CharacterSpriteCmd : Commands
{
	int character_id;
	int sprite_id;
	int fps;
	//bool blocking;

	CharacterSpriteCmd(COMMAND_TYPE t, int cid, int sid, int speed/*, bool b = false*/)
	{
		type = t;
		character_id = cid;
		sprite_id = sid;
		fps = speed;
		//blocking = b;
	}
};

struct CommandShake : Commands
{
	float time;
	int intensity;
	CommandShake(int i, float tm)
	{
		type = COMMAND_TYPE_SHAKE;
		time = tm;
		intensity = i;
	}
};

struct CommandFade : Commands
{
	int dir;
	//int count;
	std::vector<int> sprite_id;
	CommandFade(int d, /*int c,*/ std::vector<int>& ids) {
		type = COMMAND_TYPE_FADE;
		dir = d;
	//	count = c;
		for (int i = 0;i < ids.size(); i++) {
			int value = ids.at(i);
			sprite_id.push_back(value);
		}
	}
};

struct SetCharacterCoordCmd : Commands
{
	int id;
	int x;
	int y;

	SetCharacterCoordCmd(int i, int cx, int cy)
	{
		type = COMMAD_TYPE_SETCHAR_COORD;
		id = i;
		x = cx;
		y = cy;
	}
};

struct CommonCommandInt2 : Commands
{
	int val1;
	int val2;
	CommonCommandInt2(COMMAND_TYPE t, int v1, int v2)
	{
		type = t;
		val1 = v1;
		val2 = v2;
	}
};
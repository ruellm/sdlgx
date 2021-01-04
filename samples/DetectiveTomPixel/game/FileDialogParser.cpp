#include "FileDialogParser.h"
#include "Utility.h"

FileDialogParser::FileDialogParser()
{}

FileDialogParser::~FileDialogParser()
{}

void FileDialogParser::LoadFromFile(const char* szFname, std::vector<Commands*>& list)
{
	_file_idx = 0;

	FILE* fp = fopen(szFname, "r");

	printf("\n Parsing command file = %s", szFname);

	fseek(fp, 0L, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	_buffer = new char[sz];
	memset(_buffer, 0, sz);
	fread(_buffer, sz, 1, fp);
	fclose(fp);

	int cmd_count = 0;
	while (_file_idx < sz - 1) {
		std::string cmd;
		std::vector<std::string> params;

		ParseCommand(cmd);
		if (cmd == "end_script") {
			list.push_back(new Commands(COMMAND_TYPE_ENDSCRIPT));
			break;
		}
			
		printf("\n%d) Command = %s", cmd_count++, cmd.c_str());

		if (_buffer[_file_idx - 1] == ';') {
			//escape new line
			//escape new line
			while (_buffer[_file_idx] == '\n')
				_file_idx++;
		}
		else {
			ParseParams(params);
		}

		if (cmd == "cmd_dialogline") {
			list.push_back(BuildDialogCommand(params));
		}
		else if (cmd == "cmd_pause") {
			list.push_back(BuildCommonCommands(params, COMMAND_TYPE_PAUSE));
		}
		
		else if (cmd == "cmd_pause_talk") {
			list.push_back(BuildCommonCommands(params, COMMAND_TYPE_PAUSE_TALK));
		}
		else if (cmd == "cmd_shake") {
			list.push_back(BuildShakeCommand(params));
		}
		else if (cmd == "cmd_wait") {
			list.push_back(new Commands(COMMAND_TYPE_WAIT));
		}
		else if (cmd == "cmd_event") {
			list.push_back(BuildCommonCommands(params, COMMAND_TYPE_EVENT));
		}
		else if (cmd == "cmd_evidence") {
			list.push_back(BuildCommonCommands(params, COMMAND_TYPE_EVIDENCE));
		}
		else if (cmd == "cmd_setcharidle_idx") {
			list.push_back(BuildCharacterSprite(params, COMMAND_TYPE_SETCHAR_IDLE_IDX));
		}
		else if (cmd == "cmd_setsprite") {
			list.push_back(BuildCharacterSprite(params, COMMAND_TYPE_SETCHAR_SPRITE));
		}
		else if (cmd == "cmd_fade") {
			list.push_back(BuildFadeCommand(params));
		}
		else if (cmd == "cmd_setcharcoord") {
			list.push_back(BuildSetCharCoordCommand(params));			
		}
		else if (cmd == "cmd_setchar_invert") {
			list.push_back(BuildCommonCommands_Int2(params, COMMAND_TYPE_SETCHAR_INVERT));
		}
		else if (cmd == "cmd_setchar_active") {
			list.push_back(BuildCommonCommands_Int2(params, COMMAND_TYPE_SETCHAR_ACTIVE));
		}
	}

	if (_buffer)
		free(_buffer);
}

void FileDialogParser::ParseCommand(std::string& cmd) {
	char command[20] = { 0 };
	int cmd_index = 0;
	char c = 0;
	while (1) {
		c = _buffer[_file_idx++];
		if (c != 9 && c != ' ' && c != ';')
			command[cmd_index++] = c;
		else
			break;
	}
	command[cmd_index] = '\0';

	//advance index ahead
	while (_buffer[_file_idx] == 9) {
		_file_idx++;
	}

	std::string temp(command);
	cmd = temp;
}

void FileDialogParser::ParseParams(std::vector<std::string>& params) {
	//count in advance
	int index_temp = _file_idx;
	int size = 0;
	while (1) {
		char c = _buffer[index_temp++];
		if (c != ';')
			size++;
		else
			break;
	}

	char* buffer = new char[size + 1];
	int i = 0;
	while (i < size) {
		buffer[i++] = _buffer[_file_idx++];
	}

	buffer[i] = '\0';
	std::string temp(buffer);
	Utility_StringSpit(temp, '/', params);
	free(buffer);

	//advance index ahead
	while (_buffer[_file_idx] == ';' || _buffer[_file_idx] == '\n' || _buffer[_file_idx] == ' ') {
		_file_idx++;
	}
}

DialogLineCmd* FileDialogParser::BuildDialogCommand(const std::vector<std::string>& params)
{
	//id/sprite id/sprite fps/name/time/line
	DialogLineCmd* cmd = new DialogLineCmd();
	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	cmd->id = atoi(value);

	valuestr = params.at(1);
	value = valuestr.c_str();
	cmd->sprite_id = atoi(value);

	valuestr = params.at(2);
	value = valuestr.c_str();
	cmd->sprite_fps = atoi(value);

	cmd->name = params.at(3);
	cmd->line = params.at(5);
	
	int pos = 0;
	do {
		pos = cmd->line.find("\\n");
		if (pos != -1) {
			cmd->line.replace(pos, 3, "\n");
		}
	} while (pos != -1);
	
	valuestr = params.at(4);
	value = valuestr.c_str();
	cmd->display_timesec = atof(value);

	return cmd;
}

CommonCommand* FileDialogParser::BuildCommonCommands(const std::vector<std::string>& params, COMMAND_TYPE type)
{
	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	float v = atof(value);
	return new CommonCommand(type, v);
}

CharacterSpriteCmd* 
FileDialogParser::BuildCharacterSprite(const std::vector<std::string>& params, COMMAND_TYPE type)
{
	// characterid/sprite id/fps
	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	int cid = atoi(value);

	valuestr = params.at(1);
	value = valuestr.c_str();
	int spid = atoi(value);

	valuestr = params.at(2);
	value = valuestr.c_str();
	int fps = atoi(value);

/*	valuestr = params.at(0);
	value = valuestr.c_str();
	bool blocking = (bool)atoi(value);
*/
	return new CharacterSpriteCmd(type, cid, spid, fps);
}

CommandShake* FileDialogParser::BuildShakeCommand(const std::vector<std::string>& params)
{
	// intensity/time
	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	int intensity = atoi(value);

	valuestr = params.at(1);
	value = valuestr.c_str();
	float v = atof(value);

	return new CommandShake(intensity, v);
}

CommandFade* FileDialogParser::BuildFadeCommand(const std::vector<std::string>& params)
{
	// direction/ids/ids...
	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	int dir = atoi(value);

//	valuestr = params.at(1);
//	value = valuestr.c_str();
//	int count = atoi(value);

	std::vector<int> ids;
	for (int i = 1; i < params.size();i++) {
		valuestr = params.at(i);
		value = valuestr.c_str();
		int id = atoi(value);

		ids.push_back(id);
	}

	return new CommandFade(dir, ids);
}

SetCharacterCoordCmd* 
FileDialogParser::BuildSetCharCoordCommand(const std::vector<std::string>& params) {
	//id/x/y

	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	int id = atoi(value);

	valuestr = params.at(1);
	value = valuestr.c_str();
	int x = atoi(value);

	valuestr = params.at(2);
	value = valuestr.c_str();
	int y = atoi(value);


	return new SetCharacterCoordCmd(id, x, y);
}

CommonCommandInt2*  
FileDialogParser::BuildCommonCommands_Int2(const std::vector<std::string>& params, COMMAND_TYPE type)
{
	std::string valuestr = params.at(0);
	const char* value = valuestr.c_str();
	int v1 = atoi(value);

	valuestr = params.at(1);
	value = valuestr.c_str();
	int v2 = atoi(value);

	return new CommonCommandInt2(type,v1,v2);
}

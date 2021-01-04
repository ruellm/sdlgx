#pragma once
#include "Commands.h"
#include <vector>

class FileDialogParser
{
public:
	FileDialogParser();
	~FileDialogParser();
	void LoadFromFile(const char* szFname, std::vector<Commands*>& list);
private:
	int _file_idx;
	char* _buffer;

	void ParseCommand(std::string& cmd);
	void ParseParams(std::vector<std::string>& params);
	
	CommonCommand* BuildCommonCommands(const std::vector<std::string>& params, COMMAND_TYPE type);
	DialogLineCmd* BuildDialogCommand(const std::vector<std::string>& params);
	CharacterSpriteCmd* BuildCharacterSprite(const std::vector<std::string>& params, COMMAND_TYPE type);
	CommandShake* BuildShakeCommand(const std::vector<std::string>& params);
	CommandFade* BuildFadeCommand(const std::vector<std::string>& params);
	SetCharacterCoordCmd* BuildSetCharCoordCommand(const std::vector<std::string>& params);
	CommonCommandInt2*  BuildCommonCommands_Int2(const std::vector<std::string>& params, COMMAND_TYPE type);
};
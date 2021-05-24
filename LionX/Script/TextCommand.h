#ifndef LionX_LionX_Script_TextCommand_H
#define LionX_LionX_Script_TextCommand_H

#include "TextArges.h"

//===========================================================================================
//	文字指令。
//===========================================================================================

namespace LionX
{
	class CTextCommand
	{
	public:
		CTextCommand (const char *cmd, std::function<void(CTextArges&)> function);
		bool Exec (const std::vector<std::string>& cmds, CTextArges& args);
		~CTextCommand ();
	public:
		inline const std::vector<std::string>& GetKeys () const { return mKeys; }
	private:
		std::vector<std::string> mKeys;
		std::function<void(CTextArges&)> mFunction;
	};
};

#endif //	LionX_LionX_Script_TextCommand_H

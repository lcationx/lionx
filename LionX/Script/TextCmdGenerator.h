#ifndef LionX_LionX_Script_TextCmdGenerator_H
#define LionX_LionX_Script_TextCmdGenerator_H

#include "TextCommand.h"

//===========================================================================================
//	文字指令產生器。
//===========================================================================================

namespace LionX
{
	class CTextCmdGenerator
	{
	public:
		CTextCmdGenerator ();
		void Book (const char *cmd, std::function<void(CTextArges&)> function);
		bool Exec (const char *cmd, CTextArges& args);
		inline UInt16 GetSize () const { return mAmount; }
		void Release ();
		virtual ~CTextCmdGenerator ();
	private:
		UInt16 mAmount;
		std::map< std::string, std::vector<CTextCommand*> > mAllCommands;
	};

#define BookTextCommand(gen, cmd, function)		(gen).Book (cmd,function)
};

#endif //	LionX_LionX_Script_TextCmdGenerator_H

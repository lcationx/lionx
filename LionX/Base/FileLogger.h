#ifndef LionX_Base_FileLogger_H
#define LionX_Base_FileLogger_H

#include "File.h"
#include "Synchronization.h"
#include "Logger.h"

//===========================================================================================
//	檔案Logger。
//===========================================================================================

namespace LionX
{
	class CFileLogger : public ILogger
	{
	public:
		CFileLogger ();
		bool Init (const std::string& name);
		virtual bool AppendList (const char *format, va_list args);
		void Release ();
		virtual ~CFileLogger ();
	private:
		std::string mName;
		CFile mFile;
		Int32 mCount;
		Int32 mLogDay;
		std::mutex mMutex;
	};

};

#endif //	LionX_Base_FileLogger_H

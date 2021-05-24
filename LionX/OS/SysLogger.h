#ifndef LionX_LionX_OS_SysLogger_H
#define LionX_LionX_OS_SysLogger_H

#include "Base/File.h"
#include "Base/Synchronization.h"
#include "Base/Logger.h"

//===========================================================================================
//	系統紀錄。
//===========================================================================================

namespace LionX
{
	class CSysLogger : public ILogger
	{
	public:
		CSysLogger ();
		virtual bool AppendList (const char *format, va_list args);
		virtual ~CSysLogger ();
	private:
		CFile mFile;
		Int32 mCount;
		std::mutex mSpinLock;
	};
};

#endif //	LionX_LionX_OS_SysLogger_H

#ifndef LionX_LionX_Base_Logger_H
#define LionX_LionX_Base_Logger_H

//===========================================================================================
//	記錄。
//===========================================================================================

namespace LionX
{
	class ILogger
	{
	public:
		inline ILogger () { }
		bool Append (const char *format, ...) 
		{
			va_list args;
			va_start (args, format);
			bool result = AppendList (format, args);
			va_end (args);
			return result;
		}
		virtual bool AppendList (const char *format, va_list args) { return false; }
		
		virtual ~ILogger () { }
	};

	typedef TSingleton<ILogger> BaseLogger;
#define LP_BaseLogger BaseLogger::Ins()
};

#endif //	LionX_LionX_Base_Logger_H

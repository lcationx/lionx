#ifndef LionX_LionX_Base_Assert_H
#define LionX_LionX_Base_Assert_H

//===========================================================================================
//	斷言。
//===========================================================================================

namespace LionX
{
	class Assert
	{
	public:
		typedef void (*Function)(const char *, const char *, int, const char *, ...);
	public:
		static void SetFunction (Function fun) { mFunction = fun; }
	private:
		static void DefaultFunction (const char *exp, const char *file_name, int file_line, const char *format, ...);
	public:
		static Function mFunction;
	};
};

#if SD_ASSERT == 2
#define LP_ASSERT(exp, format, ...)		{ if ( !(exp) ) { Assert::mFunction (#exp, __FILE__, __LINE__, format, ##__VA_ARGS__); std::abort (); } }
#elif SD_ASSERT == 1
#define LP_ASSERT(exp, format, ...)		{ if ( !(exp) ) { Assert::mFunction (#exp, __FILE__, __LINE__, format, ##__VA_ARGS__); } }
#else
#define LP_ASSERT(exp, format, ...)
#endif

#endif //	LionX_LionX_Base_Assert_H

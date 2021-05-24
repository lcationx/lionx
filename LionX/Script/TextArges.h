#ifndef LionX_LionX_Script_TextArges_H
#define LionX_LionX_Script_TextArges_H

#include "Base/LionX.h"

//===========================================================================================
//	文字指令參數。
//===========================================================================================

namespace LionX
{
	class CTextArges
	{
	public:
		CTextArges ();
		void Push (const char *param);
		void Reset ();
		inline UInt32 GetColumns () const { return (UInt32)mParams.size (); }
		inline void Skip (UInt32 size) { mReadIndex += size; }
		//	資料流。
		CTextArges& operator >> (char& dest);
		CTextArges& operator >> (unsigned char& dest);
		CTextArges& operator >> (Int16& dest);
		CTextArges& operator >> (UInt16& dest);
		CTextArges& operator >> (Int32& dest);
		CTextArges& operator >> (UInt32& dest);
		CTextArges& operator >> (Int64& dest);
		CTextArges& operator >> (UInt64& dest);
		CTextArges& operator >> (float& dest);
		CTextArges& operator >> (double& dest);
		//	特殊資料流。
		CTextArges& operator >> (std::string& dest);
		CTextArges& operator >> (char* dest);
		inline bool IsOver () const { return (mReadIndex >= (UInt32)mParams.size ()); }
		virtual ~CTextArges ();
	private:
		UInt32 mReadIndex;
		std::vector<std::string> mParams;
	};
};

#endif //	LionX_LionX_Script_TextArges_H

#ifndef LionX_LionX_Base_Float16_H
#define LionX_LionX_Base_Float16_H

#include "Math.h"

//===========================================================================================
//	半精準浮數點(16bit)。
//===========================================================================================

namespace LionX
{
	class CFloat16
	{
	public:
		//	單精準轉半精準。
		static UInt16 F32To16 (float src);
		//	半精準轉單精準。
		static float F16To32 (UInt16 src);
		//	單精準轉半精準 (陣列)。
		static void F32To16 (const float src [], CFloat16 dest [],const size_t size);
		//	半精準轉單精準 (陣列)。
		static void F16To32 (const CFloat16 src [], float dest [], const size_t size);
	public:
		//	建構式。
		inline CFloat16 () : mValue (0) { }
		inline CFloat16 (const float v) { mValue = F32To16 (v); }
		//	半精準轉單精準。
		inline operator const float () { return F16To32 (mValue); }
		//	比較方式。
		inline bool operator == (const CFloat16& cmp) const { return mValue == cmp.mValue; }
		inline bool operator != (const CFloat16& cmp) const { return mValue != cmp.mValue; }
	private:
		//	保存的記憶體值。
		UInt16 mValue;
	};
};

#endif //	LionX_LionX_Base_Float16_H

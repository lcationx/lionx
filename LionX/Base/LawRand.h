#ifndef LionX_LionX_Base_LawRand_H
#define LionX_LionX_Base_LawRand_H

#include "Math.h"

//===========================================================================================
//	規律的亂數產生器(會依指定參數將指定範圍內的數值亂數產生一輪)。
//===========================================================================================

namespace LionX
{
	class CLawRand
	{
	public:
		inline CLawRand ()
			: mPrime (0), mMaxValue (0), mSkipValue (0), mValue (0)
		{ }
		void Reset (UInt32 max_value);
		UInt32 GetRand ();
		~CLawRand () { }
	private:
		UInt32 mPrime;
		UInt32 mMaxValue, mSkipValue;
		UInt32 mValue;
	};
};

#endif //	LionX_LionX_Base_LawRand_H

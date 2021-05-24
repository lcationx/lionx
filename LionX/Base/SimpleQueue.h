#ifndef LionX_LionX_Base_SimpleQueue_H
#define LionX_LionX_Base_SimpleQueue_H

#include "LionX.h"

//===========================================================================================
//	簡單的隊列範本。
//===========================================================================================

namespace LionX
{
	template<typename T>
	class SimpleQueue
	{
	public:
		inline SimpleQueue ()
			: mCount (0), mHead (0), mRear (0)
		{ }
		inline void PushBack (T *obj)
		{
			if (mHead == 0) {
				mHead = mRear = obj;
			} else {
				mRear->mLink = obj;
				mRear = obj;
			}
			++ mCount;
		}
		inline void PushFront (T *obj)
		{
			if (mHead == 0) {
				mHead = mRear = obj;
			} else {
				obj->mLink = mHead;
				mHead = obj;
			}
			++ mCount;
		}
		inline T* Top () const
		{
			return mHead;
		}
		inline T* Pop ()
		{
			if (mHead == 0)
				return 0;
			T *obj = mHead;
			mHead = mHead->mLink;
			obj->mLink = 0;
			-- mCount;
			return obj;
		}
		inline UInt32 GetSize () const 
		{
			return mCount;
		}
		inline ~SimpleQueue () { }
	private:
		UInt32 mCount;
		T *mHead, *mRear;
	};
};

#endif //	LionX_LionX_Base_SimpleQueue_H

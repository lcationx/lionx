#ifndef LionX_LionX_Base_ArrayContainer_H
#define LionX_LionX_Base_ArrayContainer_H

#include "LionX.h"

//===========================================================================================
//	陣列容器 (線程安全)。
//===========================================================================================

namespace LionX
{
	template<typename T>
	class CArrayContainer
	{
	public:
		static const Int32 PaddingSize = 7;
	public:
		struct SData
		{
		public:
			volatile Int64 mLink;
			T mData;
		public:
			inline SData ()
				: mLink (0)
			{ }
		};
	public:
		CArrayContainer (UInt32 capacity)
			: mArray (nullptr), mCapacity (capacity), mSize (0), mLeastPoint (0), mTailPoint (0)
		{
			mArray = LP_NEW (SData [mCapacity + 1]);
		}
		inline UInt32 Alloc ()
		{
			Int64 idx = 0, old = mLeastPoint;
			while ((idx = Atomic::LockedCompareExchange (&mLeastPoint, mArray [old & 0xFFFFFFFFFFLL].mLink, old)) != old) {
				sched_yield ();
				old = mLeastPoint;
			}
			idx &= 0xFFFFFFFFFFLL;
			if (idx == 0)
				idx = Atomic::LockedIncrement (&mTailPoint);
			LP_ASSERT (idx <= mCapacity, "FAIL:ArrayQueue put data but idx[%lld] is over[%lld].", idx, mCapacity);
			Atomic::LockedIncrement (&mSize);
			return ((UInt32)idx);
		}
		inline T& Get (UInt32 idx)
		{
			return mArray[idx].mData;
		}
		inline void Dealloc (UInt32 idx)
		{
			mArray [idx].mLink = mLeastPoint;
			Int64 old = mArray [idx].mLink;
			while (Atomic::LockedCompareExchange (&mLeastPoint, (Int64)(idx + (old & 0xFFFFFF0000000000LL) + 0x10000000000LL), old) != old) {
				sched_yield ();
				mArray [idx].mLink = mLeastPoint;
				old = mArray [idx].mLink;
			}
			Atomic::LockedDecrement (&mSize);
		}
		~CArrayContainer ()
		{
			LP_SAFE_DELETE_ARRAY (mArray);
		}
	public:
		inline T& operator [] (UInt32 idx) { return mArray[idx].mData; }
		inline const T& operator [] (UInt32 idx) const { return mArray[idx].mData; }
		inline UInt64 GetSize () const { return mSize; }
	private:
		SData* mArray;
		Int64 mCapacity;
		UInt64 mPadding0 [PaddingSize];
		volatile Int64 mSize;
		UInt64 mPadding1 [PaddingSize];
		volatile Int64 mLeastPoint;
		UInt64 mPadding2 [PaddingSize];
		volatile Int64 mTailPoint;
		UInt64 mPadding3 [PaddingSize];
	};
};

#endif //	LionX_LionX_Base_ArrayContainer_H

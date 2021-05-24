#ifndef LionX_LionX_Base_CircularQueue_H
#define LionX_LionX_Base_CircularQueue_H

#include "LionX.h"

//===========================================================================================
//	環形隊列 (線程安全)。
//===========================================================================================

namespace LionX
{
	template<typename T>
	class CSimpleCircularQueue
	{
	public:
		static const Int32 PaddingSize = 7;
	public:
		struct SData
		{
		public:
			volatile Int32 mLock;
			T mData;
		public:
			inline SData ()
				: mLock (0)
			{ }
		};
	public:
		CSimpleCircularQueue (UInt64 capacity)
			: mArray (nullptr), mCapacity (capacity), mSize (0), mReadPoint (0), mTailPoint (0)
		{
			mArray = LP_NEW (SData [mCapacity]);
		}
		inline void Push (T& data)
		{
			Int64 value = (Atomic::LockedIncrement (&mTailPoint) - 1);
			Int64 idx = value % mCapacity;
			while (Atomic::LockedCompareExchange (&mArray [idx].mLock, 1, 0) != 0) {
				sched_yield ();
			}
			mArray [idx].mData = data;
			Atomic::LockedExchange (&mArray [idx].mLock, (Int32)((value / mCapacity) << 4) + 2);
			Atomic::LockedIncrement (&mSize);
		}
		inline bool Pop (T& data)
		{
			Int64 status = 0;
			Int64 value = mReadPoint;
			Int64 idx = value % mCapacity;
			Int32 key = (Int32)((value / mCapacity) << 4) + 2;
			while ((status = Atomic::LockedCompareExchange (&mArray [idx].mLock, 3, key)) == 3 || ((key & 0xFFFFFFF0) != (status & 0xFFFFFFF0) && status != 0)) {
				sched_yield ();
				value = mReadPoint;
				idx = value % mCapacity;
				key = (Int32)((value / mCapacity) << 4) + 2;
			}
			if (status != key)
				return false;
			Atomic::LockedIncrement (&mReadPoint);
			data = mArray [idx].mData;
			Atomic::LockedExchange (&mArray [idx].mLock, 0);
			Atomic::LockedDecrement (&mSize);
			return true;
		}
		inline void Clear ()
		{
			mSize = 0;
			mReadPoint = 0;
			mTailPoint = 0;
		}
		virtual ~CSimpleCircularQueue ()
		{
			LP_SAFE_DELETE_ARRAY (mArray);
		}
	public:
		inline UInt64 GetSize () const { return mSize; }
	private:
		SData *mArray;
		Int64 mCapacity;
		UInt64 mPadding0 [PaddingSize];
		volatile Int64 mSize;
		UInt64 mPadding1 [PaddingSize];
		volatile Int64 mReadPoint;
		UInt64 mPadding2 [PaddingSize];
		volatile Int64 mTailPoint;
		UInt64 mPadding3 [PaddingSize];
	};

	template<typename T>
	class CCircularQueue
	{
	public:
		static const Int32 PaddingSize = 7;
	public:
		//	無數據。
		static const UInt32 InvalidID = -1;
	public:
		struct SData
		{
		public:
			volatile Int32 mLock;
			T mData;
		public:
			inline SData ()
				: mLock (0)
			{ }
		};
	public:
		CCircularQueue (UInt64 capacity)
			: mArray (nullptr), mCapacity (capacity), mSize (0), mReadPoint (0), mTailPoint (0)
		{
			mArray = LP_NEW (SData [mCapacity]);
		}
		//	寫入。
		inline UInt32 Prepare ()
		{
			Int64 value = (Atomic::LockedIncrement (&mTailPoint) - 1);
			Int64 idx = value % mCapacity;
			Int64 mask = ((value / mCapacity) << 4) + 1;
			while (Atomic::LockedCompareExchange (&mArray [idx].mLock, mask, 0) != 0) {
				sched_yield ();
			}
			return (UInt32)(idx);
		}
		inline void Commit (UInt32 idx)
		{
			Atomic::LockedExchange (&mArray [idx].mLock, (Int32)((mArray [idx].mLock & 0xFFFFFFF0) + 2));
			Atomic::LockedIncrement (&mSize);
		}
		//	讀取。
		inline UInt32 Checkout ()
		{
			Int64 status = 0;
			Int64 value = mReadPoint;
			Int64 idx = value % mCapacity;
			Int32 key = (Int32)((value / mCapacity) << 4) + 2;
			while ((status = Atomic::LockedCompareExchange (&mArray [idx].mLock, 3, key)) == 3 || ((key & 0xFFFFFFF0) != (status & 0xFFFFFFF0) && status != 0)) {
				sched_yield ();
				value = mReadPoint;
				idx = value % mCapacity;
				key = (Int32)((value / mCapacity) << 4) + 2;
			}
			if (status != key)
				return InvalidID;
			Atomic::LockedIncrement (&mReadPoint);
			return idx;
		}
		inline void Finish (UInt32 idx)
		{
			Atomic::LockedExchange (&mArray [idx].mLock, 0);
			Atomic::LockedDecrement (&mSize);	
		}
		inline void Clear ()
		{
			mSize = 0;
			mReadPoint = 0;
			mTailPoint = 0;
		}
		virtual ~CCircularQueue ()
		{
			LP_SAFE_DELETE_ARRAY (mArray);
		}
	public:
		inline T& operator [] (UInt32 idx) { return mArray[idx].mData; }
		inline const T& operator [] (UInt32 idx) const { return mArray[idx].mData; }
		inline UInt64 GetSize () const { return mSize; }
	private:
		SData *mArray;
		Int64 mCapacity;
		UInt64 mPadding0 [PaddingSize];
		volatile Int64 mSize;
		UInt64 mPadding1 [PaddingSize];
		volatile Int64 mReadPoint;
		UInt64 mPadding2 [PaddingSize];
		volatile Int64 mTailPoint;
		UInt64 mPadding3 [PaddingSize];
	};
};

#endif //	LionX_LionX_Base_CircularQueue_H

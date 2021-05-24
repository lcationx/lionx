#ifndef LionX_LionX_Base_IDAllocator_H
#define LionX_LionX_Base_IDAllocator_H

#include "Synchronization.h"

//===========================================================================================
//	ID分配器。
//===========================================================================================

namespace LionX
{
	class CIDAllocator
	{
	public:
		inline CIDAllocator ()
			: mMin (0), mMax (0), mIndex (0) { }
		inline CIDAllocator (UInt32 min, UInt32 max) { Init (min, max); }
		void Init (UInt32 min, UInt32 max);
		void SetIndex (UInt32 idx);
		UInt32 Alloc ();
		void PreAlloc (UInt32 id);
		void PreAlloc (UInt32 front, UInt32 rear);
		void Dealloc (UInt32 id);
		void Done ();
		virtual ~CIDAllocator () { Done (); }
	public:
		inline UInt32 GetMin () const { return mMin; }
		inline UInt32 GetMax () const { return mMax; }
	private:
		UInt32 mMin, mMax;
		UInt32 mIndex;
		std::list<UInt32> mCacheIDs;
		std::set<UInt32> mPreAllocIDs;
		CSpinLock mSpinLock;
	};

	class CIDAlloc64
	{
	public:
		inline CIDAlloc64 ()
			: mMin (0), mMax (0), mIndex (0) { }
		inline CIDAlloc64 (UInt64 min, UInt64 max) { Init (min, max); }
		void Init (UInt64 min, UInt64 max);
		void SetIndex (UInt64 idx);
		UInt64 Alloc ();
		void PreAlloc (UInt64 id);
		void PreAlloc (UInt64 front, UInt64 rear);
		void Dealloc (UInt64 id);
		void Done ();
		virtual ~CIDAlloc64 () { Done (); }
	public:
		inline UInt64 GetMin () const { return mMin; }
		inline UInt64 GetMax () const { return mMax; }
	private:
		UInt64 mMin, mMax;
		UInt64 mIndex;
		std::list<UInt64> mCacheIDs;
		std::set<UInt64> mPreAllocIDs;
		CSpinLock mSpinLock;
	};
};

#endif //	LionX_LionX_Base_IDAllocator_H

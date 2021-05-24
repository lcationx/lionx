#ifndef LionX_LionX_Base_Allocator_H
#define LionX_LionX_Base_Allocator_H

#include "Synchronization.h"

//===========================================================================================
//	分配器。
//===========================================================================================

namespace LionX
{
	template <typename T>
	class Allocator
	{
	public:
		inline Allocator (UInt32 limit = 0)
			: mHead (0), mAmount (0), mLimit (limit)
		{ }
		void Init (UInt32 limit)
		{
			mLimit = limit;
		}
		T* Alloc ()
		{
			T *t = 0;
			mLock.lock ();
			if (mHead != 0) {
				t = mHead;
				mHead = mHead->mLink;
				t->mLink = 0;
				-- mAmount;
			}
			else {
				t = LP_NEW (T);
			}
			mLock.unlock ();
			return t;
		}
		void Return (T *t)
		{
			mLock.lock ();
			if (mAmount >= mLimit) {
				LP_DELETE (t);
			} else {
				++ mAmount;
				t->mLink = mHead;
				mHead = t;
			}
			mLock.unlock ();

		}
		void Release ()
		{
			mLock.lock ();
			while (mHead != 0) {
				T *t = mHead;
				mHead = mHead->mLink;
				LP_DELETE (t);
			}
			mAmount = mLimit = 0;
			mLock.unlock ();
		}
		inline UInt32 GetAmount () const { return mAmount; }
		virtual ~Allocator () { Release (); }
	private:
		CSpinLock mLock;
		T *mHead;
		UInt32 mAmount, mLimit;
	};
};

#endif //	LionX_LionX_Base_Allocator_H

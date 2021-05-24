#ifndef LionX_LionX_Base_Synchronization_H
#define LionX_LionX_Base_Synchronization_H

#include "LionX.h"

//===========================================================================================
//	同步相關物件。
//===========================================================================================

namespace LionX
{
	class CSpinLock
	{
	public:
		inline CSpinLock () 
			: mValue (0) 
		{ }

		CSpinLock (const CSpinLock&) = delete;
		CSpinLock& operator=(const CSpinLock&) = delete;

		inline void lock ()
		{
			while (Atomic::LockedCompareExchange (&mValue, 1, 0)) {
				sched_yield ();
			}; 
		}
		inline bool islock ()
		{ 
			return (Atomic::LockedCompareExchange (&mValue, 1, 1) == 1);
		}
		inline bool try_lock ()
		{ 
			return (Atomic::LockedCompareExchange (&mValue, 1, 0) == 0);
		}
		inline void unlock ()
		{ 
			Atomic::LockedExchange (&mValue, 0); 
		}
		inline ~CSpinLock ()
		{
		}
	private:
		volatile Int32 mValue;
	};
#if 0
	class CShareLock
	{
	public:
		enum EMode
		{
			eWriteFirst = 0,
			eReadFirst,
		};
	public:
		static const Int32 DefaultValue = 100000;
	public:
		inline CShareLock (EMode mode = eWriteFirst) : mValue (DefaultValue) { }
		void lock_read ();
		void lock ();
		bool try_lock ();
		void unlock_read ();
		void unlock ();
		inline ~CShareLock () { }
	private:
		volatile Int32 mValue;
	};
#else
	class CShareLock
	{
	public:
		enum EMode
		{
			eWriteFirst = 0,
			eReadFirst,
		};
	public:
		inline CShareLock (EMode mode = eWriteFirst)
			: mMode (mode), mLockCount (0), mWriteWaitCount (0)
		{ }
		CShareLock (const CShareLock&) = delete;
		CShareLock& operator=(const CShareLock&) = delete;
		void lock_read ();
		void unlock_read ();
		void lock ();
		bool try_lock ();
		void unlock ();
		inline ~CShareLock () { }
	public:
		EMode mMode;
		std::atomic_long mLockCount;
		std::atomic_long mWriteWaitCount;
	};
#endif
	class CCondition
	{
	public:
		inline CCondition ()
			: mWaits (0)
		{ }
		CCondition (const CCondition&) = delete;
		CCondition& operator=(const CCondition&) = delete;
		bool wait (UInt32 msec = 0xFFFFFFFF);
		void notify_one ();
		void notify_all ();
		inline long get_waits () const { return mWaits; }
		inline ~CCondition () { }
	private:
		std::mutex mMutex;
		volatile Int32 mWaits;
		std::condition_variable mCondition;
	};


	class CCoroutineLock
	{
	public:
		inline CCoroutineLock ()
			: mLock (false)
		{ }
		bool try_lock (double time);
		void lock ();
		//	wait_check_method返回true表示不繼續等待，GetLock失敗返回。
		bool try_lock (std::function<bool ()> wait_check_method);
		void unlock ();
		inline bool islock () const { return mLock; }
		virtual ~CCoroutineLock () { }
	private:
		volatile bool mLock;
	};

};

#endif //	LionX_LionX_Base_Synchronization_H

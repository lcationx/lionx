#ifndef LionX_LionX_Base_AtomicOP_H
#define LionX_LionX_Base_AtomicOP_H

//===========================================================================================
//	原子操作。
//===========================================================================================

namespace LionX
{
	class Atomic
	{
	public:
		//	32 bit 原子 ++ *addend。
		static inline Int32 LockedIncrement (volatile Int32 *addend) { return __sync_add_and_fetch (addend, 1); }
		//	32 bit 原子 -- *addend。
		static inline Int32 LockedDecrement (volatile Int32 *addend) { return __sync_sub_and_fetch (addend, 1); }
		//	32 bit 原子 *addend += value; return old *addend value。
		static inline Int32 LockedExchangeAdd (volatile Int32 *addend, Int32 value) { return __sync_fetch_and_add (addend, value); }
		//	32 bit 原子 *addend = value; return old *addend value。
		static inline Int32 LockedExchange (volatile Int32 *addend, Int32 value) { return __sync_lock_test_and_set (addend, value); }
		//	32 bit 原子 if *addend == comperand then *addend = exchange; return old *addend value。
		static inline Int32 LockedCompareExchange (volatile Int32 *addend, Int32 exchange, Int32 comperand) { return __sync_val_compare_and_swap (addend, comperand, exchange); }
	public:
		//	指針 原子 *addend = value; return old *addend value。
		static inline PVoid LockedExchange (volatile PVoid *addend, PVoid value) { return __sync_lock_test_and_set (addend, value); }
		//	指針 原子 if *addend == comperand then *addend = exchange; return old *addend value。
		static inline PVoid LockedCompareExchange (volatile PVoid *addend, PVoid exchange, PVoid comperand) { return __sync_val_compare_and_swap (addend, comperand, exchange); }
	public:
		//	64 bit 原子 ++ *addend。
		static inline Int64 LockedIncrement (volatile Int64 *addend) { return __sync_add_and_fetch (addend, (Int64)1); }
		//	64 bit 原子 -- *addend。
		static inline Int64 LockedDecrement (volatile Int64 *addend) { return __sync_add_and_fetch (addend, (Int64)-1); }
		//	64 bit 原子 *addend += value; return old *addend value。
		static inline Int64 LockedExchangeAdd (volatile Int64 *addend, Int64 value) { return __sync_fetch_and_add (addend, value); }
		//	64 bit 原子 *addend = value; return old *addend value。
		static inline Int64 LockedExchange (volatile Int64 *addend, Int64 value) { return __sync_lock_test_and_set (addend, value); }
		//	64 bit 原子 if *addend == comperand then *addend = exchange; return old *addend value。
		static inline Int64 LockedCompareExchange (volatile Int64 *addend, Int64 exchange, Int64 comperand) { return __sync_val_compare_and_swap (addend, comperand, exchange); }
	};
};

#endif //	LionX_LionX_Base_AtomicOP_H

#ifndef LionX_LionX_Base_Coroutine_H
#define LionX_LionX_Base_Coroutine_H

#include "LionX.h"

//===========================================================================================
//	協同執行器 (使用時請注意 請盡量在第一個Yield呼叫前配置好所有要使用的區域變數)。
//===========================================================================================

namespace LionX
{
	class CCoroutine;

	class ICoroutineBase
	{
	public:
		enum EStatus
		{
			ePrepare = 0,
			eRunning,
			eFinish,
		};
	public:
		inline ICoroutineBase ()
			: mCoroutine (nullptr), mCoroStack (nullptr), mCoroStatus (ePrepare)
		{ }
		virtual void Execute () = 0;
		virtual ~ICoroutineBase ();
	public:
		inline bool IsFinish () const { return (mCoroStatus == eFinish); }
	protected:
		CCoroutine *mCoroutine;
		char *mCoroStack;
		EStatus mCoroStatus;
		ucontext_t mCoroContext;
	private:
		friend class CCoroutine;
	};

	class CCoroutine
	{
	public:
		static const UInt32 StackAllocSize = 67108864;
		static const UInt32 PreStackSize = 12288;
		static const UInt32 LeastStackSize = 262144;
	public:
		CCoroutine (UInt32 stack_alloc_size = StackAllocSize, UInt32 pre_stack_size = PreStackSize, UInt32 least_stack_size = LeastStackSize);
		void StartCoroutine (ICoroutineBase *corbase);
		bool Yield (ICoroutineBase *corbase, std::function<bool()> fncheck);
		~CCoroutine ();
	private:
		void ResetStack ();
		char* CutStack (UInt32 stack_size);
		void FreeStack (char *stack);
	private:
		static void Proc (UInt32 low, UInt32 hi);
	private:
		ucontext_t mContext;
		UInt32 mStackAllocSize;
		UInt32 mPreStackSize;
		UInt32 mLeastStackSize;
		char *mStack;
		char *mFocuStacksPos;
		UInt32 mStoreStackSize;
	private:
		friend class ICoroutineBase;
	};
};

#endif //	LionX_LionX_Base_Coroutine_H

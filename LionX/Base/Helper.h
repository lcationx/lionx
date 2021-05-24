#ifndef LionX_LionX_Base_Helper_H
#define LionX_LionX_Base_Helper_H

#include "Allocator.h"
#include "Synchronization.h"
#include "CircularQueue.h"

//===========================================================================================
//	多線程小幫手。
//===========================================================================================

namespace LionX
{
	class CHelper
	{
	private:
		static const Int32 MaxCircularQueueSize = 32767;
	private:
		struct SAction
		{
		public:
			volatile bool mFinish;
			std::function<void ()> mExecFunction;
			SAction* mLink;
		public:
			inline SAction ()
				: mFinish (false), mLink (nullptr)
			{ }
			inline void Reset () {
				mFinish = false;
				mExecFunction = nullptr;
			}
		};

	public:
		inline CHelper ()
			: mSwitch (false), mActions (MaxCircularQueueSize)
		{ }
		Int32 Startup (UInt32 threads = 4);
		void Go (std::function<void ()> exec_function);
		void Push (std::function<void ()> exec_function);
		UInt32 NumActions ();
		void Shutdown ();
		inline ~CHelper () { Shutdown (); }
	public:
		inline bool IsStarted () const { return mSwitch; }
	private:
		void ThreadProc ();
	private:
		volatile bool mSwitch;
		std::vector<std::thread> mWorkThreads;
		CCondition mCondition;
		Allocator<SAction> mActionAllocator;
		CSimpleCircularQueue<SAction*> mActions;
	};

	typedef TSingleton<CHelper> Helper;
#define LP_Helper Helper::Ins()	
};

#endif //	LionX_LionX_Base_Helper_H

#ifndef LionX_LionX_Network_Network_H
#define LionX_LionX_Network_Network_H

#include "Socket.h"
#include "Base/CircularQueue.h"

//===========================================================================================
//	網路系統。
//===========================================================================================

namespace LionX
{
	class CNetwork
	{
	public:
		static const Int32 EPollTimeOut = 2000;
		static const Int32 MaxOneComplete = 256;
		static const Int32 MaxCircularQueueSize = 32767;
	public:
		inline CNetwork ()
			: mSwitch (false), mEPollFD (0), mEvents (MaxCircularQueueSize), mDestroyEvents (MaxCircularQueueSize)
		{ }
		Int32 Startup (UInt32 threads = 1);
		Int32 AttachSocket (CSocket *sock);
		Int32 ResetNetwork (CSocket *sock);
		void Shutdown ();
		inline ~CNetwork () { Shutdown (); }
	public:
		inline bool IsStarted () const { return mEPollFD != 0; }
	private:
		void DetachSocket (CSocket *sock);
		void ThreadProc ();
	private:
		volatile bool mSwitch;
		Int32 mEPollFD;
		std::vector<std::thread> mWorkThreads;
		CSpinLock mWaitLock;
		CCondition mCondition;
		CSimpleCircularQueue<struct epoll_event> mEvents, mDestroyEvents;
	private:
		friend class CSocket;
	};

	typedef TSingleton<CNetwork> Network;
#define LP_Network Network::Ins()	
};

#endif //	LionX_LionX_Network_Network_H

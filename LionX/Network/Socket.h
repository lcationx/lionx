#ifndef LionX_LionX_Network_Socket_H
#define LionX_LionX_Network_Socket_H

#include "NetPack.h"
#include "Base/SimpleQueue.h"

//===========================================================================================
//	網路套接頭。
//===========================================================================================

namespace LionX
{
	class CSocket
	{
	private:
		static const Int32 MaxPackCache = 4096;
	private:
		static Int32 SockCount;
		static Allocator<CNetPack> NetPackAllocator;
	protected:
		static CCondition Condition;
	private:
		static void AddSockCount ();
		static void DecSockCount ();
	protected:
		static CNetPack* AllocPack ();
		static void FreePack (CNetPack *pack);
	public:
		enum ESignalMode
		{
			NORMAL,
			SIGNAL,
			CLOSED,
		};
	public:
		//	無效的描述符號。
		static const Int32 InvalidID = -1;
	public:
		CSocket (Int32 fd = InvalidID);
		Int32 DisableKeepalive ();
		Int32 EnableKeepalive (Int32 keep_idle = 120, Int32 keep_interval = 5, Int32 keep_count = 3);
		Int32 SetSynRetryCount (Int32 count);
		Int32 SetLinger (Int32 active, Int32 _linger);
		Int32 SetTcpNoDelay (bool enagle);
		UInt16 GetChecksum (void *buf, Int32 size);
		inline Int32 GetHandle () { return mFD; }
		void Signal (bool immediate = true);
		inline ESignalMode GetSignal () const { return static_cast<ESignalMode>(mSignal); }
		void Release ();
		//	增加記數將使socket不會被刪除。
		inline void IncRef () { 
			Atomic::LockedIncrement (&mRef); 
		}
		//	減少記數有可能會導致socket被刪除，請與IncRef成對使用。
		inline void DecRef () { Atomic::LockedDecrement (&mRef); }
		//	取得記數。
		inline Int32 GetRef () const { return mRef; }
		virtual ~CSocket ();
	public:
		virtual bool OnRead (Int32& err_code) = 0;
		virtual bool OnSend (Int32& err_code) = 0;
		virtual void OnClosed (Int32 ret_code) = 0;
	protected:
		Int32 mFD;
		volatile Int32 mSignal;
	private:
		UInt32 mDelNetFrame;
		Int32 mRef;
		CSpinLock mSpinLock;
		CSocket *mLink;
	private:
		friend class CNetwork;
		friend class SimpleQueue<CSocket>;
		friend class CNetPack;
	};
};

#endif //	LionX_LionX_Network_Socket_H

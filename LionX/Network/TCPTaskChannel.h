#ifndef LionX_LionX_Network_TCPTaskChannel_H
#define LionX_LionX_Network_TCPTaskChannel_H

#include "NetChannel.h"

//===========================================================================================
//	TCP客戶端-Task。
//===========================================================================================

namespace LionX
{
	enum ENetTranStatus
	{
		NET_TRANS_SYS_FAIL = 0,	//	錯誤無法發送。
		NET_TRANS_SENT,			//	已發送。
		NET_TRANS_SUCCESS,		//	成功返回。
	};

	class CTCPTaskChannel : public CNetChannel
	{
	public:
		inline CTCPTaskChannel ()
			: mRemotePort (0), mRemoteIPNetID (0), mRemoteAddress (""), mSent (0), mRead (0), mReadPack (0), mSendPack (0)
			, mSentAmount (0), mSendListFront (0), mSendListRear (0), mDisableResult (false), mSignalInGenTaskFail (true), mWaitCommand (nullptr)
		{ }
		Int32 Connect (Int32 fd);
		Int32 Connect (const std::string& to_address, UInt16 to_port);
		virtual ENetTranStatus SendCommand (INetCommand *net_command, bool diconnect = true);
		virtual ENetTranStatus SendResultCommand (INetCommand *net_command, double exp_date, bool diconnect = true);
		virtual ENetTranStatus SendWaitCommand (INetCommand *net_command, double exp_date, bool diconnect = true);
		virtual bool OnRead (Int32& err_code);
		virtual bool OnSend (Int32& err_code);
		virtual void OnClosed (Int32 ret_code);
		inline const UInt32 GetRemoteIPNetID () const { return mRemoteIPNetID; }
		inline const std::string& GetRemoteAddress () const { return mRemoteAddress; }
		inline UInt16 GetRemotePort () const { return mRemotePort; }
		virtual ~CTCPTaskChannel ();
	public:
		//	因協程技術限制，處理連線中斷請改繼承此函式 (併回主線程執行，且會釋放指針記數)。
		virtual void OnDisconnected (Int32 ret_code) { }
	protected:
		bool AddSendPack (CNetPack *pack);
		bool FillSendPack ();
		ITaskCommand* MakeTaskCommand (UInt16 sn, CInBinStream& in);
	public:
		inline bool GetSignalInGenTaskFail () const { return mSignalInGenTaskFail; }
		inline void SetSignalInGenTaskFail (bool singnal) { mSignalInGenTaskFail = singnal; }
		inline bool GetDisableResult () const { return mDisableResult; }
		inline void SetDisableResult (bool disable) { mDisableResult = disable; }
	protected:
		UInt16 mRemotePort;
		UInt32 mRemoteIPNetID;
		std::string mRemoteAddress;
		Int32 mSent, mRead;
		CNetPack *mReadPack, *mSendPack;
		UInt32 mSentAmount;
		CNetPack *mSendListFront, *mSendListRear;
		CSpinLock mSendSpinLock;
		bool mDisableResult;
		bool mSignalInGenTaskFail;
		INetCommand *mWaitCommand;
	};
};

#endif //	LionX_LionX_Network_TCPTaskChannel_H

#ifndef LionX_LionX_Network_UDPTaskChannel_H
#define LionX_LionX_Network_UDPTaskChannel_H

#include "NetChannel.h"

//===========================================================================================
//	UDP客戶端-Task。
//===========================================================================================

namespace LionX
{
	class CUDPTaskChannel : public CNetChannel
	{
	public:
		inline CUDPTaskChannel ()
			: mSignalInGenTaskFail (false), mPort (0), mIPNetID (0), mAddress (""), mReadPack (0), mSendPack (0), mSentAmount (0), mSendListFront (0), mSendListRear (0)
		{ }
		Int32 Startup (const std::string& address, UInt16 port);
		Int32 SendCommand (const std::string& to_address, UInt16 to_port, INetCommand *net_command, bool diconnect = true);
		Int32 SendCommand (UInt32 to_ip_net_id, UInt16 to_port, INetCommand *net_command, bool diconnect = true);
		virtual bool OnRead (Int32& err_code);
		virtual bool OnSend (Int32& err_code);
		inline UInt16 GetLocalPort () const { return mPort; }
		inline UInt32 GetLocalIPNetID () const { return mIPNetID; }
		inline const std::string& GetLocalAddress () const { return mAddress; }
		virtual ~CUDPTaskChannel ();
	public:
		inline bool GetSignalInGenTaskFail () const { return mSignalInGenTaskFail; }
		inline void SetSignalInGenTaskFail (bool singnal) { mSignalInGenTaskFail = singnal; }
	protected:
		bool AddSendPack (CNetPack *pack);
		bool FillSendPack ();
	protected:
		bool mSignalInGenTaskFail;
		UInt16 mPort;
		UInt32 mIPNetID;
		std::string mAddress;
		CNetPack *mReadPack, *mSendPack;
		UInt32 mSentAmount;
		CNetPack *mSendListFront, *mSendListRear;
		CSpinLock mSendSpinLock;
	};
};

#endif //	LionX_LionX_Network_UDPTaskChannel_H

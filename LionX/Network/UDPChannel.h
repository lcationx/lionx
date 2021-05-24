#ifndef LionX_LionX_Network_UDPChannel_H
#define LionX_LionX_Network_UDPChannel_H

#include "Socket.h"

//===========================================================================================
//	UDP客戶端。
//===========================================================================================

namespace LionX
{
	class CUDPChannel : public CSocket
	{
	public:
		inline CUDPChannel ()
			: mPort (0), mIPNetID (0), mAddress (""), mReadPack (0), mSendPack (0), mSentAmount (0), mSendListFront (0), mSendListRear (0)
		{ }
		Int32 Startup (const std::string& address, UInt16 port);
		Int32 SendData (const std::string& to_address, UInt16 to_port, const char *data, UInt16 data_size, bool diconnect = true);
		Int32 SendData (UInt32 to_ip_net_id, UInt16 to_port, const char *data, UInt16 data_size, bool diconnect = true);
		virtual bool OnRead (Int32& err_code);
		virtual bool OnSend (Int32& err_code);
		inline UInt16 GetLocalPort () const { return mPort; }
		inline UInt32 GetLocalIPNetID () const { return mIPNetID; }
		inline const std::string& GetLocalAddress () const { return mAddress; }
		virtual ~CUDPChannel ();
	public:
		virtual void OnReadCompleted (UInt32 remote_ip_net_id, UInt16 remote_port, char *data, UInt16 data_size) { }
		virtual void OnSendCompleted (UInt32 to_ip_net_id, UInt16 to_port, char *data, UInt16 data_size) { }
	protected:
		bool AddSendPack (CNetPack *pack);
		bool FillSendPack ();
	protected:
		UInt16 mPort;
		UInt32 mIPNetID;
		std::string mAddress;
		CNetPack *mReadPack, *mSendPack;
		UInt32 mSentAmount;
		CNetPack *mSendListFront, *mSendListRear;
		CSpinLock mSendSpinLock;
	};
};

#endif //	LionX_LionX_Network_UDPChannel_H

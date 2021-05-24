#ifndef LionX_LionX_Network_TCPChannel_H
#define LionX_LionX_Network_TCPChannel_H

#include "Socket.h"

//===========================================================================================
//	TCP客戶端。
//===========================================================================================

namespace LionX
{
	class CTCPChannel : public CSocket
	{
	public:
		inline CTCPChannel ()
			: mRemotePort (0), mRemoteIPNetID (0), mRemoteAddress (""), mSent (0), mReadPack (0), mSendPack (0), mSentAmount (0), mSendListFront (0), mSendListRear (0)
		{ }
		Int32 Connect (Int32 fd);
		Int32 Connect (const std::string& to_address, UInt16 to_port);
		Int32 PreSendData (const char *data, UInt16 data_size);
		Int32 SendData (const char *data, UInt16 data_size, bool diconnect = true);
		virtual bool OnRead (Int32& err_code);
		virtual bool OnSend (Int32& err_code);
		inline const UInt32 GetRemoteIPNetID () const { return mRemoteIPNetID; }
		inline const std::string& GetRemoteAddress () const { return mRemoteAddress; }
		inline UInt16 GetRemotePort () const { return mRemotePort; }
		virtual ~CTCPChannel ();
	public:
		virtual void OnReadCompleted (char *data, UInt16 data_size) { }
		virtual void OnSendCompleted (char *data, UInt16 data_size) { }
	protected:
		bool AddSendPack (CNetPack *pack);
		bool FillSendPack ();
	protected:
		UInt16 mRemotePort;
		UInt32 mRemoteIPNetID;
		std::string mRemoteAddress;
		Int32 mSent;
		CNetPack *mReadPack, *mSendPack;
		UInt32 mSentAmount;
		CNetPack *mSendListFront, *mSendListRear;
		CSpinLock mSendSpinLock;
	};
};

#endif //	LionX_LionX_Network_TCPChannel_H

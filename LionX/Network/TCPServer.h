#ifndef LionX_LionX_Network_TCPServer_H
#define LionX_LionX_Network_TCPServer_H

#include "Socket.h"

//===========================================================================================
//	TCP伺服端。
//===========================================================================================

namespace LionX
{
	class CTCPChannel;

	class CTCPServer : public CSocket
	{
	public:
		inline CTCPServer ()
			: mAcceptCount (0), mPort (0), mIPNetID (0), mAddress ("")
		{ }
		Int32 Startup (const std::string& address, UInt16 port, UInt16 backlog = 2048);
		virtual bool OnRead (Int32& err_code);
		virtual bool OnSend (Int32& err_code);
		inline UInt16 GetLocalPort () const { return mPort; }
		inline UInt32 GetLocalIPNetID () const { return mIPNetID; }
		inline const std::string& GetLocalAddress () const { return mAddress; }
		inline UInt32 GetAcceptCount () const { return mAcceptCount; }
		virtual ~CTCPServer ();
	public:
		virtual CSocket* AllocSocket (Int32 fd, UInt32 remote_address, UInt16 remote_port) = 0;
	private:
		UInt32 mAcceptCount;
		UInt16 mPort;
		UInt32 mIPNetID;
		std::string mAddress;
	};


};

#endif //	LionX_LionX_Network_TCPServer_H

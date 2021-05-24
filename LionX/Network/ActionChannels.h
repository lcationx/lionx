#ifndef LionX_LionX_Network_ActionChannels_H
#define LionX_LionX_Network_ActionChannels_H

#include "TCPChannel.h"
#include "TCPTaskChannel.h"
#include "TCPServer.h"
#include "UDPChannel.h"

//===========================================================================================
//	使用C++ 0x11 特性重新封裝。
//===========================================================================================

namespace LionX
{
	class CActionTCPChannel : public CTCPChannel
	{
	public:
		inline CActionTCPChannel ()
			: mFnOnReadCompleted (nullptr), mFnOnSendCompleted (nullptr), mFnOnClosed (nullptr)
		{ }
		inline CActionTCPChannel (std::function<void(Int32)> on_close_callback)
			: mFnOnReadCompleted (nullptr), mFnOnSendCompleted (nullptr), mFnOnClosed (on_close_callback)
		{ }
		inline CActionTCPChannel (std::function<void(char*, UInt16)> on_read_callback, std::function<void(Int32)> on_close_callback)
			: mFnOnReadCompleted (on_read_callback), mFnOnSendCompleted (nullptr), mFnOnClosed (on_close_callback)
		{ }
		inline CActionTCPChannel (std::function<void(char*, UInt16)> on_read_callback, std::function<void(char*, UInt16)> on_send_callback, std::function<void(Int32)> on_close_callback)
			: mFnOnReadCompleted (on_read_callback), mFnOnSendCompleted (on_send_callback), mFnOnClosed (on_close_callback)
		{ }
		virtual void OnReadCompleted (char *data, UInt16 data_size);
		virtual void OnSendCompleted (char *data, UInt16 data_size);
		virtual void OnClosed (Int32 ret_code);
		virtual ~CActionTCPChannel () { }
	public:
		inline void SetOnReadCompleted (std::function<void(char*, UInt16)> callback) { mFnOnReadCompleted = callback; }
		inline void SetOnSendCompleted (std::function<void(char*, UInt16)> callback) { mFnOnSendCompleted = callback; }
		inline void SetOnClosed (std::function<void(Int32)> callback) { mFnOnClosed = callback; }
	private:
		std::function<void(char*, UInt16)> mFnOnReadCompleted;
		std::function<void(char*, UInt16)> mFnOnSendCompleted;
		std::function<void(Int32)> mFnOnClosed;
	};

	class CActionTCPTaskChannel : public CTCPTaskChannel
	{
	public:
		inline CActionTCPTaskChannel ()
			: mFnEncryption (nullptr), mFnDecryption (nullptr), mFnGenerateTaskCommand (nullptr), mFnOnClosed (nullptr)
		{ }
		inline CActionTCPTaskChannel (std::function<void(Int32)> on_close_callback)
			: mFnEncryption (nullptr), mFnDecryption (nullptr), mFnGenerateTaskCommand (nullptr), mFnOnClosed (on_close_callback)
		{ }
		inline CActionTCPTaskChannel (std::function<ITaskCommand*(UInt16, CInBinStream&)>  gen_task_callback, std::function<void(Int32)> on_close_callback)
			: mFnEncryption (nullptr), mFnDecryption (nullptr), mFnGenerateTaskCommand (gen_task_callback), mFnOnClosed (on_close_callback)
		{ }
		virtual void Encryption (char *data, UInt16 len);
		virtual void Decryption (char *data, UInt16 len);
		virtual ITaskCommand* GenerateTaskCommand (UInt16 sn, CInBinStream& in);
		virtual void OnClosed (Int32 ret_code);
		virtual ~CActionTCPTaskChannel () { }
	public:
		inline void SetEncryption (std::function<void(char*, UInt16)> callback) { mFnEncryption = callback; }
		inline void SetDecryption (std::function<void(char*, UInt16)> callback) { mFnDecryption = callback; }
		inline void SetGenerateTaskCommand (std::function<ITaskCommand*(UInt16, CInBinStream&)> callback) { mFnGenerateTaskCommand = callback; }
		inline void SetOnClosed (std::function<void(Int32)> callback) { mFnOnClosed = callback; }
	private:
		std::function<void(char*, UInt16)> mFnEncryption;
		std::function<void(char*, UInt16)> mFnDecryption;
		std::function<ITaskCommand*(UInt16, CInBinStream&)> mFnGenerateTaskCommand;
		std::function<void(Int32)> mFnOnClosed;
	};

	class CActionTCPServer : public CTCPServer
	{
	public:
		inline CActionTCPServer ()
			: mFnAllocSocket (nullptr), mFnOnClosed (nullptr)
		{ }
		inline CActionTCPServer (std::function<void(Int32)> on_close_callback)
			: mFnAllocSocket (nullptr), mFnOnClosed (on_close_callback)
		{ }
		inline CActionTCPServer (std::function<CSocket*(Int32, UInt32, UInt16)> alloc_sock_callback, std::function<void(Int32)> on_close_callback)
			: mFnAllocSocket (alloc_sock_callback), mFnOnClosed (on_close_callback)
		{ }
		virtual CSocket* AllocSocket (Int32 fd, UInt32 remote_address, UInt16 remote_port);
		virtual void OnClosed (Int32 ret_code);
		virtual ~CActionTCPServer () { }
	public:
		inline void SetAllocSocket (std::function<CSocket*(Int32, UInt32, UInt16)> callback) { mFnAllocSocket = callback; }
		inline void SetOnClosed (std::function<void(Int32)> callback) { mFnOnClosed = callback; }
	private:
		std::function<CSocket*(Int32, UInt32, UInt16)> mFnAllocSocket;
		std::function<void(Int32)> mFnOnClosed;
	};

	class CActionUDPChannel : public CUDPChannel
	{
	public:
		inline CActionUDPChannel ()
			: mFnOnReadCompleted (nullptr), mFnOnSendCompleted (nullptr), mFnOnClosed (nullptr)
		{ }
		inline CActionUDPChannel (std::function<void(Int32)> on_close_callback)
			: mFnOnReadCompleted (nullptr), mFnOnSendCompleted (nullptr), mFnOnClosed (on_close_callback)
		{ }
		inline CActionUDPChannel (std::function<void(UInt32, UInt16, char*, UInt16)> on_read_callback, std::function<void(Int32)> on_close_callback)
			: mFnOnReadCompleted (on_read_callback), mFnOnSendCompleted (nullptr), mFnOnClosed (on_close_callback)
		{ }
		inline CActionUDPChannel (std::function<void(UInt32, UInt16, char*, UInt16)> on_read_callback, std::function<void(UInt32, UInt16, char*, UInt16)> on_send_callback, std::function<void(Int32)> on_close_callback)
			: mFnOnReadCompleted (on_read_callback), mFnOnSendCompleted (on_send_callback), mFnOnClosed (on_close_callback)
		{ }
		virtual void OnReadCompleted (UInt32 remote_ip_net_id, UInt16 remote_port, char *data, UInt16 data_size);
		virtual void OnSendCompleted (UInt32 to_ip_net_id, UInt16 to_port, char *data, UInt16 data_size);
		virtual void OnClosed (Int32 ret_code);
		virtual ~CActionUDPChannel () { }
	public:
		inline void SetOnReadCompleted (std::function<void(UInt32, UInt16, char*, UInt16)> callback) { mFnOnReadCompleted = callback; }
		inline void SetOnSendCompleted (std::function<void(UInt32, UInt16, char*, UInt16)> callback) { mFnOnSendCompleted = callback; }
		inline void SetOnClosed (std::function<void(Int32)> callback) { mFnOnClosed = callback; }
	private:
		std::function<void(UInt32, UInt16, char*, UInt16)> mFnOnReadCompleted;
		std::function<void(UInt32, UInt16, char*, UInt16)> mFnOnSendCompleted;
		std::function<void(Int32)> mFnOnClosed;
	};
};

#endif //	LionX_LionX_Network_ActionChannels_H

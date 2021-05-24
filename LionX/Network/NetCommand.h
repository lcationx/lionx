#ifndef LionX_LionX_Network_NetCommand_H
#define LionX_LionX_Network_NetCommand_H

#include "NetPack.h"
#include "Base/StreamData.h"
#include "Base/Task.h"
#include "NetStream.h"

//===========================================================================================
//	Net Command Task。
//===========================================================================================

namespace LionX
{
	class CNetChannel;

	class INetCommand : public IRTTI, public IStreamData
	{
	public:
		enum ECommandType
		{
			UNKNOWN,
			TASK,
			COMMAND,
		};
	public:
		DECLARE_RTTI (UNKNOWN);
	public:
		inline INetCommand ()
			: mNetChannel (nullptr), mGUID ((UInt64)this), mTimeout (false), mIsComeback (false), mPack (nullptr)
		{ }
		void SetPack (CNetPack* pack);
		inline CNetPack* GetPack () { return mPack; }
		template<typename T>
		inline T* GetChannel () { return (T*) (mNetChannel); }
		inline CNetChannel* GetBaseChannel () { return mNetChannel; }
		void SetChannel (CNetChannel *channel);
		bool CheckTimeout ();
		virtual ~INetCommand ();
	public:
		virtual UInt16 Serial () = 0;
		virtual void SetReply () { }
		virtual INetCommand* Clone () { return nullptr; }
	public:
		inline bool IsComeback () const { return mIsComeback; }
		inline bool IsTimeout () const { return mTimeout; }
		inline double GetExpiration () const { return mExpiration; }
	public:
		UInt32 mRemoteNetID;
		UInt16 mRemotePort;
	protected:
		CNetChannel *mNetChannel;
		//	唯一識別碼 (物件指針)。
		UInt64 mGUID;
		//	有效時間。
		double mExpiration;
		//	是否超時。
		bool mTimeout;
		//	是否已回傳。
		volatile bool mIsComeback;
	protected:
		CNetPack *mPack;
	private:
		friend class CTCPTaskChannel;
	};

	template<typename TNetStream>
	class BaseNetCommand : public INetCommand, public TNetStream
	{
	public:
		static UInt16 SN;
		static inline UInt16 _Serial () { return SN; }
	public:
		DECLARE_RTTI (COMMAND);
	public:
		inline BaseNetCommand ()
		{ }
		virtual UInt16 Serial ()
		{ 
			return SN; 
		}
		virtual INetCommand* Clone ()
		{
			typedef BaseNetCommand<TNetStream> CMD;
			CMD *cmd = LP_NEW (CMD);
			*cmd = *((CMD*)this);
			return cmd;
		}
		virtual void Serialize (COutBinStream& out)
		{
			TNetStream::Out (out);		
		}
		virtual void Deserialize (CInBinStream& in)
		{
			TNetStream::In (in);
		}
		virtual ~BaseNetCommand () { }
	};
	template <typename TNetStream> UInt16 BaseNetCommand<TNetStream>::SN = 0;


	template<typename TNetStream>
	class NetCommand : public INetCommand, public TNetStream
	{
	public:
		static UInt16 SN;
		static inline UInt16 _Serial () { return SN; }
	public:
		DECLARE_RTTI (COMMAND);
	public:
		inline NetCommand ()
		{ }
		virtual UInt16 Serial ()
		{ 
			return SN; 
		}
		virtual void SetReply ()
		{
			TNetStream::mIsReply = true;
		}
		virtual INetCommand* Clone ()
		{
			typedef NetCommand<TNetStream> CMD;
			CMD *cmd = LP_NEW (CMD);
			*((TNetStream *)(cmd)) = *((TNetStream*)this);
			return cmd;
		}
		virtual void Serialize (COutBinStream& out)
		{
			out << mExpiration;
			out << mGUID;
			TNetStream::Out (out);		
		}
		virtual void Deserialize (CInBinStream& in)
		{
			TNetStream::In (in);
		}
		virtual ~NetCommand () { }
	};
	template <typename TNetStream> UInt16 NetCommand<TNetStream>::SN = 0;

	class ITaskCommand : public INetCommand, public ITask
	{
	public:
		static const UInt16 InvalidSN = 0xFFFF;
	public:
		inline ITaskCommand ()
		{ }
		virtual bool IsValid () { return true; }
		virtual void Execute () { }
		virtual bool IsContinue () { return false; }
		virtual ~ITaskCommand () { }
	public:
		void Reply ();
	};

	template<typename TNetStream>
	class BaseTaskCommand : public ITaskCommand, public TNetStream
	{
	public:
		static UInt16 SN;
		static inline UInt16 _Serial () { return SN; }
	public:
		DECLARE_RTTI (TASK);
	public:
		inline BaseTaskCommand (std::function<void(BaseTaskCommand<TNetStream>*)>& fnexec)
			: mFnExecute (fnexec)
		{ }
		virtual UInt16 Serial ()
		{
			return SN;
		}
		virtual INetCommand* Clone ()
		{
			typedef BaseNetCommand<TNetStream> CMD;
			CMD *cmd = LP_NEW (CMD);
			*((TNetStream *)(cmd)) = *((TNetStream*)this);
			return cmd;
		}
		virtual void Serialize (COutBinStream& out)
		{
			TNetStream::Out (out);
		}
		virtual void Deserialize (CInBinStream& in)
		{
			TNetStream::In (in);
		}
		virtual void Execute ()
		{
			mFnExecute (this);
		}
		virtual ~BaseTaskCommand () { }
	public:
		std::function<void(BaseTaskCommand<TNetStream>*)>& mFnExecute;
	};
	template <typename TNetStream> UInt16 BaseTaskCommand<TNetStream>::SN = 0;

	template<typename TNetStream>
	class TaskCommand : public ITaskCommand, public TNetStream
	{
	public:
		static UInt16 SN;
		static inline UInt16 _Serial () { return SN; }
	public:
		DECLARE_RTTI (TASK);
	public:
		inline TaskCommand (std::function<void(TaskCommand<TNetStream>*)>& fnexec)
			: mFnExecute (fnexec)
		{ }
		virtual UInt16 Serial ()
		{
			return InvalidSN;
		}
		virtual void SetReply ()
		{
			TNetStream::mIsReply = true;
		}
		virtual INetCommand* Clone ()
		{
			typedef NetCommand<TNetStream> CMD;
			CMD *cmd = LP_NEW (CMD);
			*((TNetStream *)(cmd)) = *((TNetStream*)this);
			return cmd;
		}
		virtual void Serialize (COutBinStream& out)
		{
			out << mExpiration;
			out << mGUID;
			TNetStream::Out (out);
		}
		virtual void Deserialize (CInBinStream& in)
		{
			in >> mExpiration;
			in >> mGUID;
			TNetStream::In (in);
		}
		virtual void Execute ()
		{
			if (CheckTimeout () == false)
				mFnExecute (this);
		}
		virtual ~TaskCommand () { }
	public:
		std::function<void(TaskCommand<TNetStream>*)>& mFnExecute;
	};
	template <typename TNetStream> UInt16 TaskCommand<TNetStream>::SN = 0;
};

#endif //	LionX_LionX_Network_NetCommand_H

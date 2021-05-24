#ifndef LionX_LionX_Cluster_ClusterChannel_H
#define LionX_LionX_Cluster_ClusterChannel_H

#include "Network/TCPTaskChannel.h"
#include "Network/NetTaskGenerator.h"

//===========================================================================================
//	叢集 - TCP通訊頻道。
//===========================================================================================

namespace LionX
{
	class CClusterChannel : public CTCPTaskChannel
	{
	public:
		static const UInt16 InvalidID = -1;
	public:
		CClusterChannel (CNetTaskGenerator& taskgenerator, std::function<void(CClusterChannel*)> fn_on_closed);
		CClusterChannel (UInt16 group_id, UInt16 sid, CNetTaskGenerator& taskgenerator, std::function<void(CClusterChannel*)> fn_on_closed);
		CClusterChannel (UInt16 sid, CNetTaskGenerator& taskgenerator, std::function<void(CClusterChannel*)> fn_on_closed);
		virtual ITaskCommand* GenerateTaskCommand (UInt16 sn, CInBinStream& in);
		virtual void OnDisconnected (Int32 ret_code);
		virtual ~CClusterChannel ();
	public:
		inline UInt16 GetGroupID () const { return mGroupID; }
		inline UInt16 GetSID () const { return mSID; }
		inline UInt32 GetPriority () const { return mPriority; }
		inline const std::string& GetServiceIP () const { return mServiceIP; }
		inline UInt16 GetServicePort () const { return mServicePort; }
	public:
		union {
			struct {
				UInt32 mExData1, mExData2;
			};
			UInt64 mExData;
		};
	private:
		CNetTaskGenerator& mTaskGenerator;
		UInt16 mGroupID;
		UInt16 mSID;
		UInt32 mPriority;
		std::string mServiceIP;
		UInt16 mServicePort;
		double mTimestamp;
		UInt16 mUseCount;
		std::function<void(CClusterChannel*)> mFnOnClosed;
	private:
		friend class CClusterSupervisor;
		friend class CClusterWorker;
	};
};

#endif //	LionX_LionX_Cluster_ClusterChannel_H

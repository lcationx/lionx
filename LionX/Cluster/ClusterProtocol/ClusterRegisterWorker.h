#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterRegisterWorker_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterRegisterWorker_H

#include "Network/NetStream.h"

//===========================================================================================
//	叢集 - 登錄ClusterWorker資訊。
//===========================================================================================

namespace LionX
{
	class CClusterRegisterWorker : public CNetStream
	{
	public:
		CClusterRegisterWorker ()
			: mGroupID (-1), mSID (-1), mServicePort (0), mPriority (0), mResult (0), mBigenTime (0.0)
		{ }
		virtual void Out (COutBinStream& out)
		{
			if ( IsOriginate () )
			{
				out << mGroupID;
				out << mSID;
				out << mServiceIP;
				out << mServicePort;
				out << mPriority;
			} 
			else 
			{
				out << mResult;
				out << mBigenTime;
			}
		}
		virtual void In (CInBinStream& in)
		{
			if ( IsOriginate () )
			{
				in >> mGroupID;
				in >> mSID;
				in >> mServiceIP;
				in >> mServicePort;
				in >> mPriority;
			} 
			else 
			{
				in >> mResult;
				in >> mBigenTime;
			}
		}
		virtual ~CClusterRegisterWorker () { }
	public:
		//	in data。
		UInt16 mGroupID;
		UInt16 mSID;
		std::string mServiceIP;
		UInt16 mServicePort;
		UInt32 mPriority;
		//	out data。
		UInt16 mResult;
		double mBigenTime;		
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterRegisterWorker_H

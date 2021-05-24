#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterAskWorker_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterAskWorker_H

#include "Network/NetStream.h"

//===========================================================================================
//	叢集 - 請求ClusterWorker資訊。
//===========================================================================================

namespace LionX
{
	class CClusterAskWorker : public CNetStream
	{
	public:
		CClusterAskWorker ()
			: mGroupID (-1), mSID (-1), mResult (0)
		{ }
		virtual void Out (COutBinStream& out)
		{
			if ( IsOriginate () )
			{
				out << mGroupID;
				out << mSID;
			} 
			else 
			{
				out << mResult;
			}
		}
		virtual void In (CInBinStream& in)
		{
			if ( IsOriginate () )
			{
				in >> mGroupID;
				in >> mSID;
			} 
			else 
			{
				in >> mResult;
			}
		}
		virtual ~CClusterAskWorker () { }
	public:
		//	in data。
		UInt16 mGroupID;
		UInt16 mSID;
		//	out data。
		UInt16 mResult;
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterAskWorker_H

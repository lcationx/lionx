#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterWorkerData_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterWorkerData_H

#include "Network/NetStream.h"

//===========================================================================================
//	叢集 - ClusterWorker資訊。
//===========================================================================================

namespace LionX
{
	class CClusterWorkerData : public CNetStream
	{
	public:
		CClusterWorkerData ()
			: mGroupID (-1), mSID (-1)
		{ }
		virtual void Out (COutBinStream& out)
		{
			out << mGroupID;
			out << mSID;
		}
		virtual void In (CInBinStream& in)
		{
			in >> mGroupID;
			in >> mSID;
		}
		virtual ~CClusterWorkerData () { }
	public:
		UInt16 mGroupID;
		UInt16 mSID;	
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterWorkerData_H

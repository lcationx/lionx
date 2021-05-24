#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterUpdateWorker_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterUpdateWorker_H

#include "Network/NetStream.h"

//===========================================================================================
//	叢集 - 更新ClusterWorker資訊。
//===========================================================================================

namespace LionX
{
	class CClusterUpdateWorker : public CNetStream
	{
	public:
		CClusterUpdateWorker ()
			: mPriority (0)
		{ }
		virtual void Out (COutBinStream& out)
		{
			out << mPriority;
		}
		virtual void In (CInBinStream& in)
		{
			in >> mPriority;
		}
		virtual ~CClusterUpdateWorker () { }
	public:
		UInt32 mPriority;
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterUpdateWorker_H

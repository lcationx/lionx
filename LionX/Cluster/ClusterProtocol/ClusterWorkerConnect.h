#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterWorkerConnect_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterWorkerConnect_H

#include "Network/NetStream.h"

//===========================================================================================
//	叢集 - 請求ClusterWorker連接。
//===========================================================================================

namespace LionX
{
	class CClusterWorkerConnect : public CNetStream
	{
	public:
		CClusterWorkerConnect ()
			: mGroupID (-1), mSID (-1), mServicePort (0)
		{ }
		virtual void Out (COutBinStream& out)
		{
			out << mGroupID;
			out << mSID;
			out << mServiceIP;
			out << mServicePort;
		}
		virtual void In (CInBinStream& in)
		{
			in >> mGroupID;
			in >> mSID;
			in >> mServiceIP;
			in >> mServicePort;
		}
		virtual ~CClusterWorkerConnect () { }
	public:
		//	in data。
		UInt16 mGroupID;
		UInt16 mSID;
		std::string mServiceIP;
		UInt16 mServicePort;
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterWorkerConnect_H

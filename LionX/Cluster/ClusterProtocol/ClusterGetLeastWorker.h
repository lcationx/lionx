#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterGetLeastWorker_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterGetLeastWorker_H

#include "Network/NetStream.h"

//===========================================================================================
//	叢集 - 查詢負荷最小的Worker。
//===========================================================================================

namespace LionX
{
	class CClusterGetLeastWorker : public CNetStream
	{
	public:
		CClusterGetLeastWorker ()
			: mGroupID (-1), mSID (-1)
		{ }
		virtual void Out (COutBinStream& out)
		{
			if ( IsOriginate () )
			{
				out << mGroupID;
			} 
			else 
			{
				out << mSID;
			}
		}
		virtual void In (CInBinStream& in)
		{
			if ( IsOriginate () )
			{
				in >> mGroupID;
			} 
			else 
			{
				in >> mSID;
			}
		}
		virtual ~CClusterGetLeastWorker () { }
	public:
		//	in data。
		UInt16 mGroupID;
		//	out data。
		UInt16 mSID;
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterGetLeastWorker_H

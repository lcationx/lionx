#ifndef LionX_LionX_Cluster_ClusterProtocol_ClusterProtocols_H
#define LionX_LionX_Cluster_ClusterProtocol_ClusterProtocols_H

#include "Base/LionX.h"

//===========================================================================================
//	叢集 - 系統用封包數據。
//===========================================================================================

#include "ClusterRegisterWorker.h"
#include "ClusterGetLeastWorker.h"
#include "ClusterAskWorker.h"
#include "ClusterWorkerConnect.h"
#include "ClusterWorkerData.h"
#include "ClusterUpdateWorker.h"

namespace LionX
{
	enum EClusterProtocol
	{
		eCClusterRegisterWorker = 0,
		eCClusterGetLeastWorker,
		eCClusterAskWorker,
		eCClusterWorkerConnect,
		eCClusterWorkerData,
		eCClusterUpdateWorker,

		eMaxClusterProtoID,
	};
};

#endif //	LionX_LionX_Cluster_ClusterProtocol_ClusterProtocols_H

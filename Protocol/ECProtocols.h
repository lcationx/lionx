#ifndef LionX_Sample_Protocol_ECProtocols_H
#define LionX_Sample_Protocol_ECProtocols_H

#include "Network/NetStream.h"
#include "Cluster/ClusterProtocol/ClusterProtocols.h"
#include "Network/NetCommand.h"

//===========================================================================================
//	擴展叢集通訊協定。
//===========================================================================================

#include "EC_Hello.h"

namespace LionX
{
	enum EECProtocol
	{
		eCEC_Hello = eMaxClusterProtoID,

		eEndECProtocol,
		eECProtocolAmount = eEndECProtocol - eMaxClusterProtoID,
	};
};

#endif //	LionX_Sample_Protocol_ECProtocols_H


#ifndef LionX_LionX_Cluster_ClusterServer_H
#define LionX_LionX_Cluster_ClusterServer_H

#include "Network/TCPServer.h"
#include "Network/NetTaskGenerator.h"

//===========================================================================================
//	叢集 - TCP伺服器。
//===========================================================================================

namespace LionX
{
	class CClusterChannel;

	class CClusterServer : public CTCPServer
	{
	public:
		CClusterServer (CNetTaskGenerator& taskgenerator, std::function<void(void)> fn_on_closed, std::function<void(CClusterChannel*)> fn_on_channel_closed);
		CClusterServer (CNetTaskGenerator& taskgenerator, std::function<void(void)> fn_on_closed, std::function<void(CClusterChannel*)> fn_on_channel_closed, std::function<void(CClusterChannel*)> fn_on_channel_connected);
		virtual CSocket* AllocSocket (Int32 fd, UInt32 remote_address, UInt16 remote_port);
		virtual void OnClosed (Int32 ret_code);
		virtual ~CClusterServer ();
	private:
		CNetTaskGenerator& mTaskGenerator;
		std::function<void(void)> mFnOnClosed;
		std::function<void(CClusterChannel*)> mFnOnChannelClosed;
		std::function<void(CClusterChannel*)> mFnOnChannelConnected;
	};
};

#endif //	LionX_LionX_Cluster_ClusterServer_H

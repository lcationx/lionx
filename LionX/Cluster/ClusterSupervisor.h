#ifndef LionX_LionX_Cluster_ClusterSupervisor_H
#define LionX_LionX_Cluster_ClusterSupervisor_H

#include "ClusterChannel.h"
#include "ClusterProtocol/ClusterProtocols.h"

//===========================================================================================
//	叢集 - 調度管理者。
//===========================================================================================

namespace LionX
{
	class CClusterServer;
	class ITimeTaskAction;

	class CClusterSupervisor
	{
	private:
		enum
		{
			STOP_SERVICE		= 0x0001,
			CLOSE_ALL_WORKERS	= 0x0002,
		};
	public:
		CClusterSupervisor ();
		Int32 Initialize (UInt16 csid, const std::string& server_ip, UInt16 server_port, UInt16 extra_protocol_amount, std::function<void(CNetTaskGenerator&)> fn_book_extra_protocol);
		void CloseWorkerConnect (UInt16 group_id, UInt16 sid);
		void StopService ();
		void CloseAllWorkerConnect ();	
		CClusterChannel* GetLeastWorker (UInt16 group_id);
		CClusterChannel* GetWorker (UInt16 group_id, UInt16 sid);
		ENetTranStatus SendCommand (UInt16 group_id, UInt16 sid, INetCommand *command);
		ENetTranStatus SendCommand (UInt16 group_id, INetCommand *command);
		void Broadcast (INetCommand *command);
		void Broadcast (UInt16 group_id, INetCommand *command);
		ENetTranStatus SendResultCommand (UInt16 group_id, UInt16 sid, INetCommand *command, double exp_date = 15.0);
		ENetTranStatus SendResultCommand (UInt16 group_id, INetCommand *command, double exp_date = 15.0);
		//	禁止雙向Wait會死鎖。
		ENetTranStatus SendWaitCommand (UInt16 group_id, UInt16 sid, INetCommand *command, double exp_date = 2.0);
		ENetTranStatus SendWaitCommand (UInt16 group_id, INetCommand *command, double exp_date = 2.0);
		virtual ~CClusterSupervisor ();
	public:
		inline bool IsStopService () const { return (mFlags & STOP_SERVICE); }
		inline bool IsCloseAllWorkers () const { return (mFlags & CLOSE_ALL_WORKERS); }
		inline UInt32 GetWorkerAmount () const { return mWorkerAmount; }
		inline CNetTaskGenerator& GetNetTaskGenerator () { return mTaskGenerator; }
	protected:
		virtual void OnWorkerConnected (CClusterChannel *channel) { }
		virtual void OnWorkerDiconnected (CClusterChannel *channel) { }
		virtual void OnServerStarted () { }
		virtual void OnServerClosed () { }
		virtual void OnUpdatePriority (CClusterChannel *channel) { }
	private:
		void OnRegisterWorker (TaskCommand<CClusterRegisterWorker>* ctask);
		void OnGetLeastWorker (TaskCommand<CClusterGetLeastWorker>* ctask);
		void OnAskWorker (TaskCommand<CClusterAskWorker>* ctask);
		void OnUpdateWoker (TaskCommand<CClusterUpdateWorker>* ctask);
	private:
		void WorkerDiconnected (CClusterChannel *channel);
		void ServerClosed ();
		Int32 CreateServer (const std::string& ip, UInt16 port);
	protected:
		CNetTaskGenerator mTaskGenerator;
		UInt16 mFlags;
		ITimeTaskAction *mServerReActionTask;
		CClusterServer *mServer;
		UInt32 mWorkerAmount;
		double mBeginTime;
		std::map<UInt16, CClusterChannel*> mLeastWorkers;
		std::map< UInt16, std::map<UInt16, CClusterChannel*> > mAllWorkers;	
	};
};

#endif //	LionX_LionX_Cluster_ClusterSupervisor_H

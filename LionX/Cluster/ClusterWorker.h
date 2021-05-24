#ifndef LionX_LionX_Cluster_ClusterWorker_H
#define LionX_LionX_Cluster_ClusterWorker_H

#include "ClusterChannel.h"
#include "ClusterProtocol/ClusterProtocols.h"

//===========================================================================================
//	叢集 - 工作者。
//===========================================================================================

namespace LionX
{
	class CClusterServer;
	class ITimeTaskAction;
	class ITaskAction;

	class CClusterWorker
	{
	public:
		const UInt16 LeastSID = -1;
	private:
		enum
		{
			STOP_SERVICE			= 0x0001,
			CLOSE_ALL_SUPERVISORS	= 0x0002,
			CLOSE_ALL_WORKERS		= 0x0004,
		};
	public:
		CClusterWorker ();
		Int32 Initialize (UInt16 group_id, UInt16 sid, const std::string& service_ip, UInt16 service_port,
							 UInt16 extra_protocol_amount, std::function<void(CNetTaskGenerator&)> fn_book_extra_protocol);
		void SetPriority (UInt32 priority);
		Int32 ConnectSupervisor (UInt16 supid, const std::string& supip, UInt16 support);
		Int32 CloseSupervisorConnect (UInt16 supid);
		void CloseAllSupervisorConnect ();
		CClusterChannel* GetWorker (UInt16 group_id, UInt16 sid);
		void UpdateLeastWorkerForSupervisor (UInt16 group_id);
		virtual void StopService ();
		void CloseAllWorkerConnects ();
		//	向Supervisor發送。
		ENetTranStatus SendSupervisorCommand (INetCommand *command);
		ENetTranStatus SendSupervisorCommand (UInt16 sid, INetCommand *command);
		void BroadcastToSupervisors (INetCommand *command);
		ENetTranStatus SendResultSupervisorCommand (INetCommand *command, double exp_date = 15.0);
		ENetTranStatus SendResultSupervisorCommand (UInt16 sid, INetCommand *command, double exp_date = 15.0);
		//	禁止雙向Wait會死鎖。
		ENetTranStatus SendWaitSupervisorCommand (INetCommand *command, double exp_date = 2.0);
		ENetTranStatus SendWaitSupervisorCommand (UInt16 sid, INetCommand *command, double exp_date = 2.0);
		//	向其他Worker發送。
		void SendCommand (UInt16 group_id, INetCommand *command);
		void SendCommand (UInt16 group_id, UInt16 sid, INetCommand *command);
		ENetTranStatus SendResultCommand (UInt16 group_id, INetCommand *command, double exp_date = 15.0);
		ENetTranStatus SendResultCommand (UInt16 group_id, UInt16 sid, INetCommand *command, double exp_date = 15.0);
		virtual ~CClusterWorker ();
	public:
		inline bool IsStopService () const { return (mFlags & STOP_SERVICE); }
		inline bool IsCloseAllSupervisors () const { return (mFlags & CLOSE_ALL_SUPERVISORS); }
		inline bool IsCloseAllWorkers () const { return (mFlags & CLOSE_ALL_WORKERS); }
		inline UInt32 GetConnectAmount () const { return mConnectAmount; }
		inline CNetTaskGenerator& GetNetTaskGenerator () { return mTaskGenerator; }
	protected:
		virtual void OnSupervisorConnected (CClusterChannel *channel) { }
		virtual void OnSupervisorDeconnected (CClusterChannel *channel) { }
		virtual void OnWorkerConnected (CClusterChannel *channel) { }
		virtual void OnWorkerDeconnected (CClusterChannel *channel) { }
		virtual void OnServerStarted () { }
		virtual void OnServerClosed () { }
		virtual UInt16 GetLeastWorkerChangeCount (UInt16 group_id) { return 300; }
		virtual double GetLeastWorkerChangeTime (UInt16 group_id) { return 300.0; }
	private:
		void OnWorkerConnect (TaskCommand<CClusterWorkerConnect>* ctask);
		void OnWorkerData (TaskCommand<CClusterWorkerData>* ctask);
	private:
		void ServerClosed ();
		void SupervisorDeconnected (CClusterChannel *channel);
		void WorkerDeconnected (CClusterChannel *channel);
		Int32 CreateSupervisorConnect (UInt16 supid, const std::string& ip, UInt16 port);
		Int32 CreateServer ();
		void ResetFocusSupervisor ();
		CClusterChannel* GetLeastWorkerForSupervisor (UInt16 group_id);
		CClusterChannel* GetWorkerForSupervisor (UInt16 group_id, UInt16 sid);
		CClusterChannel* GetSupervisor (UInt16 supid);
		void SendKeepCommands (CClusterChannel* channel, UInt16 group_id, UInt16 sid);
	private:
		CNetTaskGenerator mTaskGenerator;
		UInt16 mFlags;
		UInt32 mConnectAmount;
		UInt16 mGroupID;
		UInt16 mSID;
		std::string mServiceIP;
		UInt16 mServicePort;
		UInt32 mPriority;
		ITimeTaskAction *mServerReActionTask;
		CClusterServer *mServer;
		std::map<UInt16, ITaskAction*> mTaskGetLeastWorkers;
		std::map<UInt16, CClusterChannel*> mLeastWorkers;
		std::map<UInt16, std::map<UInt16, CClusterChannel*> > mAllWorkers;
		std::map<UInt16, std::map<UInt16, std::vector<INetCommand*> > > mKeepCommands;
		CClusterChannel *mFocusSupervisor;
		std::map<UInt16, std::pair<ITimeTaskAction*, CClusterChannel*> > mAllSupervisor;
	};
};

#endif //	LionX_LionX_Cluster_ClusterWorker_H

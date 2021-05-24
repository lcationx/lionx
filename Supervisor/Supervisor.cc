
#include "Supervisor.h"


namespace LionX
{

	CGlobal gGlobal;
	CSupervisor* CSupervisor::mInstance = nullptr;

	Int32 CSupervisor::Create ()
	{
		if (mInstance != nullptr)
			return -1;
		mInstance = LP_NEW (CSupervisor);
		Int32 result = mInstance->Initialize (0, "127.0.0.1", 10000, eEndECProtocol, [](CNetTaskGenerator& gen) {
			//	加入擴增事件。
			BookResultAutoSameNameTaskCommand (gen, CEC_Hello, LP_Supervisor.OnHello (task));


			});
		if (result != 0) {
			LP_SAFE_DELETE (mInstance);
		} else {
			if ((result = mInstance->Init ()) != 0) {
				LP_SAFE_DELETE (mInstance);
			}
		}
		return result;
	}
	void CSupervisor::Release ()
	{
		LP_SAFE_DELETE (mInstance);
	}

	CSupervisor::CSupervisor ()
	{

	}
	Int32 CSupervisor::Init ()
	{

		return 0;
	}
	void CSupervisor::SentHello (UInt16 server_type, UInt16 server_id)
	{
		NetCommand<CEC_Hello> nc_hello;
		nc_hello.mSentTime = LP_Global->GetCurrentTime ();
		ENetTranStatus tran_status = SendResultCommand (server_type, server_id, &nc_hello);
		if (tran_status != NET_TRANS_SUCCESS) {
			LP_BaseLogger->Append ("Sent hello but server can't connected.");
		} else {
			LP_BaseLogger->Append ("Sent hello to server[%hu][%hu] response delay:%lf.", server_type, server_id, nc_hello.mRecvTime - nc_hello.mSentTime);
		}
	}
	void CSupervisor::OnHello (TaskCommand<CEC_Hello>* netask)
	{
		netask->mRecvTime = LP_Global->GetCurrentTime ();
		CClusterChannel* channel = netask->GetChannel<CClusterChannel> ();
		LP_BaseLogger->Append ("Server[%hu][%hu] hello sent_time:%lf delay:%lf.", channel->GetGroupID (), channel->GetSID (), netask->mSentTime, netask->mRecvTime - netask->mSentTime);
	}
	void CSupervisor::Shutdown ()
	{
		CloseAllWorkerConnect ();
	}
	CSupervisor::~CSupervisor ()
	{

	}


	CGlobal::CGlobal ()
		: mSignal (false)
	{
		
	}
	Int32 CGlobal::OnInitialize (int argc, char *argv [])
	{
		Int32 result = LP_Network->Startup (4);
		if (result != 0) {
			LP_BaseLogger->Append ("FAIL:CNetwork::Startup (%u) fail : %d.", 4, result);
			return result;
		}
		result = CSupervisor::Create ();
		if (result != 0) {
			LP_BaseLogger->Append ("CSupervisor::Init () fail : %d.", result);
			return result;
		}
		return result;
	}
	void CGlobal::Update ()
	{
		if ( mSignal ) {
			Shutdown ();
		}
	}
	void CGlobal::OnSignal (Int32 sid)
	{
		mSignal = true;
	}
	void CGlobal::OnDestroy ()
	{
		CSupervisor::Release ();
		Network::Release ();
	}
	CGlobal::~CGlobal ()
	{
	
	}

};

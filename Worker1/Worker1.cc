
#include "Worker1.h"



namespace LionX
{
	CGlobal gGlobal;
	CWorker* CWorker::mInstance = nullptr;

	Int32 CWorker::Create ()
	{
		if (mInstance != nullptr)
			return -1;
		mInstance = LP_NEW (CWorker);
		Int32 result = mInstance->Initialize (1, 1, "127.0.0.1", 10001, eEndECProtocol, [](CNetTaskGenerator& gen) {
			//	加入擴增事件。
			BookResultAutoSameNameTaskCommand (gen, CEC_Hello, LP_Worker.OnHello (task));

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
	void CWorker::Release ()
	{
		LP_SAFE_DELETE (mInstance);
	}

	CWorker::CWorker ()
	{

	}
	Int32 CWorker::Init ()
	{
		//	連接主機。
		return ConnectSupervisor (0, "127.0.0.1", 10000);
	}
	void CWorker::SentHello (UInt16 server_type, UInt16 server_id)
	{
		NetCommand<CEC_Hello> nc_hello;
		nc_hello.mSentTime = LP_Global->GetCurrentTime ();
		ENetTranStatus tran_status;
		if (server_type == 0) {
			tran_status = SendResultSupervisorCommand (server_id, &nc_hello);
		} else {
			tran_status = SendResultCommand (server_type, server_id, &nc_hello);
		}
		if (tran_status != NET_TRANS_SUCCESS) {
			LP_BaseLogger->Append ("Sent hello but server can't connected.");
		} else {
			LP_BaseLogger->Append ("Sent hello to server[%hu][%hu] response delay:%lf.", server_type, server_id, nc_hello.mRecvTime - nc_hello.mSentTime);
		}
	}
	void CWorker::OnHello (TaskCommand<CEC_Hello>* netask)
	{
		netask->mRecvTime = LP_Global->GetCurrentTime ();
		CClusterChannel* channel = netask->GetChannel<CClusterChannel> ();
		LP_BaseLogger->Append ("Server[%hu][%hu] hello sent_time:%lf delay:%lf.", channel->GetGroupID (), channel->GetSID (), netask->mSentTime, netask->mRecvTime - netask->mSentTime);
	}

	void CWorker::Shutdown ()
	{
		CloseAllSupervisorConnect ();
		CloseAllWorkerConnects ();
	}
	CWorker::~CWorker ()
	{
	}

	void CWorker::OnSupervisorConnected (CClusterChannel* channel)
	{
		SentHello (0, 0);
		SentHello (1, 2);
	}


	CGlobal::CGlobal ()
		: mSignal (false)
	{

	}
	Int32 CGlobal::OnInitialize (int argc, char* argv[])
	{
		Int32 result = LP_Network->Startup (4);
		if (result != 0) {
			LP_BaseLogger->Append ("FAIL:CNetwork::Startup (%u) fail : %d.", 4, result);
			return result;
		}
		result = CWorker::Create ();
		if (result != 0) {
			LP_BaseLogger->Append ("CWorker::Init () fail : %d.", result);
			return result;
		}
		return result;
	}
	void CGlobal::Update ()
	{
		if (mSignal) {
			Shutdown ();
		}
	}
	void CGlobal::OnSignal (Int32 sid)
	{
		mSignal = true;
	}
	void CGlobal::OnDestroy ()
	{
		CWorker::Release ();
		Network::Release ();
	}
	CGlobal::~CGlobal ()
	{

	}

};

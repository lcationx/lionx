#ifndef LionX_Sample_Global_H
#define LionX_Sample_Global_H

#include "Application.h"
#include "Cluster/ClusterWorker.h"
#include "Network/Network.h"
#include "ECProtocols.h"

#define LP_Global ((CGlobal*)&CGlobal::Ins ())
#define LP_Worker (CWorker::Ins ())

//===========================================================================================
//	Worker Sample 1。
//===========================================================================================


namespace LionX
{
	class CWorker : public CClusterWorker
	{
	private:
		static CWorker* mInstance;
	public:
		static Int32 Create ();
		static CWorker& Ins () { return *mInstance; }
		static void Release ();
	public:
		CWorker ();
		Int32 Init ();
		void SentHello (UInt16 server_type, UInt16 server_id);
		void OnHello (TaskCommand<CEC_Hello>* netask);
		void Shutdown ();
		virtual ~CWorker ();
	public:
		virtual void OnSupervisorConnected (CClusterChannel* channel);
	};


	class CGlobal : public CApplication
	{
	public:
		CGlobal ();
		virtual Int32 OnInitialize (int argc, char *argv []);
		virtual void Update ();
		virtual void OnSignal (Int32 sid);
		virtual void OnDestroy ();
		virtual ~CGlobal ();
	private:
		bool mSignal;
	};
};

#endif //	LionX_Sample_Global_H

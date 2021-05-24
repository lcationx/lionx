#ifndef LionX_Sample_Supervisor_H
#define LionX_Sample_Supervisor_H

#include "Application.h"
#include "Cluster/ClusterSupervisor.h"
#include "Network/Network.h"
#include "ECProtocols.h"

#define LP_Global ((CGlobal*)&CGlobal::Ins ())
#define LP_Supervisor (CSupervisor::Ins ())

//===========================================================================================
//	Supervisor Sample。
//===========================================================================================


namespace LionX
{

	class CSupervisor : public CClusterSupervisor
	{
	private:
		static CSupervisor* mInstance;
	public:
		static Int32 Create ();
		static CSupervisor& Ins () { return *mInstance; }
		static void Release ();
	public:
		CSupervisor ();
		Int32 Init ();
		void SentHello (UInt16 server_type, UInt16 server_id);
		void OnHello (TaskCommand<CEC_Hello>* netask);
		void Shutdown ();
		virtual ~CSupervisor ();
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

#endif //	LionX_Sample_Supervisor_H

#ifndef LionX_LionX_Network_NetTaskGenerator_H
#define LionX_LionX_Network_NetTaskGenerator_H

#include "NetCommand.h"
#include "Base/ExecImpl.h"

//===========================================================================================
//	網路任務產生器。
//===========================================================================================

namespace LionX
{
	class ITaskGeneratorImpl
	{
	public:
		inline ITaskGeneratorImpl () { }
		virtual ITaskCommand* operator () (CInBinStream& in) = 0;
		virtual ~ITaskGeneratorImpl () { }
	public:
		std::string mName;
	};

	template <typename TNetStream>
	class BaseTaskGeneratorImpl : public ITaskGeneratorImpl
	{
	public:
		inline BaseTaskGeneratorImpl (std::function<void(BaseTaskCommand<TNetStream>*)> fnexec = nullptr)
			: mFnExecute (fnexec)
		{ }
		virtual ITaskCommand* operator () (CInBinStream& in)
		{
			if (mFnExecute == nullptr)
				return nullptr;
			typedef BaseTaskCommand<TNetStream> TASK;
			TASK *task = LP_NEW (TASK (mFnExecute));
			task->Deserialize (in);
			return (ITaskCommand*)task;
		}
		virtual ~BaseTaskGeneratorImpl () { }
	public:
		std::function<void(BaseTaskCommand<TNetStream>*)> mFnExecute;
	};

	template <typename TNetStream>
	class TaskGeneratorImpl : public ITaskGeneratorImpl
	{
	public:
		inline TaskGeneratorImpl (std::function<void(TaskCommand<TNetStream>*)> fnexec = nullptr)
			: mFnExecute (fnexec)
		{ }
		virtual ITaskCommand* operator () (CInBinStream& in)
		{
			if (mFnExecute == nullptr)
				return nullptr;
			typedef TaskCommand<TNetStream> TASK;
			TASK *task = LP_NEW (TASK (mFnExecute));
			task->Deserialize (in);
			return (ITaskCommand*)task;
		}
		virtual ~TaskGeneratorImpl () { }
	public:
		std::function<void(TaskCommand<TNetStream>*)> mFnExecute;
	};

	class CNetTaskGenerator
	{
	public:
		inline CNetTaskGenerator (UInt16 max)
			: mNullName ("null"), mImplTable (max, (ITaskGeneratorImpl*)0)
		{ }
		inline CNetTaskGenerator ()
			: mNullName ("null")
		{ }
		void SetTableSize (UInt16 max_size);
		UInt16 Book (UInt16 sn, ITaskGeneratorImpl *impl);
		UInt16 Book (UInt16 sn, ITaskGeneratorImpl *impl, const char *name);
		UInt16 Book (ITaskGeneratorImpl *impl);
		UInt16 Book (ITaskGeneratorImpl *impl, const char *name);
		ITaskCommand* Generate (UInt16 sn, CInBinStream& in);
		void Release ();
		const std::string& GetName (UInt16 sn) const;
		inline UInt16 GetSize () const { return (UInt16)mImplTable.size (); }
		inline bool IsExist (UInt16 sn) const { return (sn < (UInt16)mImplTable.size () && mImplTable [sn] != 0); }
		inline ~CNetTaskGenerator () { Release (); }
	private:
		std::string mNullName;
		std::vector <ITaskGeneratorImpl*> mImplTable;
	};

	//	標記NetCommand指令 (廣播不能用這個)。
#define BookNetCommand(sn, stream)	NetCommand< stream >::SN = ((UInt16)sn);
	//	標記TaskCommand任務 (廣播不能用這個)。
#define BookTaskCommand(gen, sn, stream, fnexec)	 {\
typedef TaskGeneratorImpl< stream > IMPL; \
NetCommand< stream >::SN = ((UInt16)sn); \
TaskCommand< stream >::SN = (gen).Book (sn, LP_NEW (IMPL([&](TaskCommand< stream >* task) { fnexec; }))); }
	//	標記會返回的TaskCommand任務 (廣播不能用這個)。
#define BookResultAutoTaskCommand(gen, sn, stream, fnexec)	 {\
typedef TaskGeneratorImpl< stream > IMPL; \
NetCommand< stream >::SN = ((UInt16)sn); \
TaskCommand< stream >::SN = (gen).Book (sn, LP_NEW (IMPL([&](TaskCommand< stream >* task) { fnexec; task->Reply (); }))); }

	//	標記同名NetCommand指令 (廣播不能用這個)。
#define BookSameNameNetCommand(stream)	NetCommand< stream >::SN = ((UInt16)e##stream);
	//	標記同名TaskCommand任務 (廣播不能用這個)。
#define BookSameNameTaskCommand(gen, stream, fnexec)	 {\
typedef TaskGeneratorImpl< stream > IMPL; \
NetCommand< stream >::SN = ((UInt16)e##stream); \
TaskCommand< stream >::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](TaskCommand< stream >* task) { fnexec; }))); }
	//	標記同名會返回的TaskCommand任務 (廣播不能用這個)。
#define BookResultAutoSameNameTaskCommand(gen, stream, fnexec)	 {\
typedef TaskGeneratorImpl< stream > IMPL; \
NetCommand< stream >::SN = ((UInt16)e##stream); \
TaskCommand< stream >::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](TaskCommand< stream >* task) { fnexec; task->Reply (); }))); }

	//	標記BaseNetCommand指令 (廣播要使用這個)。
#define BookBaseNetCommand(sn, stream)	BaseNetCommand< stream >::SN = ((UInt16)sn);
	//	標記BaseTaskCommand任務 (廣播要使用這個)。
#define BookBaseTaskCommand(gen, sn, stream, fnexec)	 {\
typedef BaseTaskGeneratorImpl< stream > IMPL; \
BaseNetCommand< stream >::SN = ((UInt16)sn); \
BaseTaskCommand< stream >::SN = (gen).Book (sn, LP_NEW (IMPL([&](BaseTaskCommand< stream >* task) { fnexec; }))); }
	//	標記同名BaseNetCommand指令 (廣播要使用這個)。
#define BookSameNameBaseNetCommand(stream)	BaseNetCommand< stream >::SN = ((UInt16)e##stream);
	//	標記同名BaseTaskCommand任務 (廣播要使用這個)。
#define BookSameNameBaseTaskCommand(gen, stream, fnexec)	 {\
typedef BaseTaskGeneratorImpl< stream > IMPL; \
BaseNetCommand< stream >::SN = ((UInt16)e##stream); \
BaseTaskCommand< stream >::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](BaseTaskCommand< stream >* task) { fnexec; }))); }


	//	標記ActorTaskCommand任務。
#define BookActorTask(gen, sn, stream, actor, fnexec)	 {\
typedef TaskGeneratorImpl<stream> IMPL; \
typedef TaskCommand<stream> TASK; \
typedef NetTaskExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (sn, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }
	//	標記ResultActorTaskCommand任務。
#define BookResultActorTask(gen, sn, stream, actor, fnexec)	 {\
typedef TaskGeneratorImpl<stream> IMPL; \
typedef TaskCommand<stream> TASK; \
typedef NetTaskResultExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (sn, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }

	//	標記同名ActorTaskCommand任務。
#define BookSameNameActorTask(gen, stream, actor, fnexec)	 {\
typedef TaskGeneratorImpl<stream> IMPL; \
typedef TaskCommand<stream> TASK; \
typedef NetTaskExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }
	//	標記同名ResultActorTaskCommand任務。
#define BookSameNameResultActorTask(gen, stream, actor, fnexec)	 {\
typedef TaskGeneratorImpl<stream> IMPL; \
typedef TaskCommand<stream> TASK; \
typedef NetTaskResultExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }


	//	標記ActorBaseTaskCommand任務。
#define BookBaseActorTask(gen, sn, stream, actor, fnexec)	 {\
typedef BaseTaskGeneratorImpl<stream> IMPL; \
typedef BaseTaskCommand<stream> TASK; \
typedef NetTaskExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (sn, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }
	//	標記ResultActorBaseTaskCommand任務。
#define BookResultBaseActorTask(gen, sn, stream, actor, fnexec)	 {\
typedef BaseTaskGeneratorImpl<stream> IMPL; \
typedef BaseTaskCommand<stream> TASK; \
typedef NetTaskResultExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (sn, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }

	//	標記同名ActorBaseTaskCommand任務。
#define BookSameNameBaseActorTask(gen, stream, actor, fnexec)	 {\
typedef BaseTaskGeneratorImpl<stream> IMPL; \
typedef BaseTaskCommand<stream> TASK; \
typedef NetTaskExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }
	//	標記同名ActorBaseTaskCommand任務。
#define BookSameNameResultBaseActorTask(gen, stream, actor, fnexec)	 {\
typedef BaseTaskGeneratorImpl<stream> IMPL; \
typedef BaseTaskCommand<stream> TASK; \
typedef NetTaskResultExecImpl<TASK> EXEC; \
TASK::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](TASK* task) { task->mAutoDeleted = false; actor->Subscribe (LP_NEW (EXEC (task, std::bind(&fnexec, actor, std::placeholders::_1)))); }))); }



#define BookCheckExecTaskCommand(book,gen,nt_task,check,exec)	book (gen, nt_task, if (!(check)) return; exec);
};

#endif //	LionX_LionX_Network_NetTaskGenerator_H

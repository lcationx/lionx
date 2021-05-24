#ifndef LionX_LionX_Application_H
#define LionX_LionX_Application_H

#include "Base/Task.h"
#include "Base/ActionTask.h"
#include "Base/Synchronization.h"
#include "Base/Coroutine.h"

//===========================================================================================
//	應用介面。
//===========================================================================================

namespace LionX
{
	class CApplication
	{
	private:
		class CTask_AppUpdate : public ITimeTask
		{
		public:
			inline CTask_AppUpdate (const CTime& offset)
				: ITimeTask (true), mTimeOffset (offset), mValid (true)
			{
				mExecuteTime += mTimeOffset;
			}
			virtual void Execute ();
			virtual bool IsValid () { return mValid; }
			virtual bool IsContinue () { return mValid; }
			virtual ~CTask_AppUpdate () { }
		public:
			CTime mTimeOffset;
			bool mValid;
		};
	private:
		struct STask_Order_Compare
		{
			inline bool operator ()(const ITimeTask* lhs, const ITimeTask* rhs) { return (lhs->ExecuteTime () > rhs->ExecuteTime ()); }
		};
	private:
		static CApplication *mInstance;
	public:
		static CApplication& Ins () { return *mInstance; }
		static bool IsCreated () { return (mInstance != 0); }
		static void Release () { LP_SAFE_DELETE (mInstance); }
	public:
		CApplication ();
		Int32 Initialize (int argc, char *argv[]);
		void PushTask (ITask *task);
		void PushTask (ITask **task_first, ITask **task_last);
		void PushTimeTask (ITimeTask *time_task);
		//	在主線程執行特定操作 (不同步 所以區域變數不可用)。
		void MainExecute (std::function<void()> method);
		//	在主線程執行特定操作並等待返回 (同步 所以區域變數可用)。
		void MainWaitExecute (std::function<void()> method);
		//	設定更新時間。
		void SetUpdateOffsetTime (const CTime& offset_time);
		//	協程等待給定時間後繼續。
		bool Wait (double wait_time);
		//	協程等待。
		bool Yield (double wait_time, std::function<bool ()> fncheck);
		//	協程等待。
		bool Yield (std::function<bool()> fncheck);
		void Running ();
		void Signal (Int32 sid);
		void Shutdown ();
		void Destroy ();
		virtual ~CApplication ();
	public:
		inline void UpdateCurrentTime () { mRealTime.Update (); }
		inline const CTime& GetCurrentTime () const { return mRealTime; }
	public:
		virtual Int32 OnInitialize (int argc, char *argv[]) = 0;
		virtual void Update () = 0;
		virtual void OnSignal (Int32 sid) = 0;
		virtual void OnDestroy () = 0;
	private:
		void HandleTask ();
	protected:
		volatile bool mSwitch;
		CTime mRealTime;
		CTask_AppUpdate *mTaskUpdate;
		CTime mNextUpdateTime;
		std::mutex mSpinLock;
		CSpinLock mConditionSpinLock;
		std::vector <ITask*> mTaskQueue;
		std::priority_queue<ITimeTask*, std::deque<ITimeTask*>, STask_Order_Compare> mRealPriorityQueue;
		CCondition mCondition;
		ITask *mCurrTask;
		CCoroutine mCoroutine;
	};
};

#endif //	LionX_LionX_Application_H

#ifndef LionX_LionX_Base_ActionTask_H
#define LionX_LionX_Base_ActionTask_H

#include "Task.h"

//===========================================================================================
//	任務介面。
//===========================================================================================

namespace LionX
{
	class ITaskAction : public ITask
	{
	public:
		inline ITaskAction ()
			: mValid (true), mContinue (false), mReleaseFunction (nullptr)
		{ }
		template<typename T>
		T& GetParam1 () { return *(T*)GetParam (1); }
		template<typename T>
		T& GetParam2 () { return *(T*)GetParam (2); }
		template<typename T>
		T& GetParam3 () { return *(T*)GetParam (3); }
		template<typename T>
		T& GetParam4 () { return *(T*)GetParam (4); }
		inline void SetValid (bool valid) { mValid = valid; }
		inline bool GetValid () const { return mValid; }
		inline void SetContinue (bool _continue) { mContinue = _continue; }
		inline bool GetContinue () const { return mContinue; }
		virtual ~ITaskAction () { }
	public:
		inline void SetReleaseFunction (std::function<void(ITaskAction*)> fnexec) { mReleaseFunction = fnexec; }
		virtual bool IsValid () { return mValid; }
		virtual bool IsContinue () { return mContinue; }
	protected:
		virtual void* GetParam (UInt32 idx) = 0;
	protected:
		bool mValid, mContinue;
		std::function<void(ITaskAction*)> mReleaseFunction;
	};

	class ITimeTaskAction : public ITimeTask
	{
	public:
		inline ITimeTaskAction (const CTime& exec_time = CTime (true))
			: mValid (true), mContinue (false), mOffsetTime (0.0), mReleaseFunction (nullptr)
		{
			mExecuteTime = exec_time;
		}
		template<typename T>
		T& GetParam1 () { return *(T*)GetParam (1); }
		template<typename T>
		T& GetParam2 () { return *(T*)GetParam (2); }
		template<typename T>
		T& GetParam3 () { return *(T*)GetParam (3); }
		template<typename T>
		T& GetParam4 () { return *(T*)GetParam (4); }
		inline void SetValid (bool valid) { mValid = valid; }
		inline bool GetValid () const { return mValid; }
		inline void SetContinue (bool _continue) { mContinue = _continue; }
		inline bool GetContinue () const { return mContinue; }
		virtual ~ITimeTaskAction () { }
	public:
		inline CTime& OffsetTime () { return mOffsetTime; }
		inline void SetReleaseFunction (std::function<void(ITimeTaskAction*)> fnexec) { mReleaseFunction = fnexec; }
		virtual bool IsValid () { return mValid; }
		virtual bool IsContinue () { return mContinue; }
	protected:
		virtual void* GetParam (UInt32 idx) = 0;
	protected:
		bool mValid, mContinue;
		CTime mOffsetTime;
		std::function<void(ITimeTaskAction*)> mReleaseFunction;
	};

	template <typename T1 = char, typename T2 = char, typename T3 = char, typename T4 = char>
	class CTaskAction : public ITaskAction
	{
	public:
		inline CTaskAction (std::function<void(ITaskAction*)> fnexec = nullptr)
			: mExecFunction (fnexec)
		{ }
		inline CTaskAction (const T1& t1, std::function<void(ITaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mExecFunction (fnexec)
		{ }
		inline CTaskAction (const T1& t1, const T2& t2, std::function<void(ITaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mParam2 (t2), mExecFunction (fnexec)
		{ }
		inline CTaskAction (const T1& t1, const T2& t2, const T3& t3, std::function<void(ITaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mParam2 (t2), mParam3 (t3), mExecFunction (fnexec)
		{ }
		inline CTaskAction (const T1& t1, const T2& t2, const T3& t3, const T4& t4, std::function<void(ITaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mParam2 (t2), mParam3 (t3), mParam4 (t4), mExecFunction (fnexec)
		{ }
		inline void SetExecFunction (std::function<void(ITaskAction*)> fnexec)
		{ 
			mExecFunction = fnexec;
		}
		virtual void Execute ()
		{
			if (mExecFunction == nullptr) {
				SetContinue (false);
			} else {
				mExecFunction (this);
			}
		}
		virtual ~CTaskAction ()
		{
			if (mReleaseFunction != nullptr) {
				mReleaseFunction (this);
			}
		}
	protected:
		virtual void* GetParam (UInt32 idx)
		{
			switch (idx)
			{
			case 1:
				return (void*)&mParam1;
			case 2:
				return (void*)&mParam2;
			case 3:
				return (void*)&mParam3;
			case 4:
				return (void*)&mParam4;
			default:
				return nullptr;
			};
		}
	public:
		T1 mParam1;
		T2 mParam2;
		T3 mParam3;
		T4 mParam4;
	protected:
		std::function<void(ITaskAction*)> mExecFunction;
	};

	static ITaskAction* CreateActionTask (std::function<void(ITaskAction*)> method)
	{
		return LP_NEW (CTaskAction<char> (method));
	}

	template <typename T1>
	static ITaskAction* CreateActionTask (const T1& t1, std::function<void(ITaskAction*, T1&)> method)
	{
		typedef CTaskAction<T1> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1);
		});
		return task;
	}

	template <typename T1>
	static ITaskAction* CreateActionTask (std::function<void(ITaskAction*, T1&)> method)
	{
		typedef CTaskAction<T1> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1);
		});
		return task;
	}

	template <typename T1, typename T2>
	static ITaskAction* CreateActionTask (const T1& t1, const T2& t2, std::function<void(ITaskAction*, T1&, T2&)> method)
	{
		typedef CTaskAction<T1, T2> TASK;
		TASK *task = LP_NEW (TASK (t1, t2));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2);
		});
		return task;
	}

	template <typename T1, typename T2>
	static ITaskAction* CreateActionTask (const T1& t1, std::function<void(ITaskAction*, T1&, T2&)> method)
	{
		typedef CTaskAction<T1, T2> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2);
		});
		return task;
	}

	template <typename T1, typename T2>
	static ITaskAction* CreateActionTask (std::function<void(ITaskAction*, T1&, T2&)> method)
	{
		typedef CTaskAction<T1, T2> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITaskAction* CreateActionTask (const T1& t1, const T2& t2, const T3& t3, std::function<void(ITaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK (t1, t2, t3));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITaskAction* CreateActionTask (const T1& t1, std::function<void(ITaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITaskAction* CreateActionTask (const T1& t1, const T2& t2, std::function<void(ITaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK (t1, t2));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITaskAction* CreateActionTask (std::function<void(ITaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITaskAction* CreateActionTask (const T1& t1, const T2& t2, const T3& t3, const T4& t4, std::function<void(ITaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1, t2, t3, t4));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITaskAction* CreateActionTask (const T1& t1, std::function<void(ITaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITaskAction* CreateActionTask (const T1& t1, const T2& t2, std::function<void(ITaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1, t2));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITaskAction* CreateActionTask (const T1& t1, const T2& t2, const T3& t3, std::function<void(ITaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1, t2, t3));
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITaskAction* CreateActionTask (std::function<void(ITaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1 = char, typename T2 = char, typename T3 = char, typename T4 = char>
	class CTimeTaskAction : public ITimeTaskAction
	{
	public:
		inline CTimeTaskAction (std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, const T2& t2, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mParam2 (t2), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, const T2& t2, const T3& t3, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mParam2 (t2), mParam3 (t3), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, const T2& t2, const T3& t3, const T4& t4, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: mParam1 (t1), mParam2 (t2), mParam3 (t3), mParam4 (t4), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (CTime& exec_time, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: ITimeTaskAction (exec_time), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, CTime& exec_time, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: ITimeTaskAction (exec_time), mParam1 (t1), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, const T2& t2, CTime& exec_time, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: ITimeTaskAction (exec_time), mParam1 (t1), mParam2 (t2), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, const T2& t2, const T3& t3, CTime& exec_time, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: ITimeTaskAction (exec_time), mParam1 (t1), mParam2 (t2), mParam3 (t3), mExecFunction (fnexec)
		{
		}
		inline CTimeTaskAction (const T1& t1, const T2& t2, const T3& t3, const T4& t4, CTime& exec_time, std::function<void(ITimeTaskAction*)> fnexec = nullptr)
			: ITimeTaskAction (exec_time), mParam1 (t1), mParam2 (t2), mParam3 (t3), mParam4 (t4), mExecFunction (fnexec)
		{
		}
		inline void SetExecFunction (std::function<void(ITimeTaskAction*)> fnexec)
		{ 
			mExecFunction = fnexec;
		}
		virtual void Execute ()
		{
			if (mExecFunction == nullptr) {
				SetContinue (false);
			} else {
				mExecFunction (this);
			}
			mExecuteTime += mOffsetTime;
		}
		virtual ~CTimeTaskAction ()
		{
			if (mReleaseFunction != nullptr) {
				mReleaseFunction (this);
			}
		}
	protected:
		virtual void* GetParam (UInt32 idx)
		{
			switch (idx)
			{
			case 1:
				return (void*)&mParam1;
			case 2:
				return (void*)&mParam2;
			case 3:
				return (void*)&mParam3;
			case 4:
				return (void*)&mParam4;
			default:
				return nullptr;
			};
		}
	public:
		T1 mParam1;
		T2 mParam2;
		T3 mParam3;
		T4 mParam4;
	protected:
		std::function<void(ITimeTaskAction*)> mExecFunction;
	};

	static ITimeTaskAction* CreateTimeActionTask (std::function<void(ITimeTaskAction*)> method)
	{
		return LP_NEW (CTimeTaskAction<char> (method));
	}

	template <typename T1>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, std::function<void(ITimeTaskAction*, T1&)> method)
	{
		typedef CTimeTaskAction<T1> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1);
		});
		return task;
	}

	template <typename T1>
	static ITimeTaskAction* CreateTimeActionTask (std::function<void(ITimeTaskAction*, T1&)> method)
	{
		typedef CTimeTaskAction<T1> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1);
		});
		return task;
	}

	template <typename T1, typename T2>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, const T2& t2, std::function<void(ITimeTaskAction*, T1&, T2&)> method)
	{
		typedef CTimeTaskAction<T1, T2> TASK;
		TASK *task = LP_NEW (TASK (t1, t2));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2);
		});
		return task;
	}

	template <typename T1, typename T2>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, std::function<void(ITimeTaskAction*, T1&, T2&)> method)
	{
		typedef CTimeTaskAction<T1, T2> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2);
		});
		return task;
	}

	template <typename T1, typename T2>
	static ITimeTaskAction* CreateTimeActionTask (std::function<void(ITimeTaskAction*, T1&, T2&)> method)
	{
		typedef CTimeTaskAction<T1, T2> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, const T2& t2, const T3& t3, std::function<void(ITimeTaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK (t1, t2, t3));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, const T2& t2, std::function<void(ITimeTaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK (t1, t2));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, std::function<void(ITimeTaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3>
	static ITimeTaskAction* CreateTimeActionTask (std::function<void(ITimeTaskAction*, T1&, T2&, T3&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, const T2& t2, const T3& t3, const T4& t4, std::function<void(ITimeTaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1, t2, t3, t4));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, const T2& t2, const T3& t3, std::function<void(ITimeTaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1, t2, t3));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, const T2& t2, std::function<void(ITimeTaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1, t2));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITimeTaskAction* CreateTimeActionTask (const T1& t1, std::function<void(ITimeTaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK (t1));
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static ITimeTaskAction* CreateTimeActionTask (std::function<void(ITimeTaskAction*, T1&, T2&, T3&, T4&)> method)
	{
		typedef CTimeTaskAction<T1, T2, T3, T4> TASK;
		TASK *task = LP_NEW (TASK);
		task->SetExecFunction ([method](ITimeTaskAction* task) {
			TASK *t = (TASK*)task;
			method (task, t->mParam1, t->mParam2, t->mParam3, t->mParam4);
		});
		return task;
	}
};

#endif //	LionX_LionX_Base_ActionTask_H

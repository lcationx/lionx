#ifndef LionX_LionX_Base_Actor_H
#define LionX_LionX_Base_Actor_H

#include "ActionTask.h"
#include "ExecImpl.h"

//===========================================================================================
//	基礎Acotr物件。
//===========================================================================================

namespace LionX
{
	class CActor
	{
	public:
		CActor ();
		bool Subscribe (IExecImpl *execimpl, bool front = false);
		bool ResultSubscribe (IExecImpl *execimpl, bool immediate = false);
		bool WaitSubscribe (IExecImpl *execimpl, bool immediate = false);
		template<typename T>
		bool PushExec (void (T::*Function)(), bool front = false)
		{
			return Subscribe (CreateParamExecImpl (std::bind(Function, (T*)this)), front);
		}
		template<typename T1, typename T>
		bool PushExec (const T1& t1, void (T::*Function)(T1), bool front = false)
		{
			return Subscribe (CreateParamExecImpl<T1> (t1, std::bind(Function, (T*)this, std::placeholders::_1)), front);
		}
		template<typename T1, typename T2, typename T>
		bool PushExec (const T1& t1, const T2& t2, void (T::*Function)(T1,T2), bool front = false)
		{
			return Subscribe (CreateParamExecImpl<T1,T2> (t1, t2, std::bind(Function, (T*)this, std::placeholders::_1, std::placeholders::_2)), front);
		}
		template<typename T1, typename T2, typename T3, typename T>
		bool PushExec (const T1& t1, const T2& t2, const T3& t3, void (T::*Function)(T1,T2,T3), bool front = false)
		{
			return Subscribe (CreateParamExecImpl<T1,T2,T3> (t1, t2, t3, std::bind(Function, (T*)this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)), front);
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T>
		bool PushExec (const T1& t1, const T2& t2, const T3& t3, const T4& t4, void (T::*Function)(T1,T2,T3,T4), bool front = false)
		{
			return Subscribe (CreateParamExecImpl<T1,T2,T3,T4> (t1, t2, t3, t4, std::bind(Function, (T*)this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)), front);
		}
		bool WaitExec (std::function<void()> method);
		virtual void Execute ();
		void Close ();
		bool IsFinish ();
		void Finish (bool force = false);
		virtual ~CActor ();
	private:
		void Clear ();
		bool SubscribeResult (IExecImpl *execimpl, bool immediate = false);
	private:
		ITaskAction *mExecTask;
		std::deque<IExecImpl*> mExecImpls;
		bool mClosed;
	private:
		friend class CApplication;
	};

};

#endif //	LionX_LionX_Base_Actor_H

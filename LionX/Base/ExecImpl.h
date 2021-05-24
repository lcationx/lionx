#ifndef LionX_LionX_Base_ExecImpl_H
#define LionX_LionX_Base_ExecImpl_H

#include "LionX.h"

//===========================================================================================
//	執行介面。
//===========================================================================================

namespace LionX
{
	class IExecImpl
	{
	private:
		enum EFlags
		{
			RESULT = 0x01,
			FAIL = 0x02,
			FINISH = 0x04,
		};
	public:
		inline IExecImpl ()
			: mFlags (0)
		{ }
		void Handle ()
		{
			Execute ();
			mFlags |= FINISH;
		}
		virtual ~IExecImpl () { }
	public:
		virtual void Execute () { }
	private:
		inline void SetResult (bool result) { result ? mFlags |= RESULT : mFlags &= ~RESULT; }
		inline bool IsResult () const { return ((mFlags & RESULT) != 0); }
		inline void SetFail (bool closed) { closed ? mFlags |= FAIL : mFlags &= ~FAIL; }
		inline bool IsFail () const { return ((mFlags & FAIL) != 0); }
		inline bool IsFinish () const { return ((mFlags & FINISH) != 0); }
	private:
		UInt16 mFlags;
	private:
		friend class CActor;
	};

	class BaseExecImpl : public IExecImpl
	{
	public:
		inline BaseExecImpl (std::function<void()> method)
			: mMethod (method)
		{
		}
		virtual void Execute ()
		{
			mMethod ();
		}
		virtual ~BaseExecImpl ()
		{
		}
	private:
		std::function<void()> mMethod;
	};

	template<typename T>
	class NetTaskExecImpl : public IExecImpl
	{
	public:
		inline NetTaskExecImpl (T *task, std::function<void(T*)> method)
			: mTask (task), mMethod (method)
		{
			task->mAutoDeleted = false; 
		}
		virtual void Execute ()
		{
			mMethod (mTask);
		}
		virtual ~NetTaskExecImpl ()
		{
			LP_SAFE_DELETE (mTask);
		}
	private:
		T *mTask;
		std::function<void(T*)> mMethod;
	};

	template<typename T>
	class NetTaskResultExecImpl : public IExecImpl
	{
	public:
		inline NetTaskResultExecImpl (T *task, std::function<void(T*)> method)
			: mTask (task), mMethod (method)
		{
			task->mAutoDeleted = false; 
		}
		virtual void Execute ()
		{
			mMethod (mTask);
			mTask->Reply ();
		}
		virtual ~NetTaskResultExecImpl ()
		{
			LP_SAFE_DELETE (mTask);
		}
	private:
		T *mTask;
		std::function<void(T*)> mMethod;
	};

	template<typename T1 = char, typename T2 = char, typename T3 = char, typename T4 = char>
	class ParamExecImpl : public IExecImpl
	{
	public:
		inline ParamExecImpl (std::function<void(IExecImpl*)> method)
			: mMethod (method)
		{ }
		inline ParamExecImpl (const T1& t1, std::function<void(IExecImpl*)> method)
			: mParam1 (t1), mMethod (method)
		{ }
		inline ParamExecImpl (const T1& t1, const T2& t2, std::function<void(IExecImpl*)> method)
			: mParam1 (t1), mParam2 (t2), mMethod (method)
		{ }
		inline ParamExecImpl (const T1& t1, const T2& t2, const T3& t3, std::function<void(IExecImpl*)> method)
			: mParam1 (t1), mParam2 (t2), mParam3 (t3), mMethod (method)
		{ }
		inline ParamExecImpl (const T1& t1, const T2& t2, const T3& t3, const T4& t4,std::function<void(IExecImpl*)> method)
			: mParam1 (t1), mParam2 (t2), mParam3 (t3), mParam4 (t4), mMethod (method)
		{ }
		virtual void Execute ()
		{
			mMethod (this);
		}
		virtual ~ParamExecImpl ()
		{
		}
	public:
		T1 mParam1;
		T2 mParam2;
		T3 mParam3;
		T4 mParam4;
		std::function<void(IExecImpl*)> mMethod;
	};

	static IExecImpl* CreateParamExecImpl (std::function<void()> method)
	{
		return LP_NEW (ParamExecImpl<char> ([method](IExecImpl *_impl) {
			method ();
		}));
	}

	template <typename T1>
	static IExecImpl* CreateParamExecImpl (const T1& t1, std::function<void(T1&)> method)
	{
		typedef ParamExecImpl<T1> IMPL;
		IMPL *impl = LP_NEW (IMPL (t1, [method](IExecImpl *_impl) { 
			IMPL *impl = (IMPL*)_impl;
			method (impl->mParam1);
		}));
		return impl;
	}

	template <typename T1, typename T2>
	static IExecImpl* CreateParamExecImpl (const T1& t1, const T2& t2, std::function<void(T1&,T2&)> method)
	{
		typedef ParamExecImpl<T1, T2> IMPL;
		IMPL *impl = LP_NEW (IMPL (t1, t2, [method](IExecImpl *_impl) { 
			IMPL *impl = (IMPL*)_impl;
			method (impl->mParam1, impl->mParam2);
		}));
		return impl;
	}

	template <typename T1, typename T2, typename T3>
	static IExecImpl* CreateParamExecImpl (const T1& t1, const T2& t2, const T3& t3, std::function<void(T1&,T2&,T3&)> method)
	{
		typedef ParamExecImpl<T1, T2, T3> IMPL;
		IMPL *impl = LP_NEW (IMPL (t1, t2, t3, [method](IExecImpl *_impl) { 
			IMPL *impl = (IMPL*)_impl;
			method (impl->mParam1, impl->mParam2, impl->mParam3);
		}));
		return impl;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static IExecImpl* CreateParamExecImpl (const T1& t1, const T2& t2, const T3& t3, const T4& t4, std::function<void(T1&,T2&,T3&,T4&)> method)
	{
		typedef ParamExecImpl<T1, T2, T3, T4> IMPL;
		IMPL *impl = LP_NEW (IMPL (t1, t2, t3, t4, [method](IExecImpl *_impl) { 
			IMPL *impl = (IMPL*)_impl;
			method (impl->mParam1, impl->mParam2, impl->mParam3, impl->mParam4);
		}));
		return impl;
	}
};

#endif //	LionX_LionX_Base_ExecImpl_H

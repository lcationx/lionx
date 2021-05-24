#ifndef LionX_LionX_Base_FunctionSlot_H
#define LionX_LionX_Base_FunctionSlot_H

#include "LionX.h"

//===========================================================================================
//	函式連結。
//===========================================================================================

namespace LionX
{
	class IFunctionSlotImpl
	{
	public:
		virtual Int32 operator () (const IRTTI* args) = 0;
		virtual ~IFunctionSlotImpl () { }
	};

	class CStaticFunctionSlot : public IFunctionSlotImpl
	{
	public:
		typedef Int32 (Function)(const IRTTI*);
	public:
		inline CStaticFunctionSlot (Function *fun)
			: mFunction (fun)
		{ }
		virtual Int32 operator () (const IRTTI* args)
		{
			return mFunction (args);
		}
	private:
		Function *mFunction;
	};

	template<typename T>
	class CClassFunctionSlot : public IFunctionSlotImpl
	{
	public:
		typedef Int32 (T::*Function)(const IRTTI*);
	public:
		inline CClassFunctionSlot (T *obj, Function fun)
			: mObj (obj), mFunction (fun)
		{ }
		virtual Int32 operator () (const IRTTI* args)
		{
			return (mObj->*mFunction) (args);
		}
	private:
		T *mObj;
		Function mFunction;
	};

	class CFunctionSlot : public CRef
	{
	public:
		inline CFunctionSlot ()
			: mFunctionSlotImpl (nullptr)
		{ }
		inline CFunctionSlot (CStaticFunctionSlot::Function *fun)
		{
			mFunctionSlotImpl = LP_NEW (CStaticFunctionSlot (fun));
		}
		template<typename T>
		inline CFunctionSlot (T *obj, Int32 (T::*function)(const IRTTI*))
		{
			mFunctionSlotImpl = LP_NEW (CClassFunctionSlot<T> (obj, function));
		}
		inline void SetImpl (CStaticFunctionSlot::Function *fun)
		{
			LP_SAFE_DELETE (mFunctionSlotImpl);
			mFunctionSlotImpl = LP_NEW (CStaticFunctionSlot (fun));
		}
		template<typename T>
		inline void SetImpl (T *obj, Int32 (T::*function)(const IRTTI*))
		{
			LP_SAFE_DELETE (mFunctionSlotImpl);
			mFunctionSlotImpl = LP_NEW (CClassFunctionSlot<T> (obj, function));
		}
		inline Int32 operator () (const IRTTI* args)
		{
			return (*mFunctionSlotImpl) (args);
		}
		inline bool IsConnected () const
		{
			return (mFunctionSlotImpl != 0);
		}
		inline void DeConnect ()
		{
			LP_SAFE_DELETE (mFunctionSlotImpl);
		}
		virtual ~CFunctionSlot () { LP_SAFE_DELETE (mFunctionSlotImpl); }
	private:
		IFunctionSlotImpl *mFunctionSlotImpl;
	};

};

#endif //	LionX_LionX_Base_FunctionSlot_H

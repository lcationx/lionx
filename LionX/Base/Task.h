#ifndef LionX_LionX_Base_Task_H
#define LionX_LionX_Base_Task_H

#include "Time.h"
#include "Coroutine.h"

//===========================================================================================
//	任務介面。
//===========================================================================================

namespace LionX
{
	class ITask : public ICoroutineBase
	{
	public:
		enum EType
		{
			TYPE_TASK = 0,
			TYPE_TIME_TASK = 1,
		};
	public:
		DECLARE_RTTI (TYPE_TASK);
	public:
		inline ITask ()
			: mAutoDeleted (true)
		{ }
		virtual ~ITask () {  }
	public:
		//	需注意IsValid傳回false但已執行一半的Task還是會繼續執行完畢 (需注意指針狀態)。
		virtual bool IsValid () = 0;
		virtual bool IsContinue () = 0;
	public:
		bool mAutoDeleted;
	private:
		friend class CApplication;
	};

	class ITimeTask : public ITask
	{
	public:
		DECLARE_RTTI (TYPE_TIME_TASK);
	public:
		inline ITimeTask (bool now = false)
			: mExecuteTime (now) { }
		inline CTime& ExecuteTime () { return mExecuteTime; }
		inline CTime const& ExecuteTime () const { return mExecuteTime; }
		virtual ~ITimeTask () { }
	protected:
		CTime mExecuteTime;
	};

};

#endif //	LionX_LionX_Base_Task_H

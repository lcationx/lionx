#ifndef LionX_LionX_Base_Event_H
#define LionX_LionX_Base_Event_H

#include "FunctionSlot.h"

//===========================================================================================
//	事件介面。
//===========================================================================================

namespace LionX
{
	class CEvent
	{
	public:
		inline CEvent (const std::string& name)
			: mName (name)
		{ }
		void Subscribe (CFunctionSlot *slot, bool front = false);
		void Unsubscribe (CFunctionSlot *slot);
		void operator () (const IRTTI* args);
		inline const std::string& GetName () const { return mName; }
		~CEvent ();
	private:
		std::string mName;
		std::deque < SmartPtr<CFunctionSlot> > mSlotContainer;
	};
};

#endif //	LionX_LionX_Base_Event_H

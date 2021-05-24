#ifndef LionX_LionX_Base_EventPool_H
#define LionX_LionX_Base_EventPool_H

#include "Event.h"

//===========================================================================================
//	事件池。
//===========================================================================================

namespace LionX
{
	class CEventPool
	{
	public:
		CEventPool ();
		void AddEvent (const std::string& name);
		void RemoveEvent (const std::string& name);
		void Subscribe (const std::string& name, CFunctionSlot *slot, bool front = false);
		void Unsubscribe (const std::string& name, CFunctionSlot *slot);
		virtual void FireEvent (const std::string& name, const IRTTI* args);
		inline bool IsEventPresent (const std::string& name) const { return (mAllEvents.find (name) != mAllEvents.end ()); }
		void RemoveAllEvents ();
		virtual ~CEventPool ();
	private:
		std::map<std::string, CEvent*, SFastStringLessCompare> mAllEvents;
	};


};

#endif //	LionX_LionX_Base_EventPool_H

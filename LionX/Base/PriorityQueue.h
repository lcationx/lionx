#ifndef LionX_LionX_Base_PriorityQueue_H
#define LionX_LionX_Base_PriorityQueue_H

#include "LionX.h"

//===========================================================================================
//	優先隊列。
//===========================================================================================

namespace LionX
{
	template <typename T, typename C, typename S>
	class PriorityQueue : public std::priority_queue<T, C, S>
	{
	public:
		inline PriorityQueue () { }
		inline C& iml () { return this->c; }
		virtual ~PriorityQueue () { }
	};

};

#endif //	LionX_LionX_Base_PriorityQueue_H

#ifndef LionX_LionX_Graphics_Cloner_H
#define LionX_LionX_Graphics_Cloner_H

#include "LionX.h"

//===========================================================================================
//	克隆。
//===========================================================================================

namespace LionX
{
	class CCloner
	{
	public:
		inline CCloner ()
		{ }
		virtual bool From (CCloner *cloner) { return false; }
		virtual CCloner* Clone () { return 0; }
		virtual ~CCloner () { }
	};
};

#endif //	LionX_LionX_Graphics_Cloner_H

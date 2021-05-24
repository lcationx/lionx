#ifndef LionX_LionX_Base_Union_H
#define LionX_LionX_Base_Union_H

#include "LionX.h"

//===========================================================================================
//	聯合體。
//===========================================================================================

namespace LionX
{
	template <typename T1, typename T2>
	class Union
	{
	public:
		//	建構式。
		inline Union () { }
		inline Union (const T1& t)
			: v (t) { }
		inline Union (const T2& t1, const T2& t2)
			: v1 (t1), v2 (t2) { }
		//	[]。
		inline T2& operator [] (int i) 
		{
			return (&v2)[1 - i];
		}
		inline T2 operator [] (int i) const 
		{
			return (&v2)[1 - i];
		}
		//	&。
		inline operator T1& () { return v; }
		inline operator T1 () const { return v; }
		//	解構式。
		inline ~Union () { }
	private:
		union { struct { T2 v2, v1; }; T1 v; };
	};
};

#endif //	LionX_LionX_Base_Union_H

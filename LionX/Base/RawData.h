#ifndef LionX_LionX_Base_RawData_H
#define LionX_LionX_Base_RawData_H

#include "LionX.h"

//===========================================================================================
//	原始數據。
//===========================================================================================

namespace LionX
{
	class CRawData : public CRef
	{
	public:
		inline CRawData ()
			: mData (0), mLength (0)
		{ }
		void SetData (const char *name, char *data, UInt32 length)
		{
			mName = name;
			LP_SAFE_DELETE_ARRAY (mData);
			mData = data;
			mLength = length;
		}
		inline void SetData (const std::string& name, char *data, UInt32 length) 
		{ 
			SetData (name.c_str (), data, length); 
		}
		virtual ~CRawData ()
		{
			LP_SAFE_DELETE_ARRAY (mData);
		}
	public:
		std::string mName;
		char *mData;
		UInt32 mLength;
	};

};

#endif //	LionX_LionX_Base_RawData_H

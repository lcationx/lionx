#ifndef LionX_LionX_Base_StreamData_H
#define LionX_LionX_Base_StreamData_H

#include "BinStream.h"

//===========================================================================================
//	位元數據流處理物件。
//===========================================================================================


namespace LionX
{
	class IStreamData
	{
	public:
		inline IStreamData () { }
		virtual void Serialize (COutBinStream& out) = 0;
		virtual void Deserialize (CInBinStream& in) = 0;
		virtual ~IStreamData () { }
	};
};

#endif //	LionX_LionX_Base_StreamData_H

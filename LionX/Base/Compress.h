#ifndef LionX_LionX_Base_Compress_H
#define LionX_LionX_Base_Compress_H

#include "RawData.h"

//===========================================================================================
//	壓縮工具。
//===========================================================================================

namespace LionX
{
	class ICompress
	{
	public:
		inline ICompress ()
		{ }
		virtual bool Compress (CRawData *raw_data) = 0;
		virtual bool Decompress (CRawData *raw_data) = 0;
		virtual ~ICompress ()
		{ }
	};

	class CZlibCompress : public ICompress
	{
	public:
		inline CZlibCompress ()
		{ }
		virtual bool Compress (CRawData *raw_data);
		virtual bool Decompress (CRawData *raw_data);
		virtual ~CZlibCompress ()
		{ }
	};



};

#endif //	LionX_LionX_Base_Compress_H

#ifndef LionX_LionX_Base_BinStream_H
#define LionX_LionX_Base_BinStream_H

#include "Stream.h"

//===========================================================================================
//	位元數據流。
//===========================================================================================

namespace LionX
{
	class COutBinStream : public COutStream
	{
	public:
		template<typename PB>
		friend bool FillOutBinStreamStream (COutBinStream& out, PB& pb_data)
		{
			if ( !pb_data.SerializeToArray ((out.mStream + out.mWriteIndex), out.GetRemainSize ()) )
				return false;
			out.mWriteIndex += pb_data.ByteSizeLong ();
			return true;
		}
	public:
		//	建構式。
		inline COutBinStream (char *stream = 0, UInt32 length = 0)
			: mStream (stream)
		{
			mLength = length;
		}
		//	填充資料。
		virtual void Fill (UInt32 size, bool zero = true);
		//	塞入數據。
		virtual void PutBinary (const char *src, UInt32 size);
		//	取出數據指針。
		const char* GetPtr () const;
		//	取出數據指針。
		const char* GetCurrentPtr () const;
		//	解構式。
		inline ~COutBinStream () { }
	private:
		char *mStream;
	};

	class CInBinStream : public CInStream
	{
	public:
		//	建構式。
		inline CInBinStream (const char *stream, UInt32 size)
			: mStream (stream)
		{
			mLength = size;
		}
		//	取出數據。
		virtual void GetBinary (char *dest, UInt32 size);
		//	取出數據指針。
		const char* GetPtr () const;
		//	取出數據指針。
		virtual const char* GetCurrentPtr () const;
		//	解構式。
		inline ~CInBinStream () { }
	private:
		const char *mStream;
	};
};

#endif //	LionX_LionX_Base_BinStream_H

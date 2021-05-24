#ifndef LionX_LionX_Network_NetPack_H
#define LionX_LionX_Network_NetPack_H

#include "Base/Allocator.h"

//===========================================================================================
//	網路數據包。
//===========================================================================================

namespace LionX
{
	class CNetPack
	{
	public:
		typedef UInt16 LengthType;
		static const UInt16 DataOffset = sizeof (LengthType);
		static const UInt16 BufferSize = 8192;
		static const UInt16 DataBufferSize = (BufferSize - DataOffset);
	public:
		inline CNetPack ()
			: mRef (0), mLink (0), mRemotePort (0), mRemoteNetID (0)
		{
		}
		inline void AddRef () { Atomic::LockedIncrement (&mRef); }
		void DecRef ();
		void Clone (CNetPack* pack);
		inline void SetLength (UInt16 length) { *(LengthType*)(mBuffer) = (LengthType)length; }
		inline LengthType GetLength () const { return *(LengthType*)(mBuffer); }
		inline LengthType GetTotalLength () const { return (*(LengthType*)(mBuffer)) + DataOffset; }
		inline char* GetBuffer () { return mBuffer; }
		inline char* GetData () { return &mBuffer[DataOffset]; }
		~CNetPack () { }
	public:
		char mBuffer [BufferSize];
		Int32 mRef;
		UInt16 mRemotePort;
		UInt32 mRemoteNetID;
		CNetPack *mLink;
	};
};


#endif //	LionX_LionX_Network_NetPack_H

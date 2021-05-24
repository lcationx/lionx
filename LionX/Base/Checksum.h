#ifndef LionX_LionX_Base_Checksum_H
#define LionX_LionX_Base_Checksum_H

#include "File.h"

//===========================================================================================
//	較驗值。
//===========================================================================================

namespace LionX
{
	class IChecksum
	{
	public:
		virtual UInt32 Checksum (const char *buf, UInt32 size) = 0;
	};

	class CCrc32 : public IChecksum
	{
	private:
		static bool mInit;
		static UInt32 mCrcTable [256];
	public:
		inline CCrc32 () { }
		virtual UInt32 Checksum (const char *buf, UInt32 size);
		virtual ~CCrc32 () { }
	private:
		void InitTable ();
	};

	template<typename TChecksum>
	class Checksum
	{
	public:
		static const UInt32 ChunkSize = 4096;
	public:
		UInt32 Get (const char *buf, UInt32 size)
		{
			return mChecksum.Checksum (buf, size);
		}
		UInt32 Get (CFile& file)
		{
			UInt32 pos = file.CursorPos ();
			file.Seek (CFile::FSO_SET, 0);
			char buf [ChunkSize];
			UInt32 fsize = file.Size (), rent_size = 0, size = 0;
			UInt32 crc = 0xFFFFFFFF;
			while (rent_size < fsize) {
				size = file.Read (buf, ChunkSize);
				if (size == 0)
					break;
				rent_size += size;
				crc = mChecksum.Checksum (buf, size);
			}
			file.Seek (CFile::FSO_SET, (Int32)pos);
			return crc;
		}
		UInt32 Get (const char *file_name) {
			CFile file;
			if ( !file.Open (file_name, CFile::READ | CFile::BIN) )
				return 0xFFFFFFFF;
			char buf [ChunkSize];
			UInt32 fsize = file.Size (), rent_size = 0, size = 0;
			UInt32 crc = 0xFFFFFFFF;
			while (rent_size < fsize) {
				size = file.Read (buf, ChunkSize);
				if (size == 0)
					break;
				rent_size += size;
				crc = mChecksum.Checksum (buf, size);
			}
			file.Close ();
			return crc;
		}
	private:
		TChecksum mChecksum;
	};
};

#endif //	LionX_LionX_Base_Checksum_H

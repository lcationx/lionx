#ifndef LionX_LionX_Base_File_H
#define LionX_LionX_Base_File_H

#include "LionX.h"

//===========================================================================================
//	檔案。
//===========================================================================================

namespace LionX
{
	enum EFileSeekOrigin
	{
		MAIS_SEEK_SET = SEEK_SET,
		MAIS_SEEK_CUR = SEEK_CUR,
		MAIS_SEEK_END = SEEK_END,
	};

	class CFile
	{
	public:
		static const int MaxFormatSize = 1024;
	public:
		enum
		{
			READ		= 0x0001,
			APPEND		= 0x0002,
			WRITE		= 0x0004,
			BIN			= 0x0010,
			UPDATE		= 0x0100,
		};
		enum EFileSeekOrigin
		{
			FSO_SET = SEEK_SET,
			FSO_CUR = SEEK_CUR,
			FSO_END = SEEK_END,
		};
	public:
		inline CFile ()
			: mFD (0), mFlags (0)
		{ }
		bool Open (const char *file_name, UInt16 flags);
		inline bool Open (const std::string& file_name, UInt16 flags) { return Open (file_name.c_str (), flags); }
		UInt32 Write (const char *src, UInt32 size);
		UInt32 Read (char *dest, UInt32 dest_size);
		UInt32 Fill (UInt32 size, bool zero = false);
		bool Seek (EFileSeekOrigin origin, Int32 offset);
		bool PutString (const char *str);
		bool PutFormatString (const char *cmd, ...);
		bool Flush ();
		bool GetLineString (char *dest, Int32 dest_size);
		bool GetLineString (std::string& dest);
		UInt32 CursorPos ();
		UInt32 Size ();
		void Close ();
		inline ~CFile () { Close (); }
	public:
		inline bool IsExist () const { return (mFD != 0); }
		inline std::string const& GetFileName () const { return mFileName; }
		inline UInt16 GetFlags () const { return mFlags; }
		inline bool PutString (const std::string& str) { return PutString (str.c_str ()); }
	private:
		FILE *mFD;
		std::string mFileName;
		UInt16 mFlags;
	};

	//	模板讀取。
	template <typename T>
	bool operator >> (CFile& file, T& dest)
	{
		return (file.Read ((char*)&dest, sizeof (T)) == sizeof (T));
	}

	//	模板寫入。
	template <typename T>
	bool operator << (CFile& file, T& src)
	{
		return (file.Write ((const char*)&src, sizeof (T)) == sizeof (T));
	}
};

#endif //	LionX_LionX_Base_File_H

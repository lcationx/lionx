#ifndef LionX_LionX_Base_TextStream_H
#define LionX_LionX_Base_TextStream_H

#include "LionX.h"

//===========================================================================================
//	文本數據流。
//===========================================================================================

namespace LionX
{
	class CTextInStream
	{
	public:
		inline CTextInStream (const char *text = nullptr, char mask = 0)
			: mReadIndex (0) 
		{ 
			if (text != nullptr)
				SetText (text, mask); 
		}
		bool SetText (const char *text, char mask);
		inline bool SetText (const std::string& text, char mask) { return SetText (text.c_str (), mask); }
		inline UInt32 GetColumns () const { return (UInt32)mSection.size (); }
		inline void Skip (UInt32 size) { mReadIndex += size; }
		//	資料流。
		CTextInStream& operator >> (char& dest);
		CTextInStream& operator >> (unsigned char& dest);
		CTextInStream& operator >> (Int16& dest);
		CTextInStream& operator >> (UInt16& dest);
		CTextInStream& operator >> (Int32& dest);
		CTextInStream& operator >> (UInt32& dest);
		CTextInStream& operator >> (Int64& dest);
		CTextInStream& operator >> (UInt64& dest);
		CTextInStream& operator >> (float& dest);
		CTextInStream& operator >> (double& dest);
		//	特殊資料流。
		CTextInStream& operator >> (std::string& dest);
		CTextInStream& operator >> (char* dest);
		inline bool IsOver () const { return (mReadIndex >= (UInt32)mSection.size ()); }
		void Clear ();
		inline ~CTextInStream () { Clear (); }
	private:
		UInt32 mReadIndex;
		std::vector<std::string> mSection;
	};

	class CTextOutStream
	{
	public:
		inline CTextOutStream (const char* mask = ",")
			: mMask (mask), mColumns (0)
		{ }
		void SetMask (const char* mask);
		inline void SetMask (const std::string& mask) { SetMask (mask.c_str ()); }
		inline UInt32 GetColumns () const { return mColumns; }
		//	資料流。
		CTextOutStream& operator << (const char& dest);
		CTextOutStream& operator << (const unsigned char& dest);
		CTextOutStream& operator << (const Int16& dest);
		CTextOutStream& operator << (const UInt16& dest);
		CTextOutStream& operator << (const Int32& dest);
		CTextOutStream& operator << (const UInt32& dest);
		CTextOutStream& operator << (const Int64& dest);
		CTextOutStream& operator << (const UInt64& dest);
		CTextOutStream& operator << (const float& dest);
		CTextOutStream& operator << (const double& dest);
		//	特殊資料流。
		CTextOutStream& operator << (const std::string& dest);
		CTextOutStream& operator << (const char* dest);
		inline const std::string& GetMask () const { return mMask; }
		inline const std::string& GetStream () const { return mStream; }
		void Clear ();
		inline ~CTextOutStream () {  }
	private:
		std::string mMask;
		UInt32 mColumns;
		std::string mStream;
	};
};

#endif //	LionX_LionX_Base_TextStream_H

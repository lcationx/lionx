#ifndef LionX_LionX_Base_Stream_H
#define LionX_LionX_Base_Stream_H

#include "LionX.h"

//===========================================================================================
//	數據流。
//===========================================================================================

namespace LionX
{
	class COutStream
	{
	public:
		//	建構式。
		inline COutStream ()
			: mLength (0), mWriteIndex (0)
		{ }
		//	填充資料。
		virtual void Fill (UInt32 size, bool zero = true) = 0;
		//	塞入數據。
		virtual void PutBinary (const char *src, UInt32 size) = 0;
		//	解構式。
		inline ~COutStream () { }
	public:
		//	資料流。
		inline COutStream& operator << (const char& src)			{ PutBinary ((char*)&src, sizeof (char)); return *this; }
		inline COutStream& operator << (const unsigned char& src)	{ PutBinary ((char*)&src, sizeof (unsigned char)); return *this; }
		inline COutStream& operator << (const Int16& src)			{ PutBinary ((char*)&src, sizeof (Int16)); return *this; }
		inline COutStream& operator << (const UInt16& src)			{ PutBinary ((char*)&src, sizeof (UInt16)); return *this; }
		inline COutStream& operator << (const Int32& src)			{ PutBinary ((char*)&src, sizeof (Int32)); return *this; }
		inline COutStream& operator << (const UInt32& src)			{ PutBinary ((char*)&src, sizeof (UInt32)); return *this; }
		inline COutStream& operator << (const Int64& src)			{ PutBinary ((char*)&src, sizeof (Int64)); return *this; }
		inline COutStream& operator << (const UInt64& src)			{ PutBinary ((char*)&src, sizeof (UInt64)); return *this; }
		inline COutStream& operator << (const float& src)			{ PutBinary ((char*)&src, sizeof (float)); return *this; }
		inline COutStream& operator << (const double& src)			{ PutBinary ((char*)&src, sizeof (double)); return *this; }
		//	特殊資料流。
		COutStream& operator << (const std::string& src);
		COutStream& operator << (const char* src);
		COutStream& operator << (const std::wstring& src);
		COutStream& operator << (const wchar_t* src);
		//	是否超長。
		inline bool IsOver () const { return (mWriteIndex > mLength); }
		//	取出寫入長度。
		inline UInt32 GetWriteIndex () const { return mWriteIndex; }
		//	取出剩餘長度。
		inline Int32 GetRemainSize () const { return (Int32)(mLength - mWriteIndex); }
	protected:
		UInt32 mLength, mWriteIndex;
	};
	//	模板寫入。
	template <typename T>
	COutStream& operator << (COutStream& stream, const T& src)
	{
		stream.PutBinary ((char*)&src, sizeof (T));
		return stream;
	}
	//	模板vector寫入。
	template <typename T>
	COutStream& operator << (COutStream& stream, std::vector<T>& src)
	{
		UInt16 size = (UInt16) src.size ();
		stream << size;
		for (UInt16 i = 0; i < size; ++ i) stream << src[i];
		return stream;
	}
	//	模板list寫入。
	template <typename T>
	COutStream& operator << (COutStream& stream, std::list<T>& src)
	{
		UInt16 size = (UInt16) src.size ();
		stream << size;
		typename std::list<T>::iterator list_it;
		for (list_it = src.begin (); list_it != src.end (); ++ list_it) {
			stream << (*list_it);
		}
		return stream;
	}
	//	模板set寫入。
	template <typename T>
	COutStream& operator << (COutStream& stream, std::set<T>& src)
	{
		UInt16 size = (UInt16) src.size ();
		stream << size;
		typename std::set<T>::iterator it;
		for (it = src.begin (); it != src.end (); ++ it) {
			stream << (*it);
		}
		return stream;
	}
	//	模板pait寫入。
	template <typename A, typename B>
	COutStream& operator << (COutStream& stream, std::pair<A, B>& src)
	{
		stream << src.first;
		stream << src.second;
		return stream;
	}
	//	模板map寫入。
	template <typename A, typename B>
	COutStream& operator << (COutStream& stream, std::map<A, B>& src)
	{
		UInt16 size = (UInt16) src.size ();
		stream << size;
		typename std::map<A, B>::iterator it;
		for (it = src.begin (); it != src.end (); ++ it) {
			stream << it->first;
			stream << it->second;
		}
		return stream;
	}
	class CInStream
	{
	public:
		//	建構式。
		inline CInStream ()
			: mLength (0), mReadIndex (0)
		{ }
		//	取出數據。
		virtual void GetBinary (char *dest, UInt32 size) = 0;
		//	解構式。
		inline ~CInStream () { }
	public:
		//	資料流。
		inline CInStream& operator >> (char& dest)				{ GetBinary ((char*)&dest, sizeof (char)); return *this; }
		inline CInStream& operator >> (unsigned char& dest)		{ GetBinary ((char*)&dest, sizeof (unsigned char)); return *this; }
		inline CInStream& operator >> (Int16& dest)				{ GetBinary ((char*)&dest, sizeof (Int16)); return *this; }
		inline CInStream& operator >> (UInt16& dest)			{ GetBinary ((char*)&dest, sizeof (UInt16)); return *this; }
		inline CInStream& operator >> (Int32& dest)				{ GetBinary ((char*)&dest, sizeof (Int32)); return *this; }
		inline CInStream& operator >> (UInt32& dest)			{ GetBinary ((char*)&dest, sizeof (UInt32)); return *this; }
		inline CInStream& operator >> (Int64& dest)				{ GetBinary ((char*)&dest, sizeof (Int64)); return *this; }
		inline CInStream& operator >> (UInt64& dest)			{ GetBinary ((char*)&dest, sizeof (UInt64)); return *this; }
		inline CInStream& operator >> (float& dest)				{ GetBinary ((char*)&dest, sizeof (float)); return *this; }
		inline CInStream& operator >> (double& dest)			{ GetBinary ((char*)&dest, sizeof (double)); return *this; }
		//	特殊資料流。
		CInStream& operator >> (std::string& dest);
		CInStream& operator >> (char* dest);
		CInStream& operator >> (std::wstring& dest);
		CInStream& operator >> (wchar_t* dest);
		//	取出數據指針。
		virtual const char* GetCurrentPtr () const = 0;
		//	忽略資料。
		inline void Skip (UInt32 size) { mReadIndex += size; }
		//	是否存取越界。
		inline bool IsOver () const { return (mReadIndex > mLength); }
		//	是否存取完整。
		inline bool IsCompleted () const { return (mReadIndex == mLength); }
		//	直接結束。
		inline void ToFinish () { mReadIndex = mLength; }
		//	取出讀取位置。
		inline UInt32 GetReadIndex () const { return mReadIndex; }
		//	取出數據長度。
		inline UInt32 GetLength () const { return mLength; }
		//	取出剩餘數據長度。
		inline Int32 GetRemainSize () const { return (Int32)(mLength - mReadIndex); }
	protected:
		UInt32 mLength, mReadIndex;
	};
	//	模板讀取。
	template <typename T>
	CInStream& operator >> (CInStream& stream, T& dest)
	{
		stream.GetBinary ((char*)&dest, sizeof (T));
		return stream;
	}
	//	模板vector讀取。
	template <typename T>
	CInStream& operator >> (CInStream& stream, std::vector<T>& dest)
	{
		UInt16 size;
		T value;
		stream >> size;
		while (size-- > 0) {
			stream >> value;
			dest.push_back (value);
		}
		return stream;
	}
	//	模板list讀取。
	template <typename T>
	CInStream& operator >> (CInStream& stream, std::list<T>& dest)
	{
		UInt16 size;
		T value;
		stream >> size;
		while (size-- > 0) {
			stream >> value;
			dest.push_back (value);
		}
		return stream;
	}
	//	模板set讀取。
	template <typename T>
	CInStream& operator >> (CInStream& stream, std::set<T>& dest)
	{
		UInt16 size;
		T value;
		stream >> size;
		while (size-- > 0) {
			stream >> value;
			dest.insert (value);
		}
		return stream;
	}
	//	模板pair讀取。
	template <typename A, typename B>
	CInStream& operator >> (CInStream& stream, std::pair<A, B>& dest)
	{
		stream >> dest.first;
		stream >> dest.second;
		return stream;
	}
	//	模板map讀取。
	template <typename A, typename B>
	CInStream& operator >> (CInStream& stream, std::map<A, B>& dest)
	{
		UInt16 size;
		A key;
		B value;
		stream >> size;
		while (size-- > 0) {
			stream >> key;
			stream >> value;
			dest.insert (std::pair<A,B>(key, value));
		}
		return stream;
	}
};

#endif //	LionX_LionX_Base_Stream_H

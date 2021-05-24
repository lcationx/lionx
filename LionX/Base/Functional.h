#ifndef LionX_LionX_Base_Functional_H
#define LionX_LionX_Base_Functional_H


//===========================================================================================
//	功能函式。
//===========================================================================================

namespace LionX
{
	//===========================================================================================
	//	字串相關。
	//===========================================================================================

	//	計算字元寬數 (半形為1 全形為2)。
	Int32 NumWideChars (const char *str);
	//	計算字元數。
	Int32 NumChars (const char *str);
	//	分割字元。
	Int32 SpliChar (const char *str, std::vector<std::string>& out);
	//	分切字串。
	Int32 SplitString (const char *str, char delimit, std::vector<std::string>& out, bool keep_delimit = false);
	//	分切字串。
	Int32 SplitString (const char *str, const char *delimit, std::vector<std::string>& out, bool keep_delimit = false);
	//	分切字串。
	Int32 SplitString (const char *str, const std::set<char>& delimits, std::vector<std::string>& out, bool keep_delimit = false);
	//	格式化字串。
	Int32 Sprintf (char *buf, UInt32 size, const char *cmd, ...);
	//	格式化字串。
	const char* LSprintf (const char *cmd, ...);
	//	轉小寫字母。
	std::string& ToLowerChar (std::string& str);
	//	轉大寫字母。
	std::string& ToUpperChar (std::string& str);
	//	是否為數字。
	bool StringIsNumber (const std::string& str);
	//	是否為浮數點數值。
	bool StringIsFloat (const std::string& str);
	//	是否為ASCII碼。
	bool IsAscii (const std::string& str);
	//	是否為數字+字母。
	bool IsAlphaOrNomber (const std::string& str);
	//	是否為信箱。
	bool IsMail (const std::string& str);
	//	尋找字串。
	Int32 FindString (const std::string& src, const std::string& key, UInt32 begin_pos);
	//	模糊比對。
	bool FuzzyCompare (const std::string& text, const std::string& key);
	//	檢測SQL Injection。
	bool CatchSQLInjection (const std::string& sql);
	//	分解IP字串。
	bool IPAnalyzeRange4 (const std::string& ip, UInt32& min_net_number, UInt32& max_net_number);
	//	分解IP字串。
	UInt32 IPAnalyze (const std::string& ip);
	//	補齊檔案路徑格式。
	inline void FullPathString (std::string& str)
	{
		if (str.length () > 0 && str [str.length () - 1] != '/' && str [str.length () - 1] != '\\')
			str += "/";
	}
	//	產生完整檔案路徑。
	inline std::string FullPathString (const std::string& path, const std::string& file_name)
	{
		std::string str = path;
		if (str.length () > 0 && str [str.length () - 1] != '/' && str [str.length () - 1] != '\\')
			str += "/";
		return str + file_name;
	}
	//	字串快速排序。
	struct SFastStringLessCompare
	{
	public:
		inline bool operator () (const std::string& s1, const std::string& s2) const
		{
			if (s1.length () == s2.length ())
				return (memcmp (s1.c_str (), s2.c_str (), s1.length ()) < 0);
			return (s1.length () < s2.length ());
		}
	};
	//	給定範圍內尋找字串。
	const char* FindString (const char *src, const char *key, UInt32 len);
	//	將數值轉換成為16進制字串。
	const char* HexArrayToString (const char *hex_value, UInt32 len);


	//	分切字串。
	Int32 UTF_SplitString (const wchar_t *str, wchar_t delimit, std::vector<std::wstring>& out, bool keep_delimit = false);
	//	分切字串。
	Int32 UTF_SplitString (const wchar_t *str, const std::set<wchar_t>& delimits, std::vector<std::wstring>& out, bool keep_delimit = false);
	//	格式化字串。
	Int32 UTF_Sprintf (wchar_t *buf, UInt16 size, const wchar_t *cmd, ...);
	//	格式化字串。
	const wchar_t* UTF_LSprintf (const wchar_t *cmd, ...);
	//	轉小寫字母。
	void UTF_LowerChar (std::wstring& str);
	//	轉大寫字母。
	void UTF_UpperChar (std::wstring& str);

	//	UTF8轉UTF32。
	UTF32 UTF8toUTF32 (const char *str);
	//	UTF8轉UTF32。
	bool UTF8toUTF32 (const char *begin, const char *end, UTF32String& out);
	//	UTF8轉UTF32。
	inline bool UTF8toUTF32 (const std::string& src, UTF32String& out) { return UTF8toUTF32 (src.c_str (), src.c_str () + src.length (), out); }
	//	UTF32轉UTF8。
	bool UTF32toUTF8 (UTF32 utf32, std::string& out);
	//	UTF32轉UTF8。
	bool UTF32toUTF8 (const UTF32 *begin, const UTF32 *end, std::string& out);
	//	UTF32轉UTF8。
	inline bool UTF32toUTF8 (const UTF32String& src, std::string& out) { return UTF32toUTF8 (src.c_str (), src.c_str () + src.length (), out); }
	//	UTF32轉UTF16。
	bool UTF32toUTF16 (const UTF32 *begin, const UTF32 *end, UTF16String& out);
	//	UTF32轉UTF8。
	inline bool UTF32toUTF16 (const UTF32String& src, UTF16String& out) { return UTF32toUTF16 (src.c_str (), src.c_str () + src.length (), out); }
	//	UTF16轉UTF32。
	bool UTF16toUTF32 (const UTF16 *begin, const UTF16 *end, UTF32String& out);
	//	UTF32轉UTF8。
	inline bool UTF16toUTF32 (const UTF16String& src, UTF32String& out) { return UTF16toUTF32 (src.c_str (), src.c_str () + src.length (), out); }


	//===========================================================================================
	//	系統。
	//===========================================================================================

	//	移除檔案。
	bool RemoveFile (const char *file_name);
	//	獲取檔案路徑資訊。
	void SplitPath (const char *full_path, std::string& path, std::string& name, std::string& ext);
	//	移除檔案。
	bool UTF_RemoveFile (const wchar_t *file_name);
	//	獲取檔案路徑資訊。
	void UTF_SplitPath (const wchar_t *full_path, std::wstring& path, std::wstring& name, std::wstring& ext);


	//===========================================================================================
	//	hash key。
	//===========================================================================================

	typedef UInt32 (*HashKeyFunction) (const char*, UInt32);

	//	FNV。
	UInt32 FNV_HashKey (const char *buf, UInt32 size);
	//	RS。
	UInt32 RS_HashKey (const char *buf, UInt32 size);
	//	JS。
	UInt32 JS_HashKey (const char *buf, UInt32 size);
	//	ELF。
	UInt32 ELF_HashKey (const char *buf, UInt32 size);
	//	BKDR。
	UInt32 BKD_RHashKey (const char *buf, UInt32 size);
	//	SDBM。
	UInt32 SDBM_HashKey (const char *buf, UInt32 size);
	//	DJB。
	UInt32 DJB_HashKey (const char *buf, UInt32 size);

	//	產生64bit的hash key。
	inline UInt64 HashKey64 (const char *buf, UInt32 size, HashKeyFunction fun1 = DJB_HashKey, HashKeyFunction fun2 = FNV_HashKey) { return (((UInt64)fun1 (buf, size)) << 32 | fun2 (buf, size)); }

	//===========================================================================================
	//	Other。
	//===========================================================================================

	//	獲取類別名稱。
	template <typename T>
	inline const char* GetClassName (const T *x) { return typeid (*x).name (); }
	//	兩者交換。
	template <typename T>
	inline void SWAP (T& v1, T& v2) { T t = v1; v1 = v2; v2 = t; }
	//	判斷記憶體格式。
	bool IsLittleEndian ();
	//	指針高低位元轉換。
	inline Int16 PtrSwapToInt16 (const void *ptr)	{ return (Int16) SWAP_INT16 (*(Int16*)(ptr)); }
	inline Int32 PtrSwapToInt32 (const void *ptr)	{ return (Int32) SWAP_INT32 (*(Int32*)(ptr)); }
	inline UInt16 PtrSwapToUInt16 (const void *ptr)	{ return (UInt16) SWAP_INT16 (*(UInt16*)(ptr)); }
	inline UInt32 PtrSwapToUInt32 (const void *ptr)	{ return (UInt32) SWAP_INT32 (*(UInt32*)(ptr)); }
	//	產生GUID。
	void GenGUID (char *guid);
	//	產生Ticket-32。
	void GenTicket32 (char *ticket);
	//	產生Ticket-64。
	void GenTicket64 (char *ticket);
	//	產生Ticket-128。
	void GenTicket128 (char *ticket);
	//	產生Ticket-256。
	void GenTicket256 (char *ticket);
	//	計算Base64編碼字串長度。
	UInt32 SizeOfEncodeBase64 (UInt32 data_size);
	//	Base64編碼。
	UInt32 EncodeBase64 (char *out, UInt32 out_size, const char *src, UInt32 src_size);
	//	Base64解碼。
	bool DecodeBase64 (char *data, UInt32& in_out_size);
	//	SHA256編碼。
	std::string EncodeSHA256 (const std::string str);

	//===========================================================================================
	//	net value。
	//===========================================================================================

	class RUInt16
	{
	public:
		inline RUInt16 (UInt16 v = 0)
			: mValue (PtrSwapToUInt16 (&v))
		{ }
		inline operator UInt16 () { return PtrSwapToUInt16 (&mValue); }
		inline RUInt16& operator = (UInt16 v) { mValue = PtrSwapToUInt16 (&v); return *this; }
		inline ~RUInt16 () { }
	public:
		UInt16 mValue;
	};

	class RUInt32
	{
	public:
		inline RUInt32 (UInt32 v = 0)
			: mValue (PtrSwapToUInt32 (&v))
		{ }
		inline operator UInt32 () { return PtrSwapToUInt32 (&mValue); }
		inline RUInt32& operator = (UInt32 v) { mValue = PtrSwapToUInt32 (&v); return *this; }
		inline ~RUInt32 () { }
	public:
		UInt32 mValue;
	};

	//===========================================================================================
	//===========================================================================================
};

#endif //	LionX_LionX_Base_Functional_H

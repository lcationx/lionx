#ifndef LionX_LionX_Base_Directory_H
#define LionX_LionX_Base_Directory_H

#include "LionX.h"

//===========================================================================================
//	資料夾操作。
//===========================================================================================

namespace LionX
{
	class CDirectory
	{
	public:
		struct SObject
		{
		public:
			std::string mName, mParentName;
			bool mIsDirectory;
		public:
			inline SObject ()
				: mName (""), mParentName (""), mIsDirectory (false)
			{ }
		};
	public:
		inline CDirectory (const char *dir_name = "")
			: mName (dir_name)
		{ }
		inline CDirectory (const std::string& dir_name)
			: mName (dir_name)
		{ }
		inline std::string const& GetName () const { return mName; }
		bool IsExist () const;
		bool MakeDir ();
		bool Back ();
		void Remove ();
		void AnalyzeNames (std::vector<std::string>& out_vec) const;
		UInt32 GetDirectoryObjects (std::vector<SObject>& out_vec, const std::string& pattern = "") const;
		UInt32 GetAllDirectoryObjects (std::vector<SObject>& out_vec, const std::string& pattern = "") const;
		UInt32 GetDirectorys (std::vector<SObject>& out_vec, const std::string& pattern = "") const;
		UInt32 GetAllDirectorys (std::vector<SObject>& out_vec, const std::string& pattern = "") const;
		inline ~CDirectory () { }
	public:
		inline CDirectory& operator = (const char *str)				{ mName = str; return *this; }
		inline CDirectory& operator = (const std::string& str)		{ mName = str; return *this; }
		inline CDirectory& operator = (const CDirectory& dir)		{ mName = dir.mName; return *this; }
	public:
		CDirectory& operator / (const char *path);
		CDirectory& operator / (const std::string& path);
		CDirectory& operator / (const CDirectory& path);
		bool operator == (const CDirectory& dir);
		bool operator != (const CDirectory& dir);
	private:
		std::string mName;
	};
};

#endif //	LionX_LionX_Base_Directory_H

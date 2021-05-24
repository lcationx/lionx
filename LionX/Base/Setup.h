#ifndef LionX_LionX_Base_Setup_H
#define LionX_LionX_Base_Setup_H

#include "RawData.h"

//===========================================================================================
//	設定資訊。
//===========================================================================================

namespace LionX
{
	class CSetup
	{
	public:
		struct SLabel
		{
		public:
			std::string mName;
			std::map <std::string, std::string> mInfos;
		};
	public:
		CSetup (const std::string& base_label_name = "Global");
		bool FromFile (const std::string& file_name);
		inline const std::map<std::string, SLabel*>& GetLabels () const { return mLabels; }
		inline const std::map<std::string, std::string> GetInfos () const { return mFocus->mInfos; }
		void AddLabel (const std::string& label_name);
		bool SetFocusLabel (const std::string& label_name);
		bool Save (const std::string& file_name);
		void Release ();
		~CSetup ();
	public:
		inline Int16 GetInt16 (const std::string& key) const
		{
			Int16 v;
			sscanf ((*this)[key].c_str (), "%hd", &v);
			return v;
		}
		inline UInt16 GetUInt16 (const std::string& key) const
		{
			UInt16 v;
			sscanf ((*this)[key].c_str (), "%hu", &v);
			return v;
		}
		inline Int32 GetInt32 (const std::string& key) const
		{
			Int32 v;
			sscanf ((*this)[key].c_str (), "%d", &v);
			return v;
		}
		inline UInt32 GetUInt32 (const std::string& key) const
		{
			UInt32 v;
			sscanf ((*this)[key].c_str (), "%u", &v);
			return v;
		}
		inline Int64 GetInt64 (const std::string& key) const
		{
			Int64 v;
			sscanf ((*this)[key].c_str (), "%lld", &v);
			return v;
		}
		inline UInt64 GetUInt64 (const std::string& key) const
		{
			UInt64 v;
			sscanf ((*this)[key].c_str (), "%llu", &v);
			return v;
		}
		inline float GetFloat (const std::string& key) const
		{
			float v;
			sscanf ((*this)[key].c_str (), "%f", &v);
			return v;
		}
		inline std::string& operator [] (const std::string& key) 
		{ 
			return mFocus->mInfos [key];
		}
		inline const std::string& operator [] (const std::string& key) const
		{
			static std::string v ("");
			std::map<std::string, std::string>::const_iterator it = mFocus->mInfos.find (key);
			if (it != mFocus->mInfos.end ())
				return it->second;
			return v;
		}
	public:
		bool Get (const std::string& key, Int16& value) const;
		bool Get (const std::string& key, UInt16& value) const;
		bool Get (const std::string& key, Int32& value) const;
		bool Get (const std::string& key, UInt32& value) const;
		bool Get (const std::string& key, Int64& value) const;
		bool Get (const std::string& key, UInt64& value) const;
		bool Get (const std::string& key, float& value) const;
		bool Get (const std::string& key, double& value) const;
		bool Get (const std::string& key, std::string& value) const;
	private:
		SLabel *mFocus;
		std::string mBaseLabelName;
		std::map<std::string, SLabel*> mLabels;
	};
};

#endif //	LionX_LionX_Base_Setup_H

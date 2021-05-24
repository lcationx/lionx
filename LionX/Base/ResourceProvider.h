#ifndef LionX_LionX_Base_ResourceProvider_H
#define LionX_LionX_Base_ResourceProvider_H

#include "RawData.h"

//===========================================================================================
//	資源提供者。
//===========================================================================================

namespace LionX
{
	class IResourceProvider
	{
	public:
		inline IResourceProvider ()
		{ }
		virtual CRawData* LoadData (const char* data_name) { return nullptr; }
		inline CRawData* LoadData (const std::string& data_name) { return LoadData (data_name.c_str ()); }
		virtual ~IResourceProvider () 
		{ }
	public:
		inline void SetDefaultPath (const std::string& default_path) { mDefaultPath = default_path; FullPathString (mDefaultPath); }
		inline const std::string& GetDefaultPath () const { return mDefaultPath; }
	protected:
		std::string mDefaultPath;
	};

	typedef TSingleton<IResourceProvider> ResourceProvider;
#define LP_ResourceProvider ResourceProvider::Ins()
};

#endif //	LionX_LionX_Base_ResourceProvider_H

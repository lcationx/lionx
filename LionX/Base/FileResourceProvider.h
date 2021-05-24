#ifndef LionX_LionX_Base_FileResourceProvider_H
#define LionX_LionX_Base_FileResourceProvider_H

#include "ResourceProvider.h"

//===========================================================================================
//	資源提供者 (檔案)。
//===========================================================================================

namespace LionX
{
	class CFileResourceProvider : public IResourceProvider
	{
	public:
		CFileResourceProvider ();
		virtual CRawData* LoadData (const char *data_name);
		virtual ~CFileResourceProvider ();
	};
};

#endif //	LionX_LionX_Base_FileResourceProvider_H

#ifndef LionX_LionX_Base_Font_H
#define LionX_LionX_Base_Font_H

#include "LionX.h"

//===========================================================================================
//	字型介面。
//===========================================================================================

namespace LionX
{
	class IFont : public CRef
	{
	public:
		IFont () { }
		virtual bool IsCharExist (UTF32 key) = 0;
		virtual bool GetCharPixel (UTF32 key, UInt16 height, UInt16& width, unsigned char *out_pixel) = 0;
		virtual ~IFont () { }
	private:
		DECLARE_PUB_PARAM (std::string, Name);
	};

	class CFontSet : public CRef
	{
	public:
		enum EFileType
		{
			FT_TTF	= 0,
		};
	public:
		static CFontSet* Create (const std::string& font_name, EFileType file_type, const std::string& path, const std::string& file_name);
	public:
		CFontSet (const std::string& name);
		void AddFont (IFont *font, bool front = false);
		bool IsCharExist (UTF32 key);
		bool GetCharPixel (UTF32 key, UInt16 height, UInt16& width, unsigned char *out_pixel);
		virtual ~CFontSet ();
	private:
		std::deque < SmartPtr<IFont> > mAllFonts;
		DECLARE_PUB_PARAM (std::string, Name);
	};
};

#endif //	LionX_LionX_Base_Font_H

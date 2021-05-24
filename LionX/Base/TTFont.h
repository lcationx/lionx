#ifndef LionX_LionX_Base_TTFont_H
#define LionX_LionX_Base_TTFont_H

#include "Font.h"
#include "RawData.h"

//===========================================================================================
//	TrueType字型。
//===========================================================================================

namespace LionX
{
	class CTTFont : public IFont
	{
	public:
		struct STTFontInfo
		{
		public:
			unsigned char *mData;
			Int32 mFontStart;
			Int32 mNumGlyphs;
			Int32 mLoca, mHead, mGlyf, mHhea, mHmtx;
			Int32 mIndexMap;
			Int32 mIndexToLocFormat;
		public:
			inline STTFontInfo ()
				: mData (0), mFontStart (0), mNumGlyphs (0), mLoca (0), mHead (0), mGlyf (0), mHhea (0), mHmtx (0), mIndexMap (0), mIndexToLocFormat (0)
			{ }
		};
	public:
		CTTFont ();
		bool Load (const char *name, CRawData *raw_data);
		inline bool Load (const std::string& name, CRawData *raw_data) { return Load (name.c_str (), raw_data); }
		virtual bool IsCharExist (UTF32 key);
		virtual bool GetCharPixel (UTF32 key, UInt16 height, UInt16& width, unsigned char *out_pixel);
		virtual ~CTTFont ();
	private:
		STTFontInfo mTTFInfo;
	};
};

#endif //	LionX_LionX_Base_TTFont_H

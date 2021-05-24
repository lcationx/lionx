#ifndef LionX_LionX_Base_XmlStream_H
#define LionX_LionX_Base_XmlStream_H

#include "ResourceProvider.h"

//===========================================================================================
//	Xml數據。
//===========================================================================================

namespace LionX
{
	class CXmlLabel
	{
	public:
		CXmlLabel (const std::string& name);
		void AddParam (const std::string& title, const std::string& value);
		void AddLabel (CXmlLabel *label);
		inline const std::vector<CXmlLabel*>& GetChildren () const { return mChildren; }
		inline const std::vector< std::pair<std::string, std::string> >& GetAllParams () const { return mParams; }
		inline const std::string& GetName () const { return mName; }
		~CXmlLabel ();
	private:
		std::string mName;
		std::vector<CXmlLabel*> mChildren;
		std::vector< std::pair<std::string, std::string> > mParams;
	};

	class CXmlStream
	{
	public:
		CXmlStream ();
		bool LoadFromRawData (const CRawData *raw_data);
		bool LoadFromFile (const std::string& file_name);
		bool LoadFromString (const std::string& sources);
		void Clear ();
		void AddLabel (CXmlLabel *label);
		inline const std::vector<CXmlLabel*>& GetLabels () const { return mLabels; }
		bool SaveFile (const std::string& file_name);
		~CXmlStream ();
	private:
		std::vector<CXmlLabel*> mLabels;
	};

};

#endif //	LionX_LionX_Base_XmlStream_H

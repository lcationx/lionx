#ifndef LionX_GameDB_Other_BasicQuery_H
#define LionX_GameDB_Other_BasicQuery_H

#include "File.h"
#include "TextStream.h"

//===========================================================================================
//	設定檔查詢模板。
//===========================================================================================

namespace LionX
{
	template <typename TId, typename TData>
	class BasicQuery
	{
	public:
		typedef std::map<TId, TData*> ConType;
		typedef typename ConType::iterator iterator;
		typedef typename ConType::const_iterator const_iterator;
	public:
		inline BasicQuery () { }

		virtual bool CheckVersion (const std::string& ver) = 0;
		virtual void Deserialize (CTextInStream& stream, TId& id, TData*& data) = 0;

		bool LoadDB (const char *file_name)
		{
			if (file_name == 0) {
				LP_BaseLogger->Append ("FAIL:BasicQuery load db but file_name is null.");
				return false;
			}
			CFile file;
			if ( !file.Open (file_name, CFile::READ) ) {
				LP_BaseLogger->Append ("FAIL:BasicQuery open file:%s fail.", file_name);
				return false;
			}
			char *buf = LP_NEW (char[file.Size () + 1]);
			if ( file.Read (buf, file.Size ()) ) {
				buf[file.Size ()] = '\0';
				CTextInStream stream;
				if ( stream.SetText (buf, buf[0]) ) {
					UInt32 cols = 0, row = 0;
					std::string ver;
					stream.Skip (1);
					stream >> ver;
					stream >> cols;
					row = (stream.GetColumns () - 3) / cols;
					if ( !stream.IsOver () && CheckVersion (ver) && ((stream.GetColumns () - 3) % cols) == 0) {
						TId id;
						TData *data;
						for (UInt32 i = 0; i < row; ++ i) {
							Deserialize (stream, id, data);
							mAllData [id] = data;
						}
					} else {
						LP_DELETE_ARRAY (buf);
						LP_BaseLogger->Append ("FAIL:BasicQuery %s load fail.", file_name);
						return false;
					}
					LP_DELETE_ARRAY (buf);
					return true;
				}
			}
			LP_BaseLogger->Append ("FAIL:BasicQuery %s load fail.", file_name);
			LP_DELETE_ARRAY (buf);
			return false;
		}

		TData const* Query (TId const& id) const
		{
			const_iterator it = mAllData.find (id);
			if (it != mAllData.end ())
				return it->second;
			return 0;
		}
		 
		inline ConType const& GetAllData () const { return mAllData; }

		void Clear ()
		{
			for (iterator it = mAllData.begin (); it != mAllData.end (); ++ it)
				LP_DELETE (it->second);
			mAllData.clear ();
		}
		virtual ~BasicQuery () { Clear (); }
	protected:
		ConType mAllData;
	};

#define BookQueryInterface(Name)	\
		inline const C##Name##Data* Query##Name##Data(UInt32 id) const { return m##Name##Query.Query (id); } \
		inline const C##Name##Query::ConType& GetAll##Name##Data () const { return m##Name##Query.GetAllData (); } \
		C##Name##Query m##Name##Query;

};

#endif //	LionX_GameDB_Other_BasicQuery_H

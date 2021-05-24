#ifndef LionX_LionX_Network_HTTP_H
#define LionX_LionX_Network_HTTP_H

#include "Base/BinStream.h"

//===========================================================================================
//	HTTP (字串限定UTF8)。
//===========================================================================================

namespace LionX
{
	class HTTP
	{
	public:
		enum EOptions
		{
			POST,
			GET,
		};
	public:
		class CRequest
		{
		public:
			CRequest (EOptions op = GET, bool keep_alive = false);
			void SetFile (const char *file_name);
			void SetHost (const char *host);
			void SetUrl (const char *url);
			void SetParam (bool header, const char *key, const char *value);
			bool Parse (std::string& out);
			void Reset (EOptions op = GET, bool keep_alive = false);
			virtual ~CRequest ();
		public:
			inline void SetOption (EOptions op) { mOP = op; }
		private:
			EOptions mOP;
			std::string mParams;
		};

		class CResponse
		{
		public:
			CResponse ();
			void Append (const char *data, UInt16 len);
			bool Parse ();
			bool Next ();
			inline bool HasBody () const { return (mBody != nullptr); }
			Int32 GetRetCode ();
			std::string GetHead (const char *key);
			bool GetHead (const char *key, std::string& value);
			bool SaveFile (const char *file_name);
			bool SaveBody (const char *file_name);
			bool GetBody (std::string& out);
			bool GetBody (char *out, UInt32& lenght);
			virtual ~CResponse ();
		private:
			std::vector<char> mDatas;
			const char *mHead, *mBody, *mEnd;
			Int32 mHeadSize, mBodySize;
		};
	};
};

#endif //	LionX_LionX_Network_HTTP_H

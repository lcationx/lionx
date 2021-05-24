#ifndef LionX_LionX_Database_MongoPool_H
#define LionX_LionX_Database_MongoPool_H

#include "Base/Synchronization.h"
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/exception/exception.hpp>

//===========================================================================================
//	Mongo 資料庫操作。
//===========================================================================================

namespace LionX
{
	class CMongoPool
	{
	public:
		CMongoPool (UInt32 count);
		bool ConnectDB (const std::string& ip, const std::string& port, const std::string& account, const std::string& password, const std::string& db_name);
		inline void SetDBName (const std::string& db_name) { mDBName = db_name; }
		bool insert_one (const std::string& collection, const bsoncxx::document::view_or_value& document, std::string& oid, std::stringstream& err);
		bool find_one (const std::string& collection, const bsoncxx::document::view_or_value& filter, const mongocxx::options::find& options, bsoncxx::stdx::optional< bsoncxx::document::value >& result, std::stringstream& err);
		bool find (const std::string& collection, const bsoncxx::document::view_or_value& filter, const mongocxx::options::find& options, mongocxx::cursor& result, std::stringstream& err);
		bool find_one_and_update (const std::string& collection, const bsoncxx::document::view_or_value& filter, const bsoncxx::document::view_or_value& update, const mongocxx::options::find_one_and_update& options, bsoncxx::stdx::optional< bsoncxx::document::value >& result, std::stringstream& err);
		bool update_one (const std::string& collection, const bsoncxx::document::view_or_value& filter, const bsoncxx::document::view_or_value& update, const mongocxx::options::update& options, mongocxx::stdx::optional< mongocxx::result::update >& result, std::stringstream& err);
		bool update_many (const std::string& collection, const bsoncxx::document::view_or_value& filter, const bsoncxx::document::view_or_value& update, const mongocxx::options::update& options, mongocxx::stdx::optional< mongocxx::result::update >& result, std::stringstream& err);
		UInt64 count (const std::string& collection, const bsoncxx::document::view_or_value& filter, std::stringstream& err);
		virtual ~CMongoPool ();
	private:
		UInt32 mCount;
		std::string mDBName;
		std::unique_ptr<mongocxx::pool> mPool;
	};
};

#endif //	LionX_LionX_Database_MongoPool_H

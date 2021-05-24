#ifndef LionX_LionX_Databank_RedisPool_H
#define LionX_LionX_Databank_RedisPool_H

#include "Base/CircularQueue.h"
#include <hiredis.h>

//===========================================================================================
//	Redis 資料庫操作。
//	EXPIRE key seconds						指定某key值數據在幾秒後失效。
//	SET key s								建立並設定某key值。
//	SET key s s_lenght						建立並設定某key值 指定數據長度。
//	SETNX key s								只在key值不存在時建立並設定其值。
//	SETNX key s	s_lenght					只在key值不存在時建立並設定其值 指定數據長度。
//	SETEX key seconds s						建立並設定某key值並指定生命週期。
//	SETEX key seconds s	s_lenght			建立並設定某key值並指定生命週期 指定數據長度。
//	GET key									取得某key對應數據。
//	INCRBY key v							變更某key對應的值 v 可為正負值。
//	DEL key									刪除某key值 (hasetable也使用這個)。
//	HEXPIRE table key seconds				哈希表 - 指定某key值數據在幾秒後失效。
//	HSET table key s						哈希表 - 建立並設定某key值。
//	HSET table key s s_lenght	 			哈希表 - 建立並設定某key值 指定數據長度。
//	HSETNX table key s						哈希表 - 只在key值不存在時建立並設定其值。
//	HSETNX table key s	s_lenght			哈希表 - 只在key值不存在時建立並設定其值 指定數據長度。
//	HSETEX table key seconds s				哈希表 - 建立並設定某key值並指定生命週期。
//	HSETEX table key seconds s	s_lenght	哈希表 - 建立並設定某key值並指定生命週期 指定數據長度。
//	HGET table key							哈希表 - 取得某key對應數據。
//	HGETALL table							哈希表 - 取得哈希表內的全部數據。
//	HINCRBY table key v						哈希表 - 變更某key對應的值 v 可為正負值。
//	HDEL table key							哈希表 - 刪除某key值。
//	FLUSHALL ASYNC/SYNC						異步(ASYNC)或同步(SYNC)清除整個Redis數據庫。
//	指令請用大寫不然會有異常。
//===========================================================================================

namespace LionX
{

	class CRedisResult
	{
	public:
		inline CRedisResult ()
			: mResult (nullptr), mRow (0), mCol (0), mMaxRow (0), mMaxCol (0)
		{ }
		bool IsFail ();
		~CRedisResult ();
	public:
		//	返回結果行數。
		inline Int32 Tuples () { return mMaxRow; }
		//	返回每行欄位數。
		inline Int32 Columns () { return mMaxCol; }
		//	取得給定欄位值。
		const char* GetValue (UInt32 row, UInt32 col);
	public:
		bool Prepare ();
		//	資料流。
		CRedisResult& operator >> (char& dest);
		CRedisResult& operator >> (unsigned char& dest);
		CRedisResult& operator >> (Int16& dest);
		CRedisResult& operator >> (UInt16& dest);
		CRedisResult& operator >> (Int32& dest);
		CRedisResult& operator >> (UInt32& dest);
		CRedisResult& operator >> (Int64& dest);
		CRedisResult& operator >> (UInt64& dest);
		CRedisResult& operator >> (float& dest);
		CRedisResult& operator >> (double& dest);
		//	特殊資料流。
		CRedisResult& operator >> (std::string& dest);
		CRedisResult& operator >> (char* dest);
		//	取得數據組。
		std::pair<Int32, const char*> GetBinary ();
	private:
		void SetResult (redisReply* result, Int32 columns);
	public:
		std::string mErrMessage;
	private:
		redisReply* mResult;
		Int32 mRow, mCol;
		Int32 mMaxRow, mMaxCol;
	private:
		friend class CRedisPool;
	};

	class CRedisPool
	{
	public:
		CRedisPool (UInt32 count);
		bool ConnectDB (const std::string& ip, Int16 port, const std::string& password);
		void ExecCommand (CRedisResult& result, const char* command);
		void ExecCommand (CRedisResult& result, const char* command, const char* key, Int64 value);
		void ExecCommand (CRedisResult& result, const char* command, const char* table, const char* key, Int64 value);
		void ExecBinaryCommand (CRedisResult& result, const char* command, const char* key, const char* data, size_t data_size);
		void ExecBinaryCommand (CRedisResult& result, const char* command, const char* table, const char* key, const char* data, size_t data_size);
		virtual ~CRedisPool ();
	private:
		bool Reconnect (redisContext** con);
	private:
		UInt32 mCount;
		std::string mIP;
		Int16 mPort;
		std::string mPassword;
		CSimpleCircularQueue<redisContext*> mConnections;
	};
};

#endif //	LionX_LionX_Databank_RedisPool_H

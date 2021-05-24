#ifndef LionX_LionX_Databank_PostgresPool_H
#define LionX_LionX_Databank_PostgresPool_H

#include "Base/CircularQueue.h"
#include <libpq-fe.h>

//===========================================================================================
//	Postgres 資料庫操作。
//===========================================================================================

namespace LionX
{
	class CPostgresResult
	{
	public:
		inline CPostgresResult ()
			: mResult (nullptr), mRow (0), mCol (0), mMaxRow (0), mMaxCol (0)
		{ }
		bool IsFail ();
		~CPostgresResult ();
	public:
		//	返回受命令影響的行數。
		Int32 CmdTuples ();
		//	返回結果行數。
		inline Int32 Tuples () { return mMaxRow; }
		//	返回每行欄位數。
		inline Int32 Columns () { return mMaxCol; }
		//	取得欄位名稱。
		const char* GetTitle (UInt32 col);
		//	取得給定欄位值。
		const char* GetValue (UInt32 row, UInt32 col);
	public:
		bool Prepare ();
		//	資料流。
		CPostgresResult& operator >> (char& dest);
		CPostgresResult& operator >> (unsigned char& dest);
		CPostgresResult& operator >> (Int16& dest);
		CPostgresResult& operator >> (UInt16& dest);
		CPostgresResult& operator >> (Int32& dest);
		CPostgresResult& operator >> (UInt32& dest);
		CPostgresResult& operator >> (Int64& dest);
		CPostgresResult& operator >> (UInt64& dest);
		CPostgresResult& operator >> (float& dest);
		CPostgresResult& operator >> (double& dest);
		//	僅方便用於ENUM值。
		template<typename T>
		CPostgresResult& operator >> (T& dest)
		{
			if (mCol < mMaxCol)
				dest = (T)atoi (GetValue (mRow, mCol++));
			return *this;
		}
		//	特殊資料流。
		CPostgresResult& operator >> (std::string& dest);
		CPostgresResult& operator >> (char* dest);
	private:
		void SetResult (PGresult* result);
	public:
		std::string mErrMessage;
	private:
		PGresult* mResult;
		Int32 mRow, mCol;
		Int32 mMaxRow, mMaxCol;
	private:
		friend class CPostgresPool;
	};

	class CPostgresPool
	{
	public:
		class CExecutor
		{
		public:
			inline CExecutor (PGconn* conn)
				: mConn (conn)
			{ }
			void Exec (CPostgresResult& result, const char* command);
			void Exec (const char* command);
			~CExecutor () { }
		private:
			PGconn* mConn;
		private:
			friend class CPostgresPool;
		};
	public:
		CPostgresPool (UInt32 count);
		bool ConnectDB (const std::string& ip, const std::string& port, const std::string& account, const std::string& password, const std::string& db_name);
		void ExecCommand (CPostgresResult& result, const char* command);
		void Transaction (CPostgresResult& result, std::function<bool (CExecutor&)> method);
		virtual ~CPostgresPool ();
	private:
		bool Reconnect (PGconn* con);
		bool IsOnline (PGconn* con);
	private:
		UInt32 mCount;
		CSimpleCircularQueue<PGconn*> mConnections;
	};

};

#endif //	LionX_LionX_Databank_PostgresPool_H

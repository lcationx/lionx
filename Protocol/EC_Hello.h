#ifndef LionX_Sample_Protocol_EC_Hello_H
#define LionX_Sample_Protocol_EC_Hello_H


//===========================================================================================
//	叢集-測試訊息。
//===========================================================================================

namespace LionX
{
	class CEC_Hello : public CNetStream
	{
	public:
		inline CEC_Hello ()
			: mSentTime (0.0), mRecvTime (0.0)
		{ }
		virtual void Out (COutBinStream& out)
		{
			if ( IsOriginate () )
			{
				for (int i = 0; i < 10; ++ i)
					out << mSentTime;
			} 
			else 
			{
				for (int i = 0; i < 10; ++ i)
					out << mRecvTime;

			}
		}
		virtual void In (CInBinStream& in)
		{
			if ( IsOriginate () )
			{
				for (int i = 0; i < 10; ++ i)
					in >> mSentTime;
			} 
			else 
			{
				for (int i = 0; i < 10; ++ i)
					in >> mRecvTime;

			}		
		}
		virtual ~CEC_Hello () { }
	public:
		//	in data。
		double mSentTime;

	public:
		//	out data。
		double mRecvTime;
	};
};

#endif //	LionX_Sample_Protocol_EC_Hello_H

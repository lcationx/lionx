#ifndef LionX_LionX_Network_DNS_H
#define LionX_LionX_Network_DNS_H

#include "Base/BinStream.h"

//===========================================================================================
//	DNS。
//===========================================================================================

namespace LionX
{
	class DNS
	{
	public:
		static const UInt16 MaxDomainSize = 128;
		static const UInt16 MaxDataSize = 128;
		static const UInt16 MaxSectionCount = 10;
		static const unsigned char CompressMask = 0xC0;
	public:
		static UInt16 SerializeString (char *dest, UInt16 dest_size, const char *src);
	public:
		enum EOPCode
		{
			OP_QUERY = 0,			//	標準查詢。
			OP_INVERSE_QUERY = 1,	//	反向查詢。
			OP_STATUS = 2,			//	伺服器狀態查詢。
		};

		enum ERCode
		{
			RS_SUCCESS = 0,			//	沒有錯誤。
			RS_FORMAT_FAIL = 1,		//	格式錯誤。
			RS_DNS_FAIL = 2,		//	DNS伺服器異常。
			RS_NAME_FAIL = 3,		//	查詢的FQDN不存在。
			RS_NOT_IMPLEMENTED = 4,	//	OPCode操作不支援。
			RS_REFUSED = 5,			//	DNS拒絕處理。
		};

		enum EQType
		{
			QT_A		= 0x0001,	//	FQDN to IPV4。
			QT_NS		= 0x0002,
			QT_MD		= 0x0003,
			QT_MF		= 0x0004,
			QT_CNAME	= 0x0005,	//	別名。
			QT_SOA		= 0x0006,
			QT_WKS		= 0x000B,
			QT_PTR		= 0x000C,	//	IP to FQDN。
			QT_MX		= 0x000F,
			QT_TEXT		= 0x0010,
			QT_LOC		= 0x001D,
			QT_SRV		= 0x0021,
			QT_AAAA		= 0x001C,	//	FQDN to IPV6。
			QT_ALL		= 0x00FF,	//	要求全部支援的格式資訊。
		};

		enum EQClass
		{
			QC_RESERVED		= 0x0000,		//	保留。
			QC_IN			= 0x0001,		//	Internet。
		};
	public:
		struct SFields
		{
		public:
			union 
			{
				struct { UInt16 
					RD : 1,						//	查詢: 使用遞迴查詢。
					TC : 1,						//	封包長度大於512bytes並且已被截斷。
					AA : 1,						//	回復: 查詢資料為管轄區域內紀錄。
					OPCodes : 4,				//	查詢: 參閱EOPCode。
					QR : 1,						//	查詢=0 回復=1。
					RCodes : 4,					//	回復: 參閱ERCode。
					NonAuthenticated : 1,		//	未知。
					AnswerAuthenticated : 1,	//	未知。
					Reserved : 1,				//	保留。
					RA : 1;						//	回復: 使用遞迴查詢。
				};
				UInt16 mValue;
			};
		public:
			inline SFields ()
				: mValue (0)
			{ }
		};

		struct SHeader
		{
		public:
			RUInt16 mQID;
			SFields mFields;
			RUInt16 mQDCount, mANCount, mNSCount, mARCount;
		public:
			inline SHeader ()
				: mQID (0), mQDCount (0), mANCount (0), mNSCount (0), mARCount (0)
			{ }
		};

		struct SQuestion
		{
		public:
			char mDomainName [MaxDomainSize];
			RUInt16 mQType;
			RUInt16 mQClass;
		public:
			inline SQuestion ()
				: mQType (0), mQClass (0)
			{ }
		};

		struct SAnswer
		{
		public:
			char mDomainName [MaxDomainSize];
			RUInt16 mQType;
			RUInt16 mQClass;
			RUInt32 mTTL;
			RUInt16 mRDataLength;
			char mRData [MaxDataSize];
		public:
			inline SAnswer ()
				: mQType (0), mQClass (0), mTTL (0), mRDataLength (0)
			{ }
		};

		class CPack
		{
		public:
			SHeader mHeader;
			SQuestion mQuestions [MaxSectionCount];
			SAnswer mAnswers [MaxSectionCount];
		public:
			CPack ();
			bool Decode (char *data, UInt16 data_len);
			bool Code (char *data, UInt16& data_len);
			~CPack ();
		};
	};
};

#endif //	LionX_LionX_Network_DNS_H

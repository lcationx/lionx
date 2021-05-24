#ifndef LionX_LionX_Network_NetStream_H
#define LionX_LionX_Network_NetStream_H

#include "NetCommand.h"

//===========================================================================================
//	網路數據流。
//===========================================================================================

namespace LionX
{
	class CNetStream
	{
	public:
		CNetStream ()
			: mIsReply (false)
		{ }
		//	必須透過 IsReply() 來確認數據的流向。
		virtual void Out (COutBinStream& out) = 0;
		virtual void In (CInBinStream& in) = 0;
		virtual ~CNetStream () { }
	public:
		//	是否為開始狀態。
		inline bool IsOriginate () const { return (!mIsReply); }
	protected:
		bool mIsReply;
	};
};

#endif //	LionX_LionX_Network_NetStream_H

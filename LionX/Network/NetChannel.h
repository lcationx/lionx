#ifndef LionX_LionX_Network_NetChannel_H
#define LionX_LionX_Network_NetChannel_H

#include "Socket.h"
#include "NetCommand.h"

//===========================================================================================
//	網路頻道。
//===========================================================================================

namespace LionX
{
	class CNetChannel : public CSocket
	{
	public:
		inline CNetChannel ()
		{ }
		virtual void Encryption (char *data, UInt16 len) { }
		virtual void Decryption (char *data, UInt16 len) { }
		virtual ITaskCommand* GenerateTaskCommand (UInt16 sn, CInBinStream& in) = 0;
		virtual ~CNetChannel () { }
	protected:
		Int32 ResetNetwork ();
	};
};

#endif //	LionX_LionX_Network_NetChannel_H

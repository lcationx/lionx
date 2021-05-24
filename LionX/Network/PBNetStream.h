#ifndef LionX_LionX_Network_PBNetStream_H
#define LionX_LionX_Network_PBNetStream_H

#include "NetStream.h"

//===========================================================================================
//	Google ProtoBuffer Net Command Task。
//===========================================================================================

namespace LionX
{
	template<typename ProtoData>
	class PBNetStream : public CNetStream, public ProtoData
	{
	public:
		inline PBNetStream ()
		{ }
		virtual void Out (COutBinStream& out)
		{
			if ( !FillOutBinStreamStream (out, *((ProtoData*)this)) ) {
				LP_BaseLogger->Append ("FAIL:PBNetCommand(%s) serialize data but size %hu over %d.", GetClassName<ProtoData>(this), (unsigned short)(ProtoData::ByteSizeLong ()),  out.GetRemainSize ());
			}
		}
		virtual void In (CInBinStream& in)
		{
			if ( !ProtoData::ParseFromArray (in.GetCurrentPtr (), in.GetRemainSize ()) ) {
				LP_BaseLogger->Append ("FAIL:PBNetCommand(%s) deserialize data fail.", GetClassName<ProtoData>(this));
			} else {
				in.Skip (in.GetRemainSize ());
			}		
		}
		virtual ~PBNetStream () { } 
	};

	//	標記PBCommand指令。
#define BookPBNetCommand(sn, stream)	BaseNetCommand< PBNetStream<stream> >::SN = ((UInt16)sn);
	//	標記PBTaskCommand任務。
#define BookPBTaskCommand(gen, sn, stream, fnexec)	 {\
typedef BaseTaskGeneratorImpl< PBNetStream<stream> > IMPL; \
BaseNetCommand< PBNetStream<stream> >::SN = ((UInt16)sn); \
BaseTaskCommand< PBNetStream<stream> >::SN = (gen).Book (sn, LP_NEW (IMPL([&](BaseTaskCommand< PBNetStream<stream> >* task) { fnexec; }))); }
	//	標記同名PBCommand指令。
#define BookSameNamePBNetCommand(stream)	BaseNetCommand< PBNetStream<stream> >::SN = ((UInt16)e##stream);
	//	標記同名PBTaskCommand任務。
#define BookSameNamePBTaskCommand(gen, stream, fnexec)	 {\
typedef BaseTaskGeneratorImpl< PBNetStream<stream> > IMPL; \
BaseNetCommand< PBNetStream<stream> >::SN = ((UInt16)e##stream); \
BaseTaskCommand< PBNetStream<stream> >::SN = (gen).Book (e##stream, LP_NEW (IMPL([&](BaseTaskCommand< PBNetStream<stream> >* task) { fnexec; }))); }
};

#endif //	LionX_LionX_Network_PBNetStream_H

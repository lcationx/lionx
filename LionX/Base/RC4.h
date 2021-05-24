#ifndef LionX_LionX_Base_RC4_H
#define LionX_LionX_Base_RC4_H

#include "LionX.h"

//===========================================================================================
//	RC4加密。
//===========================================================================================

namespace LionX
{
	class CRC4
	{
	public:
		inline CRC4 ()
			: mKeyLen (0) { }
		void Init (const char *pwd = 0, UInt16 len = 0);
		void Encryption (PVoid data, UInt32 len);
		void Decryption (PVoid data, UInt32 len);
		inline UInt16 GetKeyLen () const { return mKeyLen; }
		inline const char* GetKey () const { return mKey; }
		void Done ();
		~CRC4 () { }
	public:
		char mKey[64];
		UInt16 mKeyLen;
		unsigned char mState [256];
	};
};

#endif //	LionX_LionX_Base_RC4_H

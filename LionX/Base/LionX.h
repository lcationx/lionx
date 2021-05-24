#ifndef LionX_LionX_Base_LionX_H
#define LionX_LionX_Base_LionX_H

//===========================================================================================
//	C & C++ 標頭檔。
//===========================================================================================

#include <cassert>
#include <stdexcept>
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <algorithm>
#include <functional>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <time.h>
#include <wchar.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>
#include <malloc.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <typeinfo>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <asm/ioctls.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/resource.h>
#include <zlib.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <execinfo.h>
#include <uuid/uuid.h>
#include <ucontext.h>
#include <setjmp.h>
#include <future>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <condition_variable>



//===========================================================================================
//	通用巨集。
//===========================================================================================

#define LP_NEW(x) new x 
#define LP_SAFE_DELETE(x)		if (x) { delete x; x = 0; }
#define LP_SAFE_DELETE_ARRAY(x)	if (x) { delete [] x; x = 0; }
#define LP_DELETE(x)			delete x
#define LP_DELETE_ARRAY(x)		delete [] x
#define LP_CLEAN_DELETE(x)		delete x; x = 0

#define XALIGNED(x)			__attribute__((aligned(x)))
#define LP_RELEASE(x)		x->Release ()
#define LP_SAFE_RELEASE(x)	if (x != 0) { x->Release (); x = 0; }
#define DECLARE_PUB_PARAM(type, name) public: const type& Get##name () const { return m##name; } void Set##name (const type& v) { m##name = v; } private: type m##name;
#define DECLARE_PRI_PARAM(type, name) public: const type& Get##name () const { return m##name; } private: type m##name;
#define DECLARE_FLAGS(type) public: void SetBit (bool v, type mask) { v ? mFlags |= mask : mFlags &= ~mask; } bool GetBit (type mask) const { return ((mFlags & mask) != 0); } protected: void SetField (type v, type mask, type pos) { mFlags = ((mFlags & ~mask) | (v << pos)); } type GetField (type mask, type pos) const { return ((mFlags & mask) >> pos); } protected: type mFlags = 0;

#define MAKE_INT16(a, b)	((Int16)(((UInt32)a) & 0xFF) | ((((UInt32)b) & 0xFF) << 8))
#define MAKE_INT32(a, b)	((Int32)(((UInt32)a) & 0xFFFF) | ((((UInt32)b) & 0xFFFF) << 16))
#define MAKE_INT64(a, b)	((Int64)(((UInt64)a) & 0xFFFFFFFFL) | ((((UInt64)b) & 0xFFFFFFFFL) << 32))
#define LO_INT16(l)			((Int16)(((UInt32)l) & 0xFFFF))
#define HI_INT16(l)			((Int16)((((UInt32)l) >> 16) & 0xFFFF))
#define LO_CHAR(w)			((char)(((UInt32)w) & 0xFF))
#define HI_CHAR(w)			((char)((((UInt32)w) >> 8) & 0xFF))
#define LO_INT32(l)			((Int32)(((UInt64)l) & 0xFFFFFFFFL))
#define HI_INT32(l)			((Int32)((((UInt64)l) >> 32) & 0xFFFFFFFFL))
#define SWAP_INT16(x)		MAKE_INT16(HI_CHAR(x), LO_CHAR(x))
#define SWAP_INT32(x)		MAKE_INT32(SWAP_INT16(HI_INT16(x)), SWAP_INT16(LO_INT16(x)))
#define SWAP_PTR_INT16(x)
#define SWAP_PTR_INT32(x)
#define SWAP_PTR_UINT16(x)
#define SWAP_PTR_UINT32(x)


#define MAKEUTF(x)			L  ## x
#define UTF(x)				MAKEUTF(x)
#define __UTF_FILE__		UTF(__FILE__)

#define OFFSETOF(type,member) ((size_t)&(((type*)0)->member))

//===========================================================================================
//	通用資料。
//===========================================================================================

namespace LionX
{
	//	16 bit 數據。
	typedef short				Int16;
	typedef unsigned short		UInt16;
	//	32 bit 數據。
	typedef int					Int32;
	typedef unsigned int		UInt32;
	//	64 bit 數據。
	typedef long long			Int64;
	typedef unsigned long long	UInt64;
	//	不定長度數據。
	typedef long				Long;
	typedef unsigned long		ULong;
	//	指針數據。
	typedef void*				PVoid;
	//	字元。
	typedef short				UTF16;
	typedef wchar_t				UTF32;
	//	字串。
	typedef std::basic_string<UTF16>	UTF16String;
	typedef std::basic_string<UTF32>	UTF32String;
};

//===========================================================================================
//	預先載入內容。
//===========================================================================================

#include "IRTTI.h"
#include "AtomicOP.h"
#include "Assert.h"
#include "Singleton.h"
#include "SmartPtr.h"
#include "Logger.h"
#include "Functional.h"

//===========================================================================================
//===========================================================================================

#endif //	LionX_LionX_Base_LionX_H

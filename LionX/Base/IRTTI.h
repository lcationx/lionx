#ifndef LionX_LionX_Base_IRTTI_H
#define LionX_LionX_Base_IRTTI_H

//===========================================================================================
//	執行時期資料型態介面。
//===========================================================================================

namespace LionX
{
	class IRTTI
	{
	public:
		virtual Int32 IsA () const { return 0; }
		virtual ~IRTTI () { }
	};

	class SRTTI
	{
	public:
		virtual const std::string& IsA () const = 0;
		virtual ~SRTTI () { }
	};

	//	轉型。
	template <typename T>
	inline T* PointCast (IRTTI *pvoid) { return (pvoid->IsA () == T::_IsA ()) ? (T*)pvoid : 0; }
	template <typename T>
	inline const T* PointCast (const IRTTI *pvoid) { return (pvoid->IsA () == T::_IsA ()) ? (const T*)pvoid : 0; }
	template <typename T>
	inline T* PointFrom (IRTTI *pvoid) { return ((pvoid->IsA () & T::_IsA ()) == T::_IsA ()) ? (T*)pvoid : 0; }
	template <typename T>
	inline const T* PointFrom (const IRTTI *pvoid) { return ((pvoid->IsA () & T::_IsA ()) == T::_IsA ()) ? (const T*)pvoid : 0; }

	template <typename T>
	inline T* PointCast (SRTTI *pvoid) { return (pvoid->IsA () == T::_IsA ()) ? (T*)pvoid : 0; }
	template <typename T>
	inline const T* PointCast (const SRTTI *pvoid) { return (pvoid->IsA () == T::_IsA ()) ? (const T*)pvoid : 0; }

#define DECLARE_RTTI(type)	static Int32 _IsA () { return type; } virtual Int32 IsA () const { return type; }
#define DECLARE_SRTTI(type)	static const std::string& _IsA () { static std::string v = type; return v; } virtual const std::string& IsA () const { static std::string v = type; return v; }
};

#endif //	LionX_LionX_Base_IRTTI_H

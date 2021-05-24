#ifndef LionX_LionX_Base_Singleton_H
#define LionX_LionX_Base_Singleton_H

//===========================================================================================
//	獨體模板。
//===========================================================================================

namespace LionX
{
	template<typename T>
	class TSingleton
	{
	private:
		static TSingleton<T>* mInstance;
	public:
		inline static TSingleton<T>& Ins ()
		{
			if (mInstance == nullptr)
				mInstance = LP_NEW (TSingleton);
			return *mInstance;
		}
		inline static bool IsCreated () { return (mInstance != nullptr); }
		inline static void Release () { LP_SAFE_DELETE (mInstance); }
	public:
		inline void Set (T* ref)
		{
			LP_SAFE_DELETE (mRef);
			mRef = ref;
		}
		inline T* Swap (T* ref) { T* tmp = mRef; mRef = ref; return tmp; }
		inline T* Get () { return mRef; }
		inline operator T* () const { return mRef; }
		inline T& operator* () const { return *mRef; }
		inline T* operator-> () const { return mRef; }
		inline bool operator == (const T* ref) const { return (ref == mRef); }
		inline bool operator != (const T* ref) const { return (ref != mRef); }
	protected:
		inline TSingleton ()
			: mRef (LP_NEW (T))
		{ }
		inline ~TSingleton () { LP_SAFE_DELETE (mRef); }
	private:
		T* mRef;
	};

	template <typename T>  TSingleton<T>* TSingleton<T>::mInstance = nullptr;

};

#endif //	LionX_LionX_Base_Singleton_H

#ifndef LionX_LionX_Base_SmartPtr_H
#define LionX_LionX_Base_SmartPtr_H

//===========================================================================================
//	專屬智能指針。
//===========================================================================================

namespace LionX
{
	class CRef
	{
	public:
		inline CRef ()
			: mRefCount (0) { }
		inline Int32 AddRef () { return Atomic::LockedIncrement (&mRefCount); }
		inline void DecRef () { if (Atomic::LockedDecrement (&mRefCount) == 0) LP_DELETE (this); }
		inline Int32 GetRef () const { return mRefCount; }
		bool WaitRefCount (Int32 ref_count, double time);
		//	wait_check_method返回true表示不繼續等待，WaitRefCount失敗返回。
		bool WaitRefCount (Int32 ref_count, std::function<bool ()> wait_check_method);
		inline Int32 GetRefCount () const { return mRefCount; }
		virtual ~CRef () { }
	private:
		Int32 mRefCount;
	};


	template<typename T>
	class SmartPtr
	{
	public:
		inline SmartPtr ()
			: mRef (nullptr) { }
		inline SmartPtr (T *ref)
			: mRef (ref) { if (ref != nullptr) ref->AddRef (); }
		inline SmartPtr (const SmartPtr& ptr) { mRef = ptr.mRef; if (mRef != nullptr) mRef->AddRef (); }
		inline void Set (T *ref)
		{
			if (mRef != ref) {
				if (mRef != nullptr) mRef->DecRef ();
				if ((mRef = ref) != nullptr) mRef->AddRef ();
			}
		}
		inline T* Get () const { return mRef; }
		inline operator T* () const { return mRef; }
		inline T& operator* () const { return *mRef; }
		inline T* operator-> () const { return mRef; }
		inline SmartPtr& operator = (const SmartPtr& another) { Set (another.mRef); return *this; }
		inline SmartPtr& operator = (T *ref) { Set (ref); return *this; }
		inline bool operator == (const SmartPtr& another) const { return (another.mRef == mRef); }
		inline bool operator != (const SmartPtr& another) const { return (another.mRef != mRef); }
		inline bool operator == (T *ref) const { return (ref == mRef); }
		inline bool operator != (T *ref) const { return (ref != mRef); }
		inline ~SmartPtr () { if (mRef != nullptr) mRef->DecRef (); }
	private:
		T *mRef;
	};

	template<typename T>
	class SmartLocker
	{
	public:
		inline SmartLocker ()
		{ }
		inline SmartLocker (T* smart_ptr)
			: mSmartPtr (smart_ptr)
		{
			if (mSmartPtr != nullptr)
				mSmartPtr->lock ();
		}
		inline SmartLocker (const SmartPtr<T>& smart_ptr)
			: mSmartPtr (smart_ptr)
		{
			if (mSmartPtr != nullptr)
				mSmartPtr->lock ();
		}
		inline T* Get () const { return mSmartPtr.Get (); }
		inline operator T* () const { return mSmartPtr.Get (); }
		inline operator SmartPtr<T> () const { return mSmartPtr; }
		inline T& operator* () const { return *mSmartPtr.Get (); }
		inline T* operator-> () const { return mSmartPtr.Get (); }
		inline SmartLocker& operator = (const SmartPtr<T>& another) 
		{ 
			if (mSmartPtr != nullptr)
				mSmartPtr->unlock ();
			if ((mSmartPtr = another) != nullptr)
				mSmartPtr->lock ();
			return *this; 
		}
		inline SmartLocker& operator = (T* ref)
		{
			if (mSmartPtr != nullptr)
				mSmartPtr->unlock ();
			if ((mSmartPtr = ref) != nullptr)
				mSmartPtr->lock ();
			return *this;
		}
		inline bool operator == (T* ref) const { return (ref == mSmartPtr); }
		inline bool operator != (T* ref) const { return (ref != mSmartPtr); }
		inline ~SmartLocker ()
		{
			if (mSmartPtr != nullptr)
				mSmartPtr->unlock ();
		}
	private:
		SmartPtr<T> mSmartPtr;
	};


	template<typename T>
	class SmartDelete
	{
	public:
		inline SmartDelete ()
			: mRef (nullptr) { }
		inline SmartDelete (T* ref)
			: mRef (ref) { }
		inline void Set (T* ref)
		{
			if (mRef != ref) {
				LP_SAFE_DELETE (mRef);
				mRef = ref;
			}
		}
		inline T* Get () const { return mRef; }
		inline operator T* () const { return mRef; }
		inline T& operator* () const { return *mRef; }
		inline T* operator-> () const { return mRef; }
		inline SmartDelete& operator = (T* ref) { Set (ref); return *this; }
		inline bool operator == (const SmartDelete& another) const { return (another.mRef == mRef); }
		inline bool operator != (const SmartDelete& another) const { return (another.mRef != mRef); }
		inline bool operator == (T* ref) const { return (ref == mRef); }
		inline bool operator != (T* ref) const { return (ref != mRef); }
		inline ~SmartDelete () { LP_SAFE_DELETE (mRef); }
	private:
		T* mRef;
	};

	template<typename T>
	class AutoLocker
	{
	public:
		inline AutoLocker (T* lock = nullptr)
			: mLock (lock)
		{
			if (mLock != nullptr)
				mLock->lock ();
		}
		inline AutoLocker (T& lock)
			: mLock (&lock)
		{
			if (mLock != nullptr)
				mLock->lock ();
		}
		inline AutoLocker& operator = (T* lock) {
			if (mLock != nullptr)
				mLock->unlock ();
			if ((mLock = lock) != nullptr)
				mLock->lock ();
			return *this;
		}
		inline AutoLocker& operator = (T& lock) {
			if (mLock != nullptr)
				mLock->unlock ();
			if ((mLock = &lock) != nullptr)
				mLock->lock ();
			return *this;
		}
		inline ~AutoLocker () { if (mLock != nullptr)  mLock->unlock (); }
	private:
		T* mLock;
	};

	class CSmartFreed
	{
	public:
		inline CSmartFreed (std::function<void ()> fn_release)
			: mFnRelease (fn_release)
		{
		}
		CSmartFreed (const CSmartFreed&) = delete;
		CSmartFreed& operator=(const CSmartFreed&) = delete;
		inline ~CSmartFreed () { mFnRelease (); }
	private:
		std::function<void ()> mFnRelease;
	};

#define SmartFreed(name, obj, fn_init, fn_release) \
	CSmartFreed name (std::bind(&fn_release, &obj)); \
	obj.fn_init();

};

#endif //	LionX_LionX_Base_SmartPtr_H

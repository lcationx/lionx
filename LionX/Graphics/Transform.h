#ifndef LionX_LionX_Graphics_Transform_H
#define LionX_LionX_Graphics_Transform_H

#include "Quaternion.h"

//===========================================================================================
//	轉移資訊 (先旋轉 再縮放 再轉移)。
//===========================================================================================

namespace LionX
{
	class CTransform
	{
	public:
		inline CTransform ()
			: mScale (1.0f), mTranslate (0.0f, 0.0f, 0.0f)
		{
			mRotate = CMatrix3x3::IDENTITY;
		}
		void Identity ();
		void Invert (CTransform& dest) const;
		CTransform Invert () const;
		inline ~CTransform () { }
	public:
		CVector3 operator * (const CVector3& vec) const;
		CTransform operator * (const CTransform& form) const;
	public:
		inline bool operator == (const CTransform& form) const { return (form.mRotate == mRotate && form.mScale == mScale && form.mTranslate == mTranslate); }
		inline bool operator != (const CTransform& form) const { return (form.mRotate != mRotate || form.mScale != mScale || form.mTranslate != mTranslate); }
	public:
		CMatrix3x3 mRotate;
		CVector3 mScale;
		CVector3 mTranslate;
	};
};

#endif //	LionX_LionX_Graphics_Transform_H

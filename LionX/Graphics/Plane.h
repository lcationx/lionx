#ifndef LionX_LionX_Graphics_Plane_H
#define LionX_LionX_Graphics_Plane_H

#include "Vector3.h"

//===========================================================================================
//	平面。
//	在3D空間中 一個平面在空間中定義為Ax+By+Cz+D=0 表示，
//	Normal = xyz, Constant = d
//	
//===========================================================================================

namespace LionX
{
	class CPlane
	{
	public:
		enum
		{
			POSITIVE_SIDE = 1,		//	點在正面。
			NO_SIDE = 0,			//	面在點上 (或面被包圍)。
			NEGATIVE_SIDE = -1,		//	點在反面。
		};
	public:
		inline CPlane ()
			: mConstant (0.0f)
		{ }
		inline CPlane (const CVector3& normal, float constant)
			: mNormal (normal), mConstant (constant)
		{ }
		inline CPlane (const CVector3& normal, const CVector3& point)
		{
			SetPlane (normal, point);
		}
		inline CPlane (const CVector3& v0, const CVector3& v1, const CVector3& v2)
		{
			SetPlane (v0, v1, v2);
		}
		inline bool operator == (const CPlane& plane) const { return (mNormal == plane.mNormal && mConstant == plane.mConstant); }
		inline bool operator != (const CPlane& plane) const { return (mNormal != plane.mNormal || mConstant != plane.mConstant); }
		inline void SetNormal (const CVector3& normal) { mNormal = normal; }
		inline const CVector3& GetNormal () const { return mNormal; }
		inline void SetConstant (float constant) { mConstant = constant; }
		inline float GetConstant () const { return mConstant; }
		inline float Distance (const CVector3& point) const { return (mNormal.DotProduct (point) - mConstant); }
		Int32 WhichSide (const CVector3& point) const;
		Int32 WhichSide (const CVector3& centrer, const CVector3& half_size) const;
		void SetPlane (const CVector3& normal, const CVector3& point);
		void SetPlane (const CVector3& v0, const CVector3& v1, const CVector3& v2);
		~CPlane () { }
	public:
		CVector3 mNormal;
		float mConstant;
	};
};

#endif //	LionX_LionX_Graphics_Plane_H

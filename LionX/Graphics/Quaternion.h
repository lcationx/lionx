#ifndef LionX_LionX_Graphics_Quaternion_H
#define LionX_LionX_Graphics_Quaternion_H

#include "Matrix3x3.h"

//===========================================================================================
//	四元數。
//===========================================================================================

namespace LionX
{
	class CQuaternion
	{
	public:
		static const CQuaternion ZERO;
		static const CQuaternion IDENTITY;
	public:
		//	建構式。
		inline CQuaternion (float _w = 1.0f, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
			: w (_w), x (_x), y (_y), z (_z) { }
		inline CQuaternion (const CQuaternion& qt)
			: w (qt.w), x (qt.x), y (qt.y), z (qt.z) { }
		inline CQuaternion (const CMatrix3x3& mat) { Set (mat); }
		inline CQuaternion (const CVector3& axis, float radian) { Set (axis, radian); }
		inline CQuaternion (const CVector3& xaxis, const CVector3& yaxis, const CVector3& zaxis) { Set (xaxis, yaxis, zaxis); }
		//	設定。
		inline void Set (float _w, float _x, float _y, float _z) { w = _w; x = _x; y = _y; z = _z; }
		inline void Set (const CQuaternion& qt) { w = qt.w; x = qt.x; y = qt.y; z = qt.z; }
		void Set (const CMatrix3x3& mat);
		void Set (const CVector3& axis, float radian);
		void Set (const CVector3& xaxis, const CVector3& yaxis, const CVector3& zaxis);
		//	取值。
		inline float operator [] (const int i) const
		{
			return (&w)[i];
		}
		inline float& operator [] (const int i)
		{
			return (&w)[i];
		}
		//	重載 (負號)。
		inline CQuaternion operator - () const { return CQuaternion (-w, -x, -y, -z); }
		//	重載 (指定)。
		inline CQuaternion& operator = (const CQuaternion& qt) { w = qt.w; x = qt.x; y = qt.y; z = qt.z; return *this; }
		inline CQuaternion& operator = (const CMatrix3x3& mat) { Set (mat); return *this; }
		//	重載 (比較)。
		inline bool operator == (const CQuaternion& qt) const { return ((w == qt.w) && (x == qt.x) && (y == qt.y) && (z == qt.z)); }
		inline bool operator != (const CQuaternion& qt) const { return ((w != qt.w) || (x != qt.x) || (y != qt.y) || (z != qt.z)); }
	public:
		//	重載 (+)。
		inline friend CQuaternion operator + (const CQuaternion& q1, const CQuaternion& q2) { return CQuaternion (q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z); }
		//	重載 (-)。
		inline friend CQuaternion operator - (const CQuaternion& q1, const CQuaternion& q2) { return CQuaternion (q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z); }
		//	重載 (*)。
		inline friend CQuaternion operator * (const CQuaternion& q1, const CQuaternion& q2)
		{
			return CQuaternion (q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z, q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y, q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z, q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
		}
		inline friend CQuaternion operator * (const CQuaternion& qt, float scalar)
		{
			return CQuaternion (scalar * qt.w, scalar * qt.x, scalar * qt.y, scalar * qt.z);
		}
		inline friend CQuaternion operator * (float scalar, const CQuaternion& qt)
		{
			return CQuaternion (scalar * qt.w, scalar * qt.x, scalar * qt.y, scalar * qt.z);
		}
		inline friend CVector3 operator * (const CQuaternion& qt, const CVector3& v)
		{
			CVector3 uv, uuv;
			CVector3 q (qt.x, qt.y, qt.z);
			uv = q.CrossProduct (v);
			uuv = q.CrossProduct (uv);
			uv *= (2.0f * qt.w);
			uuv *= 2.0f;
			q = v + uv + uuv;
			return q;
		}
	public:
		//	單位化。
		inline void Identity () { Set (IDENTITY); }
		//	長度。
		inline float Length () const { return Math::Sqrt (w * w + x * x + y * y + z * z); }
		//	長度平方。
		inline float SquaredLength () const { return (w * w + x * x + y * y + z * z); }
		//	內積。
		inline float DotProduct (const CQuaternion& qt) const { return (w * qt.w + x * qt.x + y * qt.y + z * qt.z); }
		//	單位化。
		inline void Normalize ()
		{
			float l = 1.0f / Length ();
			x *= l;
			y *= l;
			z *= l;
		}
		//	單位化並取得長度。
		inline float NormalizeAndGetLength ()
		{
			float l = 1.0f / Length ();
			x *= l;
			y *= l;
			z *= l;
			return l;
		}
		//	單位四元數求逆。
		inline void UnitInverse () { Set (w, -x, -y, -z); }
		//	取出旋轉矩陣。
		void ToRotateMatrix (CMatrix3x3& mt) const;
		//	取出旋轉軸與旋轉徑度。
		void ToAxis (CVector3& axis, float& radian) const;
		//	取出XYZ座標系。
		void ToAxis (CVector3& xaxis, CVector3& yaxis, CVector3& zaxis) const;
		//	取出X座標系。
		CVector3 AxisX () const;
		//	取出Y座標系。
		CVector3 AxisY () const;
		//	取出Z座標系。
		CVector3 AxisZ () const;
		//	求逆。
		void Inverse ();
		//	指數。
		void Exponent ();
		//	對數。
		void Logarithm ();
		//	取得毆拉角X軸旋轉份量。
		float GetPitch (bool reproject_axis = true) const;
		//	取得毆拉角Y軸旋轉份量。
		float GetYaw (bool reproject_axis = true) const;
		//	取得毆拉角Z軸旋轉份量。
		float GetRoll (bool reproject_axis = true) const;
		//	取得歐拉角旋轉份量。
		void GetRollPitchYaw (float& roll, float& pitch, float& yaw, bool reproject_axis = true) const;
		//	是否在誤差值內。
		bool IsEqual (const CQuaternion& qt, float tolerance) const;
		//	是否為單位四元數。
		bool IsIdentity (float tolerance = 0.00001f) const;
	public:
		//	球型插值。
		static CQuaternion SphericalLerp (const CQuaternion& p, const CQuaternion& q, float t, bool shortest_path = false);
		//	球型插值。
		static CQuaternion SphericalLerpExtraSpins (const CQuaternion& p, const CQuaternion& q, float t, int extra_spins);
		//	球型二次插值。
		static void Intermediate (const CQuaternion& q1, const CQuaternion& q2, const CQuaternion& q3, CQuaternion& a, CQuaternion& b);
		//	球型二次插值。
		static CQuaternion SphericalQuadratic (const CQuaternion& p, const CQuaternion& a, const CQuaternion& b, const CQuaternion& q, float t, bool shortest_path = false);
		//	單位線性插值。
		static CQuaternion UnitLerp (const CQuaternion& p, const CQuaternion& q, float t, bool shortest_path = false);
	public:
		float w, x, y, z;
	};

};

#endif //	LionX_LionX_Graphics_Quaternion_H

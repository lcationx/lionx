#ifndef LionX_LionX_Graphics_Vector3_H
#define LionX_LionX_Graphics_Vector3_H

#include "Vector2.h"

//===========================================================================================
//	向量 ( 3D 列向量 Vector = Mat * Vector )。
//===========================================================================================

namespace LionX
{
	class CVector3
	{
	public:
		static const CVector3 ZERO;
		static const CVector3 ONE;
		static const CVector3 UNIT_X;
		static const CVector3 UNIT_Y;
		static const CVector3 UNIT_Z;
	public:
		//	建構式。
		inline CVector3 (float v = 0.0f) : x (v), y (v), z (v) { }
		inline CVector3 (float _x, float _y, float _z) : x (_x), y (_y), z (_z) { }
		inline CVector3 (const float *v) : x (v[0]), y (v[1]), z (v[2]) { }
		inline CVector3 (const int *v) : x (float (v[0])), y (float (v[1])), z (float (v[2])) { }
		inline CVector3 (const CVector2& v) : x (v.x), y (v.y), z (0.0f) { }
		inline CVector3 (const CVector3& v) : x (v.x), y (v.y), z (v.z) { }
		//	設定。
		inline void Set (float v) { x = y = z = v; }
		inline void Set (float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
		inline void Set (const float *v) { x = v[0]; y = v[1]; z = v[2]; }
		inline void Set (const int *v) { x = float (v[0]); y = float (v[1]); z = float (v[2]); }
		inline void Set (const CVector2& v) { x = v.x; y = v.y; z = 0.0f; }
		inline void Set (const CVector3& v) { x = v.x; y = v.y; z = v.z; }
		//	取值。
		inline float operator [] (int i) const { return (&x)[i]; }
		inline float& operator [] (int i) { return (&x)[i]; }
		//	轉換。
		inline void ToX () { y = z = x; }
		inline void ToY () { x = z = y; }
		inline void ToZ () { x = y = z; }
		//	重載 (負號)。
		inline CVector3 operator - () const { return CVector3 (-x, -y, -z); }
		//	重載 (比較)。
		inline bool operator == (const CVector3& v) const { return (x == v.x && y == v.y && z == v.z); }
		inline bool operator != (const CVector3& v) const { return (x != v.x || y != v.y || z != v.z); }
		//	重載 (指定)。
		inline CVector3& operator = (float v) { x = y = z = v; return *this; }
		inline CVector3& operator = (const CVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
	public:
		//	重載 (+ - * /)。
		inline CVector3& operator += (float v) { x += v; y += v; z += v; return *this; }
		inline CVector3& operator += (const CVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		inline CVector3& operator -= (float v) { x -= v; y -= v; z -= v; return *this; }
		inline CVector3& operator -= (const CVector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		inline CVector3& operator *= (float v) { x *= v; y *= v; z *= v; return *this; }
		inline CVector3& operator *= (const CVector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		inline CVector3& operator /= (float v) { x /= v; y /= v; z /= v; return *this; }
		inline friend CVector3 operator + (const CVector3& v, float k) { return CVector3 (v.x + k, v.y + k, v.z + k); }
		inline friend CVector3 operator + (const CVector3& v1, const CVector3& v2) { return CVector3 (v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
		inline friend CVector3 operator - (const CVector3& v, float k) { return CVector3 (v.x - k, v.y - k, v.z - k); }
		inline friend CVector3 operator - (const CVector3& v1, const CVector3& v2) { return CVector3 (v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
		inline friend CVector3 operator * (const CVector3& v, float k) { return CVector3 (v.x * k, v.y * k, v.z * k); }
		inline friend CVector3 operator * (const CVector3& v1, const CVector3& v2) { return CVector3 (v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
		inline friend CVector3 operator / (const CVector3& v, float k) { return CVector3 (v.x / k, v.y / k, v.z / k); }
		inline friend CVector3 operator / (const CVector3& v1, const CVector3& v2) { return CVector3 (v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
	public:
		//	單位化。
		inline void Normalize ()
		{
			float l = Length ();
			if (l < Math::ZERO) {
				*this = 0.0f;
			} else {
				*this *= (1.0f / l);
			}
		}
		//	單位化並取得長度。
		inline float NormalizeAndGetLength ()
		{
			float l = Length ();
			if (l < Math::ZERO) {
				*this = 0.0f;
				l = 0.0f;
			} else {
				*this *= (1.0f / l);
			}
			return l;
		}
		//	長度。
		inline float Length () const { return Math::Sqrt (x * x + y * y + z * z); }
		//	長度平方。
		inline float SquaredLength () const { return (x * x + y * y + z * z); }
		//	中間點。
		inline CVector3 MidPoint (const CVector3& v) const { return (v + (*this)) * 0.5f; }
		//	取大。
		inline CVector3 Max (const CVector3& v) const { return CVector3 (Math::Max (x, v.x), Math::Max (y, v.y), Math::Max (z, v.z)); }
		//	取小。
		inline CVector3 Min (const CVector3& v) const { return CVector3 (Math::Min (x, v.x), Math::Min (y, v.y), Math::Min (z, v.z)); }
		//	絕對值。
		inline void Abs () { x = Math::Abs (x); y = Math::Abs (y); z = Math::Abs (z); }
		//	取倒。
		inline void Reciprocal () { x = 1.0f / x; y = 1.0f / y;  z = 1.0f / z; }
		//	平方根。
		inline void Sqrt () { x = Math::Sqrt (x); y = Math::Sqrt (y); z = Math::Sqrt (z); }
		//	平方根取倒。
		inline void InvSqrt () { x = Math::InvSqrt (x); y = Math::InvSqrt (y); z = Math::InvSqrt (z); }
		//	取反。
		inline void InvertSign () { x = -x; y = -y; z = -z; }
		//	相等。
		inline bool IsEqual (const CVector3& other, float tolerance = std::numeric_limits<float>::epsilon ())
		{
			if (Math::Abs (other.x - x) <= tolerance && Math::Abs (other.y - y) <= tolerance && Math::Abs (other.z - z) <= tolerance)
				return true;
			return false;
		}
		//	以0.0為低標取值。
		inline void MinZero ()
		{
			if (x < 0.0f) x = 0.0f;
			if (y < 0.0f) y = 0.0f;
			if (z < 0.0f) z = 0.0f;
		}
		//	以1.0為高標取值。
		inline void MaxOne ()
		{
			if (x > 1.0f) x = 1.0f;
			if (y > 1.0f) y = 1.0f;
			if (z > 1.0f) z = 1.0f;
		}
		//	飽和處理 (限制範圍在0.0~1.0)。
		inline void Saturate () { MinZero (); MaxOne (); }
		//	取整數。
		inline void Floor () { x = Math::Floor (x); y = Math::Floor (y); z = Math::Floor (z); }
		//	以兩向量大者組成新向量。
		inline void MakeCeil (const CVector3& v)
		{
			if (v.x > x) x = v.x;
			if (v.y > y) y = v.y;
			if (v.z > z) z = v.z;
		}
		//	以兩向量小者組成新向量。
		inline void MakeFloor (const CVector3& v)
		{
			if (v.x < x) x = v.x;
			if (v.y < y) y = v.y;
			if (v.z < z) z = v.z;
		}
		//	外積。
		inline CVector3 CrossProduct (const CVector3& v) const
		{
			return CVector3 (y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}
		//	單位外積。
		inline CVector3 UnitCrossProduct (const CVector3& v) const
		{
			CVector3 cross = CrossProduct (v);
			float l = cross.Length ();
			if (l > Math::ZERO)
				return cross / l;
			return CVector3 (0.0f);
		}
		//	內積。
		inline float DotProduct (const CVector3& v) const { return x * v.x + y * v.y + z * v.z; }
		//	整數內積。
		inline float AbsDotProduct (const CVector3& v) const { return Math::Abs (x * v.x) + Math::Abs (y * v.y) + Math::Abs (z * v.z); }
		//	正交 (獲得垂直向量)。
		inline CVector3 Perpendicular () const
		{
			CVector3 v = CrossProduct (UNIT_X);
			if (v.Length () < Math::SQR_ZERO) v = CrossProduct (UNIT_Y);
			v.Normalize ();
			return v;
		}
		//	檢測長度是否為0。
		inline bool IsZeroLength () const { return Length () <= Math::SQR_ZERO; }
	public:
		float x, y, z;
	};

};

#endif //	LionX_LionX_Graphics_Vector3_H

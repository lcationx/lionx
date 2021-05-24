#ifndef LionX_LionX_Graphics_Vector2_H
#define LionX_LionX_Graphics_Vector2_H

#include "Base/Math.h"
#include "Base/Point.h"

//===========================================================================================
//	向量 ( 2D 列向量 Vector = Mat * Vector )。
//===========================================================================================

namespace LionX
{
	class CVector2
	{
	public:
		static const CVector2 ZERO;
		static const CVector2 ONE;
		static const CVector2 UNIT_X;
		static const CVector2 UNIT_Y;
	public:
		//	建構式。
		inline CVector2 (float v = 0.0f) : x (v), y (v) { }
		inline CVector2 (float _x, float _y) : x (_x), y (_y) { }
		inline CVector2 (const int *v) : x (float (v[0])), y (float (v[1])) { }
		inline CVector2 (const CVector2& v) : x (v.x), y (v.y) { }
		//	設定。
		inline void Set (float v) { x = y = v; }
		inline void Set (float _x, float _y) { x = _x; y = _y; }
		inline void Set (const float *v) { x = v[0]; y = v[1]; }
		inline void Set (const int *v) { x = float (v[0]); y = float (v[1]); }
		inline void Set (const CVector2& v) { x = v.x; y = v.y; }
		//	取值。
		inline float operator [] (int i) const { return (&x)[i]; }
		inline float& operator [] (int i) { return (&x)[i]; }
		//	轉換。
		inline void ToX () { y = x; }
		inline void ToY () { x = y; }
		//	重載 (負號)。
		inline CVector2 operator - () const { return CVector2 (-x, -y); }
		//	重載 (比較)。
		inline bool operator == (const CVector2& v) const { return (x == v.x && y == v.y); }
		inline bool operator != (const CVector2& v) const { return (x != v.x || y != v.y); }
		//	重載 (指定)。
		inline CVector2& operator = (float v) { x = v; y = v; return *this; }
		inline CVector2& operator = (const CVector2& v) { x = v.x; y = v.y; return *this; }
	public:
		//	重載 (+ - * /)。
		inline CVector2& operator += (float v) { x += v; y += v; return *this; }
		inline CVector2& operator += (const CVector2& v) { x += v.x; y += v.y; return *this; }
		inline CVector2& operator -= (float v) { x -= v; y -= v; return *this; }
		inline CVector2& operator -= (const CVector2& v) { x -= v.x; y -= v.y; return *this; }
		inline CVector2& operator *= (float v) { x *= v; y *= v; return *this; }
		inline CVector2& operator *= (const CVector2& v) { x *= v.x; y *= v.y; return *this; }
		inline CVector2& operator /= (float v) { x /= v; y /= v; return *this; }
		inline friend CVector2 operator + (const CVector2& v, float s) { return CVector2 (v.x + s, v.y + s); }
		inline friend CVector2 operator + (const CVector2& v1, const CVector2& v2) { return CVector2 (v1.x + v2.x, v1.y + v2.y); }
		inline friend CVector2 operator - (const CVector2& v, float s) { return CVector2 (v.x - s, v.y - s); }
		inline friend CVector2 operator - (const CVector2& v1, const CVector2& v2) { return CVector2 (v1.x - v2.x, v1.y - v2.y); }
		inline friend CVector2 operator * (const CVector2& v, float s) { return CVector2 (v.x * s, v.y * s); }
		inline friend CVector2 operator * (float s, const CVector2& v) { return CVector2 (v.x * s, v.y * s); }
		inline friend CVector2 operator * (const CVector2& v1, const CVector2& v2) { return CVector2 (v1.x * v2.x, v1.y * v2.y); }
		inline friend CVector2 operator / (const CVector2& v, float s) { return CVector2 (v.x / s, v.y / s); }
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
		//	依指定角度變更值。
		inline void FromAngle (float angle) { x = Math::Cos (angle); y = Math::Sin (angle); }
		//	角度。
		inline float Angle () const { return Math::ArcTan2 (y, x); }
		//	長度。
		inline float Length () const { return Math::Sqrt (x * x + y * y); }
		//	長度平方。
		inline float SquaredLength () const { return (x * x + y * y); }
		//	外積。
		inline CVector2 CrossProduct (const CVector2& v) const { return CVector2 (0, x * v.y - y * v.x); }
		//	內積。
		inline float DotProduct (const CVector2& v) const { return (x * v.x + y * v.y); }
		//	Z分量。
		inline float CrossProductZ (const CVector2& v) const { return (x * v.y - y * v.x); }
		//	相等。
		inline bool IsEqual (const CVector2& other, float tolerance = std::numeric_limits<float>::epsilon ())
		{
			if (Math::Abs (other.x - x) <= tolerance && Math::Abs (other.y - y) <= tolerance)
				return true;
			return false;
		}
	public:
		float x, y;
	};
};

#endif //	LionX_LionX_Graphics_Vector2_H

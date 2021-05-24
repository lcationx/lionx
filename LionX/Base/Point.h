#ifndef LionX_LionX_Base_Point_H
#define LionX_LionX_Base_Point_H

#include "LionX.h"

//===========================================================================================
//	點。
//===========================================================================================

namespace LionX
{
	template<typename T>
	struct Point
	{
	public:
		static Point<T> GetZeroPoint ()
		{
			Point<T> p;
			p.Set ((T)0, (T)0);
			return p;
		}
		static Point<T> Alloc (const T& _x, const T& _y)
		{
			Point<T> p;
			p.Set (_x, _y);
			return p;
		}
	public:
		inline void Set (const Point& p) { x = p.x; y = p.y; }
		inline void Set (const T& _x, const T& _y) { x = _x; y = _y; }
		inline void Reset () { x = y = (T)0; }
	public:
		inline bool operator == (const Point& p) const { return (x == p.x && y == p.y); }
		inline bool operator != (const Point& p) const { return (x != p.x || y != p.y); }
		inline Point& operator += (T s) { x += s; y += s; return *this; }
		inline Point& operator += (const Point& p) { x += p.x; y += p.y; return *this; }
		inline Point& operator -= (T s) { x -= s; y -= s; return *this; }
		inline Point& operator -= (const Point& p) { x -= p.x; y -= p.y; return *this; }
		inline Point& operator *= (T s) { x *= s; y *= s; return *this; }
		inline Point& operator *= (const Point& p) { x *= p.x; y *= p.y; return *this; }
		inline Point& operator /= (T s) { x /= s; y /= s; return *this; }
		inline Point& operator /= (const Point& p) { x /= p.x; y /= p.y; return *this; }
		inline Point operator + (float s) const { Point p; p.x = x + s; p.y = y + s; return p; }
		inline Point operator + (const Point& p1) const { Point p; p.x = x + p1.x; p.y = y + p1.y; return p; }
		friend Point operator + (float s, const Point& p1) { Point p; p.x = s + p1.x; p.y = s + p1.y; return p; }
		inline Point operator - (float s) const { Point p; p.x = x - s; p.y = y - s; return p; }
		inline Point operator - (const Point& p1) const { Point p; p.x = x - p1.x; p.y = y - p1.y; return p; }
		friend Point operator - (float s, const Point& p1) { Point p; p.x = s - p1.x; p.y = s - p1.y; return p; }
		inline Point operator * (float s) const { Point p; p.x = x * s; p.y = y * s; return p; }
		inline Point operator * (const Point& p1) const { Point p; p.x = x * p1.x; p.y = y * p1.y; return p; }
		friend Point operator * (float s, const Point& p1) { Point p; p.x = s * p1.x; p.y = s * p1.y; return p; }
		inline Point operator / (float s) const { Point p; p.x = x / s; p.y = y / s; return p; }
		inline Point operator / (const Point& p1) const { Point p; p.x = x / p1.x; p.y = y / p1.y; return p; }
		friend Point operator / (float s, const Point& p1) { Point p; p.x = s / p1.x; p.y = s / p1.y; return p; }
		inline Point operator - () const { Point p; p.x = -x; p.y = -y; return p; }
	public:
		T x;
		T y;
	};

	typedef Point<Int32> SPoint;
	typedef Point<float> PointF;
};

#endif //	LionX_LionX_Base_Point_H

#ifndef LionX_LionX_Base_Rect_H
#define LionX_LionX_Base_Rect_H

#include "Point.h"
#include "Math.h"

//===========================================================================================
//	矩形。
//===========================================================================================

namespace LionX
{
	template<typename T>
	class Rect
	{
	public:
		inline Rect ()
			: left (0), top (0), right (0), bottom (0)
		{ }
		inline Rect (const T& _left, const T& _top, const T& _right, const T& _bottom)
			: left (_left), top (_top), right (_right), bottom (_bottom)
		{ }
		inline Rect (const Point<T>& lt, const Point<T>& rb)
			: left (lt.x), top (lt.y), right (rb.x), bottom (rb.y)
		{ }
		inline void Set (const T& _left, const T& _top, const T& _right, const T& _bottom)
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}
		inline void Reset () { left = top = right = bottom = (T)0; }
		inline T GetW () const { return (right - left); }
		inline T GetH () const { return (bottom - top); }
		inline T GetRH () const { return (top - bottom); }
		inline T Area () const { return (GetW () * GetH ()); }
		inline Rect GetOverlay (const Rect& r) const
		{
			return Rect (Math::Max (left, r.left), Math::Max (top, r.top), Math::Min (right, r.right), Math::Min (bottom, r.bottom));
		}
		inline bool IsOverlay (const Rect& r) const
		{
			return (left <= r.left && top <= r.top && right >= r.right && bottom >= r.bottom);
		}
		inline bool IsInClient (const T& x, const T& y) const
		{
			return (x >= left && y >= top && x <= right && y <= bottom);
		}
		inline bool IsInRClient (const T& x, const T& y) const
		{
			return (x >= left && y >= bottom && x <= right && y <= top);
		}
		inline bool IsCollision (const Rect& r) const
		{
			Point<T> c = GetCenter (), c1 = r.GetCenter ();
			return ((Math::Abs (c.x - c1.x) < ((GetW () + r.GetW ()) / 2)) && (Math::Abs (c.y - c1.y) < ((GetH () + r.GetH ()) / 2)));
		}
		inline Point<T> GetCenter () const
		{
			return Point<T>::Alloc (left + ((right - left) / 2), top + ((bottom - top) / 2));
		}
	public:
		inline bool operator == (const Rect& r) const { return (left == r.left && top == r.top && right == r.right && bottom == r.bottom); }
		inline bool operator != (const Rect& r) const { return (left != r.left || top != r.top || right != r.right || bottom != r.bottom); }
		inline Rect& operator = (const Rect& r) { left = r.left; top = r.top; right = r.right; bottom = r.bottom; return *this; }
		inline Rect operator - () const { return Rect (-left, -top, -right, -bottom); }
	public:
		union
		{
			struct {
				Point<T> LT;
				Point<T> RB;
			};
			struct {
				T left;
				T top;
				T right;
				T bottom;
			};
		};
	};

	typedef Rect<Int32> SRect;
	typedef Rect<float> RectF;
};

#endif //	LionX_LionX_Base_Rect_H

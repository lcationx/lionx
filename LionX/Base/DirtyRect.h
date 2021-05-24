#ifndef LionX_LionX_Base_DirtyRect_H
#define LionX_LionX_Base_DirtyRect_H

#include "Rect.h"

//===========================================================================================
//	贓矩形。
//===========================================================================================

namespace LionX
{
	template<typename T>
	class DirtyRect
	{
	public:
		DirtyRect ()
		{
		}
		void AddRect (const Rect<T>& r)
		{
			mRects.push_back (r);
		}
		void AddRect (const T& l, const T& t, const T& r, const T& b)
		{
			AddRect (Rect<T> (l, t, r, b));
		}
		bool IsOverlay (const Rect<T>& r, size_t pos = 0) const
		{
			for (size_t i = pos; i < mRects.size (); ++ i) {
				if ( mRects[i].IsOverlay (r) )
					return true;
				Rect<T> ov = mRects[i].GetOverlay (r);
				if (mRects[i].IsOverlay (ov) == false)
					continue;
				if (r.left < mRects[i].left) {
					Rect<T> tr (r.left, r.top, ov.left, r.bottom);
					if ( !IsOverlay (tr, i + 1) )
						return false;
				}
				if (r.top < mRects[i].top) {
					Rect<T> tr (ov.left, r.top, r.right, ov.top);
					if ( !IsOverlay (tr, i + 1) )
						return false;
				}
				if (r.right > mRects[i].right) {
					Rect<T> tr (ov.right, ov.top, r.right, r.bottom);
					if ( !IsOverlay (tr, i + 1) )
						return false;
				}
				if (r.bottom > mRects[i].bottom) {
					Rect<T> tr (ov.left, ov.bottom, ov.right, r.bottom);
					if ( !IsOverlay (tr, i + 1) )
						return false;
				}
				return true;
			}
			return false;
		}
		void Clear ()
		{
			mRects.clear ();
		}
		inline const std::vector< Rect<T> >& GetDirtyRects () const
		{
			return mRects;
		}
		~DirtyRect ()
		{
			Clear ();
		}
	private:
		std::vector< Rect<T> > mRects;
	};

	typedef DirtyRect<Int32> SDirtyRect;
	typedef DirtyRect<float> DirtyRectF;
};

#endif //	LionX_LionX_Base_DirtyRect_H

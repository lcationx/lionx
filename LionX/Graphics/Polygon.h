#ifndef LionX_LionX_Graphics_Polygon_H
#define LionX_LionX_Graphics_Polygon_H

#include "Graphics.h"
#include "Vector2.h"

//===========================================================================================
//	多邊形 (頂點必須依順時針放入)。
//===========================================================================================

namespace LionX
{
	class CPolygon
	{
	public:
		CPolygon ();
		CPolygon (const CVector2& lt, const CVector2& rt, const CVector2& rb, const CVector2& lb);
		CPolygon (const std::vector<CVector2>& points);
		//	設定矩形。
		void SetRectangle (const CVector2& center, float width, float height);
		void SetRectangle (const CVector2& lt, const CVector2& rt, const CVector2& rb, const CVector2& lb);
		//	快速算法，只能拿來合併不重疊矩形。
		bool MergeRectangle (const CPolygon& other);
		//	點是否在多邊形內。
		bool IsInside (const CVector2& point) const;
		//	計算點到點之間的路徑。
		void CalculationPath (const CVector2& src_point, const CVector2& dest_point, std::vector<CVector2>& path_points);
		//	取得最近的碰撞點。
		bool GetNearIntersect (const CVector2& src_point, const CVector2& dest_point, CVector2& ins_point);
		//	取得最遠的碰撞點。
		bool GetFarIntersect (const CVector2& src_point, const CVector2& dest_point, CVector2& ins_point);
		//	取得穿透線最近的碰撞點。
		bool GetPenetrateNearIntersect (const CVector2& src_point, const CVector2& dest_point, CVector2& ins_point);
		//	是否發生碰撞。
		bool IsBlock (const CVector2& src_point, const CVector2& dest_point);
		~CPolygon ();
	public:
		inline int Size () const { return (int)mPoints.size (); }
		inline const CVector2& operator [] (size_t idx) const { return mPoints[idx]; }
		inline CVector2& operator [] (size_t idx) { return mPoints[idx]; }
	public:
		std::vector<CVector2> mPoints;
	};
};

#endif //	LionX_LionX_Graphics_Polygon_H

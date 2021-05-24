#ifndef LionX_LionX_Graphics_Graphics_H
#define LionX_LionX_Graphics_Graphics_H

#include "Quaternion.h"
#include "Vector2.h"
#include "Plane.h"
#include "Transform.h"

//===========================================================================================
//	圖學庫。
//===========================================================================================

namespace LionX
{
	//===========================================================================================
	//	常數。
	//===========================================================================================

	//===========================================================================================
	//	2D。
	//===========================================================================================

	// 兩個座標的快速叉乘. va->vb X vc->vd。
	float CrossProductTowVector2 (const CVector2& va, const CVector2& vb, const CVector2& vc, const CVector2& vd);
	//	取得向量角度。
	float GetVectorAngle (const CVector2& v);
	//	檢測線段 va->vb 與 vc->vd 是否相交 line_hit_range_1 = 線段va-vb相交於線段的位置佔比 line_hit_range_2 = 線段vc-vd相交於線段的位置佔比。
	bool IsLineIntersect (const CVector2& va, const CVector2& vb, const CVector2& vc, const CVector2& vd, float* line_hit_range_1 = nullptr, float* line_hit_range_2 = nullptr);
	//	檢測線段 va->vb 與 vc->vd 是否重疊。
	bool IsLineOverlap (const CVector2& va, const CVector2& vb, const CVector2& vc, const CVector2& vd);
	//	檢測線段 va->vb 與 vc->vd 是否平行。
	bool IsLineParallel (const CVector2& va, const CVector2& vb, const CVector2& vc, const CVector2& vd);
	//	檢測線段 va->vb 與 vc->vd 是否相交，並取出相交點。	bool GetLineIntersect (const CVector2& va, const CVector2& vb, const CVector2& vc, const CVector2& vd, CVector2& contract_point);
	//	計算座標 vc 到線段 va->vb 的距離。
	float GetPointToLineDistance (const CVector2& va, const CVector2& vb, const CVector2& vc);


	//===========================================================================================
	//===========================================================================================
};

#endif //	LionX_LionX_Graphics_Graphics_H

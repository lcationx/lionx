#ifndef LionX_LionX_Math_Matrix4x4_H
#define LionX_LionX_Math_Matrix4x4_H

#include "Matrix3x3.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Transform.h"

//===========================================================================================
//	矩陣 ( 4 x 4 行主序儲存 )。
//===========================================================================================

namespace LionX
{
	class CMatrix4x4
	{
	public:
		//	零矩陣。
		static const CMatrix4x4 ZERO;
		//	單位矩陣。
		static const CMatrix4x4 IDENTITY;
	public:
		//	建構式。
		inline CMatrix4x4 () { }
		inline CMatrix4x4 (const float v) { Set (v); }
		inline CMatrix4x4 (const float _00, const float _01, const float _02, const float _03, const float _10, const float _11, const float _12, const float _13, const float _20, const float _21, const float _22, const float _23, const float _30, const float _31, const float _32, const float _33)
			: m00 (_00), m01 (_01), m02 (_02), m03 (_03), m10 (_10), m11 (_11), m12 (_12), m13 (_13), m20 (_20), m21 (_21), m22 (_22), m23 (_23), m30 (_30), m31 (_31), m32 (_32), m33 (_33) { }
		inline CMatrix4x4 (const float* v) { memcpy (m, v, sizeof (float[4][4])); }
		inline CMatrix4x4 (const CMatrix4x4& mt) { memcpy (m, mt.m, sizeof (float[4][4])); }
		//	設定。
		inline void Set (const float v) { m00 = m01 = m02 = m03 = m10 = m11 = m12 = m13 = m20 = m21 = m22 = m23 = m30 = m31 = m32 = m33 = v; }
		inline void Set (const float _00, const float _01, const float _02, const float _03, const float _10, const float _11, const float _12, const float _13, const float _20, const float _21, const float _22, const float _23, const float _30, const float _31, const float _32, const float _33)
		{
			m00 = _00; m01 = _01; m02 = _02; m03 = _03;
			m10 = _10; m11 = _11; m12 = _12; m13 = _13;
			m20 = _20; m21 = _21; m22 = _22; m23 = _23;
			m30 = _30; m31 = _31; m32 = _32; m33 = _33;
		}
		inline void Set (const float* v) { memcpy (m, v, sizeof (float[4][4])); }
		inline void Set (const CMatrix4x4& mt) { memcpy (m, mt.m, sizeof (float[4][4])); }
		//	設定。
		inline void SetRow (const int row, const float x, const float y, const float z, const float w)
		{
			m[row][0] = x;
			m[row][1] = y;
			m[row][2] = z;
			m[row][3] = w;
		}
		inline void SetColumn (const int col, const float x, const float y, const float z, const float w)
		{
			m[0][col] = x;
			m[1][col] = y;
			m[2][col] = z;
			m[3][col] = w;
		}
		//	取值。
		inline float operator () (const int i, const int j) const
		{
			return m[i][j];
		}
		inline float& operator () (const int i, const int j)
		{
			return m[i][j];
		}
		//	重載 (負號)。
		inline CMatrix4x4 operator - () const
		{
			return CMatrix4x4 (-m00, -m01, -m02, -m03, -m10, -m11, -m12, -m13, -m20, -m21, -m22, -m23, -m30, -m31, -m32, -m33);
		}
		//	重載 (比較)。
		inline bool operator == (const CMatrix4x4& mt) const
		{
			return (m00 == mt.m00 && m01 == mt.m01 && m02 == mt.m02 && m03 == mt.m03 && m10 == mt.m10 && m11 == mt.m11 && m12 == mt.m12 && m13 == mt.m13 && m20 == mt.m20 && m21 == mt.m21 && m22 == mt.m22 && m23 == mt.m23 && m30 == mt.m30 && m31 == mt.m31 && m32 == mt.m32 && m33 == mt.m33);
		}
		inline bool operator != (const CMatrix4x4& mt) const
		{
			return (m00 != mt.m00 || m01 != mt.m01 || m02 != mt.m02 || m03 != mt.m03 || m10 != mt.m10 || m11 != mt.m11 || m12 != mt.m12 || m13 != mt.m13 || m20 != mt.m20 || m21 != mt.m21 || m22 != mt.m22 || m23 != mt.m23 || m30 != mt.m30 || m31 != mt.m31 || m32 != mt.m32 || m33 != mt.m33);
		}
		//	重載 (指定)。
		inline CMatrix4x4& operator = (const float v) { Set (v); return *this; }
		inline CMatrix4x4& operator = (const CMatrix4x4& mt) { Set (mt); return *this; }
	public:
		//	重載 (+=)。
		inline CMatrix4x4& operator += (const float v)
		{
			m00 += v; m01 += v; m02 += v; m03 += v;
			m10 += v; m11 += v; m12 += v; m13 += v;
			m20 += v; m21 += v; m22 += v; m23 += v;
			m30 += v; m31 += v; m32 += v; m33 += v;
			return *this;
		}
		inline CMatrix4x4& operator += (const CMatrix4x4& mt)
		{
			m00 += mt.m00; m01 += mt.m01; m02 += mt.m02; m03 += mt.m03;
			m10 += mt.m10; m11 += mt.m11; m12 += mt.m12; m13 += mt.m13;
			m20 += mt.m20; m21 += mt.m21; m22 += mt.m22; m23 += mt.m23;
			m30 += mt.m30; m31 += mt.m31; m32 += mt.m32; m33 += mt.m33;
			return *this;
		}
		//	重載 (-=)。
		inline CMatrix4x4& operator -= (const float v)
		{
			m00 -= v; m01 -= v; m02 -= v; m03 -= v;
			m10 -= v; m11 -= v; m12 -= v; m13 -= v;
			m20 -= v; m21 -= v; m22 -= v; m23 -= v;
			m30 -= v; m31 -= v; m32 -= v; m33 -= v;
			return *this;
		}
		inline CMatrix4x4& operator -= (const CMatrix4x4& mt)
		{
			m00 -= mt.m00; m01 -= mt.m01; m02 -= mt.m02; m03 -= mt.m03;
			m10 -= mt.m10; m11 -= mt.m11; m12 -= mt.m12; m13 -= mt.m13;
			m20 -= mt.m20; m21 -= mt.m21; m22 -= mt.m22; m23 -= mt.m23;
			m30 -= mt.m30; m31 -= mt.m31; m32 -= mt.m32; m33 -= mt.m33;
			return *this;
		}
		//	重載 (*=)。
		inline CMatrix4x4& operator *= (const float v)
		{
			m00 *= v; m01 *= v; m02 *= v; m03 *= v;
			m10 *= v; m11 *= v; m12 *= v; m13 *= v;
			m20 *= v; m21 *= v; m22 *= v; m23 *= v;
			m30 *= v; m31 *= v; m32 *= v; m33 *= v;
			return *this;
		}
		inline CMatrix4x4& operator *= (const CMatrix4x4& mt)
		{
			Set (m00 * mt.m00 + m01 * mt.m10 + m02 * mt.m20 + m03 * mt.m30,
				m00 * mt.m01 + m01 * mt.m11 + m02 * mt.m21 + m03 * mt.m31,
				m00 * mt.m02 + m01 * mt.m12 + m02 * mt.m22 + m03 * mt.m32,
				m00 * mt.m03 + m01 * mt.m13 + m02 * mt.m23 + m03 * mt.m33,

				m10 * mt.m00 + m11 * mt.m10 + m12 * mt.m20 + m13 * mt.m30,
				m10 * mt.m01 + m11 * mt.m11 + m12 * mt.m21 + m13 * mt.m31,
				m10 * mt.m02 + m11 * mt.m12 + m12 * mt.m22 + m13 * mt.m32,
				m10 * mt.m03 + m11 * mt.m13 + m12 * mt.m23 + m13 * mt.m33,

				m20 * mt.m00 + m21 * mt.m10 + m22 * mt.m20 + m23 * mt.m30,
				m20 * mt.m01 + m21 * mt.m11 + m22 * mt.m21 + m23 * mt.m31,
				m20 * mt.m02 + m21 * mt.m12 + m22 * mt.m22 + m23 * mt.m32,
				m20 * mt.m03 + m21 * mt.m13 + m22 * mt.m23 + m23 * mt.m33,

				m30 * mt.m00 + m31 * mt.m10 + m32 * mt.m20 + m33 * mt.m30,
				m30 * mt.m01 + m31 * mt.m11 + m32 * mt.m21 + m33 * mt.m31,
				m30 * mt.m02 + m31 * mt.m12 + m32 * mt.m22 + m33 * mt.m32,
				m30 * mt.m03 + m31 * mt.m13 + m32 * mt.m23 + m33 * mt.m33);
			return *this;
		}
		//	重載 (/=)。
		inline CMatrix4x4& operator /= (const float v)
		{
			m00 /= v; m01 /= v; m02 /= v; m03 /= v;
			m10 /= v; m11 /= v; m12 /= v; m13 /= v;
			m20 /= v; m21 /= v; m22 /= v; m23 /= v;
			m30 /= v; m31 /= v; m32 /= v; m33 /= v;
			return *this;
		}
	public:
		//	重載 (+)。
		inline friend CMatrix4x4 operator + (const CMatrix4x4& mt, const float v) { CMatrix4x4 r = mt; r += v; return r; }
		inline friend CMatrix4x4 operator + (const float v, const CMatrix4x4& mt) { CMatrix4x4 r = mt; r += v; return r; }
		inline friend CMatrix4x4 operator + (const CMatrix4x4& mt1, const CMatrix4x4& mt2) { CMatrix4x4 r = mt1; r += mt2; return r; }
		//	重載 (-)。
		inline friend CMatrix4x4 operator - (const CMatrix4x4& mt, const float v) { CMatrix4x4 r = mt; r -= v; return r; }
		inline friend CMatrix4x4 operator - (const float v, const CMatrix4x4& mt) { CMatrix4x4 r = v; r -= mt; return r; }
		inline friend CMatrix4x4 operator - (const CMatrix4x4& mt1, const CMatrix4x4& mt2) { CMatrix4x4 r = mt1; r -= mt2; return r; }
		//	重載 (*)。
		inline friend CMatrix4x4 operator * (const CMatrix4x4& mt, const float v) { CMatrix4x4 r = mt; r *= v; return r; }
		inline friend CMatrix4x4 operator * (const float v, const CMatrix4x4& mt) { CMatrix4x4 r = mt; r *= v; return r; }
		inline friend CVector3 operator * (const CMatrix4x4& mt, const CVector3& v)
		{
			float invw = 1.0f / (mt.m30 * v.x + mt.m31 * v.y + mt.m32 * v.z + mt.m33);
			return CVector3 ((mt.m00 * v.x + mt.m01 * v.y + mt.m02 * v.z + mt.m03) * invw,
				(mt.m10 * v.x + mt.m11 * v.y + mt.m12 * v.z + mt.m13) * invw,
				(mt.m20 * v.x + mt.m21 * v.y + mt.m22 * v.z + mt.m23) * invw);
		}
		inline friend CMatrix4x4 operator * (const CMatrix4x4& mt1, const CMatrix4x4& mt2) { CMatrix4x4 r = mt1; r *= mt2; return r; }
		//	重載 (/)。
		inline friend CMatrix4x4 operator / (const CMatrix4x4& mt, const float v) { CMatrix4x4 r = mt; r /= v; return r; }
	public:
		//	單位化。
		inline void Identity () { Set (IDENTITY); }
		//	轉置。
		inline void Transpose () { Math::Swap (m01, m10); Math::Swap (m02, m20); Math::Swap (m03, m30); Math::Swap (m12, m21); Math::Swap (m13, m31);  Math::Swap (m23, m32); }
		//	設定縮放。
		inline void SetScale (const CVector3& v)
		{
			m00 = v.x;
			m11 = v.y;
			m22 = v.z;
		}
		inline void SetScale (const float x, const float y, const float z)
		{
			m00 = x;
			m11 = y;
			m22 = z;
		}
		//	產生縮放矩陣。
		inline void MakeScale (const CVector3& v)
		{
			m00 = v.x; m01 = m02 = m03 = 0.0f;
			m11 = v.y; m10 = m12 = m13 = 0.0f;
			m22 = v.z; m20 = m21 = m23 = 0.0f;
			m30 = m31 = m32 = 0.0f; m33 = 1.0f;
		}
		inline void MakeScale (const float x, const float y, const float z)
		{
			m00 = x; m01 = m02 = m03 = 0.0f;
			m11 = y; m10 = m12 = m13 = 0.0f;
			m22 = z; m20 = m21 = m23 = 0.0f;
			m30 = m31 = m32 = 0.0f; m33 = 1.0f;
		}
		//	是否包含-的縮放單位。
		inline bool HasNegativeScale () const
		{
			return (Determinant () < 0.0f);
		}
		//	設定位移。
		inline void SetTranslate (const CVector3& v)
		{
			m03 = v.x;
			m13 = v.y;
			m23 = v.z;
		}
		inline void SetTranslate (const float x, const float y, const float z)
		{
			m03 = x;
			m13 = y;
			m23 = z;
		}
		//	產生位移矩陣。
		inline void MakeTranslate (const CVector3& v)
		{
			m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = v.x;
			m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = v.y;
			m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = v.z;
			m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		}
		inline void MakeTranslate (const float x, const float y, const float z)
		{
			m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = x;
			m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = y;
			m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = z;
			m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		}
		//	取出位移資訊。
		inline CVector3 GetTranslate () const { return CVector3 (m[0][3], m[1][3], m[2][3]); }
		//	設定3x3矩陣。
		inline void FromMatrix3x3 (CMatrix3x3& mat3)
		{
			m00 = mat3.m00; m01 = mat3.m01; m02 = mat3.m02;
			m10 = mat3.m10; m11 = mat3.m11; m12 = mat3.m12;
			m20 = mat3.m20; m21 = mat3.m21; m22 = mat3.m22;
		}
		//	取得3x3矩陣。
		inline void ExtractMatrix3x3 (CMatrix3x3& mat3) const
		{
			mat3.m00 = m00; mat3.m01 = m01; mat3.m02 = m02;
			mat3.m10 = m10; mat3.m11 = m11; mat3.m12 = m12;
			mat3.m20 = m20; mat3.m21 = m21; mat3.m22 = m22;
		}
		inline CMatrix3x3 ExtractMatrix3x3 () const
		{
			return CMatrix3x3 (m00, m01, m02, m10, m11, m12, m20, m21, m22);
		}
		//	行列式。
		float Determinant () const;
		//	伴隨矩陣。
		CMatrix4x4 AdjointMatrix () const;
		//	求逆。
		inline void Inverse () { (*this) = (1.0f / Determinant ()) * AdjointMatrix (); }
		//	求逆 (正交矩陣使用的快速轉換)。
		inline void FastInverse () { CVector3 v (m[3]); v.InvertSign (); m30 = m31 = m32 = 0.0f; m33 = 1.0f; Transpose (); SetTranslate (v); }
		//	是否為仿射矩陣。
		inline bool isAffine (void) const
		{
			return m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1;
		}
		//	依照指定的旋轉、縮放、位置，產生矩陣 (先旋轉 再縮放 再轉移 位移 + 縮放 * 旋轉 * P)。
		void MakeTransform (const CVector3& translate, const CVector3& scale, const CMatrix3x3& rotate);
		//	依照指定的旋轉、縮放、位置，產生矩陣 (先旋轉 再縮放 再轉移 位移 + 縮放 * 旋轉 * P)。
		inline void MakeTransform (const CTransform& transform) { MakeTransform (transform.mTranslate, CVector3 (transform.mScale), transform.mRotate); }
		//	依照指定的旋轉、縮放、位置，產生矩陣 (先旋轉 再縮放 再轉移 位移 + 縮放 * 旋轉 * P。
		void MakeTransform (const CVector3& translate, const CVector3& scale, const CQuaternion& rotate);
		//	依照指定的旋轉、縮放、位置，產生對應的逆矩陣 (先旋轉 再縮放 再轉移 位移 + 縮放 * 旋轉 * P)。
		void MakeInverseTransform (const CVector3& translate, const CVector3& scale, const CQuaternion& rotate);
		//	將矩陣的旋轉位移縮放資訊提出。
		void Decomposition (CVector3& translate, CVector3& scale, CMatrix3x3& rotate) const;
		//	將矩陣的旋轉位移縮放資訊提出。
		inline void Decomposition (CTransform& transform) const { CVector3 scale; Decomposition (transform.mTranslate, scale, transform.mRotate); transform.mScale = scale.x; }
		//	將矩陣的旋轉位移縮放資訊提出。
		void Decomposition (CVector3& translate, CVector3& scale, CQuaternion& rotate) const;
	public:
		//	矩陣資訊。
		union
		{
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
			float m[4][4];
		};
	};
};

#endif //	LionX_LionX_Math_Matrix4x4_H

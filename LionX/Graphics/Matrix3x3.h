#ifndef LionX_LionX_Graphics_Matrix3x3_H
#define LionX_LionX_Graphics_Matrix3x3_H

#include "Vector3.h"

//===========================================================================================
//	矩陣 ( 3 x 3 行主序儲存 )。
//===========================================================================================

namespace LionX
{
	class CMatrix3x3
	{
	public:
		static const CMatrix3x3 ZERO;
		static const CMatrix3x3 IDENTITY;
	public:
		//	建構式。
		inline CMatrix3x3 () { }
		inline CMatrix3x3 (const float v) : m00 (v), m01 (v), m02 (v), m10 (v), m11 (v), m12 (v), m20 (v), m21 (v), m22 (v) { }
		inline CMatrix3x3 (const float _00, const float _01, const float _02, const float _10, const float _11, const float _12, const float _20, const float _21, const float _22)
			: m00 (_00), m01 (_01), m02 (_02), m10 (_10), m11 (_11), m12 (_12), m20 (_20), m21 (_21), m22 (_22) { }
		inline CMatrix3x3 (const float* v) { memcpy (m, v, sizeof (float[3][3])); }
		inline CMatrix3x3 (const CVector3& c0, const CVector3& c1, const CVector3& c2) { SetColumn (0, c0); SetColumn (1, c1); SetColumn (2, c2); }
		inline CMatrix3x3 (const CMatrix3x3& mt) { memcpy (m, mt.m, sizeof (float[3][3])); }
		//	設定。
		inline void Set (const float v) { m00 = m01 = m02 = m10 = m11 = m12 = m20 = m21 = m22 = v; }
		inline void Set (const float _00, const float _01, const float _02, const float _10, const float _11, const float _12, const float _20, const float _21, const float _22)
		{
			m00 = _00; m01 = _01; m02 = _02;
			m10 = _10; m11 = _11; m12 = _12;
			m20 = _20; m21 = _21; m22 = _22;
		}
		inline void Set (const float* v) { memcpy (m, v, sizeof (float[3][3])); }
		inline void Set (const CMatrix3x3& mt) { memcpy (m, mt.m, sizeof (float[3][3])); }
		//	設定。
		inline void SetRow (const int row, const CVector3& v)
		{
			m[row][0] = v.x;
			m[row][1] = v.y;
			m[row][2] = v.z;
		}
		inline void SetRow (const int row, const float x, const float y, const float z)
		{
			m[row][0] = x;
			m[row][1] = y;
			m[row][2] = z;
		}
		inline void SetRow (const int row, const float* v)
		{
			m[row][0] = v[0];
			m[row][1] = v[1];
			m[row][2] = v[2];
		}
		inline void SetColumn (const int col, const CVector3& v)
		{
			m[0][col] = v.x;
			m[1][col] = v.y;
			m[2][col] = v.z;
		}
		inline void SetColumn (const int col, const float x, const float y, const float z)
		{
			m[0][col] = x;
			m[1][col] = y;
			m[2][col] = z;
		}
		inline void SetColumn (const int col, const float* v)
		{
			m[0][col] = v[0];
			m[1][col] = v[1];
			m[2][col] = v[2];
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
		inline void GetRow (const int row, CVector3& v) const
		{
			v.x = m[row][0];
			v.y = m[row][1];
			v.z = m[row][2];
		}
		inline void GetRow (const int row, float& x, float& y, float& z) const
		{
			x = m[row][0];
			y = m[row][1];
			z = m[row][2];
		}
		inline void GetRow (const int row, float* v) const
		{
			v[0] = m[row][0];
			v[1] = m[row][1];
			v[2] = m[row][2];
		}
		inline void GetColumn (const int col, CVector3& v) const
		{
			v.x = m[0][col];
			v.y = m[1][col];
			v.z = m[2][col];
		}
		inline void GetColumn (const int col, float& x, float& y, float& z) const
		{
			x = m[0][col];
			y = m[1][col];
			z = m[2][col];
		}
		inline void GetColumn (const int col, float* v) const
		{
			v[0] = m[0][col];
			v[1] = m[1][col];
			v[2] = m[2][col];
		}
		//	重載 (負號)。
		inline CMatrix3x3 operator - () const { return CMatrix3x3 (-m00, -m01, -m02, -m10, -m11, -m12, -m20, -m21, -m22); }
		//	重載 (比較)。
		inline bool operator == (const CMatrix3x3& mt) const
		{
			return (m00 == mt.m00 && m01 == mt.m01 && m02 == mt.m02 && m10 == mt.m10 && m11 == mt.m11 && m12 == mt.m12 && m20 == mt.m20 && m21 == mt.m21 && m22 == mt.m22);
		}
		inline bool operator != (const CMatrix3x3& mt) const
		{
			return (m00 != mt.m00 || m01 != mt.m01 || m02 != mt.m02 || m10 != mt.m10 || m11 != mt.m11 || m12 != mt.m12 || m20 != mt.m20 || m21 != mt.m21 || m22 != mt.m22);
		}
		//	重載 (指定)。
		inline CMatrix3x3& operator = (const float v) { Set (v); return *this; }
		inline CMatrix3x3& operator = (const CMatrix3x3& mt) { Set (mt); return *this; }
	public:
		//	重載 (+=)。
		inline CMatrix3x3& operator += (const float v)
		{
			m00 += v; m01 += v; m02 += v;
			m10 += v; m11 += v; m12 += v;
			m20 += v; m21 += v; m22 += v;
			return *this;
		}
		inline CMatrix3x3& operator += (const CMatrix3x3& mt)
		{
			m00 += mt.m00; m01 += mt.m01; m02 += mt.m02;
			m10 += mt.m10; m11 += mt.m11; m12 += mt.m12;
			m20 += mt.m20; m21 += mt.m21; m22 += mt.m22;
			return *this;
		}
		//	重載 (-=)。
		inline CMatrix3x3& operator -= (const float v)
		{
			m00 -= v; m01 -= v; m02 -= v;
			m10 -= v; m11 -= v; m12 -= v;
			m20 -= v; m21 -= v; m22 -= v;
			return *this;
		}
		inline CMatrix3x3& operator -= (const CMatrix3x3& mt)
		{
			m00 -= mt.m00; m01 -= mt.m01; m02 -= mt.m02;
			m10 -= mt.m10; m11 -= mt.m11; m12 -= mt.m12;
			m20 -= mt.m20; m21 -= mt.m21; m22 -= mt.m22;
			return *this;
		}
		//	重載 (*=)。
		inline CMatrix3x3& operator *= (const float v)
		{
			m00 *= v; m01 *= v; m02 *= v;
			m10 *= v; m11 *= v; m12 *= v;
			m20 *= v; m21 *= v; m22 *= v;
			return *this;
		}
		inline CMatrix3x3& operator *= (const CMatrix3x3& mt)
		{
			Set (m00 * mt.m00 + m01 * mt.m10 + m02 * mt.m20,
				m00 * mt.m01 + m01 * mt.m11 + m02 * mt.m21,
				m00 * mt.m02 + m01 * mt.m12 + m02 * mt.m22,

				m10 * mt.m00 + m11 * mt.m10 + m12 * mt.m20,
				m10 * mt.m01 + m11 * mt.m11 + m12 * mt.m21,
				m10 * mt.m02 + m11 * mt.m12 + m12 * mt.m22,

				m20 * mt.m00 + m21 * mt.m10 + m22 * mt.m20,
				m20 * mt.m01 + m21 * mt.m11 + m22 * mt.m21,
				m20 * mt.m02 + m21 * mt.m12 + m22 * mt.m22);
			return *this;
		}
		//	重載 (/=)。
		inline CMatrix3x3& operator /= (const float v)
		{
			m00 /= v; m01 /= v; m02 /= v;
			m10 /= v; m11 /= v; m12 /= v;
			m20 /= v; m21 /= v; m22 /= v;
			return *this;
		}
	public:
		//	重載 (+ - * /)。
		inline friend CMatrix3x3 operator + (const CMatrix3x3& mt, const float v) { CMatrix3x3 r = mt; r += v; return r; }
		inline friend CMatrix3x3 operator + (const float v, const CMatrix3x3& mt) { CMatrix3x3 r = mt; r += v; return r; }
		inline friend CMatrix3x3 operator + (const CMatrix3x3& mt1, const CMatrix3x3& mt2) { CMatrix3x3 r = mt1; r += mt2; return r; }
		inline friend CMatrix3x3 operator - (const CMatrix3x3& mt, const float v) { CMatrix3x3 r = mt; r -= v; return r; }
		inline friend CMatrix3x3 operator - (const float v, const CMatrix3x3& mt) { CMatrix3x3 r = v; r -= mt; return r; }
		inline friend CMatrix3x3 operator - (const CMatrix3x3& mt1, const CMatrix3x3& mt2) { CMatrix3x3 r = mt1; r -= mt2; return r; }
		inline friend CMatrix3x3 operator * (const CMatrix3x3& mt, const float v) { CMatrix3x3 r = mt; r *= v; return r; }
		inline friend CMatrix3x3 operator * (const float v, const CMatrix3x3& mt) { CMatrix3x3 r = mt; r *= v; return r; }
		inline friend CVector3 operator * (const CMatrix3x3& mt, const CVector3& v)
		{
			return CVector3 (mt.m00 * v.x + mt.m01 * v.y + mt.m02 * v.z,
				mt.m10 * v.x + mt.m11 * v.y + mt.m12 * v.z,
				mt.m20 * v.x + mt.m21 * v.y + mt.m22 * v.z);
		}
		inline friend CVector3 operator * (const CVector3& v, const CMatrix3x3& mt)
		{
			return CVector3 (v.x * mt.m00 + v.y * mt.m10 + v.z * mt.m20,
				v.x * mt.m01 + v.y * mt.m11 + v.z * mt.m21,
				v.x * mt.m02 + v.y * mt.m12 + v.z * mt.m22);
		}
		inline friend CMatrix3x3 operator * (const CMatrix3x3& mt1, const CMatrix3x3& mt2) { CMatrix3x3 r = mt1; r *= mt2; return r; }
		inline friend CMatrix3x3 operator / (const CMatrix3x3& mt, const float v) { CMatrix3x3 r = mt; r /= v; return r; }
	public:
		//	是否包含縮放資訊。
		bool HasScale () const;
		//	歐拉角旋轉。
		void FromEulerAnglesXYZ (const float y, const float p, const float r);
		void FromEulerAnglesXZY (const float y, const float p, const float r);
		void FromEulerAnglesYXZ (const float y, const float p, const float r);
		void FromEulerAnglesYZX (const float y, const float p, const float r);
		void FromEulerAnglesZXY (const float y, const float p, const float r);
		void FromEulerAnglesZYX (const float y, const float p, const float r);
		//	繞任意軸旋轉。
		void FromAxisAngle (const CVector3& v, const float r);
		void FromAxisAngle (const float x, const float y, const float z, const float r);
		//	Orthogonal Q, diagonal D, upper triangular U stored as (u01, u02, u12)。
		void QDUDecomposition (CMatrix3x3& q, CVector3& d, CVector3& u) const;
		//	轉置後相乘。
		CMatrix3x3 TransposeAndMultiplication (const CMatrix3x3& mat) const;
		//	伴隨矩陣。
		CMatrix3x3 AdjointMatrix () const;
		//	求逆。
		void Inverse ();
		//	是否為單位矩陣。
		bool IsIdentity (float tolerance = 0.00001f) const;
	public:
		//	指定軸向。
		inline void FromAxes (const CVector3& x, const CVector3& y, const CVector3& z)
		{
			m00 = x.x; m01 = y.x; m02 = z.x;
			m10 = x.y; m11 = y.y; m12 = z.y;
			m20 = x.z; m21 = y.z; m22 = z.z;
		}
		//	單位化。
		inline void Identity () { Set (IDENTITY); }
		//	轉置。
		inline void Transpose () { Math::Swap (m01, m10); Math::Swap (m02, m20); Math::Swap (m12, m21); }
		//	繞X軸旋轉 (+往下 -往上)。
		inline void RotateX (const float x)
		{
			float s, c;
			Math::SinCos (x, s, c);
			m00 = 1.0f; m01 = m02 = 0.0f;
			m10 = 0.0f; m11 = c; m12 = -s;
			m20 = 0.0f; m21 = s; m22 = c;
		}
		//	繞Y軸旋轉 (+往右 -往左)。
		inline void RotateY (const float y)
		{
			float s, c;
			Math::SinCos (y, s, c);
			m00 = c; m01 = 0.0f; m02 = s;
			m10 = m12 = 0.0f; m11 = 1.0f;
			m20 = -s; m21 = 0.0f; m22 = c;
		}
		//	繞Z軸旋轉 (+逆時鐘 -順時鐘)。
		inline void RotateZ (const float z)
		{
			float s, c;
			Math::SinCos (z, s, c);
			m00 = c; m01 = -s; m02 = 0.0f;
			m10 = s; m11 = c; m12 = 0.0f;
			m20 = m21 = 0.0f; m22 = 1.0f;
		}
		//	行列式。
		float Determinant () const { return m00 * (m11 * m22 - m12 * m21) + m01 * (m12 * m20 - m10 * m22) + m02 * (m10 * m21 - m11 * m20); }
		//	求逆 (3x3正交矩陣 轉置等於逆矩陣)。
		inline void FastInvert () { Transpose (); }
	public:
		//	矩陣資訊。
		union
		{
			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			};
			float m[3][3];
		};
	};

};

#endif //	LionX_LionX_Graphics_Matrix3x3_H

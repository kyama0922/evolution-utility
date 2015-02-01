#ifndef __EVOLUTION_QUATERNION_H__
#define __EVOLUTION_QUATERNION_H__

#include <evolution_type.h>
#include <assert.h>
#include "evolution_vector4.h"
namespace EVOLUTION{

    namespace MATH{
        class Vector2;
        class Vector3;
        class Vector4;
        class Matrix;

#if defined(WIN32) | defined(WIN64)
        __declspec(align(16))
#endif
        class Quaternion :public float4
        {
        public:
            EVOLUTION_INLINE Quaternion(){}
            EVOLUTION_INLINE Quaternion(const Vector3& vec){ this->x = vec.x; this->y = vec.y; this->z = vec.z; this->w = 0.0f; }
            EVOLUTION_INLINE Quaternion(const Vector3& axis, f32 r){ this->SetR(axis, r); }
            EVOLUTION_INLINE Quaternion(float x, float y, float z, float w){ this->x = x; this->y = y; this->z = z; this->w = w; }
            EVOLUTION_INLINE Quaternion(const Quaternion& q){ this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; }
            //*****************************************************************************
            //		演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Quaternion operator + () const { return Quaternion(x, y, z, w); }
            EVOLUTION_INLINE Quaternion operator - () const { return Quaternion(-x, -y, -z, -w); }
            //*****************************************************************************
            //		Quaternion演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Quaternion operator+(const Quaternion& val)const{ return Quaternion(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w); }
            EVOLUTION_INLINE Quaternion operator-(const Quaternion& val)const{ return Quaternion(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w); }
            EVOLUTION_INLINE Quaternion operator*(const Quaternion& val) const {
                //return Quaternion(
                //	y * val.z - z * val.y + x * val.w + w * val.x,
                //	z * val.x - x * val.z + y * val.w + w * val.y,
                //	x * val.y - y * val.x + z * val.w + w * val.z,
                //	w * val.w - x * val.x - y * val.y - z * val.z
                //	);
                // 12 muls, 30 adds

                float E = (this->x + this->z)*(val.x + val.y);
                float F = (this->z - this->x)*(val.x - val.y);
                float G = (this->w + this->y)*(val.w - val.z);
                float H = (this->w - this->y)*(val.w + val.z);
                float A = F - E;
                float B = F + E;
                return Quaternion(
                    (this->w + this->x)*(val.w + val.x) + (A - G - H) * 0.5f,
                    (this->w - this->x)*(val.y + val.z) + (B + G - H) * 0.5f,
                    (this->y + this->z)*(val.w - val.x) + (B - G + H) * 0.5f,
                    (this->z - this->y)*(val.y - val.z) + (A + G + H) * 0.5f
                    );
            }
            EVOLUTION_INLINE Quaternion& operator+=(const Quaternion& val){ this->x += val.x; this->y += val.y; this->z += val.z; this->w += val.z; return *this; }
            EVOLUTION_INLINE Quaternion& operator-=(const Quaternion& val){ this->x -= val.x; this->y -= val.y; this->z -= val.z; this->w -= val.z; return *this; }
            EVOLUTION_INLINE Quaternion& operator*=(const Quaternion& val){ *this = (val)*(*this); return *this; }
            //*****************************************************************************
            //		float演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Quaternion operator+(f32 val)const{ return Quaternion(this->x + val, this->y + val, this->z + val, this->w + val); }
            EVOLUTION_INLINE Quaternion operator-(f32 val)const{ return Quaternion(this->x - val, this->y - val, this->z - val, this->w - val); }
            EVOLUTION_INLINE Quaternion operator*(f32 val)const{ return Quaternion(this->x*val, this->y*val, this->z*val, this->w*val); }
            EVOLUTION_INLINE Quaternion operator/(f32 val)const{ return Quaternion(this->x / val, this->y / val, this->z / val, this->w / val); }
            EVOLUTION_INLINE Quaternion& operator+=(f32 val){ this->x += val; this->y += val; this->z += val; this->w += val; return *this; }
            EVOLUTION_INLINE Quaternion& operator-=(f32 val){ this->x -= val; this->y -= val; this->z -= val; this->w -= val; return *this; }
            EVOLUTION_INLINE Quaternion& operator*=(f32 val){ this->x *= val; this->y *= val; this->z *= val; this->w *= val; return *this; }
            EVOLUTION_INLINE Quaternion& operator/=(f32 val){ this->x /= val; this->y /= val; this->z /= val; this->w /= val; return *this; }
            //*****************************************************************************
            //		代入演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Quaternion& operator=(const Vector3& val){ this->x = val.x; this->y = val.y; this->z = val.z; this->w = 0.0f; return *this; }
            EVOLUTION_INLINE Quaternion& operator=(const Quaternion& val){ this->x = val.x; this->y = val.y; this->z = val.z; this->w = val.w; return *this; }
            EVOLUTION_INLINE Quaternion& operator=(f32 val){ this->x = val; this->y = val; this->z = val; this->w = val; return *this; }
            //*****************************************************************************
            //		関数
            //*****************************************************************************
            //クォータニオンとの内積
            EVOLUTION_INLINE f32 Dot(const Quaternion& val) const { return this->x*val.x + this->y*val.y + this->z*val.z + this->w*val.w; }
            //長さの2乗計算
            EVOLUTION_INLINE f32 LengthSq() const { return Dot(*this); }
            //長さ計算
            f32 Length() const;

            //正規化
            EVOLUTION_INLINE const Quaternion* Normalize()
            {
                f32 len = this->Length();
                if (len == 0.0f)return nullptr;
                *this /= len;
                return this;
            }
            // 単位化
            EVOLUTION_INLINE const Quaternion* Identity(){ this->x = this->y = this->z = 0.0f; this->w = 1.0f; return this; }
            //共役化
            EVOLUTION_INLINE const Quaternion* Conjugate(){ this->x = -this->x; this->y = -this->y; this->z = -this->z; return this; }
            //共役クォータニオンを作成
            EVOLUTION_INLINE Quaternion CreateConjugate()const
            {
                Quaternion ret = *this;
                ret.x = -ret.x; ret.y = -ret.y; ret.z = -ret.z; ret.w = -ret.w;
                return ret;
            }

            //逆数化して自身に代入
            EVOLUTION_INLINE const Quaternion* Inverse()
            {
                this->Conjugate();
                f32 lensq = this->LengthSq();
                //もしクォータニオンの長さの二乗が0ならエラー
                assert(lensq != 0.0f);
                *this /= lensq;
                return this;
            }

            //逆数クォータニオンを作成,作成できなければ強制終了する
            EVOLUTION_INLINE Quaternion CreateInverse()const
            {
                Quaternion ret = this->CreateConjugate();
                f32 lensq = this->LengthSq();
                //もしクォータニオンの長さの二乗が0ならエラー
                assert(lensq != 0.0f);
                ret /= lensq;
                return ret;
            }

            //クォータニオン同士の合成して新しいクォータニオンを作成する
            EVOLUTION_INLINE Quaternion Comp(const Quaternion& q){ return q*(*this); }

            //クォータニオンをクォータニオンで回転
            EVOLUTION_INLINE const Quaternion* Rotate(const Quaternion& q){ *this = q*(*this); return this; }

            //クォータニオン球面線形補間して自身に代入する
            const Quaternion* SLerp(const Quaternion& q, f32 t);
            //*****************************************************************************
            //		成分操作関連
            //*****************************************************************************

            //オイラー角からX軸回転クォータニオン作成
            const Quaternion* SetRX(f32 rad);
            //オイラー角からY軸回転クォータニオン作成
            const Quaternion* SetRY(f32 rad);
            //オイラー角からZ軸回転クォータニオン作成
            const Quaternion* SetRZ(f32 rad);
            //オイラー角からクォータニオンを作成する(XYZオーダー)
            const Quaternion* SetRXYZ(f32 sx, f32 sy, f32 sz);
            //オイラー角からクォータニオンを作成する(XYZオーダー)
            EVOLUTION_INLINE const Quaternion* SetRXYZ(const Vector3& angle){ return this->SetRXYZ(angle.x, angle.y, angle.z); }
            //オイラー角からクォータニオンを作成する(ZXYオーダー)
            const Quaternion* SetRZXY(f32 sx, f32 sy, f32 sz);
            //オイラー角からクォータニオンを作成する(ZXYオーダー)
            EVOLUTION_INLINE const Quaternion* SetRZXY(const Vector3& angle){ return this->SetRZXY(angle.x, angle.y, angle.z); }
            //任意の軸と回転角からクォータニオンを作成する
            const Quaternion* SetR(const Vector3 &axis, f32 rad);
            //*****************************************************************************
            //		成分取得関連
            //*****************************************************************************

            //クォータニオンの軸と回転角に分解する
            void Decompose(Vector3* axis, f32* rad) const;
            //クォータニオンを姿勢ベクトルに分解する
            void Decompose(Vector3* right, Vector3* up, Vector3* front) const;

            //*****************************************************************************
            //		変換関連
            //*****************************************************************************

            //行列に変換する
            const Matrix* ToMatrix(Matrix* out)const;
            //行列に変換する
            Matrix ToMatrix()const;
            //XYZオーダーオイラー角に変換する
            const Vector3* ToEulerXYZ(Vector3* out)const;
            //ZXYオーダーオイラー角に変換する(スケーリングされていると意図した結果にならない)
            const Vector3* ToEulerZXY(Vector3* out)const;
        };
    }
}

#endif // !__EVOLUTION_QUATERNION_H__

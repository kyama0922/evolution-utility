#ifndef __EVOLUTION_VECTOR4_H__
#define __EVOLUTION_VECTOR4_H__

#include <evolution_type.h>

namespace EVOLUTION{

    namespace MATH{
        class Vector2;
        class Vector3;
        class Quaternion;
        class Matrix;

        typedef struct{
            union {
                f32 m[4];
                struct {
                    f32  x, y, z, w;
                };
            };
        }float4;

        class Vector4 :public	float4
        {
        public:
            EVOLUTION_INLINE Vector4(){}
            EVOLUTION_INLINE Vector4(f32 x, f32 y, f32 z, f32 w){ this->x = x; this->y = y; this->z = z; this->w = w; }
            EVOLUTION_INLINE Vector4(const Vector2& val){ *this = val; this->z = this->w = 0.0f; }
            EVOLUTION_INLINE Vector4(const Vector3& val){ *this = val; this->w = 0.0f; }
            EVOLUTION_INLINE Vector4(const Vector4& val){ *this = val; }
            EVOLUTION_INLINE Vector4(const Quaternion& val){ *this = val; }
            //*****************************************************************************
            //		演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector4 operator + () const { return Vector4(x, y, z, w); }
            EVOLUTION_INLINE Vector4 operator - () const { return Vector4(-x, -y, -z, -w); }
            //*****************************************************************************
            //		float演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector4 operator+(f32 val)const{ return Vector4(this->x + val, this->y + val, this->z + val, this->w + val); }
            EVOLUTION_INLINE Vector4 operator-(f32 val)const{ return Vector4(this->x - val, this->y - val, this->z - val, this->w - val); }
            EVOLUTION_INLINE Vector4 operator*(f32 val)const{ return Vector4(this->x*val, this->y*val, this->z*val, this->w*val); }
            EVOLUTION_INLINE Vector4 operator/(f32 val)const{ return Vector4(this->x / val, this->y / val, this->z / val, this->w / val); }
            EVOLUTION_INLINE Vector4& operator+=(f32 val){ this->x += val; this->y += val; this->z += val; this->w += val; return *this; }
            EVOLUTION_INLINE Vector4& operator-=(f32 val){ this->x -= val; this->y -= val; this->z -= val; this->w -= val; return *this; }
            EVOLUTION_INLINE Vector4& operator*=(f32 val){ this->x *= val; this->y *= val; this->z *= val; this->w *= val; return *this; }
            EVOLUTION_INLINE Vector4& operator/=(f32 val){ this->x /= val; this->y /= val; this->z /= val; this->w /= val; return *this; }
            //*****************************************************************************
            //		VECTOR2演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector4 operator+(const Vector2& val)const{ return Vector4(this->x + val.x, this->y + val.y, this->z, this->w); }
            EVOLUTION_INLINE Vector4 operator-(const Vector2& val)const{ return Vector4(this->x - val.x, this->y - val.y, this->z, this->w); }
            EVOLUTION_INLINE Vector4& operator+=(const Vector2& val){ this->x += val.x; this->y += val.y; return *this; }
            EVOLUTION_INLINE Vector4& operator-=(const Vector2& val){ this->x -= val.x; this->y -= val.y; return *this; }
            //*****************************************************************************
            //		VECTOR3演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector4 operator+(const Vector3& val)const{ return Vector4(this->x + val.x, this->y + val.y, this->z + val.z, this->w); }
            EVOLUTION_INLINE Vector4 operator-(const Vector3& val)const{ return Vector4(this->x - val.x, this->y - val.y, this->z - val.z, this->w); }
            EVOLUTION_INLINE Vector4& operator+=(const Vector3& val){ this->x += val.x; this->y += val.y; this->z += val.z; return *this; }
            EVOLUTION_INLINE Vector4& operator-=(const Vector3& val){ this->x -= val.x; this->y -= val.y; this->z -= val.z; return *this; }
            //*****************************************************************************
            //		Vector4演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector4 operator+(const Vector4& val)const{ return Vector4(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w); }
            EVOLUTION_INLINE Vector4 operator-(const Vector4& val)const{ return Vector4(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w); }
            EVOLUTION_INLINE Vector4& operator+=(const Vector4& val){ this->x += val.x; this->y += val.y; this->z += val.z; this->w += val.w; return *this; }
            EVOLUTION_INLINE Vector4& operator-=(const Vector4& val){ this->x -= val.x; this->y -= val.y; this->z -= val.z; this->w -= val.w; return *this; }
            //*****************************************************************************
            //		Matrix演算オペレータ
            //*****************************************************************************
            //*****************************************************************************
            //		代入演算オペレータ
            //*****************************************************************************
            Vector4& operator=(const Vector2& val);
            Vector4& operator=(const Vector3& val);
            Vector4& operator=(const Vector4& val);
            Vector4& operator=(const Quaternion& val);
            //*****************************************************************************
            //		関数
            //*****************************************************************************

            //ベクトルの内積を求める
            EVOLUTION_INLINE f32 Dot(const Vector4& val)const { return this->x*val.x + this->y*val.y + this->z*val.z + this->w*val.w; }
            //ベクトルの長さの二乗を求める
            EVOLUTION_INLINE f32 LengthSq()const{ return this->Dot(*this); }
            //ベクトルの長さを求める
            f32 Length()const;
            //ベクトルを正規化する
            const Vector4* Normalize();
            //ベクトルを線形補間する
            const Vector4* Lerp(const Vector4& from, const Vector4& dest, f32 t);
            //ベクトルを行列変換する
            const Vector4* Trans(const Matrix& m);
        };
    }
}

#endif // !__VECTOR4_H__

#ifndef __EVOLUTION_VECTOR2_H__
#define __EVOLUTION_VECTOR2_H__

#include <evolution_type.h>

namespace EVOLUTION{

    namespace MATH{
        class Vector3;
        class Vector4;
        class Quaternion;
        class Matrix;

#if defined(WIN32) | defined(WIN64)
        __declspec(align(8))
#endif
        typedef struct{
            union{
                f32 m[2];
                struct{
                    f32 x;
                    f32 y;
                };
                struct{
                    f32 u;
                    f32 v;
                };
            };
        }float2;

        class Vector2 :public	float2
        {
        public:
            EVOLUTION_INLINE Vector2(){}
            EVOLUTION_INLINE Vector2(f32 x, f32 y){ this->x = x; this->y = y; }
            EVOLUTION_INLINE Vector2(const Vector2& val){ *this = val; }
            //*****************************************************************************
            //		演算オペレータ
            //*****************************************************************************

            EVOLUTION_INLINE Vector2 operator + () const { return Vector2(x, y); }
            EVOLUTION_INLINE Vector2 operator - () const { return Vector2(-x, -y); }
            //*****************************************************************************
            //		float演算オペレータ
            //*****************************************************************************

            EVOLUTION_INLINE Vector2 operator+(f32 val)const{ return Vector2(this->x + val, this->y + val); }
            EVOLUTION_INLINE Vector2 operator-(f32 val)const{ return Vector2(this->x - val, this->y - val); }
            EVOLUTION_INLINE Vector2 operator*(f32 val)const{ return Vector2(this->x*val, this->y*val); }
            EVOLUTION_INLINE Vector2 operator/(f32 val)const{ return Vector2(this->x / val, this->y / val); }
            EVOLUTION_INLINE Vector2& operator+=(f32 val){ this->x += val; this->y += val; return *this; }
            EVOLUTION_INLINE Vector2& operator-=(f32 val){ this->x -= val; this->y -= val; return *this; }
            EVOLUTION_INLINE Vector2& operator*=(f32 val){ this->x *= val; this->y *= val; return *this; }
            EVOLUTION_INLINE Vector2& operator/=(f32 val){ this->x /= val; this->y /= val; return *this; }
            //*****************************************************************************
            //		VECTOR2演算オペレータ
            //*****************************************************************************

            EVOLUTION_INLINE Vector2 operator+(const Vector2& val)const{ return Vector2(this->x + val.x, this->y + val.y); }
            EVOLUTION_INLINE Vector2 operator-(const Vector2& val)const{ return Vector2(this->x - val.x, this->y - val.y); }
            EVOLUTION_INLINE Vector2& operator+=(const Vector2& val){ this->x += val.x; this->y += val.y; return *this; }
            EVOLUTION_INLINE Vector2& operator-=(const Vector2& val){ this->x -= val.x; this->y -= val.y; return *this; }
            //*****************************************************************************
            //		代入演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector2& operator=(const Vector2& val){ this->x = val.x; this->y = val.y; return *this; }
            Vector2& operator=(const Vector3& val);
            Vector2& operator=(const Vector4& val);
            //*****************************************************************************
            //		関数
            //*****************************************************************************
            
            //ベクトルの内積を求める
            EVOLUTION_INLINE f32 Dot(const Vector2& vec)const{ return this->x*vec.x + this->y*vec.y; }
            //ベクトルの外積を求める
            EVOLUTION_INLINE f32 Cross(const Vector2& vec)const{ return this->x*vec.y - vec.x*this->y; }
           //ベクトル間の角度を求める
            f32 Degree(const Vector2& vec)const;
            //ベクトルの長さの二乗を求める
            EVOLUTION_INLINE f32 LengthSq()const{ return Dot(*this); }
            //ベクトルの長さを求める
            f32 Length()const;
            //ベクトルの距離の二乗を求める
            f32 DistanceSq(const Vector2& vec)const;
            //ベクトルの距離を求める
            f32 Distance(const Vector2& vec)const;
            //ベクトルを正規化
            const Vector2* Normalize();
            //ベクトルを線形補間し自身に格納
            const Vector2* Lerp(const Vector2& from, const Vector2& dest, f32 t);
            //射影ベクトルを求めて自身に代入
            const Vector2* Projection(const Vector2& from, const Vector2& dest);
            //*****************************************************************************
            //		成分操作関連
            //*****************************************************************************
            
            //角度からベクトルを作成する
            const Vector2* SetR(f32 rad);
            //ベクトルを任意の長さにする
            const Vector2* SetLength(f32 len);
            //*****************************************************************************
            //		変換関連
            //*****************************************************************************
            
            //ベクトルを角度に変換する
            f32 ToEuler()const;
        };
    }
}

#endif // !__EVOLUTION_VECTOR2_H__

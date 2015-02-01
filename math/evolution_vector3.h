#ifndef __EVOLUTION_VECTOR3_H__
#define __EVOLUTION_VECTOR3_H__

#include <evolution_type.h>

namespace EVOLUTION{

    namespace MATH{
        class Vector2;
        class Vector4;
        class Quaternion;
        class Matrix;

#if defined(WIN32) | defined(WIN64)
        __declspec(align(16))
#endif
        typedef struct{
            union{
                f32 m[3];
                struct{
                    f32 x;
                    f32 y;
                    f32 z;
                };
            };
        }float3;

        class Vector3 :public float3
        {
        public:
            EVOLUTION_INLINE Vector3(){}
            EVOLUTION_INLINE Vector3(f32 x, f32 y, f32 z){ this->x = x; this->y = y; this->z = z; }
            EVOLUTION_INLINE Vector3(const Vector2& val){ *this = val; this->z = 0.0f; }
            EVOLUTION_INLINE Vector3(const Vector3& val){ *this = val; }
            EVOLUTION_INLINE Vector3(const Vector4& val){ *this = val; }
            EVOLUTION_INLINE Vector3(const Quaternion& val){ *this = val; }
            //*****************************************************************************
            //		演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator + () const { return Vector3(x, y, z); }
            EVOLUTION_INLINE Vector3 operator - () const { return Vector3(-x, -y, -z); }
            //*****************************************************************************
            //		float演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator+(f32 val)const{ return Vector3(this->x + val, this->y + val, this->z + val); }
            EVOLUTION_INLINE Vector3 operator-(f32 val)const{ return Vector3(this->x - val, this->y - val, this->z - val); }
            EVOLUTION_INLINE Vector3 operator*(f32 val)const{ return Vector3(this->x*val, this->y*val, this->z*val); }
            EVOLUTION_INLINE Vector3 operator/(f32 val)const{ return Vector3(this->x / val, this->y / val, this->z / val); }
            EVOLUTION_INLINE Vector3& operator+=(f32 val){ this->x += val; this->y += val; this->z += val; return *this; }
            EVOLUTION_INLINE Vector3& operator-=(f32 val){ this->x -= val; this->y -= val; this->z -= val; return *this; }
            EVOLUTION_INLINE Vector3& operator*=(f32 val){ this->x *= val; this->y *= val; this->z *= val; return *this; }
            EVOLUTION_INLINE Vector3& operator/=(f32 val){ this->x /= val; this->y /= val; this->z /= val; return *this; }
            //*****************************************************************************
            //		VECTOR2演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator+(const Vector2& val)const{ return Vector3(this->x + val.x, this->y + val.y, this->z); }
            EVOLUTION_INLINE Vector3 operator-(const Vector2& val)const{ return Vector3(this->x - val.x, this->y - val.y, this->z); }
            EVOLUTION_INLINE Vector3& operator+=(const Vector2& val){ this->x += val.x; this->y += val.y; return *this; }
            EVOLUTION_INLINE Vector3& operator-=(const Vector2& val){ this->x -= val.x; this->y -= val.y; return *this; }
            //*****************************************************************************
            //		Vector3演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator+(const Vector3& val)const{ return Vector3(this->x + val.x, this->y + val.y, this->z + val.z); }
            EVOLUTION_INLINE Vector3 operator-(const Vector3& val)const{ return Vector3(this->x - val.x, this->y - val.y, this->z - val.z); }
            EVOLUTION_INLINE Vector3 operator/(const Vector3& val)const{ return Vector3(this->x / val.x, this->y / val.y, this->z / val.z); }
            EVOLUTION_INLINE Vector3& operator+=(const Vector3& val){ this->x += val.x; this->y += val.y; this->z += val.z; return *this; }
            EVOLUTION_INLINE Vector3& operator-=(const Vector3& val){ this->x -= val.x; this->y -= val.y; this->z -= val.z; return *this; }
            //*****************************************************************************
            //		代入演算オペレータ
            //*****************************************************************************
            Vector3& operator=(const Vector2& val);
            EVOLUTION_INLINE Vector3& operator=(const Vector3& val){ this->x = val.x; this->y = val.y; this->z = val.z; return *this; }
            Vector3& operator=(const Vector4& val);
            Vector3& operator=(const Quaternion& val);
            //*****************************************************************************
            //		関数
            //*****************************************************************************

            //ベクトル同士の内積
            EVOLUTION_INLINE f32 Dot(const Vector3& val)const { return this->x*val.x + this->y*val.y + this->z*val.z; }
            //ベクトル同士の内積
            static EVOLUTION_INLINE f32 Dot(const Vector3& val1, const Vector3& val2){ return val1.x*val2.x + val1.y*val2.y + val1.z*val2.z; }
            //ベクトル同士の外積を求める
            const Vector3* Cross(Vector3* out, const Vector3& in)const;
            //ベクトル同士の外積を求める
            static Vector3 Cross(const Vector3& a, const Vector3& b);
            //ベクトル同士の外積を求める
            static void Cross(Vector3& out, const Vector3& a, const Vector3& b);
            //ベクトル間の角度を求める
            f32 Degree(const Vector3& in)const;
            //ベクトルの長さの二乗を求める
            EVOLUTION_INLINE f32 LengthSq()const{ return Dot(*this); }
            //ベクトルの長さを求める
            f32 Length()const;
            //ベクトル同士の距離の二乗を求める
            f32 DistanceSq(const Vector3& vec)const;
            //ベクトル同士の距離を求める
            f32 Distance(const Vector3& vec)const;
            //ベクトルを正規化する
            const Vector3* Normalize();
            //ベクトル同士の線形補間し自身に代入する
            const Vector3* Lerp(const Vector3& from, const Vector3& dest, f32 t);
            //ベクトル同士の球面線形補間し自身に代入する
            const Vector3* SLerp(const Vector3& from, const Vector3& dest, f32 t);
            //ベクトルをクォータニオンで回転させて自身に代入する
            const Vector3* Rotate(const Quaternion& q);
            // ベクトルを任意の軸と角度で回転させて自身に代入する
            const Vector3* Rotate(const Vector3& axis, f32 r);
            // ベクトルを(x, y, z, 1)として行列変換して自身に代入する
            const Vector3* Trans(const Matrix& m);
            //ベクトルを(x,y,z,0)として行列変換して自身に代入する
            const Vector3* Trans3x3(const Matrix& m);
            //反射ベクトルを格納する
            const Vector3* Reflect(const Vector3& front, const Vector3& normal);
            //屈折ベクトルを格納する
            const Vector3* Refract(const Vector3& front, const Vector3& normal, f32 Eta);
            //射影ベクトルを格納する
            const Vector3* Projection(const Vector3& from, const Vector3& dest);
            //*****************************************************************************
            //		成分操作関連
            //*****************************************************************************

            //ベクトル同士の外積を求めた後自身に代入する
            const Vector3* SetCross(const Vector3& in);
            //仰角と方位角からベクトルを求める
            const Vector3* SetR(f32 pitch, f32 yaw);
            //ベクトルを任意の長さにする
            const Vector3* SetLength(f32 len);
            //*****************************************************************************
            //		変換関連
            //*****************************************************************************

            //ベクトルを仰角と方位角に変換する
            const Vector3* ToEuler(Vector3* out)const;
        };
    }
}

#endif // !__EVOLUTION_VECTOR3_H__

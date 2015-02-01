#ifndef __EVOLUTION_MATH_UTILITY_H__
#define __EVOLUTION_MATH_UTILITY_H__

#include <assert.h>
#include <math.h>

#include "evolution_vector2.h"
#include "evolution_vector3.h"
#include "evolution_vector4.h"
#include "evolution_quaternion.h"
#include "evolution_matrix.h"

namespace EVOLUTION{
    namespace MATH{
        const f32 PI_F = 3.141592654f;
        //単精度浮動小数点型の小さい値
        const f64  FEQ_EPS = 1e-6;
        //単精度浮動小数点型のさらに小さい値
        const f64  FEQ_EPS2 = 1e-12;

        //円周率*2
        const f32 PI_F2 = 6.28318548f;
        //1ラジアン毎秒
        const f32 RAD = 57.2957802f;
        //1度毎秒
        const f32 DEG = 0.0174532924f;

        //
        const f32 FLOAT_MAX = 3.402823466e+38f;
        const f32 FLOAT_MIN = 1.175494351e-38f;

        /**
        * @brief min～maxの間を線形補間
        * @param[int] _X スカラー
        */
        template<typename T, typename U>
        EVOLUTION_INLINE T lerp(T min, T max, U t)
        {
            return min + (max - min)*t;
        }


        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 absf(f32 _X){ unsigned int tmp = *((unsigned int*)&_X) & 0x7FFFFFFF; return *((float*)&tmp); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 sinf(f32 _X){ return ::sinf(_X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 cosf(f32 _X){ return ::cosf(_X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 tanf(f32 _X){ return ::tanf(_X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 asinf(f32 _X){/*DYNAMIC_ASSERT_LIMIT(_X,-1.0f,1.0f)*/; return ::asinf(_X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 acosf(f32 _X){/*DYNAMIC_ASSERT_LIMIT(_X,-1.0f,1.0f)*/; return ::acosf(_X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 atanf(f32 _X){ return ::atanf(_X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 atan2f(f32 _Y, f32 _X){ return ::atan2f(_Y, _X); }
        /**
        * @brief 絶対値取得関数
        * @param[int] _X スカラー
        */
        static EVOLUTION_INLINE f32 sqrtf(f32 _X){ return ::sqrtf(_X); }

        /**
        * @brief 32bit整数型vをb～eの間で繰り返し
        * @param[in] b スカラー
        * @param[in] e スカラー
        * @param[in] v スカラー
        * @return ラップアラウンドされた値
        */
        static EVOLUTION_INLINE s32 wrapi(s32 b, s32 e, s32 v)
        {
            s32 dist = e - b;
            v -= b;
            v -= (v / dist)*dist;
            return v + (v >> 31 & dist) + b;
        }
        /**
        * @brief 32bit浮動小数点型vをb～eの間で繰り返し
        * @param[in] b スカラー
        * @param[in] e スカラー
        * @param[in] v スカラー
        * @return ラップアラウンドされた値
        */
        static EVOLUTION_INLINE f32 wrapf(f32 b, f32 e, f32 v)
        {
            f32 dist = e - b;
            v -= b;
            v -= s32(v / dist) * dist;
            s32 ofs = (*(s32*)&v >> 31) & *(s32*)&dist;
            return v + *(f32*)&ofs + b;
        }
        /**
        * @brief 64bit整数型vをb～eの間で繰り返し
        * @param[in] b スカラー
        * @param[in] e スカラー
        * @param[in] v スカラー
        * @return ラップアラウンドされた値
        */
        static EVOLUTION_INLINE s64 wrapl(s64 b, s64 e, s64 v)
        {
            s64 dist = e - b;
            v -= b;
            v -= (v / dist)*dist;
            return v + (v >> 63 & dist) + b;
        }
        /**
        * @brief 64bit浮動小数点型vをb～eの間で繰り返し
        * @param[in] b スカラー
        * @param[in] e スカラー
        * @param[in] v スカラー
        * @return ラップアラウンドされた値
        */
        static EVOLUTION_INLINE f64 wrap(f64 b, f64 e, f64 v)
        {
            f64 dist = e - b;
            v -= b;
            v -= s64(v / dist) * dist;
            s64 ofs = (*(s64*)&v >> 63) & *(s64*)&dist;
            return v + *(f64*)&ofs + b;
        }
        /**
        * @brief VをMin～Maxの間でクランプ
        * @param[in] Min 最少値
        * @param[in] Max 最大値
        * @param[in] V 値
        * @return クランプされた値
        */
        static EVOLUTION_INLINE f32 clampf(f32 Min, f32 Max, f32 V)
        {
            f32 d1 = Min - V;
            f32 d2 = V - Max;
            s32 r = (*(s32*)&V ^ *(s32*)&Min) & (*(s32*)&d1 >> 31);
            r ^= *(s32*)&Min;
            r = ((r ^ *(s32*)&Max) & (*(s32*)&d2 >> 31)) ^ *(s32*)&Max;
            return *(f32*)&r;
        }
        /**
        * @brief VをMin～Maxの間でクランプ
        * @param[in] Min 最少値
        * @param[in] Max 最大値
        * @param[in] V 値
        * @return クランプされた値
        */
        static EVOLUTION_INLINE void clampf(f32 Min, f32 Max, f32* V)
        {
            f32 d1 = Min - *V;
            f32 d2 = *V - Max;
            s32 r = (*(s32*)V ^ *(s32*)&Min) & (*(s32*)&d1 >> 31);
            r ^= *(s32*)&Min;
            r = ((r ^ *(s32*)&Max) & (*(s32*)&d2 >> 31)) ^ *(s32*)&Max;
            *V = *(f32*)&r;
        }

        /**
        * @brief 0～1の間にクランプ
        * @param[in] _X スカラー
        * @return クランプされた値
        */
        static EVOLUTION_INLINE f32 saturatef(const f32& _X)
        {
            long l = *(long*)&_X;
            l &= ((long)(l ^ 0x80000000) >> 31);
            l -= 0x3F800000;
            l &= l >> 31;
            l += 0x3F800000;
            return *(f32*)&l;
        }
        /**
        * @brief 0～1の間にクランプ
        * @param[input] _X スカラー
        */
        static EVOLUTION_INLINE void saturatef(f32* _X)
        {
            long l = *(long*)&_X;
            l &= ((long)(l ^ 0x80000000) >> 31);
            l -= 0x3F800000;
            l &= l >> 31;
            l += 0x3F800000;
            *_X = *(f32*)&l;
        }
        /**
        * @brief 角度をラジアンに変換します
        * @param[int] deg 角度
        * @return ラジアン
        */
        static EVOLUTION_INLINE f32 ToRadian(f32 deg){ return (deg)* (PI_F / 180.0f); }
        /**
        * @brief ラジアンを角度に変換します
        * @param[int] rad ラジアン角
        * @return 角度
        */
        static EVOLUTION_INLINE f32 ToDegree(f32 rad){ return (rad)* (180.0f / PI_F); }
        //*****************************************************************************
        //
        //		Vector2関連
        //
        //*****************************************************************************
        //*****************************************************************************
        //		変換関連
        //*****************************************************************************
        static EVOLUTION_INLINE f32 Vector2toEuler(const Vector2& vec)
        {
            return acosf(vec.x);
        }
        //*****************************************************************************
        //		関数関連
        //*****************************************************************************
        static EVOLUTION_INLINE f32 Vector2Dot(const Vector2& from, const Vector2& dest){ return from.x*dest.x + from.y, dest.y; }
        static EVOLUTION_INLINE f32 Vector2Cross(const Vector2& from, const Vector2& dest){ return from.x*dest.y - dest.x*from.y; }
        static EVOLUTION_INLINE f32 Vector2LengthSq(const Vector2& vec){ return Vector2Dot(vec, vec); }
        static EVOLUTION_INLINE f32 Vector2Length(const Vector2& vec){ return sqrtf(Vector2LengthSq(vec)); }
        /**
        * @brief ベクトルを任意の長さで複製する
        * @param[out] out 結果ベクトル
        * @param[in] in ベクトル
        * @param[in] len 任意の長さ
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector2* Vector2SetLength(Vector2* out, const Vector2& in, f32 len)
        {
            *out = (in / Vector2Length(in))*len;
            return out;
        }
        static EVOLUTION_INLINE f32 Vector2DistanceSq(const Vector2& from, const Vector2& dest){ return Vector2LengthSq(dest - from); }
        static EVOLUTION_INLINE f32 Vector2Distance(const Vector2& from, const Vector2& dest){ return Vector2Length(dest - from); }
        static EVOLUTION_INLINE const Vector2* Vector2Normalize(Vector2* out, const Vector2& vec)
        {
            f32 len = Vector2Length(vec);
            //ベクトルの距離が０ならエラー
            assert(len != 0.0f);
            *out = vec / len;
            return out;
        }
        /**
        * @brief ベクトル同士が作る角度を求める
        * @param[in] from 角度を求めるこちらのベクトル.
        * @param[in] dest 角度を求める相手ベクトル.
        * @return 角度.
        */
        static EVOLUTION_INLINE f32 Vector2Degree(const Vector2& from, const Vector2& dest)
        {
            float cos_Theta = Vector2Dot(from, dest) / Vector2Length(from) * Vector2Length(dest);
            clampf(-1.0f, 1.0f, &cos_Theta);
            float angle = acosf(cos_Theta);
            return angle;
        }
        /**
        * @brief ベクトル同士を線形補間する
        * @param[out] out 補間されたベクトル
        * @param[in] from 補間するこちらのベクトル
        * @param[in] dest 補完する相手のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector2* Vector2Lerp(Vector2* out, const Vector2& from, const Vector2& dest, f32 t)
        {
            out->x = lerp(from.x, dest.x, t);
            out->y = lerp(from.y, dest.y, t);
            return out;
        }
        static EVOLUTION_INLINE f32 Vector2ProjectionLength(const Vector2& from, const Vector2& dest){ return Vector2Dot(from, dest) / Vector2Length(dest); }
        static EVOLUTION_INLINE const Vector2* Vector2Projection(Vector2* out, const Vector2& from, const Vector2& dest)
        {
            *out = dest*(Vector2Dot(from, dest) / Vector2LengthSq(dest));
            return out;
        }
        //*****************************************************************************
        //		ベクトル作成関連
        //*****************************************************************************
        static EVOLUTION_INLINE const Vector2* Vector2fromEuler(Vector2* out, f32 r)
        {
            out->x = cosf(r);
            out->y = sinf(r);
            return out;
        }
        //*****************************************************************************
        //
        //		Vector3関連
        //
        //*****************************************************************************
        //*****************************************************************************
        //		変換関連
        //*****************************************************************************
        /**
        * @brief ベクトルから仰角(pitch角)と方位角(yaw角)を求める(スケーリングされていると意図した結果にならない)
        * @param[out] out 求めた角度
        * @param[in] in 変換するベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3toEuler(Vector3* out, const Vector3& in)
        {
            float len;
            // ベクトルの長さを求める
            len = sqrtf(in.x*in.x + in.y*in.y + in.z*in.z);
            // 長さが０の場合はエラー
            assert(len != 0.0f);
            // ベクトルを正規化する
            float X = in.x / len;
            float Y = in.y / len;
            float Z = in.z / len;
            // ピッチの計算を行う
            out->x = asinf(-Y);
            // ヨーの計算を行う
            out->y = atan2f(X, Z);
            return out;
        }
        //*****************************************************************************
        //		関数関連
        //*****************************************************************************
        /**
        * @brief ベクトルの外積を求める
        * @param[out] out ベクトルの外積
        * @param[in] from 外積を求めるこちらのベクトル
        * @param[in] dest 外積を求める相手のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Cross(Vector3* out, const Vector3& from, const Vector3& dest)
        {
            Vector3 work = from;
            out->x = work.y*dest.z - work.z*dest.y;
            out->y = work.z*dest.x - work.x*dest.z;
            out->z = work.x*dest.y - work.y*dest.x;
            return out;
        }
        /**
        * @brief ベクトルの内積を求める
        * @param[in] from 内積を求めるこちらのベクトル
        * @param[in] dest 内積を求める相手のベクトル
        * @return ベクトルの内積
        */
        static EVOLUTION_INLINE f32 Vector3Dot(const Vector3& from, const Vector3& dest)
        {
            return from.x*dest.x + from.y*dest.y + from.z*dest.z;
        }
        /**
        * @brief ベクトルの長さの二乗を求める
        * @param[in] val 長さを求めるベクトル
        * @return ベクトルの長さの二乗
        */
        static EVOLUTION_INLINE f32 Vector3LengthSq(const Vector3& val)
        {
            return Vector3Dot(val, val);
        }
        /**
        * @brief ベクトルの長さを求める
        * @param[in] val 長さを求めるベクトル
        * @return ベクトルの長さ
        */
        static EVOLUTION_INLINE f32 Vector3Length(const Vector3& val)
        {
            return sqrtf(Vector3LengthSq(val));
        }
        /**
        * @brief ベクトルを任意の長さで複製する
        * @param[out] out 結果ベクトル
        * @param[in] in ベクトル
        * @param[in] len 任意の長さ
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3SetLength(Vector3* out, const Vector3& in, f32 len)
        {
            *out = (in / Vector3Length(in))*len;
            return out;
        }
        /**
        * @brief ベクトルの距離の二乗を求める
        * @param[in] from 距離を求めるベクトル
        * @param[in] dest 距離を求めるベクトル
        * @return ベクトルの距離の二乗
        */
        static EVOLUTION_INLINE f32 Vector3DistanceSq(const Vector3& from, const Vector3& dest)
        {
            return Vector3LengthSq(dest - from);
        }
        /**
        * @brief ベクトルの距離を求める
        * @param[in] from 距離を求めるベクトル
        * @param[in] dest 距離を求めるベクトル
        * @return ベクトルの距離
        */
        static EVOLUTION_INLINE f32 Vector3Distance(const Vector3& from, const Vector3& dest)
        {
            return Vector3Length(dest - from);
        }
        /**
        * @brief ベクトルの長さを求める
        * @param[in] val 長さを求めるベクトル
        * @return ベクトルの長さ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Normalize(Vector3* out, const Vector3& val)
        {
            f32 len = Vector3Length(val);
            //ベクトルの長さが0ならエラー
            //assert(len!=0.0f);
            *out = val / len;
            return out;
        }
        /**
        * @brief ベクトル同士が作る角度を求める
        * @param[in] from 角度を求めるこちらのベクトル.
        * @param[in] dest 角度を求める相手ベクトル.
        * @return 角度.
        */
        static EVOLUTION_INLINE f32 Vector3Degree(const Vector3& from, const Vector3& dest)
        {
            float cos_Theta = Vector3Dot(from, dest) / Vector3Length(from) * Vector3Length(dest);
            clampf(-1.0f, 1.0f, &cos_Theta);
            float angle = acosf(cos_Theta);
            return angle;
        }
        /**
        * @brief ベクトル同士を線形補間する
        * @param[out] out 補間されたベクトル
        * @param[in] from 補間するこちらのベクトル
        * @param[in] dest 補完する相手のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Lerp(Vector3* out, const Vector3& from, const Vector3& dest, f32 t)
        {
            out->x = lerp(from.x, dest.x, t);
            out->y = lerp(from.y, dest.y, t);
            out->z = lerp(from.z, dest.z, t);
            return out;
        }
        /**
        * @brief ベクトル同士を球面線形補間する
        * @param[out] out 補間されたベクトル
        * @param[in] from 補間するこちらのベクトル
        * @param[in] dest 補完する相手のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Slerp(Vector3* out, const Vector3& from, const Vector3& dest, f32 t)
        {
            // 2ベクトル間の角度（鋭角側）
            f32 angle = acosf(Vector3Dot(from, dest));
            // sinθ
            f32 SinTh = sinf(angle);
            // 補間係数
            f32 Ps = sinf(angle * (1.0f - t));
            f32 Pe = sinf(angle * t);
            *out = (from  * Ps + dest * Pe) / SinTh;
            // 一応正規化して球面線形補間に
            return Vector3Normalize(out, *out);
        }

        /**
        * 反射ベクトルを求める ．
        * @param[out] out 反射ベクトル
        * @param[in] front 進行ベクトル
        * @param [in]  normal 法線ベクトル ．
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Reflect(Vector3* out, const Vector3& front, const Vector3& normal)
        {
            Vector3 v(-front);
            Vector3 t(normal * (Vector3Dot(v, normal) * 2.0f));
            *out = t + front;
            return out;
        }

        /**
        * 屈折ベクトルを求める．
        * @param[out] out 屈折ベクトル
        * @param[in] front 進行ベクトル
        * @param [in]  normal 法線ベクトル ．
        * @param[in] Eta 屈折率
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Refract(Vector3* out, const Vector3& front, const Vector3& normal, f32 Eta)
        {
            Vector3 T1(-front);
            float cosI = Vector3Dot(T1, normal);
            float cosT2 = 1.0f - Eta * Eta * (1.0f - cosI * cosI);
            if (cosT2 <= 0.0f){
                out->x = 0.0f;
                out->y = 0.0f;
            }
            else {
                T1 = front * Eta;
                Vector3 T2(normal * (Eta * cosI - sqrtf(absf(cosT2))));
                *out = T1 + T2;
            }
            return out;
        }
        /**
        * @brief 射影ベクトルの長さを求める
        * @param[in] from 射影するベクトル
        * @param[in] dest 射影されるベクトル
        * @return 射影ベクトルの長さ
        */
        static EVOLUTION_INLINE f32 Vector3ProjectionLength(const Vector3& from, const Vector3& dest){ return Vector3Dot(from, dest) / Vector3Length(dest); }
        /**
        * @brief 射影ベクトルを求める
        * @param[out] out 射影ベクトル
        * @param[in] from 射影するベクトル
        * @param[in] dest 射影されるベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* Vector3Projection(Vector3* out, const Vector3& from, const Vector3& dest)
        {
            *out = dest*(Vector3Dot(from, dest) / Vector3LengthSq(dest));
            return out;
        }
        //*****************************************************************************
        //		ベクトル作成関連
        //*****************************************************************************
        /**
        * @brief 仰角(pitch角)と方位角(yaw角)からベクトルを求める
        * @param[out] out 求めたベクトル
        * @param[in] pitch ピッチ角(X軸)
        * @param[in] yaw ヨー角(Y軸)
        * @return 求めたベクトル.
        */
        static EVOLUTION_INLINE const Vector3* Vector3fromPitchYaw(Vector3* out, f32 pitch, f32 yaw)
        {
            out->x = cosf(pitch) * sinf(yaw);
            out->y = -sinf(pitch);
            out->z = cosf(pitch) * cosf(yaw);
            return out;
        }
        //*****************************************************************************
        //
        //		Vector4関連
        //
        //*****************************************************************************
        //*****************************************************************************
        //		関数関連
        //*****************************************************************************
        /**
        * @brief ベクトルの内積を求める
        * @param[in] from 内積を求めるこちらのベクトル
        * @param[in] dest 内積を求める相手のベクトル
        * @return ベクトルの内積
        */
        static EVOLUTION_INLINE f32 Vector4Dot(const Vector4& from, const Vector4& dest){ return from.x*dest.x + from.y*dest.y + from.z*dest.z + from.w*dest.w; }
        /**
        * @brief ベクトルの長さの二乗を求める
        * @param[in] vec 長さの二乗を求めるベクトル
        * @return ベクトルの長さの二乗
        */
        static EVOLUTION_INLINE f32 Vector4LengthSq(const Vector4& vec){ return Vector4Dot(vec, vec); }
        /**
        * @brief ベクトルの長さを求める
        * @param[in] vec 長さを求めるベクトル
        * @return ベクトルの長さ
        */
        static EVOLUTION_INLINE f32 Vector4Length(const Vector4& vec){ return sqrtf(Vector4LengthSq(vec)); }
        /**
        * @brief ベクトルを正規化する
        * @param[out] out 正規化したベクトル
        * @param[in] vec 正規化するベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector4* Vector4Normalize(Vector4* out, const Vector4& vec)
        {
            f32 len = Vector4Length(vec);
            //ベクトルの長さが0ならエラー
            assert(len != 0.0f);
            *out = vec / len;
            return out;
        }
        /**
        * @brief ベクトル同士を線形補間する
        * @param[out] out 補間されたベクトル
        * @param[in] from 補間するこちらのベクトル
        * @param[in] dest 補完する相手のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector4* Vector4Lerp(Vector4* out, const Vector4& from, const Vector4& dest, f32 t)
        {
            out->x = lerp(from.x, dest.x, t);
            out->y = lerp(from.y, dest.y, t);
            out->z = lerp(from.z, dest.z, t);
            out->w = lerp(from.w, dest.w, t);
            return out;
        }
        //*****************************************************************************
        //
        //		行列関連
        //
        //*****************************************************************************
        //*****************************************************************************
        //		変換関連
        //*****************************************************************************
        /**
        * @brief 行列をクォータニオンに変換する(スケーリングされていると意図した結果にならない)
        * @param[out] q 回転クォータニオン
        * @param[in] mat 回転行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* MatrixToQuaternion(Quaternion* q, const Matrix& mat)
        {
            // 最大成分を検索
            f32 elem[4]; // 0:x, 1:y, 2:z, 3:w
            elem[0] = mat._11 - mat._22 - mat._33 + 1.0f;
            elem[1] = -mat._11 + mat._22 - mat._33 + 1.0f;
            elem[2] = -mat._11 - mat._22 + mat._33 + 1.0f;
            elem[3] = mat._11 + mat._22 + mat._33 + 1.0f;

            unsigned biggestIndex = 0;
            for (int i = 1; i < 4; i++) {
                if (elem[i] > elem[biggestIndex])
                    biggestIndex = i;
            }

            // 最大要素の値を算出
            f32 v = sqrtf(elem[biggestIndex]) * 0.5f;
            (*q).m[biggestIndex] = v;
            f32 mult = 0.25f / v;

            switch (biggestIndex) {
            case 0: // x
                (*q).m[1] = (mat._12 + mat._21) * mult;
                (*q).m[2] = (mat._31 + mat._13) * mult;
                (*q).m[3] = (mat._23 - mat._32) * mult;
                break;
            case 1: // y
                (*q).m[0] = (mat._12 + mat._21) * mult;
                (*q).m[2] = (mat._23 + mat._32) * mult;
                (*q).m[3] = (mat._31 - mat._13) * mult;
                break;
            case 2: // z
                (*q).m[0] = (mat._31 + mat._13) * mult;
                (*q).m[1] = (mat._23 + mat._32) * mult;
                (*q).m[3] = (mat._12 - mat._21) * mult;
                break;
            case 3: // w
                (*q).m[0] = (mat._23 - mat._32) * mult;
                (*q).m[1] = (mat._31 - mat._13) * mult;
                (*q).m[2] = (mat._12 - mat._21) * mult;
                break;
            }
            return q;
        }
        /**
        * @brief 行列からオイラー角に変換(XYZオーダー行列専用)(スケーリングされていると意図した結果にならない)
        * @param[out] out オイラー角
        * @param[in] mat 回転行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* MatrixToEulerXYZ(Vector3* out, const Matrix& mat)
        {
            out->y = asinf(-mat._13);
            f32 C = cosf(out->y);

            //cos(β)が0でなければ
            if (absf(C) > FEQ_EPS) {
                out->x = (mat._33 < 0) ? PI_F - asinf(mat._23 / C) : asinf(mat._23 / C);
                out->z = atan2f(mat._12, mat._11);
            }
            //cos(β)が0ならば
            else
            {
                out->x = 0.0f;
                out->z = atan2f(-mat._21, mat._22);
            }

            return out;
        }
        /**
        * @brief 行列からオイラー角に変換(ZXYオーダー行列専用)(スケーリングされていると意図した結果にならない)
        * @param[out] out オイラー角
        * @param[in] mat 回転行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* MatrixToEulerZXY(Vector3* out, const Matrix& mat)
        {
            out->x = asinf(-mat._32);
            f32 C = cosf(out->x);

            //cos(β)が0でなければ
            if (absf(C) > FEQ_EPS) {
                out->z = (mat._22 < 0) ? PI_F - asinf(mat._12 / C) : asinf(mat._12 / C);
                out->y = atan2f(mat._31, mat._33);
            }
            //cos(β)が0ならば
            else
            {
                out->z = 0.0f;
                out->y = atan2f(-mat._13, mat._11);
            }

            return out;
        }
        //*****************************************************************************
        //		関数関連
        //*****************************************************************************
        /**
        * @brief 4x4行列の行列式の計算
        * @param[in] mat 元の行列
        * @return 行列式の値
        */
        static EVOLUTION_INLINE f32 MatrixDet(const Matrix& mat)
        {
            return mat._11*mat._22*mat._33*mat._44 + mat._11*mat._23*mat._34*mat._42 + mat._11*mat._24*mat._32*mat._43
                + mat._12*mat._21*mat._34*mat._43 + mat._12*mat._23*mat._31*mat._44 + mat._12*mat._24*mat._33*mat._41
                + mat._13*mat._21*mat._32*mat._44 + mat._13*mat._22*mat._34*mat._41 + mat._13*mat._24*mat._31*mat._42
                + mat._14*mat._21*mat._33*mat._42 + mat._14*mat._22*mat._31*mat._43 + mat._14*mat._23*mat._32*mat._41
                - mat._11*mat._22*mat._34*mat._43 - mat._11*mat._23*mat._32*mat._44 - mat._11*mat._24*mat._33*mat._42
                - mat._12*mat._21*mat._33*mat._44 - mat._12*mat._23*mat._34*mat._41 - mat._12*mat._24*mat._31*mat._43
                - mat._13*mat._21*mat._34*mat._42 - mat._13*mat._22*mat._31*mat._44 - mat._13*mat._24*mat._32*mat._41
                - mat._14*mat._21*mat._32*mat._43 - mat._14*mat._22*mat._33*mat._41 - mat._14*mat._23*mat._31*mat._42;
        }
        /**
        * @brief ベクトルを(x,y,z,1)として行列変換
        * inとoutが同一でも安全
        * @param[out] out 変換後のベクトル
        * @param[in] i 変換前のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector4* MatrixVec3Transform(Vector4* out, const Vector3& in, const Matrix& mat)
        {
            Vector4 work;
            //変換
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31 + mat._41;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32 + mat._42;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33 + mat._43;
            work.w = in.x*mat._14 + in.y*mat._24 + in.z*mat._34 + mat._44;
            *out = work;
            return out;
        }
        /**
        * @brief ベクトルを(x,y,z,1)として行列変換、変換後wに射影する
        * inとoutが同一でも安全
        * @param[out] out 変換後のベクトル
        * @param[in] i 変換前のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* MatrixVec3TransformCoord(Vector3* out, const Vector3& in, const Matrix& mat)
        {
            Vector3 work;
            //変換
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31 + mat._41;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32 + mat._42;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33 + mat._43;
            float w = in.x*mat._14 + in.y*mat._24 + in.z*mat._34 + mat._44;
            //射影
            *out = work / w;
            return out;
        }
        /**
        * @brief ベクトルを(x,y,z,0)として行列変換
        * inとoutが同一でも安全
        * @param[out] out 変換後のベクトル
        * @param[in] i 変換前のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* MatrixVec3TransformNormal(Vector3* out, const Vector3& in, const Matrix& mat)
        {
            Vector3 work;
            //変換
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33;
            //射影
            *out = work;
            return out;
        }
        /**
        * @brief ベクトルを行列変換
        * inとoutが同一でも安全
        * @param[out] out 変換後のベクトル
        * @param[in] i 変換前のベクトル
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector4* MatrixVec4Transform(Vector4* out, const Vector4& in, const Matrix& mat)
        {
            Vector4 work;
            //変換
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31 + in.w*mat._41;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32 + in.w*mat._42;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33 + in.w*mat._43;
            work.w = in.x*mat._14 + in.y*mat._24 + in.z*mat._34 + in.w*mat._44;
            *out = work;
            return out;
        }

        //*****************************************************************************
        //		成分取得関連
        //*****************************************************************************
        /**
        * @brief 行列の拡大成分を取得する
        * @param[out] out 拡大成分
        * @param[in] in 行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* MatrixGetScale(Vector3* out, const Matrix& in)
        {
            //X軸正規化(スケール分解)
            out->x = sqrtf(in._11*in._11 + in._12*in._12 + in._13*in._13);
            //Y軸正規化(スケール分解)
            out->y = sqrtf(in._21*in._21 + in._22*in._22 + in._23*in._23);
            //Z軸正規化(スケール分解)
            out->z = sqrtf(in._31*in._31 + in._32*in._32 + in._33*in._33);
            return out;
        }
        /**
        * @brief 行列の各軸ベクトルを取得
        * @param[out] right X軸ベクトル
        * @param[out] up Y軸ベクトル
        * @param[out] front Z軸ベクトル
        * @param[in] in 行列
        */
        static EVOLUTION_INLINE void MatrixGetAxis(Vector3* right, Vector3* up, Vector3* front, const Matrix& in)
        {
            right->x = in._11;	right->y = in._12;	right->z = in._13;
            up->x = in._21;		up->y = in._22;		up->z = in._23;
            front->x = in._31;	front->y = in._32;	front->z = in._33;
        }
        /**
        * @brief 行列の平行移動成分を取得する
        * @param[out] out 拡大成分
        * @param[in] in 行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* MatrixGetTranslation(Vector3* out, const Matrix& in)
        {
            out->x = in._41;	out->y = in._42;	out->z = in._43;
            return out;
        }
        /**
        * @brief 行列を分解、分解できなければエラー
        * @param[out] s 拡大成分
        * @param[out] q 回転クォータニオン
        * @param[out] p 平行移動成分
        * @param[in] in 行列
        */
        static EVOLUTION_INLINE void MatrixDecompose(Vector3* s, Quaternion* q, Vector3* p, const Matrix& in)
        {
            Matrix work = in;
            MatrixGetScale(s, work);
            //スケールが一つでも0なら分解できないとしてエラー
            assert(s->x != 0.0f || s->y != 0.0f || s->z != 0.0f);
            work._11 /= s->x;	work._12 /= s->x;	work._13 /= s->x;
            work._21 /= s->y;	work._22 /= s->y;	work._23 /= s->y;
            work._31 /= s->z;	work._32 /= s->z;	work._33 /= s->z;
            MatrixToQuaternion(q, work);
            MatrixGetTranslation(p, in);
        }
        /**
        * @brief 行列をベクトルに分解
        * @param[out] x X軸ベクトル
        * @param[out] y Y軸ベクトル
        * @param[out] z Z軸ベクトル
        * @param[out] p 平行移動成分
        * @param[in] in 行列
        */
        static EVOLUTION_INLINE void MatrixDecompose(Vector3* x, Vector3* y, Vector3* z, Vector3* p, const Matrix& in)
        {
            MatrixGetAxis(x, y, z, in);
            MatrixGetTranslation(p, in);
        }
        /**
        * @brief 行列の回転成分を正規化した行列を作成する(スケーリングされていても正しい値が帰ることが保障されている)
        * @param[out] out 正規化された回転行列
        * @param[in] in 行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixDecomposeR(Matrix* out, const Matrix& in)
        {
            Vector3 s;
            MatrixGetScale(&s, in);
            out->_11 = in._11 / s.x;	out->_12 = in._12 / s.x;	out->_13 = in._13 / s.x;	out->_14 = 0.0f;
            out->_21 = in._21 / s.y;	out->_22 = in._22 / s.y;	out->_23 = in._23 / s.y;	out->_24 = 0.0f;
            out->_31 = in._31 / s.z;	out->_32 = in._32 / s.z;	out->_33 = in._33 / s.z;	out->_34 = 0.0f;
            out->_41 = 0.0f;				out->_42 = 0.0f;				out->_43 = 0.0f;				out->_44 = 1.0f;
            return out;
        }
        /**
        * @brief 行列を回転クォータニオンに分解する(スケーリングされていても正しい値が帰ることが保障されている)
        * @param[out] out 回転クォータニオン
        * @param[in] in 行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* MatrixDecomposeR(Quaternion* out, const Matrix& in)
        {
            Matrix work;
            //回転成分を行列に分解
            MatrixDecomposeR(&work, in);
            //クォータニオンに変換
            return MatrixToQuaternion(out, work);
        }
        //*****************************************************************************
        //		行列作成関連
        //*****************************************************************************
        /**
        * @brief 4x4行列の単位行列化
        * @param[inout] mat 行列
        */
        static EVOLUTION_INLINE void MatrixIdentity(Matrix* mat)
        {
            mat->m[0][0] = 1.0f;		mat->m[0][1] = 0.0f;		mat->m[0][2] = 0.0f;		mat->m[0][3] = 0.0f;
            mat->m[1][0] = 0.0f;		mat->m[1][1] = 1.0f;		mat->m[1][2] = 0.0f;		mat->m[1][3] = 0.0f;
            mat->m[2][0] = 0.0f;		mat->m[2][1] = 0.0f;		mat->m[2][2] = 1.0f;		mat->m[2][3] = 0.0f;
            mat->m[3][0] = 0.0f;		mat->m[3][1] = 0.0f;		mat->m[3][2] = 0.0f;		mat->m[3][3] = 1.0f;
        }
        /**
        * @brief 4x4行列の逆行列を求める、逆行列が存在しなければエラー
        * @param[out] out 逆行列
        * @param[out] m 元の行列
        * @return 逆行列の存在
        */
        static EVOLUTION_INLINE void MatrixInverse(Matrix* out, const Matrix& m)
        {
            Matrix mat = m;
            f32 det = MatrixDet(mat);

            //行列式が0なら逆行列が存在しないとしてエラー
            //assert(Math::absf(det) > FEQ_EPS);

            f32 inv_det = 1.0f / det;

            out->_11 = inv_det*(mat._22*mat._33*mat._44 + mat._23*mat._34*mat._42 + mat._24*mat._32*mat._43 - mat._22*mat._34*mat._43 - mat._23*mat._32*mat._44 - mat._24*mat._33*mat._42);
            out->_12 = inv_det*(mat._12*mat._34*mat._43 + mat._13*mat._32*mat._44 + mat._14*mat._33*mat._42 - mat._12*mat._33*mat._44 - mat._13*mat._34*mat._42 - mat._14*mat._32*mat._43);
            out->_13 = inv_det*(mat._12*mat._23*mat._44 + mat._13*mat._24*mat._42 + mat._14*mat._22*mat._43 - mat._12*mat._24*mat._43 - mat._13*mat._22*mat._44 - mat._14*mat._23*mat._42);
            out->_14 = inv_det*(mat._12*mat._24*mat._33 + mat._13*mat._22*mat._34 + mat._14*mat._23*mat._32 - mat._12*mat._23*mat._34 - mat._13*mat._24*mat._32 - mat._14*mat._22*mat._33);

            out->_21 = inv_det*(mat._21*mat._34*mat._43 + mat._23*mat._31*mat._44 + mat._24*mat._33*mat._41 - mat._21*mat._33*mat._44 - mat._23*mat._34*mat._41 - mat._24*mat._31*mat._43);
            out->_22 = inv_det*(mat._11*mat._33*mat._44 + mat._13*mat._34*mat._41 + mat._14*mat._31*mat._43 - mat._11*mat._34*mat._43 - mat._13*mat._31*mat._44 - mat._14*mat._33*mat._41);
            out->_23 = inv_det*(mat._11*mat._24*mat._43 + mat._13*mat._21*mat._44 + mat._14*mat._23*mat._41 - mat._11*mat._23*mat._44 - mat._13*mat._24*mat._41 - mat._14*mat._21*mat._43);
            out->_24 = inv_det*(mat._11*mat._23*mat._34 + mat._13*mat._24*mat._31 + mat._14*mat._21*mat._33 - mat._11*mat._24*mat._33 - mat._13*mat._21*mat._34 - mat._14*mat._23*mat._31);

            out->_31 = inv_det*(mat._21*mat._32*mat._44 + mat._22*mat._34*mat._41 + mat._24*mat._31*mat._42 - mat._21*mat._34*mat._42 - mat._22*mat._31*mat._44 - mat._24*mat._32*mat._41);
            out->_32 = inv_det*(mat._11*mat._34*mat._42 + mat._12*mat._31*mat._44 + mat._14*mat._32*mat._41 - mat._11*mat._32*mat._44 - mat._12*mat._34*mat._41 - mat._14*mat._31*mat._42);
            out->_33 = inv_det*(mat._11*mat._22*mat._44 + mat._12*mat._24*mat._41 + mat._14*mat._21*mat._42 - mat._11*mat._24*mat._42 - mat._12*mat._21*mat._44 - mat._14*mat._22*mat._41);
            out->_34 = inv_det*(mat._11*mat._24*mat._32 + mat._12*mat._21*mat._34 + mat._14*mat._22*mat._31 - mat._11*mat._22*mat._34 - mat._12*mat._24*mat._31 - mat._14*mat._21*mat._32);

            out->_41 = inv_det*(mat._21*mat._33*mat._42 + mat._22*mat._31*mat._43 + mat._23*mat._32*mat._41 - mat._21*mat._32*mat._43 - mat._22*mat._33*mat._41 - mat._23*mat._31*mat._42);
            out->_42 = inv_det*(mat._11*mat._32*mat._43 + mat._12*mat._33*mat._41 + mat._13*mat._31*mat._42 - mat._11*mat._33*mat._42 - mat._12*mat._31*mat._43 - mat._13*mat._32*mat._41);
            out->_43 = inv_det*(mat._11*mat._23*mat._42 + mat._12*mat._21*mat._43 + mat._13*mat._22*mat._41 - mat._11*mat._22*mat._43 - mat._12*mat._23*mat._41 - mat._13*mat._21*mat._42);
            out->_44 = inv_det*(mat._11*mat._22*mat._33 + mat._12*mat._23*mat._31 + mat._13*mat._21*mat._32 - mat._11*mat._23*mat._32 - mat._12*mat._21*mat._33 - mat._13*mat._22*mat._31);

        }
        /**
        * @brief 行列の回転成分を正規化する、正規化できなければエラー
        * @param[inout] m 行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixNormalize(Matrix* m)
        {
            Vector3 s;
            MatrixGetScale(&s, *m);
            //スケールが一つでも0なら正規化できないとしてエラー
            //assert(s.x!=0.0f || s.y!=0.0f || s.z!=0.0f);
            m->_11 = m->_11 / s.x;	m->_12 = m->_12 / s.x;	m->_13 = m->_13 / s.x;	m->_14 = 0.0f;
            m->_21 = m->_21 / s.y;	m->_22 = m->_22 / s.y;	m->_23 = m->_23 / s.y;	m->_24 = 0.0f;
            m->_31 = m->_31 / s.z;	m->_32 = m->_32 / s.z;	m->_33 = m->_33 / s.z;	m->_34 = 0.0f;
            return m;
        }
        /**
        * @brief 転置行列作成
        * @param[out] out 転置後行列
        * @param[in] in 行列
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixTranspose(Matrix* out, const Matrix& in)
        {
            Matrix work = in;
            for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)out->m[j][i] = work.m[i][j];
            return out;
        }

        /**
        * @brief X軸回転行列作成
        * @param[out] out 回転行列
        * @param[in] r X回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixRotationX(Matrix* out, f32 r)
        {
            f32 s = sinf(r);
            f32 c = cosf(r);

            out->_11 = 1.0f;	out->_12 = 0.0f;	out->_13 = 0.0f;	out->_14 = 0.0f;
            out->_21 = 0.0f;	out->_22 = c;		out->_23 = s;		out->_24 = 0.0f;
            out->_31 = 0.0f;	out->_32 = -s;		out->_33 = c;		out->_34 = 0.0f;
            out->_41 = 0.0f;	out->_42 = 0.0f;	out->_43 = 0.0f;	out->_44 = 1.0f;

            return out;
        }
        /**
        * @brief Y軸回転行列作成
        * @param[out] out 回転行列
        * @param[in] r Y回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixRotationY(Matrix* out, f32 r)
        {
            f32 s = sinf(r);
            f32 c = cosf(r);

            out->_11 = c;			out->_12 = 0.0f;	out->_13 = -s;			out->_14 = 0.0f;
            out->_21 = 0.0f;		out->_22 = 1.0f;	out->_23 = 0;			out->_24 = 0.0f;
            out->_31 = s;			out->_32 = 0.0f;	out->_33 = c;			out->_34 = 0.0f;
            out->_41 = 0.0f;		out->_42 = 0.0f;	out->_43 = 0.0f;		out->_44 = 1.0f;

            return out;
        }
        /**
        * @brief Z軸回転行列作成
        * @param[out] out 回転行列
        * @param[in] r Z回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixRotationZ(Matrix* out, f32 r)
        {
            f32 s = sinf(r);
            f32 c = cosf(r);

            out->_11 = c;			out->_12 = s;			out->_13 = 0.0f;	out->_14 = 0.0f;
            out->_21 = -s;			out->_22 = c;			out->_23 = 0.0f;	out->_24 = 0.0f;
            out->_31 = 0.0f;		out->_32 = 0.0f;		out->_33 = 1.0f;	out->_34 = 0.0f;
            out->_41 = 0.0f;		out->_42 = 0.0f;		out->_43 = 0.0f;	out->_44 = 1.0f;

            return out;
        }
        /**
        * @brief XYZ軸回転行列作成(XYZオーダー)
        * @param[out] out 回転行列
        * @param[in] a 回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixRotationXYZ(Matrix* out, const Vector3& a)
        {
            f32	sx, sy, sz, cx, cy, cz;

            sx = sinf(a.x);	sy = sinf(a.y);	sz = sinf(a.z);
            cx = cosf(a.x);	cy = cosf(a.y);	cz = cosf(a.z);

            out->_11 = (cy*cz);out->_12 = (cy*sz);out->_13 = (-sy);out->_14 = (0.0f);
            out->_21 = (sx*sy*cz + (-cx*sz));out->_22 = (sx*sy*sz + cx*cz);out->_23 = (sx*cy);out->_24 = (0.0f);
            out->_31 = (cx*sy*cz + sx*sz);out->_32 = (cx*sy*sz + (-sx*cz));out->_33 = (cx*cy);out->_34 = (0.0f);
            out->_41 = (0.0f);out->_42 = (0.0f);out->_43 = (0.0f);out->_44 = (1.0f);

            return out;
        }

        /**
        * @brief XYZ軸回転行列作成(ZXYオーダー)
        * @param[out] out 回転行列
        * @param[in] a 回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixRotationZXY(Matrix* out, const Vector3& a)
        {
            f32	sx, sy, sz, cx, cy, cz;

            sx = sinf(a.x);	sy = sinf(a.y);	sz = sinf(a.z);
            cx = cosf(a.x);	cy = cosf(a.y);	cz = cosf(a.z);

            out->_11 = (cz*cy + sz*sx*sy);	out->_12 = (sz*cx);out->_13 = (-cz*sy + sz*sx*cy);out->_14 = (0.0f);
            out->_21 = (-sz*cy + cz*sx*sy);out->_22 = (cz*cx);out->_23 = (sz*sy + cz*sx*cy);	out->_24 = (0.0f);
            out->_31 = (cx*sy);out->_32 = (-sx);	out->_33 = (cx*cy);out->_34 = (0.0f);
            out->_41 = (0.0f);	out->_42 = (0.0f);	out->_43 = (0.0f);	out->_44 = (1.0f);

            return out;
        }

        /**
        * @brief 任意軸回転行列作成
        * @param[out] out 回転行列
        * @param[in] axis 回転軸
        * @param[in] r 回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* MatrixAxisRotation(Matrix* out, const Vector3& axis, f32 r)
        {
            f32 s = sinf(r);
            f32 c = cosf(r);

            out->_11 = (axis.x*axis.x)*(1.0f - c) + c;out->_12 = (axis.x*axis.y)*(1.0f - c) + axis.z*s;out->_13 = (axis.z*axis.x)*(1.0f - c) - axis.y*s;out->_14 = 0.0f;
            out->_21 = (axis.x*axis.y)*(1.0f - c) - axis.z*s;out->_22 = (axis.y*axis.y)*(1.0f - c) + c;out->_23 = (axis.y*axis.z)*(1.0f - c) + axis.x*s;out->_24 = 0.0f;
            out->_31 = (axis.z*axis.x)*(1.0f - c) + axis.y*s;out->_32 = (axis.y*axis.z)*(1.0f - c) - axis.x*s;out->_33 = (axis.z*axis.z)*(1.0f - c) + c;out->_34 = 0.0f;
            out->_41 = 0.0f;out->_42 = 0.0f;out->_43 = 0.0f;out->_44 = 1.0f;

            return out;
        }

        static EVOLUTION_INLINE Matrix* MatrixFrontVec(Matrix* out, const Vector3& Pos, const Vector3& Front, const Vector3& Up)
        {
            Vector3 xaxis = Vector3(Up.y*Front.z - Up.z*Front.y, Up.z*Front.x - Up.x*Front.z, Up.x*Front.y - Up.y*Front.x);
            Vector3 yaxis = Vector3(Front.y*xaxis.z - Front.z*xaxis.y, Front.z*xaxis.x - Front.x*xaxis.z, Front.x*xaxis.y - Front.y*xaxis.x);

            xaxis.Normalize();
            yaxis.Normalize();

            out->_11 = xaxis.x;	out->_12 = xaxis.y;	out->_13 = xaxis.z;	out->_14 = 0;
            out->_21 = yaxis.x;	out->_22 = yaxis.y;	out->_23 = yaxis.z;	out->_24 = 0;
            out->_31 = Front.x;	out->_32 = Front.y;	out->_33 = Front.z;	out->_34 = 0;
            out->_41 = Pos.x;out->_42 = Pos.y;out->_43 = Pos.z;out->_44 = 1;
            return out;
        }
        //*****************************************************************************
        //
        //		クォータニオン関連
        //
        //*****************************************************************************
        //*****************************************************************************
        //		変換関連
        //*****************************************************************************
        /**
        * @brief クォータニオンを行列に変換する
        * @param[out] out 回転行列
        * @param[in] q クォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Matrix* QuaternionToMatrix(Matrix* out, const Quaternion& q)
        {
            f32 s = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
            s = 2.0f / (s * s);
            f32 vx = q.x * s;
            f32 vy = q.y * s;
            f32 vz = q.z * s;
            f32 wx = vx * q.w;
            f32 wy = vy * q.w;
            f32 wz = vz * q.w;
            f32 sx = q.x * vx;
            f32 sy = q.y * vy;
            f32 sz = q.z * vz;
            f32 cx = q.y * vz;
            f32 cy = q.z * vx;
            f32 cz = q.x * vy;

            out->_11 = 1.0f - sy - sz;
            out->_12 = cz + wz;
            out->_13 = cy - wy;
            out->_14 = 0.0f;
            out->_21 = cz - wz;
            out->_22 = 1.0f - sx - sz;
            out->_23 = cx + wx;
            out->_24 = 0.0f;
            out->_31 = cy + wy;
            out->_32 = cx - wx;
            out->_33 = 1.0f - sx - sy;
            out->_34 = 0.0f;
            out->_41 = 0.0f;
            out->_42 = 0.0f;
            out->_43 = 0.0f;
            out->_44 = 1.0f;

            return out;
        }
        /**
        * @brief クォータニオンからオイラー角に変換(XYZオーダー行列専用)
        * @param[out] out オイラー角
        * @param[in] q クォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* QuaternionToEulerXYZ(Vector3* out, const Quaternion& q)
        {
            Matrix work;
            QuaternionToMatrix(&work, q);
            return MatrixToEulerXYZ(out, work);
        }
        /**
        * @brief クォータニオンからオイラー角に変換(ZXYオーダー行列専用)
        * @param[out] out オイラー角
        * @param[in] q クォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* QuaternionToEulerZXY(Vector3* out, const Quaternion& q)
        {
            Matrix work;
            QuaternionToMatrix(&work, q);
            return MatrixToEulerZXY(out, work);
        }
        //*****************************************************************************
        //		関数関連
        //*****************************************************************************
        /**
        * @brief クォータニオンの内積
        * @param[in] q1 クォータニオン
        * @param[in] q2 クォータニオン
        * @return 内積
        */
        static EVOLUTION_INLINE f32 QuaternionDot(const Quaternion& q1, const Quaternion& q2)
        {
            return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
        }
        /**
        * @brief クォータニオンの長さの二乗を取得
        * @param[in] q クォータニオン
        * @return 長さの二乗
        */
        static EVOLUTION_INLINE f32 QuaternionLengthSq(const Quaternion& q)
        {
            return QuaternionDot(q, q);
        }
        /**
        * @brief クォータニオンの長さを取得
        * @param[in] q クォータニオン
        * @return 長さ
        */
        static EVOLUTION_INLINE f32 QuaternionLength(const Quaternion& q)
        {
            return sqrtf(QuaternionLengthSq(q));
        }
        /**
        * @brief クォータニオン同士の合成
        * q1の回転の後に、q2の回転をした結果を計算
        * @param[in] q1 最初の回転クォータニオン
        * @param[in] q2 次の回転クォータニオン
        * @return 回転結果のクォータニオン
        */
        static EVOLUTION_INLINE Quaternion QuaternionComp(const Quaternion& q1, const Quaternion& q2){ return q2*q1; }
        /**
        * @brief クォータニオンの球面線形補間
        * @param[out] out 補間後のクォータニオン
        * @param[in] q1 第一クォータニオン
        * @param[in] q2 第二クォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionSlerp(Quaternion* out, const Quaternion& q1, const Quaternion& q2, f32 t)
        {
            //	内積
            float dot = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
            float ss = 1.0f - (dot * dot);
            if (ss <= 0.0f)
            {
                *out = q1; return out;
            }

            Quaternion Target = q2;
            if (dot < 0.0f)
            {
                Target = -Target;
                dot = -dot;
            }
            //	内積値補正
            if (dot > 1.0f)
            {
                dot = 1.0f;
            }
            //	補間割合計算
            float ph = acosf(dot);
            float s = 1.0f / sinf(ph);
            float s1 = sinf(ph * (1.0f - t)) * s;
            float s2 = sinf(ph *  t) * s;
            *out = q1*s1 + Target*s2;
            //	補間
            return out;
        }
        /*
        * @brief ベクトルをクォータニオンで回転させる
        * @param[out] out 回転後ベクトル
        * @param[in] in クォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Vector3* QuaternionVec3Rotation(Vector3* out, const Quaternion& q)
        {
            *out = Vector3(q*Quaternion(*out)*q.CreateConjugate());
            return out;
        }
        //*****************************************************************************
        //		成分取得関連
        //*****************************************************************************
        /**
        * @brief クォータニオンの軸と回転角に分解する
        * @param[out] axis 軸
        * @param[out] rad 回転角
        * @param[in] クォータニオン
        */
        static EVOLUTION_INLINE void QuaternionDecompose(Vector3* axis, f32* rad, const Quaternion& q){
            *rad = acosf(q.w);
            axis->x = q.x / sinf(*rad);
            axis->y = q.y / sinf(*rad);
            axis->z = q.z / sinf(*rad);
            *rad *= 2.0f;
        }
        /**
        * @brief クォータニオンを姿勢ベクトルに分解する
        * 行列に変換して取得するよりは精度は悪いが高速
        * @param[out] right X軸ベクトル
        * @param[out] up Y軸ベクトル
        * @param[out] front Z軸ベクトル
        * @param[in] クォータニオン
        */
        static EVOLUTION_INLINE void QuaternionDecompose(Vector3* right, Vector3* up, Vector3* front, const Quaternion& q){
            f32 x2 = q.x + q.x;
            f32 y2 = q.y + q.y;
            f32 z2 = q.z + q.z;
            f32 xx = q.x * x2; f32 xy = q.x  * y2; f32 xz = q.x * z2;
            f32 yy = q.y * y2; f32 yz = q.y * z2; f32 zz = q.z * z2;
            f32 wx = q.w * x2; f32 wy = q.w * y2; f32 wz = q.w * z2;
            right->x = 1.0f - (yy + zz);
            right->y = xy + wz;
            right->z = xz - wy;
            up->x = xy - wz;
            up->y = 1.0f - (xx + zz);
            up->z = yz + wx;
            front->x = xz + wy;
            front->y = yz - wx;
            front->z = 1.0f - (xx + yy);
        }
        //*****************************************************************************
        //		行列作成関連
        //*****************************************************************************
        /**
        * @brief クォータニオンを単位化
        * @param[out] q 単位化するクォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionIdentity(Quaternion* q)
        {
            q->x = 0.0f;
            q->y = 0.0f;
            q->z = 0.0f;
            q->w = 1.0f;
            return q;
        }
        /**
        * @brief クォータニオンを共役クォータニオンで返す(-x,-y,-z,w)
        * @param[out] out 共役化されたクォータニオン
        * @param[in] in クォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionConjugate(Quaternion* out, const Quaternion& in)
        {
            out->x = -in.x;
            out->y = -in.y;
            out->z = -in.z;
            out->w = in.w;
            return out;
        }
        /**
        * @brief クォータニオンを正規化
        * @param[out] out 正規化されたクォータニオン
        * @param[in] in 正規化するクォータニオン
        * @return 出力結果と同じ(正規化できなければNULLが帰る)
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionNormalize(Quaternion* out, const Quaternion& in)
        {
            f32 len = QuaternionLength(in);
            //長さが0なら正規化できないとしてエラー
            assert(len != 0.0f);
            *out = in / len;
            return out;
        }
        /**
        * @brief クォータニオンを逆数化
        * @param[out] out 逆数化されたクォータニオン
        * @param[in] in 逆数化するクォータニオン
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionInverse(Quaternion* out, const Quaternion& in)
        {
            *out = (*QuaternionConjugate(out, in)) / QuaternionLengthSq(in);
        }
        /**
        * @brief X軸回転クォータニオンを作成
        * @param[out] out 回転クォータニオン
        * @param[in] rad 回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionRotationX(Quaternion* out, float rad)
        {
            f32 r = rad*0.5f;
            out->x = sinf(r);
            out->y = 0.0f;
            out->z = 0.0f;
            out->w = cosf(r);
            return out;
        }
        /**
        * @brief Y軸回転クォータニオンを作成
        * @param[out] out 回転クォータニオン
        * @param[in] rad 回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionRotationY(Quaternion* out, float rad)
        {
            f32 r = rad*0.5f;
            out->x = 0.0f;
            out->y = sinf(r);
            out->z = 0.0f;
            out->w = cosf(r);
            return out;
        }
        /**
        * @brief Z軸回転クォータニオンを作成
        * @param[out] out 回転クォータニオン
        * @param[in] rad 回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionRotationZ(Quaternion* out, float rad)
        {
            f32 r = rad*0.5f;
            out->x = 0.0f;
            out->y = 0.0f;
            out->z = sinf(r);
            out->w = cosf(r);
            return out;
        }
        /**
        * @brief XYZ回転クォータニオンを作成
        * @param[out] out 回転クォータニオン
        * @param[in] sx x回転角
        * @param[in] sy y回転角
        * @param[in] sz z回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionRotationXYZ(Quaternion* out, const Vector3& angle)
        {
            f32 ssx = sinf(angle.x*.5f);
            f32 ssy = sinf(angle.y*.5f);
            f32 ssz = sinf(angle.z*.5f);
            f32 csx = cosf(angle.x*.5f);
            f32 csy = cosf(angle.y*.5f);
            f32 csz = cosf(angle.z*.5f);

            out->w = csz*csy*csx + ssz*ssy*ssx;
            out->x = csz*csy*ssx - ssz*ssy*csx;
            out->y = csz*ssy*csx + ssz*csy*ssx;
            out->z = ssz*csy*csx - csz*ssy*ssx;

            return out;
        }
        /**
        * @brief ZXY回転クォータニオンを作成
        * @param[out] out 回転クォータニオン
        * @param[in] sx x回転角
        * @param[in] sy y回転角
        * @param[in] sz z回転角
        * @return 出力結果と同じ
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionRotationZXY(Quaternion* out, const Vector3& angle)
        {
            f32 ssx = sinf(angle.x*.5f);
            f32 ssy = sinf(angle.y*.5f);
            f32 ssz = sinf(angle.z*.5f);
            f32 csx = cosf(angle.x*.5f);
            f32 csy = cosf(angle.y*.5f);
            f32 csz = cosf(angle.z*.5f);

            out->w = csy*csx*csz + ssy*csx*ssz;
            out->x = ssy*csx*ssz + csy*ssx*csz;
            out->y = -csy*ssx*ssz + ssy*csx*csz;
            out->z = -ssy*ssx*csz + csy*csx*ssz;

            return out;
        }
        /**
        * @brief 任意の軸と回転角からクォータニオンを作成する
        * @param[out] out クォータニオン
        * @param[in] axis 任意の軸
        * @param[in] rad 回転角
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionAxisRotation(Quaternion* out, const Vector3 &axis, f32 rad){
            f32 d = rad * 0.5f;
            out->x = axis.x*sinf(d);
            out->y = axis.y*sinf(d);
            out->z = axis.z*sinf(d);
            out->w = cosf(d);
            return out;
        }

        static bool hitSphere(const Vector3& p1, float r1, const Vector3& p2, float r2)
        {
            float xx = p2.x - p1.x;
            float yy = p2.y - p1.y;
            float zz = p2.z - p1.z;
            float rr = r1 + r2;
            return (xx*xx + yy*yy + zz*zz) <= (rr*rr);
        }

    }
}
#endif //!__EVOLUTION_MATH_UTILITY_H__
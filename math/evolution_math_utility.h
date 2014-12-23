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
        //�P���x���������_�^�̏������l
        const f64  FEQ_EPS = 1e-6;
        //�P���x���������_�^�̂���ɏ������l
        const f64  FEQ_EPS2 = 1e-12;

        //�~����*2
        const f32 PI_F2 = 6.28318548f;
        //1���W�A�����b
        const f32 RAD = 57.2957802f;
        //1�x���b
        const f32 DEG = 0.0174532924f;

        //
        const f32 FLOAT_MAX = 3.402823466e+38f;
        const f32 FLOAT_MIN = 1.175494351e-38f;

        /**
        * @brief min�`max�̊Ԃ���`���
        * @param[int] _X �X�J���[
        */
        template<typename T, typename U>
        EVOLUTION_INLINE T lerp(T min, T max, U t)
        {
            return min + (max - min)*t;
        }


        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 absf(f32 _X){ unsigned int tmp = *((unsigned int*)&_X) & 0x7FFFFFFF; return *((float*)&tmp); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 sinf(f32 _X){ return ::sinf(_X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 cosf(f32 _X){ return ::cosf(_X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 tanf(f32 _X){ return ::tanf(_X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 asinf(f32 _X){/*DYNAMIC_ASSERT_LIMIT(_X,-1.0f,1.0f)*/; return ::asinf(_X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 acosf(f32 _X){/*DYNAMIC_ASSERT_LIMIT(_X,-1.0f,1.0f)*/; return ::acosf(_X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 atanf(f32 _X){ return ::atanf(_X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 atan2f(f32 _Y, f32 _X){ return ::atan2f(_Y, _X); }
        /**
        * @brief ��Βl�擾�֐�
        * @param[int] _X �X�J���[
        */
        static EVOLUTION_INLINE f32 sqrtf(f32 _X){ return ::sqrtf(_X); }

        /**
        * @brief 32bit�����^v��b�`e�̊ԂŌJ��Ԃ�
        * @param[in] b �X�J���[
        * @param[in] e �X�J���[
        * @param[in] v �X�J���[
        * @return ���b�v�A���E���h���ꂽ�l
        */
        static EVOLUTION_INLINE s32 wrapi(s32 b, s32 e, s32 v)
        {
            s32 dist = e - b;
            v -= b;
            v -= (v / dist)*dist;
            return v + (v >> 31 & dist) + b;
        }
        /**
        * @brief 32bit���������_�^v��b�`e�̊ԂŌJ��Ԃ�
        * @param[in] b �X�J���[
        * @param[in] e �X�J���[
        * @param[in] v �X�J���[
        * @return ���b�v�A���E���h���ꂽ�l
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
        * @brief 64bit�����^v��b�`e�̊ԂŌJ��Ԃ�
        * @param[in] b �X�J���[
        * @param[in] e �X�J���[
        * @param[in] v �X�J���[
        * @return ���b�v�A���E���h���ꂽ�l
        */
        static EVOLUTION_INLINE s64 wrapl(s64 b, s64 e, s64 v)
        {
            s64 dist = e - b;
            v -= b;
            v -= (v / dist)*dist;
            return v + (v >> 63 & dist) + b;
        }
        /**
        * @brief 64bit���������_�^v��b�`e�̊ԂŌJ��Ԃ�
        * @param[in] b �X�J���[
        * @param[in] e �X�J���[
        * @param[in] v �X�J���[
        * @return ���b�v�A���E���h���ꂽ�l
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
        * @brief V��Min�`Max�̊ԂŃN�����v
        * @param[in] Min �ŏ��l
        * @param[in] Max �ő�l
        * @param[in] V �l
        * @return �N�����v���ꂽ�l
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
        * @brief V��Min�`Max�̊ԂŃN�����v
        * @param[in] Min �ŏ��l
        * @param[in] Max �ő�l
        * @param[in] V �l
        * @return �N�����v���ꂽ�l
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
        * @brief 0�`1�̊ԂɃN�����v
        * @param[in] _X �X�J���[
        * @return �N�����v���ꂽ�l
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
        * @brief 0�`1�̊ԂɃN�����v
        * @param[input] _X �X�J���[
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
        * @brief �p�x�����W�A���ɕϊ����܂�
        * @param[int] deg �p�x
        * @return ���W�A��
        */
        static EVOLUTION_INLINE f32 ToRadian(f32 deg){ return (deg)* (PI_F / 180.0f); }
        /**
        * @brief ���W�A�����p�x�ɕϊ����܂�
        * @param[int] rad ���W�A���p
        * @return �p�x
        */
        static EVOLUTION_INLINE f32 ToDegree(f32 rad){ return (rad)* (180.0f / PI_F); }
        //*****************************************************************************
        //
        //		Vector2�֘A
        //
        //*****************************************************************************
        //*****************************************************************************
        //		�ϊ��֘A
        //*****************************************************************************
        static EVOLUTION_INLINE f32 Vector2toEuler(const Vector2& vec)
        {
            return acosf(vec.x);
        }
        //*****************************************************************************
        //		�֐��֘A
        //*****************************************************************************
        static EVOLUTION_INLINE f32 Vector2Dot(const Vector2& from, const Vector2& dest){ return from.x*dest.x + from.y, dest.y; }
        static EVOLUTION_INLINE f32 Vector2Cross(const Vector2& from, const Vector2& dest){ return from.x*dest.y - dest.x*from.y; }
        static EVOLUTION_INLINE f32 Vector2LengthSq(const Vector2& vec){ return Vector2Dot(vec, vec); }
        static EVOLUTION_INLINE f32 Vector2Length(const Vector2& vec){ return sqrtf(Vector2LengthSq(vec)); }
        /**
        * @brief �x�N�g����C�ӂ̒����ŕ�������
        * @param[out] out ���ʃx�N�g��
        * @param[in] in �x�N�g��
        * @param[in] len �C�ӂ̒���
        * @return �o�͌��ʂƓ���
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
            //�x�N�g���̋������O�Ȃ�G���[
            assert(len != 0.0f);
            *out = vec / len;
            return out;
        }
        /**
        * @brief �x�N�g�����m�����p�x�����߂�
        * @param[in] from �p�x�����߂邱����̃x�N�g��.
        * @param[in] dest �p�x�����߂鑊��x�N�g��.
        * @return �p�x.
        */
        static EVOLUTION_INLINE f32 Vector2Degree(const Vector2& from, const Vector2& dest)
        {
            float cos_Theta = Vector2Dot(from, dest) / Vector2Length(from) * Vector2Length(dest);
            clampf(-1.0f, 1.0f, &cos_Theta);
            float angle = acosf(cos_Theta);
            return angle;
        }
        /**
        * @brief �x�N�g�����m����`��Ԃ���
        * @param[out] out ��Ԃ��ꂽ�x�N�g��
        * @param[in] from ��Ԃ��邱����̃x�N�g��
        * @param[in] dest �⊮���鑊��̃x�N�g��
        * @return �o�͌��ʂƓ���
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
        //		�x�N�g���쐬�֘A
        //*****************************************************************************
        static EVOLUTION_INLINE const Vector2* Vector2fromEuler(Vector2* out, f32 r)
        {
            out->x = cosf(r);
            out->y = sinf(r);
            return out;
        }
        //*****************************************************************************
        //
        //		Vector3�֘A
        //
        //*****************************************************************************
        //*****************************************************************************
        //		�ϊ��֘A
        //*****************************************************************************
        /**
        * @brief �x�N�g������p(pitch�p)�ƕ��ʊp(yaw�p)�����߂�(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
        * @param[out] out ���߂��p�x
        * @param[in] in �ϊ�����x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* Vector3toEuler(Vector3* out, const Vector3& in)
        {
            float len;
            // �x�N�g���̒��������߂�
            len = sqrtf(in.x*in.x + in.y*in.y + in.z*in.z);
            // �������O�̏ꍇ�̓G���[
            assert(len != 0.0f);
            // �x�N�g���𐳋K������
            float X = in.x / len;
            float Y = in.y / len;
            float Z = in.z / len;
            // �s�b�`�̌v�Z���s��
            out->x = asinf(-Y);
            // ���[�̌v�Z���s��
            out->y = atan2f(X, Z);
            return out;
        }
        //*****************************************************************************
        //		�֐��֘A
        //*****************************************************************************
        /**
        * @brief �x�N�g���̊O�ς����߂�
        * @param[out] out �x�N�g���̊O��
        * @param[in] from �O�ς����߂邱����̃x�N�g��
        * @param[in] dest �O�ς����߂鑊��̃x�N�g��
        * @return �o�͌��ʂƓ���
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
        * @brief �x�N�g���̓��ς����߂�
        * @param[in] from ���ς����߂邱����̃x�N�g��
        * @param[in] dest ���ς����߂鑊��̃x�N�g��
        * @return �x�N�g���̓���
        */
        static EVOLUTION_INLINE f32 Vector3Dot(const Vector3& from, const Vector3& dest)
        {
            return from.x*dest.x + from.y*dest.y + from.z*dest.z;
        }
        /**
        * @brief �x�N�g���̒����̓������߂�
        * @param[in] val ���������߂�x�N�g��
        * @return �x�N�g���̒����̓��
        */
        static EVOLUTION_INLINE f32 Vector3LengthSq(const Vector3& val)
        {
            return Vector3Dot(val, val);
        }
        /**
        * @brief �x�N�g���̒��������߂�
        * @param[in] val ���������߂�x�N�g��
        * @return �x�N�g���̒���
        */
        static EVOLUTION_INLINE f32 Vector3Length(const Vector3& val)
        {
            return sqrtf(Vector3LengthSq(val));
        }
        /**
        * @brief �x�N�g����C�ӂ̒����ŕ�������
        * @param[out] out ���ʃx�N�g��
        * @param[in] in �x�N�g��
        * @param[in] len �C�ӂ̒���
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* Vector3SetLength(Vector3* out, const Vector3& in, f32 len)
        {
            *out = (in / Vector3Length(in))*len;
            return out;
        }
        /**
        * @brief �x�N�g���̋����̓������߂�
        * @param[in] from ���������߂�x�N�g��
        * @param[in] dest ���������߂�x�N�g��
        * @return �x�N�g���̋����̓��
        */
        static EVOLUTION_INLINE f32 Vector3DistanceSq(const Vector3& from, const Vector3& dest)
        {
            return Vector3LengthSq(dest - from);
        }
        /**
        * @brief �x�N�g���̋��������߂�
        * @param[in] from ���������߂�x�N�g��
        * @param[in] dest ���������߂�x�N�g��
        * @return �x�N�g���̋���
        */
        static EVOLUTION_INLINE f32 Vector3Distance(const Vector3& from, const Vector3& dest)
        {
            return Vector3Length(dest - from);
        }
        /**
        * @brief �x�N�g���̒��������߂�
        * @param[in] val ���������߂�x�N�g��
        * @return �x�N�g���̒���
        */
        static EVOLUTION_INLINE const Vector3* Vector3Normalize(Vector3* out, const Vector3& val)
        {
            f32 len = Vector3Length(val);
            //�x�N�g���̒�����0�Ȃ�G���[
            //assert(len!=0.0f);
            *out = val / len;
            return out;
        }
        /**
        * @brief �x�N�g�����m�����p�x�����߂�
        * @param[in] from �p�x�����߂邱����̃x�N�g��.
        * @param[in] dest �p�x�����߂鑊��x�N�g��.
        * @return �p�x.
        */
        static EVOLUTION_INLINE f32 Vector3Degree(const Vector3& from, const Vector3& dest)
        {
            float cos_Theta = Vector3Dot(from, dest) / Vector3Length(from) * Vector3Length(dest);
            clampf(-1.0f, 1.0f, &cos_Theta);
            float angle = acosf(cos_Theta);
            return angle;
        }
        /**
        * @brief �x�N�g�����m����`��Ԃ���
        * @param[out] out ��Ԃ��ꂽ�x�N�g��
        * @param[in] from ��Ԃ��邱����̃x�N�g��
        * @param[in] dest �⊮���鑊��̃x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* Vector3Lerp(Vector3* out, const Vector3& from, const Vector3& dest, f32 t)
        {
            out->x = lerp(from.x, dest.x, t);
            out->y = lerp(from.y, dest.y, t);
            out->z = lerp(from.z, dest.z, t);
            return out;
        }
        /**
        * @brief �x�N�g�����m�����ʐ��`��Ԃ���
        * @param[out] out ��Ԃ��ꂽ�x�N�g��
        * @param[in] from ��Ԃ��邱����̃x�N�g��
        * @param[in] dest �⊮���鑊��̃x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* Vector3Slerp(Vector3* out, const Vector3& from, const Vector3& dest, f32 t)
        {
            // 2�x�N�g���Ԃ̊p�x�i�s�p���j
            f32 angle = acosf(Vector3Dot(from, dest));
            // sin��
            f32 SinTh = sinf(angle);
            // ��ԌW��
            f32 Ps = sinf(angle * (1.0f - t));
            f32 Pe = sinf(angle * t);
            *out = (from  * Ps + dest * Pe) / SinTh;
            // �ꉞ���K�����ċ��ʐ��`��Ԃ�
            return Vector3Normalize(out, *out);
        }

        /**
        * ���˃x�N�g�������߂� �D
        * @param[out] out ���˃x�N�g��
        * @param[in] front �i�s�x�N�g��
        * @param [in]  normal �@���x�N�g�� �D
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* Vector3Reflect(Vector3* out, const Vector3& front, const Vector3& normal)
        {
            Vector3 v(-front);
            Vector3 t(normal * (Vector3Dot(v, normal) * 2.0f));
            *out = t + front;
            return out;
        }

        /**
        * ���܃x�N�g�������߂�D
        * @param[out] out ���܃x�N�g��
        * @param[in] front �i�s�x�N�g��
        * @param [in]  normal �@���x�N�g�� �D
        * @param[in] Eta ���ܗ�
        * @return �o�͌��ʂƓ���
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
        * @brief �ˉe�x�N�g���̒��������߂�
        * @param[in] from �ˉe����x�N�g��
        * @param[in] dest �ˉe�����x�N�g��
        * @return �ˉe�x�N�g���̒���
        */
        static EVOLUTION_INLINE f32 Vector3ProjectionLength(const Vector3& from, const Vector3& dest){ return Vector3Dot(from, dest) / Vector3Length(dest); }
        /**
        * @brief �ˉe�x�N�g�������߂�
        * @param[out] out �ˉe�x�N�g��
        * @param[in] from �ˉe����x�N�g��
        * @param[in] dest �ˉe�����x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* Vector3Projection(Vector3* out, const Vector3& from, const Vector3& dest)
        {
            *out = dest*(Vector3Dot(from, dest) / Vector3LengthSq(dest));
            return out;
        }
        //*****************************************************************************
        //		�x�N�g���쐬�֘A
        //*****************************************************************************
        /**
        * @brief �p(pitch�p)�ƕ��ʊp(yaw�p)����x�N�g�������߂�
        * @param[out] out ���߂��x�N�g��
        * @param[in] pitch �s�b�`�p(X��)
        * @param[in] yaw ���[�p(Y��)
        * @return ���߂��x�N�g��.
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
        //		Vector4�֘A
        //
        //*****************************************************************************
        //*****************************************************************************
        //		�֐��֘A
        //*****************************************************************************
        /**
        * @brief �x�N�g���̓��ς����߂�
        * @param[in] from ���ς����߂邱����̃x�N�g��
        * @param[in] dest ���ς����߂鑊��̃x�N�g��
        * @return �x�N�g���̓���
        */
        static EVOLUTION_INLINE f32 Vector4Dot(const Vector4& from, const Vector4& dest){ return from.x*dest.x + from.y*dest.y + from.z*dest.z + from.w*dest.w; }
        /**
        * @brief �x�N�g���̒����̓������߂�
        * @param[in] vec �����̓������߂�x�N�g��
        * @return �x�N�g���̒����̓��
        */
        static EVOLUTION_INLINE f32 Vector4LengthSq(const Vector4& vec){ return Vector4Dot(vec, vec); }
        /**
        * @brief �x�N�g���̒��������߂�
        * @param[in] vec ���������߂�x�N�g��
        * @return �x�N�g���̒���
        */
        static EVOLUTION_INLINE f32 Vector4Length(const Vector4& vec){ return sqrtf(Vector4LengthSq(vec)); }
        /**
        * @brief �x�N�g���𐳋K������
        * @param[out] out ���K�������x�N�g��
        * @param[in] vec ���K������x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector4* Vector4Normalize(Vector4* out, const Vector4& vec)
        {
            f32 len = Vector4Length(vec);
            //�x�N�g���̒�����0�Ȃ�G���[
            assert(len != 0.0f);
            *out = vec / len;
            return out;
        }
        /**
        * @brief �x�N�g�����m����`��Ԃ���
        * @param[out] out ��Ԃ��ꂽ�x�N�g��
        * @param[in] from ��Ԃ��邱����̃x�N�g��
        * @param[in] dest �⊮���鑊��̃x�N�g��
        * @return �o�͌��ʂƓ���
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
        //		�s��֘A
        //
        //*****************************************************************************
        //*****************************************************************************
        //		�ϊ��֘A
        //*****************************************************************************
        /**
        * @brief �s����N�H�[�^�j�I���ɕϊ�����(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
        * @param[out] q ��]�N�H�[�^�j�I��
        * @param[in] mat ��]�s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Quaternion* MatrixToQuaternion(Quaternion* q, const Matrix& mat)
        {
            // �ő听��������
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

            // �ő�v�f�̒l���Z�o
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
        * @brief �s�񂩂�I�C���[�p�ɕϊ�(XYZ�I�[�_�[�s���p)(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
        * @param[out] out �I�C���[�p
        * @param[in] mat ��]�s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* MatrixToEulerXYZ(Vector3* out, const Matrix& mat)
        {
            out->y = asinf(-mat._13);
            f32 C = cosf(out->y);

            //cos(��)��0�łȂ����
            if (absf(C) > FEQ_EPS) {
                out->x = (mat._33 < 0) ? PI_F - asinf(mat._23 / C) : asinf(mat._23 / C);
                out->z = atan2f(mat._12, mat._11);
            }
            //cos(��)��0�Ȃ��
            else
            {
                out->x = 0.0f;
                out->z = atan2f(-mat._21, mat._22);
            }

            return out;
        }
        /**
        * @brief �s�񂩂�I�C���[�p�ɕϊ�(ZXY�I�[�_�[�s���p)(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
        * @param[out] out �I�C���[�p
        * @param[in] mat ��]�s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* MatrixToEulerZXY(Vector3* out, const Matrix& mat)
        {
            out->x = asinf(-mat._32);
            f32 C = cosf(out->x);

            //cos(��)��0�łȂ����
            if (absf(C) > FEQ_EPS) {
                out->z = (mat._22 < 0) ? PI_F - asinf(mat._12 / C) : asinf(mat._12 / C);
                out->y = atan2f(mat._31, mat._33);
            }
            //cos(��)��0�Ȃ��
            else
            {
                out->z = 0.0f;
                out->y = atan2f(-mat._13, mat._11);
            }

            return out;
        }
        //*****************************************************************************
        //		�֐��֘A
        //*****************************************************************************
        /**
        * @brief 4x4�s��̍s�񎮂̌v�Z
        * @param[in] mat ���̍s��
        * @return �s�񎮂̒l
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
        * @brief �x�N�g����(x,y,z,1)�Ƃ��čs��ϊ�
        * in��out������ł����S
        * @param[out] out �ϊ���̃x�N�g��
        * @param[in] i �ϊ��O�̃x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector4* MatrixVec3Transform(Vector4* out, const Vector3& in, const Matrix& mat)
        {
            Vector4 work;
            //�ϊ�
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31 + mat._41;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32 + mat._42;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33 + mat._43;
            work.w = in.x*mat._14 + in.y*mat._24 + in.z*mat._34 + mat._44;
            *out = work;
            return out;
        }
        /**
        * @brief �x�N�g����(x,y,z,1)�Ƃ��čs��ϊ��A�ϊ���w�Ɏˉe����
        * in��out������ł����S
        * @param[out] out �ϊ���̃x�N�g��
        * @param[in] i �ϊ��O�̃x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* MatrixVec3TransformCoord(Vector3* out, const Vector3& in, const Matrix& mat)
        {
            Vector3 work;
            //�ϊ�
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31 + mat._41;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32 + mat._42;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33 + mat._43;
            float w = in.x*mat._14 + in.y*mat._24 + in.z*mat._34 + mat._44;
            //�ˉe
            *out = work / w;
            return out;
        }
        /**
        * @brief �x�N�g����(x,y,z,0)�Ƃ��čs��ϊ�
        * in��out������ł����S
        * @param[out] out �ϊ���̃x�N�g��
        * @param[in] i �ϊ��O�̃x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* MatrixVec3TransformNormal(Vector3* out, const Vector3& in, const Matrix& mat)
        {
            Vector3 work;
            //�ϊ�
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33;
            //�ˉe
            *out = work;
            return out;
        }
        /**
        * @brief �x�N�g�����s��ϊ�
        * in��out������ł����S
        * @param[out] out �ϊ���̃x�N�g��
        * @param[in] i �ϊ��O�̃x�N�g��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector4* MatrixVec4Transform(Vector4* out, const Vector4& in, const Matrix& mat)
        {
            Vector4 work;
            //�ϊ�
            work.x = in.x*mat._11 + in.y*mat._21 + in.z*mat._31 + in.w*mat._41;
            work.y = in.x*mat._12 + in.y*mat._22 + in.z*mat._32 + in.w*mat._42;
            work.z = in.x*mat._13 + in.y*mat._23 + in.z*mat._33 + in.w*mat._43;
            work.w = in.x*mat._14 + in.y*mat._24 + in.z*mat._34 + in.w*mat._44;
            *out = work;
            return out;
        }

        //*****************************************************************************
        //		�����擾�֘A
        //*****************************************************************************
        /**
        * @brief �s��̊g�听�����擾����
        * @param[out] out �g�听��
        * @param[in] in �s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* MatrixGetScale(Vector3* out, const Matrix& in)
        {
            //X�����K��(�X�P�[������)
            out->x = sqrtf(in._11*in._11 + in._12*in._12 + in._13*in._13);
            //Y�����K��(�X�P�[������)
            out->y = sqrtf(in._21*in._21 + in._22*in._22 + in._23*in._23);
            //Z�����K��(�X�P�[������)
            out->z = sqrtf(in._31*in._31 + in._32*in._32 + in._33*in._33);
            return out;
        }
        /**
        * @brief �s��̊e���x�N�g�����擾
        * @param[out] right X���x�N�g��
        * @param[out] up Y���x�N�g��
        * @param[out] front Z���x�N�g��
        * @param[in] in �s��
        */
        static EVOLUTION_INLINE void MatrixGetAxis(Vector3* right, Vector3* up, Vector3* front, const Matrix& in)
        {
            right->x = in._11;	right->y = in._12;	right->z = in._13;
            up->x = in._21;		up->y = in._22;		up->z = in._23;
            front->x = in._31;	front->y = in._32;	front->z = in._33;
        }
        /**
        * @brief �s��̕��s�ړ��������擾����
        * @param[out] out �g�听��
        * @param[in] in �s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* MatrixGetTranslation(Vector3* out, const Matrix& in)
        {
            out->x = in._41;	out->y = in._42;	out->z = in._43;
            return out;
        }
        /**
        * @brief �s��𕪉��A�����ł��Ȃ���΃G���[
        * @param[out] s �g�听��
        * @param[out] q ��]�N�H�[�^�j�I��
        * @param[out] p ���s�ړ�����
        * @param[in] in �s��
        */
        static EVOLUTION_INLINE void MatrixDecompose(Vector3* s, Quaternion* q, Vector3* p, const Matrix& in)
        {
            Matrix work = in;
            MatrixGetScale(s, work);
            //�X�P�[������ł�0�Ȃ番���ł��Ȃ��Ƃ��ăG���[
            assert(s->x != 0.0f || s->y != 0.0f || s->z != 0.0f);
            work._11 /= s->x;	work._12 /= s->x;	work._13 /= s->x;
            work._21 /= s->y;	work._22 /= s->y;	work._23 /= s->y;
            work._31 /= s->z;	work._32 /= s->z;	work._33 /= s->z;
            MatrixToQuaternion(q, work);
            MatrixGetTranslation(p, in);
        }
        /**
        * @brief �s����x�N�g���ɕ���
        * @param[out] x X���x�N�g��
        * @param[out] y Y���x�N�g��
        * @param[out] z Z���x�N�g��
        * @param[out] p ���s�ړ�����
        * @param[in] in �s��
        */
        static EVOLUTION_INLINE void MatrixDecompose(Vector3* x, Vector3* y, Vector3* z, Vector3* p, const Matrix& in)
        {
            MatrixGetAxis(x, y, z, in);
            MatrixGetTranslation(p, in);
        }
        /**
        * @brief �s��̉�]�����𐳋K�������s����쐬����(�X�P�[�����O����Ă��Ă��������l���A�邱�Ƃ��ۏႳ��Ă���)
        * @param[out] out ���K�����ꂽ��]�s��
        * @param[in] in �s��
        * @return �o�͌��ʂƓ���
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
        * @brief �s�����]�N�H�[�^�j�I���ɕ�������(�X�P�[�����O����Ă��Ă��������l���A�邱�Ƃ��ۏႳ��Ă���)
        * @param[out] out ��]�N�H�[�^�j�I��
        * @param[in] in �s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Quaternion* MatrixDecomposeR(Quaternion* out, const Matrix& in)
        {
            Matrix work;
            //��]�������s��ɕ���
            MatrixDecomposeR(&work, in);
            //�N�H�[�^�j�I���ɕϊ�
            return MatrixToQuaternion(out, work);
        }
        //*****************************************************************************
        //		�s��쐬�֘A
        //*****************************************************************************
        /**
        * @brief 4x4�s��̒P�ʍs��
        * @param[inout] mat �s��
        */
        static EVOLUTION_INLINE void MatrixIdentity(Matrix* mat)
        {
            mat->m[0][0] = 1.0f;		mat->m[0][1] = 0.0f;		mat->m[0][2] = 0.0f;		mat->m[0][3] = 0.0f;
            mat->m[1][0] = 0.0f;		mat->m[1][1] = 1.0f;		mat->m[1][2] = 0.0f;		mat->m[1][3] = 0.0f;
            mat->m[2][0] = 0.0f;		mat->m[2][1] = 0.0f;		mat->m[2][2] = 1.0f;		mat->m[2][3] = 0.0f;
            mat->m[3][0] = 0.0f;		mat->m[3][1] = 0.0f;		mat->m[3][2] = 0.0f;		mat->m[3][3] = 1.0f;
        }
        /**
        * @brief 4x4�s��̋t�s������߂�A�t�s�񂪑��݂��Ȃ���΃G���[
        * @param[out] out �t�s��
        * @param[out] m ���̍s��
        * @return �t�s��̑���
        */
        static EVOLUTION_INLINE void MatrixInverse(Matrix* out, const Matrix& m)
        {
            Matrix mat = m;
            f32 det = MatrixDet(mat);

            //�s�񎮂�0�Ȃ�t�s�񂪑��݂��Ȃ��Ƃ��ăG���[
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
        * @brief �s��̉�]�����𐳋K������A���K���ł��Ȃ���΃G���[
        * @param[inout] m �s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Matrix* MatrixNormalize(Matrix* m)
        {
            Vector3 s;
            MatrixGetScale(&s, *m);
            //�X�P�[������ł�0�Ȃ琳�K���ł��Ȃ��Ƃ��ăG���[
            //assert(s.x!=0.0f || s.y!=0.0f || s.z!=0.0f);
            m->_11 = m->_11 / s.x;	m->_12 = m->_12 / s.x;	m->_13 = m->_13 / s.x;	m->_14 = 0.0f;
            m->_21 = m->_21 / s.y;	m->_22 = m->_22 / s.y;	m->_23 = m->_23 / s.y;	m->_24 = 0.0f;
            m->_31 = m->_31 / s.z;	m->_32 = m->_32 / s.z;	m->_33 = m->_33 / s.z;	m->_34 = 0.0f;
            return m;
        }
        /**
        * @brief �]�u�s��쐬
        * @param[out] out �]�u��s��
        * @param[in] in �s��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Matrix* MatrixTranspose(Matrix* out, const Matrix& in)
        {
            Matrix work = in;
            for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)out->m[j][i] = work.m[i][j];
            return out;
        }

        /**
        * @brief X����]�s��쐬
        * @param[out] out ��]�s��
        * @param[in] r X��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief Y����]�s��쐬
        * @param[out] out ��]�s��
        * @param[in] r Y��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief Z����]�s��쐬
        * @param[out] out ��]�s��
        * @param[in] r Z��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief XYZ����]�s��쐬(XYZ�I�[�_�[)
        * @param[out] out ��]�s��
        * @param[in] a ��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief XYZ����]�s��쐬(ZXY�I�[�_�[)
        * @param[out] out ��]�s��
        * @param[in] a ��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief �C�ӎ���]�s��쐬
        * @param[out] out ��]�s��
        * @param[in] axis ��]��
        * @param[in] r ��]�p
        * @return �o�͌��ʂƓ���
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
        //		�N�H�[�^�j�I���֘A
        //
        //*****************************************************************************
        //*****************************************************************************
        //		�ϊ��֘A
        //*****************************************************************************
        /**
        * @brief �N�H�[�^�j�I�����s��ɕϊ�����
        * @param[out] out ��]�s��
        * @param[in] q �N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
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
        * @brief �N�H�[�^�j�I������I�C���[�p�ɕϊ�(XYZ�I�[�_�[�s���p)
        * @param[out] out �I�C���[�p
        * @param[in] q �N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* QuaternionToEulerXYZ(Vector3* out, const Quaternion& q)
        {
            Matrix work;
            QuaternionToMatrix(&work, q);
            return MatrixToEulerXYZ(out, work);
        }
        /**
        * @brief �N�H�[�^�j�I������I�C���[�p�ɕϊ�(ZXY�I�[�_�[�s���p)
        * @param[out] out �I�C���[�p
        * @param[in] q �N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* QuaternionToEulerZXY(Vector3* out, const Quaternion& q)
        {
            Matrix work;
            QuaternionToMatrix(&work, q);
            return MatrixToEulerZXY(out, work);
        }
        //*****************************************************************************
        //		�֐��֘A
        //*****************************************************************************
        /**
        * @brief �N�H�[�^�j�I���̓���
        * @param[in] q1 �N�H�[�^�j�I��
        * @param[in] q2 �N�H�[�^�j�I��
        * @return ����
        */
        static EVOLUTION_INLINE f32 QuaternionDot(const Quaternion& q1, const Quaternion& q2)
        {
            return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
        }
        /**
        * @brief �N�H�[�^�j�I���̒����̓����擾
        * @param[in] q �N�H�[�^�j�I��
        * @return �����̓��
        */
        static EVOLUTION_INLINE f32 QuaternionLengthSq(const Quaternion& q)
        {
            return QuaternionDot(q, q);
        }
        /**
        * @brief �N�H�[�^�j�I���̒������擾
        * @param[in] q �N�H�[�^�j�I��
        * @return ����
        */
        static EVOLUTION_INLINE f32 QuaternionLength(const Quaternion& q)
        {
            return sqrtf(QuaternionLengthSq(q));
        }
        /**
        * @brief �N�H�[�^�j�I�����m�̍���
        * q1�̉�]�̌�ɁAq2�̉�]���������ʂ��v�Z
        * @param[in] q1 �ŏ��̉�]�N�H�[�^�j�I��
        * @param[in] q2 ���̉�]�N�H�[�^�j�I��
        * @return ��]���ʂ̃N�H�[�^�j�I��
        */
        static EVOLUTION_INLINE Quaternion QuaternionComp(const Quaternion& q1, const Quaternion& q2){ return q2*q1; }
        /**
        * @brief �N�H�[�^�j�I���̋��ʐ��`���
        * @param[out] out ��Ԍ�̃N�H�[�^�j�I��
        * @param[in] q1 ���N�H�[�^�j�I��
        * @param[in] q2 ���N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionSlerp(Quaternion* out, const Quaternion& q1, const Quaternion& q2, f32 t)
        {
            //	����
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
            //	���ϒl�␳
            if (dot > 1.0f)
            {
                dot = 1.0f;
            }
            //	��Ԋ����v�Z
            float ph = acosf(dot);
            float s = 1.0f / sinf(ph);
            float s1 = sinf(ph * (1.0f - t)) * s;
            float s2 = sinf(ph *  t) * s;
            *out = q1*s1 + Target*s2;
            //	���
            return out;
        }
        /*
        * @brief �x�N�g�����N�H�[�^�j�I���ŉ�]������
        * @param[out] out ��]��x�N�g��
        * @param[in] in �N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Vector3* QuaternionVec3Rotation(Vector3* out, const Quaternion& q)
        {
            *out = Vector3(q*Quaternion(*out)*q.CreateConjugate());
            return out;
        }
        //*****************************************************************************
        //		�����擾�֘A
        //*****************************************************************************
        /**
        * @brief �N�H�[�^�j�I���̎��Ɖ�]�p�ɕ�������
        * @param[out] axis ��
        * @param[out] rad ��]�p
        * @param[in] �N�H�[�^�j�I��
        */
        static EVOLUTION_INLINE void QuaternionDecompose(Vector3* axis, f32* rad, const Quaternion& q){
            *rad = acosf(q.w);
            axis->x = q.x / sinf(*rad);
            axis->y = q.y / sinf(*rad);
            axis->z = q.z / sinf(*rad);
            *rad *= 2.0f;
        }
        /**
        * @brief �N�H�[�^�j�I�����p���x�N�g���ɕ�������
        * �s��ɕϊ����Ď擾������͐��x�͈���������
        * @param[out] right X���x�N�g��
        * @param[out] up Y���x�N�g��
        * @param[out] front Z���x�N�g��
        * @param[in] �N�H�[�^�j�I��
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
        //		�s��쐬�֘A
        //*****************************************************************************
        /**
        * @brief �N�H�[�^�j�I����P�ʉ�
        * @param[out] q �P�ʉ�����N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
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
        * @brief �N�H�[�^�j�I���������N�H�[�^�j�I���ŕԂ�(-x,-y,-z,w)
        * @param[out] out ���������ꂽ�N�H�[�^�j�I��
        * @param[in] in �N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
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
        * @brief �N�H�[�^�j�I���𐳋K��
        * @param[out] out ���K�����ꂽ�N�H�[�^�j�I��
        * @param[in] in ���K������N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���(���K���ł��Ȃ����NULL���A��)
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionNormalize(Quaternion* out, const Quaternion& in)
        {
            f32 len = QuaternionLength(in);
            //������0�Ȃ琳�K���ł��Ȃ��Ƃ��ăG���[
            assert(len != 0.0f);
            *out = in / len;
            return out;
        }
        /**
        * @brief �N�H�[�^�j�I�����t����
        * @param[out] out �t�������ꂽ�N�H�[�^�j�I��
        * @param[in] in �t��������N�H�[�^�j�I��
        * @return �o�͌��ʂƓ���
        */
        static EVOLUTION_INLINE const Quaternion* QuaternionInverse(Quaternion* out, const Quaternion& in)
        {
            *out = (*QuaternionConjugate(out, in)) / QuaternionLengthSq(in);
        }
        /**
        * @brief X����]�N�H�[�^�j�I�����쐬
        * @param[out] out ��]�N�H�[�^�j�I��
        * @param[in] rad ��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief Y����]�N�H�[�^�j�I�����쐬
        * @param[out] out ��]�N�H�[�^�j�I��
        * @param[in] rad ��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief Z����]�N�H�[�^�j�I�����쐬
        * @param[out] out ��]�N�H�[�^�j�I��
        * @param[in] rad ��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief XYZ��]�N�H�[�^�j�I�����쐬
        * @param[out] out ��]�N�H�[�^�j�I��
        * @param[in] sx x��]�p
        * @param[in] sy y��]�p
        * @param[in] sz z��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief ZXY��]�N�H�[�^�j�I�����쐬
        * @param[out] out ��]�N�H�[�^�j�I��
        * @param[in] sx x��]�p
        * @param[in] sy y��]�p
        * @param[in] sz z��]�p
        * @return �o�͌��ʂƓ���
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
        * @brief �C�ӂ̎��Ɖ�]�p����N�H�[�^�j�I�����쐬����
        * @param[out] out �N�H�[�^�j�I��
        * @param[in] axis �C�ӂ̎�
        * @param[in] rad ��]�p
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
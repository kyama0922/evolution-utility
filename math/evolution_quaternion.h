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

        class Quaternion :public float4
        {
        public:

            EVOLUTION_INLINE Quaternion(){}
            EVOLUTION_INLINE Quaternion(const Vector3& vec){ this->x = vec.x; this->y = vec.y; this->z = vec.z; this->w = 0.0f; }
            EVOLUTION_INLINE Quaternion(const Vector3& axis, f32 r){ this->SetR(axis, r); }
            EVOLUTION_INLINE Quaternion(float x, float y, float z, float w){ this->x = x; this->y = y; this->z = z; this->w = w; }
            EVOLUTION_INLINE Quaternion(const Quaternion& q){ this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; }
            //*****************************************************************************
            //		���Z�I�y���[�^
            //*****************************************************************************
            EVOLUTION_INLINE Quaternion operator + () const { return Quaternion(x, y, z, w); }
            EVOLUTION_INLINE Quaternion operator - () const { return Quaternion(-x, -y, -z, -w); }
            //*****************************************************************************
            //		Quaternion���Z�I�y���[�^
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
            //		float���Z�I�y���[�^
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
            //		������Z�I�y���[�^
            //*****************************************************************************
            EVOLUTION_INLINE Quaternion& operator=(const Vector3& val){ this->x = val.x; this->y = val.y; this->z = val.z; this->w = 0.0f; return *this; }
            EVOLUTION_INLINE Quaternion& operator=(const Quaternion& val){ this->x = val.x; this->y = val.y; this->z = val.z; this->w = val.w; return *this; }
            EVOLUTION_INLINE Quaternion& operator=(f32 val){ this->x = val; this->y = val; this->z = val; this->w = val; return *this; }
            //*****************************************************************************
            //		�֐�
            //*****************************************************************************
            //�N�H�[�^�j�I���Ƃ̓���
            EVOLUTION_INLINE f32 Dot(const Quaternion& val) const { return this->x*val.x + this->y*val.y + this->z*val.z + this->w*val.w; }
            //������2��v�Z
            EVOLUTION_INLINE f32 LengthSq() const { return Dot(*this); }
            //�����v�Z
            f32 Length() const;

            //���K��
            EVOLUTION_INLINE const Quaternion* Normalize()
            {
                f32 len = this->Length();
                if (len == 0.0f)return nullptr;
                *this /= len;
                return this;
            }
            // �P�ʉ�
            EVOLUTION_INLINE const Quaternion* Identity(){ this->x = this->y = this->z = 0.0f; this->w = 1.0f; return this; }
            //������
            EVOLUTION_INLINE const Quaternion* Conjugate(){ this->x = -this->x; this->y = -this->y; this->z = -this->z; return this; }
            //�����N�H�[�^�j�I�����쐬
            EVOLUTION_INLINE Quaternion CreateConjugate()const
            {
                Quaternion ret = *this;
                ret.x = -ret.x; ret.y = -ret.y; ret.z = -ret.z; ret.w = -ret.w;
                return ret;
            }

            //�t�������Ď��g�ɑ��
            EVOLUTION_INLINE const Quaternion* Inverse()
            {
                this->Conjugate();
                f32 lensq = this->LengthSq();
                //�����N�H�[�^�j�I���̒����̓�悪0�Ȃ�G���[
                assert(lensq != 0.0f);
                *this /= lensq;
                return this;
            }

            //�t���N�H�[�^�j�I�����쐬,�쐬�ł��Ȃ���΋����I������
            EVOLUTION_INLINE Quaternion CreateInverse()const
            {
                Quaternion ret = this->CreateConjugate();
                f32 lensq = this->LengthSq();
                //�����N�H�[�^�j�I���̒����̓�悪0�Ȃ�G���[
                assert(lensq != 0.0f);
                ret /= lensq;
                return ret;
            }

            //�N�H�[�^�j�I�����m�̍������ĐV�����N�H�[�^�j�I�����쐬����
            EVOLUTION_INLINE Quaternion Comp(const Quaternion& q){ return q*(*this); }

            //�N�H�[�^�j�I�����N�H�[�^�j�I���ŉ�]
            EVOLUTION_INLINE const Quaternion* Rotate(const Quaternion& q){ *this = q*(*this); return this; }

            //�N�H�[�^�j�I�����ʐ��`��Ԃ��Ď��g�ɑ������
            const Quaternion* SLerp(const Quaternion& q, f32 t);
            //*****************************************************************************
            //		��������֘A
            //*****************************************************************************

            //�I�C���[�p����X����]�N�H�[�^�j�I���쐬
            const Quaternion* SetRX(f32 rad);
            //�I�C���[�p����Y����]�N�H�[�^�j�I���쐬
            const Quaternion* SetRY(f32 rad);
            //�I�C���[�p����Z����]�N�H�[�^�j�I���쐬
            const Quaternion* SetRZ(f32 rad);
            //�I�C���[�p����N�H�[�^�j�I�����쐬����(XYZ�I�[�_�[)
            const Quaternion* SetRXYZ(f32 sx, f32 sy, f32 sz);
            //�I�C���[�p����N�H�[�^�j�I�����쐬����(XYZ�I�[�_�[)
            EVOLUTION_INLINE const Quaternion* SetRXYZ(const Vector3& angle){ return this->SetRXYZ(angle.x, angle.y, angle.z); }
            //�I�C���[�p����N�H�[�^�j�I�����쐬����(ZXY�I�[�_�[)
            const Quaternion* SetRZXY(f32 sx, f32 sy, f32 sz);
            //�I�C���[�p����N�H�[�^�j�I�����쐬����(ZXY�I�[�_�[)
            EVOLUTION_INLINE const Quaternion* SetRZXY(const Vector3& angle){ return this->SetRZXY(angle.x, angle.y, angle.z); }
            //�C�ӂ̎��Ɖ�]�p����N�H�[�^�j�I�����쐬����
            const Quaternion* SetR(const Vector3 &axis, f32 rad);
            //*****************************************************************************
            //		�����擾�֘A
            //*****************************************************************************

            //�N�H�[�^�j�I���̎��Ɖ�]�p�ɕ�������
            void Decompose(Vector3* axis, f32* rad) const;
            //�N�H�[�^�j�I�����p���x�N�g���ɕ�������
            void Decompose(Vector3* right, Vector3* up, Vector3* front) const;

            //*****************************************************************************
            //		�ϊ��֘A
            //*****************************************************************************

            //�s��ɕϊ�����
            const Matrix* ToMatrix(Matrix* out)const;
            //�s��ɕϊ�����
            Matrix ToMatrix()const;
            //XYZ�I�[�_�[�I�C���[�p�ɕϊ�����
            const Vector3* ToEulerXYZ(Vector3* out)const;
            //ZXY�I�[�_�[�I�C���[�p�ɕϊ�����(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
            const Vector3* ToEulerZXY(Vector3* out)const;
        };
    }
}

#endif // !__EVOLUTION_QUATERNION_H__

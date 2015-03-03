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
            //		���Z�I�y���[�^
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator + () const { return Vector3(x, y, z); }
            EVOLUTION_INLINE Vector3 operator - () const { return Vector3(-x, -y, -z); }
            //*****************************************************************************
            //		float���Z�I�y���[�^
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
            //		VECTOR2���Z�I�y���[�^
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator+(const Vector2& val)const{ return Vector3(this->x + val.x, this->y + val.y, this->z); }
            EVOLUTION_INLINE Vector3 operator-(const Vector2& val)const{ return Vector3(this->x - val.x, this->y - val.y, this->z); }
            EVOLUTION_INLINE Vector3& operator+=(const Vector2& val){ this->x += val.x; this->y += val.y; return *this; }
            EVOLUTION_INLINE Vector3& operator-=(const Vector2& val){ this->x -= val.x; this->y -= val.y; return *this; }
            //*****************************************************************************
            //		Vector3���Z�I�y���[�^
            //*****************************************************************************
            EVOLUTION_INLINE Vector3 operator+(const Vector3& val)const{ return Vector3(this->x + val.x, this->y + val.y, this->z + val.z); }
            EVOLUTION_INLINE Vector3 operator-(const Vector3& val)const{ return Vector3(this->x - val.x, this->y - val.y, this->z - val.z); }
            EVOLUTION_INLINE Vector3 operator/(const Vector3& val)const{ return Vector3(this->x / val.x, this->y / val.y, this->z / val.z); }
            EVOLUTION_INLINE Vector3& operator+=(const Vector3& val){ this->x += val.x; this->y += val.y; this->z += val.z; return *this; }
            EVOLUTION_INLINE Vector3& operator-=(const Vector3& val){ this->x -= val.x; this->y -= val.y; this->z -= val.z; return *this; }
            //*****************************************************************************
            //		������Z�I�y���[�^
            //*****************************************************************************
            Vector3& operator=(const Vector2& val);
            EVOLUTION_INLINE Vector3& operator=(const Vector3& val){ this->x = val.x; this->y = val.y; this->z = val.z; return *this; }
            Vector3& operator=(const Vector4& val);
            Vector3& operator=(const Quaternion& val);
            //*****************************************************************************
            //		�֐�
            //*****************************************************************************

            //�x�N�g�����m�̓���
            EVOLUTION_INLINE f32 Dot(const Vector3& val)const { return this->x*val.x + this->y*val.y + this->z*val.z; }
            //�x�N�g�����m�̓���
            static EVOLUTION_INLINE f32 Dot(const Vector3& val1, const Vector3& val2){ return val1.x*val2.x + val1.y*val2.y + val1.z*val2.z; }
            //�x�N�g�����m�̊O�ς����߂�
            const Vector3* Cross(Vector3* out, const Vector3& in)const;
            //�x�N�g�����m�̊O�ς����߂�
            static Vector3 Cross(const Vector3& a, const Vector3& b);
            //�x�N�g�����m�̊O�ς����߂�
            static void Cross(Vector3& out, const Vector3& a, const Vector3& b);
            //�x�N�g���Ԃ̊p�x�����߂�
            f32 Degree(const Vector3& in)const;
            //�x�N�g���̒����̓������߂�
            EVOLUTION_INLINE f32 LengthSq()const{ return Dot(*this); }
            //�x�N�g���̒��������߂�
            f32 Length()const;
            //�x�N�g�����m�̋����̓������߂�
            f32 DistanceSq(const Vector3& vec)const;
            //�x�N�g�����m�̋��������߂�
            f32 Distance(const Vector3& vec)const;
            //�x�N�g���𐳋K������
            const Vector3* Normalize();
            //�x�N�g�����m�̐��`��Ԃ����g�ɑ������
            const Vector3* Lerp(const Vector3& from, const Vector3& dest, f32 t);
            //�x�N�g�����m�̋��ʐ��`��Ԃ����g�ɑ������
            const Vector3* SLerp(const Vector3& from, const Vector3& dest, f32 t);
            //�x�N�g�����N�H�[�^�j�I���ŉ�]�����Ď��g�ɑ������
            const Vector3* Rotate(const Quaternion& q);
            // �x�N�g����C�ӂ̎��Ɗp�x�ŉ�]�����Ď��g�ɑ������
            const Vector3* Rotate(const Vector3& axis, f32 r);
            // �x�N�g����(x, y, z, 1)�Ƃ��čs��ϊ����Ď��g�ɑ������
            const Vector3* Trans(const Matrix& m);
            //�x�N�g����(x,y,z,0)�Ƃ��čs��ϊ����Ď��g�ɑ������
            const Vector3* Trans3x3(const Matrix& m);
            //���˃x�N�g�����i�[����
            const Vector3* Reflect(const Vector3& front, const Vector3& normal);
            //���܃x�N�g�����i�[����
            const Vector3* Refract(const Vector3& front, const Vector3& normal, f32 Eta);
            //�ˉe�x�N�g�����i�[����
            const Vector3* Projection(const Vector3& from, const Vector3& dest);
            //*****************************************************************************
            //		��������֘A
            //*****************************************************************************

            //�x�N�g�����m�̊O�ς����߂��㎩�g�ɑ������
            const Vector3* SetCross(const Vector3& in);
            //�p�ƕ��ʊp����x�N�g�������߂�
            const Vector3* SetR(f32 pitch, f32 yaw);
            //�x�N�g����C�ӂ̒����ɂ���
            const Vector3* SetLength(f32 len);
            //*****************************************************************************
            //		�ϊ��֘A
            //*****************************************************************************

            //�x�N�g�����p�ƕ��ʊp�ɕϊ�����
            const Vector3* ToEuler(Vector3* out)const;
        };
    }
}

#endif // !__EVOLUTION_VECTOR3_H__

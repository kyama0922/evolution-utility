#ifndef __EVOLUTION_VECTOR2_H__
#define __EVOLUTION_VECTOR2_H__

#include <evolution_type.h>

namespace EVOLUTION{

    namespace MATH{
        class Vector3;
        class Vector4;
        class Quaternion;
        class Matrix;

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
            //		���Z�I�y���[�^
            //*****************************************************************************

            EVOLUTION_INLINE Vector2 operator + () const { return Vector2(x, y); }
            EVOLUTION_INLINE Vector2 operator - () const { return Vector2(-x, -y); }
            //*****************************************************************************
            //		float���Z�I�y���[�^
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
            //		VECTOR2���Z�I�y���[�^
            //*****************************************************************************

            EVOLUTION_INLINE Vector2 operator+(const Vector2& val)const{ return Vector2(this->x + val.x, this->y + val.y); }
            EVOLUTION_INLINE Vector2 operator-(const Vector2& val)const{ return Vector2(this->x - val.x, this->y - val.y); }
            EVOLUTION_INLINE Vector2& operator+=(const Vector2& val){ this->x += val.x; this->y += val.y; return *this; }
            EVOLUTION_INLINE Vector2& operator-=(const Vector2& val){ this->x -= val.x; this->y -= val.y; return *this; }
            //*****************************************************************************
            //		������Z�I�y���[�^
            //*****************************************************************************
            EVOLUTION_INLINE Vector2& operator=(const Vector2& val){ this->x = val.x; this->y = val.y; return *this; }
            Vector2& operator=(const Vector3& val);
            Vector2& operator=(const Vector4& val);
            //*****************************************************************************
            //		�֐�
            //*****************************************************************************
            
            //�x�N�g���̓��ς����߂�
            EVOLUTION_INLINE f32 Dot(const Vector2& vec)const{ return this->x*vec.x + this->y*vec.y; }
            //�x�N�g���̊O�ς����߂�
            EVOLUTION_INLINE f32 Cross(const Vector2& vec)const{ return this->x*vec.y - vec.x*this->y; }
           //�x�N�g���Ԃ̊p�x�����߂�
            f32 Degree(const Vector2& vec)const;
            //�x�N�g���̒����̓������߂�
            EVOLUTION_INLINE f32 LengthSq()const{ return Dot(*this); }
            //�x�N�g���̒��������߂�
            f32 Length()const;
            //�x�N�g���̋����̓������߂�
            f32 DistanceSq(const Vector2& vec)const;
            //�x�N�g���̋��������߂�
            f32 Distance(const Vector2& vec)const;
            //�x�N�g���𐳋K��
            const Vector2* Normalize();
            //�x�N�g������`��Ԃ����g�Ɋi�[
            const Vector2* Lerp(const Vector2& from, const Vector2& dest, f32 t);
            //�ˉe�x�N�g�������߂Ď��g�ɑ��
            const Vector2* Projection(const Vector2& from, const Vector2& dest);
            //*****************************************************************************
            //		��������֘A
            //*****************************************************************************
            
            //�p�x����x�N�g�����쐬����
            const Vector2* SetR(f32 rad);
            //�x�N�g����C�ӂ̒����ɂ���
            const Vector2* SetLength(f32 len);
            //*****************************************************************************
            //		�ϊ��֘A
            //*****************************************************************************
            
            //�x�N�g�����p�x�ɕϊ�����
            f32 ToEuler()const;
        };
    }
}

#endif // !__EVOLUTION_VECTOR2_H__

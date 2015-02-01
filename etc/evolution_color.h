#ifndef __EVOLUTION_COLOR_H__
#define __EVOLUTION_COLOR_H__

#include "../math/evolution_math.h"

namespace EVOLUTION{
    namespace UTILITY{

        typedef struct{
            union {
                f32 m[4];
                struct {
                    f32  r, g, b, a;
                };
            };
        }RGBA4;

        typedef struct{
            union {
                f32 m[4];
                struct {
                    f32  a, r, g, b;
                };
            };
        }ARGB4;

        class Color :public RGBA4
        {
        public:
            EVOLUTION_INLINE Color(){}
            EVOLUTION_INLINE Color(u32 rgba){ this->r = (f32)((rgba & 0xFF000000) >> 24) / 255.0f; this->g = (f32)((rgba & 0x00FF0000) >> 16) / 255.0f; this->b = (f32)((rgba & 0x0000FF00) >> 8) / 255.0f; this->a = (f32)(rgba & 0x000000FF) / 255.0f; }
            EVOLUTION_INLINE Color(f32 r, f32 g, f32 b, f32 a){ this->r = r; this->g = g; this->b = b; this->a = a; }
            EVOLUTION_INLINE Color(const EVOLUTION::MATH::Vector2& val){ *this = val; this->m[2] = this->m[3] = 0.0f; }
            EVOLUTION_INLINE Color(const EVOLUTION::MATH::Vector3& val){ *this = val; this->m[3] = 0.0f; }
            EVOLUTION_INLINE Color(const EVOLUTION::MATH::Vector4& val){ *this = val; }
            EVOLUTION_INLINE Color(const EVOLUTION::MATH::Quaternion& val){ *this = val; }
            //*****************************************************************************
            //		演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Color operator + () const { return EVOLUTION::MATH::Vector4(this->m[0], this->m[1], this->m[2], this->m[3]); }
            EVOLUTION_INLINE Color operator - () const { return EVOLUTION::MATH::Vector4(-this->m[0], -this->m[1], -this->m[2], -this->m[3]); }
            //*****************************************************************************
            //		float演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Color operator+(f32 val)const{ return EVOLUTION::MATH::Vector4(this->m[0] + val, this->m[1] + val, this->m[2] + val, this->m[3] + val); }
            EVOLUTION_INLINE Color operator-(f32 val)const{ return EVOLUTION::MATH::Vector4(this->m[0] - val, this->m[1] - val, this->m[2] - val, this->m[3] - val); }
            EVOLUTION_INLINE Color operator*(f32 val)const{ return EVOLUTION::MATH::Vector4(this->m[0] * val, this->m[1] * val, this->m[2] * val, this->m[3] * val); }
            EVOLUTION_INLINE Color operator/(f32 val)const{ return EVOLUTION::MATH::Vector4(this->m[0] / val, this->m[1] / val, this->m[2] / val, this->m[3] / val); }
            EVOLUTION_INLINE Color& operator+=(f32 val){ this->m[0] += val; this->m[1] += val; this->m[2] += val; this->m[3] += val; return *this; }
            EVOLUTION_INLINE Color& operator-=(f32 val){ this->m[0] -= val; this->m[1] -= val; this->m[2] -= val; this->m[3] -= val; return *this; }
            EVOLUTION_INLINE Color& operator*=(f32 val){ this->m[0] *= val; this->m[1] *= val; this->m[2] *= val; this->m[3] *= val; return *this; }
            EVOLUTION_INLINE Color& operator/=(f32 val){ this->m[0] /= val; this->m[1] /= val; this->m[2] /= val; this->m[3] /= val; return *this; }
            //*****************************************************************************
            //		代入演算オペレータ
            //*****************************************************************************
            EVOLUTION_INLINE Color& operator=(const EVOLUTION::MATH::Vector2& val){ this->m[0] = val.x; this->m[1] = val.y; return *this; }
            EVOLUTION_INLINE Color& operator=(const EVOLUTION::MATH::Vector3& val){ this->m[0] = val.x; this->m[1] = val.y; this->m[2] = val.z; return *this; }
            EVOLUTION_INLINE Color& operator=(const EVOLUTION::MATH::Vector4& val){ this->m[0] = val.x; this->m[1] = val.y; this->m[2] = val.z; this->m[3] = val.w; return *this; }
            Color& operator=(const EVOLUTION::MATH::Quaternion& val);
            //*****************************************************************************
            //		関数
            //*****************************************************************************

            EVOLUTION_INLINE f32 LengthSq()const{
                return this->r * this->r + this->g * this->g + this->b * this->b + this->a * this->a;
            }
            EVOLUTION_INLINE f32 Length()const{
                return this->LengthSq();
            }
            //カラーを正規化する
            EVOLUTION_INLINE const Color* Normalize(){
                f32 len = this->Length();
                if (len == 0.0f)return nullptr;
                *this /= len;
                return this;
            }

            EVOLUTION_INLINE static Color RGBA(u32 rgba){ return Color((f32)((rgba & 0xFF000000) >> 24) / 255.0f, (f32)((rgba & 0x00FF0000) >> 16) / 255.0f, (f32)((rgba & 0x0000FF00) >> 8) / 255.0f, (f32)(rgba & 0x000000FF) / 255.0f); }
            EVOLUTION_INLINE static Color ARGB(u32 argb){ return Color((f32)((argb & 0x00FF0000) >> 16) / 255.0f, (f32)((argb & 0x0000FF00) >> 8) / 255.0f, (f32)(argb & 0x000000FF) / 255.0f, (f32)((argb & 0xFF000000) >> 24) / 255.0f); }

            const f32* GetColorFloat4()const{ return &this->r; }
        };
    }
}

#endif // !__EVOLUTION_COLOR_H__

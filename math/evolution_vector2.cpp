#include "evolution_math_utility.h"
#include "evolution_vector2.h"
using namespace EVOLUTION;
using namespace EVOLUTION::MATH;


//--------------------------------------------------------------------------------------------------
//
//		Vector2
//
//--------------------------------------------------------------------------------------------------

//*****************************************************************************
//		代入演算オペレータ
//*****************************************************************************
Vector2& Vector2::operator=(const Vector3& val){ this->x = val.x; this->y = val.y; return *this; }
Vector2& Vector2::operator=(const Vector4& val){ this->x = val.x; this->y = val.y; return *this; }
//*****************************************************************************
//		関数
//*****************************************************************************
f32 Vector2::Degree(const Vector2& vec)const{ return Vector2Degree(*this, vec); }
f32 Vector2::Length()const{ return Vector2Length(*this); }
f32 Vector2::DistanceSq(const Vector2& vec)const{ return Vector2DistanceSq(*this, vec); }
f32 Vector2::Distance(const Vector2& vec)const{ return Vector2Distance(*this, vec); }
const Vector2* Vector2::Normalize(){ return Vector2Normalize(this, *this); }
const Vector2* Vector2::Lerp(const Vector2& from, const Vector2& dest, f32 t){ return Vector2Lerp(this, from, dest, t); }
const Vector2* Vector2::Projection(const Vector2& from, const Vector2& dest){ return Vector2Projection(this, from, dest); }
//*****************************************************************************
//		成分操作関連
//*****************************************************************************
const Vector2* Vector2::SetR(f32 rad){ return Vector2fromEuler(this, rad); }
const Vector2* Vector2::SetLength(f32 len){ return Vector2SetLength(this, *this, len); }
//*****************************************************************************
//		変換関連
//*****************************************************************************
f32 Vector2::ToEuler()const{ return Vector2toEuler(*this); }



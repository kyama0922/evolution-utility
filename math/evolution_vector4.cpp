#include "evolution_math_utility.h"
#include "evolution_vector4.h"
using namespace EVOLUTION;
using namespace EVOLUTION::MATH;
//--------------------------------------------------------------------------------------------------
//
//		VECTOR4
//
//--------------------------------------------------------------------------------------------------
//*****************************************************************************
//		代入演算オペレータ
//*****************************************************************************
Vector4& Vector4::operator=(const Vector2& val){ this->x = val.x; this->y = val.y; return *this; }
Vector4& Vector4::operator=(const Vector3& val){ this->x = val.x; this->y = val.y; this->z = val.z; return *this; }
Vector4& Vector4::operator=(const Vector4& val){ this->x = val.x; this->y = val.y; this->z = val.z; this->w = val.w; return *this; }
Vector4& Vector4::operator=(const Quaternion& val){ this->x = val.x; this->y = val.y; this->z = val.z; this->w = val.w; return *this; }


//*****************************************************************************
//		関数
//*****************************************************************************
f32 Vector4::Length()const{ return Vector4Length(*this); }
const Vector4* Vector4::Normalize(){ return Vector4Normalize(this, *this); }
const Vector4* Vector4::Lerp(const Vector4& from, const Vector4& dest, f32 t){ return Vector4Lerp(this, from, dest, t); }
const Vector4* Vector4::Trans(const Matrix& m){ return MatrixVec4Transform(this, *this, m); }




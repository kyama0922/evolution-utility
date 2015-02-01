#include "evolution_math_utility.h"
#include "evolution_vector3.h"
using namespace EVOLUTION;
using namespace EVOLUTION::MATH;
//--------------------------------------------------------------------------------------------------
//
//		Vector3
//
//--------------------------------------------------------------------------------------------------
//*****************************************************************************
//		代入演算オペレータ
//*****************************************************************************
Vector3& Vector3::operator=(const Vector2& val){ this->x = val.x; this->y = val.y; return *this; }
Vector3& Vector3::operator=(const Vector4& val){ this->x = val.x; this->y = val.y; this->z = val.z; return *this; }
Vector3& Vector3::operator=(const Quaternion& val){ this->x = val.x; this->y = val.y; this->z = val.z; return *this; }
//*****************************************************************************
//		関数
//*****************************************************************************
const Vector3* Vector3::Cross(Vector3* out, const Vector3& in) const { return Vector3Cross(out, *this, in); }
Vector3 Vector3::Cross(const Vector3& a, const Vector3& b){ Vector3 out; return *Vector3Cross(&out, a, b); }
void Vector3::Cross(Vector3& out, const Vector3& a, const Vector3& b){ Vector3Cross(&out, a, b); }
f32 Vector3::Degree(const Vector3& in) const { return Vector3Degree(*this, in); }
f32 Vector3::Length()const{ return Vector3Length(*this); }
f32 Vector3::DistanceSq(const Vector3& vec)const{ return Vector3DistanceSq(*this, vec); }
f32 Vector3::Distance(const Vector3& vec)const{ return Vector3Distance(*this, vec); }
const Vector3* Vector3::Normalize(){ return Vector3Normalize(this, *this); }
const Vector3* Vector3::Lerp(const Vector3& from, const Vector3& dest, f32 t) { return Vector3Lerp(this, from, dest, t); }
const Vector3* Vector3::SLerp(const Vector3& from, const Vector3& dest, f32 t) { return Vector3Slerp(this, from, dest, t); }
const Vector3* Vector3::Rotate(const Quaternion& q){ return QuaternionVec3Rotation(this, q); }
const Vector3* Vector3::Rotate(const Vector3& axis, f32 r)
{
    Quaternion rot(axis, r);
    return QuaternionVec3Rotation(this, rot);
}
const Vector3* Vector3::Trans(const Matrix& m){ return MatrixVec3TransformCoord(this, *this, m); }
const Vector3* Vector3::Trans3x3(const Matrix& m){ return MatrixVec3TransformNormal(this, *this, m); }
const Vector3* Vector3::Reflect(const Vector3& front, const Vector3& normal){ return Vector3Reflect(this, front, normal); }
const Vector3* Vector3::Refract(const Vector3& front, const Vector3& normal, f32 Eta){ return Vector3Refract(this, front, normal, Eta); }
const Vector3* Vector3::Projection(const Vector3& from, const Vector3& dest){ return Vector3Projection(this, from, dest); }
//*****************************************************************************
//		成分操作関連
//*****************************************************************************
const Vector3* Vector3::SetCross(const Vector3& in){ return Vector3Cross(this, *this, in); }
const Vector3* Vector3::SetR(f32 pitch, f32 yaw){ return Vector3fromPitchYaw(this, pitch, yaw); }
const Vector3* Vector3::SetLength(f32 len){ return Vector3SetLength(this, *this, len); }
//*****************************************************************************
//		変換関連
//*****************************************************************************
const Vector3* Vector3::ToEuler(Vector3* out)const{ return Vector3toEuler(out, *this); }

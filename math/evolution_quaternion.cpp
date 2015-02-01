#include "evolution_math_utility.h"
#include "evolution_quaternion.h"
using namespace EVOLUTION;
using namespace EVOLUTION::MATH;
//--------------------------------------------------------------------------------------------------
//
//		Quaternion
//
//--------------------------------------------------------------------------------------------------
//*****************************************************************************
//		関数
//*****************************************************************************
float Quaternion::Length() const { return sqrtf(this->LengthSq()); }
const Quaternion* Quaternion::SLerp(const Quaternion& q, f32 t)
{
    return QuaternionSlerp(this, *this, q, t);
}
//*****************************************************************************
//		成分操作関連
//*****************************************************************************
//オイラー角からX軸回転クォータニオン作成
const Quaternion* Quaternion::SetRX(f32 rad)
{
    return QuaternionRotationX(this, rad);
}
//オイラー角からY軸回転クォータニオン作成
const Quaternion* Quaternion::SetRY(f32 rad)
{
    return QuaternionRotationY(this, rad);
}
//オイラー角からZ軸回転クォータニオン作成
const Quaternion* Quaternion::SetRZ(f32 rad)
{
    return QuaternionRotationZ(this, rad);
}
//オイラー角からクォータニオンを作成する(XYZオーダー)
const Quaternion* Quaternion::SetRXYZ(f32 sx, f32 sy, f32 sz)
{
    return QuaternionRotationXYZ(this, Vector3(sx, sy, sz));
}
//オイラー角からクォータニオンを作成する(ZXYオーダー)
const Quaternion* Quaternion::SetRZXY(f32 sx, f32 sy, f32 sz)
{
    return QuaternionRotationZXY(this, Vector3(sx, sy, sz));
}
//任意の軸と回転角からクォータニオンを作成する
const Quaternion* Quaternion::SetR(const Vector3 &axis, f32 rad){
    return QuaternionAxisRotation(this, axis, rad);
}
//*****************************************************************************
//		成分取得関連
//*****************************************************************************
//クォータニオンの軸と回転角に分解する
void Quaternion::Decompose(Vector3* axis, f32* rad) const {
    QuaternionDecompose(axis, rad, *this);
}
//クォータニオンを姿勢ベクトルに分解する
void Quaternion::Decompose(Vector3* right, Vector3* up, Vector3* front) const {
    QuaternionDecompose(right, up, front, *this);
}
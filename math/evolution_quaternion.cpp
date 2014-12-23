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
//		�֐�
//*****************************************************************************
float Quaternion::Length() const { return sqrtf(this->LengthSq()); }
const Quaternion* Quaternion::SLerp(const Quaternion& q, f32 t)
{
    return QuaternionSlerp(this, *this, q, t);
}
//*****************************************************************************
//		��������֘A
//*****************************************************************************
//�I�C���[�p����X����]�N�H�[�^�j�I���쐬
const Quaternion* Quaternion::SetRX(f32 rad)
{
    return QuaternionRotationX(this, rad);
}
//�I�C���[�p����Y����]�N�H�[�^�j�I���쐬
const Quaternion* Quaternion::SetRY(f32 rad)
{
    return QuaternionRotationY(this, rad);
}
//�I�C���[�p����Z����]�N�H�[�^�j�I���쐬
const Quaternion* Quaternion::SetRZ(f32 rad)
{
    return QuaternionRotationZ(this, rad);
}
//�I�C���[�p����N�H�[�^�j�I�����쐬����(XYZ�I�[�_�[)
const Quaternion* Quaternion::SetRXYZ(f32 sx, f32 sy, f32 sz)
{
    return QuaternionRotationXYZ(this, Vector3(sx, sy, sz));
}
//�I�C���[�p����N�H�[�^�j�I�����쐬����(ZXY�I�[�_�[)
const Quaternion* Quaternion::SetRZXY(f32 sx, f32 sy, f32 sz)
{
    return QuaternionRotationZXY(this, Vector3(sx, sy, sz));
}
//�C�ӂ̎��Ɖ�]�p����N�H�[�^�j�I�����쐬����
const Quaternion* Quaternion::SetR(const Vector3 &axis, f32 rad){
    return QuaternionAxisRotation(this, axis, rad);
}
//*****************************************************************************
//		�����擾�֘A
//*****************************************************************************
//�N�H�[�^�j�I���̎��Ɖ�]�p�ɕ�������
void Quaternion::Decompose(Vector3* axis, f32* rad) const {
    QuaternionDecompose(axis, rad, *this);
}
//�N�H�[�^�j�I�����p���x�N�g���ɕ�������
void Quaternion::Decompose(Vector3* right, Vector3* up, Vector3* front) const {
    QuaternionDecompose(right, up, front, *this);
}
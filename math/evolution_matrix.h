#ifndef __EVOLUTION_MATRIX_H__
#define __EVOLUTION_MATRIX_H__

#include <evolution_type.h>

namespace EVOLUTION{

    namespace MATH{

        class Vector2;
        class Vector3;
        class Vector4;
        class Quaternion;

#if defined(WIN32) | defined(WIN64)
        __declspec(align(64))
#endif
        typedef struct{
            union {
                f32	m[4][4];
                f32	m16[16];
                struct {
                    f32  _11, _12, _13, _14;
                    f32  _21, _22, _23, _24;
                    f32  _31, _32, _33, _34;
                    f32  _41, _42, _43, _44;
                };
            };
        }MatrixFloat16;
        
        class Matrix :public MatrixFloat16
        {
        public:
            /**
            * @brief �R���X�g���N�^
            */
            Matrix();
            Matrix(
                f32 m11, f32 m12, f32 m13, f32 m14,
                f32 m21, f32 m22, f32 m23, f32 m24,
                f32 m31, f32 m32, f32 m33, f32 m34,
                f32 m41, f32 m42, f32 m43, f32 m44
                );
            EVOLUTION_INLINE operator f32*(){ return (f32*)m; }
            EVOLUTION_INLINE operator const f32*()const{ return (const f32*)m; }
            /**
            * @brief *���Z�q
            * @param[in] mat �|����s��
            */
            EVOLUTION_INLINE Matrix operator*(const Matrix& mat)const
            {
                Matrix ref;
                ref._11 = this->_11 * mat._11 + this->_12 * mat._21 + this->_13 * mat._31 + this->_14 * mat._41;
                ref._12 = this->_11 * mat._12 + this->_12 * mat._22 + this->_13 * mat._32 + this->_14 * mat._42;
                ref._13 = this->_11 * mat._13 + this->_12 * mat._23 + this->_13 * mat._33 + this->_14 * mat._43;
                ref._14 = this->_11 * mat._14 + this->_12 * mat._24 + this->_13 * mat._34 + this->_14 * mat._44;

                ref._21 = this->_21 * mat._11 + this->_22 * mat._21 + this->_23 * mat._31 + this->_24 * mat._41;
                ref._22 = this->_21 * mat._12 + this->_22 * mat._22 + this->_23 * mat._32 + this->_24 * mat._42;
                ref._23 = this->_21 * mat._13 + this->_22 * mat._23 + this->_23 * mat._33 + this->_24 * mat._43;
                ref._24 = this->_21 * mat._14 + this->_22 * mat._24 + this->_23 * mat._34 + this->_24 * mat._44;

                ref._31 = this->_31 * mat._11 + this->_32 * mat._21 + this->_33 * mat._31 + this->_34 * mat._41;
                ref._32 = this->_31 * mat._12 + this->_32 * mat._22 + this->_33 * mat._32 + this->_34 * mat._42;
                ref._33 = this->_31 * mat._13 + this->_32 * mat._23 + this->_33 * mat._33 + this->_34 * mat._43;
                ref._34 = this->_31 * mat._14 + this->_32 * mat._24 + this->_33 * mat._34 + this->_34 * mat._44;

                ref._41 = this->_41 * mat._11 + this->_42 * mat._21 + this->_43 * mat._31 + this->_44 * mat._41;
                ref._42 = this->_41 * mat._12 + this->_42 * mat._22 + this->_43 * mat._32 + this->_44 * mat._42;
                ref._43 = this->_41 * mat._13 + this->_42 * mat._23 + this->_43 * mat._33 + this->_44 * mat._43;
                ref._44 = this->_41 * mat._14 + this->_42 * mat._24 + this->_43 * mat._34 + this->_44 * mat._44;
                return ref;
            }

            /**
            * @brief *���Z�q
            * @param[in] val
            * @param[in] mat �|����s��
            */
            EVOLUTION_INLINE Matrix operator*(f32& val)const
            {
                Matrix ref;
                ref._11 = this->_11 * val;
                ref._12 = this->_12 * val;
                ref._13 = this->_13 * val;
                ref._14 = this->_14 * val;

                ref._21 = this->_21 * val;
                ref._22 = this->_22 * val;
                ref._23 = this->_23 * val;
                ref._24 = this->_24 * val;

                ref._31 = this->_31 * val;
                ref._32 = this->_32 * val;
                ref._33 = this->_33 * val;
                ref._34 = this->_34 * val;

                ref._41 = this->_41 * val;
                ref._42 = this->_42 * val;
                ref._43 = this->_43 * val;
                ref._44 = this->_44 * val;
                return ref;
            }
            /**
            * @brief *=���Z�q
            * @param[in] mat �|����s��
            */
            EVOLUTION_INLINE Matrix& operator*=(const Matrix& mat)
            {
                Matrix work;
                work._11 = this->_11 * mat._11 + this->_12 * mat._21 + this->_13 * mat._31 + this->_14 * mat._41;
                work._12 = this->_11 * mat._12 + this->_12 * mat._22 + this->_13 * mat._32 + this->_14 * mat._42;
                work._13 = this->_11 * mat._13 + this->_12 * mat._23 + this->_13 * mat._33 + this->_14 * mat._43;
                work._14 = this->_11 * mat._14 + this->_12 * mat._24 + this->_13 * mat._34 + this->_14 * mat._44;

                work._21 = this->_21 * mat._11 + this->_22 * mat._21 + this->_23 * mat._31 + this->_24 * mat._41;
                work._22 = this->_21 * mat._12 + this->_22 * mat._22 + this->_23 * mat._32 + this->_24 * mat._42;
                work._23 = this->_21 * mat._13 + this->_22 * mat._23 + this->_23 * mat._33 + this->_24 * mat._43;
                work._24 = this->_21 * mat._14 + this->_22 * mat._24 + this->_23 * mat._34 + this->_24 * mat._44;

                work._31 = this->_31 * mat._11 + this->_32 * mat._21 + this->_33 * mat._31 + this->_34 * mat._41;
                work._32 = this->_31 * mat._12 + this->_32 * mat._22 + this->_33 * mat._32 + this->_34 * mat._42;
                work._33 = this->_31 * mat._13 + this->_32 * mat._23 + this->_33 * mat._33 + this->_34 * mat._43;
                work._34 = this->_31 * mat._14 + this->_32 * mat._24 + this->_33 * mat._34 + this->_34 * mat._44;

                work._41 = this->_41 * mat._11 + this->_42 * mat._21 + this->_43 * mat._31 + this->_44 * mat._41;
                work._42 = this->_41 * mat._12 + this->_42 * mat._22 + this->_43 * mat._32 + this->_44 * mat._42;
                work._43 = this->_41 * mat._13 + this->_42 * mat._23 + this->_43 * mat._33 + this->_44 * mat._43;
                work._44 = this->_41 * mat._14 + this->_42 * mat._24 + this->_43 * mat._34 + this->_44 * mat._44;

                *this = work;
                return *this;
            }
            /**
            * @brief �P�ʍs��
            * @return this
            */
            const Matrix* Identity();
            /**
            * @brief �t�s��
            * @return this
            */
            const Matrix* Inverse();
            /**
            * @brief ���K��
            * �e�������𐳋K������
            * @return this
            */
            const Matrix* Normalize();
            /**
            * @brief �s��]�u
            * @return this
            */
            EVOLUTION_INLINE const Matrix* Transpose()
            {
                Matrix work = *this;
                for (int i = 0; i<4; i++)for (int j = 0; j<4; j++)this->m[j][i] = work.m[i][j];
                return this;
            }
            /**
            * @brief �s�񎮂�����
            * @return �s��
            */
            f32 Determinant()const;
            //*****************************************************************************
            //		��������֘A
            //*****************************************************************************
            /**
            * @brief ���s�ړ�������������
            * @param[in] x x�ړ�����
            * @param[in] y y�ړ�����
            * @param[in] z z�ړ�����
            * @return this
            */
            const Matrix* SetT(f32 x, f32 y, f32 z);
            /**
            * @brief ���s�ړ�������������
            * @param[in] pos �ړ�����
            * @return this
            */
            EVOLUTION_INLINE const Matrix* SetT(const Vector3& pos){ return this->SetT(pos.x, pos.y, pos.z); }
            /**
            * @brief ��]������������(XYZ�I�[�_�[)
            * @param[in] x x�p����
            * @param[in] y y�p����
            * @param[in] z z�p����
            * @return this
            */
            const Matrix* SetRXYZ(f32 x, f32 y, f32 z);
            /**
            * @brief ��]������������(XYZ�I�[�_�[)
            * @param[in] angle �I�C���[�p����
            * @return this
            */
            EVOLUTION_INLINE const Matrix* SetRXYZ(const Vector3& angle){ return this->SetRXYZ(angle.x, angle.y, angle.z); }
            /**
            * @brief ��]������������(ZXY�I�[�_�[)
            * @param[in] x x�p����
            * @param[in] y y�p����
            * @param[in] z z�p����
            * @return this
            */
            const Matrix* SetRZXY(f32 x, f32 y, f32 z);
            /**
            * @brief ��]������������(ZXY�I�[�_�[)
            * @param[in] angle �I�C���[�p����
            * @return this
            */
            EVOLUTION_INLINE const Matrix* SetRZXY(const Vector3& angle){ return this->SetRZXY(angle.x, angle.y, angle.z); }
            /**
            * @brief �C�ӎ���]������������
            * @param[in] axis x�p����
            * @param[in] r ��]�p����
            * @return this
            */
            const Matrix* SetR(const Vector3& axis, f32 r);
            /**
            * @brief �N�H�[�^�j�I����]������������
            * @param[in] q �N�H�[�^�j�I��
            * @return this
            */
            const Matrix* SetR(const Quaternion& q);
            /**
            * @brief X����]������������
            * @param[in] r ��]�p
            * @return this
            */
            const Matrix* SetRX(f32 r);
            /**
            * @brief y����]������������
            * @param[in] r ��]�p
            * @return this
            */
            const Matrix* SetRY(f32 r);
            /**
            * @brief z����]������������
            * @param[in] r ��]�p
            * @return this
            */
            const Matrix* SetRZ(f32 r);
            /**
            * @brief �g�听������Z����
            * @param[in] x x�g�听��
            * @param[in] y y�g�听��
            * @param[in] z z�g�听��
            * @return this
            */
            EVOLUTION_INLINE const Matrix* MulS(f32 x, f32 y, f32 z)
            {
                _11 *= x;		_12 *= x;		_13 *= x;
                _21 *= y;		_22 *= y;		_23 *= y;
                _31 *= z;		_32 *= z;		_33 *= z;
                return this;
            }
            /**
            * @brief �g�听������Z����
            * @param[in] xyz �g�听��
            * @return this
            */
            EVOLUTION_INLINE const Matrix* MulS(f32 xyz)
            {
                _11 *= xyz;		_12 *= xyz;		_13 *= xyz;
                _21 *= xyz;		_22 *= xyz;		_23 *= xyz;
                _31 *= xyz;		_32 *= xyz;		_33 *= xyz;
                return this;
            }
            /**
            * @brief �g�听������Z����
            * @param[in] s �g�听��
            * @return this
            */
            EVOLUTION_INLINE const Matrix* MulS(const Vector3& s){ return MulS(s.x, s.y, s.z); }
            //*****************************************************************************
            //		�����擾�֘A
            //*****************************************************************************
            /**
            * @brief �s�������擾����
            * @param[in] index �擾����s�̃C���f�b�N�X
            * @param[out] out �s����
            * @return �o�͌��ʂƓ���
            */
            EVOLUTION_INLINE const Vector4* GetRow(s32 index, Vector4* out)const{ out->x = this->m[index][0]; out->y = this->m[index][1]; out->z = this->m[index][2]; out->w = this->m[index][3]; return out; }
            /**
            * @brief �񐬕����擾����
            * @param[in] index �擾�����̃C���f�b�N�X
            * @param[out] out �񐬕�
            * @return �o�͌��ʂƓ���
            */
            EVOLUTION_INLINE const Vector4* GetCol(s32 index, Vector4* out)const{ out->x = this->m[0][index]; out->y = this->m[1][index]; out->z = this->m[2][index]; out->w = this->m[3][index]; return out; }
            /**
            * @brief �s�������擾����
            * @param[in] index �擾����s�̃C���f�b�N�X
            * @param[out] out �s����
            * @return �o�͌��ʂƓ���
            */
            EVOLUTION_INLINE const Vector3* GetRow(s32 index, Vector3* out)const{ out->x = this->m[index][0]; out->y = this->m[index][1]; out->z = this->m[index][2]; return out; }
            /**
            * @brief �񐬕����擾����
            * @param[in] index �擾�����̃C���f�b�N�X
            * @param[out] out �񐬕�
            * @return �o�͌��ʂƓ���
            */
            EVOLUTION_INLINE const Vector3* GetCol(s32 index, Vector3* out)const{ out->x = this->m[0][index]; out->y = this->m[1][index]; out->z = this->m[2][index]; return out; }
            /**
            * @brief ���s�ړ��������擾����
            * @param[out] out �ړ�����
            * @return �o�͌��ʂƓ���
            */
            EVOLUTION_INLINE const Vector3* GetT(Vector3* out)const{ out->x = this->_41; out->y = this->_42; out->z = this->_43; return out; }
            /**
            * @brief ���s�ړ��������擾����
            * @return ���s�ړ�����
            */
            EVOLUTION_INLINE const Vector3 GetT()const{ return Vector3(this->_41, this->_42, this->_43); }
            /**
            * @brief �s��̐����𕪉�����
            * @param[out] s �g�听��
            * @param[out] q ��]�N�H�[�^�j�I������
            * @param[out] p �ړ�����
            */
            void Decompose(Vector3* s, Quaternion* q, Vector3* p)const;
            /**
            * @brief �s��̐������x�N�g���ɕ�������
            * @param[out] x �s���X������
            * @param[out] y �s���Y������
            * @param[out] z �s���Z������
            * @param[out] p �s��̈ʒu����
            */
            void Decompose(Vector3* x, Vector3* y, Vector3* z, Vector3* p)const;
            /**
            * @brief ��]�����݂̂��s��ɕ�������
            * 3x3�v�f�𐳋K�����Ĉʒu����0�ɂ������̂��o��
            * @param[out] m ��]�s��
            * @return �����̐���
            */
            const Matrix* DecomposeR(Matrix* m)const;
            /**
            * @brief ��]�����݂̂��N�H�[�^�j�I���ɕ�������
            * 3x3�v�f�𐳋K�����Ĉʒu����0�ɂ������̂��o��
            * @param[out] q ��]�N�H�[�^�j�I��
            * @return �����̐���
            */
            const Quaternion* DecomposeR(Quaternion* q)const;
            //*****************************************************************************
            //		�ϊ��֘A
            //*****************************************************************************
            /**
            * @brief �N�H�[�^�j�I���ɕϊ�����(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
            * @param[out] q ��]�N�H�[�^�j�I��
            * @return �o�͌��ʂƓ���
            */
            const Quaternion* ToQuaternion(Quaternion* q)const;
            /**
            * @brief �N�H�[�^�j�I���ɕϊ�����(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
            * @param[out] q ��]�N�H�[�^�j�I��
            * @return �o�͌��ʂƓ���
            */
            Quaternion ToQuaternion()const;

            /**
            * @brief XYZ�I�[�_�[�I�C���[�p�ɕϊ�����(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
            * @param[out] out �I�C���[�p
            * @return �o�͌��ʂƓ���
            */
            const Vector3* ToEulerXYZ(Vector3* out)const;
            /**
            * @brief ZXY�I�[�_�[�I�C���[�p�ɕϊ�����(�X�P�[�����O����Ă���ƈӐ}�������ʂɂȂ�Ȃ�)
            * @param[out] out �I�C���[�p
            * @return �o�͌��ʂƓ���
            */
            const Vector3* ToEulerZXY(Vector3* out)const;
        };

        /**
        * @brief ���[���h�s����쐬����
        */
        extern void MatrixWorld(Matrix& out, const Vector3 &pos, const Vector3 &angle, const Vector3 &scale);
        /**
        * @brief View�s����쐬����
        */
        extern void MatrixView(Matrix& out, const Vector3 &Eye, const Vector3 &At, const Vector3 &tmpUp);
        /**
        * @brief Projection�s����쐬����
        */
        extern void MatrixPerspective(Matrix& out, float forY, float aspect, float zn, float zf);
        /**
        * @brief ���s���e�s����쐬����
        */
        extern void MatrixOrthography(Matrix& out, float w, float h, float near, float far);
        /**
        * @brief �X�N���[�����W���烏�[���h���W�ɕϊ�����
        */
        extern void ScreenToWorld(Vector3& out_vec, int x, int y, int width, int heigth, const Matrix& view, const Matrix& projection);
    }
}

#endif // !__EVOLUTION_MATRIX_H__

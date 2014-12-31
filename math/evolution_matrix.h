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
            * @brief コンストラクタ
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
            * @brief *演算子
            * @param[in] mat 掛ける行列
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
            * @brief *演算子
            * @param[in] val
            * @param[in] mat 掛ける行列
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
            * @brief *=演算子
            * @param[in] mat 掛ける行列
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
            * @brief 単位行列化
            * @return this
            */
            const Matrix* Identity();
            /**
            * @brief 逆行列化
            * @return this
            */
            const Matrix* Inverse();
            /**
            * @brief 正規化
            * 各軸成分を正規化する
            * @return this
            */
            const Matrix* Normalize();
            /**
            * @brief 行列転置
            * @return this
            */
            EVOLUTION_INLINE const Matrix* Transpose()
            {
                Matrix work = *this;
                for (int i = 0; i<4; i++)for (int j = 0; j<4; j++)this->m[j][i] = work.m[i][j];
                return this;
            }
            /**
            * @brief 行列式を解く
            * @return 行列式
            */
            f32 Determinant()const;
            //*****************************************************************************
            //		成分操作関連
            //*****************************************************************************
            /**
            * @brief 平行移動成分を代入する
            * @param[in] x x移動成分
            * @param[in] y y移動成分
            * @param[in] z z移動成分
            * @return this
            */
            const Matrix* SetT(f32 x, f32 y, f32 z);
            /**
            * @brief 平行移動成分を代入する
            * @param[in] pos 移動成分
            * @return this
            */
            EVOLUTION_INLINE const Matrix* SetT(const Vector3& pos){ return this->SetT(pos.x, pos.y, pos.z); }
            /**
            * @brief 回転成分を代入する(XYZオーダー)
            * @param[in] x x角成分
            * @param[in] y y角成分
            * @param[in] z z角成分
            * @return this
            */
            const Matrix* SetRXYZ(f32 x, f32 y, f32 z);
            /**
            * @brief 回転成分を代入する(XYZオーダー)
            * @param[in] angle オイラー角成分
            * @return this
            */
            EVOLUTION_INLINE const Matrix* SetRXYZ(const Vector3& angle){ return this->SetRXYZ(angle.x, angle.y, angle.z); }
            /**
            * @brief 回転成分を代入する(ZXYオーダー)
            * @param[in] x x角成分
            * @param[in] y y角成分
            * @param[in] z z角成分
            * @return this
            */
            const Matrix* SetRZXY(f32 x, f32 y, f32 z);
            /**
            * @brief 回転成分を代入する(ZXYオーダー)
            * @param[in] angle オイラー角成分
            * @return this
            */
            EVOLUTION_INLINE const Matrix* SetRZXY(const Vector3& angle){ return this->SetRZXY(angle.x, angle.y, angle.z); }
            /**
            * @brief 任意軸回転成分を代入する
            * @param[in] axis x角成分
            * @param[in] r 回転角成分
            * @return this
            */
            const Matrix* SetR(const Vector3& axis, f32 r);
            /**
            * @brief クォータニオン回転成分を代入する
            * @param[in] q クォータニオン
            * @return this
            */
            const Matrix* SetR(const Quaternion& q);
            /**
            * @brief X軸回転成分を代入する
            * @param[in] r 回転角
            * @return this
            */
            const Matrix* SetRX(f32 r);
            /**
            * @brief y軸回転成分を代入する
            * @param[in] r 回転角
            * @return this
            */
            const Matrix* SetRY(f32 r);
            /**
            * @brief z軸回転成分を代入する
            * @param[in] r 回転角
            * @return this
            */
            const Matrix* SetRZ(f32 r);
            /**
            * @brief 拡大成分を乗算する
            * @param[in] x x拡大成分
            * @param[in] y y拡大成分
            * @param[in] z z拡大成分
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
            * @brief 拡大成分を乗算する
            * @param[in] xyz 拡大成分
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
            * @brief 拡大成分を乗算する
            * @param[in] s 拡大成分
            * @return this
            */
            EVOLUTION_INLINE const Matrix* MulS(const Vector3& s){ return MulS(s.x, s.y, s.z); }
            //*****************************************************************************
            //		成分取得関連
            //*****************************************************************************
            /**
            * @brief 行成分を取得する
            * @param[in] index 取得する行のインデックス
            * @param[out] out 行成分
            * @return 出力結果と同じ
            */
            EVOLUTION_INLINE const Vector4* GetRow(s32 index, Vector4* out)const{ out->x = this->m[index][0]; out->y = this->m[index][1]; out->z = this->m[index][2]; out->w = this->m[index][3]; return out; }
            /**
            * @brief 列成分を取得する
            * @param[in] index 取得する列のインデックス
            * @param[out] out 列成分
            * @return 出力結果と同じ
            */
            EVOLUTION_INLINE const Vector4* GetCol(s32 index, Vector4* out)const{ out->x = this->m[0][index]; out->y = this->m[1][index]; out->z = this->m[2][index]; out->w = this->m[3][index]; return out; }
            /**
            * @brief 行成分を取得する
            * @param[in] index 取得する行のインデックス
            * @param[out] out 行成分
            * @return 出力結果と同じ
            */
            EVOLUTION_INLINE const Vector3* GetRow(s32 index, Vector3* out)const{ out->x = this->m[index][0]; out->y = this->m[index][1]; out->z = this->m[index][2]; return out; }
            /**
            * @brief 列成分を取得する
            * @param[in] index 取得する列のインデックス
            * @param[out] out 列成分
            * @return 出力結果と同じ
            */
            EVOLUTION_INLINE const Vector3* GetCol(s32 index, Vector3* out)const{ out->x = this->m[0][index]; out->y = this->m[1][index]; out->z = this->m[2][index]; return out; }
            /**
            * @brief 平行移動成分を取得する
            * @param[out] out 移動成分
            * @return 出力結果と同じ
            */
            EVOLUTION_INLINE const Vector3* GetT(Vector3* out)const{ out->x = this->_41; out->y = this->_42; out->z = this->_43; return out; }
            /**
            * @brief 平行移動成分を取得する
            * @return 平行移動成分
            */
            EVOLUTION_INLINE const Vector3 GetT()const{ return Vector3(this->_41, this->_42, this->_43); }
            /**
            * @brief 行列の成分を分解する
            * @param[out] s 拡大成分
            * @param[out] q 回転クォータニオン成分
            * @param[out] p 移動成分
            */
            void Decompose(Vector3* s, Quaternion* q, Vector3* p)const;
            /**
            * @brief 行列の成分をベクトルに分解する
            * @param[out] x 行列のX軸成分
            * @param[out] y 行列のY軸成分
            * @param[out] z 行列のZ軸成分
            * @param[out] p 行列の位置成分
            */
            void Decompose(Vector3* x, Vector3* y, Vector3* z, Vector3* p)const;
            /**
            * @brief 回転成分のみを行列に分解する
            * 3x3要素を正規化して位置情報を0にしたものを出力
            * @param[out] m 回転行列
            * @return 分解の成功
            */
            const Matrix* DecomposeR(Matrix* m)const;
            /**
            * @brief 回転成分のみをクォータニオンに分解する
            * 3x3要素を正規化して位置情報を0にしたものを出力
            * @param[out] q 回転クォータニオン
            * @return 分解の成功
            */
            const Quaternion* DecomposeR(Quaternion* q)const;
            //*****************************************************************************
            //		変換関連
            //*****************************************************************************
            /**
            * @brief クォータニオンに変換する(スケーリングされていると意図した結果にならない)
            * @param[out] q 回転クォータニオン
            * @return 出力結果と同じ
            */
            const Quaternion* ToQuaternion(Quaternion* q)const;
            /**
            * @brief クォータニオンに変換する(スケーリングされていると意図した結果にならない)
            * @param[out] q 回転クォータニオン
            * @return 出力結果と同じ
            */
            Quaternion ToQuaternion()const;

            /**
            * @brief XYZオーダーオイラー角に変換する(スケーリングされていると意図した結果にならない)
            * @param[out] out オイラー角
            * @return 出力結果と同じ
            */
            const Vector3* ToEulerXYZ(Vector3* out)const;
            /**
            * @brief ZXYオーダーオイラー角に変換する(スケーリングされていると意図した結果にならない)
            * @param[out] out オイラー角
            * @return 出力結果と同じ
            */
            const Vector3* ToEulerZXY(Vector3* out)const;
        };

        /**
        * @brief ワールド行列を作成する
        */
        extern void MatrixWorld(Matrix& out, const Vector3 &pos, const Vector3 &angle, const Vector3 &scale);
        /**
        * @brief View行列を作成する
        */
        extern void MatrixView(Matrix& out, const Vector3 &Eye, const Vector3 &At, const Vector3 &tmpUp);
        /**
        * @brief Projection行列を作成する
        */
        extern void MatrixPerspective(Matrix& out, float forY, float aspect, float zn, float zf);
        /**
        * @brief 平行投影行列を作成する
        */
        extern void MatrixOrthography(Matrix& out, float w, float h, float near, float far);
        /**
        * @brief スクリーン座標からワールド座標に変換する
        */
        extern void ScreenToWorld(Vector3& out_vec, int x, int y, int width, int heigth, const Matrix& view, const Matrix& projection);
    }
}

#endif // !__EVOLUTION_MATRIX_H__

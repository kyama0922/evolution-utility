#include "evolution_math_utility.h"
#include "evolution_matrix.h"
using namespace EVOLUTION;
using namespace EVOLUTION::MATH;
//--------------------------------------------------------------------------------------------------
//
//		Matrix
//
//--------------------------------------------------------------------------------------------------
//コンストラクタ
Matrix::Matrix(){
    memset(&this->_11, 0, sizeof(Matrix));
}

Matrix::Matrix(
    f32 m11, f32 m12, f32 m13, f32 m14,
    f32 m21, f32 m22, f32 m23, f32 m24,
    f32 m31, f32 m32, f32 m33, f32 m34,
    f32 m41, f32 m42, f32 m43, f32 m44
    ){
    this->_11 = m11; this->_12 = m12; this->_13 = m13; this->_14 = m14;
    this->_21 = m21; this->_22 = m22; this->_23 = m23; this->_24 = m24;
    this->_31 = m31; this->_32 = m32; this->_33 = m33; this->_34 = m34;
    this->_41 = m41; this->_42 = m42; this->_43 = m43; this->_44 = m44;
}
//単位行列化
const Matrix* Matrix::Identity(){ MatrixIdentity(this); return this; }
//逆行列化
const Matrix* Matrix::Inverse(){ MatrixInverse(this, *this); return this; }
//正規化
const Matrix* Matrix::Normalize(){ return MatrixNormalize(this); }
//行列式取得
f32 Matrix::Determinant()const{ return MatrixDet(*this); }
//移動成分を代入する
const Matrix* Matrix::SetT(f32 x, f32 y, f32 z)
{
    this->m[3][0] = x;
    this->m[3][1] = y;
    this->m[3][2] = z;
    this->m[3][3] = 1.0f;
    return this;
}
//yaw pitch roll回転成分代入(XYZオーダー)
const Matrix* Matrix::SetRXYZ(f32 x, f32 y, f32 z)
{
    f32	sx, sy, sz, cx, cy, cz;

    sx = sinf(x);	sy = sinf(y);	sz = sinf(z);
    cx = cosf(x);	cy = cosf(y);	cz = cosf(z);

    this->_11 = (cy*cz);							this->_12 = (cy*sz);							this->_13 = (-sy);			this->_14 = (0.0f);
    this->_21 = (sx*sy*cz + (-cx*sz));		this->_22 = (sx*sy*sz + cx*cz);			this->_23 = (sx*cy);		this->_24 = (0.0f);
    this->_31 = (cx*sy*cz + sx*sz);			this->_32 = (cx*sy*sz + (-sx*cz));		this->_33 = (cx*cy);		this->_34 = (0.0f);
    return this;
}
//yaw pitch roll回転成分代入(ZXYオーダー)
const Matrix* Matrix::SetRZXY(f32 x, f32 y, f32 z)
{
    f32	sx, sy, sz, cx, cy, cz;

    sx = sinf(x);	sy = sinf(y);	sz = sinf(z);
    cx = cosf(x);	cy = cosf(y);	cz = cosf(z);

    this->_11 = (cz*cy + sz*sx*sy);		this->_12 = (sz*cx);		this->_13 = (-cz*sy + sz*sx*cy);	this->_14 = (0.0f);
    this->_21 = (-sz*cy + cz*sx*sy);	this->_22 = (cz*cx);		this->_23 = (sz*sy + cz*sx*cy);		this->_24 = (0.0f);
    this->_31 = (cx*sy);						this->_32 = (-sx);			this->_33 = (cx*cy);						this->_34 = (0.0f);
    return this;
}
//任意軸回転代入
const Matrix* Matrix::SetR(const Vector3& axis, f32 r)
{
    f32 s = sinf(r);
    f32 c = cosf(r);

    this->_11 = (axis.x*axis.x)*(1.0f - c) + c;					this->_12 = (axis.x*axis.y)*(1.0f - c) + axis.z*s;		this->_13 = (axis.z*axis.x)*(1.0f - c) - axis.y*s;		this->_14 = 0.0f;
    this->_21 = (axis.x*axis.y)*(1.0f - c) - axis.z*s;		this->_22 = (axis.y*axis.y)*(1.0f - c) + c;					this->_23 = (axis.y*axis.z)*(1.0f - c) + axis.x*s;		this->_24 = 0.0f;
    this->_31 = (axis.z*axis.x)*(1.0f - c) + axis.y*s;		this->_32 = (axis.y*axis.z)*(1.0f - c) - axis.x*s;		this->_33 = (axis.z*axis.z)*(1.0f - c) + c;					this->_34 = 0.0f;
    return this;
}
//クォータニオンから回転代入
const Matrix* Matrix::SetR(const Quaternion& q)
{
    return QuaternionToMatrix(this, q);
}
//X軸回転代入
const Matrix* Matrix::SetRX(f32 r)
{
    f32 s = sinf(r);
    f32 c = cosf(r);

    this->_11 = 1.0f;	this->_12 = 0.0f;		this->_13 = 0.0f;		this->_14 = 0.0f;
    this->_21 = 0.0f;	this->_22 = c;			this->_23 = s;			this->_24 = 0.0f;
    this->_31 = 0.0f;	this->_32 = -s;			this->_33 = c;			this->_34 = 0.0f;
    return this;
}
//Y軸回転代入
const Matrix* Matrix::SetRY(f32 r)
{
    f32 s = sinf(r);
    f32 c = cosf(r);

    this->_11 = c;			this->_12 = 0.0f;	this->_13 = -s;			this->_14 = 0.0f;
    this->_21 = 0.0f;		this->_22 = 1.0f;	this->_23 = 0;			this->_24 = 0.0f;
    this->_31 = s;			this->_32 = 0.0f;	this->_33 = c;			this->_34 = 0.0f;
    return this;
}
//Z軸回転代入
const Matrix* Matrix::SetRZ(f32 r)
{
    f32 s = sinf(r);
    f32 c = cosf(r);

    this->_11 = c;			this->_12 = s;			this->_13 = 0.0f;	this->_14 = 0.0f;
    this->_21 = -s;			this->_22 = c;			this->_23 = 0.0f;	this->_24 = 0.0f;
    this->_31 = 0.0f;		this->_32 = 0.0f;		this->_33 = 1.0f;	this->_34 = 0.0f;
    return this;
}


//*****************************************************************************
//		成分取得関連
//*****************************************************************************
//行列をスケール・回転・位置に分解
void Matrix::Decompose(Vector3* s, Quaternion* q, Vector3* p)const
{
    MatrixDecompose(s, q, p, *this);
}
//行列をベクトルに分解
void Matrix::Decompose(Vector3* x, Vector3* y, Vector3* z, Vector3* p)const
{
    MatrixDecompose(x, y, z, p, *this);
}
//回転成分を行列に分解
const Matrix* Matrix::DecomposeR(Matrix* m)const
{
    return MatrixDecomposeR(m, *this);
}
//回転成分をクォータニオンに分解
const Quaternion* Matrix::DecomposeR(Quaternion* q)const
{
    return MatrixDecomposeR(q, *this);
}


//*****************************************************************************
//		変換関連
//*****************************************************************************
//クォータニオン変換
Quaternion Matrix::ToQuaternion()const
{
    //クォータニオンに変換
    Quaternion q;
    MatrixToQuaternion(&q, *this);
    return q;
}
const Quaternion* Matrix::ToQuaternion(Quaternion* q)const
{
    //クォータニオンに変換
    return MatrixToQuaternion(q, *this);
}
//オイラー角変換
const Vector3* Matrix::ToEulerXYZ(Vector3* out)const
{
    return MatrixToEulerXYZ(out, *this);
}
//オイラー角変換
const Vector3* Matrix::ToEulerZXY(Vector3* out)const
{
    return MatrixToEulerZXY(out, *this);
}


void EVOLUTION::MATH::MatrixWorld(Matrix& out, const Vector3 &pos, const Vector3 &angle, const Vector3 &scale){
    out.SetR(angle);
    out.SetT(scale);
    out.MulS(scale);
}

void EVOLUTION::MATH::MatrixView(Matrix& out, const Vector3 &Eye, const Vector3 &At, const Vector3 &tmpUp){
    Vector3 front(At - Eye);
    Vector3 rite, up;
    Vector3::Cross(rite, tmpUp, front);
    Vector3::Cross(up, front, rite);
    front.Normalize();
    rite.Normalize();
    up.Normalize();

    float dotR = MATH::Vector3Dot(rite, Eye);
    float dotF = MATH::Vector3Dot(front, Eye);
    float dotU = MATH::Vector3Dot(up, Eye);

    out._11 = rite.x; out._12 = up.x; out._13 = front.x; out._14 = 0.0f;
    out._21 = rite.y; out._22 = up.y; out._23 = front.y; out._24 = 0.0f;
    out._31 = rite.z; out._32 = up.z; out._33 = front.z; out._34 = 0.0f;
    out._41 = -dotR; out._42 = -dotU; out._43 = -dotF; out._44 = 1.0f;
}

void EVOLUTION::MATH::MatrixPerspective(Matrix& out, float forY, float aspect, float zn, float zf){
    float yScale = 1 / MATH::tanf(forY / 2);
    float xScale = yScale / aspect;

    out._11 = xScale; out._12 = 0.0f;  out._13 = 0.0f;				out._14 = 0.0f;
    out._21 = 0.0f; out._22 = yScale; out._23 = 0.0f;				out._24 = 0.0f;
    out._31 = 0.0f; out._32 = 0.0f;  out._33 = zf / (zf - zn);	out._34 = 1.0f;
    out._41 = 0.0f; out._42 = 0.0f;  out._43 = -zn * zf / (zf - zn);	out._44 = 0.0f;
}

void EVOLUTION::MATH::MatrixOrthography(Matrix& out, float w, float h, float near, float far){

    out._11 = 2 / w;	out._12 = 0.0f;		out._13 = 0.0f;					out._14 = 0.0f;
    out._21 = 0.0f;		out._22 = 2 / h;	out._23 = 0.0f;					out._24 = 0.0f;
    out._31 = 0.0f;		out._32 = 0.0f;		out._33 = 1 / (far - near);	out._34 = 0.0f;
    out._41 = 0;		out._42 = 0;		out._43 = near / (near - far);	out._44 = 1.0f;
}



void EVOLUTION::MATH::ScreenToWorld(Vector3& out_vec, int x, int y, int width, int heigth, const Matrix& view, const Matrix& projection){

    Matrix inv_view, inv_prj, vp, inv_viewport;

    MATH::MatrixInverse(&inv_view, view);
    MATH::MatrixInverse(&inv_prj, projection);
    MATH::MatrixIdentity(&vp);

    vp._11 = width / 2.0f; vp._22 = -heigth / 2.0f;
    vp._41 = width / 2.0f; vp._42 = heigth / 2.0f;

    MATH::MatrixInverse(&inv_viewport, vp);
    //// 逆変換
    Matrix work = inv_viewport * inv_prj * inv_view;

    Vector3 screen;
    screen.x = (float)x;
    screen.y = (float)y;
    screen.z = 0.0f;

    Vector4 tmp1, tmp2;
    MATH::MatrixVec3Transform(&tmp1, screen, work);

    tmp1.x /= tmp1.w;
    tmp1.y /= tmp1.w;
    tmp1.z /= tmp1.w;

    screen.z = 1.0f;
    MATH::MatrixVec3Transform(&tmp2, screen, work);

    tmp2.x /= tmp2.w;
    tmp2.y /= tmp2.w;
    tmp2.z /= tmp2.w;

    out_vec = tmp2 - tmp1;
}
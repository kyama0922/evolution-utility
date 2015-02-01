#include "evolution_math.h"

using namespace EVOLUTION;
using namespace EVOLUTION::MATH;


//*****************************************************************************
//		変換関連
//*****************************************************************************
//クォータニオン変換
const Matrix* Quaternion::ToMatrix(Matrix* out)const
{
    //クォータニオンに変換
    return QuaternionToMatrix(out, *this);
}
Matrix Quaternion::ToMatrix()const{
    Matrix tmp;
    QuaternionToMatrix(&tmp, *this);
    return tmp;
}
//オイラー角変換
const Vector3* Quaternion::ToEulerXYZ(Vector3* out)const
{
    return QuaternionToEulerXYZ(out, *this);
}
//オイラー角変換
const Vector3* Quaternion::ToEulerZXY(Vector3* out)const
{
    return QuaternionToEulerZXY(out, *this);
}


//*****************************************************************************
//		変換関連
//*****************************************************************************
void MatrixWorld(Matrix& out, const Vector3 &pos, const Vector3 &angle, const Vector3 &scale){
    out.Identity();
    out.SetR(angle);
    out.SetT(scale);
    out.MulS(scale);
}

void MatrixView(Matrix& out, const Vector3 &Eye, const Vector3 &At, const Vector3 &tmpUp){
    Vector3 front(At - Eye);
    Vector3 rite, up;
    Vector3::Cross(rite, tmpUp, front);
    Vector3::Cross(up, front, rite);
    front.Normalize();
    rite.Normalize();
    up.Normalize();

    float dotR = Vector3::Dot(rite, Eye);
    float dotF = Vector3::Dot(front, Eye);
    float dotU = Vector3::Dot(up, Eye);

    out._11 = rite.x; out._12 = up.x; out._13 = front.x; out._14 = 0.0f;
    out._21 = rite.y; out._22 = up.y; out._23 = front.y; out._24 = 0.0f;
    out._31 = rite.z; out._32 = up.z; out._33 = front.z; out._34 = 0.0f;
    out._41 = -dotR; out._42 = -dotU; out._43 = -dotF; out._44 = 1.0f;
}

void MatrixPerspective(Matrix& out, float forY, float aspect, float zn, float zf){
    float yScale = 1 / EVOLUTION::MATH::tanf(forY / 2);
    float xScale = yScale / aspect;

    out._11 = xScale; out._12 = 0.0f;  out._13 = 0.0f;				out._14 = 0.0f;
    out._21 = 0.0f; out._22 = yScale; out._23 = 0.0f;				out._24 = 0.0f;
    out._31 = 0.0f; out._32 = 0.0f;  out._33 = zf / (zf - zn);	out._34 = 1.0f;
    out._41 = 0.0f; out._42 = 0.0f;  out._43 = -zn * zf / (zf - zn);	out._44 = 0.0f;
}

void MatrixOrthography(Matrix& out, float w, float h, float near, float far){

    out._11 = 2 / w;	out._12 = 0.0f;		out._13 = 0.0f;					out._14 = 0.0f;
    out._21 = 0.0f;		out._22 = 2 / h;	out._23 = 0.0f;					out._24 = 0.0f;
    out._31 = 0.0f;		out._32 = 0.0f;		out._33 = 1 / (far - near);	out._34 = 0.0f;
    out._41 = 0;		out._42 = 0;		out._43 = near / (near - far);	out._44 = 1.0f;
}



void ScreenToWorld(Vector3& out_vec, int x, int y, int width, int heigth, const Matrix& view, const Matrix& projection){

    Matrix inv_view, inv_prj, vp, inv_viewport;

    MatrixInverse(&inv_view, view);
    MatrixInverse(&inv_prj, projection);
    MatrixIdentity(&vp);

    vp._11 = width / 2.0f; vp._22 = -heigth / 2.0f;
    vp._41 = width / 2.0f; vp._42 = heigth / 2.0f;

    MatrixInverse(&inv_viewport, vp);
    //// 逆変換
    Matrix work = inv_viewport * inv_prj * inv_view;

    Vector3 screen;
    screen.x = (float)x;
    screen.y = (float)y;
    screen.z = 0.0f;

    Vector4 tmp1, tmp2;
    MatrixVec3Transform(&tmp1, screen, work);

    tmp1.x /= tmp1.w;
    tmp1.y /= tmp1.w;
    tmp1.z /= tmp1.w;

    screen.z = 1.0f;
    MatrixVec3Transform(&tmp2, screen, work);

    tmp2.x /= tmp2.w;
    tmp2.y /= tmp2.w;
    tmp2.z /= tmp2.w;

    out_vec = tmp2 - tmp1;
}
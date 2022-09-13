// Dag Nylund 31/1/18 - 1/2/18
// gsml fra 5/11/20
#include "../Matrix4x4/Matrix4x4.h"

#include <iomanip>
#include <cmath>

namespace gsml {

using std::fixed;
using std::right;
using std::setw;
using std::setprecision;
#define debug 0


const float Matrix4x4::EPS = 0.000001;

Matrix4x4::Matrix4x4() : m(4), n(4), lu_faktorisert(false)
{
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            A[i][j] = 0.0f;
}

void Matrix4x4::setToIdentity()
{
    if (m == n) {
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            A[i][j] = 0.0f;
    for (int i=0; i<m; i++)
        A[i][i] = 1.0f;
    }
}
void Matrix4x4::read(std::string filnavn)
{
    std::ifstream inn(filnavn.c_str()); // Åpne eksisterende fil
    if (inn.is_open()) // Lese punkter - her: linje for linje
    {
        inn >> m >> n;
        // Må kreve m=n=4
        for (int i=0; i<m; i++)
           for (int j=0; j<n; j++)
               inn >> A[i][j];
   }
   inn.close(); // Lukke fil
}

void Matrix4x4::print() const
{
    for (int i=0; i<m; i++)
    {
        //std::cout << setw(8) << setprecision(2)  << fixed << right;
        for (int j=0; j<n; j++)
            std::cout << setw(8) << setprecision(2)  << fixed << right << A[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix4x4::set(int i, int j, float x)
{
    A[i][j] = x;
}

void Matrix4x4::set(int j, Vector4d &v)
{
    for (int i=0; i<m; i++)
        A[i][j] = v[i];
}

void Matrix4x4::set_dim(int rader, int kolonner)
{
    m = rader; n = kolonner;
}

Dimension Matrix4x4::get_dim() const
{
    return Dimension(m, n);
}

// Det er ikke veldig elegant å skrive M.A[i][j]
// gjentatte ganger. Et alternativ er å overlaste
// en () operator for klassen
void Matrix4x4::operator =(const Matrix4x4 &M)
{
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            set(i, j, M.A[i][j]);
            //A[i][j] = M(i,j);
}

void Matrix4x4::mult(const Matrix4x4& M) // Hjelpefunksjon
{
    Matrix4x4 AA;
    //M.print();
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
           for(int k=0; k<4; k++)
                // multipliserer i-te rad i A
                // med j-te kolonne i B
                AA.A[i][j] += A[i][k]*M.A[k][j];
                //AA(i,j) += A[i][k]*M(k,j);
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            //set(i, j, AA.A[i][j]);
            A[i][j] = AA.A[i][j];
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& M) const
{
    Matrix4x4 AA;
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            for (int k=0; k<4; k++)
                // endre for andre enn 4x4 matriser
                // altså kontroller dimensjonene
                AA.A[i][j] += A[i][k]*M.A[k][j];
                //AA(i,j) += A[i][k]*M(k,j);
    return AA;
}
Vector4d Matrix4x4::operator * ( Vector4d& v) const
{
    Vector4d x;
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            x[i] += A[i][j]*v[j];
    return x;
}


void Matrix4x4::translate(float tx, float ty, float tz)
{
    // Lager translasjonssmatrise
    Matrix4x4 T;
    T.setToIdentity();
    T(0,3) = tx;
    T(1,3) = ty;
    T(2,3) = tz;

    // Translerer - multipliserer med translasjonsmatrisen
    mult(T);
}

// Rotasjon om (1,0,0), (0,1,0) eller (0,0,1)
// Rotasjon om vilkårlig akse er beskrevet i Angel 4.10.4
void Matrix4x4::rotate(float degrees, float rx, float ry, float rz)
{
    // Lager rotasjonsmatrise
    Matrix4x4 R;
    R.setToIdentity();

    float pi = 4*std::atan(1.0);
    float rad = degrees*pi/180;
    float a = std::cos(rad);
    float b = std::sin(rad);
// Her kan vi ha både 1 og -1 som rx ry rz
    if (rx==0.0f && ry==0.0f && rz==1.0f)
    {
        R(0,0) = a;
        R(1,0) = b;
        R(0,1) = -b;
        R(1,1) = a;
    }
    else if (rx==0.0f && ry==1.0f && rz==0.0f)
    {
        R(0,0) = a;
        R(2,0) = b;
        R(0,2) = -b;
        R(2,2) = a;
    }
    if (rx==1.0f && ry==0.0f && rz==0.0f)
    {
        R(1,1) = a;
        R(2,1) = b;
        R(1,2) = -b;
        R(2,2) = a;
    }
    // Roterer - multipliserer med rotasjonematrisen
    mult(R);
}

void Matrix4x4::scale(float sx, float sy, float sz)
{
    // Lager skaleringsmatrisen
    Matrix4x4 S;
    S.setToIdentity();
    S(0,0) = sx;
    S(1,1) = sy;
    S(2,2) = sz;
    // Skalerer - multipliserer med skaleringsmatrisen
    mult(S);
}
// Se Angel kapittel 5.7.2
void Matrix4x4::frustum(float left, float right, float bottom, float top, float near, float far)
{
    // Forutsetter a_ij initielt 0
    A[0][0] = 2*near/(right-left);
    A[1][1] = 2*near/(top-bottom);
    A[0][2] = (right+left)/(right-left);
    A[1][2] = (top+bottom)/(top-bottom);
    A[2][2] = -(far+near)/(far-near);
    A[2][3] = -2*far*near/(far-near);
    A[3][2] = -1.0f;
    A[3][3] = 0.0f;
    /*
    */
}
// Se Angel kapittel 5.7.2
void Matrix4x4::perspective(float fovy, float aspectRatio, float near, float far)
{
    float top = near*std::tan(fovy);
    float right = top/aspectRatio;
    A[0][0] = near/right;
    A[1][1] = near/top;
    A[2][2] = -(far+near)/(far-near);
    A[2][3] = -2*far*near/(far-near);
    A[3][2] = -1;
}
// Transformasjon fra xyz til uvn, se Angel(7th ed) 5.3.2
// up - orienteringen av kamera, trenger ikke ligge i viewplan
// u = v x n gir riktig retning i høyrehåndssystem.
// n er normal på viewplan, retning mot kamera (som z-aksen er default)
void Matrix4x4::lookAt(const Vector3d &eye, const Vector3d &at, const Vector3d &up)
{
    Matrix4x4 M;
    M.setToIdentity();
    Vector3d v = up;
    v.normalize();          // y-akse i kameraframe
    Vector3d n = eye-at;
    n.normalize();          // z-akse i kameraframe
    Vector3d u = v.cross(n);
    u.normalize();          // x-akse i kameraframe
    v = n.cross(u);
    v.normalize();
    M(0,0) = u.x;  M(0,1) = u.y;  M(0,2) = u.z;
    M(1,0) = v.x;  M(1,1) = v.y;  M(1,2) = v.z;
    M(2,0) = n.x;  M(2,1) = n.y;  M(2,2) = n.z;
    M.translate(-eye.x, -eye.y, -eye.z);
    //M.print();
    mult(M);
}
// internt er A M*N, så return &A[0][0];
// går ikke. Returner kolonnevis 4x4
const float *Matrix4x4::constData() const
{
    return &A[0][0];
}


}

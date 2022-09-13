// Nytt namespace navn gsml fra 5/11/20
// gs2019 ligger nederst
#include "vertex.h"
#include <iomanip>

namespace gsml {
Vertex::Vertex()
{

}
/*
Vertex::Vertex(const Vertex& v)
{
    for (int i=0; i<3; i++) m_xyz[i] = v.m_xyz[i];
    for (int i=0; i<3; i++) m_normal[i] = v.m_normal[i];
    for (int i=0; i<2; i++) m_st[i] = v.m_st[i];
}
*/
Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
    m_xyz[0] = x;
    m_xyz[1] = y;
    m_xyz[2] = z;
    m_normal[0] = r;
    m_normal[1] = g;
    m_normal[2] = b;
    m_st[0] = 0.0f;
    m_st[1] = 0.0f;
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float s, float t)
{
    m_xyz[0] = x;
    m_xyz[1] = y;
    m_xyz[2] = z;
    m_normal[0] = r;
    m_normal[1] = g;
    m_normal[2] = b;
    m_st[0] = s;
    m_st[1] = t;
}
Vertex::~Vertex()
{
    //qDebug() << "Vertex::~Vertex()";
}

//! \param xyz pointer to coordinate array
void Vertex::set_xyz(GLfloat* xyz)
{
    for (int i=0; i<3; i++) m_xyz[i] = xyz[i];
}

//! \param x, y, z coordinates
void Vertex::set_xyz(GLfloat x, GLfloat y, GLfloat z)
{
    m_xyz[0] = x; m_xyz[1] = y; m_xyz[2] = z;
}

//! \param rgb pointer to coordinate array
void Vertex::set_rgb(GLfloat* rgb)
{
    for (int i=0; i<3; i++) m_normal[i] = rgb[i];
}

//! The normal coordinate array is used for color values
//! \param r, g, b color values
void Vertex::set_rgb(GLfloat r, GLfloat g, GLfloat b)
{
    m_normal[0] = r; m_normal[1] = g; m_normal[2] = b;
}

void Vertex::set_normal(GLfloat* normal)
{
    for (int i=0; i<3; i++) m_normal[i] = normal[i];
}

void Vertex::set_normal(GLfloat x, GLfloat y, GLfloat z)
{
    m_normal[0] = x; m_normal[1] = y; m_normal[2] = z;
}

void Vertex::set_st(GLfloat* st)
{
    for (int i=0; i<2; i++) m_st[i] = st[i];
}

void Vertex::set_st(GLfloat s, GLfloat t)
{
    m_st[0] = s; m_st[1] = t;
}

void Vertex::set_uv(GLfloat u, GLfloat v)
{
    set_st(u,v);
}

std::ostream& operator<< (std::ostream& os, const Vertex& v)
{
    os << std::fixed << std::setprecision(2) << std::setw(10);

   os << "(" << v.m_xyz[0] << ", " << std::fixed << v.m_xyz[1] << ", " << v.m_xyz[2] << ") ";
   os << "(" << v.m_normal[0] << ", " << v.m_normal[1] << ", " << v.m_normal[2] << ") ";
   os << "(" << v.m_st[0] << ", " << v.m_st[1] << ") ";
   return os;
}
std::istream& operator>> (std::istream& is, Vertex& v)
{
// Trenger fire temporære variabler som kun skal lese inn parenteser og komma
   char dum, dum2, dum3, dum4;
   is >> dum >> v.m_xyz[0] >> dum2 >> v.m_xyz[1] >> dum3 >> v.m_xyz[2] >> dum4;
   is >> dum >> v.m_normal[0] >> dum2 >> v.m_normal[1] >> dum3 >> v.m_normal[2] >> dum4;
   is >> dum >> v.m_st[0] >> dum2 >> v.m_st[1] >> dum3;

   return is;
}

void Vertex::data(float v[]) const
{
    //return static_cast<float*>(*this);

    for (int i=0; i<3; i++) v[i] = m_xyz[i];
    for (int i=3; i<6; i++) v[i] = m_normal[i-3];
    for (int i=6; i<8; i++) v[i] = m_st[i-6];
}
gsml::Vector3d Vertex::getXYZ() const
{
    return gsml::Vector3d{m_xyz[0], m_xyz[1], m_xyz[2]};
}

void Vertex::operator =(const Vertex &v)
{
    for (int i=0; i<3; i++) {
        m_xyz[i] = v.m_xyz[i];
        m_normal[i] = v.m_normal[i];

    }
}

}

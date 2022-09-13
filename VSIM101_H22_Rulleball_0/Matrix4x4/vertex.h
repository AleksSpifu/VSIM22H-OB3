// Lager et nytt namespace gsml
// Bruker dette etter 5/11/20
#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <fstream>
#include <ostream>
#include "vector3d.h"
typedef float GLfloat;

//! \brief Vertex class for structures of Vertex data xyz_rgb_st
//!
//! The class Vertex defines vertex data for uploading through OpenGL API,
//! using array of structures as recommended.
//! The vertex coordinates, normal coordinates and texture coordinates are
//! stored in separate arrays. The array for normal coordinates can also be used
//! for color attributtes rgb.
//! Finally, the class implements overloading stream operators for easy file io.
//!
//! \author Dag Nylund
//! \date 15/04/15-20/09/19 - 5/11/20
//!

namespace gsml { // nytt navn 5/11/20
class Vertex
{
    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);

private:
     //GLfloat m_rgba[4];
    float m_xyz[3];       // position i 3D
    float m_normal[3];    // normal in 3D or rgb colors
    /// Lager en anonym union siden vi aldri trenger både rgba og normal
    /// Trenger riktignok heller ikke st når vi bruker rgba
    /*union {
        GLfloat m_rgba[4];
        GLfloat m_normal[3];
    };*/
    float m_st[2];        // texture coordiantes if used

public:
    Vertex();
    Vertex(float x, float y, float z, float r, float g, float b);
    Vertex(float x, float y, float z, float r, float g, float b, float s, float t);

    ~Vertex();
    void set_xyz(GLfloat* xyz);
    void set_xyz(GLfloat x, GLfloat y, GLfloat z);
    void set_rgb(GLfloat* rgb);
    void set_rgb(GLfloat r, GLfloat g, GLfloat b);
    void set_normal(GLfloat* normal);
    void set_normal(GLfloat x, GLfloat y, GLfloat z);
    void set_st(GLfloat* st);
    void set_st(GLfloat s, GLfloat t);
    void set_uv(GLfloat u, GLfloat v);
    void data(float v[]) const;
    gsml::Vector3d getXYZ() const;
    void operator = (const Vertex& v);
};
}


#endif // VERTEX_H

#include "octahedronball.h"
#include "matrix4x4\vertex.h"

//! - n is the recursion level (number of repeated subdivisions)
//!

OctahedronBall::OctahedronBall(int n) : m_rekursjoner(n), m_indeks(0), VisualObject()
{
   mVertices.reserve(3 * 8 * pow(4, m_rekursjoner));
   oktaederUnitBall();
}

//!//! \brief OctahedronBall::~OctahedronBall() virtual destructor
//!
OctahedronBall::~OctahedronBall()
{
   //
}

// Parametre inn: xyz koordinatene til et triangle v1, v2, v3 ccw
// Bevarer orienteringen av hjørnene
//!
//! \brief OctahedronBall::lagTriangel()
//! \param v1 - position on the unit ball for vertex 1
//! \param v2 - position on the unit ball for vertex 2
//! \param v3 - position on the unit ball for vertex 3
//!
//! lagTriangel() creates vertex data for a triangle's 3 vertices. This is done in the
//! final step of recursion.
//!
void OctahedronBall::lagTriangel(const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
   gsml::Vertex v{};

   v.set_xyz(v1.x, v1.y, v1.z);		// koordinater v.x = v1.x, v.y=v1.y, v.z=v1.z
   v.set_normal(v1.x, v1.y, v1.z);	// rgb
   v.set_st(0.0f, 0.0f);			// kan utelates
   mVertices.push_back(v);
   v.set_xyz(v2.x, v2.y, v2.z);
   v.set_normal(v2.x, v2.y, v2.z);
   v.set_st(1.0f, 0.0f);
   mVertices.push_back(v);
   v.set_xyz(v3.x, v3.y, v3.z);
   v.set_normal(v3.x, v3.y, v3.z);
   v.set_st(0.5f, 1.0f);
   mVertices.push_back(v);
}

// Rekursiv subdivisjon av triangel
//!
//! \brief OctahedronBall::subDivide() recursive subdivision of a triangel
//! \param a coordinates for vertex a
//! \param b coordinates for vertex b
//! \param c coordinates for vertex c
//! \param n level of recursion
//!
//! The function tests
//! (if n>0)
//! - three new edge midpoints are computed and normalized,
//! - four new calls to subDivide() is done - one for each new triangle, preserving orientation
//! and with decreased parameter n
//! else
//! - call lagTriangel(a, b, c)
//!
void OctahedronBall::subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n)
{
   if (n>0) {
       Vec3 v1 = a+b; v1.normalize();
       Vec3 v2 = a+c; v2.normalize();
       Vec3 v3 = c+b; v3.normalize();
       subDivide(a, v1, v2, n-1);
       subDivide(c, v2, v3, n-1);
       subDivide(b, v3, v1, n-1);
       subDivide(v3, v2, v1, n-1);
   } else {
       lagTriangel(a, b, c);
   }
}

//!
//! \brief OctahedronBall::oktaederUnitBall() creates 8 unit ball vertices and call subDivide()
//!
//! If the parameter n of the constructor OctahedronBall() is zero, the result will be the
//! original octahedron consisting of 8 triangles with duplicated vertices.
//!
void OctahedronBall::oktaederUnitBall()
{
   Vec3 v0{0, 0, 1};
   Vec3 v1{1, 0, 0};
   Vec3 v2{0, 1, 0};
   Vec3 v3{-1, 0, 0};
   Vec3 v4{0, -1, 0};
   Vec3 v5{0, 0, -1};

   subDivide(v0, v1, v2, m_rekursjoner);
   subDivide(v0, v2, v3, m_rekursjoner);
   subDivide(v0, v3, v4, m_rekursjoner);
   subDivide(v0, v4, v1, m_rekursjoner);
   subDivide(v5, v2, v1, m_rekursjoner);
   subDivide(v5, v3, v2, m_rekursjoner);
   subDivide(v5, v4, v3, m_rekursjoner);
   subDivide(v5, v1, v4, m_rekursjoner);
}

//!
//! \brief OctahedronBall::initVertexBufferObjects() calls glGenBuffers(), glBindBuffer() and glBufferdata()
//! for using later use of glDrawArrays()
//!
void OctahedronBall::init(GLint matrixUniform)
{
   mMatrixUniform = matrixUniform;
   initializeOpenGLFunctions();

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(gsml::Vertex), mVertices.data(), GL_STATIC_DRAW );

   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(gsml::Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(gsml::Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   glBindVertexArray(0);
}

//!
//! \brief OctahedronBall::draw() draws a ball using glDrawArrays()
//! \param positionAttribute    vertex shader variable for position
//! \param normalAttribute      vertex shader variable for normal or color
//! \param textureAttribute     vertex shader variable for texture coordinates (optional)
//!
//! draw()
//! - glBindBuffer()
//! - glVertexAttribPointer()
//! - glBindTexture()
//! - glVertexAttribPointer()
//! - glDrawArrays() with GL_TRIANGLES
//!
void OctahedronBall::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_TRUE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());//mVertices.size());
}


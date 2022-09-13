#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H
#include "visualobject.h"

class Vertex;
typedef gsml::Vector3d Vec3;
class OctahedronBall : public VisualObject {
private:
   int m_rekursjoner;
   int m_indeks;               // brukes i rekursjon, til å bygge m_vertices
   void lagTriangel(const Vec3& v1, const Vec3& v2, const Vec3& v3);
   void subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n);
   void oktaederUnitBall();
public:
   OctahedronBall(int n);
   ~OctahedronBall();
   void init(GLint matrixUniform);
   void draw();
};

#endif

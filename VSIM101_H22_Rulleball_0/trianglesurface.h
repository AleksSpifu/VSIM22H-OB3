#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include "visualobject.h"
#include "vector3d.h"
#include "triangle.h"

class TriangleSurface : public VisualObject
{
public:
    TriangleSurface();
    TriangleSurface(std::string filnavn);
    ~TriangleSurface() override;
    void readFile(std::string filnavn);
    void writeFile(std::string filnavn);
    void init(GLint matrixUniform) override;
    void draw() override;
    void construct();
    void construct_cylinder();
    void construct_plane();
    std::vector<gsml::Vertex>& get_vertices() { return mVertices; } // 191120
    Triangle GetTriangle(gsml::Vector3d location);
    bool isPointInTriangle(gsml::Vector3d pt, gsml::Vector3d v1, gsml::Vector3d v2, gsml::Vector3d v3);
    bool isCrossproductPositive(gsml::Vector3d pt, gsml::Vector3d v1, gsml::Vector3d v2, gsml::Vector3d v3);
};

#endif // TRIANGLESURFACE_H

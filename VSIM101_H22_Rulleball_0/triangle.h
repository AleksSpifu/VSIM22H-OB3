#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector3d.h"


struct Triangle {
    Triangle(gsml::Vector3d A, gsml::Vector3d B, gsml::Vector3d C) : a{A}, b{B}, c{C}
    {
        gsml::Vector3d v1 = b - a;
        gsml::Vector3d v2 = c - a;
        normal = v1.cross(v2);
        normal.normalize();

    }
    gsml::Vector3d a;
    gsml::Vector3d b;
    gsml::Vector3d c;
    gsml::Vector3d normal;
    bool valid{true};
};

#endif // TRIANGLE_H

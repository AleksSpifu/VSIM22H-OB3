#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "octahedronball.h"
#include "trianglesurface.h"

class RollingBall : public OctahedronBall
{
public:
    RollingBall(int n);
    ~RollingBall() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float dt) override;
    void setSurface(VisualObject* surface) { triangle_surface = surface; }
    gsml::Vector3d GetPosition();
protected:
    VisualObject* triangle_surface;
private:
    gsml::Vector3d old_normal{0.0, 0.0, 1.0};
    int old_index{0};
    std::vector<GLuint> mIndices;
    GLuint mIBO{0};
    gsml::Vector3d mAcceleration{0, 0, -98.1};
    gsml::Vector3d mVelocity{0, 0, 0};
};
#endif // ROLLINGBALL_H

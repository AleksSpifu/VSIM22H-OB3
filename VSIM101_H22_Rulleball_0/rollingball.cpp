#include "rollingball.h"
#include "triangle.h"
RollingBall::RollingBall(int n) : OctahedronBall (n)
{
    //mVelocity = gsml::Vector3d{1.0f, 1.0f, -0.05f};
    mPosition.translate(0,2.5,1.25);
    mScale.scale(0.25,0.25,0.25);

    for (GLuint i=0; i<mVertices.size(); i++) mIndices.push_back(i);
}
RollingBall::~RollingBall()
{

}

gsml::Vector3d RollingBall::GetPosition()
{
    return gsml::Vector3d{mPosition(0, 3), mPosition(1, 3), mPosition(2, 3)};
}

void RollingBall::move(float dt)
{
    gsml::Vector3d myPos = GetPosition();
    Triangle tri = dynamic_cast<TriangleSurface*>(triangle_surface)->GetTriangle(myPos);
    if (!tri.valid)
    {
        return;
    }
    gsml::Vector3d newVelocity = mVelocity + (mAcceleration * dt);
    gsml::Vector3d adjustedSpeed = newVelocity * dt;

    gsml::Vector3d slideAlongNormal = tri.normal * (adjustedSpeed*tri.normal);
    adjustedSpeed = adjustedSpeed - slideAlongNormal;

    mVelocity = mVelocity + adjustedSpeed;

    std::cout << adjustedSpeed.x << "\t" << adjustedSpeed.y << "\t" << adjustedSpeed.z << std::endl;

    mPosition.translate(adjustedSpeed.x, adjustedSpeed.y, adjustedSpeed.z);
    mMatrix = mPosition * mScale;

}

void RollingBall::init(GLint matrixUniform)
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

   glGenBuffers(1, &mIBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);


   glBindVertexArray(0);
}

void RollingBall::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_TRUE, mMatrix.constData());
   glDrawElements(GL_TRIANGLES, mVertices.size(), GL_UNSIGNED_INT, reinterpret_cast<const void*>(0));//mVertices.size());

}

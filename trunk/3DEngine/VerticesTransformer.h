#pragma once
#include "VerticesData.h"
#include "glm/glm.hpp"
class CVerticesTransformer
{
public:
    CVerticesTransformer(void);
    ~CVerticesTransformer(void);

    CVerticesData TransformVerticesData(CVerticesData& verticesData, glm::mat4 );
    void SetAspect(float fAspect);
    void SetEyeDirection(CWorldCoordinate eyeDir);
private:
    glm::mat4 m_perspectiveMat;
    glm::mat4 m_viewMat;
    CWorldCoordinate m_eyeDir;

    float m_fAspect;
};


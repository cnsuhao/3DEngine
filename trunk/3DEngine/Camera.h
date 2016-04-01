#pragma once
#include "glm/glm.hpp"
#include "Common.h"
class CCamera
{
public:
    CCamera(void);
    ~CCamera(void);
    glm::mat4 GetViewProjectionMat();
    void SetAspect(float fAspect);
    void MouseEvent(UINT msg, WPARAM wParam, LPARAM lParam);
    CWorldCoordinate GetDirection();
protected:
    float m_fPitchAngle;
    float m_fMinPitchAngle;
    float m_fMaxPitchAngle;
    float m_fYawAngle;
    float m_fDistanceToTarget;


    glm::mat4 m_perspectiveMat;
    float m_fAspect;

    POINT m_lastPoint;
};


#include "StdAfx.h"
#include <windowsx.h>
#include "glm/detail/func_common.hpp"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#define M_PI_180 0.01745329252

CCamera::CCamera(void)
    : m_fPitchAngle(0)
    , m_fMinPitchAngle(-80 * M_PI_180)
    , m_fMaxPitchAngle(80 * M_PI_180)
    , m_fYawAngle(90 * M_PI_180)
    , m_fDistanceToTarget(20)
{
}


CCamera::~CCamera(void)
{
}

glm::mat4 CCamera::GetViewProjectionMat()
{
    glm::vec3 vDir( cos(m_fYawAngle), -tan(m_fPitchAngle), -sin(m_fYawAngle) );
    glm::vec3 eyePos = -glm::normalize(vDir) * m_fDistanceToTarget;
    glm::mat4 viewMat = glm::lookAt(
        eyePos,
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
        );
    return m_perspectiveMat * viewMat;
}

void CCamera::SetAspect(float fAspect)
{
    m_fAspect = fAspect;
    m_perspectiveMat = glm::perspective(60.0f, m_fAspect, 0.1f, 100.0f);
}

inline POINT PointFromLPARAM(LPARAM lParam)
{
    POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    return pt;
}

void CCamera::MouseEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINT pt = PointFromLPARAM(lParam);
    switch(msg)
    {
    case WM_LBUTTONDOWN:
        m_lastPoint = pt;
        break;
    case WM_LBUTTONUP:
        m_lastPoint = pt;
        break;
    case WM_MOUSEMOVE:
        if ( (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 )
        {
            int nDeltaX = pt.x - m_lastPoint.x;
            int nDeltaY = pt.y - m_lastPoint.y;
            m_fYawAngle += nDeltaX * 0.5f * M_PI_180;
            m_fPitchAngle += nDeltaY * 0.2f * M_PI_180;
            m_fPitchAngle = glm::min(m_fPitchAngle, m_fMaxPitchAngle);
            m_fPitchAngle = glm::max(m_fPitchAngle, m_fMinPitchAngle);
            m_lastPoint = pt;
        }
        break;
    case WM_MOUSEWHEEL:
        {
            int zDelta = (short) HIWORD(wParam) / 120;
            int tLen = -zDelta + m_fDistanceToTarget;
            if (tLen > 2 && tLen < 20)
            {
                m_fDistanceToTarget = tLen;
            }
        }
        break;
    default:
        break;
    }
}

CWorldCoordinate CCamera::GetDirection()
{
    glm::vec3 vDir( cos(m_fYawAngle), -tan(m_fPitchAngle), -sin(m_fYawAngle) );
    glm::vec3 eyePos = -glm::normalize(vDir) * m_fDistanceToTarget;
    return -eyePos;
}

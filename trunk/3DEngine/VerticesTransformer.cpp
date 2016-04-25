#include "StdAfx.h"
#include "VerticesTransformer.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include "glm/gtx/string_cast.hpp"

CVerticesTransformer::CVerticesTransformer(void)
    : m_bLightEnabled(false)
{

}


CVerticesTransformer::~CVerticesTransformer(void)
{
}

inline CColor ComputeColor(const CColor& originalColor, const CColor& lightColor, float fAngle)
{
    if ( fAngle < 0 )
    {
        unsigned int tValue = (1.0+fAngle) * 100;
        tValue = glm::max(tValue, (unsigned int)50);
        CColor tColor(tValue, tValue, tValue);
        return tColor;
    }
    //fAngle *= 1.2f;
    int minValue = 100;
    CColor newColor;
    int nValue = lightColor.r * fAngle;
    nValue = glm::min(nValue, 255);
    nValue = glm::max(nValue, minValue);
    newColor.r = nValue;

    nValue = lightColor.g * fAngle;
    nValue = glm::min(nValue, 255);
    nValue = glm::max(nValue, minValue);
    newColor.g = nValue;

    nValue = lightColor.b * fAngle;
    nValue = glm::min(nValue, 255);
    nValue = glm::max(nValue, minValue);
    newColor.b = nValue;
    return newColor;
}

CVerticesData CVerticesTransformer::TransformVerticesData(CVerticesData& verticesData, glm::mat4 viewPerspectiveMat)
{
    // 变换位置
    CVerticesData transformedData;
    const std::vector<CWorldCoordinate>& posVec = verticesData.GetPosVec();
    std::vector<CWorldCoordinate> tPosVec;

    for (size_t i=0; i<posVec.size(); ++i)
    {
        glm::vec4 pos(posVec[i], 1);
        pos = viewPerspectiveMat * pos;
        pos /= pos.w;
        CWorldCoordinate tPos(pos);
        tPosVec.push_back(tPos);
    }
    transformedData.SetPosVec(tPosVec);

    // 变换法线
    const std::vector<glm::vec3>& normalVec = verticesData.GetNormalVec();
    //std::vector<glm::vec3> tNormalVec;
    //for (size_t i=0; i<normalVec.size(); ++i)
    //{
    //    glm::vec4 normal(normalVec[i], 0);
    //    normal = viewPerspectiveMat * normal;
    //    glm::vec3 tNormal(normal);
    //    tNormalVec.push_back(tNormal);
    //}
    //transformedData.SetNormalVec(tNormalVec);

    CWorldCoordinate lightDirection = glm::normalize( CWorldCoordinate(0.6f, 0.4f, 1.0f) );
    //CColor lightColor(255, 255, 255);

    // 计算光照
    const std::vector<CColor>& colorVec = verticesData.GetColorVec();
    std::vector<CColor> newColor;
    newColor.reserve( colorVec.size() );
    if (verticesData.GetPrimitiveType() == CVerticesData::PT_TRIANGLES && m_bLightEnabled)
    {
        for (size_t i=0; i<posVec.size(); )
        {
            size_t j = i;
            CWorldCoordinate averageNormal = normalVec[i++];
            averageNormal += normalVec[i++];
            averageNormal += normalVec[i++];

            averageNormal = glm::normalize(averageNormal);
            CColor originalColor(65, 65, 65);

            // 漫反射

            int ambient = 110;
            CColor tmpColor(ambient, ambient, ambient);
            originalColor += tmpColor;

            float fAngle = glm::dot(averageNormal, lightDirection);
            float lightValue = fAngle * 70;

            if ( fAngle > 0.0f )
            {
                // 镜面反射
                CColor lightColor(lightValue, lightValue, lightValue);
                originalColor += lightColor;
            }
            else
            {
                lightValue = -lightValue;
                CColor lightColor(lightValue, lightValue, lightValue);
                originalColor -= lightColor;
            }
            //float fAngle = glm::dot(averageNormal, lightDirection);
            //if ( fAngle > 0.0f )
            //{
            //    int ambient = fAngle * 150;
            //    CColor tmpColor(ambient, ambient, ambient);
            //    originalColor += tmpColor;

            //    // 镜面反射
            //    CWorldCoordinate R = 2.0f * averageNormal * lightDirection - lightDirection;
            //    float ffAngle = glm::dot( glm::normalize(-m_eyeDir), R );
            //    if (ffAngle > 0.0f)
            //    {
            //        int ambient = ffAngle * 100;
            //        CColor tmpColor(ambient, ambient, ambient);
            //        originalColor += tmpColor;
            //    }
            //}
            //else
            //{
            //    int ambient = fAngle * 10;
            //    CColor tmpColor(ambient, ambient, ambient);
            //    originalColor += tmpColor;
            //}
            newColor.push_back( originalColor );
            newColor.push_back( originalColor );
            newColor.push_back( originalColor );
        }
    }
    else
    {
        for (size_t i=0; i<posVec.size(); ++i)
        {
            newColor.push_back( CColor(255, 255, 255) );
        }
    }
    transformedData.SetColorVec( newColor );
    transformedData.SetPrimitiveType( verticesData.GetPrimitiveType() );

    const std::vector<CTexCoordinate>& texVec = verticesData.GetTexVec();
    transformedData.SetTexVec(texVec);
    return transformedData;
}

void CVerticesTransformer::SetAspect(float fAspect)
{
    m_fAspect = fAspect;
}

void CVerticesTransformer::SetEyeDirection(CWorldCoordinate eyeDir)
{
    m_eyeDir = glm::normalize(eyeDir);
}

void CVerticesTransformer::ChangeLightState()
{
    m_bLightEnabled ^= true;
}

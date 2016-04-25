#include "StdAfx.h"
#include "VerticesData.h"


CVerticesData::CVerticesData(void)
{
}


CVerticesData::~CVerticesData(void)
{
}

const std::vector<CWorldCoordinate>& CVerticesData::GetPosVec()
{
    return m_vPosVec;
}

const std::vector<glm::vec3>& CVerticesData::GetNormalVec()
{
    return m_vNormalVec;
}

void CVerticesData::SetPosVec(std::vector<CWorldCoordinate>& tData)
{
    m_vPosVec = tData;
}

CVerticesData::EnPrimitiveType CVerticesData::GetPrimitiveType()
{
    return m_ePrimitive;
}

void CVerticesData::SetPrimitiveType(EnPrimitiveType ePrimitive)
{
    m_ePrimitive = ePrimitive;
}

const std::vector<CColor>& CVerticesData::GetColorVec()
{
    return m_vColorVec;
}

const std::vector<glm::vec2>& CVerticesData::GetTexVec()
{
    return m_vTexVec;
}

void CVerticesData::SetNormalVec(std::vector<glm::vec3>& tData)
{
    m_vNormalVec = tData;
}

void CVerticesData::SetColorVec(const std::vector<CColor>& tData)
{
    m_vColorVec = tData;
}

void CVerticesData::SetTexVec(const std::vector<glm::vec2>& tData)
{
    m_vTexVec = tData;
}

void CVerticesData::ChangePrimitiveType()
{
    if (m_ePrimitive == PT_LINE_STRIP)
    {
        m_ePrimitive = PT_TRIANGLES;
    }
    else
    {
        m_ePrimitive = PT_LINE_STRIP;
    }
}

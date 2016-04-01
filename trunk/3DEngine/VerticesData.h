#pragma once
#include "glm/glm.hpp"
#include <vector>
#include "Common.h"

class CVerticesTransformer;
class CVerticesData
{
    friend class CVerticesTransformer;
public:
    enum EnPrimitiveType
    {
        PT_LINES,
        PT_TRIANGLES
    };
    CVerticesData(void);
    ~CVerticesData(void);

    void SetPosVec( std::vector<CWorldCoordinate>& tData);
    void SetNormalVec( std::vector<glm::vec3>& tData);
    void SetColorVec(const std::vector<CColor>& tData);
    void SetTexVec(const std::vector<glm::vec2>& tData);

    const std::vector<CWorldCoordinate>& GetPosVec();
    const std::vector<glm::vec3>& GetNormalVec();
    const std::vector<CColor>&    GetColorVec();
    const std::vector<glm::vec2>& GetTexVec();
    EnPrimitiveType GetPrimitiveType();
    void SetPrimitiveType(EnPrimitiveType ePrimitive);
protected:
    std::vector<CWorldCoordinate> m_vPosVec;
    std::vector<CColor>    m_vColorVec;
    std::vector<glm::vec3> m_vNormalVec;
    std::vector<glm::vec2> m_vTexVec;

    EnPrimitiveType m_ePrimitive;
};


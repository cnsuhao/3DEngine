#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "VerticesData.h"
#include "GeometryData.h"


class CAssembler
{
public:
    CAssembler(void);
    ~CAssembler(void);

    void SetVerticesData(CVerticesData* verticesData);

    bool GetNextGeometry(CGeometryData*& geometry);

    void SetViewportSize(unsigned int nWidth, unsigned int nHeight);

private:
    CWorldCoordinate ViewportTransform(const CWorldCoordinate& pt); 

    CVerticesData* m_pVerticesData;
    unsigned int m_nIndex;
    unsigned int m_nTotalNum;

    unsigned int m_uViewportWidht;
    unsigned int m_uViewportHeight;
};


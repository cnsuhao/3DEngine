#include "StdAfx.h"
#include "Assembler.h"


CAssembler::CAssembler(void)
    : m_nIndex(0)
    , m_nTotalNum(0)
{
}


CAssembler::~CAssembler(void)
{
}

void CAssembler::SetVerticesData(CVerticesData* verticesData)
{
    m_pVerticesData = verticesData;
    m_nTotalNum = verticesData->GetPosVec().size();
    //m_nTotalNum = 3;// 
    m_nIndex = 0;
}

bool CAssembler::GetNextGeometry(CGeometryData*& geometry)
{
    const std::vector<CWorldCoordinate>& vPos   = m_pVerticesData->GetPosVec();
    const std::vector<CColor>&    vColor        = m_pVerticesData->GetColorVec();
    const std::vector<glm::vec2>& vTex          = m_pVerticesData->GetTexVec();

    switch(m_pVerticesData->GetPrimitiveType())
    {
    case CVerticesData::PT_LINES:
        {
            if ( m_nIndex + 1 < m_nTotalNum )
            {
                // 可以在这儿进行视口变换
                //GPoint pt0(tScreenCoor, vColor[m_nIndex], vTex[m_nIndex]);
                CWorldCoordinate wpt0 = ViewportTransform( vPos[m_nIndex] );
                GPoint pt0(wpt0, vColor[m_nIndex]);
                m_nIndex++;
                //GPoint pt1(vPos[m_nIndex], vColor[m_nIndex], vTex[m_nIndex]);
                wpt0 = ViewportTransform( vPos[m_nIndex] );
                GPoint pt1(wpt0, vColor[m_nIndex]);
                geometry = new CLine(pt0, pt1);
                m_nIndex ++;
            }
            else
            {
                return false;
            }
        }
        break;
    case CVerticesData::PT_LINE_STRIP:
    {
        if (m_nIndex + 1 < m_nTotalNum)
        {
            // 可以在这儿进行视口变换
            //GPoint pt0(tScreenCoor, vColor[m_nIndex], vTex[m_nIndex]);
            CWorldCoordinate wpt0 = ViewportTransform(vPos[m_nIndex]);
            GPoint pt0(wpt0, vColor[m_nIndex]);
            m_nIndex++;
            //GPoint pt1(vPos[m_nIndex], vColor[m_nIndex], vTex[m_nIndex]);
            wpt0 = ViewportTransform(vPos[m_nIndex]);
            GPoint pt1(wpt0, vColor[m_nIndex]);
            geometry = new CLine(pt0, pt1);
        }
        else
        {
            return false;
        }
    }
    break;
        
    case CVerticesData::PT_TRIANGLES:
        {
            if ( m_nIndex + 2 < m_nTotalNum )
            {
                CWorldCoordinate wpt0 = ViewportTransform( vPos[m_nIndex] );
                GPoint pt0(wpt0, vColor[m_nIndex], vTex[m_nIndex]);
                m_nIndex++;
                wpt0 = ViewportTransform( vPos[m_nIndex] );
                GPoint pt1(wpt0, vColor[m_nIndex], vTex[m_nIndex]);
                m_nIndex++;
                wpt0 = ViewportTransform( vPos[m_nIndex] );
                GPoint pt2(wpt0, vColor[m_nIndex], vTex[m_nIndex]);
                geometry = new CTriangle(pt0, pt1, pt2);
                m_nIndex ++;
            }
            else
            {
                return false;
            }
        }
        break;
    default:
        break;
    }
    return true;
}

CWorldCoordinate CAssembler::ViewportTransform(const CWorldCoordinate& pt)
{
    CWorldCoordinate wPt;
    wPt.x = (pt.x + 1.0f) * 0.5f * m_uViewportWidht;
    wPt.y = (1.0f + pt.y) * 0.5f * m_uViewportHeight;
    wPt.z = pt.z;
    return wPt;
}

void CAssembler::SetViewportSize(unsigned int nWidth, unsigned int nHeight)
{
    m_uViewportWidht    = nWidth;
    m_uViewportHeight   = nHeight;
}

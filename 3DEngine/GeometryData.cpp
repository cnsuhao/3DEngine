#include "StdAfx.h"
#include "GeometryData.h"

CColor ColorInteration(const CColor c0, const CColor c1, float fRadio)
{
    float fRadio1 = 1.0f - fRadio;
    CColor cc;
    cc.r = c0.r * fRadio1 + c1.r * fRadio;
    cc.g = c0.g * fRadio1 + c1.g * fRadio;
    cc.b = c0.b * fRadio1 + c1.b * fRadio;
    return cc;
}
GPoint PointInteration(const GPoint pt0, const GPoint pt1, float fRadio)
{
    GPoint pt;
    float fRadio1 = 1.0f - fRadio;
    
    // 插值坐标
    pt.vPos.x = pt0.vPos.x * fRadio1 + pt1.vPos.x * fRadio + 0.5f;
    pt.vPos.y = pt0.vPos.y * fRadio1 + pt1.vPos.y * fRadio + 0.5f;

    // 插值深度
    pt.fDepth   = pt0.fDepth * fRadio1 + pt1.fDepth * fRadio;

    // 插值颜色
    pt.uColor   = ColorInteration(pt0.uColor, pt1.uColor, fRadio);

    pt.uvPos    = pt0.uvPos * fRadio1 + pt1.uvPos * fRadio;

    return pt;
};

CGeometryData::CGeometryData(void)
{
}


CGeometryData::~CGeometryData(void)
{
}

CLine::CLine(const GPoint& pt0, const GPoint& pt1)
    //: m_points({pt0, pt1})
    //, m_points[1](pt1)
{
    m_points.reserve(2);
    m_points.push_back(pt0);
    m_points.push_back(pt1);
}

CTriangle::CTriangle(const GPoint& pt0, const GPoint& pt1, const GPoint& pt2)
{
    m_points.reserve(3);
    m_points.push_back(pt0);
    m_points.push_back(pt1);
    m_points.push_back(pt2);
}

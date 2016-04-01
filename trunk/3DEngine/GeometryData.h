#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Common.h"


struct GPoint
{
    GPoint()
        : fDepth(0)
        , uColor( CColor(255, 255, 255))
    {
    }
    GPoint(const CWorldCoordinate& pos, const CColor& color, const glm::vec2& uv)
    {
        vPos.x  = pos.x + 0.5f;
        vPos.y  = pos.y + 0.5f;
        fDepth  = pos.z;
        uColor  = color;

        uvPos   = uv;
    };

    GPoint(const CWorldCoordinate& pos, const CColor& color = CColor(255, 255, 255))
    {
        vPos.x  = pos.x + 0.5f;
        vPos.y  = pos.y + 0.5f;
        fDepth  = pos.z;
        uColor  = color;

    }
    //friend GPoint operator * (const GPoint& pt0, const float fValue)
    //{
    //    GPoint pt;
    //    pt.vPos.x = pt0.vPos.x * fValue + 0.5f;
    //    pt.vPos.y = pt0.vPos.y * fValue + 0.5f;
    //    pt.fDepth = pt0.fDepth * fValue;

    //    const unsigned int maxColorValue = 255;
    //    unsigned int R = pt0.uColor.r * fValue + 0.5f;
    //    unsigned int G = pt0.uColor.g * fValue + 0.5f;
    //    unsigned int B = pt0.uColor.b * fValue + 0.5f;
    //    R = glm::min(R, maxColorValue);
    //    G = glm::min(G, maxColorValue);
    //    B = glm::min(B, maxColorValue);
    //    pt.uColor.r = R;
    //    pt.uColor.g = G;
    //    pt.uColor.b = B;

    //    pt.uvPos  = pt0.uvPos * fValue;
    //    return pt;
    //}
    //friend  GPoint operator * (const float fValue, const GPoint pt0)
    //{
    //    GPoint pt;
    //    return pt;
    //}

    //GPoint operator * (float fValue)
    //{
    //    GPoint pt;
    //    pt.vPos.x = vPos.x * fValue + 0.5f;
    //    pt.vPos.y = vPos.y * fValue + 0.5f;
    //    pt.fDepth = fDepth * fValue;

    //    const unsigned int maxColorValue = 255;
    //    unsigned int R = uColor.r * fValue + 0.5f;
    //    unsigned int G = uColor.g * fValue + 0.5f;
    //    unsigned int B = uColor.b * fValue + 0.5f;
    //    R = glm::min(R, maxColorValue);
    //    G = glm::min(G, maxColorValue);
    //    B = glm::min(B, maxColorValue);
    //    pt.uColor.r = R;
    //    pt.uColor.g = G;
    //    pt.uColor.b = B;

    //    pt.uvPos  = uvPos * fValue;
    //    return pt;
    //}
    //GPoint operator + (const GPoint& pt)
    //{
    //    GPoint tpt;
    //    tpt.vPos    = vPos + pt.vPos;
    //    tpt.fDepth  = fDepth + pt.fDepth;

    //    const unsigned int maxColorValue = 255;
    //    unsigned int R = uColor.r + pt.uColor.r;
    //    unsigned int G = uColor.g + pt.uColor.g;
    //    unsigned int B = uColor.b + pt.uColor.b;
    //    R = glm::min(R, maxColorValue);
    //    G = glm::min(G, maxColorValue);
    //    B = glm::min(B, maxColorValue);
    //    tpt.uColor.r = R;
    //    tpt.uColor.g = G;
    //    tpt.uColor.b = B;

    //    tpt.uvPos   = uvPos + pt.uvPos;
    //    return tpt;
    //}
    //GPoint(GPoint& tPt){};
    CScreenCoordinate   vPos;
    float               fDepth;
    CColor              uColor; // B G R，为了使插值更准确，这儿用浮点数
    CTexCoordinate      uvPos;
};

CColor ColorInteration(const CColor c0, const CColor c1, float fRadio);
GPoint PointInteration(const GPoint pt0, const GPoint pt1, float fRadio);


class CGeometryData
{
    
public:
    enum EnGeometryType
    {
        EN_LINE,
        EN_TRIANGLE,
    };

    CGeometryData(void);
    ~CGeometryData(void);
    virtual EnGeometryType GetGeometryType() = 0;
    virtual const std::vector<GPoint>& GetPoints() = 0;

};

class CLine : public CGeometryData
{
public:
    CLine(const GPoint& pt0, const GPoint& pt1);
    ~CLine();
    virtual EnGeometryType GetGeometryType()
    {
        return CGeometryData::EN_LINE;
    }
    virtual const std::vector<GPoint>& GetPoints()
    {
        return m_points;
    }
private:
    std::vector<GPoint> m_points;
};


class CTriangle : public CGeometryData
{
public:
    CTriangle(const GPoint& pt0, const GPoint& pt1, const GPoint& pt2);
    ~CTriangle();
    virtual EnGeometryType GetGeometryType()
    {
        return CGeometryData::EN_TRIANGLE;
    }

    virtual const std::vector<GPoint>& GetPoints()
    {
        return m_points;
    }
private:
    std::vector<GPoint> m_points;
};
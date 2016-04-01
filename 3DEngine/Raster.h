#pragma once
#include "GeometryData.h"
class CTexture;
class CRaster
{
    enum EnTexState
    {
        TEX_ENABLED,
        TEX_DISABLED,
    };
    //class GPoint
    //{
    //public:
    //    glm::u16vec2    vPos;
    //    float           fDepth;
    //    CColor          fColor; // B G R，为了使插值更准确，这儿用浮点数
    //};
public:
    CRaster(void);
    ~CRaster(void);

    void SetBufferData(LPBYTE pBuffer, unsigned int uBufferWidth, unsigned int uBufferHeight);
    void SetDepthBufferData(float* fBuffer);
    void Rasterization(CGeometryData* pGeometry);
    void SetTexture(CTexture* pTexture);

protected:
    void RasterizationLine(const GPoint& pt0, const GPoint& pt1);
    void RasterizationTriangle(const GPoint& pt0, const GPoint& pt1, const GPoint& pt2);
    void RasterizationHorizontalLine(GPoint& pt0, GPoint& pt1);
    void RasterizationVerticalLine(GPoint& pt0, GPoint& pt1);

    void SetPixelColor(unsigned int xIndex, unsigned int yIndex, float fDepth, CColor uColor);
    void SetFragmentColor(const GPoint& pt0);

    void ViewportTransform(GPoint& pt);

    unsigned int m_nBufferWidth;
    unsigned int m_nBufferHeight;
    LPBYTE       m_pBuffer;
    float*       m_pDepthBuffer;
    CTexture*    m_pTexture;

    EnTexState   m_eTexState;
};


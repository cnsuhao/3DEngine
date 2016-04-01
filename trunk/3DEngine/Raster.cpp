#include "StdAfx.h"
#include "Raster.h"
#include "Texture.h"

CRaster::CRaster(void)
    : m_pTexture(nullptr)
    , m_eTexState(TEX_DISABLED)
{
}


CRaster::~CRaster(void)
{
}

void CRaster::Rasterization(CGeometryData* pGeometry)
{
    const std::vector<GPoint>& pPoints = pGeometry->GetPoints();
    switch( pGeometry->GetGeometryType() )
    {
    case CGeometryData::EN_LINE:
        RasterizationLine(pPoints[0], pPoints[1]);
        break;
    case CGeometryData::EN_TRIANGLE:
        RasterizationTriangle(pPoints[0], pPoints[1], pPoints[2]);
        break;
    default:
        break;
    }
}


void CRaster::RasterizationTriangle(const GPoint& pt0, const GPoint& pt1, const GPoint& pt2)
{
    // 判断三角形是否在视椎体内部

    //

    // 如果是线框模式，只画三条线
    RasterizationLine(pt0, pt1);
    RasterizationLine(pt0, pt2);
    RasterizationLine(pt1, pt2);

    {
        // 画填充三角形
        // 按y的大小排序
        const GPoint* firstPt   = &pt0;
        const GPoint* secondPt  = &pt1;
        const GPoint* thirdPt   = &pt2;
        const GPoint* tmpPt;
        if ( firstPt->vPos.y < secondPt->vPos.y )
        {
            tmpPt       = firstPt;
            firstPt     = secondPt;
            secondPt    = tmpPt;
        }
        if ( firstPt->vPos.y < thirdPt->vPos.y )
        {
            tmpPt       = firstPt;
            firstPt     = thirdPt;
            thirdPt     = tmpPt;
        }

        if ( secondPt->vPos.y < thirdPt->vPos.y )
        {
            tmpPt       = secondPt;
            secondPt    = thirdPt;
            thirdPt     = tmpPt;
        }
        int uDeltaY0   = firstPt->vPos.y - secondPt->vPos.y;
        if ( uDeltaY0 != 0 )
        {
            int uBeginY    = firstPt->vPos.y;
            float uLen0             = firstPt->vPos.y - thirdPt->vPos.y;
            float uLen1             = firstPt->vPos.y - secondPt->vPos.y;
            for (int i=uBeginY; i>secondPt->vPos.y; --i)
            {
                float fRadius0 = (uBeginY - i) / uLen0;
                GPoint tp0  = PointInteration(*firstPt, *thirdPt, fRadius0);

                float fRadius1 = (uBeginY - i) / uLen1;
                GPoint tp1  = PointInteration(*firstPt, *secondPt, fRadius1);

                //GPoint tp0 = (*firstPt) * (1.0f - fRadius0) + (*thirdPt) * fRadius0;
                //GPoint tp1 = (*firstPt) * (1.0f - fRadius1) + (*secondPt) * fRadius1;

                RasterizationLine(tp0, tp1);
            }
        }
        int uDeltaY1   = secondPt->vPos.y - thirdPt->vPos.y;
        if ( uDeltaY1 != 0 )
        {
            int uBeginY    = thirdPt->vPos.y;
            float uLen0             = -(thirdPt->vPos.y - firstPt->vPos.y);
            float uLen1             = -(thirdPt->vPos.y - secondPt->vPos.y);
            for (int i=uBeginY; i<=secondPt->vPos.y; ++i)
            {
                float fRadius0 = (i - uBeginY) / uLen0;
                GPoint tp0  = PointInteration(*thirdPt, *firstPt, fRadius0);

                float fRadius1 = (i - uBeginY) / uLen1;
                GPoint tp1  = PointInteration(*thirdPt, *secondPt, fRadius1);

                //GPoint tp0 = (*thirdPt) * (1.0f - fRadius0) + (*firstPt) * fRadius0;
                //GPoint tp1 = (*thirdPt) * (1.0f - fRadius1) + (*secondPt) * fRadius1;
                RasterizationLine(tp0, tp1);
            }
        }

    }
}

void CRaster::RasterizationLine(const GPoint& in_pt0, const GPoint& in_pt1)
{
    GPoint pt0 = in_pt0;
    GPoint pt1 = in_pt1;
    // cull 处理 begin

    // cull 处理 end

    //ViewportTransform(pt0);
    //ViewportTransform(pt1);

    int nDeltaX = pt1.vPos.x - pt0.vPos.x;
    if (nDeltaX == 0)   // 竖直线
    {
        return RasterizationVerticalLine(pt0, pt1);
    }
    int nDeltaY = pt1.vPos.y - pt0.vPos.y;
    if (nDeltaY == 0)   // 水平线
    {
        return RasterizationHorizontalLine(pt0, pt1);
    }
    if ( abs(nDeltaY) > abs(nDeltaX) )  // 斜率大于1
    {
        return RasterizationVerticalLine(pt0, pt1);
    }
    else
    {
        return RasterizationHorizontalLine(pt0, pt1);
    }
}

void CRaster::SetFragmentColor(const GPoint& pt0)
{
    int xIndex = m_nBufferWidth - pt0.vPos.x - 1;
    int yIndex = pt0.vPos.y;

    if ( xIndex <0 || xIndex >= m_nBufferWidth || yIndex >= m_nBufferHeight || yIndex <0)
    {
        return;
    }
    // 根据深度判断
    unsigned int uIndex = yIndex * m_nBufferWidth + xIndex;
    // 深度判断
    if ( m_pDepthBuffer[uIndex] < pt0.fDepth )
    {
        return;
    }
    m_pDepthBuffer[uIndex] = pt0.fDepth;
    // 计算纹理
    CColor uColor = pt0.uColor;
    float fx = uColor.r / 255.0f;
    float fy = uColor.g / 255.0f;
    float fz = uColor.b / 255.0f;
    //uColor = CColor(200, 200, 200);
    switch(m_eTexState)
    {
    case TEX_ENABLED:
        {
            CColor tColor = m_pTexture->GetTexByCoordinate(pt0.uvPos.x, pt0.uvPos.y);

            uColor.r = tColor.r * fx;
            uColor.g = tColor.g * fy;
            uColor.b = tColor.b * fz;
        }
        break;
    case TEX_DISABLED:
        break;
    default:
        break;
    }    
    
    uIndex *= BYTE_PER_PIXEL;
    unsigned char* pBuffer = (unsigned char*)m_pBuffer;
    pBuffer[uIndex++]   = uColor.x;
    pBuffer[uIndex++]   = uColor.y;
    pBuffer[uIndex++]   = uColor.z;
    // 颜色混合

}

void CRaster::SetPixelColor(unsigned int xIndex, unsigned int yIndex, float fDepth, CColor uColor)
{
    // 图片是上下颠倒的，所以要把yIndex翻转一下
    //yIndex = m_nBufferHeight - yIndex - 1;
    xIndex = m_nBufferWidth  - xIndex - 1;
    if ( xIndex >= m_nBufferWidth || yIndex >= m_nBufferHeight )
    {
        return;
    }
    unsigned int uIndex = yIndex * m_nBufferWidth + xIndex;
    // 深度判断
    if ( m_pDepthBuffer[uIndex] < fDepth )
    {
        return;
    }
    m_pDepthBuffer[uIndex]  = fDepth;

    uIndex *= BYTE_PER_PIXEL;
    unsigned char* pBuffer = (unsigned char*)m_pBuffer;
    pBuffer[uIndex++]   = uColor.x;
    pBuffer[uIndex++]   = uColor.y;
    pBuffer[uIndex++]   = uColor.z;

    //m_pBuffer[uIndex]   = uColor;

}

void CRaster::RasterizationHorizontalLine(GPoint& pt0, GPoint& pt1)
{
    // 水平线就递增x
    GPoint* minPt = nullptr;
    GPoint* maxPt = nullptr;
    if ( pt0.vPos.x < pt1.vPos.x )
    {
        minPt = &pt0;
        maxPt = &pt1;
    }
    else
    {
        minPt = &pt1;
        maxPt = &pt0;
    }
    SetFragmentColor(pt0);
    SetFragmentColor(pt1);
    //SetPixelColor(pt0.vPos.x, pt0.vPos.y, pt0.fDepth, pt0.uColor);
    //SetPixelColor(pt1.vPos.x, pt1.vPos.y, pt1.fDepth, pt1.uColor);
    float fDeltaY = maxPt->vPos.y - minPt->vPos.y;
    float fDeltaX = maxPt->vPos.x - minPt->vPos.x;
    float fGradient = fDeltaY / fDeltaX;
    float tY=minPt->vPos.y + 0.5f;

    int minX = minPt->vPos.x;
    int maxX = maxPt->vPos.x;
    float fLen  = maxX - minX;
    for (int i=minX; i<maxX; i++)
    {
        float fRadio = (i - minX) / fLen;
        GPoint pt  = PointInteration(*minPt, *maxPt, fRadio);
        SetFragmentColor(pt);
        tY += fGradient;
    }
}

void CRaster::RasterizationVerticalLine(GPoint& pt0, GPoint& pt1)
{
    // 垂直线就递增y
    GPoint* minPt = nullptr;
    GPoint* maxPt = nullptr;
    if ( pt0.vPos.y < pt1.vPos.y )
    {
        minPt = &pt0;
        maxPt = &pt1;
    }
    else
    {
        minPt = &pt1;
        maxPt = &pt0;
    }
    //SetPixelColor(pt0.vPos.x, pt0.vPos.y, pt0.fDepth, pt0.uColor);
    //SetPixelColor(pt1.vPos.x, pt1.vPos.y, pt1.fDepth, pt1.uColor);
    SetFragmentColor(pt0);
    SetFragmentColor(pt1);

    float fDeltaY = maxPt->vPos.y - minPt->vPos.y;
    float fDeltaX = maxPt->vPos.x - minPt->vPos.x;
    float fGradient = fDeltaX / fDeltaY;
    float tX=minPt->vPos.x + 0.5f;

    unsigned int minY = minPt->vPos.y;
    unsigned int maxY = maxPt->vPos.y;
    float fLen  = maxY - minY;
    for (unsigned int i=minY; i<maxY; i++)
    {
        float fRadio = (i - minY) / fLen;
        GPoint pt  = PointInteration(*minPt, *maxPt, fRadio);
        SetFragmentColor(pt);
        tX += fGradient;
    }
}

void CRaster::SetBufferData(LPBYTE pBuffer, unsigned int uBufferWidth, unsigned int uBufferHeight)
{
    m_pBuffer = pBuffer;
    m_nBufferWidth = uBufferWidth;
    m_nBufferHeight = uBufferHeight;
}


void CRaster::ViewportTransform(GPoint& pt)
{
    pt.vPos.x = (pt.vPos.x + 1.0f) * 0.5f * m_nBufferWidth;
    pt.vPos.y = (1.0f - pt.vPos.y) * 0.5f * m_nBufferHeight;
}

void CRaster::SetDepthBufferData(float* fBuffer)
{
    m_pDepthBuffer = fBuffer;
}

void CRaster::SetTexture(CTexture* pTexture)
{
    m_pTexture = pTexture;
}


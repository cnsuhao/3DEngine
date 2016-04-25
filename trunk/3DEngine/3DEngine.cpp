#include "stdafx.h"
#include "3DEngine.h"
#include <string>


C3DEngine::C3DEngine(HWND hWnd, int iWindowWidth, int iWindowHeight)
    : m_hWnd(hWnd)
    , m_nWindowHeight(iWindowHeight)
    , m_nWindowWidth(iWindowWidth)
{
    m_nPointNum = m_nWindowHeight * m_nWindowWidth;
    int nArraySize = m_nPointNum * BYTE_PER_PIXEL;
    m_lpData = (LPBYTE)malloc(nArraySize*sizeof(BYTE));
    memset(m_lpData, 0, nArraySize*sizeof(BYTE));

    m_pDepthBuffer = (float*)malloc( nArraySize*sizeof(float) );    // 深度缓存

    m_raster.SetBufferData(m_lpData, m_nWindowWidth, m_nWindowHeight);
    m_raster.SetDepthBufferData(m_pDepthBuffer);
    m_raster.SetTexture(&m_texture);
    m_oVerticesDataTransformer.SetAspect(m_nWindowWidth / (float)m_nWindowHeight);
    m_assembler.SetViewportSize(m_nWindowWidth, m_nWindowHeight);
    m_camera.SetAspect(m_nWindowWidth / (float)m_nWindowHeight);

    memset(&m_bih, 0, sizeof(BITMAPINFOHEADER));
    m_bih.biSize = sizeof(BITMAPINFOHEADER);
    m_bih.biWidth = m_nWindowWidth;
    m_bih.biHeight = m_nWindowHeight;
    m_bih.biPlanes = 1;
    m_bih.biBitCount = BYTE_PER_PIXEL * 8;
    m_bih.biCompression = BI_RGB;
    m_bih.biSizeImage = nArraySize;
    m_hDD = DrawDibOpen();

    m_texture.LoadFromFile(std::wstring(L"muban1.jpg"));
}

C3DEngine::~C3DEngine()
{

}

void C3DEngine::Draw()
{
    Clear();
    m_oVerticesDataTransformer.SetEyeDirection(m_camera.GetDirection());
    CVerticesData transformedData = m_oVerticesDataTransformer.TransformVerticesData(m_verticesData, m_camera.GetViewProjectionMat());   // 顶点变换
    m_assembler.SetVerticesData(&transformedData);                       // 图元组装
    CGeometryData* pGeometry;
    //m_raster.SetTextureState(CRaster::TEX_ENABLED);
    while( m_assembler.GetNextGeometry(pGeometry) )
    {
        m_raster.Rasterization(pGeometry);          // 光栅化
    }


    HDC hDC = GetDC(m_hWnd);
    //////////////////////////////////////////////////////////////////////////
    //const std::vector<glm::vec3>& posVec = m_verticesData.GetPosVec();


    //DrawDibDraw(m_hDD, hDC, 0, 0, m_nWindowWidth, m_nWindowHeight, &m_bih, m_lpData, 
    //    0, 0, m_nWindowWidth, m_nWindowHeight, 0);
    //unsigned char* pBuffer = (unsigned char*)m_lpData;
    //for (int i=0; i<m_nWindowHeight; ++i)
    //{
    //    int index = (i*m_nWindowWidth+1) * 3;
    //    pBuffer[index] = 255;
    //    pBuffer[index+1] = 255;
    //    pBuffer[index+2] = 255;

    //    index = ((i+1)*m_nWindowWidth-2) * 3;
    //    pBuffer[index] = 255;
    //    pBuffer[index+1] = 255;
    //    pBuffer[index+2] = 255;
    //}

    DrawDibDraw(m_hDD, hDC, 0, 0, -1, -1, &m_bih, m_lpData, 
        0, 0, m_nWindowWidth, m_nWindowHeight, 0);
    ReleaseDC(m_hWnd, hDC);
}

void C3DEngine::SetCamera()
{

}

void C3DEngine::SetVerticesData(CVerticesData& pVerticesData)
{
    m_verticesData = pVerticesData;
}

void C3DEngine::Clear()
{
    //unsigned char* pBuffer = (unsigned char*) m_lpData;
    //for(int i=0; i<m_nPointNum; ++i)
    //{
    //    *pBuffer++  = 0;
    //    *pBuffer++  = 200;
    //    *pBuffer++  = 0;
    //}
    //return;
    //DWORD clearColor = _RGB(0, 200, 0);
    //memset(m_lpData, clearColor, m_nImageSize / 4);
    //return;
    // Clear surface and z-buffer
    LPDWORD lpData = (LPDWORD)m_lpData;
    LPDWORD lpZBufferData = (LPDWORD)m_pDepthBuffer;
    glm::u8vec3 clearColor(0, 0, 0);   // B G R
    float fInitDepth = 2.0f;
    DWORD dwSize = m_nPointNum;
    __asm {
            mov edi, lpData
            mov esi, lpZBufferData
            mov eax, clearColor
            mov ebx, fInitDepth
            mov ecx, dwSize
loop1:		mov [edi], eax
            mov [esi], ebx
            add edi, BYTE_PER_PIXEL
            add esi, 4
            dec ecx
            jnz loop1
    }
}

void C3DEngine::MouseEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
    m_camera.MouseEvent(msg, wParam, lParam);
}

void C3DEngine::KeyEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case 'q':
    case 'Q':
        m_verticesData.ChangePrimitiveType();
        break;
    case 'w':
    case 'W':
        m_raster.ChangeTextureState();
        break;
    case 'e':
    case 'E':
        m_oVerticesDataTransformer.ChangeLightState();
        break;
    default:
        break;
    }
}

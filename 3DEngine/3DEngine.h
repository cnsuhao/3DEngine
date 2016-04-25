#pragma once

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <stdio.h>
#include <vfw.h>
#include <xmmintrin.h>

#include <vector>
#include "VerticesData.h"
#include "VerticesTransformer.h"
#include "Assembler.h"
#include "Raster.h"
#include "Camera.h"
#include "Texture.h"

#pragma comment (lib, "vfw32")

class C3DEngine
{
#define _RGB(r,g,b)	(((r) << 16) | ((g) << 8) | (b))			// Convert to RGB
public:
    C3DEngine(HWND hWnd, int iWindowWidth, int iWindowHeight);
    ~C3DEngine();

    void Draw();

    void SetCamera();

    void SetVerticesData(CVerticesData& pVerticesData);
    void MouseEvent(UINT msg, WPARAM wParam, LPARAM lParam);
    void KeyEvent(UINT msg, WPARAM wParam, LPARAM lParam);

private:
    void Clear();


    std::vector<CVerticesData*> m_pVerticesDataVec;

    CVerticesTransformer    m_oVerticesDataTransformer;
    CAssembler              m_assembler;
    CRaster                 m_raster;

    CVerticesData           m_verticesData;
    CCamera                 m_camera;

    HWND m_hWnd;
    int m_nWindowWidth;
    int m_nWindowHeight;
    int m_nPointNum;

    HDRAWDIB m_hDD;
    LPBYTE m_lpData;
    BITMAPINFOHEADER m_bih;

    float* m_pDepthBuffer;

    // π‚’’
    glm::vec3 m_vLightPos;
    CColor    m_lightColor;

    CTexture  m_texture;
};
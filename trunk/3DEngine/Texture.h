#pragma once
#include <string>
#include "glm/glm.hpp"
#include "Common.h"
#include "FreeImage/FreeImage.h"
class CTexture
{
public:
    CTexture();
    ~CTexture(void);

    CColor GetTexByCoordinate(float fu, float fv);
    bool LoadFromFile(std::wstring& imageFileName);
protected:
    unsigned int m_uImageHeight;
    unsigned int m_uImageWidth;
    unsigned int m_uImagePitch;

    BYTE*        m_pBuffer;
    FREE_IMAGE_COLOR_TYPE m_eColorType;
};


#include "StdAfx.h"
#include "Texture.h"

#pragma comment(lib, "FreeImage32d.lib")

CTexture::CTexture()
{
}


CTexture::~CTexture(void)
{
}

bool CTexture::LoadFromFile(std::wstring& imageFileName)
{
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);


    //check the file signature and deduce its format
    fif = FreeImage_GetFileTypeU(imageFileName.c_str(), 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN) 
        fif = FreeImage_GetFIFFromFilenameU(imageFileName.c_str());
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        return 0;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_LoadU(fif, imageFileName.c_str());

    if (!dib)
    {
        return 0;
    }

    // color model
    FREE_IMAGE_COLOR_TYPE m_eColorType = FreeImage_GetColorType(dib);
    FREE_IMAGE_TYPE imageTpye = FreeImage_GetImageType(dib);


    //get the image width, height and pitch
    m_uImageWidth   = FreeImage_GetWidth(dib);
    m_uImageHeight  = FreeImage_GetHeight(dib);
    m_uImagePitch   = FreeImage_GetPitch(dib) / 3;
    m_pBuffer       = FreeImage_GetBits(dib);

    return true;
}

CColor CTexture::GetTexByCoordinate(float fu, float fv)
{
    fu = glm::min(fu, 1.0f);
    fv = glm::min(fv, 1.0f);
    unsigned int tx = fu * m_uImageWidth - 0.5f;
    unsigned int ty = fv * m_uImageHeight- 0.5f;
    unsigned int uIndex = ty * m_uImagePitch + tx;
    unsigned int tIndex = uIndex * 3;
    CColor color;
    color.r = m_pBuffer[tIndex++];
    color.g = m_pBuffer[tIndex++];
    color.b = m_pBuffer[tIndex++];
    return color;
}

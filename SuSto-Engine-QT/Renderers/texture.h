#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "3rdParty/MathGeoLib/Math/float2.h"
#include "globals.h"

class Texture
{
    friend class TextureManager;
    friend class RenderTargetRenderer;

private:
    Texture(const std::string& file_path);
    void operator delete(void *) {}

public:
    std::string GetFilePath() const;

    bool GetLoaded() const;

    int GetTextureId() const;
    float2 GetTextureSize() const;

private:
    std::string file_path = "";
    std::string file_name = "";

    bool loaded = false;

    uint texture_id = 0;

    float2 texture_size = float2::zero;

    unsigned char* texture_data = nullptr;
    uint texture_data_size = 0;
    uint texture_data_channels = 0;
};

#endif // TEXTURE_H

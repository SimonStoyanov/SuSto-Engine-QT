#include "texture.h"

Texture::Texture(const std::string &path)
{
    file_path = path;
}

std::string Texture::GetFilePath() const
{
    return file_path;
}

bool Texture::GetLoaded() const
{
    return loaded;
}

int Texture::GetTextureId() const
{
    return texture_id;
}

float2 Texture::GetTextureSize() const
{
    return texture_size;
}

#include "texturemanager.h"
#include "Renderers/texture.h"
#include "Managers/rendermanager.h"
#include "Managers/eventmanager.h"
#include "Events/event.h"

#define STB_IMAGE_IMPLEMENTATION
#include "3rdParty/StbImage/stb_image.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{

}

Texture *TextureManager::LoadTexture(const std::string &path)
{
    Texture* ret = nullptr;

    bool all_correct = true;

    all_correct = GetLoadedTextureFromFilepath(path) == nullptr;

    if(all_correct)
    {
        int width, height, channels;
        unsigned char *image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        all_correct = image != nullptr;

        if(all_correct)
        {
            ret = new Texture(path);

            ret->texture_data = image;
            ret->texture_data_size = sizeof(image);
            ret->texture_data_channels = channels;

            ret->texture_size = float2(width, height);

            textures.push_back(ret);
        }
        else
        {
            SPOOKYLOG("Error opening texture file: " + path);
        }
    }
    else
    {
        SPOOKYLOG("Texture file was already loaded: " + path);
    }

    return ret;
}

void TextureManager::UnloadTexture(Texture *tex)
{

}

void TextureManager::LoadToVRAM(Texture *tex)
{
    if(tex != nullptr)
    {
        RenderManager::Instance()->UseGL();

        if(!tex->GetLoaded())
        {
            tex->loaded = true;

            tex->texture_id = RenderManager::Instance()->LoadTextureToVRAM
                    (tex->texture_size.x, tex->texture_size.y, tex->texture_data, GL_RGBA);

            SPOOKYLOG("Loading texture to VRAM with id: " + std::to_string((tex->texture_id)));

            EventManager::Instance()->SendEvent(new Event(EventType::EVENT_TEXTURE_LOADED));

        }
    }
}

void TextureManager::UnloadFromVRAM(Texture *tex)
{
    if(tex != nullptr)
    {
        RenderManager::Instance()->UseGL();

        if(tex->GetLoaded())
        {
            tex->loaded = false;

            RenderManager::Instance()->DeleteTexture(tex->texture_id);
        }
    }
}

Texture *TextureManager::GetLoadedTextureFromFilepath(const std::string &filepath)
{
    Texture* ret = nullptr;

    for(std::vector<Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        if((*it)->file_path.compare(filepath) == 0)
        {
            ret = (*it);

            break;
        }
    }

    return ret;
}

std::vector<Texture *> TextureManager::GetAllTextures() const
{
    return textures;
}

void TextureManager::Start()
{
    stbi_set_flip_vertically_on_load(true);
}

void TextureManager::CleanUp()
{

}

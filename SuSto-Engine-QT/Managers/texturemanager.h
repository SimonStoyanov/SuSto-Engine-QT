#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>

class Texture;

class TextureManager
{
    friend class AppManager;

private:
    TextureManager();
    void operator delete(void *) {}

public:
    static TextureManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new TextureManager();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

public:
    Texture* LoadTexture(const std::string& path);
    void UnloadTexture(Texture* tex);

    void LoadToVRAM(Texture* tex);
    void UnloadFromVRAM(Texture* tex);

    Texture *GetLoadedTextureFromFilepath(const std::string& filepath);
    std::vector<Texture*> GetAllTextures() const;

private:
    void Start();
    void CleanUp();

private:
    static TextureManager* instance;

private:
    std::vector<Texture*> textures;

};

#endif // TEXTUREMANAGER_H

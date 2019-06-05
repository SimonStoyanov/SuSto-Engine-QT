#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <vector>

class aiScene;
class aiNode;
class aiMesh;
class Mesh;
class SubMesh;

class MeshManager
{
    friend class AppManager;

private:
    MeshManager();
    void operator delete(void *) {}

public:
    static MeshManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new MeshManager();
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
    Mesh* LoadMesh(const std::string& filepath);

    void LoadToVRAM(Mesh* mesh);
    void UnloadFromVRAM(Mesh* mesh);

private:
    void Start();
    void CleanUp();

    void ProcessNode(aiScene* scene, aiNode* node, Mesh* mesh);
    SubMesh* ProcessMesh(aiScene* scene, aiMesh* mesh);

private:
    static MeshManager* instance;

private:
    std::vector<Mesh*> meshes;
};

#endif // MESHMANAGER_H

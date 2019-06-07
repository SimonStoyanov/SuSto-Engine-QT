#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <vector>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include "globals.h"

class Mesh;
class SubMesh;

class AssimpLogger : public Assimp::LogStream
{
public:
    AssimpLogger()
    {

    }
    ~AssimpLogger()
    {}
    void write(const char* message)
    {
        SPOOKYLOG(message);
    }
};

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

    std::vector<Mesh*> GetAllMeshes() const;

private:
    void Start();
    void CleanUp();

    void ProcessNode(const aiScene* scene, aiNode* node, Mesh* mesh);
    SubMesh* ProcessMesh(const aiScene* scene, aiMesh* mesh);

private:
    static MeshManager* instance;

private:
    std::vector<Mesh*> meshes;

    bool debug_logs = true;
};

#endif // MESHMANAGER_H

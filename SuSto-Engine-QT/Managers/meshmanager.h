#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <vector>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include "globals.h"
#include <filesystem>

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
    std::vector<Mesh*> LoadMesh(const std::string& filepath);

    void LoadToVRAM(Mesh* mesh);
    void UnloadFromVRAM(Mesh* mesh);

    std::vector<Mesh*> GetLoadedMeshesFromFilepath(const std::string& filepath);
    Mesh* GetLoadedMeshFromFilepathPlusName(const std::string& filepath_plus_name);
    std::vector<Mesh*> GetAllMeshes() const;

    void LoadDefaultMeshes();

private:
    void Start();
    void CleanUp();

    void ProcessNode(const aiScene* scene, aiNode* node, std::vector<Mesh*>& mesh_list, std::experimental::filesystem::path path);
    Mesh* ProcessMesh(const aiScene* aiscene, aiMesh* aimesh, std::experimental::filesystem::path path);

private:
    static MeshManager* instance;

public:
    Mesh* vertical_plane_mesh = nullptr;
    Mesh* sphere_mesh = nullptr;

private:
    std::vector<Mesh*> meshes;

    bool debug_logs = true;
};

#endif // MESHMANAGER_H

#include "meshmanager.h"
#include <qfile.h>
#include "Managers/rendermanager.h"
#include "Renderers/mesh.h"
#include "Managers/eventmanager.h"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/cfileio.h>
#include <assimp/Importer.hpp>
#include <assimp/importerdesc.h>

#include <filesystem>

MeshManager* MeshManager::instance = nullptr;

MeshManager::MeshManager()
{
    Assimp::DefaultLogger::create();
    const uint severity = Assimp::Logger::Debugging | Assimp::Logger::Info | Assimp::Logger::Err | Assimp::Logger::Warn;
    Assimp::DefaultLogger::get()->attachStream(new AssimpLogger(),severity);
}

std::vector<Mesh*> MeshManager::LoadMesh(const std::string &filepath)
{
    std::vector<Mesh*> ret;

    std::experimental::filesystem::path path = filepath;

    bool all_correct = true;

    all_correct = GetLoadedMeshesFromFilepath(filepath).size() == 0;

    QFile file(filepath.c_str());

    if(all_correct)
    {
        all_correct = file.open(QIODevice::ReadOnly);
        file.close();

        if(all_correct)
        {
            const aiScene* scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes |
                                                aiProcess_PreTransformVertices | aiProcess_ImproveCacheLocality | aiProcess_CalcTangentSpace);

            all_correct = (scene != nullptr) && (scene->mRootNode != nullptr) && ((scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == false);

            if(all_correct)
            {
                if(debug_logs)
                {
                    SPOOKYLOG("Mesh scene properly loaded: " + filepath);
                }

                ProcessNode(scene, scene->mRootNode, ret, path);
            }
            else
            {
                if(scene == nullptr)
                    SPOOKYLOG("Error loading mesh scene [scene was nullptr]: " + filepath);
                else if(scene->mRootNode == nullptr)
                    SPOOKYLOG("Error loading mesh scene [scene root node was nullptr]: " + filepath);
                else if(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
                    SPOOKYLOG("Error loading mesh scene [scene flag incomplete]: " + filepath);
            }
        }
        else
        {
            SPOOKYLOG("Error opening mesh file: " + filepath);
        }
    }
    else
    {
        SPOOKYLOG("Mesh file was already loaded: " + filepath);
    }

    if(all_correct)
    {
        for(std::vector<Mesh*>::iterator it = ret.begin(); it != ret.end(); ++it)
        {
            meshes.push_back(*it);
        }
    }

    return ret;
}

void MeshManager::Start()
{

}

void MeshManager::CleanUp()
{

}

void MeshManager::ProcessNode(const aiScene *aiscene, aiNode *node, std::vector<Mesh*>& mesh_list, std::experimental::filesystem::path path)
{
    std::vector<aiNode*> nodes_to_check;
    nodes_to_check.push_back(node);

    while(nodes_to_check.size() > 0)
    {
        aiNode* curr_node = *nodes_to_check.begin();

        for(int i = 0; i < curr_node->mNumMeshes; ++i)
        {
            aiMesh* aimesh = aiscene->mMeshes[curr_node->mMeshes[i]];

            Mesh* new_mesh = ProcessMesh(aiscene, aimesh, path);

            mesh_list.push_back(new_mesh);
        }

        for(int i = 0; i < curr_node->mNumChildren; ++i)
        {
            aiNode* node_to_add = curr_node->mChildren[i];

            nodes_to_check.push_back(node_to_add);
        }

        nodes_to_check.erase(nodes_to_check.begin());
    }
}

Mesh *MeshManager::ProcessMesh(const aiScene *aiscene, aiMesh * aimesh, std::experimental::filesystem::path path)
{
    Mesh* ret = new Mesh(path.string());

    ret->name = aimesh->mName.C_Str();

    ret->has_uvs = aimesh->HasTextureCoords(0);

    ret->vertex_buffer.reserve(aimesh->mNumVertices * 2 * 3);
    ret->vertex_buffer.reserve(aimesh->mNumVertices * 2);

    for(int i = 0; i < aimesh->mNumVertices; ++i)
    {
        aiVector3D aivertice = aimesh->mVertices[i];
        aiVector3D ainormals = aimesh->mNormals[i];

        ret->vertex_buffer.push_back(aivertice.x);
        ret->vertex_buffer.push_back(aivertice.y);
        ret->vertex_buffer.push_back(aivertice.z);

        ret->vertex_buffer.push_back(ainormals.x);
        ret->vertex_buffer.push_back(ainormals.y);
        ret->vertex_buffer.push_back(ainormals.z);

        if(ret->has_uvs)
        {
            aiVector3D aiuvs = aimesh->mTextureCoords[0][i];

            ret->vertex_buffer.push_back(aiuvs.x);
            ret->vertex_buffer.push_back(aiuvs.y);
        }
        else
        {
            ret->vertex_buffer.push_back(0);
            ret->vertex_buffer.push_back(0);
        }
    }

    ret->index_buffer.reserve(aimesh->mNumFaces * 3);

    for(int i = 0; i < aimesh->mNumFaces; ++i)
    {
        aiFace aiface = aimesh->mFaces[i];

        if(aiface.mNumIndices <= 3)
        {
            for(int f = 0; f < aiface.mNumIndices; ++f)
            {
                uint indice = aiface.mIndices[f];

                ret->index_buffer.push_back(indice);
            }
        }
    }

    // Textures -----------

    if(aimesh->mMaterialIndex > 0 && aimesh->mMaterialIndex < aiscene->mNumMaterials)
    {
        aiMaterial* aimaterial = aiscene->mMaterials[aimesh->mMaterialIndex];

        int diffuse_count = aimaterial->GetTextureCount(aiTextureType_DIFFUSE);
        int height_count = aimaterial->GetTextureCount(aiTextureType_HEIGHT);
        int normals_count = aimaterial->GetTextureCount(aiTextureType_NORMALS);

        if(diffuse_count > 0)
        {
            aiString texture_path;
            bool success = aimaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS;

            std::experimental::filesystem::path new_path = path.parent_path().string() + "/" + std::string(texture_path.C_Str());

            if(success)
                ret->textures_difuse_paths.push_back(new_path.string());

            SPOOKYLOG("Mesh contains diffuse: " + new_path.string());
        }

        if(height_count > 0)
        {
            aiString texture_path;
            bool success = aimaterial->GetTexture(aiTextureType_HEIGHT, 0, &texture_path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS;

            std::experimental::filesystem::path new_path = path.parent_path().string() + "/" + std::string(texture_path.C_Str());

            if(success)
                ret->textures_height_paths.push_back(new_path.string());

            SPOOKYLOG("Mesh contains height map: " + new_path.string());
        }

        if(normals_count > 0)
        {
            aiString texture_path;
            bool success = aimaterial->GetTexture(aiTextureType_NORMALS, 0, &texture_path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS;

            std::experimental::filesystem::path new_path = path.parent_path().string() + "/" + std::string(texture_path.C_Str());

            if(success)
                ret->textures_normals_paths.push_back(new_path.string());

            SPOOKYLOG("Mesh contains normal map: " + new_path.string());
        }
    }

    return ret;
}

void MeshManager::LoadToVRAM(Mesh *mesh)
{
    if(mesh != nullptr)
    {
        RenderManager::Instance()->UseGL();

        if(!mesh->loaded)
        {
            mesh->loaded = true;

            SPOOKYLOG("Loading mesh to VRAM with vao: " + std::to_string((mesh->vao)));

            SPOOKYLOG("Loaded " + std::to_string(mesh->vertex_buffer.size()) + " vertices to VRAM");
            SPOOKYLOG("Loaded " + std::to_string(mesh->index_buffer.size()) + " indices to VRAM");

            // VAO
            mesh->vao = RenderManager::Instance()->GenVertexArrayBuffer();
            RenderManager::Instance()->BindVertexArrayBuffer(mesh->vao);

            // VBO
            mesh->vbo = RenderManager::Instance()->GenBuffer();
            RenderManager::Instance()->BindArrayBuffer(mesh->vbo);

            RenderManager::Instance()->LoadArrayToVRAM(mesh->vertex_buffer.size() * sizeof(float),
                                                       &mesh->vertex_buffer[0], GL_STATIC_DRAW);

            RenderManager::Instance()->EnableVertexAttributeArray(0);
            RenderManager::Instance()->EnableVertexAttributeArray(1);
            RenderManager::Instance()->EnableVertexAttributeArray(2);

            // Set info
            RenderManager::Instance()->SetVertexAttributePointer(0, 3, 8, 0);
            RenderManager::Instance()->SetVertexAttributePointer(1, 3, 8, 3);
            RenderManager::Instance()->SetVertexAttributePointer(2, 2, 8, 6);

            // VBIO
            mesh->vbio = RenderManager::Instance()->GenBuffer();
            RenderManager::Instance()->BindElementArrayBuffer(mesh->vbio);

            RenderManager::Instance()->LoadElementArrayToVRAM(mesh->index_buffer.size() * sizeof(uint),
                                                              &mesh->index_buffer[0], GL_STATIC_DRAW);


            // Clear
            RenderManager::Instance()->UnbindVertexArrayBuffer();

            RenderManager::Instance()->DisableVertexAttributeArray(0);
            RenderManager::Instance()->DisableVertexAttributeArray(1);
            RenderManager::Instance()->DisableVertexAttributeArray(2);

            EventManager::Instance()->SendEvent(new Event(EventType::EVENT_MESH_LOADED));
        }

    }
}

void MeshManager::UnloadFromVRAM(Mesh *mesh)
{
    if(mesh != nullptr)
    {
        RenderManager::Instance()->UseGL();

        if(mesh->loaded)
        {
            mesh->loaded = false;

            RenderManager::Instance()->DeleteFrameBuffer(mesh->vao);

            mesh->vao = 0;
        }

    }
}

Mesh *MeshManager::GetLoadedMeshFromFilepathPlusName(const std::string &filepath_plus_name)
{
    Mesh* ret = nullptr;

    for(std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        if((*it)->GetFilePathPlusName().compare(filepath_plus_name) == 0)
        {
            ret = (*it);

            break;
        }
    }

    return ret;
}

std::vector<Mesh*> MeshManager::GetLoadedMeshesFromFilepath(const std::string &filepath)
{
    std::vector<Mesh*> ret;

    for(std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        if((*it)->GetFilePath().compare(filepath) == 0)
        {
            ret.push_back((*it));
        }
    }

    return ret;
}

std::vector<Mesh *> MeshManager::GetAllMeshes() const
{
    return meshes;
}



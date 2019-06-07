#include "meshmanager.h"
#include <qfile.h>
#include "Managers/rendermanager.h"
#include "Renderers/mesh.h"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/cfileio.h>
#include <assimp/Importer.hpp>
#include <assimp/importerdesc.h>

MeshManager* MeshManager::instance = nullptr;

MeshManager::MeshManager()
{
    Assimp::DefaultLogger::create();
    const uint severity = Assimp::Logger::Debugging | Assimp::Logger::Info | Assimp::Logger::Err | Assimp::Logger::Warn;
    Assimp::DefaultLogger::get()->attachStream(new AssimpLogger(),severity);
}

Mesh* MeshManager::LoadMesh(const std::string &filepath)
{
    Mesh* ret = new Mesh();

    bool all_correct = true;

    Assimp::Importer importer;

    QFile file(filepath.c_str());

    all_correct = file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();

    if(all_correct)
    {
        const aiScene* scene = aiImportFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes |
                                            aiProcess_PreTransformVertices | aiProcess_ImproveCacheLocality);

        all_correct = (scene != nullptr) && (scene->mRootNode != nullptr) && ((scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == false);

        if(all_correct)
        {
            if(debug_logs)
            {
                SPOOKYLOG("Mesh scene properly loaded: " + filepath);
            }

            ProcessNode(scene, scene->mRootNode, ret);
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

    return ret;
}

void MeshManager::Start()
{

}

void MeshManager::CleanUp()
{

}

void MeshManager::ProcessNode(const aiScene *scene, aiNode *node, Mesh *mesh)
{
    std::vector<aiNode*> nodes_to_check;
    nodes_to_check.push_back(node);

    while(nodes_to_check.size() > 0)
    {
        aiNode* curr_node = *nodes_to_check.begin();

        for(int i = 0; i < curr_node->mNumMeshes; ++i)
        {
            aiMesh* aimesh = scene->mMeshes[curr_node->mMeshes[i]];

            SubMesh* sub_mesh = ProcessMesh(scene, aimesh);

            mesh->sub_meshes.push_back(sub_mesh);
        }

        for(int i = 0; i < curr_node->mNumChildren; ++i)
        {
            aiNode* node_to_add = curr_node->mChildren[i];

            nodes_to_check.push_back(node_to_add);
        }

        nodes_to_check.erase(nodes_to_check.begin());
    }
}

SubMesh *MeshManager::ProcessMesh(const aiScene *scene, aiMesh *mesh)
{
    SubMesh* ret = new SubMesh();

    ret->has_uvs = mesh->HasTextureCoords(0);

    ret->vertex_buffer.reserve(mesh->mNumVertices * 2 * 3);
    ret->vertex_buffer.reserve(mesh->mNumVertices * 2);

    for(int i = 0; i < mesh->mNumVertices; ++i)
    {
        aiVector3D aivertice = mesh->mVertices[i];
        aiVector3D ainormals = mesh->mNormals[i];

        ret->vertex_buffer.push_back(aivertice.x);
        ret->vertex_buffer.push_back(aivertice.y);
        ret->vertex_buffer.push_back(aivertice.z);

        ret->vertex_buffer.push_back(ainormals.x);
        ret->vertex_buffer.push_back(ainormals.y);
        ret->vertex_buffer.push_back(ainormals.z);

        if(ret->has_uvs)
        {
            aiVector3D aiuvs = mesh->mTextureCoords[0][i];

            ret->vertex_buffer.push_back(aiuvs.x);
            ret->vertex_buffer.push_back(aiuvs.y);
        }
        else
        {
            ret->vertex_buffer.push_back(0);
            ret->vertex_buffer.push_back(0);
        }
    }

    ret->index_buffer.reserve(mesh->mNumFaces * 3);

    for(int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace aiface = mesh->mFaces[i];

        if(aiface.mNumIndices <= 3)
        {
            for(int f = 0; f < aiface.mNumIndices; ++f)
            {
                uint indice = aiface.mIndices[f];

                ret->index_buffer.push_back(indice);
            }
        }
    }

    return ret;
}

void MeshManager::LoadToVRAM(Mesh *mesh)
{
    if(mesh != nullptr)
    {
        std::vector<SubMesh*> sub_meshes = mesh->GetSubMeshes();

        SPOOKYLOG(std::to_string(sub_meshes.size()));

        for(std::vector<SubMesh*>::iterator it = sub_meshes.begin(); it != sub_meshes.end(); ++it)
        {
            SubMesh* curr_submesh = (*it);

            if(!curr_submesh->loaded)
            {
                curr_submesh->loaded = true;

                // VAO
                curr_submesh->vao = RenderManager::Instance()->GenVertexArrayBuffer();
                RenderManager::Instance()->BindVertexArrayBuffer(curr_submesh->vao);

                // VBO
                curr_submesh->vbo = RenderManager::Instance()->GenBuffer();
                RenderManager::Instance()->BindArrayBuffer(curr_submesh->vbo);

                RenderManager::Instance()->LoadArrayToVRAM(curr_submesh->vertex_buffer.size() * sizeof(float),
                                                           &curr_submesh->vertex_buffer[0], GL_STATIC_DRAW);

                RenderManager::Instance()->EnableVertexAttributeArray(0);
                RenderManager::Instance()->EnableVertexAttributeArray(1);
                RenderManager::Instance()->EnableVertexAttributeArray(2);

                // Set info
                RenderManager::Instance()->SetVertexAttributePointer(0, 3, 8, 0);
                RenderManager::Instance()->SetVertexAttributePointer(1, 3, 8, 3);
                RenderManager::Instance()->SetVertexAttributePointer(2, 2, 8, 6);

                // VBIO
                curr_submesh->vbio = RenderManager::Instance()->GenBuffer();
                RenderManager::Instance()->BindElementArrayBuffer(curr_submesh->vbio);

                RenderManager::Instance()->LoadElementArrayToVRAM(curr_submesh->index_buffer.size() * sizeof(uint),
                                                                  &curr_submesh->index_buffer[0], GL_STATIC_DRAW);

                SPOOKYLOG("Loading mesh to VRAM with vao: " + std::to_string((curr_submesh->vao)));

                SPOOKYLOG("Loaded " + std::to_string(curr_submesh->vertex_buffer.size()) + " vertices to VRAM");
                SPOOKYLOG("Loaded " + std::to_string(curr_submesh->index_buffer.size()) + " indices to VRAM");

                // Clear
                RenderManager::Instance()->UnbindVertexArrayBuffer();

                RenderManager::Instance()->DisableVertexAttributeArray(0);
                RenderManager::Instance()->DisableVertexAttributeArray(1);
                RenderManager::Instance()->DisableVertexAttributeArray(2);
            }
        }
    }
}

void MeshManager::UnloadFromVRAM(Mesh *mesh)
{
    if(mesh != nullptr)
    {
        std::vector<SubMesh*> sub_meshes = mesh->GetSubMeshes();

        for(std::vector<SubMesh*>::iterator it = sub_meshes.begin(); it != sub_meshes.end(); ++it)
        {
            SubMesh* curr_submesh = (*it);

            if(curr_submesh->loaded)
            {
                curr_submesh->loaded = false;

                RenderManager::Instance()->DeleteFrameBuffer(curr_submesh->vao);

                curr_submesh->vao = 0;
            }
        }
    }
}

std::vector<Mesh *> MeshManager::GetAllMeshes() const
{
    return meshes;
}



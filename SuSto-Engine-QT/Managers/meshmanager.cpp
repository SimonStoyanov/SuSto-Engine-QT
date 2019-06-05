#include "meshmanager.h"
#include <qfile.h>
#include "Managers/rendermanager.h"
#include "Renderers/mesh.h"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/cfileio.h>
#include <assimp/Importer.hpp>
#include <assimp/importerdesc.h>
#include <assimp/scene.h>

MeshManager* MeshManager::instance = nullptr;

MeshManager::MeshManager()
{

}

Mesh* MeshManager::LoadMesh(const std::string &filepath)
{
    Mesh* ret = nullptr;

    Assimp::Importer importer;

    QFile file(filepath.c_str());

    bool all_correct = file.open(QIODevice::ReadOnly);

    if(all_correct)
    {
        QByteArray data = file.readAll();

        /*const aiScene* scene = importer.ReadFileFromMemory(data.data(), data.size(),
         aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes |
         aiProcess_PreTransformVertices | aiProcess_ImproveCacheLocality);*/

        const aiScene* scene = aiImportFile(filepath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

        all_correct = (scene != nullptr) && (scene->mRootNode != nullptr) && (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE == false);

        if(all_correct)
        {

        }
        else
        {
            SPOOKYLOG("Error loading mesh scene: " + filepath);
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

void MeshManager::ProcessNode(aiScene *scene, aiNode *node, Mesh *mesh)
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
        }

        for(int i = 0; i < curr_node->mNumChildren; ++i)
        {
            aiNode* node_to_add = curr_node->mChildren[i];

            nodes_to_check.push_back(node_to_add);
        }

        nodes_to_check.erase(nodes_to_check.begin());
    }
}

SubMesh *MeshManager::ProcessMesh(aiScene *scene, aiMesh *mesh)
{
    SubMesh* ret = new SubMesh();

    ret->has_uvs = mesh->HasTextureCoords(0);

    ret->vertex_buffer.reserve(mesh->mNumVertices * 2 * 3);

    if(ret->has_uvs)
    {
        ret->vertex_buffer.reserve(mesh->mNumVertices * 2);
    }

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
    }

    ret->index_buffer.reserve(mesh->mNumFaces * 3);

    for(int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace aiface = mesh->mFaces[i];

        if(aiface.mNumIndices <= 3)
        {
            for(int f = 0; f < aiface.mNumIndices; ++f)
            {
                uint indice = aiface.mIndices[i];

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
                int vbo = RenderManager::Instance()->GenBuffer();
                RenderManager::Instance()->BindArrayBuffer(vbo);

                RenderManager::Instance()->LoadArrayToVRAM(curr_submesh->vertex_buffer.size(),
                                                           &curr_submesh->vertex_buffer[0], GL_STATIC_DRAW);

                // VBIO
                uint vbio = RenderManager::Instance()->GenBuffer();
                RenderManager::Instance()->BindElementArrayBuffer(vbio);

                RenderManager::Instance()->LoadElementArrayToVRAM(curr_submesh->index_buffer.size(), &curr_submesh->index_buffer[0], GL_STATIC_DRAW);

                // Clear
                RenderManager::Instance()->UnbindVertexArrayBuffer();
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



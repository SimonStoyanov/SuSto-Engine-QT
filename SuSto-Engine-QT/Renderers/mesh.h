#ifndef MESH_H
#define MESH_H

#include <vector>
#include "globals.h"
#include "Renderers/vertexbuffer.h"

#include <filesystem>

class Mesh
{
    friend class MeshManager;
    friend class RenderTargetRenderer;

private:
    Mesh(const std::string& file_path);
    void operator delete(void *) {}

    void CleanUp();

public:
    int GetLoaded() const;

    int GetVao() const;
    int GetVbo() const;
    int GetVbio() const;

    int GetElementsCount();

    std::vector<std::string> GetTexturesDifusePaths() const;
    std::vector<std::string> GetTexturesHeightPaths() const;
    std::vector<std::string> GetTexturesNormalPaths() const;

    std::string GetFilePath() const;
    std::string GetFilePathPlusName();
    std::string GetFilePlusName();

private:
    std::string file_path = "";
    std::string name = "";
    std::experimental::filesystem::path filesystem_path;

private:
    std::vector<float> vertex_buffer;
    std::vector<uint> index_buffer;

    std::vector<std::string> textures_difuse_paths;
    std::vector<std::string> textures_height_paths;
    std::vector<std::string> textures_normals_paths;

    bool loaded = false;

    int vao = 0;
    int vbo = 0;
    int vbio = 0;
};

#endif // MESH_H

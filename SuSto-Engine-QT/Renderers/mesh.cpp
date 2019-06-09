#include "mesh.h"

Mesh::Mesh(const std::string &path)
{
    file_path = path;

    filesystem_path = path;
}

int Mesh::GetLoaded() const
{
    return loaded;
}

int Mesh::GetVao() const
{
    return vao;
}

int Mesh::GetVbo() const
{
    return vbo;
}

int Mesh::GetVbio() const
{
    return vbio;
}

int Mesh::GetElementsCount()
{
    return index_buffer.size();
}

std::vector<std::string> Mesh::GetTexturesDifusePaths() const
{
    return textures_difuse_paths;
}

std::vector<std::string> Mesh::GetTexturesHeightPaths() const
{
    return textures_height_paths;
}

std::vector<std::string> Mesh::GetTexturesNormalPaths() const
{
    return textures_normals_paths;
}

std::string Mesh::GetFilePath() const
{
    return file_path;
}

std::string Mesh::GetFilePathPlusName()
{
    return file_path + " [" + name + "]";
}

std::string Mesh::GetFilePlusName()
{
    return filesystem_path.filename().string() + " [" + name + "]";
}

#include "mesh.h"

Mesh::Mesh()
{

}

std::vector<SubMesh*> Mesh::GetSubMeshes() const
{
    return sub_meshes;
}

SubMesh::SubMesh()
{

}

void SubMesh::CleanUp()
{

}

int SubMesh::GetLoaded() const
{
    return loaded;
}

int SubMesh::GetVao() const
{
    return vao;
}

int SubMesh::GetVbo() const
{
    return vbo;
}

int SubMesh::GetVbio() const
{
    return vbio;
}

int SubMesh::GetElementsCount()
{
    return index_buffer.size();
}

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

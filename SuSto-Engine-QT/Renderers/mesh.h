#ifndef MESH_H
#define MESH_H

#include <vector>
#include "globals.h"
#include "Renderers/vertexbuffer.h"

class SubMesh
{
    friend class MeshManager;

public:
    SubMesh();

    void CleanUp();

    void LoadToVRAM();
    void UnloadFromVRAM();

private:
    std::vector<float> vertex_buffer;
    std::vector<uint> index_buffer;

    bool has_uvs = false;

    bool loaded = false;

    int vao = 0;
};

class Mesh
{
    friend class MeshManager;

private:
    Mesh();
    void operator delete(void *) {}

public:
    std::vector<SubMesh*> GetSubMeshes() const;

private:
    std::vector<SubMesh*> sub_meshes;
};

#endif // MESH_H
